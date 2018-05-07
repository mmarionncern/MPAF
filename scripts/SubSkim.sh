#!/bin/bash

SAMPLES=( 
#DYJetsToLL_M10to50_LO_treeProducerSusyMultilepton_tree
#DYJetsToLL_M50_LO_part1_treeProducerSusyMultilepton_tree
#DYJetsToLL_M50_LO_part2_treeProducerSusyMultilepton_tree
#DYJetsToLL_M50_LO_part3_treeProducerSusyMultilepton_tree
#DYJetsToLL_M50_LO_part4_treeProducerSusyMultilepton_tree
#DYJetsToLL_M50_LO_part5_treeProducerSusyMultilepton_tree
#GGHZZ4L_treeProducerSusyMultilepton_tree
#TBarToLeptons_tch_powheg_treeProducerSusyMultilepton_tree
#TBar_tWch_treeProducerSusyMultilepton_tree
#TGJets_treeProducerSusyMultilepton_tree
#TTGJets_part1_treeProducerSusyMultilepton_tree
#TTGJets_part2_treeProducerSusyMultilepton_tree
#TTHnobb_pow_treeProducerSusyMultilepton_tree
#TTJets_DiLepton_part1_treeProducerSusyMultilepton_tree
#TTJets_DiLepton_part2_treeProducerSusyMultilepton_tree
#TTJets_DiLepton_part3_treeProducerSusyMultilepton_tree
#TTJets_SingleLeptonFromT_part1_treeProducerSusyMultilepton_tree
#TTJets_SingleLeptonFromT_part2_treeProducerSusyMultilepton_tree
#TTJets_SingleLeptonFromT_part3_treeProducerSusyMultilepton_tree
#TTJets_SingleLeptonFromTbar_part1_treeProducerSusyMultilepton_tree
#TTJets_SingleLeptonFromTbar_part2_treeProducerSusyMultilepton_tree
#TTJets_SingleLeptonFromTbar_part3_treeProducerSusyMultilepton_tree
#TTJets_SingleLeptonFromTbar_part4_treeProducerSusyMultilepton_tree
#TTLLJets_m1to10_treeProducerSusyMultilepton_tree
#TTTT_treeProducerSusyMultilepton_tree
#TTWToLNu_treeProducerSusyMultilepton_tree
#TTZToLLNuNu_treeProducerSusyMultilepton_tree
#TToLeptons_sch_treeProducerSusyMultilepton_tree
#TToLeptons_tch_powheg_treeProducerSusyMultilepton_tree
#T_tWch_treeProducerSusyMultilepton_tree
#VHToNonbb_treeProducerSusyMultilepton_tree
#WGToLNuG_treeProducerSusyMultilepton_tree
#WJetsToLNu_LO_treeProducerSusyMultilepton_tree
#WWDouble_treeProducerSusyMultilepton_tree
#WWW_treeProducerSusyMultilepton_tree
#WWZ_treeProducerSusyMultilepton_tree
#WZTo3LNu_treeProducerSusyMultilepton_tree
#WZZ_treeProducerSusyMultilepton_tree
#WpWpJJ_treeProducerSusyMultilepton_tree
#ZGTo2LG_treeProducerSusyMultilepton_tree
#ZZTo4L_treeProducerSusyMultilepton_tree
#ZZZ_treeProducerSusyMultilepton_tree
#tZq_ll_treeProducerSusyMultilepton_tree


##for training
TTHnobb_pow
TTZToLLNuNu_ext2
tZq_ll
tZW_ll_ext
#WZTo3LNu
WZTo3LNu_amcatnlo

#WZTo3LNu_ext_part1_treeProducerSusyMultilepton_tree
#WZTo3LNu_ext_part2_treeProducerSusyMultilepton_tree
#WZTo3LNu_ext_part3_treeProducerSusyMultilepton_tree
#WZTo3LNu_ext_part4_treeProducerSusyMultilepton_tree


#DYJetsToLL_M10to50
#DYJetsToLL_M50
#GGHZZ4L
#TBar_tch_powheg
#TGJets
#TTGJets
#TTHnobb_pow
#TTJets_DiLepton
#TTJets_DiLepton_ext
#TTJets_SingleLeptonFromT
#TTJets_SingleLeptonFromT_ext
#TTJets_SingleLeptonFromTbar
#TTJets_SingleLeptonFromTbar_ext
#TTLLJets_m1to10
#TTTT
#TTZToLLNuNu
#TTZToLLNuNu_ext2
#TTZToLLNuNu_ext2_part1
#TTZToLLNuNu_ext2_part2
#T_tch_powheg
#VHToNonbb
#WGToLNuG
#WJetsToLNu
#WW2L2NuDouble
#WWG
#WWTo2L2Nu
#WWW
#WZG
#WZTo3LNu
#WZTo3LNu_ext
#WZTo3LNu_ext_part1
#WZTo3LNu_ext_part2
#WZTo3LNu_ext_part3
#WZTo3LNu_ext_part4
#WZZ
#WpWpJJ
#ZGTo2LG
#ZGTo2LG_part1
#ZGTo2LG_part2
#ZZTo4L
#ZZZ
#tZW_ll




)

LINKS=(
""
"link:DYJetsToLL_M50_LO_p*"
"link:DYJetsToLL_M50_LO_p*"
"link:DYJetsToLL_M50_LO_p*"
"link:DYJetsToLL_M50_LO_p*"
"link:DYJetsToLL_M50_LO_p*"
"link:DYJetsToLL_M50_LO_p*"
""
""
""
""
""
""
""
"link:TTJets_DiLepton_p*"
"link:TTJets_DiLepton_p*"
"link:TTJets_DiLepton_p*"
"link:TTJets_SingleLeptonFromT_p*"
"link:TTJets_SingleLeptonFromT_p*"
"link:TTJets_SingleLeptonFromT_p*"
"link:TTJets_SingleLeptonFromTbar_p*"
"link:TTJets_SingleLeptonFromTbar_p*"
"link:TTJets_SingleLeptonFromTbar_p*"
"link:TTJets_SingleLeptonFromTbar_p*"
""
""
""
""
""
""
""
""
""
""
""
""
""
""
""
""
""
""
""
""
)

ERAS=(
8011_Aug8
8011_Aug8
8011_Aug8
8011_Aug8
8011_Aug8
8011_Aug8
8011_Aug8
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
8011_Aug23
)



#SAMPLES=( TTW_LO )

cfgFile=ttvAnalysis.cfg #skimLimited.cfg #skimSSDL2016.cfg #skimSSDL2016.cfg #skimsusy3l.cfg
era=8011_Aug23

rm cfg/tmpFiles/skim_*
rm workdir/logs/logskim*
N=0
for ds in ${SAMPLES[@]}; do

    link=${LINKS[$N]}
    era=${ERAS[$N]}

    cp cfg/$cfgFile cfg/tmpFiles/skim_${ds}.cfg
    sed -i 's|SAMPLE|'$ds'|' cfg/tmpFiles/skim_${ds}.cfg
    #sed -i 's|LINKS|'$link'|' cfg/tmpFiles/skim_${ds}.cfg
    #sed -i 's|ERA|'$era'|' cfg/tmpFiles/skim_${ds}.cfg
    
    #qsub -q long.q -N Skim${ds} -o $MPAF/workdir/logs/logskim_${ds}.out -e $MPAF/workdir/logs/logskim_${ds}.err $MPAF/scripts/submit.sh $MPAF $MPAF/cfg/tmpFiles/skim_${ds}.cfg

	if [ "${HOST:0:6}" == "lxplus" ]; then
	    bsub -q 1nd -o $MPAF/workdir/logs/skim_${ds}.out -e $MPAF/workdir/logs/skim_${ds}.err $MPAF/scripts/submitLxbatch.sh $MPAF/cfg/tmpFiles/skim_${ds}.cfg
	else
	    qsub -q long.q -N SSDL$ds -o $MPAF/workdir/logs/skim_${ds}.out -e $MPAF/workdir/logs/skim_${ds}.err $MPAF/scripts/submitLxbatch.sh $MPAF $MPAF/cfg/tmpFiles/skim_${ds}.cfg
	fi
    N=`echo $N + 1 | bc`

done
