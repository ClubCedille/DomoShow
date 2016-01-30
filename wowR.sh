#!/bin/bash
##########
# Wow random show
#
#
padded=""
checkNumber() {
  if [ $1 -lt 10 ]
  then
     padded="00$1"
  elif [ $1 -lt 100 ]
  then
     padded="0$1"
  else
     padded="$1"
  fi
}

# while [[ true ]]; do
for j in {0..100}; do
  for i in {0..7}
  do
    led="$i"

    # Generate R Number
    checkNumber $[ RANDOM % 255 ]
    # echo "Padded : $padded"
    led="$led$padded"
    # Generate G Number
    checkNumber $[ RANDOM % 255 ]
    # echo "Padded : $padded"
    led="$led$padded"

    # Generate B Number
    checkNumber $[ RANDOM % 255 ]
    # echo "Padded : $padded"
    led="$led$padded"

    echo $led
    echo $led > /dev/ttyACM0

    sleep 0.05
  done
done
