#!/bin/sh
# -- stop clock application, lua scripts and cron daemon
kill -9 `pidof clock.bin` 2>/dev/null
killall lua 2>/dev/null
