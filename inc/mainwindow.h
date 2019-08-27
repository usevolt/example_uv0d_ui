/*
 * This file is part of the uv_hal distribution (www.usevolt.fi).
 * Copyright (c) 2017 Usevolt Oy.
 *
 *
 * MIT License
 *
 * Copyright (c) 2019 usevolt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef INC_MAINWINDOW_H_
#define INC_MAINWINDOW_H_


#include <uv_utilities.h>
#include <uv_ui.h>


/// @file: Defines a UI window named *mainwindow*.
/// A simple example of how to create different screens on UV0D.
/// Use this example file to create other screens.

// Define a buffer that is big enough to hold all the uiobjects which are
// drawn on this mainwindow
#define MAINWINDOW_BUFFER_SIZE	10

typedef struct {
	// EXTENDS macro is a nice way (although a bit dirty as it violates the MISRA C standard)
	// of creating an object which is inherited from another object in C.
	// The EXTENDS macro **has to be the first member inside the structure**!
	EXTENDS(uv_uiwindow_st);

	uv_uiobject_st *buffer[MAINWINDOW_BUFFER_SIZE];

	uv_uibutton_st button;
	uv_uitogglebutton_st togglebutton;
	uv_uilistbutton_st listbutton;
	uv_uimediabutton_st mediabutton;
	uv_uislider_st slider;
	uv_uiimage_st en_image;
	uv_uiprogressbar_st progressbar;
	uv_uiscalartransition_st progressbar_transition;
	uv_uicheckbox_st checkbox;
	uv_uidigitedit_st digitedit;
	uv_uiacceptdialog_st acceptidalog;

	bool animation_on;


	uv_uimedia_st en_bitmap;
	uv_uimedia_st fi_bitmap;

} mainwindow_st;

/// @brief: Initializes the mainwindow. Should be called prior to adding it
/// to any display and prior to claling mainwindow_show.
void mainwindow_init(mainwindow_st *this);

/// @brief: Shows up the mainwindow
///
/// @param this: Pointer to the actual mainwindow structure
/// @param parent_window: The parent window where the mainwindow is shown.
/// Usually means the uidisplay itself.
void mainwindow_show(mainwindow_st *this);


#endif /* INC_MAINWINDOW_H_ */
