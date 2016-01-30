#!/bin/bash
for j in {0..255}
do
  for i in {0..7}
  do
    r_pos=$(( ((($i*8)-$i)/8+$j)%255 ))
    sect=$(( ($r_pos/85)%3 ))
    pos=$(( ($r_pos/85)*3 ))

    # echo $r_pos
    echo $sect
    # echo $pos
    calculate=$((255 - $pos))

    case $sec in
      $0 ) echo "$calculate, $pos, 0"
        ;;
      $1 ) echo "0, $calculate, $pos"
        ;;
      $2 ) echo "$pos, 0, $calculate"
        ;;
      # * ) echo "wrong"
        # ;;
    esac


  done
done
