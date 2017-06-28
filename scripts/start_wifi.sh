#!/bin/sh
# -- load kernel modules for wifi, bring up network interfaces and
#    start wpa_supplicant and udhcpc to start a wireless connection.

insmod /lib/modules/sdio_wifi_pwr.ko
insmod /lib/modules/dhd.ko

sleep 1

ifconfig eth0 up
wlarm_le -i eth0 up

sleep 1
wpa_supplicant -D wext -s -i eth0 -c /etc/wifi.conf -B

sleep 1
udhcpc -i eth0 -s /etc/init.d/udhcpc.script -S > /dev/null 2>&1&
