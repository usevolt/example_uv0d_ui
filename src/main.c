/*
===============================================================================
 Name        : main.c
 Author      : Olli Usenius
 Version     :
 Copyright   : $(copyright)
 Description :
===============================================================================
*/


#include <uv_utilities.h>
#include <uv_rtos.h>
#include <string.h>
#include <uv_eeprom.h>
#include <uv_timer.h>
#include <uv_wdt.h>
#include "main.h"
#include "messages.h"
#include "pin_mappings.h"
#include "gui.h"

dev_st dev = {};
static bool initialized = false;
#define this ((dev_st*) &dev)
#define HOUR_COUNTER_UPDATE_US			(1000000 * 60 * 6)




/// @brief: Returns the hour count from EEPROM memory in desihours, e.g.
/// one tenth of hours precision
static CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) get_hours(void) {
	CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) ret = 0;
	for (uint8_t i = 0; i < HOUR_COUNTER_COUNT; i++) {
		CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) value;
		uv_eeprom_read(&value, sizeof(value), HOUR_COUNTER_EEPROM_ADDR + sizeof(value) * i);
		if (value > ret) {
			ret = value;
		}
	}
	return ret;
}

/// @brief: Writes the usage hours to the EEPROM.
/// The hour count is distributed across multiple EEPROM locations,
/// to reduce the write count to the same address. EEPROM memory endures ~100000
/// write cycles, thus one tenth of hour precision might cause memory corruption
/// after 10000 hours. To prevent this, the hour count is written in multiple
/// locations, thus reducing the write stress for each address.
///
/// @param value: Hours in desihours, e.g. one tenth of hours
static void store_hours(CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) value) {
	uint32_t addr  = HOUR_COUNTER_EEPROM_ADDR;
	CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) smallest_hours;
	uv_eeprom_read(&smallest_hours, sizeof(smallest_hours), HOUR_COUNTER_EEPROM_ADDR);

	for (uint8_t i = 1; i < HOUR_COUNTER_COUNT; i++) {
		CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) value;
		uv_eeprom_read(&value, sizeof(value), HOUR_COUNTER_EEPROM_ADDR + sizeof(value) * i);
		if (value < smallest_hours) {
			smallest_hours = value;
			addr = HOUR_COUNTER_EEPROM_ADDR + sizeof(value) * i;
		}
	}
	if (value > smallest_hours) {
		uv_eeprom_write(&value, sizeof(value), addr);
	}
}


bool dev_initialied(void) {
	return initialized;
}





void init(dev_st* me) {

	// load non-volatile data
	if (uv_memory_load(MEMORY_APP_PARAMS)) {

		// Loading the non-volatile settings failed. This usually means
		// that the CRC checksums didn't match, so it's possible
		// that the device is booting up the first time. Thus
		// initialize all the data between *data_start* and *data_end*
		// to their default value.
		memset(this->array_example, 0, sizeof(this->array_example));
		this->lang = UV0D_LANG_DEFAULT;

		// Lastly save the settings. Since the non-volatile data is actually
		// the mcu flash memory, the settings shouldn't be written too often.
		// The flash memory can sustain only ~10000 write cycles or so.
		uv_memory_save();
	}

	// initialize the command line interface for system developers
	uv_terminal_init(terminal_commands, commands_size());

	this->dev_type = 1;
	strcpy(this->dev_name, "UV0D");

	// make sure to initialize the hour counter eeprom
	for (uint8_t i = 0; i < HOUR_COUNTER_COUNT; i++) {
		CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) value;
		uv_eeprom_read(&value, sizeof(value),
				HOUR_COUNTER_EEPROM_ADDR + sizeof(value) * i);
		if (value == 0xFFFFFFFF) {
			value = 0;
			uv_eeprom_write(&value, sizeof(value),
					HOUR_COUNTER_EEPROM_ADDR + sizeof(value) * i);
		}
	}
	this->hours_dh = get_hours();
	this->hours_us = 0;
	// start up the hour counter timer
	uv_timer_init(HOUR_COUNTER_TIMER);
	uv_timer_start(HOUR_COUNTER_TIMER);

	// mark the system to initialized. After this the GUI task can initialize itself
	initialized = true;

	// If the CANopen system doesn't have an NMT master device, the
	// UV0D can set itself to OPERATIONAL state, starting to send TXPDO messages
	// and receive RXPDO messages. Usually this is done by the NMT Master,
	// but this example shows a simple way of transmitting PDO messages without
	// the dependency of the NMT Master. Note that this actually violates the
	// CANopen standard.
	uv_canopen_set_state(CANOPEN_OPERATIONAL);
}




// The main application step function. FreeRTOS task functions should never return!
static void step(void* me) {

	init(this);

	while (true) {
		unsigned int step_ms = 20;
		// update watchdog timer value to prevent a hard reset
		// Note that the WDT has to be enabled with CONFIG_WDT symbol.
		// This example disables the WDT to make finding bugs easier.
		// In case of a system bug, the processor ends up in HardFault
		// and the WDT doesn't reset the device.
		 uv_wdt_update();

		// terminal step function
		uv_terminal_step();

		// hour counter logic
		uint32_t hours = uv_timer_get_us(HOUR_COUNTER_TIMER);
		if (hours > 1000000) {
			uv_timer_clear(HOUR_COUNTER_TIMER);
			this->hours_us += hours;
			if (this->hours_us > HOUR_COUNTER_UPDATE_US) {
				this->hours_us = 0;
				this->hours_dh++;
				store_hours(this->hours_dh);
			}
		}

		uv_rtos_task_delay(step_ms);
	}
}






int main(void) {
	// initialize the uv_hal library. Mandatory!
	uv_init(&dev);

	// create a task for the main program step function
	// The memory available for the RTOS is defined with
	// CONFIG_RTOS_HEAP_SIZE in uv_hal_config.h
	uv_rtos_task_create(&step, "step", UV_RTOS_MIN_STACK_SIZE * 2,
			&dev, UV_RTOS_IDLE_PRIORITY + 1, NULL);

	// create a task for the GUI. Make sure to give the GUI enough memory.
	// The memory available for the RTOS is defined with
	// CONFIG_RTOS_HEAP_SIZE in uv_hal_config.h
	uv_rtos_task_create(&gui_step, "gui", UV_RTOS_MIN_STACK_SIZE * 4,
			NULL, UV_RTOS_IDLE_PRIORITY + 1, NULL);

	// start up the FreeRTOS scheduler
	uv_rtos_start_scheduler();


    // Enter an infinite loop
	// never should end up here
    while(1) {
    	printf("scheduler returned??\n");
    }
    return 0;
}
