#!/bin/bash

dss=(
DYJetsToLL_M10to50_LO_0
#DYJetsToLL_M50_LO
DYJetsToLL_M50_chunk0
DYJetsToLL_M50_chunk1
DYJetsToLL_M50_chunk2
GGHZZ4L_0
GGHZZ4L_ext_0
#GluGluToContinToZZTo2e2nu
#GluGluToContinToZZTo2e2tau
#GluGluToContinToZZTo2mu2nu
#GluGluToContinToZZTo2mu2tau
#QCD_Mu15
#QCD_Pt1000toInf_Mu5
#QCD_Pt120to170_EMEnriched
#QCD_Pt120to170_Mu5
#QCD_Pt15to20_EMEnriched
#QCD_Pt15to20_Mu5
#QCD_Pt170to300_EMEnriched
#QCD_Pt20to30_EMEnriched
#QCD_Pt300to470_Mu5
#QCD_Pt300to470_Mu5_ext
#QCD_Pt300toInf_EMEnriched
#QCD_Pt30to50_EMEnriched
#QCD_Pt30to50_Mu5
#QCD_Pt470to600_Mu5
#QCD_Pt470to600_Mu5_ext
#QCD_Pt50to80_EMEnriched
#QCD_Pt50to80_Mu5
#QCD_Pt600to800_Mu5
#QCD_Pt600to800_Mu5_ext
#QCD_Pt80to120_EMEnriched
#QCD_Pt80to120_Mu5
#QCD_Pt_15to20_bcToE
#QCD_Pt_170to250_bcToE
#QCD_Pt_20to30_bcToE
#QCD_Pt_250toInf_bcToE
#QCD_Pt_30to80_bcToE
#QCD_Pt_80to170_bcToE
TBar_tWch_0
TBar_tWch_1
TBar_tWch_2
TBar_tWch_noFullHad_0
TBar_tWch_noFullHad_1
TBar_tWch_noFullHad_ext_0
TBar_tWch_noFullHad_ext_1
TBar_tch_powheg
TTGJets_0
TTGJets_1
TTHnobb
TTHnobb_pow
TTJets
#TTJets_SingleLeptonFromT_chunk0	link:TTJets_SingleLeptonFromT_chunk*
#TTJets_SingleLeptonFromT_chunk1	link:TTJets_SingleLeptonFromT_chunk*
#TTJets_SingleLeptonFromT_chunk2	link:TTJets_SingleLeptonFromT_chunk*
#TTJets_SingleLeptonFromT_chunk3	link:TTJets_SingleLeptonFromT_chunk*
#TTJets_SingleLeptonFromT_chunk4	link:TTJets_SingleLeptonFromT_chunk*
TTLLJets_m1to10
TTTT_ext
TTWToLNu
TTWW
TTWZ
TTW_LO
TTZH
TTZToLLNuNu
TTZZ
TTZ_LO_0
TTZ_LO_1
TTZ_LO_2
TTZ_LO_3
TToLeptons_sch_0
TToLeptons_sch_1
T_tWch_0
T_tWch_1
T_tWch_2
T_tWch_noFullHad
T_tch_powheg
VBF_HToZZTo4L_0
WJetsToLNu_LO
WWTo1L1Nu2Q_0
WWTo2L2Nu_0
WWW_4F
WZG
WZTo3LNu_amcatnlo
WZZ
ZZTo2L2Nu
ZZTo4L_0
ZZTo4L_1
ZZZ
tZq_ll

#DoubleEG_Run2017B_17Nov2017_v1_runs_297046_299329
#DoubleEG_Run2017C_17Nov2017_v1_runs_299368_302029
#DoubleEG_Run2017D_17Nov2017_v1_runs_302030_303434
#DoubleEG_Run2017E_17Nov2017_v1_runs_303824_304797
#DoubleEG_Run2017F_17Nov2017_v1_runs_305040_306462
#DoubleMuon_Run2017B_17Nov2017_v1_runs_297046_299329
#DoubleMuon_Run2017C_17Nov2017_v1_runs_299368_302029
#DoubleMuon_Run2017D_17Nov2017_v1_runs_302030_303434
#DoubleMuon_Run2017E_17Nov2017_v1_runs_303824_304797
#DoubleMuon_Run2017F_17Nov2017_v1_runs_305040_306462
#MuonEG_Run2017B_17Nov2017_v1_runs_297046_299329
#MuonEG_Run2017C_17Nov2017_v1_runs_299368_302029
#MuonEG_Run2017D_17Nov2017_v1_runs_302030_303434
#MuonEG_Run2017E_17Nov2017_v1_runs_303824_304797
#MuonEG_Run2017F_17Nov2017_v1_runs_305040_306462
)


#dss=(
#DoubleMuon_Run2017C_17Nov2017_v1_runs_299368_302029
#DoubleMuon_Run2017B_17Nov2017_v1_runs_297046_299329
#DoubleEG_Run2017F_17Nov2017_v1_runs_305040_306462
#DoubleEG_Run2017E_17Nov2017_v1_runs_303824_304797
#DoubleEG_Run2017D_17Nov2017_v1_runs_302030_303434
#DoubleEG_Run2017C_17Nov2017_v1_runs_299368_302029
#DoubleEG_Run2017B_17Nov2017_v1_runs_297046_299329
#DoubleMuon_Run2017F_17Nov2017_v1_runs_305040_306462
#DoubleMuon_Run2017E_17Nov2017_v1_runs_303824_304797
#DoubleMuon_Run2017D_17Nov2017_v1_runs_302030_303434
#MuonEG_Run2017C_17Nov2017_v1_runs_299368_302029
#MuonEG_Run2017B_17Nov2017_v1_runs_297046_299329
#MuonEG_Run2017F_17Nov2017_v1_runs_305040_306462
#MuonEG_Run2017E_17Nov2017_v1_runs_303824_304797
#MuonEG_Run2017D_17Nov2017_v1_runs_302030_303434
#
#)

for i in ${dss[@]}; do
    #echo $i
    k=$i
    if [ $i == "TTZToLLNuNu" ]; then
	k="$i -k 5511402"
    elif [ $i == "WZTo3LNu_amcatnlo" ]; then
	k="$i -k 5203933"
    elif [ $i == "tZq_ll" ]; then
	k="$i -k 3224506"
    fi
    
    if [ -e /afs/cern.ch/user/m/mmarionn/workspace/private/MPAF/workdir/root/TTVAnalysis/ttvAnalysisFall17_${i}.root ]; then
	echo "skipping $i"
	continue
    fi
    
    bsub -q 8nh -o $MPAF/workdir/logs/ttv_${i}.out -e $MPAF/workdir/logs/ttv_${i}.err $MPAF/scripts/submitLxbatch.sh $MPAF/cfg/ttvAnalysisFall17.cfg $k
done