#!/bin/bash

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi


#all
#80X
DATASETS=("GGHZZ4L" "VHToNonbb" "WWZ" "WZZ" "ZZZ" "TTTT" "tZq_ll" "ZZTo4L" "WGToLNuG" "ZGTo2LG" "TTGJets" "TGJets" "TTWToLNu" "TTZToLLNuNu" "TTHnobb_pow" "TTLLJets_m1to10" "WZTo3LNu" "DYJetsToLL_M50" "DYJetsToLL_M10to50" "TTJets" "WJetsToLNu" "T_tWch" "TToLeptons_sch" "TBar_tWch" "DoubleEG_Run2016B_PromptReco_v2_runs_273150_274443" "DoubleMuon_Run2016B_PromptReco_v2_runs_273150_274443" "MuonEG_Run2016B_PromptReco_v2_runs_273150_274443" )

#76X
#DATASETS=("GGHZZ4L" "WWZ" "WZZ" "ZZZ" "TTTT" "tZq_ll" "ZZTo4L" "WGToLNuG" "ZGTo2LG" "TTGJets" "TGJets" "TTWToLNu" "TTZToLLNuNu_LO" "TTHnobb" "TTLLJets_m1to10" "WZTo3LNu" "DYJetsToLL_M50" "DYJetsToLL_M10to50" "TTJets" "TToLeptons_sch" "TToLeptons_tch_powheg" "TBarToLeptons_tch_powheg" "TBar_tWch" "T_tWch" "WJetsToLNu" "WWTo2L2Nu" "ZZTo2L2Nu" "T1tttt_mGo1200_mChi800" "T1tttt_mGo1500_mChi100")


#all
#DIRS=( "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June10" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June10" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June10" )

#skims
#80X
DIRS=("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" )

#76X
#DIRS=("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" )


N=0
echo $MPAF
for ds in ${DATASETS[@]}; do

	cp $MPAF/cfg/3l_scan.cfg $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg

	dir=${DIRS[$N]}

	sed -i 's|FILE|'$ds'|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	sed -i 's|PATH|'$dir'|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	sed -i 's|SIMFLAG|0|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg

    #analysis -c $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/SUSY3L/3l_scanBkg_${ds}.out -e $MPAF/workdir/logs/SUSY3L/3l_scanBkg_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	qsub -q long.q -N MPAFjob $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	#bsub -q 8nh source submitLxbatch.sh $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg

	N=`echo $N + 1 | bc`
    #break
done



