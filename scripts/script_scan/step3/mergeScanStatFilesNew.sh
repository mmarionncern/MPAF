#!/bin/bash

AN=$1

#mainFile=${MPAF}/workdir/stats/${AN}/merged_12_Bkg.dat
mainFile=${MPAF}/workdir/stats/${AN}/TT_pow_ext4.dat

## first merge backgrounds
#python ${MPAF}/scripts/script_scan/step3/mergeBkgs.py ${mainFile} ${MPAF}/workdir/stats/${AN}/ssdl_bkg_
python ${MPAF}/scripts/script_scan/step3/mergeBkgs.py ${mainFile} ${MPAF}/workdir/stats/${AN}/skim_TT_pow_ext4

### merge signals and backgrounds
#for i in `ls $MPAF/workdir/stats/${AN}/ssdl_scanSig_*.dat`; do

#    red=${i#$MPAF/workdir/stats/${AN}/ssdl_scanSig_}
#    echo $red
#    python ${MPAF}/scripts/script_scan/step3/addSample.py $mainFile $i $MPAF/workdir/stats/${AN}/merged_12_$red
#
#done
#
#### merge root files
files="vector<string> tks;\n tks.push_back(\"$MPAF/workdir/root/${AN}/merged_12_Bkg.root\");\n"
for i in `ls $MPAF/workdir/root/${AN}/ssdl_scanSig_*.root`; do
    files=$files" tks.push_back(\"$i\");\n"
done
#
##past string to next step
echo -e $files > logFiles




