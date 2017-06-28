/*  snooze.c: simulates a snooze button: increment light from min to max,
    stay there five seconds and decrement light from max to min.

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

#include "light.h"

#define FL_OFF 0
#define FL_MAX 80

void main(){
    int i;
    float zzz = 0.1;
    for (i = FL_OFF; i < FL_MAX; i++) fl_set(i); sleep(zzz);
    sleep(5);
    for (i = FL_MAX; i > FL_OFF; i--) fl_set(i); sleep(zzz);
    fl_set(0);
}
