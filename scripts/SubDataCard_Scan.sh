#!/bin/bash

sub() {
    cd display
    root -b -l cards/tmpFilesShape/$1
    cd $MPAF
}

#===============================================================================
rm display/cards/tmpFilesShape/*

NJ=0
NSR=0

N=0
for i in `ls $MPAF/workdir/stats/SSDL2015/ssdlScan-*-*-.dat`; do
#while [[ $N -lt ${#SIGS[*]} ]]; do

tmp=${i#"/shome/mmarionn/MPAF/workdir/stats/SSDL2015/ssdlScan"}
mass=${tmp%"-.dat"}
bench=`echo $mass | tr "-" "_"`

    
    cp display/cards/ssdlScan_template.C display/cards/tmpFilesShape/ssdlScan_${bench}.C

    sed -i 's|MASS|'$mass'|' display/cards/tmpFilesShape/ssdlScan_${bench}.C
    sed -i 's|BENCH|'$bench'|' display/cards/tmpFilesShape/ssdlScan_${bench}.C
    sed -i 's|BENCH|'$bench'|' display/cards/tmpFilesShape/ssdlScan_${bench}.C

    N=`echo $N +1 | bc`
    #break
    if [[ $NJ -lt 4 ]]; then
	sub ssdlScan_${bench}.C &
	NJ=`echo $NJ +1 | bc`
    else
	sub  ssdlScan_${bench}.C
	NJ=0
    fi
    
done
