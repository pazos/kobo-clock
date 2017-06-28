/*  eink.c: functions to refresh the e-ink screen to display the contents
            of the framebuffer.

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
#include "mxcfb.h"

static void update_screen(int x, int y, int w, int h, int full){
    FILE* fb0;
    int fd;
    char update_mode;
    if (full == 1 ) {
        update_mode = UPDATE_MODE_FULL;
    } else {
	update_mode = UPDATE_MODE_PARTIAL;
    }
    fb0 = fopen("/dev/fb0", "r+");
    fd = fileno(fb0);
    struct fb_var_screeninfo vinfo;
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    struct mxcfb_update_data update = {
            .update_marker = 1,
            .update_region.top = y,
            .update_region.left = x,
            .update_region.width = w,
            .update_region.height = h,
            .waveform_mode = WAVEFORM_MODE_AUTO,
            .update_mode = update_mode,
            .temp = TEMP_USE_AMBIENT,
            .flags = 0,
        };
    ioctl(fd, MXCFB_SEND_UPDATE, &update);
}

void update_screen_full(){
    update_screen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
}

void update_screen_partial(){
    update_screen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void update_clock_partial(){
    update_screen( FRAME_LEFT, FRAME_TOP,
		   SCREEN_WIDTH - FRAME_RIGHT - FRAME_LEFT,
		   CLOCK_BOTTOM, 0 );
}

void update_panel_partial(){
    update_screen( FRAME_LEFT, CLOCK_BOTTOM,
		   SCREEN_WIDTH - FRAME_RIGHT - FRAME_LEFT,
		   SCREEN_HEIGHT - FRAME_BOTTOM - CLOCK_BOTTOM, 0 );
}
