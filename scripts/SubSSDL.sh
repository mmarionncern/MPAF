#!/bin/bash

SAMPLES=( 
#DYJetsToLL_M10to50
#DYJetsToLL_M50
DoubleEG_Run2016B_03Feb2017_ver2_v2_runs_273150_275376
DoubleEG_Run2016C_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016D_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016E_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016F_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016G_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016H_03Feb2017_ver2_v1_runs_281085_284035
DoubleEG_Run2016H_03Feb2017_ver3_v1_runs_284036_284044
DoubleMuon_Run2016B_03Feb2017_ver2_v2_runs_273150_275376
DoubleMuon_Run2016C_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016D_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016E_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016F_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016G_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016H_03Feb2017_ver2_v1_runs_281085_284035
DoubleMuon_Run2016H_03Feb2017_ver3_v1_runs_284036_284044
MuonEG_Run2016B_03Feb2017_ver2_v2_runs_273150_275376
MuonEG_Run2016C_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016D_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016E_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016F_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016G_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016H_03Feb2017_ver2_v1_runs_281085_284035
MuonEG_Run2016H_03Feb2017_ver3_v1_runs_284036_284044
#GGHZZ4L
#JetHT_Run2016B_23Sep2016_v3_runs_273150_275376
#JetHT_Run2016C_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016D_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016E_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016F_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016G_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016H-PromptReco-v2_runs_281207_284035
#JetHT_Run2016H-PromptReco-v3_runs_284036_284044
#MET_Run2016B_23Sep2016_v3_runs_273150_275376
#MET_Run2016C_23Sep2016_v1_runs_271036_284044
#MET_Run2016D_23Sep2016_v1_runs_271036_284044
#MET_Run2016E_23Sep2016_v1_runs_271036_284044
#MET_Run2016F_23Sep2016_v1_runs_271036_284044
#MET_Run2016G_23Sep2016_v1_runs_271036_284044
#MET_Run2016H-PromptReco-v2_runs_281207_284035
#MET_Run2016H-PromptReco-v3_runs_284036_284044
#SingleElectron_Run2016B_23Sep2016_v3_runs_273150_275376
#SingleElectron_Run2016C_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016D_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016E_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016F_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016G_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016H-PromptReco-v2_runs_281207_284035
#SingleElectron_Run2016H-PromptReco-v3_runs_284036_284044
#SingleMuon_Run2016B_23Sep2016_v3_runs_273150_275376
#SingleMuon_Run2016C_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016D_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016E_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016F_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016G_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016H-PromptReco-v2_runs_281207_284035
#SingleMuon_Run2016H-PromptReco-v3_runs_284036_284044
#TBar_tch_powheg
#TGJets
#TTGJets
#TTHnobb_pow
#TTJets_DiLepton_part1
#TTJets_DiLepton_part2
#TTJets_SingleLeptonFromT_part1
#TTJets_SingleLeptonFromT_part2
#TTJets_SingleLeptonFromT_part3
#TTJets_SingleLeptonFromTbar
#TTLLJets_m1to10
#TTTT
#TTWToLNu_ext1
#TTWToLNu_ext2_part1
#TTWToLNu_ext2_part2
#TTWToQQ
#TTZToLLNuNu
#TTZToQQ
#T_tch_powheg
#VHToNonbb
#WGToLNuG
#WJetsToLNu
#WJetsToLNu_LO
#WW2L2NuDouble
#WWG
#WWTo2L2Nu
#WWW
#WWZ
#WZG
#WZTo2L2Q
#WZTo3LNu
#WZZ
#WpWpJJ
#ZGTo2LG
#ZZTo2L2Nu
#ZZTo4L_part1
#ZZTo4L_part2
#ZZZ
#tZW_ll
#tZq_ll
)


LINKS=( 
#DYJetsToLL_M10to50
#DYJetsToLL_M50
DoubleEG_Run2016B_03Feb2017_ver2_v2_runs_273150_275376
DoubleEG_Run2016C_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016D_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016E_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016F_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016G_03Feb2017_v1_runs_271036_284044
DoubleEG_Run2016H_03Feb2017_ver2_v1_runs_281085_284035
DoubleEG_Run2016H_03Feb2017_ver3_v1_runs_284036_284044
DoubleMuon_Run2016B_03Feb2017_ver2_v2_runs_273150_275376
DoubleMuon_Run2016C_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016D_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016E_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016F_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016G_03Feb2017_v1_runs_271036_284044
DoubleMuon_Run2016H_03Feb2017_ver2_v1_runs_281085_284035
DoubleMuon_Run2016H_03Feb2017_ver3_v1_runs_284036_284044
MuonEG_Run2016B_03Feb2017_ver2_v2_runs_273150_275376
MuonEG_Run2016C_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016D_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016E_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016F_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016G_03Feb2017_v1_runs_271036_284044
MuonEG_Run2016H_03Feb2017_ver2_v1_runs_281085_284035
MuonEG_Run2016H_03Feb2017_ver3_v1_runs_284036_284044
#GGHZZ4L
#JetHT_Run2016B_23Sep2016_v3_runs_273150_275376
#JetHT_Run2016C_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016D_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016E_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016F_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016G_23Sep2016_v1_runs_271036_284044
#JetHT_Run2016H-PromptReco-v2_runs_281207_284035
#JetHT_Run2016H-PromptReco-v3_runs_284036_284044
#MET_Run2016B_23Sep2016_v3_runs_273150_275376
#MET_Run2016C_23Sep2016_v1_runs_271036_284044
#MET_Run2016D_23Sep2016_v1_runs_271036_284044
#MET_Run2016E_23Sep2016_v1_runs_271036_284044
#MET_Run2016F_23Sep2016_v1_runs_271036_284044
#MET_Run2016G_23Sep2016_v1_runs_271036_284044
#MET_Run2016H-PromptReco-v2_runs_281207_284035
#MET_Run2016H-PromptReco-v3_runs_284036_284044
#SingleElectron_Run2016B_23Sep2016_v3_runs_273150_275376
#SingleElectron_Run2016C_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016D_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016E_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016F_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016G_23Sep2016_v1_runs_271036_284044
#SingleElectron_Run2016H-PromptReco-v2_runs_281207_284035
#SingleElectron_Run2016H-PromptReco-v3_runs_284036_284044
#SingleMuon_Run2016B_23Sep2016_v3_runs_273150_275376
#SingleMuon_Run2016C_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016D_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016E_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016F_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016G_23Sep2016_v1_runs_271036_284044
#SingleMuon_Run2016H-PromptReco-v2_runs_281207_284035
#SingleMuon_Run2016H-PromptReco-v3_runs_284036_284044
#TBar_tch_powheg
#TGJets
#TTGJets
#TTHnobb_pow
#TTJets_DiLepton_part1
#TTJets_DiLepton_part2
#link:TTJets_SingleLeptonFromT_part1
#link:TTJets_SingleLeptonFromT_part2
#link:TTJets_SingleLeptonFromT_part3
#TTJets_SingleLeptonFromTbar
#TTLLJets_m1to10
#TTTT
#link:TTWToLNu_ext*
#link:TTWToLNu_ext*
#link:TTWToLNu_ext*
#TTWToQQ
#TTZToLLNuNu
#TTZToQQ
#T_tch_powheg
#VHToNonbb
#WGToLNuG
#WJetsToLNu
#WJetsToLNu_LO
#WW2L2NuDouble
#WWG
#WWTo2L2Nu
#WWW
#WWZ
#WZG
#WZTo2L2Q
#WZTo3LNu
#WZZ
#WpWpJJ
#ZGTo2LG
#ZZTo2L2Nu
#link:ZZTo4L_part1
#link:ZZTo4L_part2
#ZZZ
#tZW_ll
#tZq_ll
)




cfgFile=ssdlMoriond_dump.cfg



rm cfg/tmpFiles/ssdl_bkgDump_*.cfg
rm workdir/logs/logssdl*
for ds in ${SAMPLES[@]}; do
	cp cfg/$cfgFile cfg/tmpFiles/ssdl_bkgDump_${ds}.cfg

	if [ "${link:0:5}" != "link:" ];then
	    #continue
	    link=""
	fi

	#if [ "$ds" != "DYJetsToLL_M50_LO" ];then
	#    continue
	#fi

	sed -i 's|SAMPLE|'$ds'|' cfg/tmpFiles/ssdl_bkgDump_${ds}.cfg
	sed -i 's|LINK|'$link'|' cfg/tmpFiles/ssdl_bkgDump_${ds}.cfg

	if [ "${HOST:0:6}" == "lxplus" ]; then
	    bsub -q 8nh -o $MPAF/workdir/logs/logssdlDump_${ds}.out -e $MPAF/workdir/logs/logssdlDump_${ds}.err $MPAF/scripts/submitLxbatch.sh $MPAF/cfg/tmpFiles/ssdl_bkgDump_${ds}.cfg
	else
	    qsub -q long.q -N SSDL$ds -o $MPAF/workdir/logs/logssdlDump_${ds}.out -e $MPAF/workdir/logs/logssdlDump_${ds}.err $MPAF/scripts/submitLxbatch.sh $MPAF $MPAF/cfg/tmpFiles/ssdl_bkgDump_${ds}.cfg
	fi
#break
done