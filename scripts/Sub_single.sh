#!/bin/bash

#run locally
#analysis -c $MPAF/cfg/tmpFiles/susy3l_${sregion}_${pairstate}.cfg
 
#submit jobs to batch
#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/susy3l_wzcr1.out -e $MPAF/workdir/logs/susy3l/susy3l_wzcr1.err $MPAF/scripts/submit.sh $MPAF/cfg/wzcr1.cfg
#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/susy3l_wzcr2.out -e $MPAF/workdir/logs/susy3l/susy3l_wzcr2.err $MPAF/scripts/submit.sh $MPAF/cfg/wzcr2.cfg
#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/susy3l_wzcr3.out -e $MPAF/workdir/logs/susy3l/susy3l_wzcr3.err $MPAF/scripts/submit.sh $MPAF/cfg/wzcr3.cfg
qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/susy3l_wzcr4.out -e $MPAF/workdir/logs/susy3l/susy3l_wzcr4.err $MPAF/scripts/submit.sh $MPAF/cfg/wzcr4.cfg
