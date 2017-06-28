#!/bin/sh
current_path=`pwd`

dev_headers=$current_path/include
dev_libraries=$current_path/lib
target_dir=$current_path/rootfs/kobo-clock

# 1st stage: download and build libraries

LUA="lua-5.2.4"
SDL="SDL-1.2.15"
FREETYPE="freetype-2.4.8"
SDL_ttf="SDL_ttf-2.0.11"

if [ ! -d dl/ ]; then
  mkdir -pv dl
fi

if [ ! -f dl/$FREETYPE.tar.gz ]; then
  ( cd dl && wget http://download.savannah.gnu.org/releases/freetype/$FREETYPE.tar.gz )
fi

if [ ! -f dl/$SDL.tar.gz ]; then
  ( cd dl && wget https://www.libsdl.org/release/$SDL.tar.gz )
fi

if [ ! -f dl/$SDL_ttf.tar.gz ]; then
  ( cd dl && wget https://www.libsdl.org/projects/SDL_ttf/release/$SDL_ttf.tar.gz )
fi

if [ ! -f dl/$LUA.tar.gz ]; then
  ( cd dl && wget https://www.lua.org/ftp/$LUA.tar.gz )
fi

if [ ! -f dl/lua-evdev-master.zip ]; then
    cd dl/
    wget https://github.com/Tangent128/lua-evdev/archive/master.zip
    mv master.zip lua-evdev-master.zip
    cd $current_path
fi

if [ ! -f dl/luasocket-master.zip ]; then
    cd dl/
    wget https://github.com/diegonehab/luasocket/archive/master.zip
    mv master.zip luasocket-master.zip
    cd $current_path
fi

if [ ! -f dl/json.lua-master.zip ]; then
    cd dl/
    wget https://github.com/rxi/json.lua/archive/master.zip
    mv master.zip json.lua-master.zip
    cd $current_path
fi

if [ ! -d build ]; then
  mkdir -pv build
fi
( cd build && tar -xvf ../dl/$LUA.tar.gz )
( cd build && tar -xvf ../dl/$SDL.tar.gz )
( cd build && tar -xvf ../dl/$SDL_ttf.tar.gz )
( cd build && tar -xvf ../dl/$FREETYPE.tar.gz )
( cd build && unzip ../dl/lua-evdev-master.zip )
( cd build && unzip ../dl/luasocket-master.zip )
( cd build && unzip ../dl/json.lua-master.zip )
( cd build/$LUA && patch -Np1 -i ../../patches/01-$LUA-cross_disable-readline.patch )
( cd build/lua-evdev-master && patch -Np1 -i ../../patches/02-lua-evdev_cross_compile.patch )
( cd build/luasocket-master && patch -Np1 -i ../../patches/03-luasocket-crosscompile-with-headers.patch )

# build and install freetype2
cd build/$FREETYPE
./configure --prefix=$target_dir --host=arm-linux-gnueabihf \
            --with-zlib=no --with-bzip2=no --without-png --with-gnu-ld \
            --includedir=$dev_headers --libdir=$dev_libraries
make
make install
cd $current_path

# build and install SDL
cd build/$SDL
./configure --prefix=$target_dir --host=arm-linux-gnueabihf \
            --disable-pulseaudio --disable-audio --disable-video-x11 \
            --disable-video-dummy --disable-oss --disable-alsa --disable-esd \
            --disable-joystick --disable-cdrom --includedir=$dev_headers \
            --libdir=$dev_libraries
make
make install
cd $current_path

# build and install SDL_ttf
cd build/$SDL_ttf
CPPFLAGS=-I"/home/pazos/Escritorio/software-kobo/rootfs/include/freetype2" \
LDFLAGS=-L"/home/pazos/Escritorio/software-kobo/rootfs/lib" \
./configure --prefix=$target_dir --host=arm-linux-gnueabihf \
    --with-sdl-prefix=$target_dir --with-freetype-prefix=$target_dir \
    --includedir=$dev_headers --libdir=$dev_libraries
make
make install
cd $current_path

# build lua and lua modules
( cd build/$LUA && make linux )
( cd build/lua-evdev-master && make )
( cd build/luasocket-master && make )

# copy lua and lua modules in the rootfs
mkdir -pv $target_dir/lua/socket $target_dir/lua/mime
( cd build/$LUA/src && cp lua $target_dir/bin )
( cd build/lua-evdev-master && cp -pR evdev evdev.lua $target_dir/lua )
cp build/json.lua-master/json.lua $target_dir/lua
cd build/luasocket-master/src
cp socket-3.0-rc1.so $target_dir/lua/socket/core.so
cp ftp.lua headers.lua http.lua smtp.lua tp.lua url.lua $target_dir/lua/socket
cp mime-1.0.3.so $target_dir/lua/mime/core.so
cp ltn12.lua mime.lua socket.lua $target_dir/lua
cd $current_path
