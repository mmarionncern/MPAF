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
for i in `ls $MPAF/workdir/stats/SUSY3L/3l_scanSig_T1tttt-*-*-.dat`; do
#while [[ $N -lt ${#SIGS[*]} ]]; do

    tmp=${i#"/shome/jhoss/analysis/MPAF/workdir/stats/SUSY3L/3l_scanSig_T1tttt-"}
    mass=${tmp%"-.dat"}
    bench=`echo $mass | tr "-" "_"`
	echo $bench
    
    cp $MPAF/display/cards/susy3lScan_template.C $MPAF/display/cards/tmpFilesShape/susy3l_scanSig_${bench}.C

    sed -i 's|MASS|'$mass'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig_${bench}.C
    sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig_${bench}.C
    sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig_${bench}.C

    N=`echo $N +1 | bc`
    #break
    if [[ $NJ -lt 4 ]]; then
	sub susy3l_scanSig_${bench}.C &
	NJ=`echo $NJ +1 | bc`
    else
	sub  susy3l_scanSig_${bench}.C
	NJ=0
    fi
    #break
done
