#!/bin/bash


mydir=/shome/jhoss/logs_bkp/160229_T6ttWW_bySR

for dir in $mydir/*; do
    #echo $dir
    folder=`echo $dir | tr '/' ' '`
    name=`echo $folder | awk '{print $5}'`
    #echo $name
    echo -n "" > ObsLimits_T6ttWW_$name.txt
    
    for i in `ls $dir/*.log`; do

        #echo $i
        spl=`echo $i | tr '_' ' '`
        #echo $spl
        sig="T6ttWW"
        m1=`echo $spl | awk '{print $6}'`
        #m1=${m1#T6ttWW}
        m2=`echo $spl | awk '{print $7}'`
        m2=${m2%.txt.log}

        #echo $m1
        #echo $m2
        #echo $m2

        obs=`grep "Observed"    $i | awk '{print $5}'`
        #exp=`grep "Expected 50" $i | awk '{print $5}'`
        #d1s=`grep "Expected 16" $i | awk '{print $5}'`
        #u1s=`grep "Expected 84" $i | awk '{print $5}'`
        #u2s=`grep "Expected 97" $i | awk '{print $5}'`
        #d2s=`grep "Expected  2" $i | awk '{print $5}'`

        #$sig"\t"
        #if [[ -n "$exp" ]]; then
        echo -e $m1"\t"$m2"\t"$obs >> ObsLimits_T6ttWW_$name.txt
        #fi
    
    
    done
    #break

done


