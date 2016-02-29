#!/bin/bash

#VAR=("njets" "nbjets" "met" "ht" "pt1" "pt2" "pt3" "srs")
VAR=("ttbar_lep1_dxy" "ttbar_lep1_dz" "ttbar_lep2_dxy" "ttbar_lep2_dz" "ZMuMu_lep1_dxy" "ZMuMu_lep1_dz" "ZMuMu_lep2_dxy" "ZMuMu_lep2_dz" "ZElEl_lep1_dxy" "ZElEl_lep1_dz" "ZElEl_lep2_dxy" "ZElEl_lep2_dz" "Wl_lep1_dxy" "Wl_lep1_dz" "Wl_lep2_dxy" "Wl_lep2_dz" "Zl_lep1_dxy" "Zl_lep1_dz" "Zl_lep2_dxy" "Zl_lep2_dz" )
#VAR=("ftype")
#VAR=("srs")


for var in ${VAR[@]}; do

    variable=$var

    cp cards/susy3l.C cards/tmpFiles/susy3l.C
    #sed -i 's|VARIABLE|'$variable'|' cards/tmpFiles/susy3l.C
    sed -i 's|OBS|'$variable'|' cards/tmpFiles/susy3l.C

    root -l -b cards/tmpFiles/susy3l.C

done

