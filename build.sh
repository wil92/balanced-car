#!/usr/bin/env bash

if [ -f .env ]
then
  export $(cat .env | xargs)
fi

cd build

#cmake ../
#make

# show serial devices
ls -l /dev/ttyUSB*
#ls -l /dev/ttyS*

read -p "Select the serial device [/dev/ttyUSB0]: " SERIAL_SEVICE
if [ -z "$SERIAL_SEVICE" ]; then SERIAL_SEVICE=/dev/ttyUSB0; fi

echo $SERIAL_SEVICE

avrdude --help

