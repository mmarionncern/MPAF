#!/bin/bash

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi


#all
DATASETS=("GGHZZ4L" "WWZ" "WZZ" "ZZZ" "TTTT" "tZq_ll" "ZZTo4L" "WGToLNuG" "ZGTo2LG" "TTGJets" "TGJets" "TTWToLNu" "TTZToLLNuNu_LO" "TTHnobb" "TTLLJets_m1to10" "WZTo3LNu" "DYJetsToLL_M50" "DYJetsToLL_M10to50" "TTJets" "TToLeptons_sch" "TToLeptons_tch_powheg" "TBarToLeptons_tch_powheg" "TBar_tWch" "T_tWch" "WJetsToLNu" "WWTo2L2Nu" "ZZTo2L2Nu" "T1tttt_mGo1200_mChi800" "T1tttt_mGo1500_mChi100")

#all
#DIRS=("/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod"  "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod" "/pnfs/psi.ch/cms/trivcat/store/user/jhoss/samples/2016-05-30_76X_May26_Prod")

#skims
DIRS=("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" )

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



