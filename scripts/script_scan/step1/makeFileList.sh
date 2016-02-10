#!/bin/bash

for file in /pnfs/psi.ch/cms/trivcat/store/user/cheidegg/11/2016-02-01-00-01-00/*
    do
        fdir=$(dirname "$file")
        fname=$(basename "$file")
        fname=${fname%.root}
        echo "$fdir     $fname" >> /shome/jhoss/analysis/MPAF/scripts/script_scan/step1/fileNamesT6ttWW
    done
