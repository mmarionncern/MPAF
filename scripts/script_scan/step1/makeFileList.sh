#!/bin/bash

#for file in /pnfs/psi.ch/cms/trivcat/store/user/cheidegg/11/2016-02-01-00-01-00/*
#for file in /pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-02-02-11-22-00/*.root
for file in /pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-03-04-18-49-00/*.root
    do
        fdir=$(dirname "$file")
        fname=$(basename "$file")
        fname=${fname%.root}
        echo "$fdir     $fname" >> /shome/jhoss/analysis/MPAF/scripts/script_scan/step1/fileNamesT5qqqqVV
    done
