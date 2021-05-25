#!/bin/bash
#a script to reset usb hub
sudo echo 0 > /sys/bus/usb/devices/1-0:1.0/authorized
sleep 10
sudo echo 1 > /sys/bus/usb/devices/1-0:1.0/authorized
