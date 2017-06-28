/*  rect.c: define the position of the elements on the screen.

    This file is part of kobo-clock

    kobo-clock is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    kobo-clock is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with kobo-clock.  If not, see <http://www.gnu.org/licenses/>. */

#include "defs.h"
#include "SDL.h"

SDL_Rect r_background, r_clock_time, r_clock_date, r_city, r_temp,
    r_icon, r_weather;

void set_position(void) {

    r_background.x = 0;
    r_background.y = 0;
    r_background.w = SCREEN_WIDTH;
    r_background.h = SCREEN_HEIGHT;

    r_clock_time.x = CLOCK_MARGIN_LEFT;
    r_clock_time.y = FRAME_TOP;
    r_clock_time.w = SCREEN_WIDTH - FRAME_RIGHT - CLOCK_MARGIN_LEFT;
    r_clock_time.h = 280;

    r_clock_date.x = CLOCK_MARGIN_LEFT;
    r_clock_date.y = FRAME_TOP + 300;
    r_clock_date.w = SCREEN_WIDTH - FRAME_RIGHT - CLOCK_MARGIN_LEFT;
    r_clock_date.h = 80;

    r_city.x = PANEL_MARGIN_LEFT;
    r_city.y = CLOCK_BOTTOM + 50;
    r_city.w = FRAME_RIGHT - FRAME_LEFT - PANEL_MARGIN_LEFT;
    r_city.h = 100;

    r_temp.x = PANEL_MARGIN_LEFT;
    r_temp.y = CLOCK_BOTTOM + 150;
    r_temp.w = 150;
    r_temp.h = 150;

    r_icon.x = PANEL_MARGIN_LEFT + 140;
    r_icon.y = CLOCK_BOTTOM + 150;
    r_icon.w = 150;
    r_icon.h = 150;

    r_weather.x = SCREEN_WIDTH - FRAME_RIGHT - 380;
    r_weather.y = CLOCK_BOTTOM;
    r_weather.w = 350;
    r_weather.h = 350;
}
