#!/bin/bash

#rm $MPAF/workdir/logs/FRinSitu/FRinSituSkim.out
#rm $MPAF/workdir/logs/FRinSitu/FRinSituSkim.err
#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FRinSitu/FRinSituSkim.out -e $MPAF/workdir/logs/FRinSitu/FRinSituSkim.err $MPAF/scripts/submit.sh $MPAF/cfg/FRinSituSkim.cfg

rm $MPAF/workdir/logs/FRinSitu/FRinSitu2015D.out
rm $MPAF/workdir/logs/FRinSitu/FRinSitu2015D.err
qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FRinSitu/FRinSitu2015D.out -e $MPAF/workdir/logs/FRinSitu/FRinSitu2015D.err $MPAF/scripts/submit.sh $MPAF/cfg/FRinSitu2015D.cfg

