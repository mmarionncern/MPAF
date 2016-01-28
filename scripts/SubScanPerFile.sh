#!/bin/bash

TEMPCARD=$1
ANTYPE=$2
MASSFILE=$3
SIGNAME=$4
FNAME=$5

#TEMPCARD=susy3lScan_template
#ANTYPE=SUSY3L
#MASSFILE=massT6ttWW.txt
#SIGNAME=T6ttWW

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi

#root -b -l getMassBenchmarks.C <<EOF
#.q
#EOF

N=0
while read fileLine; do

    if [[ "${fileLine:0:1}" == "#" ]]; then
	continue
    fi

    path=`echo $fileLine | awk '{print $1}'`
    file=`echo $fileLine | awk '{print $2}'`

    echo $path $file

    if [[ "$SIGNAME" != "$file" ]]; then
	
	cp $MPAF/cfg/${TEMPCARD}.cfg $MPAF/cfg/tmpFiles/${ANTYPE}${file}.cfg

	sed -i 's|MASSBENCH||' $MPAF/cfg/tmpFiles/${ANTYPE}${file}.cfg
	sed -i 's|FILE|'$file'|' $MPAF/cfg/tmpFiles/${ANTYPE}${file}.cfg
	sed -i 's|PATH|'$path'|' $MPAF/cfg/tmpFiles/${ANTYPE}${file}.cfg
	sed -i 's|FSIM|0|' $MPAF/cfg/tmpFiles/${ANTYPE}${file}.cfg
	sed -i 's|SIGNAME|NOSIG|' $MPAF/cfg/tmpFiles/${ANTYPE}${file}.cfg

	qsub -q all.q -N MPAFjob${ANTYPE}${file} -o $MPAF/workdir/logs/${ANTYPE}/${ANTYPE}${file}.out -e $MPAF/workdir/logs/${ANTYPE}/${ANTYPE}${file}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/${ANTYPE}${file}.cfg $HOME
	
    else
	
	while read line; do
	    mass=$line
	    python splitLineScan.py $path $mass $SIGNAME $file $ANTYPE $TEMPCARD

	    if [[ ! -e $MPAF/cfg/tmpFiles/${ANTYPE}${SIGNAME}${mass}.cfg ]]; then
		continue
	    fi

	    qsub -q all.q -N MPAFjob${ANTYPE}${SIGNAME}${mass} -o $MPAF/workdir/logs/${ANTYPE}/${ANTYPE}${SIGNAME}${mass}.out -e $MPAF/workdir/logs/${ANTYPE}/${ANTYPE}${SIGNAME}${mass}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/${ANTYPE}${SIGNAME}${mass}.cfg $HOME


	done < ${MASSFILE}
    
    fi

	#while read line; do

	#	mass=$line
		
	#	if [[ -e $MPAF/cfg/tmpFiles/${ANTYPE}_${mass}.cfg ]]; then
	#	    continue
	#	fi

		##python splitLineScan.py $path $mass $SIGNAME

		#dec=`python splitLineScan.py $path $mass`
		#if [[ $dec == 0 ]]; then
		#    continue
		#fi
		#break


		#cp $MPAF/cfg/${TEMPCARD}.cfg $MPAF/cfg/tmpFiles/${ANTYPE}${mass}.cfg

		#sed -i 's|MASSBENCH|'$mass'|' $MPAF/cfg/tmpFiles/${ANTYPE}${mass}.cfg
		#sed -i 's|FILE|'$file'|' $MPAF/cfg/tmpFiles/${ANTYPE}${mass}.cfg
		#sed -i 's|PATH|'$path'|' $MPAF/cfg/tmpFiles/${ANTYPE}${mass}.cfg
	
	#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/${ANTYPE}/${ANTYPE}${mass}.out -e $MPAF/workdir/logs/${ANTYPE}/${ANTYPE}${mass}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/${ANTYPE}${mass}.cfg


   # done < ${MASSFILE}

#N=`echo $N + 1 | bc`

#break

done < $FNAME
