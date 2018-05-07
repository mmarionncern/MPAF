#!/bin/bash

sub() {
    echo $1
    cd $MPAF/display
    root -b -l cards/tmpFiles/$1
    cd $MPAF
}

#===============================================================================
rm $MPAF/display/cards/tmpFilesShape/*

source /mnt/t3nfs01/data01/swshare/ROOT/root_v5.34.18_slc6_amd64/bin/thisroot.sh

MPAFPATH=$1

cd $MPAFPATH
source setup.sh

NJ=0
NSR=0

N=0
SIG="T1tttt"

for i in `ls $MPAF/workdir/stats/SSDL2015/ssdl_scanSig_$SIG_*.dat`; do
   
        tmp=${i#"$MPAF/workdir/stats/SSDL2015/ssdl_scanSig_"}
        sig=${tmp%".dat"}
       
        bench=`echo $mass | tr '_' ' '`

        cp $MPAF/display/cards/ssdl2016_scanShape.C $MPAF/display/cards/tmpFiles/ssdl2016_scanSig_shape_${sig}.C

        sed -i 's|SIGNAME|'$sig'|' $MPAF/display/cards/tmpFiles/ssdl2016_scanSig_shape_${sig}.C
        sed -i 's|SIGTAG|'$sig'|' $MPAF/display/cards/tmpFiles/ssdl2016_scanSig_shape_${sig}.C
        #sed -i 's|BENCH|'$bench'|' $MPAF/display/cards/tmpFilesShape/susy3l_scanSig${bench}.C

        #N=`echo $N +1 | bc`
	#nJobs=`ps ux | grep ssdl2016_scanSig | wc -l`
	#while [[ $nJobs -gt 5 ]];do
	#   sleep 10s
	#   nJobs=`ps ux | grep ssdl2016_scanSig | wc -l`
	#done

        #if [[ $NJ -lt 4 ]]; then
	#    sub ssdl2016_scanSig_${sig}.C &
	#    NJ=`echo $NJ +1 | bc`
        #else
#	    sub  ssdl2016_scanSig_${sig}.C
	#    NJ=0
        #fi
        #break
#done

    #sleep 10
    #mkdir -p $MPAF/workdir/datacards/SR$nr/
    #mv $MPAF/workdir/datacards/ra7_* $MPAF/workdir/datacards/SR$nr/

	#echo "qsub -q short.q -N -o $MPAF/workdir/logs/card_${sig}.out -e $MPAF/workdir/logs/card_${sig}.err $MPAF/scripts/script_scan/step6/subSingleCard.sh $MPAF ssdl2016_scanSig_${sig}.C"
	qsub -q short.q -N card$sig -o $MPAF/workdir/logs/card_shape_${sig}.out -e $MPAF/workdir/logs/card_shape_${sig}.err $MPAF/scripts/script_scan/step6/subSingleCard.sh $MPAF ssdl2016_scanSig_shape_${sig}.C


    #break
done
