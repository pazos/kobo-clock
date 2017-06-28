#!/bin/sh
output=`cat /opt/kobo-clock/data/weather.forecast 2>/dev/null || printf "?|-|50n.bmp"`
printf "${output}"
