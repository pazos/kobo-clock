#!/bin/sh
current_path=`pwd`

dev_headers=$current_path/include
dev_libraries=$current_path/lib

target_dir=$current_path/rootfs/kobo-clock

cd src

# build main application
arm-linux-gnueabihf-gcc -static main.c init.c rect.c eink.c light.c \
    -o $target_dir/clock.bin \
    -L $dev_libraries -I $dev_headers/SDL -I $dev_headers/freetype2 \
    -lSDL -lSDL_ttf -lfreetype -lpthread -lm -Wall
arm-linux-gnueabihf-gcc snooze.c light.c -o $target_dir/bin/snooze
arm-linux-gnueabihf-strip $target_dir/clock.bin
arm-linux-gnueabihf-strip $target_dir/bin/snooze

# copy miscelaneous scripts on target:
cd $current_path/scripts
cp input.lua power.lua weather.lua $target_dir/lua
cp start_clock.sh stop_clock.sh start_wifi.sh stop_wifi.sh \
   date.sh weather.sh sync.sh $target_dir/bin


# make scripts executable
cd $target_dir/bin
chmod +x *.sh
cd $current_path

# Copy resources on target
( cd resources && cp -pR bitmaps/ data/ fonts/ $target_dir )

# Remove misc stuff in the rootfs
rm $target_dir/share -rf
( cd $target_dir/bin && rm -rf sdl-config freetype-config )

# Create a tar file of the files in our rootfs:
cd rootfs/
tar -cf ../kobo-clock.tar .
cd $current_path
