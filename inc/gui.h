/*
 * gui.h
 *
 *  Created on: Jul 29, 2017
 *      Author: usevolt
 */

#ifndef GUI_H_
#define GUI_H_


#include <uv_utilities.h>
#include <uv_ui.h>
#include <uv_ft81x.h>
#include <uv_w25q128.h>
#include "splashwindow.h"
#include "mainwindow.h"


// menuwindow adds itself to the display, make sure the display len is one bigger
// than uiobjects on gui_st structure
#define DISPLAY_BUFFER_LEN	4
#define DEFAULT_BRIGHTNESS	50


typedef struct {
	// module for the external flash available on UV0D
	uv_w25q128_st w25q128;

	// the uidisplay represents the main LCD display in uv_hal UI library
	uv_uidisplay_st display;
	uv_uiobject_st *buffer[DISPLAY_BUFFER_LEN];

	// splashwindow is shown when the system boots
	splashwindow_st splashwindow;

	// all the windows which are shown on the LCD. Putting the windows inside
	// a union saves *alot* of memory, since union ensures that all it's
	// members are located in a same memory address.
	// The drawback is that two union members cannot be available at the same time.
	// Thus union is a good place for windows which fill up the whole screen, but
	// not for windows that use for example transitions, to move over each other.
	// During the transition both windows have to be visible at the same time.
	union {
		mainwindow_st mainwindow;
	};


} gui_st;
extern gui_st gui;


/// @brief: Initializes the GUI
void gui_init(void);


/// @brief: Gui step function. Should be initialized from main.c
/// to keep all FreeRTOS task creations in a one place
void gui_step(void *nullptr);


/// @brief: Sets the display backlight. Pretty straight forward..?
static inline void gui_set_backlight(uint8_t percent) {
	uv_ft81x_set_backlight(percent);
}


/// @brief: Takes care of calibrating the LCD touchscreen
void gui_calibrate_touchscreen(void);





#endif /* GUI_H_ */
