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


#ifndef SPLASHWINDOW_H_
#define SPLASHWINDOW_H_

#include <uv_utilities.h>
#include <uv_ui.h>

#define SPLASHWINDOW_BUFFER_LEN		5
#define SPLASHWINDOW_ANIM_LEN_MS	500
#define SPLASHWINDOW_ANIMSTART_DELAY_MS	3000

typedef struct {
	uv_uiwindow_st window;
	uv_uiobject_st* window_buffer[SPLASHWINDOW_BUFFER_LEN];

	uv_uitoucharea_st touch;
	uv_uicolortransition_st transition;
	uv_delay_st delay;

	uv_uimedia_st uv_bitmap;
	uv_uiimage_st uv_img;
	bool finished;
} splashwindow_st;





void splashwindow_init(void);

/// @brief: Returns true when the splashwindow has been disappeared
bool splashwindow_is_finished(void);

/// @brief: Remove should be called after the splashscreen
/// has been shown, to free memory to other windows
void splashwindow_remove(void);



#endif /* SPLASHWINDOW_H_ */
