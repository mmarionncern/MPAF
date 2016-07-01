#!/bin/bash

sub() {
    cd $MPAF/display
    root -b -l cards/tmpFilesShape/$1
    cd $MPAF
}

#===============================================================================

TEMPCARD=$1
ANTYPE=$2
#MASSFILE=$3
SIGNAME=$3

rm $MPAF/display/cards/tmpFilesShape/*

NJ=0
NSR=0

N=0
for i in `ls $MPAF/workdir/stats/${ANTYPE}/mergedFile${SIGNAME}*`; do
#while [[ $N -lt ${#SIGS[*]} ]]; do

tmp=${i#"/shome/mmarionn/MPAF/workdir/stats/${ANTYPE}/mergedFile${SIGNAME}"}
mass=${tmp%"-.dat"}
bench=`echo $mass | tr "-" "_"`

    
    cp $MPAF/display/cards/${TEMPCARD}.C $MPAF/display/cards/tmpFilesShape/${ANTYPE}${SIGNAME}${bench}.C

    sed -i 's|MASS|'$mass'|' $MPAF/display/cards/tmpFilesShape/${ANTYPE}${SIGNAME}${bench}.C
    sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/${ANTYPE}${SIGNAME}${bench}.C
    sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/${ANTYPE}${SIGNAME}${bench}.C
    sed -i 's|SIGNAME|'$SIGNAME'|' $MPAF/display/cards/tmpFilesShape/${ANTYPE}${SIGNAME}${bench}.C


    N=`echo $N +1 | bc`
    #break
    if [[ $NJ -lt 4 ]]; then
	sub ${ANTYPE}${SIGNAME}_${bench}.C &
	NJ=`echo $NJ +1 | bc`
    else
	sub  ${ANTYPE}${SIGNAME}_${bench}.C
	NJ=0
    fi
    
done #< ${MASSFILE}
