#!/bin/bash
echo 0 > /sys/bus/usb/devices/1-0:1.0/authorized
sleep 10
echo 1 > /sys/bus/usb/devices/1-0:1.0/authorized
echo "aaa"
