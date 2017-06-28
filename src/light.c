/*  light.c: function to handle the frontlight

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

#include "defs.h"

// set a FrontLight value
void fl_set(int value){
    if (value >= 0 && value <= 100){
        int fl = open("/dev/ntx_io", O_RDWR);
        if (fl != -1) ioctl(fl, 241, value);
        }
}
