#!/bin/bash

#VAR=("njets" "nbjets" "met" "ht" "pt1" "pt2" "pt3") # "srs" "flavor" "mt") # "el_multi" "mu_multi" "lep_multi")
#VAR=("ftype")
#VAR=("srs")
VAR=("lep1dxy" "lep1dz" "lep1sip") # "srs" "flavor" "mt") # "el_multi" "mu_multi" "lep_multi")


for var in ${VAR[@]}; do

    variable=$var

    cp cards/susy3l_data.C cards/tmpFiles/susy3l_data.C
    sed -i 's|VARIABLE|'$variable'|' cards/tmpFiles/susy3l_data.C

    root -l -b cards/tmpFiles/susy3l_data.C

done

