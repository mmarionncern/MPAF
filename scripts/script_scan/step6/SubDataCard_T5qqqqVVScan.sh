#!/bin/bash

sub() {
    echo $1
    cd $MPAF/display
    root -b -l cards/tmpFilesShape/$1
    cd $MPAF
}

#===============================================================================
rm $MPAF/display/cards/tmpFilesShape/*

NJ=0
NSR=0

N=0
for i in `ls $MPAF/workdir/stats/SUSY3L/merged_v2_4fb_T5qqqqVV_noDM_mG_*_mN_*.dat`; do
#while [[ $N -lt ${#SIGS[*]} ]]; do

    tmp=${i#"$MPAF/workdir/stats/SUSY3L/merged_v2_4fb_T5qqqqVV_noDM_mG_"}
    mass=${tmp%".dat"}
       
    #echo 'bench'
    #echo $bench
    #echo 'mass'
    #echo $mass
    
    bench=`echo $mass | tr '_' ' '`

    m1=`echo $bench | awk '{print $1}'`
    m2=`echo $bench | awk '{print $3}'`

    mass="mG_"$m1"_mN_"$m2
    bench="_m"$m1"_m"$m2

    #echo $m1
    #echo $m2
    #echo $bench
    
    #cp $MPAF/display/cards/susy3lScanCombine.C $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
    cp $MPAF/display/cards/susy3lScanCombine.C $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C

    sed -i 's|MASS|'$mass'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
    sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
    #sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C

    N=`echo $N +1 | bc`
    #break
    if [[ $NJ -lt 4 ]]; then
	sub susy3l_scanSig${bench}.C &
	NJ=`echo $NJ +1 | bc`
    else
	sub  susy3l_scanSig${bench}.C
	NJ=0
    fi
    #break
done
