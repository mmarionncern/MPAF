#!/bin/bash

# to be executed in MPAF/display directory

SRS=( "WZ" "TZq" "TTH" "TZW" )
PTS=( "TTZToLLNuNu_ext2" "TTZ_LO" "WZTo3LNu_amcatnlo" "tZq_ll" "tZW_ll_ext" )

rm cards/tmpFiles/*

for training in ${SRS[@]}; do
    for proc in ${PTS[@]}; do
	
	cp cards/ttVPlotsTemplate.C cards/tmpFiles/ttVPlots${training}${proc}.C
	sed -i 's|TRAINING|'$training'|' cards/tmpFiles/ttVPlots${training}${proc}.C
	sed -i 's|PROC|'$proc'|' cards/tmpFiles/ttVPlots${training}${proc}.C
	
	root -l -b cards/tmpFiles/ttVPlots${training}${proc}.C
	
    done
done
