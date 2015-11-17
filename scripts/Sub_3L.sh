#!/bin/bash

#rm cfg/tmpFiles/*


cp cfg/3L_data_25ns.cfg cfg/tmpFiles/susy3l_data_25ns.cfg

#run locally
#analysis -c $MPAF/cfg/tmpFiles/susy3l_skim.cfg

#submit jobs to batch
qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/susy3l/susy3l_data_25ns.out -e $MPAF/workdir/logs/susy3l/susy3l_data_25ns.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/susy3l_data_25ns.cfg
