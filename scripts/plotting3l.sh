#!/bin/bash

#VAR=("njets" "nbjets" "met" "ht" "pt1" "pt2" "pt3" "srs")
#VAR=("ftype")
VAR=("srs")


for var in ${VAR[@]}; do

    variable=$var

    cp cards/susy3l.C cards/tmpFiles/susy3l.C
    sed -i 's|VARIABLE|'$variable'|' cards/tmpFiles/susy3l.C

    root -l -b cards/tmpFiles/susy3l.C

done

