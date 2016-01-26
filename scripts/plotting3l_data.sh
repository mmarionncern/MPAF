#!/bin/bash

#VAR=("njets" "nbjets" "met" "ht" "pt1" "pt2" "pt3" "srs")
#VAR=("ftype")
VAR=("srs")


for var in ${VAR[@]}; do

    variable=$var

    cp cards/susy3l_data.C cards/tmpFiles/susy3l_data.C
    sed -i 's|VARIABLE|'$variable'|' cards/tmpFiles/susy3l_data.C

    root -l -b cards/tmpFiles/susy3l_data.C

done

