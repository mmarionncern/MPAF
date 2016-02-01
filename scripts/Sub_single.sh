#!/bin/bash

#run locally
#analysis -c $MPAF/cfg/tmpFiles/susy3l_${sregion}_${pairstate}.cfg
 
#submit jobs to batch
qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/3l_test.out -e $MPAF/workdir/logs/susy3l/3l_test.err $MPAF/scripts/submit.sh $MPAF/cfg/3l_test.cfg
