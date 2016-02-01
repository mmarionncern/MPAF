#!/bin/bash

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi



#DATASETS=("GGHZZ4L" "VHToNonbb" "WWZ" "WZZ" "ZZZ" "TTTT" "tZq_ll" "ZZTo4L" "WGToLNuG" "ZGTo2LG" "TTGJets" "TGJets" "TTWToLNu" "TTZToLLNuNu" "TTHnobb" "TTLLJets_m1to10" "WZTo3LNu" "DoubleEG_Run2015C_Oct05_runs_254231_254914" "DoubleEG_Run2015D_Oct05_runs_256630_258158" "DoubleEG_Run2015D_PromptV4_runs_258159_260627" "DoubleMuon_Run2015C_Oct05_runs_254231_254914" "DoubleMuon_Run2015D_Oct05_runs_256630_258158" "DoubleMuon_Run2015D_PromptV4_runs_258159_260627" "MuonEG_Run2015C_Oct05_runs_254231_254914" "MuonEG_Run2015D_Oct05_runs_256630_258158" "MuonEG_Run2015D_PromptV4_runs_258159_260627" )

DATASETS=("DoubleEG_Run2015C_Oct05_runs_254231_254914" "DoubleEG_Run2015D_Oct05_runs_256630_258158" "DoubleEG_Run2015D_PromptV4_runs_258159_260627" "DoubleMuon_Run2015C_Oct05_runs_254231_254914" "DoubleMuon_Run2015D_Oct05_runs_256630_258158" "DoubleMuon_Run2015D_PromptV4_runs_258159_260627" "MuonEG_Run2015C_Oct05_runs_254231_254914" "MuonEG_Run2015D_Oct05_runs_256630_258158" "MuonEG_Run2015D_PromptV4_runs_258159_260627" )

DIRS=( "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00/" )

N=0

for ds in ${DATASETS[@]}; do

	cp $MPAF/cfg/3l_scan.cfg $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg

	dir=${DIRS[$N]}

	sed -i 's|FILE|'$ds'|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	sed -i 's|PATH|'$dir'|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	sed -i 's|SIMFLAG|0|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg

    #analysis -c $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/SUSY3L/3l_scanBkg_${ds}.out -e $MPAF/workdir/logs/SUSY3L/3l_scanBkg_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	#bsub -q 8nh source submitLxbatch.sh $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg

	N=`echo $N + 1 | bc`
    #break
done



