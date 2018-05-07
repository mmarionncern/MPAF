#include "analysis/src/Comissioning.hh"

#include <algorithm>

Comissioning::Comissioning(std::string cfg){
  
  configure(cfg);
  initialize();

}

Comissioning::~Comissioning(){
 
}

void
Comissioning::initialize(){

  _vc->registerVar("nVert");
  _vc->registerVar("nTrueInt");

  _vc->registerVar("nLepGood");

  _vc->registerVar("LepGood_pt"                   );
  _vc->registerVar("LepGood_eta"                  );
  _vc->registerVar("LepGood_etaSc"                );
  _vc->registerVar("LepGood_phi"                  );
  _vc->registerVar("LepGood_charge"               );
  _vc->registerVar("LepGood_tightCharge"          );
  _vc->registerVar("LepGood_mediumMuonId"         );
  _vc->registerVar("LepGood_mediumMuonID2016"     );
  _vc->registerVar("LepGood_mvaIdSpring15"        );
  _vc->registerVar("LepGood_mvaIdSpring16GP"        );
  _vc->registerVar("LepGood_pdgId"                );
  _vc->registerVar("LepGood_relIso03"             );
  _vc->registerVar("LepGood_relIso04"             );
  _vc->registerVar("LepGood_jetPtRatiov2"         );
  _vc->registerVar("LepGood_jetPtRelv2"           );
  _vc->registerVar("LepGood_jetBTagCSV"           );
  _vc->registerVar("LepGood_jetRawPt"             );
  _vc->registerVar("LepGood_jetCorrFactor_L1L2L3Res");
  _vc->registerVar("LepGood_miniRelIso"           );
  _vc->registerVar("LepGood_dxy"                  );
  _vc->registerVar("LepGood_dz"                   );
  _vc->registerVar("LepGood_sip3d"                );
  _vc->registerVar("LepGood_convVeto"             );
  _vc->registerVar("LepGood_lostHits"             );
  _vc->registerVar("LepGood_mvaTTH"               );
  _vc->registerVar("LepGood_mvaSUSY"              );
  _vc->registerVar("LepGood_mcMatchId"            );
  _vc->registerVar("LepGood_mcMatchPdgId"         );
  _vc->registerVar("LepGood_mcUCSXMatchId"        );
  _vc->registerVar("LepGood_mcMatchAny"           );
  _vc->registerVar("LepGood_sigmaIEtaIEta"        );
  _vc->registerVar("LepGood_dEtaScTrkIn"          );
  _vc->registerVar("LepGood_dPhiScTrkIn"          );
  _vc->registerVar("LepGood_hadronicOverEm"       );
  _vc->registerVar("LepGood_eInvMinusPInv"        );
  _vc->registerVar("LepGood_ecalPFClusterIso"     );
  _vc->registerVar("LepGood_hcalPFClusterIso"     );
  _vc->registerVar("LepGood_dr03TkSumPt"          );
  _vc->registerVar("LepGood_jetLepAwareJEC_pt"    );
  _vc->registerVar("LepGood_jetLepAwareJEC_eta"    );
  _vc->registerVar("LepGood_jetLepAwareJEC_phi"    );
  _vc->registerVar("LepGood_jetLepAwareJEC_energy"    );
  _vc->registerVar("LepGood_jetCorrFactor_L1L2L3Res"    );
  _vc->registerVar("LepGood_mcMatchId");

  _vc->registerVar("run");
  _vc->registerVar("lumi");
  _vc->registerVar("event");

  _vc->registerVar("HLT_DoubleMu");
  _vc->registerVar("HLT_SingleMu");
  _vc->registerVar("HLT_DoubleEl");
  _vc->registerVar("HLT_SingleEl");
  _vc->registerVar("HLT_MuEG");
  _vc->registerVar("HLT_DoubleMuHT");
  _vc->registerVar("HLT_DoubleElHT");
  _vc->registerVar("HLT_BIT_HLT_Mu17_v");

  _vc->registerVar("met_pt");
  _vc->registerVar("met_phi");
  _vc->registerVar("met_sumEt");

  _vc->registerVar("metNoHF_pt");
  _vc->registerVar("metNoHF_phi");
  _vc->registerVar("metNoHF_sumEt");

  _vc->registerVar("nJet");
  _vc->registerVar("Jet_pt");
  _vc->registerVar("Jet_eta");
  _vc->registerVar("Jet_phi");
  _vc->registerVar("Jet_id");
  _vc->registerVar("Jet_area");
  

  _vc->registerVar("rhoCN");
 

  _vc->registerVar("vtxWeight");
  _vc->registerVar("genWeight");

}

void
Comissioning::initHLTLines() {

  _puLines.push_back("HLT_DoubleMu"); 
  _puLines.push_back("HLT_BIT_HLT_IsoMu22_v"); 
  _puLines.push_back("HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); 
  _puLines.push_back("HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v"); 
  _puLines.push_back("HLT_BIT_HLT_Ele27_WPTight_Gsf_v"); 
  _puLines.push_back("HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v"); 

  _zeeLines.push_back("HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  _zeeLines.push_back("HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v");
  _zeeLines.push_back("HLT_BIT_HLT_Ele27_WPTight_Gsf_v"); 
  _zeeLines.push_back("HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v");

  _zmmLines.push_back("HLT_DoubleMu");
  _zmmLines.push_back("HLT_BIT_HLT_IsoMu22_v");

  _zlLines.push_back("HLT_DoubleMu");
  _zlLines.push_back("HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  _zlLines.push_back("HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
  _zlLines.push_back("HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");

  _weLines.push_back("HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v");
  _weLines.push_back("HLT_BIT_HLT_Ele27_WPTight_Gsf_v");
  _weLines.push_back("HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v");

  _wmLines.push_back("HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v");
  _wmLines.push_back("HLT_BIT_HLT_Ele27_WPTight_Gsf_v");
  _wmLines.push_back("HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v");

  _wlLines.push_back("HLT_BIT_HLT_IsoMu22_v");
  _wlLines.push_back("HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v");
  _wlLines.push_back("HLT_BIT_HLT_Ele27_WPTight_Gsf_v");
  _wlLines.push_back("HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v");

  _ttbarLines.push_back("HLT_DoubleMu");
  _ttbarLines.push_back("HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  _ttbarLines.push_back("HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
  _ttbarLines.push_back("HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");

  _ttbarSlLines.push_back("HLT_BIT_HLT_IsoMu22_v");
  _ttbarSlLines.push_back("HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v");
  _ttbarSlLines.push_back("HLT_BIT_HLT_Ele27_WPTight_Gsf_v");
  _ttbarSlLines.push_back("HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v");

  // _wzLines.push_back("

  //   _zzLines.push_back("
    

}



void
Comissioning::modifyWeight() {

  // if(_sampleName.find("runs")==(size_t)-1)
  // _weight *= _dbm->getDBValue("puw",_vc->get("nVert") );
  //   _isData=true;
  // if(_sampleName.find("Double")==(size_t)-1) {
  //   _weight *=_vc->get("genWeight")*_dbm->getDBValue("puw",_vc->get("nTrueInt")); //_vc->get("vtxWeight")*
  //   //_puW = _vc->get("genWeight")*_dbm->getDBValue("puw",_vc->get("nTrueInt")); //_vc->get("vtxWeight")*

    
  //   double nProc=getCurrentDS()->getSumProcWgts(); //ugly
  //   if(nProc==-1) nProc=getCurrentDS()->getNProcEvents();
  //   double w=_dbm->getDBValue("XSections",_sampleName)*_dbm->getDBValue("KFactors",_sampleName)/nProc * 65.43;//last number is lumi
  //   //cout<<w<<"  "<<_dbm->getDBValue("XSections",_sampleName)<<"  "<<nProc<<"  "<<_dbm->getDBValue("KFactors",_sampleName)<<endl;
  //   _puW *=w;

  //   //_weight *=_dbm->getDBValue("XSections",_sampleName)*_dbm->getDBValue("KFactors",_sampleName)/nProc * 848;

  //   _isData=false;
  // }
  //cout<<_vc->get("vtxWeight")<<endl;
}

void
Comissioning::modifySkimming() {
}


void
Comissioning::defineOutput() {

  vector<string> leps({"l1","l2"});
  if(_selection=="WEl" || _selection=="WMu") {
    leps.clear();
    leps.push_back("#ell")
      }
    
  vector<string> wTypes({"","+","-"});
  if(_selection!="WEl" && _selection!="WMu") {
    wTypes.clear();
    wTypes.push_back("");
  }

  string lepType="l";
  if(_selection.find("El")!=string::npos) { // && _selection!="WMu") {
    lepType="e";
    lepPairType="ee";
  }
  if(_selection.find("Mu")!=string::npos) { // && _selection!="WMu") {
    lepType="#mu";
    lepPairType="#mu#mu";
  }
  
  
  //Leptons

  //overall kinematic variables
  _hm->addVariable("lepPt", 200, 0., 200.0,"p_{T}("+leps[il]+") [GeV]");
  _hm->addVariable("lepEta", 60, -3.0, 3.0,"#eta("+leps[il]+") ");
  _hm->addVariable("lepPhi", 60, 0, 3.1416926524*2,"#phi("+leps[il]+") ");

  //ID variables
  _hm->addVariable("lepMedMuId",3,-1.5,1.5,"medium #mu Id ");
  _hm->addVariable("lepSIP3D",50,0,10,"SIP_{3D}(#ell) ");
  _hm->addVariable("lepDxy",50,0,100,"dxy(#ell) [#mum]");
  _hm->addVariable("lepDy",,50,0,100,"dy(#ell) [#mum]");
  _hm->addVariable("lepMvaIdSpring15",50,-1,1,"e mvaIdSpring15 ");
  _hm->addVariable("lepMvaTTH",50,-1,1,"#ell mvaTTH ");
  _hm->addVariable("lepMvaSUSY",50,-1,1,"#ell mvaSUSY ");
  _hm->addVariable("lepSegCompa",20,0,1,"segment compatibility ");
  _hm->addVariable("lepPixLayer",11,-0.5,10.5,"pixel layers hits");
  _hm->addVariable("lepTrkLayer",11,-0.5,10.5,"tracker layers hits ");
  _hm->addVariable("lepLostHits",16,-5.5,10.5,"lost hits in inner track");
  _hm->addVariable("lepJetBTAgCSV",50,0,1,"CSV b-tag of nearest jet");

  //isolation variables
  _hm->addVariable("lepMinRelIso",50,0,4,"mRelIso ");
  _hm->addVariable("lepMinRelIsoCharged",50,0,4,"charged mRelIso ");
  _hm->addVariable("lepMinRelIsoNeutral",50,0,4,"neutral mRelIso ");
  _hm->addVariable("lepPtRelV2",60,0,30,"lepton-jet p_{T} Relv2 [GeV] ");
  _hm->addVariable("lepPtRatioV2",60,0,1.2,"p_{T}(#ell)/p_{T}(j) ");
  

  //global event variables
  _hm->addVariable("nVertices", 50, 0., 50,"N(vertices) ");
  _hm->addVariable("nLepton",11,-0.5,10.5,"N(leptons) ");
  _hm->addVariable("nMu",11,-0.5,10.5,"N(#mu) ");
  _hm->addVariable("nEl",11,-0.5,10.5,"N(e) ");
  _hm->addVariable("charge",10,-5.5,5.5,"#Sum(C_{#ell}) ");
 
  //Jets
  _hm->addVariable("nJets", 20, 0., 20.0,"N(jet, p_{T}>30 GeV) ");
  _hm->addVariable("Jet1Pt", 200, 0., 500.0,"#p_{T}(j1) [GeV]");
  _hm->addVariable("Jet2Pt", 200, 0., 500.0,"#p_{T}(j2) [GeV]");
  _hm->addVariable("Jet1Eta", 60, -3.0, 3.0,"#eta(j1) ");
  _hm->addVariable("Jet2Eta", 60, -3.0, 3.0,"#eta(j2) ");
  _hm->addVariable("Jet1Phi", 60, 0, 3.1416926524*2,"#phi(j1) [rad]");
  _hm->addVariable("Jet2Phi", 60, 0, 3.1416926524*2,"#phi(j2) [rad]");
  _hm->addVariable("HT", 200,0. 500.0,"H_{T}(jet, p_{T}>30 GeV) [GeV]");
 
  _hm->addVariable("nBJetsLoose", 20, 0., 20.0,"N(jet, p_{T}>25 GeV, CSVL) ");
  _hm->addVariable("nBJets", 20, 0., 20.0,"N(jet, p_{T}>25 GeV, CSVM) ");
  _hm->addVariable("BJet1Pt", 200, 0., 500.0,"#p_{T}(j_{1}, CSVM) [GeV]");
  _hm->addVariable("BJet2Pt", 200, 0., 500.0,"#p_{T}(j_{2}, CSVM) [GeV]");
  _hm->addVariable("HTB", 200,0. 500.0,"H_{T}(jet, p_{T}>25 GeV, CSVM) [GeV]");

  //MET
  _hm->addVariable("MetPt", 200, 0., 200.0,"#slash{E}_{T} [GeV]");
  _hm->addVariable("MetPhi", 60, 0, 3.1416926524*2,"#phi(#slash{E}_{T}) [rad]");
  _hm->addVariable("MetSumEt", 1000, 0, 2000,"#Sigma E_{T} [GeV]");
  _hm->addVariable("dPhiMetJ1",60,-3.1416926524,3.1416926524,"#Delta#phi(#slash{E}_{T},j_{1}) [rad]");
  _hm->addVariable("dPhiMetJ2",60,-3.1416926524,3.1416926524,"#Delta#phi(#slash{E}_{T},j_{2}) [rad]");
  for(int il=0;il<leps.size();il++) {
    _hm->addVariable("dPhiMet"+leps[il],60,-3.1416926524,3.1416926524,"#Delta#phi(#slash{E}_{T},"+leps[il]+") [rad]");
  }
 
  if(_selection=="WEl" || _selection=="WMu" || _selection=="WZ") {
    //single lepton variables
    for(size_t iwt=0;iwt<wTypes.size();iwt++) {
      string wType=wTypes[iwt];
      _hm->addVariable("WPt"+wType, 200, 0., 200.0,"p_{T}(W_{"+wType+"}) [GeV]");
      _hm->addVariable("WPhi"+wType, 60, 0, 3.1416926524*2,"#phi(W_{"+wType+"}) [rad]");
      _hm->addVariable("MT"+wType, 200, 0., 200.0,"#M_{T}("+wType+") [GeV]");
      _hm->addVariable("WY"+wType, 60, 0, 3.1416926524*2,"Y("+wType+") ");
      _hm->addVariable("lCTS"+wType, 50, -1, 1,"cos(#theta^{*}_{#ell^{"+wType+"}}) ");
    }
  }
  
  if(_selection!="WEl" && _selection!="WMu" && _selection!="4L") { //dilepton
    //dilepton variables
    _hm->addVariable("Zmass", 400, 0., 400.0,"m_{"+lepPairType+"} [GeV]");
    _hm->addVariable("ZmassSS", 400, 0., 400.0,"m_{"+lepPairType+"} [GeV]");
    _hm->addVariable("ZPt", 400, 0., 400.0,"p_{T}("+lepPairType+") [GeV]");
    _hm->addVariable("ZPhi", 60, 0, 3.1416926524*2,"#phi("+lepPairType+") [rad]");
    _hm->addVariable("ZY", 60, 0, 3.1416926524*2,"Y("+lepPairType+") ");
    for(int il=0;il<leps.size();il++) {
      //kinematic and dynamic variables
      _hm->addVariable(leps[il]+"Pt", 200, 0., 200.0,"p_{T}("+leps[il]+") [GeV]");
      _hm->addVariable(leps[il]+"Eta", 60, -3.0, 3.0,"#eta("+leps[il]+") ");
      _hm->addVariable(leps[il]+"Phi", 60, 0, 3.1416926524*2,"#phi("+leps[il]+") ");
      _hm->addVariable(leps[il]+"CTS", 50, -1, 1,"cos(#theta^{*}_{"+leps[il]+"}) ");
    }
  }

  if(_selection=="4L") {
    //4L variables
    _hm->addVariable("4lmass", 400, 0., 400.0,"m_{4l} [GeV]");
    _hm->addVariable("flavor",4,0,4,"flavor",true,false,
		     vector<string>({"eee","ee#mu","e#mu#mu","#mu#mu#mu"}));
  }
 
}
  

void
Comissioning::writeOutput() {
 
}


void
Comissioning::run() {

  counter("denominator");

 
  selectObjects();
  

}


bool
Comissioning::passFilters() {

  if(!_vc->get("hbheFilterNew25ns")) return false;
  if(!_vc->get("Flag_CSCTightHaloFilter")) return false;
  if(!_vc->get("Flag_eeBadScFilter")) return false;
  
  return true;
}

bool
Comissioning::pileupSelection() {

  if(!passMultiLine(_puLines)) return false;
  if(!_vc->get("nLepGood")>=2) return false;
 
  selectObject(kLep);
  
  if(!_leps[0]->pt()>25) return false;
  if(!_leps[1]->pt()>15) return false;
  if( !(_leps[0]->eta()<2.1&&_leps[1]->eta()<2.1) ) return false;
  if( !(_leps[0]->pdgId()==-_leps[1]->pdgId() ) ) return false;
  float mass=Candidate::create(_leps[0],_leps[1])->mass();
  if(mass<60 || mass>120) return false;
  
}

bool
Comissioning::ZeeSelection() {

  if(!passMultiLine(_zeeLines)) return false;
  if(!_vc->get("nLepGood"==2) ) return false;
  
  selectObject(kEl, false);
  
  if( !(_leps[0]->pdgId()==-_leps[1]->pdgId() ) ) return false;
  if(!(_leps[0]->pt()>30 && _leps[1]->pt()>15) ) return false;
  if( !(_leps[0]->eta()<2.1) ) return false;
  if(!std::abs(_leps[0]->pdgId())==-11) return false;
  
  float mass=Candidate::create(_leps[0],_leps[1])->mass();
  if(mass<60 || mass>120) return false;
  if(! (_vc->get("LepGood_relIso03",_lepsIdx[0])<0.2) ) return false;
  
  return true;
}

bool
Comissioning::ZmmSelection() {

  if(!passMultiLine(_zmmLines)) return false;
  if(!_vc->get("nLepGood")==2) return false;
 
  selectObject(kMu);


  if( !(_leps[0]->pdgId()==-_leps[1]->pdgId() ) ) return false;
  if(!(_leps[0]->pt()>30 && _leps[1]->pt()>15) ) return false;
  if( !(_leps[0]->eta()<2.1) ) return false;
  if(!std::abs(_leps[0]->pdgId())==-11) return false;
  
  float mass=Candidate::create(_leps[0],_leps[1])->mass();
  if(mass<60 || mass>120) return false;
  if(! (_vc->get("LepGood_relIso03",_lepsIdx[0])<0.2) ) return false;
  
  return true;
  
}

bool
Comissioning::ZlSelection() {

  if(!passMultiLine(_zlLines)) return false;
  if(!_vc->get("nLepGood")==3) return false;
 
  selectObject(kLep);
  
  if( !(_leps[0]->pdgId()==-_leps[1]->pdgId() ) ) return false;
  if(!(_leps[0]->pt()>25 && _leps[1]->pt()>15) ) return false;
  if(!(_leps[0]->pt()>50) ) return false;

  float mass=Candidate::create(_leps[0],_leps[1])->mass();
  if(!mass>12) return false;
  if(!std::abs(mass-91.2)>10 ) return false;
  
  if(! KineUtils::M_T(_leps[0]->pt(), _met->pt(),_leps[0]->phi(), _met->phi())<55 ) return false;

  if(!_met->pt()<60) return false;

  return true;
}

bool
Comissioning::WeSelection() {

  if(!passMultiLine(_weLines)) return false;
  if(!_vc->get("nLepGood")==1) return false;
  
  selectObject(kEl);


  if(! (_leps[0]->charge()*_leps[0]->charge()>0) ) return false;
  if(!(_leps[0]->pt()>30) ) return false;
  if(! (_vc->get("LepGood_tightCharge",_lepsIdx[0])>1) ) return false;
  if(! (_vc->get("LepGood_relIso03",_lepsIdx[0])<0.05) ) return false;
  if(! (_vc->get("LepGood_miniRelIso",_lepsIdx[0])<0.05) ) return false;
  if(! (_vc->get("LepGood_sip3d",_lepsIdx[0])<4) ) return false;
  if(! _vc->get("nBJetMedium25")==0 ) return false;
  if(! KineUtils::M_T(_leps[0]->pt(), _met->pt(),_leps[0]->phi(), _met->phi())>40 ) return false;
  
  return true;


}

bool
Comissioning::WmSelection() {

  if(!passMultiLine(_wmLines)) return false;
  if(!_vc->get("nLepGood")==1) return false;
  
  selectObject(kMu);

  if(! (_leps[0]->charge()*_leps[0]->charge()>0) ) return false;
  if(!(_leps[0]->pt()>30) ) return false;
  if(! (_vc->get("LepGood_relIso03",_lepsIdx[0])<0.05) ) return false;
  if(! (_vc->get("LepGood_miniRelIso",_lepsIdx[0])<0.05) ) return false;
  if(! (_vc->get("LepGood_sip3d",_lepsIdx[0])<4) ) return false;
  if(! _vc->get("nBJetMedium25")==0 ) return false;
  if(! KineUtils::M_T(_leps[0]->pt(), _met->pt(),_leps[0]->phi(), _met->phi())>40 ) return false;
  
  return true;
}


bool
Comissioning::WlSelection() {

  if(!passMultiLine(_weLines)) return false;
  if(!_vc->get("nLepGood")==2) return false;
  
  selectObject(kLep, false);
  if(! (_leps[0]->charge()*_leps[0]->charge()>0) ) return false;
  if(!(_leps[0]->pt()>30 && _leps[1]->pt()>10) ) return false;
  if(! (_vc->get("LepGood_tightCharge",_lepsIdx[0])>(std::abs(_leps[0]->pdgId())==11) ) ) return false;
  if(! (_vc->get("LepGood_tightCharge",_lepsIdx[1])>(std::abs(_leps[1]->pdgId())==11) ) ) return false;  
  if(! (_vc->get("LepGood_relIso03",_lepsIdx[0])<0.05) ) return false;
  if(! (_vc->get("LepGood_miniRelIso",_lepsIdx[0])<0.05) ) return false;
  if(! (_vc->get("LepGood_sip3d",_lepsIdx[0])<4) ) return false;
  if(! _vc->get("nBJetMedium25")==0 ) return false;
  if(! KineUtils::M_T(_leps[0]->pt(), _met->pt(),_leps[0]->phi(), _met->phi())>40 ) return false;
  if(!(std::abs(_leps[0]->pdgId()+leps[1]->pdgId())!=22 || 
       std::abs(Candidate::create(_leps[0],_leps[1])->mass()-91.2)>15) ) return false;

  return true;
}




bool
Comissioning::ttbarSelection() {

  if(!passMultiLine(_ttbarLines)) return false;
  if(!_vc->get("nLepGood")>=2) return false;
  
  selectObject(kLep, false);

  if( !(_leps[0]->pdgId()==-_leps[1]->pdgId() ) ) return false;
  if(!(_leps[0]->pt()>25 && _leps[1]->pt()>15) ) return false;
  if(! (_vc->get("LepGood_miniRelIso",_lepsIdx[0])<0.05) ) return false;
  float mass=Candidate::create(_leps[0],_leps[1])->mass();
  if(!mass>12) return false;
  if(!std::abs(mass-91.2)>10 ) return false;
  if(!_jets.size()>=2) return false;
  if(!(_vc->get("nBJetMedium25")>=1||_vc->get("nBJetLoose25")>=1)) return false;

  return true;
}

bool
Comissioning::ttbarSemiLepSelection() {

  if(!passMultiLine(_ttbarSlLines)) return false;
  if(!_vc->get("nLepGood")>=2) return false;
  
  selectObject(kLep, false);


  if(!(_vc->get("nJet25")>=3 && _vc->get("nJet25")<=4) ) return false;
  if(!(_vc->get("nBJetMedium25")==1) ) return false;

  if(!(_leps[0]->pt()>25 && _leps[1]->pt()>15) ) return false;
  if(! (_leps[0]->charge()*_leps[0]->charge()>0) ) return false;
  if(! (_vc->get("LepGood_sip3d",_lepsIdx[0])<4) ) return false;
  if(! (_vc->get("LepGood_miniRelIso",_lepsIdx[0])<0.05) ) return false;
  float mass=Candidate::create(_leps[0],_leps[1])->mass();
  if(!mass>12) return false;
  if(! (_vc->get("LepGood_tightCharge",_lepsIdx[0])>(std::abs(_leps[0]->pdgId())==11) ) ) return false;
  if(! (_vc->get("LepGood_mvaTTH",_lepsIdx[1])<0.8) ) return false;
  if(! ( (_leps[0]->pt()>30 && std::abs(_leps[0]->pdgId()==11) ) || (_leps[0]->pt()>20 && std::abs(_leps[0]->pdgId()==13) ) ) ) return false;
  if(!std::abs(_leps[0]->eta())<2.1) return false;

  return true;
}


// bool
// Comissioning::WZSelection() {


// }

// bool
// Comissioning::ZZSelection() {


// }



void
Comissioning::selectObjects(int type, bool sel) {

  _leps.clear();
  _lepsIdx.clear();
  
  _jets.clear();
  _jetsIdxs.clear();

  for(size_t il=0;il<_vc->get("nLepGood"); il++) {

    bool isMu=std::abs(_vc->get("LepGood_pdgId", il))==13;

    if(isMu && type==kEl) continue;
    if(!isMu && type==kMu) continue;

    Candidate* cand=Candidate::create(_vc->get("LepGood_pt", il),
				      _vc->get("LepGood_eta", il),
				      _vc->get("LepGood_phi", il),
				      _vc->get("LepGood_pdgId", il),
				      _vc->get("LepGood_charge", il),
				      isMu?0.105:0.0005);
   
   
    int cc1=_vc->get("LepGood_mcUCSXMatchId",il) ;
  

    _leps.push_back(cand);
    _lepsIdx.push_back(il);

  }//lep loop

  for(size_t ij=0;ij<_vc->get("nJet");ij++) {
    
    if(_vc->get("Jet_id",ij)<1) continue;

    Candidate* jet=Candidate::create(_vc->get("Jet_pt", ij),
				     _vc->get("Jet_eta", ij),
				     _vc->get("Jet_phi", ij) );
    
    bool findLep=false;
    for(unsigned int il=0;il<_leptons.size();il++) {
      
      if( _leptons[il]->dR( jet )<0.4 ) {findLep=true; 
	continue;} 
    }
    if(findLep) continue;
    
    if(jet->pt()<25) continue;
    _jets.push_back(jet);
    _jetsIdxs.push_back(ij);
  }

  _met = Candidate::create( _vc->get("met_pt"), _vc->get("met_phi") );  
  
}

bool
Comissioning::passHLLine(string line) {
  if(_vc->get(line)) return true;
  else return false;
}

bool
Comissioning::passMultiLine(const vector<string>& hltLines) {
  
  if(!_isData) return true;
  for(size_t ih=0;ih<hltLines.size();ih++) {
    if(passHLLine(hltLines[ih])) return true;
  }

  return false;
}
