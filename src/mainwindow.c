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

#include "mainwindow.h"
#include "main.h"
#include "gui.h"
#include <uv_reset.h>


static uv_uiobject_ret_e step(void *user_ptr, const uint16_t step_ms);



void mainwindow_init(mainwindow_st *this) {
	// since this object inherits the uv_uiwindow_st, make sure to
	// initialize it
	uv_uiwindow_init(this, this->buffer, &uv_uistyles[0]);

	uint32_t addr = 0;

	// load the english flag
	// See the documentation of uv_uimedia_loadbitmapexmem for
	// information about supported media files
	addr += uv_uimedia_loadbitmapexmem(&this->en_bitmap,
			addr, &gui.w25q128, "media/en.png");

	// load the finnish flag
	// See the documentation of uv_uimedia_loadbitmapexmem for
	// information about supported media files
	addr += uv_uimedia_loadbitmapexmem(&this->fi_bitmap,
			addr, &gui.w25q128, "media/fin.png");

}


static const char *listbutton_content[UV0D_LANG_COUNT] = {
		"English",
		"Suomi"
};


void mainwindow_show(mainwindow_st *this) {
	uv_uiwindow_clear(this);
	// register a step function for mainwindow. Step function
	// will be called on each step cycle
	uv_uiwindow_set_stepcallback(this, &step, this);

	// uigridlayout is a helper module that simplifies greatly
	// the ui component placement
	uv_uigridlayout_st grid;
	uv_uigridlayout_init(&grid, 0, 0,
			uv_uibb(this)->width, uv_uibb(this)->height, 2, 4);
	uv_uigridlayout_set_padding(&grid, 5, 5);
	uv_uigridlayout_set_vertical_order(&grid);
	// each call to uv_uigridlayout_next returns a bounding box
	// which has the coordinates for each grid layout cell.
	// Make sure not to clal uv_uigridlayout_next too many times!
	uv_bounding_box_st bb = uv_uigridlayout_next(&grid);

	// initialize the reset button.
	// Also a good example how to create a multilingual user interface with uv_uitr.
	// Note that any special characters are not supported, only ASCII basic set.
	uv_uibutton_init(&this->button,
			uv_uitr(dev.lang, "Reset the UV0D", "Resetoi UV0D"), &uv_uistyles[0]);
	uv_uiwindow_add(this, &this->button, &bb);

	bb = uv_uigridlayout_next(&grid);
	uv_uitogglebutton_init(&this->togglebutton, false,
			uv_uitr(dev.lang, "Animation", "Animaatio"),
			&uv_uistyles[0]);
	uv_uiwindow_add(this, &this->togglebutton, &bb);

	bb = uv_uigridlayout_next(&grid);
	uv_uilistbutton_init(&this->listbutton, (char**) listbutton_content,
			sizeof(listbutton_content) / sizeof(listbutton_content[0]),
			dev.lang, &uv_uistyles[0]);
	uv_uilistbutton_set_title(&this->listbutton,
			uv_uitr(dev.lang, "System language:", "Jarjestelman kieli:"));
	uv_uiwindow_add(this, &this->listbutton, &bb);

	bb = uv_uigridlayout_next(&grid);
	uv_uimediabutton_init(&this->mediabutton,
			uv_uitr(dev.lang, "God Save the Queen", "Suomi Perkele"),
			(dev.lang == UV0D_LANG_EN) ? &this->en_bitmap : &this->fi_bitmap,
					&uv_uistyles[0]);
	uv_uiwindow_add(this, &this->mediabutton, &bb);

	bb = uv_uigridlayout_next(&grid);
	uv_uislider_init(&this->slider, 10, FT81X_BACKLIGHT_MAX,
			uv_ft81x_get_backlight(), &uv_uistyles[0]);
	uv_uislider_set_horizontal(&this->slider);
	uv_uislider_set_inc_step(&this->slider, 5);
	uv_uislider_set_title(&this->slider,
			uv_uitr(dev.lang, "Screen Brightness", "Nayton Kirkkaus"));
	uv_uiwindow_add(this, &this->slider, &bb);

	// progressbar shows how to use colors and uitransitions for animating the user interface
	bb = uv_uigridlayout_next(&grid);
	uv_uiprogressbar_init(&this->progressbar, 0, 100, &uv_uistyles[0]);
	uv_uiprogressbar_set_horizontal(&this->progressbar);
	uv_uiprogressbar_set_limit(&this->progressbar, UI_PROGRESSBAR_LIMIT_UNDER, 30, C(0xFFFF0000));
	uv_uiscalartransition_init(&this->progressbar_transition, UITRANSITION_EASING_INOUT_QUAD,
			500, 0, 100, &this->progressbar.value);
	uv_uiobject_set_transition(&this->progressbar, &this->progressbar_transition);
	uv_uiwindow_add(this, &this->progressbar, &bb);

	bb = uv_uigridlayout_next(&grid);
	uv_uicheckbox_init(&this->checkbox, false, uv_uitr(dev.lang, "Animation", "Animaatio"),
			&uv_uistyles[0]);
	uv_uiwindow_add(this, &this->checkbox, &bb);

	bb = uv_uigridlayout_next(&grid);
	uv_uidigitedit_init(&this->digitedit, uv_uistyles[0].font, C(0xFFFFFFFF),
			0, &uv_uistyles[0]);
	uv_uidigitedit_set_minlimit(&this->digitedit, -100);
	uv_uidigitedit_set_maxlimit(&this->digitedit, 100);
	uv_uidigitedit_set_title(&this->digitedit, uv_uitr(dev.lang,
			"Some value", "Joku luku"));
	uv_uidigitedit_set_numpad_title(&this->digitedit, uv_uitr(dev.lang,
			"Give a value between -100 ... 100", "Anna luku valilta -100 ... 100"));
	uv_uiwindow_add(this, &this->digitedit, &bb);

	this->animation_on = false;
}


static uv_uiobject_ret_e step(void *user_ptr, const uint16_t step_ms) {
	// The step function return value tells uv_hal ui library if this
	// object has been deleted during the step function. This
	// can happen if the windows are stored inside a union
	// (as in this example project) and a new window is shown.
	// In that case this step function should return UIOBJECT_RETURN_KILLED
	// to prevent UI glitches, and in worst case a HardFault.
	uv_uiobject_ret_e ret = UIOBJECT_RETURN_ALIVE;

	// user_ptr can be used to pass any pointer to the step function.
	// Since we passed pointer to our mainwindow structure when adding the step
	// function with uv_uiwindow_set_stepcallback, we can reach the objects
	// contained in the mainwindow.
	mainwindow_st *this = user_ptr;

	if (this->animation_on) {
		switch(uv_uitransition_get_state(&this->progressbar_transition)) {
		case UITRANSITION_INIT:
		case UITRANSITION_PAUSE:
			uv_uitransition_play(&this->progressbar_transition);
			break;
		case UITRANSITION_FINISH:
			uv_uitransition_reverseplay(&this->progressbar_transition);
			break;
		default:
			break;
		}
	}
	else {
		uv_uitransition_pause(&this->progressbar_transition);
	}

	// todo: Implement the display logic here when the uiobjects on the screen
	// are touched or used...

	if (uv_uibutton_clicked(&this->button)) {
		if (uv_uiacceptdialog_exec(&this->acceptidalog,
				uv_uitr(dev.lang, "Are you sure you want to reset the UV0D?",
						"Haluatko varmasti kaynnistaa UV0D:n uudelleen?"),
				uv_uitr(dev.lang, "Yes", "Kylla"),
				uv_uitr(dev.lang, "No", "Ei"),
				&uv_uistyles[0]) == UIACCEPTDIALOG_RET_YES) {
			uv_system_reset();
		}
	}
	else if (uv_uitogglebutton_clicked(&this->togglebutton)) {
		this->animation_on = uv_uitogglebutton_get_state(&this->togglebutton);
		uv_uicheckbox_set_state(&this->checkbox, this->animation_on);
	}
	else if (uv_uicheckbox_clicked(&this->checkbox)) {
		this->animation_on = uv_uicheckbox_get_state(&this->checkbox);
		uv_uitogglebutton_set_state(&this->togglebutton, this->animation_on);
	}
	else if (uv_uilistbutton_clicked(&this->listbutton)) {
		// set the system language and refresh the display
		dev.lang = uv_uilistbutton_get_current_index(&this->listbutton);
		mainwindow_show(this);
		// remember to set the return value to UIOBJECT_RETURN_KILLED,
		// to prevent glitches since mainwindow_show initializes all the contained objects
		// to their default values. We dont want this step function to continue
		// executing the step function for any other objects that the
		// mainwindow might have contained.
		ret = UIOBJECT_RETURN_KILLED;
	}
	else if (uv_uislider_value_changed(&this->slider)) {
		gui_set_backlight(uv_uislider_get_value(&this->slider));
	}
	else if (uv_uimediabutton_clicked(&this->mediabutton)) {
		static char str[50] = {};
		if (uv_uikeyboard_show(uv_uitr(dev.lang, "Enter some text", "Syota jotain tekstia"),
				str, sizeof(str), &uv_uistyles[0])) {
			uv_uimediabutton_set_text(&this->mediabutton, str);
			// setting the text might not trigger the window refresh if
			// the mediabutton already had the same text pointer assigned. Thus,
			// we make sure that the mediabutton get's refreshed.
			uv_ui_refresh(&this->mediabutton);
		}
	}
	else {

	}

	return ret;
}
