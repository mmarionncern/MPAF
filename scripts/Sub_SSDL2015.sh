#!/bin/bash

FILTERS=( "none" "PV" "trkMSC" "trkTMSC" "trkLETMC" "CSC" "HBHE" "HBHEiso" "ECALtp" "ECALsc" "all" )

for filter in ${FILTERS[@]}; do

  f=$filter
  cp cfg/template_SSDL2015.cfg cfg/tmpFiles/SSDL2015_${f}.cfg
  sed -i 's|USEFILTER|'$f'|' cfg/tmpFiles/SSDL2015_${f}.cfg
  
  qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/SSDL2015/SSDL2015_${f}.out -e $MPAF/workdir/logs/SSDL2015/SSDL2015_${f}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/SSDL2015_${f}.cfg

done
