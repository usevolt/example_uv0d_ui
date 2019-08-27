/*
 * uw_messages.c
 *
 *  Created on: Feb 19, 2015
 *      Author: usenius
 */


#include "main.h"
#include "messages.h"
#include "pin_mappings.h"
#include "gui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uv_timer.h>
#include <uv_utilities.h>
#include <uv_eeprom.h>

extern dev_st dev;
#define this (&dev)




void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void clear_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void files_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void hour_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);

const uv_command_st terminal_commands[] = {
		{
				.id = CMD_STAT,
				.str = "stat",
				.instructions = "Displays the system status information.\n"
						"Usage: stat",
				.callback = &stat_callb
		},
		{
				.id = CMD_CLEAR,
				.str = "clear",
				.instructions = "Clears the ext flash memory sector.\n"
						"Usage: clear (address)",
				.callback = &clear_callb
		},
		{
				.id = CMD_FILES,
				.str = "files",
				.instructions = "Lists all media files found in the external memory.\n",
				.callback = &files_callb
		},
		{
				.id = CMD_HOUR,
				.str = "hour",
				.instructions = "Clears or sets the hour counter. \n"
						"Usage: hour <uv_password> (value)",
				.callback = &hour_callb
		}
};




unsigned int commands_size(void) {
	return sizeof(terminal_commands) / sizeof(uv_command_st);
}




void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	printf("SYSTEM STATUS:\n\n");

	printf("FT81X RAMDL usage: %u %%\n",
			(unsigned int) (100 * uv_ft81x_get_ramdl_usage() / FT81X_RAMDL_SIZE));
	uint32_t i = 0;
	uv_fd_st fd;
	uint32_t usage = 0;
	while (uv_exmem_index(&gui.w25q128, i++, &fd)) {
		usage = fd.data_addr + fd.file_size;
	}
	printf("w25q128 memory usage: %u bytes (%u %%)\n", (unsigned int) usage,
			(unsigned int) (100ULL * usage / (W25Q128_PAGE_SIZE * W25Q128_PAGE_COUNT)));
}


void clear_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	if (args) {
		printf("Clearing w25q128 memory from address %u\n", (unsigned int) argv[0].number);
		uv_w25q128_clear_sector_at(&gui.w25q128, argv[0].number);
	}
	else {
		printf("Clearing the whole memory\n");
		uv_w25q128_clear(&gui.w25q128);
		printf("Done\n");
	}
}


void files_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	uint32_t i = 0;
	uv_fd_st fd;
	while (uv_exmem_index(&gui.w25q128, i++, &fd)) {
		printf("Filename: %s\nsize: %u\naddress: 0x%x\n\n",
				fd.filename, (unsigned int) fd.file_size, (unsigned int) fd.data_addr);
	}
}


void hour_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	if (args && argv[0].type == ARG_STRING) {

		// Settings the usage hours requires a password, which in this example is "uv"
		if (strcmp(argv[0].str, "uv") == 0) {

			CANOPEN_TYPEOF(UV0D_HOUR_COUNTER_TYPE) value = 0;
			// clear the old data
			for (uint8_t i = 0; i < HOUR_COUNTER_COUNT; i++) {
				uv_eeprom_write(&value, sizeof(value), HOUR_COUNTER_EEPROM_ADDR + sizeof(value) * i);
			}
			if (args > 1 && argv[1].type == ARG_INTEGER) {
				value = argv[1].number;
				// write the new data
				uv_eeprom_write(&value, sizeof(value), HOUR_COUNTER_EEPROM_ADDR);
			}
			dev.hours_dh = value;
			dev.hours_us = 0;
		}
		printf("hour counter: %u.%u h\n",
				(unsigned int) dev.hours_dh / 10,
				(unsigned int) dev.hours_dh % 10);
	}
	else {
		printf("Give at least the password as an argument.\n"
				"The correct password is found in the source code, \n"
				"messages.c file, line 113.\n");
	}
}





