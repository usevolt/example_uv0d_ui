/*
 * main.h
 *
 *  Created on: Apr 26, 2015
 *      Author: usevolt
 */

#ifndef MAIN_H_
#define MAIN_H_


#include <uv_memory.h>
#include <uv_filters.h>
#include <uv_ft81x.h>
#include "can_uv0d.h"


#define FT81X_EEPROM_ADDR			0
#define FT81X_EEPROM_LEN			(sizeof(ft81x_transfmat_st) + sizeof(uint16_t))
#define HOUR_COUNTER_EEPROM_ADDR	(FT81X_EEPROM_ADDR + FT81X_EEPROM_LEN)
#define HOUR_COUNTER_COUNT			10
#define HOUR_COUNTER_EEPROM_LEN		(CANOPEN_SIZEOF(UV0D_HOUR_COUNTER_TYPE) * HOUR_COUNTER_COUNT)





/// @brief: main data structure.
/// This struct can be save to non-volatile flash memory with
/// a terminal commmand 'save'.
typedef struct _dev_st {

	// type of this device in the uvcan network, i.e. UV0D_DEV_TYPE
	CANOPEN_TYPEOF(UV0D_DEV_TYPE_TYPE) dev_type;

	// stores the current hours with 1/10 hour precision
	CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) hours_dh;
	uint64_t hours_us;

	char dev_name[UV0D_DEV_NAME_STRING_LEN];

	// this marks the start of non-volatile data.
	// All the data between *data_start* and *data_end*
	// are saved in mcu flash memory with *uv_memory_save*
	// and can be loaded with *uv_memory_load*.
	// Since uv_hal has no way of telling what the data should contain,
	// verifying the coherency of the data should be done
	// by the application.
	uv_data_start_t data_start;

	CANOPEN_TYPEOF(UV0D_ARRAY_EXAMPLE_TYPE)
		array_example[UV0D_ARRAY_EXAMPLE_ARRAY_MAX_SIZE];

	uv0d_lang_e lang;

	uv_data_end_t data_end;

} dev_st;


extern dev_st dev;

void init(dev_st* me);


bool dev_initialied(void);


#endif /* MAIN_H_ */
