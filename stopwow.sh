#!/bin/bash
##########
# Wow random show
#
#
for i in {0..7}
do
  led=""
  terminate="000000000"
  led="$i$terminate"

  echo $led
  echo $led > /dev/ttyACM0

  sleep 0.1
done
