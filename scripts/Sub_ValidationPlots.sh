#!/bin/bash

REGS=( "ttbar" "ZMuMu" "ZEE" "Zl" "Wl" )

VARS=( "lep1_jetPtRatio"
       "lep1_jetPtRel"   
       "lep1_miniRelIso" 
       "lep1_Pt"         
       "lep1_Eta"        
       "lep1_SIP3D"      
       "lep2_jetPtRatio" 
       "lep2_jetPtRel"   
       "lep2_miniRelIso" 
       "lep2_Pt"         
       "lep2_Eta"        
       "lep2_SIP3D"      
       "MET"         
       "htJet40j"        
       "mZ1"             
       "MTmin"           
       "NBJetsLoose25" 
       "NBJetsMedium25"
       "NBJetsTight40" 
       "NJets40"       )  

TODAY="150910" #$(date +"%y%m%d")

if [ ! -d "$MPAF/workdir/plots/SSDL2015_${TODAY}" ]; then
    mkdir $MPAF/workdir/plots/SSDL2015_${TODAY}
fi

cd $MPAF/display

DIR=$MPAF/workdir/plots/SSDL2015_${TODAY}

for reg in ${REGS[@]}; do
    if [ ! -d "$DIR/${reg}" ]; then
	mkdir $DIR/${reg}
    fi
    for var in ${VARS[@]}; do
	plot=${reg}_${var}
	root -l -b -q cards/template_Validation.C\(\"${plot}\"\) 
	
	mv $DIR/png/${plot}.png   $DIR/${reg}/${var}.png
	mv $DIR/pdf/${plot}.pdf   $DIR/${reg}/${var}.pdf
	mv $DIR/eps/${plot}.eps   $DIR/${reg}/${var}.eps
	mv $DIR/root/${plot}.root $DIR/${reg}/${var}.root
    done
done

rmdir $DIR/png
rmdir $DIR/pdf
rmdir $DIR/eps
rmdir $DIR/root