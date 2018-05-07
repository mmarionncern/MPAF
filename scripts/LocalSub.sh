#!/bin/bash

for i in `ls cfg/tmpFiles/3l_v2_scanBkg_*`; do

    

    nJobs=`ps ux | grep analysis | wc -l`
    while [[ $nJobs -gt 4 ]];do
	sleep 1m
	nJobs=`ps ux | grep analysis | wc -l`
    done

    analysis -c $i &
    sleep 3s
   # break
done