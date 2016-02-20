#!/bin/bash/

for file in /pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-12-04-21-54-00/*
    do
        fdir=$(dirname "$file")
        fname=$(basename "$file")
        echo "$fdir"
        echo "$fname"
        
        IFS='-' read -ra MASSES <<< "$fname"  
        M1="${MASSES[1]}"
        M2="${MASSES[2]}"
        echo "$M1"
        echo "$M2"
        root -b -q -l "PrintXfactor.C(\"$fdir\",\"$fname\",\"$M1\",\"$M2\")"
        
    done


