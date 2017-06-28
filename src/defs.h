/*  defs.h: common definitions

    This file is part of kobo-clock.

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

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#include "init.h"
#include "rect.h"
#include "eink.h"
#include "light.h"

#define FONT_TYPE_SPACE   "fonts/spacemono-bold.ttf"
#define FONT_TYPE_UBUNTU  "fonts/ubuntu-mono.ttf"

#define IMAGE_BACKGROUND  "bitmaps/clock.bmp"
#define IMAGE_CELSIUS     "bitmaps/celsius.bmp"

#define WEATHER_UTIL      "bin/weather.sh"
#define TIME_UTIL         "bin/date.sh"

#define SCREEN_WIDTH      1440 //Aura HD - landscape width
#define SCREEN_HEIGHT     1080 //Aura HD - landscape height

#define FRAME_TOP          100
#define FRAME_LEFT         150
#define FRAME_RIGHT        150
#define FRAME_BOTTOM       100
#define CLOCK_BOTTOM       500

#define CLOCK_MARGIN_LEFT  372
#define PANEL_MARGIN_LEFT  200

#define FONT_SIZE_TIME     248
#define FONT_SIZE_DATE      80
#define FONT_SIZE_TEMP     144
#define FONT_SIZE_CITY      64
