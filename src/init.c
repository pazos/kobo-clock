/*  init.c: functions to init/quit/interrupt an SDL application

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
#include "SDL_ttf.h"

SDL_Surface *screen;

void sdl_init(void) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
	fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
	exit(1);
        }

    if ( TTF_Init() < 0 ) {
        fprintf(stderr, "Couldn't initialize TTF: %s\n",SDL_GetError());
        exit(2);
        }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 8, SDL_SWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Couldn't set video mode: %s\n",SDL_GetError());
        exit(3);
        }
}

void cleanup(int exitcode) {
    if (exitcode != 0){
        fprintf(stderr, "Exiting with code %d\n", exitcode);
        }
    TTF_Quit();
    SDL_Quit();
    exit(exitcode);
}

void interrupt(int sig) {
    if (sig == SIGINT){
       fprintf(stderr, "Ctrl+C pressed. exiting...\n");
       exit(0);
       }
}

void quit(void){
    cleanup(0);
}
