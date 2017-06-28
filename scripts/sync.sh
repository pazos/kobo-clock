#!/bin/sh

# start the wifi
/opt/kobo-clock/bin/start_wifi.sh

sleep 5

# sync the time via the Network Time Protocol
ntpd -q -p 0.pool.ntp.org

# fetch new weather data
( cd /opt/kobo-clock/lua && /opt/kobo-clock/bin/lua weather.lua )

sleep 2

# stop the wifi
/opt/kobo-clock/bin/stop_wifi.sh
