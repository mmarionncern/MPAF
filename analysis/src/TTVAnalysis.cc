#include "analysis/src/TTVAnalysis.hh"

#include <algorithm>

TTVAnalysis::TTVAnalysis(std::string cfg){
  
  configure(cfg);
  _susyMod=new SusyModule(_vc,_dbm);
  
  _susyMod->configureLeptonId(SusyModule::kMVA);
  initialize();
  
}

TTVAnalysis::~TTVAnalysis(){
  if(_dumpEvents) {
    _ofileDump->close();
  }
  //_vc->printUsedVarNames();
}

void
TTVAnalysis::initialize(){


  _vc->registerVar("run"                          );
  _vc->registerVar("lumi"                         );
  _vc->registerVar("evt");
  _vc->registerVar("isData"                       );
  _vc->registerVar("HLT_SingleEl"                 );
  _vc->registerVar("HLT_SingleMu"                 );
  _vc->registerVar("HLT_SingleEl50ns"             );
  _vc->registerVar("HLT_SingleMu50ns"             );
  _vc->registerVar("HLT_MuEG"                     );
  _vc->registerVar("HLT_MuEGHT"                   );
  _vc->registerVar("HLT_DoubleEl"                 );
  _vc->registerVar("HLT_DoubleElHT"               );
  _vc->registerVar("HLT_DoubleMu"                 );
  _vc->registerVar("HLT_DoubleMuHT"               );
  _vc->registerVar("nVert"                        );
  _vc->registerVar("nTrueInt"                     );
  _vc->registerVar("nBJetPt40Medium"              );
  _vc->registerVar("puWeight"                     );
  _vc->registerVar("genWeight"                    );
  if(_lheSystComputation)
    _vc->registerVar("LHEweight_wgt"              );
  _vc->registerVar("nLepGood"                     );
  _vc->registerVar("LepGood_pt"                   );
  _vc->registerVar("LepGood_eta"                  );
  _vc->registerVar("LepGood_etaSc"                );
  _vc->registerVar("LepGood_phi"                  );
  _vc->registerVar("LepGood_charge"               );
  _vc->registerVar("LepGood_tightCharge"          );
  _vc->registerVar("LepGood_tightId"              );
  _vc->registerVar("LepGood_looseIdOnly"          );
  _vc->registerVar("LepGood_mediumMuonId"         );
  _vc->registerVar("LepGood_mediumMuonID2016"     );
  _vc->registerVar("LepGood_mvaIdSpring15"        );
  _vc->registerVar("LepGood_mvaIdSpring16GP"      );
  _vc->registerVar("LepGood_mvaIdSpring16HZZ"     );
  _vc->registerVar("LepGood_mvaIdFall17noIso"     );
  _vc->registerVar("LepGood_jetNDauChargedMVASel" );
  _vc->registerVar("LepGood_miniRelIsoCharged"    );
  _vc->registerVar("LepGood_miniRelIsoNeutral"    );
  _vc->registerVar("LepGood_pdgId"                );
  _vc->registerVar("LepGood_relIso03"             );
  _vc->registerVar("LepGood_relIso04"             );
  _vc->registerVar("LepGood_jetPtRatiov2"         );
  _vc->registerVar("LepGood_jetPtRelv2"           );
  _vc->registerVar("LepGood_jetBTagCSV"           );
  _vc->registerVar("LepGood_jetBTagDeepCSV"       );
  _vc->registerVar("LepGood_jetRawPt"             );
  _vc->registerVar("LepGood_jetCorrFactor_L1L2L3Res");
  _vc->registerVar("LepGood_miniRelIso"           );
  _vc->registerVar("LepGood_segmentCompatibility" );
  _vc->registerVar("LepGood_dxy"                  );
  _vc->registerVar("LepGood_dz"                   );
  _vc->registerVar("LepGood_sip3d"                );
  _vc->registerVar("LepGood_convVeto"             );
  _vc->registerVar("LepGood_lostHits"             );
  _vc->registerVar("LepGood_mvaSUSY"              );
  _vc->registerVar("LepGood_mvaTTH"               );
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
  // _vc->registerVar("nLepOther"                     );
  // _vc->registerVar("LepOther_pt"                   );
  // _vc->registerVar("LepOther_eta"                  );
  // _vc->registerVar("LepOther_etaSc"                );
  // _vc->registerVar("LepOther_phi"                  );
  // _vc->registerVar("LepOther_charge"               );
  // _vc->registerVar("LepOther_tightCharge"          );
  // _vc->registerVar("LepOther_mediumMuonId"         );
  // _vc->registerVar("LepOther_mediumMuonID2016"     );
  // _vc->registerVar("LepOther_mvaIdSpring15"        );
  // _vc->registerVar("LepOther_mvaIdSpring16GP"      );
  // _vc->registerVar("LepOther_pdgId"                );
  // _vc->registerVar("LepOther_relIso03"             );
  // _vc->registerVar("LepOther_relIso04"             );
  // _vc->registerVar("LepOther_jetPtRatiov2"         );
  // _vc->registerVar("LepOther_jetPtRelv2"           );
  // _vc->registerVar("LepOther_jetBTagCSV"           );
  // _vc->registerVar("LepOther_jetRawPt"             );
  // _vc->registerVar("LepOther_jetCorrFactor_L1L2L3Res");
  // _vc->registerVar("LepOther_miniRelIso"           );
  // _vc->registerVar("LepOther_segmentCompatibility" );
  // _vc->registerVar("LepOther_dxy"                  );
  // _vc->registerVar("LepOther_dz"                   );
  // _vc->registerVar("LepOther_sip3d"                );
  // _vc->registerVar("LepOther_convVeto"             );
  // _vc->registerVar("LepOther_lostHits"             );
  // _vc->registerVar("LepOther_mvaSUSY"              );
  // _vc->registerVar("LepOther_mcMatchId"            );
  // _vc->registerVar("LepOther_mcMatchPdgId"         );
  // _vc->registerVar("LepOther_mcUCSXMatchId"        );
  // _vc->registerVar("LepOther_mcMatchAny"           );
  // _vc->registerVar("LepOther_sigmaIEtaIEta"        );
  // _vc->registerVar("LepOther_dEtaScTrkIn"          );
  // _vc->registerVar("LepOther_dPhiScTrkIn"          );
  // _vc->registerVar("LepOther_hadronicOverEm"       );
  // _vc->registerVar("LepOther_eInvMinusPInv"        );
  // _vc->registerVar("LepOther_ecalPFClusterIso"     );
  // _vc->registerVar("LepOther_hcalPFClusterIso"     );
  // _vc->registerVar("LepOther_dr03TkSumPt"          );
  // _vc->registerVar("LepOther_jetLepAwareJEC_pt"    );
  // _vc->registerVar("LepOther_jetLepAwareJEC_eta"    );
  // _vc->registerVar("LepOther_jetLepAwareJEC_phi"    );
  // _vc->registerVar("LepOther_jetLepAwareJEC_energy"    );
  // _vc->registerVar("LepOther_jetCorrFactor_L1L2L3Res"    );

  vector<string> extsJEC({""});//,"_jecUp","_jecDown"});

  for(unsigned int ie=0;ie<extsJEC.size();ie++) {

    _vc->registerVar("met"+extsJEC[ie]+"_pt"                       );
    _vc->registerVar("met"+extsJEC[ie]+"_eta"                      );
    _vc->registerVar("met"+extsJEC[ie]+"_phi"                      );
    _vc->registerVar("met"+extsJEC[ie]+"_mass"                     );
    _vc->registerVar("met"+extsJEC[ie]+"_genPt"                    );
    _vc->registerVar("met"+extsJEC[ie]+"_genPhi"                   );

    _vc->registerVar("nJet"+extsJEC[ie]                            );
    _vc->registerVar("Jet"+extsJEC[ie]+"_id"                       );
    _vc->registerVar("Jet"+extsJEC[ie]+"_puId"                     );
    _vc->registerVar("Jet"+extsJEC[ie]+"_pt"                       );
    _vc->registerVar("Jet"+extsJEC[ie]+"_rawPt"                    );
    _vc->registerVar("Jet"+extsJEC[ie]+"_eta"                      );
    _vc->registerVar("Jet"+extsJEC[ie]+"_phi"                      );
    _vc->registerVar("Jet"+extsJEC[ie]+"_mass"                     );
    _vc->registerVar("Jet"+extsJEC[ie]+"_mcFlavour"                );
    _vc->registerVar("Jet"+extsJEC[ie]+"_btagCSV"                  );
    _vc->registerVar("Jet"+extsJEC[ie]+"_btagDeepCSV"              );
    _vc->registerVar("Jet"+extsJEC[ie]+"_partonMotherId"           );
    _vc->registerVar("Jet"+extsJEC[ie]+"_qgl"                      );
    _vc->registerVar("Jet"+extsJEC[ie]+"_mcPt"                     );
    _vc->registerVar("Jet"+extsJEC[ie]+"_chHEF"                    );

    _vc->registerVar("Jet"+extsJEC[ie]+"_CorrFactor_L1"            );
    _vc->registerVar("Jet"+extsJEC[ie]+"_CorrFactor_L1L2L3Res"     );

    _vc->registerVar("Jet"+extsJEC[ie]+"_corr_JECUp"               );
    _vc->registerVar("Jet"+extsJEC[ie]+"_corr_JECDown"             );


    // _vc->registerVar("nDiscJet"+extsJEC[ie]                        );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_id"                   );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_pt"                   );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_rawPt"                );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_eta"                  );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_phi"                  );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_mass"                 );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_mcFlavour"            );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_btagCSV"              );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_partonMotherId"       );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_mcPt"                 );
    // _vc->registerVar("DiscJet"+extsJEC[ie]+"_chHEF"                );
  }

  // _vc->registerVar("nJetFwd"                      );
  // _vc->registerVar("JetFwd_pt"                    );
  // _vc->registerVar("JetFwd_eta"                   );
  // _vc->registerVar("JetFwd_phi"                   );
  
  //generator informations
  _vc->registerVar("nGenPart"                     );
  _vc->registerVar("GenPart_pt"                   );
  _vc->registerVar("GenPart_eta"                  );
  _vc->registerVar("GenPart_phi"                  );
  _vc->registerVar("GenPart_pdgId"                );
  _vc->registerVar("GenPart_motherId"             );
  _vc->registerVar("GenPart_mass");
  _vc->registerVar("GenPart_charge");
  _vc->registerVar("GenPart_status");

  _vc->registerVar("GenHiggsDecayMode");
  
  // FLAGS
  _vc->registerVar("hbheFilterNew25ns"            );
  _vc->registerVar("hbheFilterIso"                );
  _vc->registerVar("Flag_CSCTightHaloFilter"      );
  _vc->registerVar("Flag_eeBadScFilter"           );
  _vc->registerVar("Flag_goodVertices"            );
  _vc->registerVar("Flag_globalTightHalo2016Filter"  );
  // _vc->registerVar("Flag_badChargedHadronFilter"     );
  // _vc->registerVar("Flag_badMuonFilter"              );
  _vc->registerVar("Flag_badMuonMoriond2017"         );    

  //pileup
  _vc->registerVar("puWeight"                     );
  _vc->registerVar("vtxWeight"                    );

  //triggers
  _trgLines.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v");
  _trgLines.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v");
  _trgLines.push_back("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v");
  _trgLines.push_back("HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v");
  _trgLines.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  _trgLines.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  _trgLines.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  _trgLines.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  _trgLines.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
  for(size_t i=0;i<_trgLines.size();i++) {
    _vc->registerVar(_trgLines[i]);
  }



  string nnScheme=getCfgVarS("NNAnalysisScheme","vsWZ");

  _nnScheme=kNULL;
  if(nnScheme=="vsWZ") _nnScheme=kVsWZ;
  else if(nnScheme=="vsTZq") _nnScheme=kVsTZq;
  else if(nnScheme=="vsTZW") _nnScheme=kVsTZW;
  else if(nnScheme=="vsWZ:TZq") _nnScheme=kVsWZandTZq;
  else if(nnScheme=="vsWZ:TZW") _nnScheme=kVsWZandTZW;
  else if(nnScheme=="vsWZ:TTH") _nnScheme=kVsWZandTTH;
  else if(nnScheme=="vsWZ:TZq:TZW:TTH") _nnScheme=kVsWZandTZqandTZWandTTH;
  else if(nnScheme=="vsMulti") _nnScheme=kMulti;

  _valid=(bool)getCfgVarI("validation", 1);
  _sync=(bool)getCfgVarI("synchronization", 0);
  
  _id=getCfgVarS("lepIdScheme","TTH");
  _pickEvt=getCfgVarI("pickEvent",-1);

  _an=(getCfgVarS("analysisType","ttZ")=="ttZ"?(kTTZ):(kTTW));
  _fastAnalysis=(bool)(getCfgVarI("fastAnalysis",0));
  
  //NeuralNet
  if(!_skim && !_valid) {
    _vc->registerVarPfx("nNNScores_NNWZ","TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNWZ"    ,"TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNWZ_Up" ,"TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNWZ_Do" ,"TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNtZq"   ,"TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNtZq_Up","TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNtZq_Do","TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNMulti" ,"TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNMulti_Up","TiamattZFall17");
    _vc->registerVarPfx("NNRes_NNMulti_Do","TiamattZFall17");
    
    //if(_fastAnalysis) {
    _vc->registerVarPfx("nLepTight_Mini","ftIndices");
    _vc->registerVarPfx("iT_Mini","ftIndices");
    _vc->registerVarPfx("nJetSel_Mini","ftIndices");
    _vc->registerVarPfx("iJSel_Mini","ftIndices");	
      //  }
    
  }
    
  //Databases
  _dbm->loadDb("XS", "XSectionsSpring16.db");  
  _dbm->loadDb("KF", "kFactorsSpring16.db" );  
  _dbm->loadDb("puWeights","puWeights_37fb.root","puw");
  //_dbm->loadDb("fliprate"  , "chargeMId_80X_2016.root", "elChMId");
  _dbm->loadDb("fliprate"  , "chargeMId_80X_data_Moriond.root", "chargeMisId");
  _dbm->loadDb("fliprateMVAM"  , "chargeMId_80X_2016_AllMVA.root", "elChMId");
  _dbm->loadDb("fliprateMVAVT"  , "chargeMId_80X_2016_AllMVA.root", "elChMId");
  
  // for(int ids=0;ids<_datasets.size();ids++) {
  //   if(_datasets[ids]->getName().find("MuonEG")==(size_t)-1 && _datasets[ids]->getName().find("Double")==(size_t)-1)
  //     _dbm->loadDb("puWeights_"+_datasets[ids]->getName(),"pileupWeightsFall2017_nVert.root","pileup_"+_datasets[ids]->getName());
  // }


  
  //addWorkflow( 1, "SSW" );
  
  addWorkflow( kGlobalFake, "Fake" );
  _lheSystComputation=(bool)getCfgVarI("lheSystComputation", 0);
  if( ! (bool)getCfgVarI("noSystematics", 0) ) {
    addManualSystSource("jes",SystUtils::kNone);
    addManualSystSource("LF",SystUtils::kNone);
    addManualSystSource("HF",SystUtils::kNone);
    addManualSystSource("CSVHFStats1",SystUtils::kNone);
    addManualSystSource("CSVHFStats2",SystUtils::kNone);
    addManualSystSource("CSVLFStats1",SystUtils::kNone);
    addManualSystSource("CSVLFStats2",SystUtils::kNone);
    addManualSystSource("CSVCFErr1",SystUtils::kNone);
    addManualSystSource("CSVCFErr2",SystUtils::kNone);

    //addManualSystSource("btagJ",SystUtils::kNone);
    addManualSystSource("btagJ",SystUtils::kNone);
  }

  _dumpEvents = (bool)getCfgVarI("dumpEvents", 0 );
  if(_dumpEvents) {
    _ofileDump=new ofstream("eventDump_"+_cfgName+".txt", ios::out | ios::trunc );
  }

}

void
TTVAnalysis::modifyWeight() {
  _weight=1;
  if(!_vc->get("isData"))
    _weight=_vc->get("genWeight");
  if(!_vc->get("isData") && _valid && !_dumpEvents ) {//mm fixme
    //_weight *= _dbm->getDBValue("puWeights", _vc->get("nTrueInt"));
    //_weight *= _dbm->getDBValue("puWeights_"+_sampleName, _vc->get("nTrueInt"));
    double nProc=getCurrentDS()->getSumProcWgts(); 
    if(nProc==-1) nProc=getCurrentDS()->getNProcEvents();
    double w=1;//_dbm->getDBValue("XS", _sampleName) * _dbm->getDBValue("KF", _sampleName)/nProc * 1;//last number is lumi
    w*=36500;
    _weight *=w;
  }

}

void
TTVAnalysis::modifySkimming() {

  //removal for old full samples
  removeSkimBranch("lepWIdx");
  removeSkimBranch("jetIdx");
  removeSkimBranch("lepZIdx");

  
  // addSkimBranch<vector<int> >("jetIdx",&_jetIdx);
  addSkimBranch<int>("lepWIdx",&_lepWIdx);
  // addSkimBranch<vector<int> >("lepZIdx",&_lepZIdx);

  addSkimBranch<int>("jetIdx",_jetIdx,"jetIdx[10]/I");
  addSkimBranch<int>("lepZIdx",_lepZIdx,"lepZIdx[2]/I");

  
}


void
TTVAnalysis::defineOutput() {

  vector<string> leps({"l1","l2","l3","l4"});
  
  _hm->addVariable("nVertices",100,0,100,"vertex multiplicity ");
  _hm->addVariable("nTrueInt",100,0,100,"trueI multiplicity ");

  //lepton related variables
  _hm->addVariable("muMvaTTHEndcap",200,-1,1,"mvaTTH score (#mu, |#eta|>1.3)");
  _hm->addVariable("muMvaTTHBarrel",200,-1,1,"mvaTTH score (#mu, |#eta|<1.3)");
  _hm->addVariable("elMvaTTHEndcap",200,-1,1,"mvaTTH score (e, |#eta|>1.45)");
  _hm->addVariable("elMvaTTHBarrel",200,-1,1,"mvaTTH score (e, |#eta|<1.45)");
  
  //Jet related variables
  _hm->addVariable("nJets25", 20, 0., 20.0,"N(jet, p_{T}>25 GeV) ");
  //_hm->addVariable("nJets", 20, 0., 20.0,"N(jet, p_{T}>30 GeV) ");
  _hm->addVariable("nJets5", 21, -0.5, 20.5,"N(jet, p_{T}>25 GeV, |#eta|<5) ");
  _hm->addVariable("Jet1Pt", 200, 0., 500.0,"#p_{T}(j1) [GeV]");
  _hm->addVariable("Jet2Pt", 200, 0., 500.0,"#p_{T}(j2) [GeV]");
  _hm->addVariable("Jet1Eta", 60, -3.0, 3.0,"#eta(j1) ");
  _hm->addVariable("Jet2Eta", 60, -3.0, 3.0,"#eta(j2) ");
  _hm->addVariable("Jet1Phi", 60, 0, 3.1416926524*2,"#phi(j1) [rad]");
  _hm->addVariable("Jet2Phi", 60, 0, 3.1416926524*2,"#phi(j2) [rad]");
  _hm->addVariable("HT", 200,0., 500.0,"H_{T}(jet, p_{T}>30 GeV) [GeV]");
  _hm->addVariable("HT25", 200,0., 500.0,"H_{T}(jet, p_{T}>25 GeV) [GeV]");
 
  _hm->addVariable("nBJetsLoose", 20, 0., 20.0,"N(jet, p_{T}>25 GeV, CSVL) ");
  _hm->addVariable("nBJets", 20, 0., 20.0,"N(jet, p_{T}>25 GeV, CSVM) ");
  _hm->addVariable("BJet1Pt", 200, 0., 500.0,"#p_{T}(j_{1}, CSVM) [GeV]");
  _hm->addVariable("BJet2Pt", 200, 0., 500.0,"#p_{T}(j_{2}, CSVM) [GeV]");
  _hm->addVariable("HTB", 200,0., 500.0,"H_{T}(jet, p_{T}>25 GeV, CSVM) [GeV]");

  //MET related variables
  // _hm->addVariable("MetPt", 200, 0., 200.0,"#slash{E}_{T} [GeV]");
  // _hm->addVariable("MetPhi", 60, 0, 3.1416926524*2,"#phi(#slash{E}_{T}) [rad]");
  _hm->addVariable("MetSumEt", 1000, 0, 2000,"#Sigma E_{T} [GeV]");
  _hm->addVariable("dPhiMetJ1",60,-3.1416926524,3.1416926524,"#Delta#phi(#slash{E}_{T},j_{1}) [rad]");
  _hm->addVariable("dPhiMetJ2",60,-3.1416926524,3.1416926524,"#Delta#phi(#slash{E}_{T},j_{2}) [rad]");
  for(unsigned int il=0;il<leps.size();il++) {
    _hm->addVariable("dPhiMet"+leps[il],60,-3.1416926524,3.1416926524,"#Delta#phi(#slash{E}_{T},"+leps[il]+") [rad]");
  }

  _hm->addVariable("WMassW",200,0,1000,"m_{T}(l_{w}) [GeV]");
  _hm->addVariable("WMassZ1",200,0,1000,"m_{T}(l_{1}) [GeV]");
  _hm->addVariable("WMassZ2",200,0,1000,"m_{T}(l_{2}) [GeV]");
  
  //overall kinematic variables
  for(unsigned int il=0;il<leps.size();il++) {
    //kinematic and dynamic variables
    _hm->addVariable(leps[il]+"Pt", 200, 0., 200.0,"p_{T}("+leps[il]+") [GeV]");
    _hm->addVariable(leps[il]+"Eta", 60, -3.0, 3.0,"#eta("+leps[il]+") ");
    _hm->addVariable(leps[il]+"Phi", 60, 0, 3.1416926524*2,"#phi("+leps[il]+") ");
  }


  //higs decay channel
  _hm->addVariable("HDecayMode",30,0,30,"H decay mode ");
  
  vector<float> ptb({0,10,20,30,40,50,70,120,200});
  
  _hm->addVariable("elTTHEffPt",8,ptb, "p_{T}(e) [GeV]", true, true);
  _hm->addVariable("elTTHEffEta",6,vector<float>({0,0.4,0.8,1.2,1.479,1.8,2.5}), "|#eta|", true, true);
  _hm->addVariable("muTTHEffPt",8,ptb, "p_{T}(#mu) [GeV]", true, true);
  _hm->addVariable("muTTHEffEta",4,vector<float>({0,0.6,1.2,2.1,2.4}), "|#eta|", true, true);

  _hm->addVariable("elTTZEffPt",8,ptb, "p_{T}(e) [GeV]", true, true);
  _hm->addVariable("elTTZEffEta",6,vector<float>({0,0.4,0.8,1.2,1.479,1.8,2.5}), "|#eta|", true, true);
  _hm->addVariable("muTTZEffPt",8,ptb, "p_{T}(#mu) [GeV]", true, true);
  _hm->addVariable("muTTZEffEta",4,vector<float>({0,0.6,1.2,2.1,2.4}), "|#eta|", true, true);

  _hm->addVariable("elFakeTTHEffPt",8,ptb, "p_{T}(e) [GeV]", true, true);
  _hm->addVariable("elFakeTTHEffEta",6,vector<float>({0,0.4,0.8,1.2,1.479,1.8,2.5}), "|#eta|", true, true);
  _hm->addVariable("muFakeTTHEffPt",8,ptb, "p_{T}(#mu) [GeV]", true, true);
  _hm->addVariable("muFakeTTHEffEta",4,vector<float>({0,0.6,1.2,2.1,2.4}), "|#eta|", true, true);

  _hm->addVariable("elFakeTTZEffPt",8,ptb, "p_{T}(e) [GeV]", true, true);
  _hm->addVariable("elFakeTTZEffEta",6,vector<float>({0,0.4,0.8,1.2,1.479,1.8,2.5}),"|#eta|",true,true);
  _hm->addVariable("muFakeTTZEffPt",8,ptb, "p_{T}(#mu) [GeV]", true, true);
  _hm->addVariable("muFakeTTZEffEta",4,vector<float>({0,0.6,1.2,2.1,2.4}), "|#eta|", true, true);



  //NeuralNet
  _hm->addVariable("NeuralNetWZ",100.,0.,1.,"TiamattZ(WZ) score ");
  _hm->addVariable("NeuralNetTZq",100.,0.,1.,"TiamattZ(tZq) score ");
  _hm->addVariable("NeuralNetTZW",100.,0.,1.,"TiamattZ(tZW) score ");
  _hm->addVariable("NeuralNetTTH",100.,0.,1.,"TiamattZ(ttH) score ");

  _hm->addVariable("NeuralNetWZpos",100.,0.,1.,"TiamattZ(WZ) (+) score ");
  _hm->addVariable("NeuralNetTZqpos",100.,0.,1.,"TiamattZ(tZq) (+) score ");
  _hm->addVariable("NeuralNetTZWpos",100.,0.,1.,"TiamattZ(tZW) (+) score ");
  _hm->addVariable("NeuralNetTTHpos",100.,0.,1.,"TiamattZ(ttH) (+) score ");

  _hm->addVariable("NeuralNetWZneg",100.,0.,1.,"TiamattZ(WZ) (-) score ");
  _hm->addVariable("NeuralNetTZqneg",100.,0.,1.,"TiamattZ(tZq) (-) score ");
  _hm->addVariable("NeuralNetTZWneg",100.,0.,1.,"TiamattZ(tZW) (-) score ");
  _hm->addVariable("NeuralNetTTHneg",100.,0.,1.,"TiamattZ(ttH) (-) score ");

  _hm->addVariable("TiamattZCategStd",100.,0.,100,"TiamattZ(WZ) score ");
  _hm->addVariable("TiamattZCategStd2",100.,0.,100,"TiamattZ(WZ) score ");
  
  _hm->addVariable("TiamattZCateg",100,0,100,"TiamattZ category ");
  _hm->addVariable("TiamattZCategV2",42,1,43,"TiamattZ red. category ");

  
  int nBinCat=getNNCategV3(0.99,0.99,0.99,0.99);//38;
  _hm->addVariable("TiamattZCategV3", nBinCat,1,1+nBinCat,"");

  _hm->addVariable("TiamattZCategFall17", 40,1,41,"");
  _hm->addVariable("TiamattZCategFall17Multi", 40,1,41,"");
  
  _hm->addVariable("NN2DWZtZq",100,0.,1.,100,0.,1.,"NN(WZ) score","NN(tZq) score");
  _hm->addVariable("NN2DWZtZW",100,0.,1.,100,0.,1.,"NN(WZ) score","NN(tZW) score");
  _hm->addVariable("NN2DWZttH",100,0.,1.,100,0.,1.,"NN(WZ) score","NN(ttH) score");
  _hm->addVariable("NN2DtZqtZW",100,0.,1.,100,0.,1.,"NN(tZq) score","NN(tZW) score");
  _hm->addVariable("NN2DtZqttH",100,0.,1.,100,0.,1.,"NN(tZq) score","NN(ttH) score");
  _hm->addVariable("NN2DtZWttH",100,0.,1.,100,0.,1.,"NN(tZW) score","NN(ttH) score");
  
  _hm->addVariable("NNvsPdf",nBinCat,1,1+nBinCat,300,-3.,3.,"TiamattZ score","PDF weight relative variation");
  _hm->addVariable("NNmuR1muF05" ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=1, #mu_{F}=0.5)");
  _hm->addVariable("NNmuR1muF1"  ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=1, #mu_{F}=1)");
  _hm->addVariable("NNmuR1muF2"  ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=1, #mu_{F}=2)");
  _hm->addVariable("NNmuR05muF05",nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=0.5, #mu_{F}=0.5)");
  _hm->addVariable("NNmuR05muF1" ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=0.5, #mu_{F}=1)");
  _hm->addVariable("NNmuR05muF2" ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=0.5, #mu_{F}=2)");
  _hm->addVariable("NNmuR2muF05" ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=2, #mu_{F}=0.5)");
  _hm->addVariable("NNmuR2muF1"  ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=2, #mu_{F}=1)");
  _hm->addVariable("NNmuR2muF2"  ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=2, #mu_{F}=2)");

  _hm->addVariable("normNNmuR1muF05" ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=1, #mu_{F}=0.5)");
  _hm->addVariable("normNNmuR1muF1"  ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=1, #mu_{F}=1)");
  _hm->addVariable("normNNmuR1muF2"  ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=1, #mu_{F}=2)");
  _hm->addVariable("normNNmuR05muF05",nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=0.5, #mu_{F}=0.5)");
  _hm->addVariable("normNNmuR05muF1" ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=0.5, #mu_{F}=1)");
  _hm->addVariable("normNNmuR05muF2" ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=0.5, #mu_{F}=2)");
  _hm->addVariable("normNNmuR2muF05" ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=2, #mu_{F}=0.5)");
  _hm->addVariable("normNNmuR2muF1"  ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=2, #mu_{F}=1)");
  _hm->addVariable("normNNmuR2muF2"  ,nBinCat,1,1+nBinCat,"TiamattZ score (#mu_{R}=2, #mu_{F}=2)");

  vector<string> scales({
      "#mu_{R}=1, #mu_{F}=1",
	"#mu_{R}=1, #mu_{F}=2",
	"#mu_{R}=1, #mu_{F}=0.5",
	"#mu_{R}=2, #mu_{F}=1",
	"#mu_{R}=2, #mu_{F}=2",
	"#mu_{R}=2, #mu_{F}=0.5",
	"#mu_{R}=0.5, #mu_{F}=1",
	"#mu_{R}=0.5, #mu_{F}=2",
	"#mu_{R}=0.5, #mu_{F}=0.5"});
  _hm->addVariable("accQCDScales",9,0.,9.,"QCD scales",true,false, scales );
  _hm->addVariable("nEvtQCDScales",9,0.,9.,"QCD scales",true,false, scales );
  
  //jet categoring
  _hm->addVariable("JetCateg",9,0,9,"jet categ",true,false,
		   vector<string>{"2j0b","2j1b","2j2b+",
		       "3j0b","3j1b","3j2b+",
		       "4j+0b","4j+1b","4j+2b+"});

  validationPlots();
  
}


void
TTVAnalysis::validationPlots() {
  
  int nJMax=10;

  vector<plotVar> var4V({plotVar("Pt",200, 0., 500.0,"p_{T} [GeV]"),
	                 plotVar("Eta",100, -5., 5.,"#eta "),
                         plotVar("Phi",60, 0, 3.1416926524*2,"#phi ")});

  vector<plotVar> varLep({plotVar("pdgId",2,0,2,"pdgId")});
  vector<plotVar> varZ({plotVar("Mass",200,0,500,"m_{ll} [GeV]")});
  vector<plotVar> varW({plotVar("TMass",200,0,500,"m_{T} [GeV]")});
  vector<plotVar> varJet({plotVar("DeepCSV",110,-0.05,1.05,"deepCSV "),
                          plotVar("QGL",110,-0.05,1.05,"q/g disc. "),
			  plotVar("Mass",200,0,500,"m_{j} [GeV]")});

  //storing the variables to be used
  for(auto it=var4V.begin(); it!=var4V.end(); it++)
    _var4V.push_back(it->name);
  for(auto it=varLep.begin(); it!=varLep.end(); it++)
    _varLep.push_back(it->name);
  for(auto it=varZ.begin(); it!=varZ.end(); it++)
    _varZ.push_back(it->name);
  for(auto it=varW.begin(); it!=varW.end(); it++)
    _varW.push_back(it->name);
  for(auto it=varJet.begin(); it!=varJet.end(); it++)
    _varJet.push_back(it->name);
  
  
  //first, Z leptons
  for(int i=0;i<2;i++) {
    ostringstream os; os<<i;

    for(auto it=var4V.begin(); it!=var4V.end(); it++) {
      _hm->addVariable("lepZ"+os.str()+it->name,it->nBins,it->xmin,it->xmax,it->leg);
      _hm->addVariable("lepZ"+os.str()+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
      _hm->addVariable("lepZ"+os.str()+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    }
    for(auto it=varLep.begin(); it!=varLep.end(); it++) {
      _hm->addVariable("lepZ"+os.str()+it->name,it->nBins,it->xmin,it->xmax,it->leg,true,false,vector<string>({"e","#mu"}));
      _hm->addVariable("lepZ"+os.str()+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true,vector<string>({"e","#mu"}));
      _hm->addVariable("lepZ"+os.str()+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true,vector<string>({"e","#mu"}));
    }
    for(auto it=varW.begin(); it!=varW.end(); it++) {
      _hm->addVariable("lepZ"+os.str()+it->name,it->nBins,it->xmin,it->xmax,it->leg);
      _hm->addVariable("lepZ"+os.str()+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
      _hm->addVariable("lepZ"+os.str()+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    }
    
  }//Z leptons

  //then Z candidate
  for(auto it=var4V.begin(); it!=var4V.end(); it++) {
    _hm->addVariable("Z"+it->name,it->nBins,it->xmin,it->xmax,it->leg);
    _hm->addVariable("Z"+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    _hm->addVariable("Z"+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
  }
  for(auto it=varZ.begin(); it!=varZ.end(); it++) {
    _hm->addVariable("Z"+it->name,it->nBins,it->xmin,it->xmax,it->leg);
    _hm->addVariable("Z"+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    _hm->addVariable("Z"+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
  }

  //then W
  for(auto it=var4V.begin(); it!=var4V.end(); it++) {
    _hm->addVariable("W"+it->name,it->nBins,it->xmin,it->xmax,it->leg);
    _hm->addVariable("W"+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    _hm->addVariable("W"+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
  }
  for(auto it=varW.begin(); it!=varW.end(); it++) {
    _hm->addVariable("W"+it->name,it->nBins,it->xmin,it->xmax,it->leg);
    _hm->addVariable("W"+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    _hm->addVariable("W"+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
  }

  //then W lepton
  for(auto it=var4V.begin(); it!=var4V.end(); it++) {
    _hm->addVariable("lepW"+it->name,it->nBins,it->xmin,it->xmax,it->leg);
    _hm->addVariable("lepW"+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    _hm->addVariable("lepW"+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
  }
  for(auto it=varLep.begin(); it!=varLep.end(); it++) {
    _hm->addVariable("lepW"+it->name,it->nBins,it->xmin,it->xmax,it->leg,true,false,vector<string>({"e","#mu"}));
    _hm->addVariable("lepW"+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true,vector<string>({"e","#mu"}));
    _hm->addVariable("lepW"+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true,vector<string>({"e","#mu"}));
  }

  //then jets
  for(int i=0;i<nJMax;i++) {
    ostringstream os; os<<i;

    for(auto it=var4V.begin(); it!=var4V.end(); it++) {
      _hm->addVariable("jet"+os.str()+it->name,it->nBins,it->xmin,it->xmax,it->leg);
      _hm->addVariable("jet"+os.str()+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
      _hm->addVariable("jet"+os.str()+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    }
    for(auto it=varJet.begin(); it!=varJet.end(); it++) {
      _hm->addVariable("jet"+os.str()+it->name,it->nBins,it->xmin,it->xmax,it->leg);
      _hm->addVariable("jet"+os.str()+it->name+"ProfDisc1",it->nBins,it->xmin,it->xmax,it->leg,true,true);
      _hm->addVariable("jet"+os.str()+it->name+"ProfDisc2",it->nBins,it->xmin,it->xmax,it->leg,true,true);
    }
  }
  
  //now general variables
  _hm->addVariable("disc1",104,-1.05,1.05,"disc1 ");
  _hm->addVariable("disc2",104,-1.05,1.05,"disc2 ");

  _hm->addVariable("disc1Vsdisc2",52,-1.05,1.05,52,-1.05,1.05,"disc1 ","disc2 ");

  _hm->addVariable("nJets", 20, 0., 20.0,"N(jet, p_{T}>30 GeV) ",true,false);
  _hm->addVariable("nLeps", 10, 0., 10.0,"N(lep) ",true,false);
  _hm->addVariable("lepFlavor", 4, 0., 4.0," ",true,false,vector<string>({"eee","ee#mu","e#mu#mu","#mu#mu#mu"}));
  _hm->addVariable("MetPt", 200, 0., 200.0,"#slash{E}_{T} [GeV]",true,false);
  _hm->addVariable("MetPhi", 60, 0, 3.1416926524*2,"#phi(#slash{E}_{T}) [rad]",true,false);

  _hm->addVariable("nJetsProfDisc1", 20, 0., 20.0,"N(jet, p_{T}>30 GeV) ",true,true);
  _hm->addVariable("nLepsProfDisc1", 10, 0., 10.0,"N(lep) ",true,true);
  _hm->addVariable("lepFlavorProfDisc1", 4, 0., 4.0," ",true,true,vector<string>({"eee","ee#mu","e#mu#mu","#mu#mu#mu"}));
  _hm->addVariable("MetPtProfDisc1", 200, 0., 200.0,"#slash{E}_{T} [GeV]",true,true);
  _hm->addVariable("MetPhiProfDisc1", 60, 0, 3.1416926524*2,"#phi(#slash{E}_{T}) [rad]",true,true);

  _hm->addVariable("nJetsProfDisc2", 20, 0., 20.0,"N(jet, p_{T}>30 GeV) ",true,true);
  _hm->addVariable("nLepsProfDisc2", 10, 0., 10.0,"N(lep) ",true,true);
  _hm->addVariable("lepFlavorProfDisc2", 4, 0., 4.0," ",true,true,vector<string>({"eee","ee#mu","e#mu#mu","#mu#mu#mu"}));
  _hm->addVariable("MetPtProfDisc2", 200, 0., 200.0,"#slash{E}_{T} [GeV]",true,true);
  _hm->addVariable("MetPhiProfDisc2", 60, 0, 3.1416926524*2,"#phi(#slash{E}_{T}) [rad]",true,true);
  
  
    
}



void
TTVAnalysis::fillPlots() {
  
  //fill("nJets", _cleanJets.size(), _weight);
  fill("nJets25", _cleanJets25.size(), _weight);
  if(_cleanJets.size()>=1) {
    fill("Jet1Pt", _cleanJets[0].c()->pt(), _weight);
    fill("Jet1Eta", _cleanJets[0].c()->eta(), _weight);
    fill("Jet1Phi", _cleanJets[0].c()->phi(), _weight);
  }
  if(_cleanJets.size()>=2) {
    fill("Jet2Pt", _cleanJets[1].c()->pt(), _weight);
    fill("Jet2Eta", _cleanJets[1].c()->eta(), _weight);
    fill("Jet2Phi", _cleanJets[1].c()->phi(), _weight);
  }
  
  fill("HT", _HT, _weight);
  fill("HT25", _HT25, _weight);
 
  //fill("nBJetsLoose", , _weight);
  fill("nBJets", _cleanBJets.size() , _weight);
  if(_cleanBJets.size()>=1)
    fill("BJet1Pt", _cleanBJets[0].c()->pt(), _weight);
  if(_cleanBJets.size()>=2)
    fill("BJet2Pt", _cleanBJets[1].c()->pt(), _weight);
  fill("HTB", _HTB, _weight);

  //MET related variables
  // fill("MetPt", _met->pt(), _weight);
  // fill("MetPhi", _met->phi(), _weight);
  //fill("MetSumEt", _vc->get("met_sumet"), _weight);
  if(_cleanJets.size()>=1)
    fill("dPhiMetJ1", KineUtils::dPhi(_cleanJets[0].c()->phi(),_met->phi()), _weight);
  if(_cleanBJets.size()>=1)
    fill("dPhiMetJ2", KineUtils::dPhi(_cleanJets[1].c()->phi(),_met->phi()), _weight);

  vector<string> leps({"l1","l2","l3","l4"});	   
  for(unsigned int il=0;il<leps.size();il++) {
    if(il<_allLeps.size())
      fill("dPhiMet"+leps[il], KineUtils::dPhi(_allLeps[il].c()->phi(),_met->phi()), _weight);
  }

 
  fill("WMassZ1", Candidate::create(_zCands[0]->daughter(0),_met)->mass(), _weight);
  fill("WMassZ2", Candidate::create(_zCands[0]->daughter(1),_met)->mass(), _weight);

  
  //overall kinematic variables
  for(unsigned int il=0;il<leps.size();il++) {
    //kinematic and dynamic variables
    if(il>=_allLeps.size()) continue;
    fill(leps[il]+"Pt", _allLeps[il].c()->pt(), _weight);
    fill(leps[il]+"Eta", _allLeps[il].c()->eta(), _weight);
    fill(leps[il]+"Phi", _allLeps[il].c()->phi(), _weight);
  }

  //if(!_isData)
  fill("HDecayMode", _vc->get("GenHiggsDecayMode"), _weight);

  
  string ext="";
  if(isInUncProc() && getUncName()=="jes" && getUncDir()==SystUtils::kUp)  ext="_Up";
  if(isInUncProc() && getUncName()=="jes" && getUncDir()==SystUtils::kDown)  ext="_Do";
  //float nnscore=0;
 
  //cout<<_vc->get("NNRes"+ext,0)<<"  "<<_vc->get("NNRes"+ext,1)<<"  "<<_vc->get("NNRes"+ext,2)<<endl;
  float w= _weight*_susyMod->btagCSVSF(_cleanJets, getUncName() , getUncDir() );
  //cout<<" --->>>>>>> "<<getUncName()<<"  "<<getUncDir()<<" -> "<<_weight<<"   "<<w<<" / "<<w/_weight<<endl;
  if(!_skim && _valid) {
    
    float nnscoreWZ=_vc->get("TiamattZFall17.NNRes_NNWZ"+ext,0);
    float nnscoreTZq=_vc->get("TiamattZFall17.NNRes_NNtZq"+ext,0);

    float nnscoreWZMulti=_vc->get("TiamattZFall17.NNRes_NNMulti"+ext,1);
    float nnscoreTZqMulti=_vc->get("TiamattZFall17.NNRes_NNMulti"+ext,2);

    float nnscoreTZW=-1000;
    float nnscoreTTH=-1000;
    //float nnscore=nnscoreWZ;
    
    // if(_nnScheme==kVsTZq || _nnScheme==kVsWZandTZq || _nnScheme==kVsWZandTZqandTZWandTTH ) {
    //   nnscoreTZq=_vc->get("TiamattZFall17.NNRes_NNtZq"+ext,0);
    //   //nnscore=nnscoreTZq;
    // }
    // if(_nnScheme==kVsTZW || _nnScheme==kVsWZandTZW || _nnScheme==kVsWZandTZqandTZWandTTH ) {
    //   nnscoreTZW=_vc->get("TiamattZv5.NNRes_NNtZW"+ext,0);
    //   //nnscore=nnscoreTZW;
    // }
    // if(_nnScheme==kVsTTH || _nnScheme==kVsWZandTTH || _nnScheme==kVsWZandTZqandTZWandTTH ) {
    //   nnscoreTTH=_vc->get("TiamattZv5.NNRes_NNttH"+ext,0);
    //   //nnscore=nnscoreTTH;
    // }

    int NNCategV3=0;//getNNCategV3(nnscoreWZ, nnscoreTZq, nnscoreTZW, nnscoreTTH);
    // fill("TiamattZCategV3",NNCategV3, w);

    int nnCateg=getNNCategFall17Separated(nnscoreWZ, nnscoreTZq);
    int nnCategMulti=getNNCategFall17MultiClassifier(nnscoreWZMulti, nnscoreTZqMulti);

    fill("TiamattZCategFall17",nnCateg, w);
    fill("TiamattZCategFall17Multi",nnCategMulti, w);

    
    if(_sampleName!="WZTo3LNu_ext" && _lheSystComputation) {
    

      for(int iw=0;iw<9;iw++) {
	fill("accQCDScales",iw, _vc->get("LHEweight_wgt",iw) );
      }

 

      for(int iw=9;iw<9+100;iw++) {
	float ww=_vc->get("LHEweight_wgt",iw)/_vc->get("LHEweight_wgt",0); //_vc->get("genWeight")
	fill("NNvsPdf", NNCategV3, ww);
      }
      
      fill("normNNmuR1muF1"  ,NNCategV3,1);
      fill("normNNmuR1muF2"  ,NNCategV3,1);
      fill("normNNmuR1muF05" ,NNCategV3,1);
      fill("normNNmuR2muF1"  ,NNCategV3,1);
      fill("normNNmuR2muF2"  ,NNCategV3,1);
      fill("normNNmuR2muF05" ,NNCategV3,1);
      fill("normNNmuR05muF1" ,NNCategV3,1);
      fill("normNNmuR05muF2" ,NNCategV3,1);
      fill("normNNmuR05muF05",NNCategV3,1);

      fill("NNmuR1muF1"  ,NNCategV3,_vc->get("LHEweight_wgt",0));
      fill("NNmuR1muF2"  ,NNCategV3,_vc->get("LHEweight_wgt",1));
      fill("NNmuR1muF05" ,NNCategV3,_vc->get("LHEweight_wgt",2));
      fill("NNmuR2muF1"  ,NNCategV3,_vc->get("LHEweight_wgt",3));
      fill("NNmuR2muF2"  ,NNCategV3,_vc->get("LHEweight_wgt",4));
      fill("NNmuR2muF05" ,NNCategV3,_vc->get("LHEweight_wgt",5));
      fill("NNmuR05muF1" ,NNCategV3,_vc->get("LHEweight_wgt",6));
      fill("NNmuR05muF2" ,NNCategV3,_vc->get("LHEweight_wgt",7));
      fill("NNmuR05muF05",NNCategV3,_vc->get("LHEweight_wgt",8));
    }

    fill("NeuralNetWZ",nnscoreWZ, w);
    if(_vc->get("genWeight")>=0) {
      fill("NeuralNetWZpos",nnscoreWZ, 1);
    } else {
      fill("NeuralNetWZneg",nnscoreWZ, 1);
    }
    if(_nnScheme==kVsTZq || _nnScheme==kVsWZandTZq || _nnScheme==kVsWZandTZqandTZWandTTH ) {
      fill("NeuralNetTZq",nnscoreTZq, w);
      if(_vc->get("genWeight")>=0) {
	fill("NeuralNetTZqpos",nnscoreTZq, 1);
      } else {
	fill("NeuralNetTZqneg",nnscoreTZq, 1);
      }
    }
    if(_nnScheme==kVsTZW || _nnScheme==kVsWZandTZW || _nnScheme==kVsWZandTZqandTZWandTTH ) {
      fill("NeuralNetTZW",nnscoreTZW, w);
      if(_vc->get("genWeight")>=0) {
	fill("NeuralNetTZWpos",nnscoreTZW, 1);
      } else {
	fill("NeuralNetTZWneg",nnscoreTZW, 1);
      }
    }
    if(_nnScheme==kVsTTH || _nnScheme==kVsWZandTTH || _nnScheme==kVsWZandTZqandTZWandTTH ) {
      fill("NeuralNetTTH",nnscoreTTH, w);
      if(_vc->get("genWeight")>=0) {
	fill("NeuralNetTTHpos",nnscoreTTH, 1);
      } else {
	fill("NeuralNetTTHneg",nnscoreTTH, 1);
      }
    }
    
    fill("NN2DWZtZq",nnscoreWZ,nnscoreTZq,w);
    fill("NN2DWZtZW",nnscoreWZ,nnscoreTZW,w);
    fill("NN2DWZttH",nnscoreWZ,nnscoreTTH,w);
    fill("NN2DtZqtZW",nnscoreTZq,nnscoreTZW,w);
    fill("NN2DtZqttH",nnscoreTZq,nnscoreTTH,w);
   

    int NNCateg=getNNCateg(nnscoreWZ, nnscoreTZq, nnscoreTZW, nnscoreTTH);
    fill("TiamattZCateg",NNCateg,w);

    int NNCategV2=getNNCategV2(nnscoreWZ, nnscoreTZq, nnscoreTZW, nnscoreTTH);
    //cout<<"  WZ="<<nnscoreWZ<<"  tZq="<<nnscoreTZq<<"   ttH="<<nnscoreTTH<<"   tZW="<<nnscoreTZW<<" -->> "<<NNCategV2<<endl;
    fill("TiamattZCategV2",NNCategV2,w);
        
    if(nnscoreWZ>0.95 && nnscoreTZq>0.5)
      fill("TiamattZCategStd",std::min(9,(int)(10*nnscoreTZW))+10*std::min(9,(int)(10*nnscoreTTH)), w);
    if(nnscoreWZ<=0.95 && nnscoreTZq<=0.5)
      fill("TiamattZCategStd2",std::min(9,(int)(10*nnscoreWZ))+10*std::min(9,(int)(10*nnscoreTZq)), w);
    
    fill("NN2DtZWttH",nnscoreTZW,nnscoreTTH,w);
      
  }
    
  float jetbtagw=_weight;
  //_btagW=1;
  if(!isInUncProc())  {
    _btagW = _susyMod->bTagSF( _cleanJets, _cleanBJets, 0, false, 0);
    jetbtagw *= _btagW;
  }
  else if(isInUncProc() && getUncName()=="btagJ" && getUncDir()==SystUtils::kUp )
    jetbtagw *= _susyMod->bTagSF( _cleanJets, _cleanBJets, 1, false); 
  else if(isInUncProc() && getUncName()=="btagJ" && getUncDir()==SystUtils::kDown )
    jetbtagw *= _susyMod->bTagSF( _cleanJets, _cleanBJets, -1, false); 
  else //other syst. variations
    jetbtagw *= _btagW;

  //cout<<" >>>>>>>>>> "<<getUncName()<<"  "<<getUncDir()<<" -> "<<jetbtagw/_weight<<endl;
  // cout<<isInUncProc()<<"   "<<getUncName()<<"   "<<getUncDir()
  //     <<" -->>> "<<_cleanJets.size()<<"  "<<_cleanBJets.size()<<endl;

  
  int jcateg=std::min(2, std::max((int)_cleanJets.size()-2,0))*3+std::min(2,(int)_cleanBJets.size());
  fill("JetCateg",jcateg,jetbtagw);

}

float
TTVAnalysis::getValue(const string& flag,const Candidate* c, int idx, const string& coll) {
  
  if(flag=="Pt")
    return c->pt();
  if(flag=="Eta")
    return c->eta();
  if(flag=="Phi")
    return c->phi();
  if(flag=="pdgId")
    return c->pdgId();
  if(flag=="Mass")
    return c->mass();
  if(flag=="TMass")
    return c->mass();
  if(flag=="DeepCSV")
    return _vc->get(coll+"_btagDeepCSV",idx);
  if(flag=="QGL")
    return _vc->get(coll+"_qgl",idx);
}


void
TTVAnalysis::fillValidationPlots() {
  
  string ext="";
  if(isInUncProc() && getUncName()=="jes" && getUncDir()==SystUtils::kUp)  ext="_Up";
  if(isInUncProc() && getUncName()=="jes" && getUncDir()==SystUtils::kDown)  ext="_Do";

  float nnscoreWZ=_vc->get("TiamattZFall17.NNRes_NNWZ"+ext,0);
  float nnscoreTZq=_vc->get("TiamattZFall17.NNRes_NNtZq"+ext,0);
  
  float nnscoreTTZMulti=_vc->get("TiamattZFall17.NNRes_NNMulti"+ext,0);
  float nnscoreWZMulti=_vc->get("TiamattZFall17.NNRes_NNMulti"+ext,1);

  //FIXME MM
  // TString sigA="(NNRes_NNMulti[0] - (NNRes_NNMulti[2]+NNRes_NNMulti[1]) )/(NNRes_NNMulti[0] + (NNRes_NNMulti[2]+NNRes_NNMulti[1]))";
  // //TString sigA="NNRes_NNMulti[0]";
  // tWZ->Draw("(NNRes_NNMulti[2]-NNRes_NNMulti[1])/(NNRes_NNMulti[2]+NNRes_NNMulti[1]):"+sigA+">>hWZ","nNNScores_NNMulti!=0","goff");
  float disc1=nnscoreWZ*2-1.;
  float disc2=nnscoreTZq*2-1.;
  if(false) {
    disc1=(2.*nnscoreTTZMulti-1);
    float nnscoreTZqMulti=1-nnscoreTTZMulti-nnscoreWZMulti;
    disc2=(nnscoreTZqMulti-nnscoreWZMulti)/(nnscoreTZqMulti+nnscoreWZMulti);
  }

  //first, Z leptons
  for(int i=0;i<2;i++) {
    ostringstream os; os<<i;
    for(auto it=_var4V.begin(); it!=_var4V.end(); it++) {
      fill("lepZ"+os.str()+(*it), getValue((*it),_zCands[0]->daughter(i)),_weight);
      fill("lepZ"+os.str()+(*it)+"ProfDisc1", getValue((*it),_zCands[0]->daughter(i)),disc1, _weight);
      fill("lepZ"+os.str()+(*it)+"ProfDisc2", getValue((*it),_zCands[0]->daughter(i)), disc2, _weight);
    }
    for(auto it=_varLep.begin(); it!=_varLep.end(); it++) {
      fill("lepZ"+os.str()+(*it), getValue((*it),_zCands[0]->daughter(i)),_weight);
      fill("lepZ"+os.str()+(*it)+"ProfDisc1", getValue((*it),_zCands[0]->daughter(i)),disc1, _weight);
      fill("lepZ"+os.str()+(*it)+"ProfDisc2", getValue((*it),_zCands[0]->daughter(i)), disc2, _weight);
    }
  }//z leptons

  //then Z candidate
  for(auto it=_var4V.begin(); it!=_var4V.end(); it++) {
    fill("Z"+(*it), getValue((*it),_zCands[0]),_weight);
    fill("Z"+(*it)+"ProfDisc1", getValue((*it),_zCands[0]),disc1, _weight);
    fill("Z"+(*it)+"ProfDisc2", getValue((*it),_zCands[0]), disc2, _weight);
  }
  for(auto it=_varZ.begin(); it!=_varZ.end(); it++) {
    fill("Z"+(*it), getValue((*it),_zCands[0]),_weight);
    fill("Z"+(*it)+"ProfDisc1", getValue((*it),_zCands[0]),disc1, _weight);
    fill("Z"+(*it)+"ProfDisc2", getValue((*it),_zCands[0]), disc2, _weight);
  }
  
  //then W
  //cout<<_lepWIdx<<"  "<<_allLeps.size()<<"  "<<_met<<endl;
  Candidate* wCand=Candidate::create(_allLeps[_lepWIdx].c(),_met);
  for(auto it=_var4V.begin(); it!=_var4V.end(); it++) {
    fill("W"+(*it), getValue((*it),wCand),_weight);
    fill("W"+(*it)+"ProfDisc1", getValue((*it),wCand),disc1, _weight);
    fill("W"+(*it)+"ProfDisc2", getValue((*it),wCand), disc2, _weight);
  }
  for(auto it=_varW.begin(); it!=_varW.end(); it++) {
    fill("W"+(*it), getValue((*it),wCand),_weight);
    fill("W"+(*it)+"ProfDisc1", getValue((*it),wCand),disc1, _weight);
    fill("W"+(*it)+"ProfDisc2", getValue((*it),wCand), disc2, _weight);
  }
  
  //then W lepton
  for(auto it=_var4V.begin(); it!=_var4V.end(); it++) {
    fill("lepW"+(*it), getValue((*it),_allLeps[_lepWIdx].c()),_weight);
    fill("lepW"+(*it)+"ProfDisc1", getValue((*it),_allLeps[_lepWIdx].c()),disc1, _weight);
    fill("lepW"+(*it)+"ProfDisc2", getValue((*it),_allLeps[_lepWIdx].c()), disc2, _weight);
  }
  for(auto it=_varLep.begin(); it!=_varLep.end(); it++) {
    fill("lepW"+(*it), getValue((*it),_allLeps[_lepWIdx].c()),_weight);
    fill("lepW"+(*it)+"ProfDisc1", getValue((*it),_allLeps[_lepWIdx].c()),disc1, _weight);
    fill("lepW"+(*it)+"ProfDisc2", getValue((*it),_allLeps[_lepWIdx].c()), disc2, _weight);
  }
    
  //then jets
  int nJMax=10;
  for(int i=0;i<10;i++) {
    if(_jetIdx[i]==-1) nJMax--;
  }
  
  for(int i=0;i<nJMax;i++) {
    ostringstream os; os<<i;
    Candidate* jet=_cleanJets[i].c();
    const string& coll=_cleanJets[i].coll();
    int idx=_cleanJets[i].idx();
    for(auto it=_var4V.begin(); it!=_var4V.end(); it++) {
      fill("jet"+os.str()+(*it), getValue((*it),jet),_weight);
      fill("jet"+os.str()+(*it)+"ProfDisc1", getValue((*it),jet),disc1, _weight);
      fill("jet"+os.str()+(*it)+"ProfDisc2", getValue((*it),jet), disc2, _weight);
    }
    for(auto it=_varJet.begin(); it!=_varJet.end(); it++) {
      fill("jet"+os.str()+(*it), getValue((*it),jet,idx,coll),_weight);
      fill("jet"+os.str()+(*it)+"ProfDisc1", getValue((*it),jet,idx,coll),disc1, _weight);
      fill("jet"+os.str()+(*it)+"ProfDisc2", getValue((*it),jet,idx,coll), disc2, _weight);
    }
  }//jets

  //now general variables
  int lepFlav=(_allLeps[_lepZIdx[0]].c()->pdgId()==13)+(_allLeps[_lepZIdx[0]].c()->pdgId()==13)+(_allLeps[_lepWIdx].c()->pdgId()==13);
  
  fill("disc1", disc1, _weight);
  fill("disc2", disc2, _weight);

  fill("disc1Vsdisc2", disc1, disc2, _weight);

  fill("nJets", nJMax, _weight);
  fill("nLeps", _allLeps.size(), _weight);
  fill("lepFlavor", lepFlav, _weight);
  fill("MetPt", _met->pt(), _weight);
  fill("MetPhi", _met->phi(), _weight);

  fill("nJetsProfDisc1", nJMax, disc1, _weight);
  fill("nLepsProfDisc1", _allLeps.size(), disc1, _weight);
  fill("lepFlavorProfDisc1", lepFlav, disc1, _weight);
  fill("MetPtProfDisc1", _met->pt(), disc1, _weight);
  fill("MetPhiProfDisc1", _met->phi(), disc1, _weight);
  
  fill("nJetsProfDisc2", nJMax,  disc2, _weight);
  fill("nLepsProfDisc2", _allLeps.size(),  disc2, _weight);
  fill("lepFlavorProfDisc2", lepFlav,  disc2, _weight);
  fill("MetPtProfDisc2", _met->pt(),  disc2, _weight);
  fill("MetPhiProfDisc2", _met->phi(),  disc2, _weight);
    
}


void
TTVAnalysis::writeOutput() {
 
}

void
TTVAnalysis::clearEvent() {

  _allLeps.clear();
  _leps.clear();
  _fakables.clear();

  _cleanJets.clear();
  _cleanJets25.clear();
  _cleanBJets.clear();
  _cleanJetsEta5.clear();
  _lepJets.clear();

  _zCands.clear();

  //_jetIdx.clear();
  _lepWIdx=-1;
  //_lepZIdx.clear();

  for(int i=0;i<10;i++) {
    _jetIdx[i]=-1;
    if(i<2)
      _lepZIdx[i]=-1;
  }

  _nJets=0;
  
}

void
TTVAnalysis::run() {
  clearEvent();
  counter("denominator");

  fill("nVertices",_vc->get("nVert"), _weight);
  if(!_vc->get("isData"))
    fill("nTrueInt",_vc->get("nTrueInt"), _weight);
  else {
    if(!passTriggerLine()) return;
  }
    
  counter("trigger");
  
  if( _pickEvt!=-1)
    if(_vc->get("evt")!=_pickEvt) return; //175711

  //if(_an==kTTZ && !_sync && !_skim && !_valid && _vc->get("TiamattZv2.nNNScores_NNWZ")==0) return;
  
  if(_sync)
    cout<<" -->> "<<_vc->get("nLepGood")<<endl;

  if(_fastAnalysis) {
    //if(_an==kTTW) ttWAnalysis();
    if(_an==kTTZ) ttZAnalysisFast();

    return;
  }
  
  //No need to consider so far events with less than 3 leptons
  //if(!_sync && _vc->get("nLepGood")<(_an+1)) {fillSkimTree();return;} //fillSkimTree();
  counter("super L leptons selection");

  //lepton selection
  makeLeptonList("LepGood", _leps,_fakables);
  _allLeps.insert(_allLeps.end(), _leps.begin(), _leps.end());
  //if(_sync)
  _allLeps.insert(_allLeps.end(), _fakables.begin(), _fakables.end());
  sort(_allLeps.rbegin(), _allLeps.rend() );

  if(_an==kTTW) ttWAnalysis();
  if(_an==kTTZ) ttZAnalysis();
  
}

void
TTVAnalysis::ttZAnalysisFast() {

  // if(_vc->get("ftIndices.lepWIdx")==-1) return;
  // if(_vc->get("ftIndices.lepZIdx",0)==-1 || _vc->get("ftIndices.lepZIdx",1)==-1) return;
  // if(_vc->get("ftIndices.jetIdx",0)==-1 || _vc->get("ftIndices.jetIdx",1)==-1) return;

  if(_vc->get("ftIndices.nLepTight_Mini")<3) return;
  counter("3 tight leptons");
  string ext="";
  if(isInUncProc() && getUncName()=="jes" && getUncDir()==SystUtils::kUp)  ext="_jecUp";
  if(isInUncProc() && getUncName()=="jes" && getUncDir()==SystUtils::kDown)  ext="_jecDown";
  bool isJecUnc=(isInUncProc() && getUncName()=="jes");

  if(_vc->get("ftIndices.nJetSel_Mini"+ext)<2) return;
  counter("2+ jets");
  makeObjectListFast("LepGood", "ftIndices.nLepTight_Mini" ,"ftIndices.iT_Mini",_allLeps);
  makeObjectListFast("Jet", "ftIndices.nJetSel_Mini","ftIndices.iJSel_Mini"+ext,_cleanJets, isJecUnc , getUncDir(), false);
  
  if(_allLeps[0].c()->pt()<25) {fillSkimTree();return;}
  if(_allLeps[1].c()->pt()<15) {fillSkimTree();return;}
  if(_allLeps[2].c()->pt()<15) {fillSkimTree();return;}
  counter("lepton pt");

  _zCands = buildZCands(_allLeps);
  if(_zCands.size()==0) return;
  counter("Z candidate");

  sortZCandidate( _zCands );
  _met = Candidate::create( _vc->get("met_pt"), _vc->get("met_phi") );
  //cout<<_allLeps.size()<<" <><> "<<_zCands.size()<<endl;
  for(int i=0;i<min((int)_cleanJets.size(),10);i++) {
    _jetIdx[i]=_cleanJets[i].idx();
  }

  for(unsigned int i=0;i<_allLeps.size();i++) {
    if(_allLeps[i].c()==_zCands[0]->daughter(0) ||
       _allLeps[i].c()==_zCands[0]->daughter(1) ) {
      if(_lepZIdx[0]==-1)
	_lepZIdx[0]=i;//_allLeps[i].idx();
      else
	_lepZIdx[1]=i;//_allLeps[i].idx();
    }
    else {
      if(_lepWIdx==-1) {
	_lepWIdx=i;//_allLeps[i].idx();
      }
    }
  }

  if(!passGenSelectionFast()) {setWorkflow(kGlobalFake);} //return false;
  else setWorkflow(kGlobal);
  counter("genlep selection");

  for(unsigned int il=0;il<_allLeps.size();il++) {
    if(std::abs(_allLeps[il].c()->pdgId())==11 &&
       _vc->get(_allLeps[il].coll()+"_tightCharge",_allLeps[il].idx())<2) return;
  }
  counter("charge sel");

  if(std::abs(_zCands[0]->mass()-91.1876)>25) {fillSkimTree();return;}//return false;
  counter("Z candidate");
  
  if( _cleanJets.size()<2) return;
  counter("dijet");
  
  fillPlots();
  fillValidationPlots();
  
}

void
TTVAnalysis::ttZAnalysis() {
  
  if(!_sync) if(!genAcceptanceSelection(3)) {fillSkimTree();return;} //fillSkimTree();
  if(_sampleName!="WZTo3LNu_ext" && _lheSystComputation)
    for(int iw=0;iw<9;iw++) {
      fill("nEvtQCDScales",iw, _vc->get("LHEweight_wgt",iw) );
    }
  
  counter("gen acceptance");
  //No need to consider so far events with less than 3 leptons
  if( _allLeps.size()!=3 ) {fillSkimTree();return;}//fillSkimTree();  return; //_fakables.size()+
  //if( !(_leps.size()<=3 && _allLeps.size()>=3) ) {fillSkimTree();return;}//return; //_fakables.size()+
  counter("3 tight or fakable leptons");
    
  // for(int i=0;i<allLeps.size();i++)
  //   cout<<"  -->>  "<<allLeps[i].c()->pdgId()<<"  "<<allLeps[i].c()->pt()<<endl;
  //cout<<" aqui "<<endl;
 
  if(_allLeps[0].c()->pt()<25) {fillSkimTree();return;} //fillSkimTree();
  if(_allLeps[1].c()->pt()<15) {fillSkimTree();return;} //fillSkimTree();
  if(_allLeps[2].c()->pt()<15) {fillSkimTree();return;} //fillSkimTree();
  counter("lepton pt");
    
  //MET definition
  _met = Candidate::create( _vc->get("met_pt"), _vc->get("met_phi") );
  //cout<<" aqua "<<endl;
  //could be done better
  bool isJecUnc=(isInUncProc() && getUncName()=="jes");
  cleanJets( &_allLeps, _cleanJets, _cleanBJets, _lepJets, 25, 25, (_sync?2.4:5), isJecUnc , getUncDir());
  if(_skim) {
    CandWrapList cleanBJetsEta5;
    cleanJets( &_allLeps, _cleanJets25, cleanBJetsEta5, _lepJets, 25, 25, 2.4, isJecUnc, SystUtils::kUp);
    cleanJets( &_allLeps, _cleanJetsEta5, cleanBJetsEta5, _lepJets, 25, 25, 5, isJecUnc, SystUtils::kDown);
    _nJets=std::max( _cleanJets.size(), std::max(_cleanJets25.size(), _cleanJetsEta5.size()) );
  }
  


  if(_cleanJets.size()!=_vc->get("ftIndices.nJetSel_Mini") ) {
    cout<<"================================================"<<endl;
    cout<<" WARNING "<<_ie<<"  "<<(unsigned long long)(_vc->get("evt"))<<endl;
    cout<<"leptons : "<<_allLeps.size()<<" / "<<_vc->get("ftIndices.nLepTight_Mini")<<endl;
    for(size_t i=0;i<_allLeps.size();i++)
      cout<<" --> "<<_allLeps[i].idx()<<" >> "<<_allLeps[i].c()->pt()<<endl;
    for(int i=0;i<_vc->get("ftIndices.nLepTight_Mini");i++)
      cout<<" ==> "<<_vc->get("ftIndices.iT_Mini",i)<<"  "<<_vc->get("LepGood_pt", _vc->get("ftIndices.iT_Mini",i) )<<"  "<<_vc->get("LepGood_pdgId", _vc->get("ftIndices.iT_Mini",i) )<<endl;

    cout<<" jets : "<<_cleanJets.size()<<" / "<<_vc->get("ftIndices.nJetSel_Mini")<<endl;
    for(size_t i=0;i<_cleanJets.size();i++)
      cout<<" --> "<<_cleanJets[i].idx()<<" >>  "<<_cleanJets[i].c()->pt()<<endl;
    for(int i=0;i<_vc->get("ftIndices.nJetSel_Mini");i++)
      cout<<" ==> "<<_vc->get("ftIndices.iJSel_Mini",i)
	  <<" >-> "<<_vc->get("Jet_pt", _vc->get("ftIndices.iJSel_Mini",i))<<endl;

  }

  //cout<<_ie<<" -->>> "<<_cleanJets.size()<<endl;
  _HT=_susyMod->HT( _cleanJets );
  _HT25=_susyMod->HT( _cleanJets25 );
  _HTB=_susyMod->HT( _cleanBJets );

  //  cout<<" aquo "<<endl;
  _zCands = buildZCands(_allLeps);
  sortZCandidate( _zCands );

  if(!selectionGhent()) return;

  if(!_skim && !_sync)
     fillValidationPlots();
  
  if(_dumpEvents) {
    dumpEvents();
  }


}


void
TTVAnalysis::ttWAnalysis() {
 
  if(!_sync) if(!genAcceptanceSelection(2)) {fillSkimTree();return;}
  if(_sampleName!="WZTo3LNu_ext" && _lheSystComputation)
    for(int iw=0;iw<9;iw++) {
      fill("nEvtQCDScales",iw, _vc->get("LHEweight_wgt",iw) );
    }
  
  counter("gen acceptance");
 
  if( _allLeps.size()!=2 ) {fillSkimTree();return;} //fillSkimTree();

  counter("2 tight or fakable leptons");
  if(_allLeps[0].c()->pt()<25) {fillSkimTree();return;} //fillSkimTree();
  if(_allLeps[1].c()->pt()<15) {fillSkimTree();return;} //fillSkimTree();
  counter("lepton pt");

  
  if( _allLeps[0].c()->charge()!=_allLeps[1].c()->charge() ) {fillSkimTree(); return;}
  counter("charge selection");
  
  //MET definition
  _met = Candidate::create( _vc->get("met_pt"), _vc->get("met_phi") );

  //could be done better
  bool isJecUnc=(isInUncProc() && getUncName()=="jes");
  cleanJets( &_allLeps, _cleanJets, _cleanBJets, _lepJets, 25, 25, (_sync?2.4:5), isJecUnc , getUncDir());
  //cleanJets( &_allLeps, _cleanJets25, _cleanBJets, _lepJets, 25, 25, 2.4, isJecUnc, getUncDir());
  CandWrapList cleanBJetsEta5;
  
  _HT=_susyMod->HT( _cleanJets );
  _HT25=_susyMod->HT( _cleanJets25 );
  _HTB=_susyMod->HT( _cleanBJets );

  if( (!_skim && _cleanJets.size()<2) ||
      (_skim && _vc->get("nJet")<2) ) {fillSkimTree();return;}//return false;
  counter("dijet");
  if(_skim) {
    for(int i=0;i<min((int)_cleanJets.size(),10);i++) {
      _jetIdx[i]=_cleanJets[i].idx();
    }
    
    for(unsigned int i=0;i<_allLeps.size();i++) {
      _lepZIdx[i]=_allLeps[i].idx();
    }
    fillSkimTree();
  }
  
  
}

void
TTVAnalysis::makeObjectListFast(const string& coll, const string& nObjTag, const string& tag,
				CandWrapList& listObj, bool isJESVar, int dir, bool full4V) {
  
  size_t nObj=_vc->get(nObjTag);
  for(size_t io=0;io<nObj;io++) {
    
    size_t il=_vc->get(tag,io);
    if(il==(size_t)-1) continue;
    Candidate* obj=nullptr;
    if(full4V) {
      obj=Candidate::create(_vc->get(coll+"_pt", il),
			    _vc->get(coll+"_eta", il),
			    _vc->get(coll+"_phi", il),
			    _vc->get(coll+"_pdgId",il),
			    _vc->get(coll+"_charge",il) );
    } else {
      //cout<<_ie<<"  "<<_vc->get(tag,io)<<"  "<<(unsigned int )(_vc->get(tag,io))<<"  "<<io<<"  "<<il<<"  "<<nObj<<"   "<<endl;
      float pt=_vc->get(coll+"_pt", il);
      if(isJESVar) {
	if(SystUtils::kUp==dir)
	  pt *=_vc->get(coll+"_corr_JECUp",il)/_vc->get(coll+"_CorrFactor_L1L2L3Res",il);
	else if(SystUtils::kDown==dir)
	  pt *=_vc->get(coll+"_corr_JECDown",il)/_vc->get(coll+"_CorrFactor_L1L2L3Res",il);
      }
      obj=Candidate::create(pt, _vc->get(coll+"_eta", il), _vc->get(coll+"_phi", il));
    }
    listObj.push_back( CandWrapper(obj, io, coll) );
  }

}
				
void
TTVAnalysis::makeLeptonList(const string& coll, 
			    CandWrapList& listLeps, 
			    CandWrapList& listFakes) {
 
  size_t nLep=_vc->get("n"+coll);
  for(size_t il=0;il<nLep;il++) {
    
    Candidate* obj=Candidate::create(_vc->get(coll+"_pt", il),
				     _vc->get(coll+"_eta", il),
				     _vc->get(coll+"_phi", il),
				     _vc->get(coll+"_pdgId",il),
				     _vc->get(coll+"_charge",il) );

    float ptCorr=0;
    if(_id!="TTH")
      ptCorr=conePtIllia(obj->pt(),obj->eta(),
			 std::abs(obj->pdgId())==13,
			 (std::abs(obj->pdgId())==13)?(_vc->get(coll+"_relIso04",il)):(_vc->get(coll+"_relIso03",il)) );
    else ptCorr=conePt(obj,il, coll);

    Candidate* objPtCorr=Candidate::create( ptCorr,
					    _vc->get("LepGood_eta", il),
					    _vc->get("LepGood_phi", il),
					    _vc->get(coll+"_pdgId",il),
					    _vc->get(coll+"_charge",il)	);


    //bool passLooseId=looseId(obj, il, "LepGood");
    bool passTightId=tightId(obj, il, "LepGood");
    bool passFakableId=fakableId(obj, il, "LepGood");
    
    if(_sync)
      cout<<" new lepton "<<obj->pdgId()<<"   "<<obj->pt()<<" / "<<obj->eta()<<" / "<<obj->phi()<<"  "<<ptCorr<<"  ==  "
	  <<passTightId<<"/"<<passFakableId
	  <<" ======================================================= "<<endl;

    
    if(std::abs(obj->eta()) > (std::abs(obj->pdgId())==13?2.4:2.5) ) continue; 
    if(obj->pt() < 10 ) continue;

    
    //if(_id!="TTH" && passLooseId ) continue;
    
   
   
    // if(std::abs(obj->pdgId())==11) {
    //   passTightId = _susyMod->elIdSelTTH(obj, il, "LepGood", SusyModule::kTight);
    //   passFakableId = _susyMod->elIdSelTTHClean(obj, il, "LepGood");
    // } else {
    //   passTightId = _susyMod->muIdSelTTH(obj, il, "LepGood", SusyModule::kTight);
    //   passFakableId = _susyMod->muIdSelTTHClean(obj, il, "LepGood");
    // }

    //if(_vc->get(coll+"_mcMatchId")!=0) {
    // if(!_skim) {
    //   if(_vc->get(coll+"_mcUCSXMatchId")<=1) {
    // 	if(std::abs(obj->pdgId())==11) {
    // 	  fill("elTTHEffPt", obj->pt(), elIdSelTTHTight(obj, il, coll) );
    // 	  fill("elTTHEffEta", std::abs(obj->eta()), elIdSelTTHTight(obj, il, coll) );
    // 	  fill("elTTZEffPt", obj->pt(), elIdSelTTZTight(obj, il, coll) );
    // 	  fill("elTTZEffEta", std::abs(obj->eta()), elIdSelTTZTight(obj, il, coll) );

    // 	} else {
    // 	  fill("muTTHEffPt", obj->pt(), muIdSelTTHTight(obj, il, coll) );
    // 	  fill("muTTHEffEta", std::abs(obj->eta()), muIdSelTTHTight(obj, il, coll) );
    // 	  fill("muTTZEffPt", obj->pt(), muIdSelTTZTight(obj, il, coll) );
    // 	  fill("muTTZEffEta", std::abs(obj->eta()), muIdSelTTZTight(obj, il, coll) );

    // 	}
    //   }
    //   if(_vc->get(coll+"_mcUCSXMatchId")>1) {
    // 	if(std::abs(obj->pdgId())==11) {
    // 	  fill("elFakeTTHEffPt", obj->pt(), elIdSelTTHTight(obj, il, coll) );
    // 	  fill("elFakeTTHEffEta", std::abs(obj->eta()), elIdSelTTHTight(obj, il, coll) );
    // 	  fill("elFakeTTZEffPt", obj->pt(), elIdSelTTZTight(obj, il, coll) );
    // 	  fill("elFakeTTZEffEta", std::abs(obj->eta()), elIdSelTTZTight(obj, il, coll) );
	  
    // 	} else {
    // 	  fill("muFakeTTHEffPt", obj->pt(), muIdSelTTHTight(obj, il, coll) );
    // 	  fill("muFakeTTHEffEta", std::abs(obj->eta()), muIdSelTTHTight(obj, il, coll) );
    // 	  fill("muFakeTTZEffPt", obj->pt(), muIdSelTTZTight(obj, il, coll) );
    // 	  fill("muFakeTTZEffEta", std::abs(obj->eta()), muIdSelTTZTight(obj, il, coll) );
	  
    // 	}
    //   }
    // }
    
    if( ptCorr<10 ) continue; //|| (!_valid && _vc->get(coll+"_pt",il)<10)

    if( !passFakableId ) continue;
    
    if(passTightId) {
      listLeps.push_back( CandWrapper(obj, il, coll) );
      //cout<<" tight lepton "<<obj->pdgId()<<"   "<<obj->pt()<<"  "<<obj->eta()<<endl;
    } else {
      // cout<<" fake lepton "<<obj->pdgId()<<"   "<<obj->pt()<<"  "<<objPtCorr->pt()<<endl;
      listFakes.push_back( CandWrapper(objPtCorr, il, coll) );
    }

    //dump ID
    // if(looseTTVLepton(il)) {
    //   listLeps.push_back( CandWrapper(obj, il, coll) );
    // }

    
  } //lepton loop
  
  //sort leptons
  std::sort(listLeps.rbegin(), listLeps.rend() ); 
  std::sort(listFakes.rbegin(), listFakes.rend() ); 

}


float 
TTVAnalysis::getFR(Candidate* cand, int idx, const string& type) {
  string db;
  float ptM=10;
  if( std::abs(cand->pdgId())==13) db="Mu";
  else { db="El"; ptM=15;}
  
  // // if(_HT<300) db+= "Iso";
  // // else
  //   db += "NIso";
  db+= "Iso";

  if(_vc->get("isData")!=1) db +="MC";


  if(isInUncProc() && getUncName()=="ewk_fr" && getUncDir()==SystUtils::kUp ) db+="Up";
  if(isInUncProc() && getUncName()=="ewk_fr" && getUncDir()==SystUtils::kDown ) db+="Do";

  float ptVal=cand->pt();
  //float etaVal=std::abs(cand->eta());

  int wp=SusyModule::kTight;

  ptVal=std::max(conePt(cand, idx, "LepGood"), ptM);
  //if(_FR.find("J")!=string::npos) ptVal/=_vc->get("LepGood_jetPtRatiov2", idx);

  ptVal=std::max(ptVal, ptM);

  //return max((float)0.,_dbm->getDBValue(db+type, std::min( ptVal,(float)69.9),
  //std::min(etaVal,(float)((std::abs(cand->pdgId())==11)?2.49:2.39) ) ) );

  float fr =0;// (std::abs(cand->pdgId())==13)?muonFakeRate(ptVal,etaVal):electronFakeRate(ptVal,etaVal);
  // if(type!="") {
  //   fr=_dbm->getDBValue(db+type, std::min( ptVal,(float)69.9),std::min(etaVal,(float)((std::abs(cand->pdgId())==11)?2.49:2.39) ) );
  // }

  return fr; 
}

bool
TTVAnalysis::isPrompt() {

  if(_vc->get("isData")==1) return false;

  if( _vc->get("LepGood_mcUCSXMatchId",0)<=1 &&
      _vc->get("LepGood_mcUCSXMatchId",1)<=1 ) return true;
  else return false;
  
}

bool
TTVAnalysis::passHLLine(string line) {
  if(_vc->get(line)) return true;
  else return false;
}



void
TTVAnalysis::cleanJets(CandWrapList* leptons, CandWrapList& cleanJets,
		       CandWrapList& cleanBJets, CandWrapList& lepJets,
		       float thr, float bthr, float etac, bool isJESVar, int dir ) {
  _sync=false;
  cleanJets.clear();
  cleanBJets.clear();
  lepJets.clear();
  
  vector<string> jetTypes({"Jet"}); //,"DiscJet"
  CandWrapList jets;
  vector<bool> bvals;
  
  for(size_t it=0;it<jetTypes.size();it++) {
    string jType=jetTypes[it];
    
    for(int ij=0;ij<_vc->get("n"+jType);ij++) {
      //if(_vc->get(jType+"_id",ij)<1) continue; //for now
      //if(std::abs(_vc->get(jType+"_eta",ij))>2.4) continue;
      
      float pt=_vc->get(jType+"_pt", ij);
      if(isJESVar) {
	if(SystUtils::kUp==dir)
	  pt *=_vc->get(jType+"_corr_JECUp",ij)/_vc->get(jType+"_CorrFactor_L1L2L3Res",ij);
	else if(SystUtils::kDown==dir)
	  pt *=_vc->get(jType+"_corr_JECDown",ij)/_vc->get(jType+"_CorrFactor_L1L2L3Res",ij);
      }
      
      Candidate* jet=Candidate::create(pt,
				       _vc->get(jType+"_eta", ij),
				       _vc->get(jType+"_phi", ij) );

      jets.push_back(CandWrapper(jet,ij,jType));
      bvals.push_back( _vc->get(jType+"_btagDeepCSV",ij)<0.8484  );//0.814
    }
  }

  map<Candidate*, std::pair<float,Candidate*> > cmap;
  map<Candidate*, std::pair<float,Candidate*> >::const_iterator it;
  //cout<<" nleptons "<<leptons->size()<<endl;
  for(unsigned int il=0;il<leptons->size();il++) {
    for(unsigned int ij=0;ij<jets.size();ij++) {
      float dR=leptons->at(il).c()->dR( jets[ij].c() );
      if(_sync)
       	cout<<" lep pt "<<leptons->at(il).c()->pt()<<" / jet pt "<<jets[ij].c()->pt()<<"  ==>> "<<dR<<endl;
      it = cmap.find(leptons->at(il).c());
      if(it==cmap.end() ) {
        cmap[ leptons->at(il).c() ] =std::make_pair(dR, jets[ij].c() );
      }
      else if(dR<it->second.first) {
        cmap[ leptons->at(il).c() ] =std::make_pair(dR, jets[ij].c() );
      }
    }
  }

  bool pass=true;
  if(_sync)
    cout<<" =============>>>>> "<<leptons->size()<<endl;
  for(unsigned int ij=0;ij<jets.size();ij++) {
    
    if(std::abs(jets[ij].c()->eta())>etac) continue;
    if(_sync)
      cout<<" jet  ====>>>>> "<<jets[ij].c()->pt()
	  <<" / "<<jets[ij].c()->eta()
	  <<" / "<<jets[ij].c()->phi()<<endl;
    
    pass=true;
    for(unsigned int il=0;il<leptons->size();il++) {
      it = cmap.find(leptons->at(il).c());
      if(it->second.first > 0.4 ) continue;
      if(it->second.second == jets[ij].c() ) {pass=false; break;}
      if(_sync)
	cout<<ij<<"  "<<il<<"  -->> dR="<<it->second.first<<"  leppt="<<leptons->at(il).c()->pt()<<"  <>  jetpt="<<jets[ij].c()->pt()<<" / "<<it->second.second->pt()<<"  -->>  "<<pass<<endl;
    }
    //cout<<jets[ij].c()->pt()<<"  passing? "<<pass<<endl;
    if(!pass) {
      lepJets.push_back(jets[ij]);
      continue;
    }
    
    //if(etac>3 && _vc->get(jets[ij].coll()+"_puId",jets[ij].idx())==0) continue;

    if(jets[ij].c()->pt()>thr) {
   
      cleanJets.push_back(jets[ij] );
    }
    
    if(bvals[ij]) continue;
    if(jets[ij].c()->pt()<bthr) continue;
    cleanBJets.push_back(jets[ij]);
  } //loop jets

  //cout<<" --->>> "<<cleanJets.size()<<endl;
  sort(cleanJets.rbegin(), cleanJets.rend());
  sort(cleanBJets.rbegin(), cleanBJets.rend());
  sort(lepJets.rbegin(), lepJets.rend());
  _sync=false;
}


CandList
TTVAnalysis::buildZCands(const CandWrapList& leps) {
  
  CandList zCandList;
  if(leps.size()==0) return zCandList;
 
  for(unsigned int il1=0;il1<leps.size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps.size();il2++) {
      
      if(leps[il1].c()->charge()==leps[il2].c()->charge() ) continue;
      if(leps[il1].c()->pdgId()!=-leps[il2].c()->pdgId() ) continue;
      zCandList.push_back( Candidate::create(leps[il1].c(), leps[il2].c()) );
      if(_sync)
	cout<<" l1: "<<leps[il1].c()->pt()<<"  l2: "<<leps[il2].c()->pt()
	    <<" --->>> "<<zCandList.back()->mass()<<endl;
    }
  }

  return zCandList;
}

void
TTVAnalysis::sortZCandidate(CandList& zList) {

  Candidate* tmpZ;
  
  for(unsigned int iz=0;iz<zList.size();iz++) {
    for(unsigned int iz2=0;iz2<iz;iz2++) {
      if( std::abs(zList[iz]->mass()-91.1876)<std::abs(zList[iz2]->mass()-91.1876)) {
	tmpZ=zList[iz];
	zList[iz]=zList[iz2];
	zList[iz2]=tmpZ;
      }
    }
  }

}

CandList
TTVAnalysis::buildWCands(const CandWrapList& leps, Candidate* met) {

  CandList wCandList;
  
  for(unsigned int il=0;il<leps.size();il++) {
    wCandList.push_back( Candidate::create(leps[il].c(), met) );
  }
  
  return wCandList;
}

bool
TTVAnalysis::selectionGhent() {
  
  if(!_sync && !_valid) {
    if(!passGenSelection()) {fillSkimTree();return false;}//return false;
  } else {
    if(!passGenSelection()) {setWorkflow(kGlobalFake);} //return false;
    else setWorkflow(kGlobal);
  }
  
  counter("gen selection");
  if(_sync && _id=="TTH") {
    for(unsigned int il=0;il<_allLeps.size();il++) {
      if(std::abs(_allLeps[il].c()->pdgId())==11 &&
	 _vc->get(_allLeps[il].coll()+"_tightCharge",_allLeps[il].idx())<2) return false;
    }
  }
  
  counter("charge sel");
  
  if(_zCands.size()==0) {fillSkimTree();return false;}//return false;
  if(_sync)
    cout<<" ---------=====>>>> "<<_zCands.size()<<"  "<<_zCands[0]->mass()<<" nJet: "<<_cleanJets.size()<<endl;
  if(std::abs(_zCands[0]->mass()-91.1876)>25) {fillSkimTree();return false;}//return false;
  counter("Z candidate");
  
  fill("nJets5", _cleanJetsEta5.size(), _weight);
  if((!_skim && _cleanJets.size()<2) ||
     (_skim && _nJets<2 ) ) {fillSkimTree();return false;}//return false; _vc->get("nJet")_vc->get("nJet")<2
  counter("dijet");

  if(!_skim && !_sync)
    fillPlots();
  
  {
    //_jetIdx.clear();
    for(int i=0;i<min((int)_cleanJets.size(),10);i++) {
      //_jetIdx.push_back(_cleanJets[i].idx());
      _jetIdx[i]=_cleanJets[i].idx();
    }
    
    for(unsigned int i=0;i<_allLeps.size();i++) {
      if(_allLeps[i].c()==_zCands[0]->daughter(0) ||
	 _allLeps[i].c()==_zCands[0]->daughter(1) ) {
	//_lepZIdx.push_back(_leps[i].idx());
	if(_lepZIdx[0]==-1)
	  _lepZIdx[0]=(_skim?_allLeps[i].idx():i);
	else
	  _lepZIdx[1]=(_skim?_allLeps[i].idx():i);
      }
      else {
	if(_lepWIdx==-1) {
	  _lepWIdx=(_skim?_allLeps[i].idx():i);
	  fill("WMassW", Candidate::create(_allLeps[i].c(),_met)->mass(), _weight);
	}
      }
    }
    if(_skim)
      fillSkimTree();
  }

  //cout<<"==.>> "<<_lepWIdx<<"  "<<_allLeps.size()<<endl;
  return true;
}

bool
TTVAnalysis::passGenSelection() {

  if(_sampleName=="TTHnobb_mWCutfix_ext") return true; //bypass
  //if(_sampleName.find("DY")!=string::npos || _sampleName.find("DY")!=string::npos
  //bypass
  //return true;
  // cout<<" -> "<<_vc->get(_leps[0].coll()+"_mcUCSXMatchId", _leps[0].idx())<<"   "
  //     <<" -> "<<_vc->get(_leps[1].coll()+"_mcUCSXMatchId", _leps[1].idx())<<"   "
  //     <<" -> "<<_vc->get(_leps[2].coll()+"_mcUCSXMatchId", _leps[2].idx())<<endl;
  if(_vc->get(_allLeps[0].coll()+"_mcUCSXMatchId", _allLeps[0].idx())!=0 ||
     _vc->get(_allLeps[0].coll()+"_mcMatchId", _allLeps[0].idx())==100) return false;
  if(_vc->get(_allLeps[1].coll()+"_mcUCSXMatchId", _allLeps[1].idx())!=0 ||
     _vc->get(_allLeps[1].coll()+"_mcMatchId", _allLeps[1].idx())==100) return false;
  if(_vc->get(_allLeps[2].coll()+"_mcUCSXMatchId", _allLeps[2].idx())!=0 ||
     _vc->get(_allLeps[2].coll()+"_mcMatchId", _allLeps[2].idx())==100) return false;
  return true;
}

bool
TTVAnalysis::passGenSelectionFast() {

  if(_sampleName=="TTHnobb_mWCutfix_ext") return true; //bypass
  //if(_sampleName.find("DY")!=string::npos || _sampleName.find("DY")!=string::npos
  //bypass
  //return true;
  // cout<<" -> "<<_vc->get(_leps[0].coll()+"_mcUCSXMatchId", _leps[0].idx())<<"   "
  //     <<" -> "<<_vc->get(_leps[1].coll()+"_mcUCSXMatchId", _leps[1].idx())<<"   "
  //     <<" -> "<<_vc->get(_leps[2].coll()+"_mcUCSXMatchId", _leps[2].idx())<<endl;
  if(_vc->get(_allLeps[_lepZIdx[0]].coll()+"_mcUCSXMatchId", _allLeps[_lepZIdx[0]].idx())!=0 ||
     _vc->get(_allLeps[_lepZIdx[0]].coll()+"_mcMatchId", _allLeps[_lepZIdx[0]].idx())==100) return false;
  if(_vc->get(_allLeps[_lepZIdx[1]].coll()+"_mcUCSXMatchId", _allLeps[_lepZIdx[1]].idx())!=0 ||
     _vc->get(_allLeps[_lepZIdx[1]].coll()+"_mcMatchId", _allLeps[_lepZIdx[1]].idx())==100) return false;
  if(_vc->get(_allLeps[_lepWIdx].coll()+"_mcUCSXMatchId", _allLeps[_lepWIdx].idx())!=0 ||
     _vc->get(_allLeps[_lepWIdx].coll()+"_mcMatchId", _allLeps[_lepWIdx].idx())==100) return false;
  return true;
}

bool
TTVAnalysis::genAcceptanceSelection(int targetGLep) {

  if(_sampleName=="TTHnobb_mWCutfix_ext") return true;
  
  int nGoodLep=0;
  size_t nLep=_vc->get("nLepGood");
  for(size_t il=0;il<nLep;il++) {
    if(_vc->get("LepGood_mcUCSXMatchId", il)<1 &&
       _vc->get("LepGood_mcMatchId", il)!=100) nGoodLep++;
  
  }
  if(nGoodLep==targetGLep) return true;
  return false;

}

void
TTVAnalysis::topSolver3Jplus(const CandWrapList& jets, const CandWrapList& bjets) {

  //cout<<" new event =========================== "<<jets.size()<<"   "<<bjets.size()<<endl;
  //pair the light jets
  CandList wCands;
  for(unsigned int ij1=0;ij1<jets.size()-1;ij1++) {
    for(unsigned int ij2=ij1+1;ij2<jets.size();ij2++) {

      //veto bjets
      // bool veto=false;
      // for(unsigned int ib=0;ib<bjets.size();ib++) {
      // 	if(jets[ij1].c()==bjets[ib].c() || jets[ij1].c()==bjets[ib].c() ) {
      // 	  veto=true;
      // 	  break;
      // 	}
      // }
      // if(veto) continue;

      wCands.push_back(Candidate::create(jets[ij1].c(),jets[ij2].c()));
      //cout<<ij1<<"  "<<ij2<<" --> "<<wCands.back()->mass()<<endl;
    }//ij2
  }//ij1

  //pair the W candidates and the b jets
 
  CandList topCands;
  for(unsigned int iw=0;iw<wCands.size();iw++) {
    for(unsigned int ib=0;ib<jets.size();ib++) {

      if(wCands[iw]->daughter(0)==jets[ib].c() || wCands[iw]->daughter(1)==jets[ib].c() )
	continue;
      
      topCands.push_back( Candidate::create(wCands[iw],jets[ib].c()) );
      // cout<<iw<<"  "<<ib<<"   "<<topCands.back()->mass()
      // 	  <<" <-> "<<topCands.back()->daughter(0)->mass()
      // 	  <<" <-> "<<topCands.back()->daughter(1)->pt()<<endl;
    } //bjets
  } //wcands

  
  
}


int
TTVAnalysis::getNNCategFall17Separated( float nnWZ, float nnTZq) {

  vector<float> binsWZ({-1,-0.9,-0.8,-0.7,0.7,0.8,0.9,1}); //7
  vector<float> binsTZq({-1,-0.9,-0.8,-0.7,0,0.5,0.7,0.8,0.9,1}); //9

  int binWZ=StatUtils::findBin<float>(nnWZ*2-1., binsWZ);
  int binTZq=StatUtils::findBin<float>(nnTZq*2-1, binsTZq);

  if(binWZ==0 && binTZq==0 ) return 1;
  else if(binWZ==0 && binTZq==1 ) return 2;
  else if(binWZ==0 && binTZq==2 ) return 3;
  else if(binWZ==0 && binTZq==3 ) return 4;
  else if(binWZ==0 && binTZq==4 ) return 5;
  else if(binWZ==0 && binTZq>=5 ) return 6;

  else if(binWZ==1 && binTZq==0 ) return 7;
  else if(binWZ==1 && binTZq==1 ) return 8;
  else if(binWZ==1 && binTZq==2 ) return 9;
  else if(binWZ==1 && binTZq==3 ) return 10;
  else if(binWZ==1 && binTZq==4 ) return 11;
  else if(binWZ==1 && binTZq>=5 ) return 12;

  else if(binWZ==2 && binTZq==0 ) return 13;
  else if(binWZ==2 && binTZq==1 ) return 14;
  else if(binWZ==2 && binTZq==2 ) return 15;
  else if(binWZ==2 && binTZq==3 ) return 16;
  else if(binWZ==2 && binTZq==4 ) return 17;
  else if(binWZ==2 && binTZq>=5 ) return 18;

  else if(binWZ==3 && binTZq<=2 ) return 19;
  else if(binWZ==3 && binTZq<=5 ) return 20;
  else if(binWZ==3 && binTZq<=8 ) return 21;
  
  else if(binWZ>=4 && binTZq<=2 ) return 22;
  else if(binWZ==4 && binTZq==3 ) return 23;
  else if(binWZ==5 && binTZq==3 ) return 24;
  else if(binWZ==6 && binTZq==3 ) return 25;

  else if(binWZ==4 && binTZq==4 ) return 26;
  else if(binWZ==5 && binTZq==4 ) return 27;
  else if(binWZ==6 && binTZq==4 ) return 28;

  else if(binWZ==4 && binTZq==5 ) return 29;
  else if(binWZ==5 && binTZq==5 ) return 30;
  else if(binWZ==6 && binTZq==5 ) return 31;

  else if(binWZ==4 && binTZq==6 ) return 32;
  else if(binWZ==5 && binTZq==6 ) return 33;
  else if(binWZ==6 && binTZq==6 ) return 34;
  
  else if(binWZ==4 && binTZq==7 ) return 35;
  else if(binWZ==5 && binTZq==7 ) return 36;
  else if(binWZ==6 && binTZq==7 ) return 37;
  
  else if(binWZ==4 && binTZq==8 ) return 38;
  else if(binWZ==5 && binTZq==8 ) return 39;
  else if(binWZ==6 && binTZq==8 ) return 40;
  
  else return -1;
}


int
TTVAnalysis::getNNCategFall17MultiClassifier( float nnWZ, float nnTZq) {

  vector<float> binsAbkg({-1,-0.9,-0.8,-0.7,0,0.7,0.8,0.9,1}); //8
  vector<float> binsTZq({-1,-0.9,-0.8,-0.6,0,0.6,0.8,0.9,1}); //8

  float AttZBkg=((1-2*nnWZ-2*nnTZq));
  float AtZqWZ=(nnTZq-nnWZ)/(nnTZq+nnWZ);
  
  int binBkg=StatUtils::findBin<float>(AttZBkg, binsAbkg);
  int binTZq=StatUtils::findBin<float>(AtZqWZ, binsTZq);

  if(binBkg==0 && binTZq==0) return 1;
  else if(binBkg==0 && binTZq==1) return 2;
  else if(binBkg==0 && binTZq==2) return 3;
  else if(binBkg==0 && binTZq<=4) return 4;
  else if(binBkg==0 && binTZq==5) return 5;
  else if(binBkg==0 && binTZq==6) return 6;
  else if(binBkg==0 && binTZq==7) return 7;

  else if(binBkg==1 && binTZq==0) return 8;
  else if(binBkg==1 && binTZq==1) return 9;
  else if(binBkg==1 && binTZq==2) return 10;
  else if(binBkg==1 && binTZq<=4) return 11;
  else if(binBkg==1 && binTZq==5) return 12;
  else if(binBkg==1 && binTZq==6) return 13;
  else if(binBkg==1 && binTZq==7) return 14;

  else if(binBkg==2 && binTZq==0) return 15;
  else if(binBkg==2 && binTZq==1) return 16;
  else if(binBkg==2 && binTZq<=5) return 17;
  else if(binBkg==2 && binTZq==6) return 18;
  else if(binBkg==2 && binTZq==7) return 19;

  else if(binBkg==3 && binTZq==5) return 20;
  else if(binBkg==4 && binTZq==5) return 21;
  else if( (binBkg<=7 && binTZq<=2) ||
      (binBkg<=5 && binTZq<=4) ) return 22;
  else if(binBkg<=5 && binTZq<=4) return 23;
  else if(binBkg<=5 && binTZq==3) return 24;
  else if(binBkg<=5 && binTZq==3) return 25;

  else if(binBkg==3 && binTZq==7) return 26;
  else if(binBkg==3 && binTZq==8) return 27;
  else if(binBkg==4 && binTZq==7) return 28;
  else if(binBkg==4 && binTZq==8) return 29;
  
  else if(binBkg<=7 && binTZq==2) return 30;
  else if(binBkg<=6 && binTZq==3) return 31;
  else if(binBkg==7 && binTZq==3) return 32;

  else if(binBkg==5 && binTZq==4) return 33;
  else if(binBkg==6 && binTZq==4) return 34;
  else if(binBkg==7 && binTZq==4) return 35;

  else if(binBkg==5 && binTZq==5) return 36;
  else if(binBkg==6 && binTZq==5) return 37;
  else if(binBkg==7 && binTZq==5) return 38;

  else if(binBkg==5 && binTZq<=6) return 39;
  else if(binBkg<=7 && binTZq<=7) return 40;

  else return -1;
}

int
TTVAnalysis::getNNCategV3( float nnWZ, float nnTZq, float nnTZW, float nnTTH) {

  vector<float> binsWZ({0,0.1,0.2,0.8,0.9,1}); //5
  vector<float> binsTZq({0,0.2,0.4,0.6,0.8,0.9,1}); //6
  vector<float> binsTTH({0,0.8,1}); //2
  vector<float> binsTZW({0,0.6,1}); //2

  int binWZ=StatUtils::findBin<float>(nnWZ, binsWZ);
  int binTZq=StatUtils::findBin<float>(nnTZq, binsTZq);
  int binTTH=StatUtils::findBin<float>(nnTTH, binsTTH);
  int binTZW=StatUtils::findBin<float>(nnTZW, binsTZW);
  //cout<<binWZ<<" <> "<<binTZq<<" <> "<<binTTH<<" <> "<<binTZW<<endl;

  if(binWZ==0 && binTZq==0 ) return 1;
  if(binWZ==0 && binTZq==1 ) return 2;
  if(binWZ==0 && binTZq==2 ) return 3;
  if(binWZ==0 && binTZq==3 ) return 4;
  if(binWZ==0 && binTZq==4 ) return 5;
  if(binWZ==0 && binTZq==5 ) return 6;
  
  if(binWZ==1 && binTZq==0 ) return 7;
  if(binWZ==1 && binTZq==1 ) return 8;
  if(binWZ==1 && binTZq==2 ) return 9;
  if(binWZ==1 && binTZq==3 ) return 10;
  if(binWZ==1 && binTZq==4 ) return 11;
  if(binWZ==1 && binTZq==5 ) return 12;
  
  if(binWZ==2 && binTZq==0 ) return 13;
  if(binWZ==2 && binTZq==1 ) return 14;
  if(binWZ==2 && binTZq==2 ) return 15;
  if(binWZ==2 && binTZq==3 ) return 16;
  if(binWZ==2 && binTZq==4 ) return 17;
  if(binWZ==2 && binTZq==5 ) return 18;
  
  if(binWZ==3 && binTZq==0 ) return 19;
  if(binWZ==3 && binTZq==1 ) return 20;
  if(binWZ==3 && binTZq==2 ) return 21;
  if(binWZ==3 && binTZq==3 ) return 22;
  if(binWZ==3 && binTZq==4 ) return 23;
  
  if(binWZ==4 && binTZq==0 ) return 24;
  if(binWZ==4 && binTZq==1 ) return 25;
  if(binWZ==4 && binTZq==2 ) return 26;
  
  // if(binWZ==3 && binTZq==3 && binTTH==0 && binTZW==0 ) return 25;
  // if(binWZ==3 && binTZq==3 && binTTH==0 && binTZW==1 ) return 26;
  // if(binWZ==3 && binTZq==3 && binTTH==1 && binTZW==0 ) return 27;
  // if(binWZ==3 && binTZq==3 && binTTH==1 && binTZW==1 ) return 28;

  // if(binWZ==3 && binTZq==4 && binTTH==0 && binTZW==0 ) return 29;
  // if(binWZ==3 && binTZq==4 && binTTH==0 && binTZW==1 ) return 30;
  // if(binWZ==3 && binTZq==4 && binTTH==1 && binTZW==0 ) return 31;
  // if(binWZ==3 && binTZq==4 && binTTH==1 && binTZW==1 ) return 32;

  // if(binWZ==3 && binTZq==3 && binTTH==0 ) return 25;
  // if(binWZ==3 && binTZq==3 && binTTH==1 ) return 26;
  // if(binWZ==3 && binTZq==4 && binTTH==0 ) return 27;
  // if(binWZ==3 && binTZq==4 && binTTH==1 ) return 28;

 
  

  // if(binWZ==3 && binTZq==5 && binTTH==0 && binTZW==0 ) return 29;
  // if(binWZ==3 && binTZq==5 && binTTH==0 && binTZW==1 ) return 30;
  // if(binWZ==3 && binTZq==5 && binTTH==1 && binTZW==0 ) return 31;
  // if(binWZ==3 && binTZq==5 && binTTH==1 && binTZW==1 ) return 32;

  if(binWZ==3 && binTZq==5 && binTZW==0 ) return 27;
  if(binWZ==3 && binTZq==5 && binTZW==1 ) return 28;

  
  if(binWZ==4 && binTZq==3 && binTTH==0 && binTZW==0 ) return 29;
  if(binWZ==4 && binTZq==3 && binTTH==0 && binTZW==1 ) return 30;
  if(binWZ==4 && binTZq==3 && binTTH==1 && binTZW==0 ) return 31;
  if(binWZ==4 && binTZq==3 && binTTH==1 && binTZW==1 ) return 32;

  // if(binWZ==4 && binTZq==4 && binTTH==0 && binTZW==0 ) return 37;
  // if(binWZ==4 && binTZq==4 && binTTH==0 && binTZW==1 ) return 38;
  // if(binWZ==4 && binTZq==4 && binTTH==1 && binTZW==0 ) return 39;
  // if(binWZ==4 && binTZq==4 && binTTH==1 && binTZW==1 ) return 40;

  if(binWZ==4 && binTZq==4 && binTZW==0 ) return 33;
  if(binWZ==4 && binTZq==4 && binTZW==1 ) return 34;

  if(binWZ==4 && binTZq==5 && binTTH==0 && binTZW==0 ) return 35;
  if(binWZ==4 && binTZq==5 && binTTH==0 && binTZW==1 ) return 36;
  if(binWZ==4 && binTZq==5 && binTTH==1 && binTZW==0 ) return 37;
  if(binWZ==4 && binTZq==5 && binTTH==1 && binTZW==1 ) return 38;

  return -1;
  
}

int
TTVAnalysis::getNNCategV2( float nnWZ, float nnTZq, float nnTZW, float nnTTH, int opt) {

  int offsetC1=3;
  int offsetC2=1;
  int offsetC3=0;
  int offsetC4=2;
  int k1=(opt&1);
  int k2=(opt&2);
  int k4=(opt&4);
  int k8=(opt&8);
  if(k1!=0) { //cadran 1 included
    
  }
  if(k2!=0) { //cadran 2 included
    offsetC1 += 4-1;
    offsetC4 += 4-1;
  }
  if(k4!=0) { //cadran 3 included
    offsetC1 += 7-1;
    offsetC2 += 7-1;
    offsetC4 += 7-1;
  }
  if(k8!=0) { //cadran 4 included
    offsetC1 += 3-1;
  }
  

  
  if(nnWZ>0.95 && nnTZq>0.50) { //quadran 1
    if(k1!=0) {
      if(nnTTH<0.3 || ( nnTTH<0.4 && nnTZW>0.4) ) return 1+offsetC1;
      else if(nnTTH<0.6 && nnTZW<0.4) return 2+offsetC1;
      else if(nnTTH<0.6 && nnTZW<0.6) return 3+offsetC1;
      else if(nnTTH<0.6 && nnTZW<0.8) return 4+offsetC1;
      else if(nnTTH<0.6             ) return 5+offsetC1;
      else if(nnTTH<0.7 && nnTZW<0.5) return 6+offsetC1;
      else if(nnTTH<0.7 && nnTZW<0.6) return 7+offsetC1;
      else if(nnTTH<0.7 && nnTZW<0.7) return 8+offsetC1;
      else if(nnTTH<0.7 && nnTZW<0.8) return 9+offsetC1;
      else if(nnTTH<0.7             ) return 10+offsetC1;
      else if(nnTTH<0.8 && nnTZW<0.4) return 11+offsetC1;
      else if(nnTTH<0.8 && nnTZW<0.5) return 12+offsetC1;
      else if(nnTTH<0.8 && nnTZW<0.6) return 13+offsetC1;
      else if(nnTTH<0.8 && nnTZW<0.7) return 14+offsetC1;
      else if(nnTTH<0.8 && nnTZW<0.8) return 15+offsetC1;
      else if(nnTTH<0.8             ) return 16+offsetC1;
      else if(nnTTH<0.9 && nnTZW<0.4) return 17+offsetC1;
      else if(nnTTH<0.9 && nnTZW<0.5) return 18+offsetC1;
      else if(nnTTH<0.9 && nnTZW<0.6) return 19+offsetC1;
      else if(nnTTH<0.9 && nnTZW<0.7) return 20+offsetC1;
      else if(nnTTH<0.9 && nnTZW<0.8) return 21+offsetC1;
      else if(nnTTH<0.9             ) return 22+offsetC1;
      else if(             nnTZW<0.4) return 23+offsetC1;
      else if(             nnTZW<0.5) return 24+offsetC1;
      else if(             nnTZW<0.6) return 25+offsetC1;
      else if(             nnTZW<0.7) return 26+offsetC1;
      else if(             nnTZW<0.8) return 27+offsetC1;
      else                            return 28+offsetC1;
    } else {
      int k=(opt&16);
      if(k!=0) {
	return 1+offsetC1;
      } else {
	if(nnWZ>0.95 && nnTZq<0.60) return 1+offsetC1;
	else if(nnWZ>0.95 && nnTZq<0.70) return 2+offsetC1;
	else if(nnWZ>0.95 && nnTZq<0.80) return 3+offsetC1;
	else if(nnWZ>0.95 && nnTZq<0.90) return 4+offsetC1;
	else return 5+offsetC1;

      }
    }
    
    
  }
  else if(nnWZ>0.95 && nnTZq<=0.50) { //quadran 2
    if(k2!=0) {
      if(nnTZq<0.1) return 1+offsetC2;
      else if(nnTZq<0.2) return 2+offsetC2;
      else if(nnTZq<0.3) return 3+offsetC2;
      else {return 4+offsetC2;}
    } else {
      return 1+offsetC2;
    }

  }
  else if(nnWZ<=0.95 && nnTZq<=0.50) { //quadran 3
    if(k4!=0) {
      if(     nnWZ<0.2) return 1+offsetC3;
      else if(nnWZ<0.4) return 2+offsetC3;
      else if(nnWZ<0.7) return 3+offsetC3;
      else if(nnTZq<0.1) return 4+offsetC3;
      else if(nnTZq<0.2 && nnWZ>0.8) return 5+offsetC3;
      else if(nnTZq<0.3 && nnWZ>0.8) return 6+offsetC3;
      else  return 7+offsetC3;
    } else {
      return 1+offsetC3;
    }
    
  }
  else if(nnWZ<=0.95 && nnTZq>0.50) { //quadran 4
    if(k8!=0) {
      if(nnWZ<0.7 || nnTZq<0.9) return 1+offsetC4;
      else if(nnWZ<0.8        ) return 2+offsetC4;
      else return 3+offsetC4;
    } else {
      return 1+offsetC4;
    }
      
  }
  
  return -1;
}

int
TTVAnalysis::getNNCateg( float nnWz, float nnTZq, float nnTZW, float nnTTH) {

  int categ=-1;

  //bypass
  return std::min(9,(int)(10*nnWz))+10*std::min(9,(int)(10*nnTZq));
  switch(_nnScheme) {
  case kVsWZ: {
    categ=(int)(nnWz*100);
    break;
  }
  case kVsTZq: {
    categ=(int)(nnTZq*100);
    break;
  }
  case kVsTZW: {
    categ=(int)(nnTZW*100);
    break;
  }
  case kVsTTH: {
    categ=(int)(nnTTH*100);
    break;
  }
  case kVsWZandTZq: {
    categ=std::min(9,(int)(10*nnWz))+10*std::min(9,(int)(10*nnTZq));
    break;
  }
  case kVsWZandTZW: {
    categ=std::min(9,(int)(10*nnWz))+10*std::min(9,(int)(10*nnTZW));
    break;
  }
  case kVsWZandTTH: {
    categ=std::min(9,(int)(10*nnWz))+10*std::min(9,(int)(10*nnTTH));
    break;
  }
  case kVsWZandTZqandTZWandTTH: {
    //categ=std::min(1,(int)(2*nnWz))+2*std::min(1,(int)(2*nnTZq))+2*2*std::min(4,(int)(5*nnTZW))+2*2*5*std::min(4,(int)(5*std::max((float)0.2,nnTTH)));
    categ=std::min(4,(int)(5*(std::max(0.,nnTTH-0.2)/0.8)))+5*std::min(4,(int)(5*nnTZW))+5*5*std::min(1,(int)(2*nnTZq))+5*5*2*std::min(1,(int)(2*nnWz));
    break;
  }   

  }

  //cout<<nnWz<<" / "<<nnTZq<<" / "<<nnTZW<<" / "<<nnTTH<<" --> "<<categ<<endl;

  return categ;

}




int
TTVAnalysis::u(int x, int N) {
  
  if(x==0) return 0;
  else {
    return u(x-1,N)+N-(x-1);
  }
}

int
TTVAnalysis::u2(int x, int N) {
  
  if(x==0 || N==0) return 0;
  else {
    return u2(x-1,N)+u(N-x+1,N-x+1); 
  }
  
}


int
TTVAnalysis::nnMultiBin(float valTTZ, float valWZ, float valTZq, int N) {

  // N-=1;
  int k=(int)(std::min((float)0.999999,valTTZ)*N);
  int j=(int)(std::min((float)0.999999,valWZ)*N);
  int i=(int)(std::min((float)0.999999,valTZq)*N);

  // if(valTTZ<0.05)
  //   cout<<setprecision(3)<<valTTZ<<" / "<<k<<"   "
  // 	<<valWZ<<" / "<<j<<"   "
  // 	<<valTZq<<" / "<<i<<" -->>>  "
  // 	<<(k + u(j,N) + u2(i,N))<<endl;
    
  return k + u(j,N) + u2(i,N);
}

void
TTVAnalysis::dumpEvents() {

  int run=_vc->get("run");
  int lumi=_vc->get("lumi");
  unsigned long event=_vc->get("evt");
  
  *_ofileDump << Form("%1d %d %d", run, lumi, event)<<endl;
  // for(unsigned int il=0;il<_leps.size();il++) {
  //   cout<<_vc->get("LepGood_jetNDauChargedMVASel",_leps[il].idx())<<endl;
    
  //   *_ofileDump << Form("%1d %9d %12d\t%5.1f %5.1f\t%1d %1.5f %1.5f\t%5.1f %1.3f %1.3f\t%2.3f %1.3f %1.3f\t%1.3f",
  // 		       run,
  // 		       lumi,
  // 		       event,
  // 		       _vc->get("LepGood_pt",_leps[il].idx()),
  // 		       _vc->get("LepGood_eta",_leps[il].idx()),
  // 			(int)_vc->get("LepGood_jetNDauChargedMVASel",_leps[il].idx()),
  // 			(float)_vc->get("LepGood_miniRelIsoCharged",_leps[il].idx()),
  // 			(float)_vc->get("LepGood_miniRelIsoNeutral",_leps[il].idx()),
  // 			(float)_vc->get("LepGood_jetPtRelv2",_leps[il].idx()),
  // 			(float)_vc->get("LepGood_jetPtRatiov2",_leps[il].idx()),
  // 			(float)_vc->get("LepGood_jetBTagCSV",_leps[il].idx()),
  // 			(float)_vc->get("LepGood_sip3d",_leps[il].idx()),
  // 			(TMath::Log(std::abs(_vc->get("LepGood_dxy",_leps[il].idx())))),
  // 			(TMath::Log(std::abs(_vc->get("LepGood_dz",_leps[il].idx())))),
  // 			(float)((std::abs(_vc->get("LepGood_pdgId",_leps[il].idx()))==11)?_vc->get("LepGood_mvaIdSpring16HZZ",_leps[il].idx()):_vc->get("LepGood_segmentCompatibility",_leps[il].idx())) ) <<endl;
  // 		       //int(LepGood_jetNDauChargedMVASel), LepGood_miniRelIsoCharged, LepGood_miniRelIsoNeutral, LepGood_jetPtRelv2, LepGood_jetPtRatio, LepGood_jetBTagCSV, LepGood_sip3d, LepGood_dxy, LepGood_dz, LepGood_mvaIdSpring15/LepGood_segmentCompatibility) << endl;
  // }

}



//==================================================================
//
//
//==================================================================

bool
TTVAnalysis::looseId(const Candidate* c, int idx, const string& branch) {
  if(_id=="TTH") {
    if(std::abs(c->pdgId() )==11) return elIdSelTTHLoose(c,idx, branch);
    else return muIdSelTTHLoose(c,idx, branch);
  } else {
    if(std::abs(c->pdgId() )==11) return elIdSelTTZLoose(c,idx, branch);
    else return muIdSelTTZLoose(c,idx, branch);
  }
}

bool
TTVAnalysis::fakableId(const Candidate* c, int idx, const string& branch) {
  if(_id=="TTH") {
    if(std::abs(c->pdgId() )==11) return elIdSelTTHFakable(c,idx, branch);
    else return muIdSelTTHFakable(c,idx, branch);
  } else {
    if(std::abs(c->pdgId() )==11) return elIdSelTTZFakable(c,idx, branch);
    else return muIdSelTTZFakable(c,idx, branch);
  }
}

bool
TTVAnalysis::tightId(const Candidate* c, int idx, const string& branch) {

  if(_id=="TTH") {
    if(std::abs(c->pdgId() )==11) return elIdSelTTHTight(c,idx, branch);
    else return muIdSelTTHTight(c,idx, branch);
  } else {
    if(std::abs(c->pdgId() )==11) return elIdSelTTZTight(c,idx, branch);
    else return muIdSelTTZTight(c,idx, branch);
  }
}


bool
TTVAnalysis::looseTTVLepton(int idx, const string& branch) {
  if(std::abs(_vc->get("LepGood_pdgId",idx))==11) {
    if(std::abs(_vc->get("LepGood_eta",idx))>2.5) return false;
    if(_vc->get("LepGood_pt",idx)<=10) return false;
    if(std::abs(_vc->get("LepGood_dz",idx))>=0.1) return false;
    if(std::abs(_vc->get("LepGood_dxy",idx))>=0.05) return false;
    if(_vc->get("LepGood_sip3d",idx)>=4) return false;
    if(_vc->get("LepGood_relIso03",idx)>=1) return false;
    //if(_vc->get("LepGood_mvaIdFall17noIso",idx) <(-0.76+(0.76-0.52)*(std::abs(_vc->get("LepGood_eta",idx))>0.8 && std::abs(_vc->get("LepGood_eta",idx))<1.479)+(0.76-0.23)*(std::abs(_vc->get("LepGood_eta",idx))>1.479)  )) return false;
    //if(! elMvaIDFall17(
    cout<<"check that function looseTTVLepton (not up to date)"<<endl;
    abort();
    if(! HLTEmul(idx, branch)) return false;
  }
  if(std::abs(_vc->get("LepGood_pdgId",idx))==13) {
    if(std::abs(_vc->get("LepGood_eta",idx))>2.4) return false;
    if(_vc->get("LepGood_pt",idx)<=10) return false;
    if(std::abs(_vc->get("LepGood_dz",idx))>=0.1) return false;
    if(std::abs(_vc->get("LepGood_dxy",idx))>=0.05) return false;
    if(_vc->get("LepGood_sip3d",idx)>=4) return false;
    if(_vc->get("LepGood_relIso03",idx)>=0.7) return false;
    if(_vc->get("LepGood_mediumMuonID2016",idx)==0) return false;
    return true;
  }

  return false;
}



bool TTVAnalysis::HLTEmul(int idx, const string& branch) {
  if (std::abs(_vc->get(branch+"_pdgId",idx))!=11) return true;
  bool scEndcap=std::abs(_vc->get(branch + "_etaSc", idx))>1.479;
  if (_vc->get(branch+"_hadronicOverEm",idx)>=(0.10-0.03*scEndcap)) return false;
  if (std::abs(_vc->get(branch+"_dEtaScTrkIn",idx))>=(0.01-0.002*scEndcap)) return false;
  if (std::abs(_vc->get(branch+"_dPhiScTrkIn",idx))>=(0.04+0.03*scEndcap)) return false;
  if (_vc->get(branch+"_eInvMinusPInv",idx)<=-0.05) return false;
  if (_vc->get(branch+"_eInvMinusPInv",idx)>=(0.01-0.005*scEndcap)) return false;
  if (_vc->get(branch+"_sigmaIEtaIEta",idx)>=(0.011+0.019*scEndcap)) return false;
  return true;
}
 




bool
TTVAnalysis::muIdSelTTHLoose(const Candidate* c, int idx, const string& branch) {

  if(std::abs(c->eta()) > 2.4 ) return false; //cout<<" bli 1 "<<endl;
  if(c->pt() < 5 ) return false;  //cout<<" bli 2 "<<endl;

  if(std::abs(_vc->get(branch+"_dz",idx))>=0.1) return false; //cout<<" bli 3 "<<endl;
  if(std::abs(_vc->get(branch+"_dxy",idx))>=0.05) return false; //cout<<" bli 4 "<<endl;
  if(_vc->get(branch+"_sip3d",idx)>=8) return false; //cout<<" bli 5 "<<endl;
  if(_vc->get(branch+"_miniRelIso",idx)>=0.4) return false; //cout<<" bli 6 "<<endl;
  if(_vc->get(branch+"_looseIdOnly",idx)==0) return false; //cout<<" bli 7 "<<endl;

  if(_valid) {
    if(_vc->get("LepGood_mcUCSXMatchId",idx)<=1) setWorkflow(kGlobal);
    else setWorkflow(kGlobalFake);
    if(c->pt()>=10) {
      if(c->pt() <25) fill("muMvaTTHEndcap",_vc->get("LepGood_mvaTTH",idx));
      else fill("muMvaTTHBarrel",_vc->get("LepGood_mvaTTH",idx));
    }
    setWorkflow(kGlobal);
  }
  return true;
}



bool
TTVAnalysis::muIdSelTTZLoose(const Candidate* c, int idx, const string& branch) {

  if(std::abs(c->eta()) > 2.4 ) return false; //cout<<" bli 1 "<<endl;
  if(c->pt() < 5 ) return false;  //cout<<" bli 2 "<<endl;

  if(std::abs(_vc->get(branch+"_dz",idx))>=0.1) return false; //cout<<" bli 3 "<<endl;
  if(std::abs(_vc->get(branch+"_dxy",idx))>=0.05) return false; //cout<<" bli 4 "<<endl;
  if(_vc->get(branch+"_sip3d",idx)>=8) return false; //cout<<" bli 5 "<<endl;
  if(_vc->get(branch+"_miniRelIso",idx)>=0.4) return false; //cout<<" bli 6 "<<endl;
  if(_vc->get(branch+"_looseIdOnly",idx)==0) return false; //cout<<" bli 7 "<<endl;
  
  return true;
}




bool
TTVAnalysis::elIdSelTTHLoose(const Candidate* c, int idx, const string& branch) {

  if(std::abs(_vc->get(branch+"_etaSc",idx)) > 2.5 ) return false; 
  if(c->pt() < 7 ) return false;

  if(std::abs(_vc->get(branch+"_dz",idx))>=0.1) return false;
  if(std::abs(_vc->get(branch+"_dxy",idx))>=0.05) return false;
  if(_vc->get(branch+"_sip3d",idx)>=8) return false;
  if(_vc->get(branch+"_miniRelIso",idx)>=0.4) return false;
  if(_vc->get(branch+"_looseIdOnly",idx)==0) return false;
  
  // if(std::abs(c->eta())<0.8) {
  //   if(_vc->get("LepGood_mvaIdSpring16HZZ",idx) <0.856871961305474) return false; }
  // else if(std::abs(c->eta())<1.479) {
  //   if(_vc->get("LepGood_mvaIdSpring16HZZ",idx) <0.8107642141584835) return false; }
  // else {
  //   if(_vc->get("LepGood_mvaIdSpring16HZZ",idx) <0.7) return false; }
  if(! elMvaIdFall17(c,idx, SusyModule::kLoose) ) return false;

  if(_vc->get(branch + "_lostHits" , idx) >=2 ) return false;

  
  if(_valid) {
    if(_vc->get("LepGood_mcUCSXMatchId",idx)<=1) setWorkflow(kGlobal);
    else setWorkflow(kGlobalFake);
    if(c->pt()>=10) {
      if(c->pt() < 25)  fill("elMvaTTHEndcap",_vc->get("LepGood_mvaTTH"));
      else fill("elMvaTTHBarrel",_vc->get("LepGood_mvaTTH"));
    }
    setWorkflow(kGlobal);
  }
  
  return true;
  
}




bool
TTVAnalysis::elIdSelTTZLoose(const Candidate* c, int idx, const string& branch) {
  
  if(std::abs(c->eta()) > 2.5 ) return false; 
  if(c->pt() < 7 ) return false;
  
  if(std::abs(_vc->get(branch+"_dz",idx))>=0.1) return false;
  if(std::abs(_vc->get(branch+"_dxy",idx))>=0.05) return false;
  if(_vc->get(branch+"_sip3d",idx)>=8) return false;
  if(_vc->get(branch+"_miniRelIso",idx)>=0.4) return false;
  if(_vc->get(branch+"_looseIdOnly",idx)==0) return false;
  
  // if(std::abs(c->eta())<0.8) {
  //   if(_vc->get("LepGood_mvaIdFall17noIso",idx) <0.5) return false; }
  // else if(std::abs(c->eta())<1.479) {
  //   if(_vc->get("LepGood_mvaIdFall17noIso",idx) <0.5) return false; }
  // else {
  //   if(_vc->get("LepGood_mvaIdFall17noIso",idx) <0.357) return false; }
  if(! elMvaIdFall17(c,idx, SusyModule::kLoose) ) return false;
  
  ////cout<<" bli3 "<<endl;
  if(_vc->get(branch + "_lostHits" , idx) >=2 ) return false;
  ////cout<<" bli4 "<<endl;
  return true;

  
}



bool
TTVAnalysis::muIdSelTTHFakable(const Candidate* c, int idx, const string& branch) {

  //cout<<"lepton "<<c->pt()<<"  "<<c->eta()<<" mu "<<endl;
  if(!muIdSelTTHLoose(c,idx,branch) ) return false;
  //cout<<" passing loose id "<<endl;
  if(_vc->get(branch + "_jetBTagCSV",idx)  > 0.8484 ) return false;

  bool id1=_vc->get(branch + "_mvaTTH",idx)>0.75;
  bool id2= (_vc->get(branch + "_jetPtRatiov2",idx)>0.5 && _vc->get(branch + "_jetBTagCSV",idx)<0.3 && _vc->get(branch+ "_segmentCompatibility",idx)>0.3);
  //cout<<" -->> "<<_vc->get(branch+ "_segmentCompatibility",idx)<<"  "<<_vc->get(branch + "_mvaTTH",idx)<<"   "<<_vc->get(branch + "_jetPtRatiov2",idx)<<endl;
  //cout<<"id1 "<<id1<<" // "<<_vc->get(branch + "_mvaTTH",idx)<<"    "<<_vc->get(branch+"_mediumMuonID2016", idx)<<endl;
  //cout<<"id2 "<<id2<<"   "<<(_vc->get(branch + "_jetPtRatiov2",idx)>0.5)<<"  "<<(_vc->get(branch + "_jetBTagCSV",idx)<0.3)<<"   "<<(_vc->get(branch+ "_segmentCompatibility",idx)>0.3)<<endl;
  
  if(!(id1 || id2) ) return false;
  //cout<<" pass ID"<<endl;
  return true;
}

bool
TTVAnalysis::elIdSelTTHFakable(const Candidate* c, int idx, const string& branch) {
  ////cout<<"lepton === "<<c->pt()<<"  "<<c->eta()<<" el "<<endl;

  //fixme ?
  if(!elIdSelTTHLoose(c,idx,branch) ) return false;
  
  if(_vc->get(branch + "_jetBTagCSV",idx) > 0.8484 ) return false;

  //bool barrel=std::abs(c->eta())<1.479;
  bool id1=_vc->get(branch + "_mvaTTH",idx)>0.75;
  bool id2= (_vc->get(branch + "_jetPtRatiov2",idx)>0.5 && _vc->get(branch + "_jetBTagCSV",idx)<0.3);// && _vc->get(branch+ "_mvaIdSpring16HZZ",idx)>(barrel?0.:0.7));

  ////cout<<"id1 "<<id1<<" <> "<<_vc->get(branch + "_mvaTTH",idx)<<endl;
  ////cout<<"id2 "<<id2<<"   "<<(_vc->get(branch + "_jetPtRatiov2",idx)>0.5)<<"   "<<(_vc->get(branch + "_jetBTagCSV",idx)<0.3)<<"   "<<(_vc->get(branch+ "_mvaIdSpring16HZZ",idx)>(barrel?0.:0.7))<<endl;
  
  if(!(id1 || id2) ) return false;

  ////cout<<" pass id "<<endl;
  if(!HLTEmul(idx, branch) ) return false;
  ////cout<<" pass emul "<<endl;
	     
  if(_vc->get(branch + "_lostHits" , idx) !=0 ) return false;
  
  ////cout<<" pass ID"<<endl;
  return true;
}


bool 
TTVAnalysis::muIdSelTTHTight(const Candidate* c, int idx, const string& branch ) {
  // (abs(lep.pdgId)!=13 or lep.mediumMuonId>0) and lep.mvaTTH > 0.90,
  //return lep.conept>10 and lep.jetBTagCSV<0.8484 and (abs(lep.pdgId)!=11 or _ttH_idEmu_cuts_E2(lep)) 
  //and (lep.mvaTTH>0.90 or (lep.jetPtRatiov2>0.5 and lep.jetBTagCSV<0.3 and (abs(lep.pdgId)!=13 or lep.segmentCompatibility>0.3)
  //and (abs(lep.pdgId)!=11 or lep.mvaIdSpring16HZZ > (0.0 if abs(lep.eta)<1.479 else 0.7)) ) )

  if(std::abs(c->eta())                    > 2.4  ) return false;
  if(_vc->get(branch+"_mediumMuonID2016", idx) == 0   ) return false;
  if(_vc->get(branch + "_mvaTTH",idx)      <  0.75 ) return false;
  if(_vc->get(branch + "_tightCharge",idx)     <  2 ) return false;
  if(!muIdSelTTHFakable(c,idx,branch) ) return false;
  
  return true;
}


bool 
TTVAnalysis::elIdSelTTHTight(const Candidate* c, int idx, const string& branch ) {
  // (abs(lep.pdgId)!=13 or lep.mediumMuonId>0) and lep.mvaTTH > 0.90,
  //return lep.conept>10 and lep.jetBTagCSV<0.8484 and (abs(lep.pdgId)!=11 or _ttH_idEmu_cuts_E2(lep)) 
  //and (lep.mvaTTH>0.90 or (lep.jetPtRatiov2>0.5 and lep.jetBTagCSV<0.3 and (abs(lep.pdgId)!=13 or lep.segmentCompatibility>0.3)
  //and (abs(lep.pdgId)!=11 or lep.mvaIdSpring16HZZ > (0.0 if abs(lep.eta)<1.479 else 0.7)) ) )
  ////cout<<" youlou1 "<<endl;
  if(std::abs(_vc->get(branch+"_etaSc",idx)) > 2.5 ) return false;
  if(_vc->get(branch + "_convVeto" , idx) !=1 ) return false;
  ////cout<<" youlou2 "<<c->pt()<<"  "<<_vc->get(branch + "_mvaTTH",idx)<<endl;
  if(_vc->get(branch + "_mvaTTH",idx) < 0.75 ) return false;
  ////cout<<" youlou3 "<<endl;
  if(!elIdSelTTHFakable(c,idx,branch) ) return false;
  
  return true;
}


float
TTVAnalysis::conePt(const Candidate* c, int idx, const string& branch) {
  //if (abs(lep.pdgId)!=11 and abs(lep.pdgId)!=13): return lep.pt
  //if (abs(lep.pdgId)!=13 or lep.mediumMuonId>0) and lep.mvaTTH > 0.90: return lep.pt
  //  else: return 0.90 * lep.pt / lep.jetPtRatiov2
  ////cout<<" ========= "<<c->pt()<<"  "<<_vc->get(branch+"_jetPtRatiov2")<<endl;
  if(std::abs(c->pdgId())!=11 && std::abs(c->pdgId())!=13) return c->pt();
  if( (std::abs(c->pdgId())!=13 || _vc->get(branch+"_mediumMuonID2016",idx)>0) &&
      _vc->get(branch+"_mvaTTH",idx)>0.75) return c->pt();
  else return 0.750*c->pt()/_vc->get(branch+"_jetPtRatiov2",idx);
}

float
TTVAnalysis::conePtIllia(float lpt, float leta, int flavor, float isolation) {
  float ptf = lpt;
  vector<float> stiso({0.0994, 0.107});
  ptf = lpt * (1 + TMath::Max(0.,isolation - (flavor ? 0.25 : stiso[std::abs(leta) > 1.479])));
  return ptf;
}



bool
TTVAnalysis::elIdSelTTZFakable(const Candidate*c, int idx, const string& branch) {

  //if(!HLTEmul(idx, branch) ) return false;

  if(std::abs(c->eta()) > 2.5 ) return false; 
  if(c->pt() < 10 ) return false;
  ////cout<<" bli "<<endl;
  if(std::abs(_vc->get(branch+"_dz",idx))>=0.1) return false;
  if(std::abs(_vc->get(branch+"_dxy",idx))>=0.05) return false;
  if(_vc->get(branch+"_sip3d",idx)>=4) return false;
  //cout<<"relIso "<<_vc->get(branch+"_relIso03",idx)<<"  "<<_vc->get(branch+"_relIso04",idx)<<endl;
  if(_vc->get(branch+"_relIso03",idx)>=0.7) return false;

  float valC=0.5;
  if(std::abs(c->eta())> 1.479) valC=0.357;
  else if(std::abs(c->eta())>0.8) valC=0.5;
  //cout<<" ====== "<<c->pt()<<"  "<<_vc->get("LepGood_mvaIdSpring16GP",idx)<<endl;
  if(_vc->get("LepGood_mvaIdFall17noIso",idx)<valC) return false;

  if(!HLTEmul(idx, branch) ) return false;
  
  return true;

}


bool
TTVAnalysis::muIdSelTTZFakable(const Candidate*c, int idx, const string& branch) {

  if(std::abs(c->eta()) > 2.4 ) return false; 
  if(c->pt() < 10 ) return false;
  if(std::abs(_vc->get(branch+"_dz",idx))>=0.1) return false;
  if(std::abs(_vc->get(branch+"_dxy",idx))>=0.05) return false;
  if(_vc->get(branch+"_sip3d",idx)>=4) return false;
  //cout<<"relIso "<<_vc->get(branch+"_relIso03",idx)<<"  "<<_vc->get(branch+"_relIso04",idx)<<endl;
  if(_vc->get(branch+"_relIso04",idx)>=0.7) return false;
  
  if(_vc->get("LepGood_mediumMuonID2016",idx)!=1) return false;
	  
  return true;
  
}


bool
TTVAnalysis::elIdSelTTZTight(const Candidate*c, int idx, const string& branch) {

  if(!elIdSelTTZFakable(c,idx, branch)) return false;

  bool barrel=std::abs(c->eta())<1.5;
  if(_vc->get(branch+"_relIso03",idx)>=((barrel)?0.0994:0.107) ) return false;

  return true;  
}


bool
TTVAnalysis::muIdSelTTZTight(const Candidate*c, int idx, const string& branch) {

  if(!muIdSelTTZFakable(c,idx, branch)) return false;

  if(_vc->get(branch+"_relIso04",idx)>=0.25) return false;

  return true;
  
}


bool
TTVAnalysis::elMvaIdFall17(const Candidate*c, int idx, int wp) {

  if(wp==SusyModule::kLoose) {
    if(c->pt()<=10) {
      if(std::abs(c->eta())<0.8)
	return _vc->get("LepGood_mvaIdFall17noIso",idx)>-0.13285867293779202;
      else if(std::abs(c->eta())<1.479)
	return _vc->get("LepGood_mvaIdFall17noIso",idx)>-0.31765300958836074;
      else
	return _vc->get("LepGood_mvaIdFall17noIso",idx)>-0.0799205914718861;
    } else {
      if(std::abs(c->eta())<0.8)
	return _vc->get("LepGood_mvaIdFall17noIso",idx)>-0.856871961305474;
      else if(std::abs(c->eta())<1.479)
	return _vc->get("LepGood_mvaIdFall17noIso",idx)>-0.8107642141584835;
      else
	return _vc->get("LepGood_mvaIdFall17noIso",idx)>-0.7179265933023059;
    }
  }
  else if (wp==SusyModule::kMedium) { //wp 90 %
    float C=0;
    float tau=0;
    float A=0;
    if(c->pt()<=10 && std::abs(c->eta())<0.8) {
      C = 0.9165112826974601;
      tau = 2.7381703555094217;
      A = 1.03549199648109;
    }
    else if(c->pt()>10 && std::abs(c->eta())<0.8) {
      C = 0.9616542816132922;
      tau = 8.757943837889817;
      A = 3.1390200321591206;
    }
    else if(c->pt()<=10 && std::abs(c->eta())<1.479) {
      C = 0.8655738322220173;
      tau = 2.4027944652597073;
      A = 0.7975615613282494;
    }
    else if(c->pt()>10 && std::abs(c->eta())<1.479) {
      C = 0.9319258011430132;
      tau = 8.846057432565809;
      A = 3.5985063793347787;
    }
    else if(c->pt()<=10) {
      C = -3016.035055227131;
      tau = -52140.61856333602;
      A = -3016.3029387236506;
    }
    else if(c->pt()>10) {
      C = 0.8899260780999244;
      tau = 10.124234115859881;
      A = 4.352791250718547;
    }
    return _vc->get("LepGood_mvaIdFall17noIso",idx)> C-A*exp(-c->pt()/tau);
  }
  else if (wp==SusyModule::kTight) { //wp 80 %
    float C=0;
    float tau=0;
    float A=0;
    if(c->pt()<=10 && std::abs(c->eta())<0.8) {
      C = 0.9530240956555949;
      tau = 2.7591425841003647;
      A = 0.4669644718545271;
    }
    else if(c->pt()>10 && std::abs(c->eta())<0.8) {
      C = 0.9825268564943458;
      tau = 8.702601455860762;
      A = 1.1974861596609097;
    }
    else if(c->pt()<=10 && std::abs(c->eta())<1.479) {
      C = 0.9336564763961019;
      tau = 2.709276284272272;
      A = 0.33512286599215946;
    }
    else if(c->pt()>10 && std::abs(c->eta())<1.479) {
      C = 0.9727509457929913;
      tau = 8.179525631018565;
      A = 1.7111755094657688;
    }
    else if(c->pt()<=10) {
      C = 0.9313133688365339;
      tau = 1.5821934800715558;
      A = 3.8889462619659265;
    }
    else if(c->pt()>10) {
      C = 0.9562619539540145;
      tau = 8.109845366281608;
      A = 3.013927699126942;
    }
    return _vc->get("LepGood_mvaIdFall17noIso",idx)> C-A*exp(-c->pt()/tau);
  }

  return false;
}


bool
TTVAnalysis::passTriggerLine() {
  for(size_t i=0;i<_trgLines.size();i++) {
    if(_vc->get(_trgLines[i])) return true;
  }
  return false;
}
