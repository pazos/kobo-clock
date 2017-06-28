#!/bin/sh
# kobo-clock launcher

# turn off the blinking led:
echo "Turning of led"
echo 0 > /sys/class/leds/pmic_ledsg/brightness

# launch input monitoring on background:
echo "Listening for events on /dev/input/event0"
( cd /opt/kobo-clock/lua && /opt/kobo-clock/bin/lua input.lua )&

# launch SDL app:
echo "Starting kobo-clock"
cd /opt/kobo-clock
echo 0 > /sys/class/graphics/fb0/rotate
SDL_NOMOUSE=1 ./clock.bin &

# sync time and fetch weather for first time:
/opt/kobo-clock/bin/sync.sh
