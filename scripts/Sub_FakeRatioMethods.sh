#!/bin/bash


#METS=( "UCSX" )
METS=( "ECO20" "ECO30" "ECOlite" )
#METS=( "ECO20" "ECO30" "ECOlite" "UCSX" )

#rm cfg/tmpFiles/*

for met in ${METS[@]}; do

  m=$met

  cp cfg/template_FakeRatio2015Bel.cfg cfg/tmpFiles/FakeRatio2015Bel_${m}.cfg
  sed -i 's|EMETHOD|'$m'|' cfg/tmpFiles/FakeRatio2015Bel_${m}.cfg
  qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bel_${m}.out -e $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bel_${m}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FakeRatio2015Bel_${m}.cfg

  cp cfg/template_FakeRatio2015Bmu.cfg cfg/tmpFiles/FakeRatio2015Bmu_${m}.cfg
  sed -i 's|EMETHOD|'$m'|' cfg/tmpFiles/FakeRatio2015Bmu_${m}.cfg
  qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bmu_${m}.out -e $MPAF/workdir/logs/FakeRatio/FakeRatio2015Bmu_${m}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/FakeRatio2015Bmu_${m}.cfg

done
