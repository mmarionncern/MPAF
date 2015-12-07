#!/bin/bash

sub() {
    cd display
    root -b -l cards/tmpFilesShape/$1
    cd $MPAF
}

SIGS=( 
    "_sig_T1t_1200_800"
    "_sig_T1t_1500_100"
    "_sig_T5q"
    "_sig_T5Deg"
    "_sig_T5t"
    "_sig_T6_600_425"
    "_sig_T6_650_150"
)


SIGTAGS=(
    "T14t12"
    "T14t15"
    "T54q12"
    "T54qDeg"
    "T54t"
    "T6ttWW60"
    "T6ttWW65"
)
#===============================================================================
rm display/cards/tmpFilesShape/*

NJ=0
NSR=0

N=0
while [[ $N -lt ${#SIGS[*]} ]]; do

    sig=${SIGS[$N]}
    tag=${SIGTAGS[$N]}
    
    cp display/cards/ssdl2015card_shape.C display/cards/tmpFilesShape/dataCardProd_shape_${tag}.C

    sed -i 's|SIGNAME|'$sig'|' display/cards/tmpFilesShape/dataCardProd_shape_${tag}.C
    sed -i 's|SIGTAG|'$tag'|' display/cards/tmpFilesShape/dataCardProd_shape_${tag}.C
    sed -i 's|SIGTAG|'$tag'|' display/cards/tmpFilesShape/dataCardProd_shape_${tag}.C 

    N=`echo $N +1 | bc`
    
    if [[ $NJ -lt 4 ]]; then
	sub dataCardProd_shape_${tag}.C &
	NJ=`echo $NJ +1 | bc`
    else
	sub dataCardProd_shape_${tag}.C
	NJ=0
    fi
    
done
