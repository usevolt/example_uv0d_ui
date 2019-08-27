/* 
 * This file is part of the uv_hal distribution (www.usevolt.fi).
 * Copyright (c) 2017 Usevolt Oy.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/




#include "splashwindow.h"
#include "gui.h"
#include "main.h"
#include "uv_ft81x.h"



static uv_uiobject_ret_e step(void *user_ptr, const uint16_t step_ms);


#define this (&gui.splashwindow)

void splashwindow_init(void) {
	uv_uiwindow_init(&this->window, this->window_buffer, &uv_uistyles[0]);
	uv_uiwindow_set_stepcallback(&this->window, &step, NULL);
	uv_uiwindow_set_transparent(&this->window, false);
	uv_uidisplay_addxy(&gui.display, &this->window, 0, 0,
			uv_uibb(&gui.display)->width, uv_uibb(&gui.display)->height);

	uv_uitoucharea_init(&this->touch);
	uv_uiwindow_addxy(&this->window, &this->touch, 0, 0,
			uv_uibb(&this->window)->width, uv_uibb(&this->window)->height);
	this->finished = false;

	// download the splashscreen to middle of ft81x graphics RAM memory,
	// since it most probably is not used for anything else and
	// the splashscreen is shown only once on startup
	uv_uimedia_loadbitmapexmem(&this->uv_bitmap, FT81X_GRAPHIC_RAM_MAX_SIZE / 2,
			&gui.w25q128, "media/splashuv.png");
	uv_uiimage_init(&this->uv_img, &this->uv_bitmap, UIIMAGE_WRAP_BORDER, ALIGN_CENTER);
	uv_uiwindow_addxy(&this->window, &this->uv_img, 0, 0,
			uv_uibb(&this->window)->width, uv_uibb(&this->window)->height);

	color_st c;
	*((color_t*) &c) = uv_uiwindow_get_bgc(&this->window);
	c.a = 0;
	uv_uicolortransition_init(&this->transition, UITRANSITION_EASING_LINEAR, SPLASHWINDOW_ANIM_LEN_MS,
			uv_uiwindow_get_bgc(&this->window), *((color_t*) &c), &this->window.bg_c);
	uv_ui_add_transition(&this->window, &this->transition);

	uv_delay_init(&this->delay, SPLASHWINDOW_ANIMSTART_DELAY_MS);
}

static uv_uiobject_ret_e step(void *user_ptr, const uint16_t step_ms) {
	uv_uiobject_ret_e ret = UIOBJECT_RETURN_ALIVE;

	if (uv_uitoucharea_clicked(&this->touch, NULL, NULL)) {
		this->finished = true;
	}
	else {
		if (uv_delay(&this->delay, step_ms)) {
			uv_uitransition_play(&this->transition);
		}
		uv_uic_copy_alpha(&this->uv_img.blend_c, &this->window.bg_c);
		if (uv_uitransition_is_finished(&this->transition)) {
			this->finished = true;
		}
	}

	return ret;
}


void splashwindow_remove(void) {
	uv_uidisplay_remove(&gui.display, &this->window);
}


bool splashwindow_is_finished(void) {
	return this->finished;
}
