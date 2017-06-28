#!/bin/sh
# -- kill wpa_supplicant and udhcpc, stop network
#    interfaces and remove kernel modules.

killall udhcpc wpa_supplicant
sleep 1

wlarm_le -i eth0 down
ifconfig eth0 down

sleep 2

rmmod -f dhd
rmmod -f sdio_wifi_pwr
