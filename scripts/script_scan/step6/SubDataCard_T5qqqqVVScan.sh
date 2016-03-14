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
NUMBER=(1) # 1 2 3 4 5 6 7 8 9 10 11 12 13 14 )

for nr in ${NUMBER[@]}; do

    for i in `ls $MPAF/workdir/stats/SUSY3L/3l_scanSig_T5qqqqVV_*_*.dat`; do
    #while [[ $N -lt ${#SIGS[*]} ]]; do

        tmp=${i#"/shome/jhoss/analysis/MPAF/workdir/stats/SUSY3L/3l_scanSig_T5qqqqVV"}
        mass=${tmp%".dat"}
        bench=`echo $mass | tr "-" "_"`
	    echo $mass
        echo $bench
   
        cp $MPAF/display/cards/susy3lScan_template.C $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C

        sed -i 's|NUMBER|'$nr'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
        sed -i 's|MASS|'$mass'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
        sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C
        sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C

        N=`echo $N +1 | bc`
        #break
        if [[ $NJ -lt 4 ]]; then
	    sub susy3l_scanSig${bench}.C &
	    NJ=`echo $NJ +1 | bc`
        else
	    sub  susy3l_scanSig${bench}.C
	    NJ=0
        fi
        break
    done
    mv $MPAF/workdir/datacards/susy3l* $MPAF/workdir/datacards/SR$nr/
done
