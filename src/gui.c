/*
 * gui.c
 *
 *  Created on: Jul 29, 2017
 *      Author: usevolt
 */


#include "gui.h"
#include "main.h"
#include <uv_rtos.h>
#include <uv_eeprom.h>
#include <uv_terminal.h>






gui_st gui;
#define this (&gui)




void gui_init(void) {

	// wait until the main task has been initialized. This is important since
	// the main task is responsible for loading the non-volatile settings from memory.
	while (!dev_initialied()) {
		uv_rtos_task_yield();
	}

	// initialize the external flash memory module
	if (uv_w25q128_init(&this->w25q128, SPI1, SPI_SLAVE0) != ERR_NONE) {
		uv_terminal_enable();
		printf("**** ERROR **** W25Q128 initialization failed.\n");
	}

	// initialize the LCD driver
	bool calib_req = uv_ft81x_init();

	// read the touchscreen calibration data from the EEPROM memory
	ft81x_transfmat_st mat;
	uint16_t crc;
	uv_eeprom_read(&mat, sizeof(mat), FT81X_EEPROM_ADDR);
	uv_eeprom_read(&crc, sizeof(crc), FT81X_EEPROM_ADDR + sizeof(mat));
	// check if the transform matrix crc matches the one fetched from the EEPROM memory
	if (calib_req ||
			(uv_memory_calc_crc(&mat, sizeof(mat)) != crc) ||
			(crc == 0)) {
		// crc doesn't match, we have to calibrate the display
		gui_calibrate_touchscreen();
	}
	else {
		// crc matches, fetch the values from eeprom
		uv_ft81x_touchscreen_set_transform_matrix(&mat);
	}
	// set the display brightness
	uv_ft81x_set_backlight(DEFAULT_BRIGHTNESS);



	// initialize the UI library
	uv_uidisplay_init(&this->display, this->buffer, &uv_uistyles[0]);

	uint8_t step_ms = 20;

	// initialize the mainwindow and add it to the screen.
	// Te mainwindow is drawn only after calling the mainwindow_show.
	mainwindow_init(&gui.mainwindow);
	uv_uidisplay_addxy(&gui.display, &gui.mainwindow, 0, 0,
			uv_uibb(&gui.display)->width, uv_uibb(&gui.display)->height);
	mainwindow_show(&gui.mainwindow);

	// show splashscreen
	splashwindow_init();
	// the main application loop for as long as the splash window is present
	while (!splashwindow_is_finished()) {
		uv_uidisplay_step(&this->display, step_ms);
		uv_w25q128_step(&this->w25q128, step_ms);
		uv_rtos_task_delay(step_ms);
	}
	splashwindow_remove();

}





// The main GUI task loop. FreeRTOS task functions should never return!
void gui_step(void *nullptr) {
	gui_init();

	while (true) {
		uint16_t step_ms = 20;

		uv_w25q128_step(&this->w25q128, step_ms);

		uv_uidisplay_step(&this->display, step_ms);

		uv_rtos_task_delay(step_ms);
	}
}



void gui_calibrate_touchscreen(void) {
	ft81x_transfmat_st mat;
	uint16_t crc;
	uv_eeprom_read(&mat, sizeof(mat), FT81X_EEPROM_ADDR);
	uv_eeprom_read(&crc, sizeof(crc), FT81X_EEPROM_ADDR + sizeof(mat));

	uv_ft81x_touchscreen_calibrate(&mat);
	crc = uv_memory_calc_crc(&mat, sizeof(mat));
	// store results to eeprom with crc
	uv_eeprom_write(&mat, sizeof(mat), FT81X_EEPROM_ADDR);
	uv_eeprom_write(&crc, sizeof(crc), FT81X_EEPROM_ADDR + sizeof(mat));
}




