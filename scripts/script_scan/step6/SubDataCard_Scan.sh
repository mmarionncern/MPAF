#!/bin/bash

sub() {
    echo $1
    cd display
    root -b -l cards/tmpFilesShape/$1
    cd $MPAF
}

#===============================================================================
rm display/cards/tmpFilesShape/*

NJ=0
NSR=0

N=0
for i in `ls $MPAF/workdir/stats/SUSY3L/3l_scanSig_T1tttt-*-*-.dat`; do
#while [[ $N -lt ${#SIGS[*]} ]]; do

    tmp=${i#"/shome/jhoss/analysis/MPAF/workdir/stats/SUSY3L/3l_scanSig_T1tttt-"}
    mass=${tmp%"-.dat"}
    bench=`echo $mass | tr "-" "_"`
	echo $bench
    
    cp display/cards/susy3lScan_template.C display/cards/tmpFilesShape/3l_scanSig_${bench}.C

    sed -i 's|MASS|'$mass'|' display/cards/tmpFilesShape/3l_scanSig_${bench}.C
    sed -i 's|BENCH|'$bench'|' display/cards/tmpFilesShape/3l_scanSig_${bench}.C
    sed -i 's|BENCH|'$bench'|' display/cards/tmpFilesShape/3l_scanSig_${bench}.C

    N=`echo $N +1 | bc`
    #break
    if [[ $NJ -lt 4 ]]; then
	sub 3l_scanSig_${bench}.C &
	NJ=`echo $NJ +1 | bc`
    else
	sub  3l_scanSig_${bench}.C
	NJ=0
    fi
    
done
