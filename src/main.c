/*  kobo-clock: a simple clock for kobos.

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

int main(int argc, char *argv[]) {
    int uptime = 0;
    int counter = 0;

    char last_time[5] = "24:00";
    char last_date[30] = "Saturday, 31 of February";
    char last_info[80] = " city | weather-icon.bmp | degrees_celsius";

    char time[10], date[20], city[20], weather_icon[10], temperature[4],
         buffer[80], string[80], icon[40];

    SDL_Color black = {0,0,0};
    SDL_Color white = {255,255,255};

    // start SDL and SDL_ttf
    sdl_init();
    extern SDL_Surface *screen;

    // define SDL_Rects
    set_position();
    extern SDL_Rect r_background, r_clock_time, r_clock_date,
                    r_city, r_temp, r_icon, r_weather;

    // handle signals and exit gracefully:
    signal (SIGINT, interrupt);
    atexit(quit);

    // load fonts
    TTF_Font *font_time = TTF_OpenFont(FONT_TYPE_SPACE, FONT_SIZE_TIME);
    TTF_Font *font_date = TTF_OpenFont(FONT_TYPE_UBUNTU, FONT_SIZE_DATE);
    TTF_Font *font_temp = TTF_OpenFont(FONT_TYPE_UBUNTU, FONT_SIZE_TEMP);
    TTF_Font *font_city = TTF_OpenFont(FONT_TYPE_UBUNTU, FONT_SIZE_CITY);

    if (font_time==NULL||font_date==NULL||font_temp==NULL||font_city==NULL){
        fprintf(stderr, "Couldn't load TTF font: %s\n",SDL_GetError());
        cleanup(4);
        }

    // load background
    SDL_Surface *temp = SDL_LoadBMP(IMAGE_BACKGROUND);

    if ( temp == NULL) {
        fprintf(stderr, "Couldn't render background surface: %s\n",SDL_GetError());
        cleanup(5);
        }

    // display background
    SDL_Surface *s_background = SDL_DisplayFormat(temp);
    SDL_BlitSurface(s_background, NULL, screen, &r_background);
    SDL_UpdateRect(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    update_screen_full();
    SDL_FreeSurface(temp);
    SDL_FreeSurface(s_background);

    do { // main loop starts here...

        FILE *fp1 = popen(TIME_UTIL, "r");
        if (fp1 == NULL) {
            fprintf(stderr, "Couldn't get info from file: %s\n", TIME_UTIL);
            cleanup(5);
            }

	if (fgets(buffer, 79, fp1) != NULL) {
            sprintf(string, "%s", buffer);
            }
        pclose(fp1);
        strcpy(time, strtok(string , "|"));
        strcpy(date, strtok(NULL, "|"));
        if (strcmp(last_time, time) != 0) {
            sprintf(last_time, "%s", time);
            sprintf(last_date, "%s", date);

            // rendering time and date
            SDL_Surface *s_clock_time = TTF_RenderText_Shaded(font_time, last_time, black, white);
            SDL_Surface *s_clock_date = TTF_RenderText_Shaded(font_date, last_date, black, white);
            if ( s_clock_time == NULL || s_clock_date == NULL ) {
                fprintf(stderr, "Couldn't render clock date surface: %s\n",SDL_GetError());
                cleanup(6);
                }

            SDL_BlitSurface(s_clock_time, NULL, screen, &r_clock_time);
            SDL_BlitSurface(s_clock_date, NULL, screen, &r_clock_date);

            // update the region of the screen used by the clock.
            SDL_UpdateRect(screen,
                           FRAME_LEFT,
                           FRAME_TOP,
                           SCREEN_WIDTH - FRAME_RIGHT - FRAME_LEFT,
                           CLOCK_BOTTOM - FRAME_TOP);


            // full e-ink update each 15 minutes:
            if (counter > 15) {
                counter = 0;
                update_screen_full();
            } else {
                counter++;
                update_clock_partial();
            }
            // keep track of uptime - in minutes:
            uptime++;
            if (uptime >= 60 && uptime % 60 == 0) {
                // sync time and fetch weather from the internet
                system("/opt/kobo-clock/bin/sync.sh");
                }

            SDL_FreeSurface(s_clock_date);
            SDL_FreeSurface(s_clock_time);

            FILE *fp2 = popen(WEATHER_UTIL, "r");
            if (fp2 == NULL) {
                fprintf(stderr, "Couldn't get info from file: %s\n", WEATHER_UTIL);
                cleanup(5);
                }

            if (fgets(buffer, 79, fp2) != NULL) {
                sprintf(string, "%s", buffer);
                }
            pclose(fp2);
            strcpy(city, strtok(string, "|"));
            strcpy(temperature , strtok(NULL, "|"));
            strcpy(weather_icon , strtok(NULL, "|"));

             if (strcmp(last_info, string) != 0) {
                sprintf(last_info, "%s", string);

                // display panel with weather info
                if (strcmp(city, "?") != 0) {
                    // rendering image used to display celsius degrees
                    temp = SDL_LoadBMP(IMAGE_CELSIUS);
                    if (temp == NULL) {
                        fprintf(stderr, "Couldn't render temperature icon surface: %s\n",SDL_GetError());
                        cleanup(6);
                        }

                    SDL_Surface *s_icon = SDL_DisplayFormat(temp);
                    SDL_FreeSurface(temp);

                    // get the relative path to the weather icon to be displayed
                    sprintf(icon, "bitmaps/%s", weather_icon);

                    // rendering weather icon
                    temp = SDL_LoadBMP(icon);
                    if (temp == NULL) {
                        fprintf(stderr, "Couldn't render weather icon surface: %s\n",SDL_GetError());
                        cleanup(6);
                        }

                    SDL_Surface *s_weather = SDL_DisplayFormat(temp);
                    SDL_FreeSurface(temp);

                    // rendering temperature and city text
                    SDL_Surface *s_temp = TTF_RenderText_Shaded(font_temp, temperature, black, white);
                    SDL_Surface *s_city = TTF_RenderText_Shaded(font_city, city, black, white);
                    if ( s_temp == NULL || s_city == NULL ) {
                        fprintf(stderr, "Couldn't render text surface: %s\n",SDL_GetError());
                        cleanup(6);
                        }

                    // push weather info on the screen
                    SDL_BlitSurface(s_city, NULL, screen, &r_city);
                    SDL_BlitSurface(s_temp, NULL, screen, &r_temp);
                    SDL_BlitSurface(s_icon, NULL, screen, &r_icon);
                    SDL_BlitSurface(s_weather, NULL, screen, &r_weather);

                    // update the screen
                    SDL_UpdateRect(screen,
                                   FRAME_LEFT, CLOCK_BOTTOM,
                                   SCREEN_WIDTH - FRAME_LEFT - FRAME_RIGHT,
                                   SCREEN_HEIGHT - FRAME_BOTTOM - CLOCK_BOTTOM);
                    update_panel_partial();

                    // free weather surfaces
                    SDL_FreeSurface(s_weather);
                    SDL_FreeSurface(s_icon);
                    SDL_FreeSurface(s_temp);
                    SDL_FreeSurface(s_city);
                    }
                }
               // Screen updated, sleep almost a minute before start again
               if (uptime > 1) sleep(45);
            }
        // Don't waste CPU cycles
        sleep(0.2);
    }while(1);
}
