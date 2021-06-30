#!/usr/bin/env bash

if [ -f .env ]
then
  export $(cat .env | xargs)
fi

echo $ARDUINO_SDK_PATH

ARDUINO_SDK_PATH="$ARDUINO_SDK_PATH" cmake .
