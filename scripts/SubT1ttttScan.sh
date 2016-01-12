#!/bin/bash

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi

root -b -l getMassBenchmarks.C <<EOF
.q
EOF

while read line; do

    mass=$line

    cp $MPAF/cfg/ssdlScan_template.cfg $MPAF/cfg/tmpFiles/ssdlScan_$mass.cfg

    sed -i 's|MASSBENCH|'$mass'|' $MPAF/cfg/tmpFiles/ssdlScan_$mass.cfg

    #bsub -q 8nh source submitLxbatch.sh cfg/tmpFiles/ssdlScan_$mass.cfg


done < massT1ttt.txt
