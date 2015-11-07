#include "analysis/src/SSDL2015.hh"

#include <algorithm>
#include <sstream>
#include <iostream>

SSDL2015::SSDL2015(std::string cfg){
  
  startExecution(cfg);
  initialize();

}

SSDL2015::~SSDL2015(){
 
}

void
SSDL2015::initialize(){
  fillEvents();
  
  _vc->registerVar("run"                          );
  _vc->registerVar("lumi"                         );
  //_vc->registerVar("evt"                          );
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
  _vc->registerVar("nTrueInt"                     );
  _vc->registerVar("nBJetPt40Medium"              );
  _vc->registerVar("puWeight"                     );
  _vc->registerVar("genWeight"                    );
  _vc->registerVar("nLepGood"                     );
  _vc->registerVar("LepGood_pt"                   );
  _vc->registerVar("LepGood_eta"                  );
  _vc->registerVar("LepGood_phi"                  );
  _vc->registerVar("LepGood_charge"               );
  _vc->registerVar("LepGood_tightCharge"          );
  _vc->registerVar("LepGood_mediumMuonId"         );
  _vc->registerVar("LepGood_mvaIdSpring15"        );
  _vc->registerVar("LepGood_pdgId"                );
  _vc->registerVar("LepGood_relIso03"             );
  _vc->registerVar("LepGood_relIso04"             );
  //_vc->registerVar("LepGood_jetPtRatio"           );
  _vc->registerVar("LepGood_jetPtRatiov2"         );
  //_vc->registerVar("LepGood_jetPtRel"             );
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
  _vc->registerVar("LepGood_mvaSusy"              );
  _vc->registerVar("LepGood_mcMatchId"            );
  _vc->registerVar("LepGood_mcMatchAny"           );
  _vc->registerVar("LepGood_sigmaIEtaIEta"        );
  _vc->registerVar("LepGood_dEtaScTrkIn"          );
  _vc->registerVar("LepGood_dPhiScTrkIn"          );
  _vc->registerVar("LepGood_hadronicOverEm"       );
  _vc->registerVar("LepGood_eInvMinusPInv"        );
  _vc->registerVar("LepGood_ecalPFClusterIso"          );
  _vc->registerVar("LepGood_hcalPFClusterIso"          );
  _vc->registerVar("LepGood_dr03TkSumPt"               );

  _vc->registerVar("met_pt"                       );
  _vc->registerVar("met_eta"                      );
  _vc->registerVar("met_phi"                      );
  _vc->registerVar("met_mass"                     );
  _vc->registerVar("metNoHF_pt"                   );
  _vc->registerVar("metNoHF_eta"                  );
  _vc->registerVar("metNoHF_phi"                  );
  _vc->registerVar("metNoHF_mass"                 );
  _vc->registerVar("nJet25"                       );
  _vc->registerVar("nJet40"                       );

  _vc->registerVar("nJet"                         );
  _vc->registerVar("Jet_id"                       );
  _vc->registerVar("Jet_pt"                       );
  _vc->registerVar("Jet_rawPt"                    );
  _vc->registerVar("Jet_eta"                      );
  _vc->registerVar("Jet_phi"                      );
  _vc->registerVar("Jet_mass"                     );
  _vc->registerVar("Jet_btagCSV"                  );

  _vc->registerVar("nDiscJet"                     );
  _vc->registerVar("DiscJet_id"                   );
  _vc->registerVar("DiscJet_pt"                   );
  _vc->registerVar("DiscJet_rawPt"                );
  _vc->registerVar("DiscJet_eta"                  );
  _vc->registerVar("DiscJet_phi"                  );
  _vc->registerVar("DiscJet_mass"                 );
  _vc->registerVar("DiscJet_btagCSV"              );

  _vc->registerVar("nJetFwd"                      );
  _vc->registerVar("JetFwd_pt"                    );
  _vc->registerVar("JetFwd_phi"                   );
  

  _vc->registerVar("htJet40j"                     );
  _vc->registerVar("minMllAFAS"                   );
  _vc->registerVar("minMllAFOS"                   );
  _vc->registerVar("mZ1"                          );
  _vc->registerVar("nLepGood10"                   );

 
  //generator informations
  _vc->registerVar("nGenPart"                     );
  _vc->registerVar("GenPart_pt"                   );
  _vc->registerVar("GenPart_eta"                  );
  _vc->registerVar("GenPart_phi"                  );
  _vc->registerVar("GenPart_pdgId"                );
  _vc->registerVar("GenPart_motherId"             );
  
  //LHE gen level weights
  _vc->registerVar("nLHEweight"                   );
  _vc->registerVar("LHEweight_id"                 );
  _vc->registerVar("LHEweight_wgt"                );

  //bjets
  _vc->registerVar("nBJetLoose25"                 );
  _vc->registerVar("nBJetMedium40"                );
  _vc->registerVar("nBJetMedium25"                );
  _vc->registerVar("nBJetTight40"                 );
  _vc->registerVar("nSoftBJetMedium25"            );
  
  // FLAGS
  _vc->registerVar("hbheFilterNew25ns"            );
  _vc->registerVar("Flag_CSCTightHaloFilter"      );
  _vc->registerVar("Flag_eeBadScFilter"           );
  
  //pileup
  _vc->registerVar("puWeight"                     );
  _vc->registerVar("vtxWeight"                    );

  _susyMod = new SusyModule(_vc, _dbm);
  
  int nCateg=237; //n*(1+78) + 1  
  _categs.resize(nCateg);
  string srs[237]={ 

    "HH SR1", "HH SR2", "HH SR3", "HH SR4", "HH SR5", "HH SR6", "HH SR7", "HH SR8",
    "HH SR9", "HH SR10", "HH SR11", "HH SR12", "HH SR13", "HH SR14", "HH SR15", "HH SR16",
    "HH SR17", "HH SR18", "HH SR19", "HH SR20", "HH SR21", "HH SR22", "HH SR23", "HH SR24",
    "HH SR25", "HH SR26", "HH SR27", "HH SR28", "HH SR29", "HH SR30", "HH SR31", "HH SR32",
    
    "HL SR1", "HL SR2", "HL SR3", "HL SR4", "HL SR5", "HL SR6", "HL SR7", "HL SR8",
    "HL SR9", "HL SR10", "HL SR11", "HL SR12", "HL SR13", "HL SR14", "HL SR15", "HL SR16",
    "HL SR17", "HL SR18", "HL SR19", "HL SR20", "HL SR21", "HL SR22", "HL SR23", "HL SR24",
    "HL SR25","HL SR26",
    
    "LL SR1", "LL SR2", "LL SR3", "LL SR4", "LL SR5", "LL SR6", "LL SR7", "LL SR8",

    //"BR0H", "BR0M", "BR0L",

    "BR00H", "BR00M", "BR00L",
    "BR10H", "BR10M", "BR10L",
    "BR20H", "BR20M", "BR20L",
    "BR30H", "BR30M", "BR30L",
    
    // //fake workflows ==================================================

    "HH SR1_Fake", "HH SR2_Fake", "HH SR3_Fake", "HH SR4_Fake", "HH SR5_Fake", "HH SR6_Fake", "HH SR7_Fake", "HH SR8_Fake",
    "HH SR9_Fake", "HH SR10_Fake", "HH SR11_Fake", "HH SR12_Fake", "HH SR13_Fake", "HH SR14_Fake", "HH SR15_Fake", "HH SR16_Fake",
    "HH SR17_Fake", "HH SR18_Fake", "HH SR19_Fake", "HH SR20_Fake", "HH SR21_Fake", "HH SR22_Fake", "HH SR23_Fake", "HH SR24_Fake",
    "HH SR25_Fake", "HH SR26_Fake", "HH SR27_Fake", "HH SR28_Fake", "HH SR29_Fake", "HH SR30_Fake", "HH SR31_Fake", "HH SR32_Fake",
    
    "HL SR1_Fake", "HL SR2_Fake", "HL SR3_Fake", "HL SR4_Fake", "HL SR5_Fake", "HL SR6_Fake", "HL SR7_Fake", "HL SR8_Fake",
    "HL SR9_Fake", "HL SR10_Fake", "HL SR11_Fake", "HL SR12_Fake", "HL SR13_Fake", "HL SR14_Fake", "HL SR15_Fake", "HL SR16_Fake",
    "HL SR17_Fake", "HL SR18_Fake", "HL SR19_Fake", "HL SR20_Fake", "HL SR21_Fake", "HL SR22_Fake", "HL SR23_Fake", "HL SR24_Fake",
    "HL SR25_Fake","HL SR26_Fake",
    
    "LL SR1_Fake", "LL SR2_Fake", "LL SR3_Fake", "LL SR4_Fake", "LL SR5_Fake", "LL SR6_Fake", "LL SR7_Fake", "LL SR8_Fake",



    "BR00H_Fake", "BR00M_Fake", "BR00L_Fake",
    "BR10H_Fake", "BR10M_Fake", "BR10L_Fake",
    "BR20H_Fake", "BR20M_Fake", "BR20L_Fake",
    "BR30H_Fake", "BR30M_Fake", "BR30L_Fake",


    // //misId workflows ==================================================

    "HH SR1_mId", "HH SR2_mId", "HH SR3_mId", "HH SR4_mId", "HH SR5_mId", "HH SR6_mId", "HH SR7_mId", "HH SR8_mId",
    "HH SR9_mId", "HH SR10_mId", "HH SR11_mId", "HH SR12_mId", "HH SR13_mId", "HH SR14_mId", "HH SR15_mId", "HH SR16_mId",
    "HH SR17_mId", "HH SR18_mId", "HH SR19_mId", "HH SR20_mId", "HH SR21_mId", "HH SR22_mId", "HH SR23_mId", "HH SR24_mId",
    "HH SR25_mId", "HH SR26_mId", "HH SR27_mId", "HH SR28_mId", "HH SR29_mId", "HH SR30_mId", "HH SR31_mId", "HH SR32_mId",
    
    "HL SR1_mId", "HL SR2_mId", "HL SR3_mId", "HL SR4_mId", "HL SR5_mId", "HL SR6_mId", "HL SR7_mId", "HL SR8_mId",
    "HL SR9_mId", "HL SR10_mId", "HL SR11_mId", "HL SR12_mId", "HL SR13_mId", "HL SR14_mId", "HL SR15_mId", "HL SR16_mId",
    "HL SR17_mId", "HL SR18_mId", "HL SR19_mId", "HL SR20_mId", "HL SR21_mId", "HL SR22_mId", "HL SR23_mId", "HL SR24_mId",
    "HL SR25_mId","HL SR26_mId",
    
    "LL SR1_mId", "LL SR2_mId", "LL SR3_mId", "LL SR4_mId", "LL SR5_mId", "LL SR6_mId", "LL SR7_mId", "LL SR8_mId",



    "BR00H_mId", "BR00M_mId", "BR00L_mId",
    "BR10H_mId", "BR10M_mId", "BR10L_mId",
    "BR20H_mId", "BR20M_mId", "BR20L_mId",
    "BR30H_mId", "BR30M_mId", "BR30L_mId",

    "Fake", //global fake
    "mId", // global mId
    "WZCR" //WZ CR
 
  };

  _categs.assign(srs, srs+nCateg);

  for(size_t ic=0;ic< _categs.size();ic++) {
    _SR = _categs[ic];
    setSignalRegions();
    addWorkflow( ic+1, _categs[ic] );
  }


  addWorkflow( kGlobalFake, "Fake" );
  addWorkflow( kGlobalmId, "mId" );
  addWorkflow( kWZCR, "WZCR");

  //extra input variables
  _lepflav = getCfgVarS("LEPFLAV", "all");
  _leppt   = getCfgVarS("LEPPT"  , "all");
  _SR      = getCfgVarS("SR"     , "BR02H");
  _FR      = getCfgVarS("FR"     , "FO2C");
  _LHESYS = getCfgVarS("LHESYS", "");
  _categorization = getCfgVarI("categorization", 1);
  _DoValidationPlots = getCfgVarI("ValidationPlots", 0);

//  vector<string> jess;
//  jess.push_back("Jet_pt");
//  addSystSource("JES",SystUtils::kNone, "%", jess, "JES8TeV.db", "" );

  //FR databases
  if(_FR=="FO2C") {
    _dbm->loadDb("ElNIso","FR_Oct21.root","FRElPtCorr_ETH_non");
    _dbm->loadDb("MuNIso","FR_Oct21.root","FRMuPtCorr_ETH_non");
    _dbm->loadDb("ElIso","FR_Oct21.root","FRElPtCorr_ETH_iso");
    _dbm->loadDb("MuIso","FR_Oct21.root","FRMuPtCorr_ETH_iso");

    _dbm->loadDb("ElNIsoMC","FR_Oct21.root","FRElPtCorr_qcd_non");
    _dbm->loadDb("MuNIsoMC","FR_Oct21.root","FRMuPtCorr_qcd_non");
    _dbm->loadDb("ElIsoMC","FR_Oct21.root","FRElPtCorr_qcd_iso");
    _dbm->loadDb("MuIsoMC","FR_Oct21.root","FRMuPtCorr_qcd_iso");
  }
  if(_FR=="FO4C") {
    _dbm->loadDb("El","MaySync/CH_FRFile_090615.root","tt/nosel/FRISisofo4RElPtMIso2");
    _dbm->loadDb("Mu","MaySync/CH_FRFile_090615.root","tt/nosel/FRISisofo4RMuPtMIso2");
  }

  //chargeflip DB
  // _dbm->loadDb("chargeMId","ChargeMisIdProb.root","chargeMisId");
  // _dbm->loadDb("chargeMIdMC","ChargeMisIdProb_MC.root","chargeMisId");
  _dbm->loadDb("chargeMId","comissioning_data.root","chargeMisId");
  _dbm->loadDb("chargeMIdMC","comissioning_data.root","chargeMisId");
  
 
  int ilhe = (int)atoi(_LHESYS.c_str());
  bool tmp_ismux = ilhe >= 1001 && ilhe <= 1009;
  bool tmp_ispdf = ilhe >= 2001 && ilhe <= 2100;
  
  if (!tmp_ismux && !tmp_ispdf) {
    _LHESYS = "0";
  }

}

void
SSDL2015::modifyWeight() {

  if (_vc->get("isData") != 1) {
    //generator weights
    if (_LHESYS == "0") {_weight *= _vc->get("genWeight");}///23443.423;}
    else {_weight *= lheWeight();}
    //pileup weights
    _weight *= _vc->get("vtxWeight");
  }

}

double        
SSDL2015::lheWeight() {


  int tmp_nlhe = _vc->get("nLHEweight");
  //std::cout << "tmp_nlhe=" << tmp_nlhe << std::endl;
  
  for (int i = 0; i < tmp_nlhe; i++) {
        int tmp_lhe_id = _vc->get("LHEweight_id", i);
	
      
        if (tmp_lhe_id == (int)atoi(_LHESYS.c_str())) {
	  double tmp_lhe_wgt = _vc->get("LHEweight_wgt", i);
	  
	  
          //std::cout << "using weight LHEid[" << i << "]="  << tmp_lhe_id << " LHEvalue=" << tmp_lhe_wgt  <<  std::endl;
		
          return tmp_lhe_wgt;
        }
      
  }
  return 1.0;

}

void
SSDL2015::modifySkimming() {
}


void
SSDL2015::defineOutput() {
  ///////////////////////////////////////////////////////////////////////////
  // GLOBAL PLOTS:  These plots are drawn for every SR
  ///////////////////////////////////////////////////////////////////////////
  _hm->addVariable("l1Pt"  , 150, 0.,  150, "p_{T}(l_{1}) [GeV]"                 );
  _hm->addVariable("l2Pt"  , 150, 0.,  150, "p_{T}(l_{2}) [GeV]"                 );
  _hm->addVariable("MET"   , 500, 0. , 500, "#slash{E}_{T} [GeV]"                );
  _hm->addVariable("HT"    , 800, 0. , 800, "H_{T} [GeV]"                        );
  _hm->addVariable("MT"    , 200, 0. , 200, "min(M_{T,1}, M_{T,2}) [GeV]"        );
  _hm->addVariable("NBJets",   8,-0.5, 7.5, "N_{b-jets} (p_{T} > 25 GeV, medium)");
  _hm->addVariable("NJets" ,   8,-0.5, 7.5, "N_{jets} (p_{T} > 40 GeV)"          );

  _hm->addVariable("mass" ,   200,0, 200, "m_{ll} [GeV]"  );
  
  if(!_DoValidationPlots) return; 
  ///////////////////////////////////////////////////////////////////////////
  // VALIDATION PLOTS:  plotting these varibles for a general SS selection //
  ///////////////////////////////////////////////////////////////////////////
  vector<string> reg;
  reg.push_back("ttbar");
  reg.push_back("ZMuMu");
  reg.push_back("ZEE");
  reg.push_back("Zl");
  reg.push_back("Wl");
  
  for (size_t r=0; r<reg.size(); r++) {
    // lepton variables
    _hm->addVariable(reg[r]+"_lep1_jetPtRatio", 100, 0., 1.2, "Leading Lepton Jet p_{T} Ratio [GeV]", false);
    _hm->addVariable(reg[r]+"_lep1_jetPtRel"  , 100, 0., 40., "Leading Lepton Jet p_{T} Rel   [GeV]", false);
    _hm->addVariable(reg[r]+"_lep1_miniRelIso", 100, 0., 0.4, "Leading Lepton Isolation", false);
    _hm->addVariable(reg[r]+"_lep1_Pt"        , 100, 0., 100, "Leading Lepton p_{T} [GeV]", false);
    _hm->addVariable(reg[r]+"_lep1_Eta"       , 100, 0., 2.5, "Leading Lepton #eta", false);
    _hm->addVariable(reg[r]+"_lep1_SIP3D"     , 100, 0., 5.0, "Leading Lepton SIP_{3D}", false);
    _hm->addVariable(reg[r]+"_lep2_jetPtRatio", 100, 0., 1.2, "Subleading Lepton Jet p_{T} Ratio [GeV]", false);
    _hm->addVariable(reg[r]+"_lep2_jetPtRel"  , 100, 0., 40., "Subleading Lepton Jet p_{T} Rel   [GeV]", false);
    _hm->addVariable(reg[r]+"_lep2_miniRelIso", 100, 0., 0.4, "Subleading Lepton Isolation", false);
    _hm->addVariable(reg[r]+"_lep2_Pt"        , 100, 0., 100, "Subleading Lepton p_{T} [GeV]", false);
    _hm->addVariable(reg[r]+"_lep2_Eta"       , 100, 0., 2.5, "Subleading Lepton #eta", false);
    _hm->addVariable(reg[r]+"_lep2_SIP3D"     , 100, 0., 5.0, "Subleading Lepton SIP_{3D}", false);
    
    // event variables 
    _hm->addVariable(reg[r]+"_MET"            , 500, 0. , 500, "#slash{E}_{T} [GeV]", false);
    _hm->addVariable(reg[r]+"_htJet40j"       , 800, 0. , 800, "H_{T} [GeV]", false);
    _hm->addVariable(reg[r]+"_mZ1"            , 300, 0. , 300, "best m_{l^{+}l^{-}} [GeV]", false);
    _hm->addVariable(reg[r]+"_MTmin"          ,  20, 0. , 200, "min(M_{T,1}, M_{T,2}) [GeV]", false);
    _hm->addVariable(reg[r]+"_NBJetsLoose25"  ,   8,-0.5, 7.5, "N_{b-jets} (p_{T} > 25 GeV, loose)", false);
    _hm->addVariable(reg[r]+"_NBJetsMedium25" ,   8,-0.5, 7.5, "N_{b-jets} (p_{T} > 25 GeV, medium)", false);
    _hm->addVariable(reg[r]+"_NBJetsTight40"  ,   8,-0.5, 7.5, "N_{b-jets} (p_{T} > 40 GeV, tight)", false);
    _hm->addVariable(reg[r]+"_NJets40"        ,   8,-0.5, 7.5, "N_{jets} (p_{T} > 40 GeV)", false);
  }


  
}


void
SSDL2015::writeOutput() {
 
}


void
SSDL2015::run() {
  //cout<<" ================== new event ================== "<<endl;
  //if(_vc->get("evt")!=69430384  && _vc->get("evt")!=37738763 && _vc->get("evt")!=58845792 // &&
  //    // _vc->get("evt")!=72951 && _vc->get("evt")!=142649
  //  ) return;
  
  //if(_vc->get("evt")!=375924 ) return;
  
  //if(_vc->get("evt")!=103973 )  return;
  //if(_vc->get("evt")!=142649 && _vc->get("evt")!=72951 ) return;
  //if(_vc->get("evt")!=72688 && _vc->get("evt")!=49205) return;
  ////cout<<" =================================="<< _sampleName <<endl;
 
  // bool find=false;
  // for(size_t ii=0;ii<_events.size();ii++)
  //   if(_events[ii]==_vc->get("evt")) {
  //     find=true;
  //     break;
  //   }

  // if(!find) return;

  counter("denominator");
  //cout<<" ============================== "<<_vc->get("evt")<<" ============================== "<<endl;
  
  retrieveObjects();
 
 
    
  if(_DoValidationPlots) {
    if (ttbarSelection())   fillValidationHistos("ttbar");
    if (ZlSelection())      fillValidationHistos("Zl");
    if (WlSelection())      fillValidationHistos("Wl");
    if (ZMuMuSelection())   fillValidationHistos("ZMuMu");
    if (ZEESelection())     fillValidationHistos("ZEE");
  }
  
   bool ssLepSel=ssLeptonSelection();
   if(_vc->get("isData") && !_isOS && !_isFake) return; //blinding of signal regions
 
  if(!ssLepSel) { //!makeCut(ssLeptonSelection(),"SS Selection")
    // failed same-sign lepton selection, fill WZ control region
    wzCRSelection(); 
    setWorkflow(kGlobal); //MANDATORY (otherwise double counting in other categories)
    return;
  }
   counter("SS like pair");
   //===============================================
  if(!_isFake && !_isOS) {
    setWorkflow(kGlobal);
    counter("dispatching");
    advancedSelection( kGlobal );
  }
  else {
    
    vector<float> frs=getFRs();
    int n=0;
    for(unsigned int ip=0;ip<_auxPairs.size();ip++) {
      _l1Cand = _auxPairs[ip][0];
      _l2Cand = _auxPairs[ip][1];
      _idxL1 = _auxIdxs[ip][0];
      _idxL2 = _auxIdxs[ip][1];

      if(_auxFlags[ip]==kIsOS) {
	setWorkflow(kGlobalmId);
	counter("dispatching");
	chargeFlipProb();
	advancedSelection( kGlobalmId );
      }
      if(_auxFlags[ip]==kIsFake || _auxFlags[ip]==kIsDFake ) {
	setWorkflow(kGlobalFake);
	counter("dispatching");
	getFRProb(_auxFlags[ip], kIsDFake?0:frs[n] );
	advancedSelection( kGlobalFake );
	if(_auxFlags[ip]==kIsFake) n++;
      }
    }
  }
}


void 
SSDL2015::advancedSelection(int WF) {

  int offset=0;
  if(WF==kGlobalFake) offset=kBR30L;
  if(WF==kGlobalmId)  offset=kBR30L_Fake;

  counter("weigthing");

  if (_leppt=="hh" && _l1Cand->pt()<25.) return;
  if (_leppt=="hh" && _l2Cand->pt()<25.) return;
  if (_leppt=="hl" && (_l1Cand->pt()<25. && _l2Cand->pt()<25.) ) return;
  if (_leppt=="hl" && (_l1Cand->pt()>25. && _l2Cand->pt()>25.) ) return;
  if (_leppt=="ll" && _l1Cand->pt()>25.) return;
  if (_leppt=="ll" && _l2Cand->pt()>25.) return;
  
  if(_lepflav=="mm" &&
     (std::abs(_l1Cand->pdgId())!=13 || std::abs(_l2Cand->pdgId())!=13 ) ) return;
  if(_lepflav=="ee" && 
     (std::abs(_l1Cand->pdgId())!=11 || std::abs(_l2Cand->pdgId())!=11 ) ) return;
  if(_lepflav=="em" && std::abs(_l1Cand->pdgId())==std::abs(_l2Cand->pdgId()) ) return;

  counter("ptflav");
   Candidate* Z=Candidate::create(_l1Cand, _l2Cand);
  fill("mass",Z->mass(),_weight);
 
  if (_vc->get("isData") != 1) {
    if(!passGenSelection() ) return;
  }
  counter("genselection");
 
  _flav=std::abs(_l1Cand->pdgId())+std::abs(_l2Cand->pdgId());

  if(!hltSelection() ) return;
  counter("HLT");
 
  //Scale factors =======================
  _susyMod->applySingleLepSF(_l1Cand, _weight);
  _susyMod->applySingleLepSF(_l2Cand, _weight);
  // ====================================

  //===============================
  _mTmin=min( Candidate::create(_l1Cand, _met)->mass(),
	      Candidate::create(_l2Cand, _met)->mass() );
  //===============================

  counter("lepton baseline");
  
  //default cuts for baseline
  if(_HT<80) return;
  if( (_HT<500 && _metPt < 30) ) return;
  if(_nJets<2) return;

  counter("std baseline");
  
  fillhistos();//fill histos for kGlobal, kGlobalFake, kGlobalmId
 
  if(_categorization) {
    categorize();
    setWorkflow(getCurrentWorkflow()+offset);
    counter("region splitting");
  }
  else {
    if(!testRegion() ) return;
  }

  counter("selected");
  if(_categorization) {
    fillhistos();//fill histos for SR and BR  (and the SR_Fake and BR_Fake)
  }

  // if( getCurrentWorkflow()==0) return; //getCurrentWorkflow()==100 ||
  // if( getCurrentWorkflow()>kSR32A 
  //     && getCurrentWorkflow()!=kBR00H
  //     && getCurrentWorkflow()!=kBR10H
  //     && getCurrentWorkflow()!=kBR20H
  //     && getCurrentWorkflow()!=kBR30H
  //     ) return;

  // int run=_vc->get("run");
  // int lumi=_vc->get("lumi");
  // int event=_vc->get("evt");
  // int nLep = _looseLeps.size();//_looseLepsVeto.size();//_vc->get("nLepGood_Mini");
  // // cout<<" <====> "<<_vc->get("nLepGood_Mini")<<"  "<<_looseLepsVeto.size()<<"  "<<_looseLeps.size()<<endl;
  // int id1 = _l1Cand->pdgId();
  // double pt1 = _l1Cand->pt();
  // int id2 = _l2Cand->pdgId();
  // double pt2 = _l2Cand->pt();
  // int njet = _nJets;
  // int nbjet = _nBJets;
  // double met = _met->pt();
  // double HT = _HT;
  // int sr = ((getCurrentWorkflow()<kBR00H)?(getCurrentWorkflow()):(0));

  // if(getCurrentWorkflow()==kBR00H || getCurrentWorkflow()==kBR10H || getCurrentWorkflow()==kBR20H || getCurrentWorkflow()==kBR30H) sr=0;
  
  // cout << Form("%1d %9d %12d\t%2d\t%+2d %5.1f\t%+2d %5.1f\t%d\t%2d\t%5.1f\t%6.1f\t%2d",
  // 	       run, lumi, event, nLep,
  // 	       id1, pt1, id2, pt2,
  // 	       njet, nbjet, met, HT,
  // 	       sr ) << endl;

  // if(_auxPairs.size()==1 && _auxFlags[0]==kIsFake) {
  //   unsigned long int event=_vc->get("evt");
  //   float lepPt = _vc->get("LepGood_pt",_idxL2);
  //   float conePt = _l2Cand->pt();
  //   float pTrel = _vc->get("LepGood_jetPtRelv2",_idxL2);
  //   float jetPt = _vc->get("LepGood_jetRawPt",_idxL2)*_vc->get("LepGood_jetCorrFactor_L1L2L3Res",_idxL2);

  //   cout<<Form("%1d\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t",event,lepPt,conePt, pTrel, jetPt)<<_categs[getCurrentWorkflow()-offset-1]<<endl; 
  // }


}

vector<float> 
SSDL2015::getFRs() {

  vector<float> frs;
  for(unsigned int ip=0;ip<_auxPairs.size();ip++) {
    if(_auxFlags[ip]!=kIsFake ) continue;
    float fr=getFR(_auxPairs[ip][1], _auxIdxs[ip][1]);
    frs.push_back(fr);
  }
  
  vector<float> probs;
  if(frs.size()==0) return probs;
  probs.push_back(frs[0]);
  for(unsigned int i=1;i<frs.size();i++) {
    float prob = frs[i]/(1-frs[i]);
    for(unsigned int j=0;j<i;j++) {
      //cout<<" computing proba :"<<i<<"  "<<j<<" prob "<<prob<<"  "<<(1-frs[i])<<endl;
      prob*=(1-frs[i]);
    }
    probs.push_back(prob);
  }
  return probs;

}

void
SSDL2015::getFRProb(int flag, float fr) {

  float p=0;
  if(flag==kIsFake) {
    // float fr=getFR(_l2Cand, _idxL2);
    // p=fr/(1-fr);
    p=fr;
  }
  else {
    float fr1=getFR(_l1Cand, _idxL1);
    float fr2=getFR(_l2Cand, _idxL2);
    p=fr1*fr2/(1-fr1*fr2);
  }
  _weight *= p;
}


void
SSDL2015::getFRProb() {

  CandList fObj1,fObj2;
  vector<unsigned int> fIdx1, fIdx2;

  float w=0;
  for(unsigned int i=0;i<_auxPairs.size();i++) {

    if(_auxFlags[i]==kIsFake && _auxFlags[i]!=kIsDFake) {
      fObj1.push_back(_auxPairs[i][1]);
      fIdx1.push_back(_auxIdxs[i][1]);
    }
    if(_auxFlags[i]!=kIsFake && _auxFlags[i]==kIsDFake) {
      fObj2.push_back(_auxPairs[i][0]);
      fIdx2.push_back(_auxIdxs[i][0]);
      fObj2.push_back(_auxPairs[i][1]);
      fIdx2.push_back(_auxIdxs[i][1]);
      
    }
  }

  float p1=getProbAtLeastNIso( fObj1, fIdx1, 1);
  float p2=getProbAtLeastNIso( fObj2, fIdx2, 2);
  
  _weight *= (p1+p2)/(1-p1-p2);

}

bool
SSDL2015::noIsoSel() {
  
  if( _fakableLepsPtCutVeto.size()!=0 ) return false;
  
  float p=getProbAtLeastNIso( _fakableLepsPtCutVeto ,_fakableLepsPtCutVetoIdx , 2);
  _weight *= p/(1-p);
  return true;
}

bool
SSDL2015::oneIsoSel() {
  
  if( _fakableLepsPtCutVeto.size()!=1 ) return false;

  float p=getProbAtLeastNIso( _fakableLepsPtCutVeto ,_fakableLepsPtCutVetoIdx , 1);
  _weight *= p/(1-p);

  return true;
}

bool
SSDL2015::twoIsoSel() {
  
  if( _fakableLepsPtCutVeto.size()!=2 ) return false;

  float p=getProbAtLeastNIso( _fakableLepsPtCutVeto ,_fakableLepsPtCutVetoIdx , 2);
  _weight *= p/(1-p);

  return true;
}


float
SSDL2015::getProbAtLeastNIso(CandList fObjs, vector<unsigned int> fObjIdx,
			      int nIso) {

  //MM tirage Bernoulli sans remise non ordonne avec probas individuelles
  //formule generale probablement tres compliquee, et surtout pas trouvee

  if(fObjs.size()<(size_t)nIso) {cout<<"not enough leptons for your configuration : "<<fObjs.size()<<" vs  "<<nIso<<endl; return 0;}
  if(nIso>2) {cout<<"not implemented for nIso>2"<<endl; return 0;}

  vector<float> frs(fObjs.size(),0);
 
  float pNoIso = 1;
  for(size_t io=0;io<fObjs.size(); io++) {
    frs[io] = getFR(fObjs[io], fObjIdx[io]);
    pNoIso *= (1-frs[io]);
  }

  if(nIso==0) return pNoIso;// no isolated lepton among all leptons
  if(nIso==1) return (1-pNoIso);// at least one isolated lepton among all leptons

  //at least 2 iso case : computes proba to have only 1 iso within N
  float p1Iso = 0;
  for(size_t ii=0;ii<fObjs.size(); ii++) {
    float pii = frs[ii];
    for(size_t ij=0;ij<fObjs.size(); ij++) {
      if(ij!=ii)
	pii *= 1-frs[ij];
    }
    p1Iso += pii;
  }

  if(nIso==2) return (1-p1Iso-pNoIso);

  return 0;
}


//==================================================================================================
void 
SSDL2015::retrieveObjects(){
  
  _jets.clear();
  

  _l1Cand=nullptr;
  _l2Cand=nullptr;
  
  _looseLeps.clear();
  _looseLepsIdx.clear();

  _looseLeps10.clear();
  _looseLeps10Idx.clear();

  _looseLepsPtCut.clear();
  _looseLepsPtCutIdx.clear();

  // _looseLepsVeto.clear();
  // _looseLepsVetoIdx.clear();

  _looseLepsPtCutVeto.clear();
  _looseLepsPtCutVetoIdx.clear();

  _looseLepsPtCorrCutVeto.clear();
  _looseLepsPtCorrCutVetoIdx.clear();

  _looseLepsPtCorrCut.clear();
  _looseLepsPtCorrCutIdx.clear();

  _jetCleanLeps10.clear();
  _jetCleanLeps10Idx.clear();
  
  _fakableLepsPtCutVeto.clear();
  _fakableLepsPtCutVetoIdx.clear();
  
  _tightLepsPtCut.clear();
  _tightLepsPtCutIdx.clear();

  _tightLepsPtCutVeto.clear();
  _tightLepsPtCutVetoIdx.clear();


  //background vectors
  _tightLepsOSPtCut.clear();
  _tightLepsOSPtCutIdx.clear();

  _auxPairs.clear();
  _auxFlags.clear();
  _auxIdxs.clear();
  //===================

  selectLeptons();

  _nJets=_jets.size();
  _nBJets=_bJets.size();
 

  if(false) {
    TVector2 met = varyMET();
    _met = Candidate::create( met.Mod(), met.Phi() );
  }
  else
    _met = Candidate::create( _vc->get("met_pt"), _vc->get("met_phi") );

  _metPt = _met->pt();
  //cout<<" coinon"<<endl;
  //MET and MT
 

}

//=========================================================

bool
SSDL2015::ssLeptonSelection() {
  _isFake=false;
  _isOS=false;
  _dFake=false;

  //cout<<" size "<<_tightLepsVeto10.size()<<endl;
  // 2Tight ===============================
  bool isGoodPair=false;
  if(_tightLepsPtCutVeto.size()>=2) { //main
    // _isFake=false;
    // _isOS=false;
   
    CandList lepPair=_susyMod->bestSSPair( (&_tightLepsPtCutVeto), true, false, false, 10, 15, _idxL1, _idxL2);
    if(lepPair.size()>=2) {
      _l1Cand = lepPair[0];
      _l2Cand = lepPair[1];
      if(_l1Cand!=nullptr && _l2Cand!=nullptr) {
      	_idxL1 = _tightLepsPtCutVetoIdx[_idxL1];
	_idxL2 = _tightLepsPtCutVetoIdx[_idxL2];
	isGoodPair=true;
      }
    }    

  }
  if(isGoodPair) return true;
  
  //====================================
  //=== backgrond stuff ================
  //====================================
  vector<int> idxs1,idxs2;

  // 2Tight, opposite charge ===================
  if(_tightLepsOSPtCut.size()>=2) {
    //_isFake=false;
    
    CandList lepPair=_susyMod->bestSSPair( (&_tightLepsOSPtCut), true, false, true, 10, 15, _idxL1, _idxL2);
    if(lepPair.size()>=2) { 
      _l1Cand = lepPair[0];
      _l2Cand = lepPair[1];
    
      if(_l1Cand!=nullptr && _l2Cand!=nullptr) {
  	_idxL1 = _tightLepsOSPtCutIdx[_idxL1];
  	_idxL2 = _tightLepsOSPtCutIdx[_idxL2];
    	_isOS=true;

	_auxPairs.push_back(lepPair);
	_auxFlags.push_back(kIsOS);
	_auxIdxs.push_back( vector<int>({_idxL1, _idxL2}) );
      }
    }
  }

  //fake stuff==========================================================================================
  // 1Tight 1Loose ====================================
  vector<CandList> lepPairs;
  if(_tightLepsPtCutVeto.size()>=1 && _fakableLepsPtCutVeto.size()>=1) { 
    lepPairs=_susyMod->buildSSPairs( (&_tightLepsPtCutVeto), (&_fakableLepsPtCutVeto), true, false, false, 10, 15, idxs1, idxs2);
 
    //filling =======================
    for(unsigned int i=0;i<lepPairs.size();i++) {
      _isFake=true;
    
      _auxPairs.push_back(lepPairs[i]);
      _auxFlags.push_back(kIsFake);
    
      _idxL1 = _tightLepsPtCutVetoIdx[idxs1[i]];
      _idxL2 = _fakableLepsPtCutVetoIdx[idxs2[i]];
      vector<int> tmp;
      tmp.push_back(_idxL1);
      tmp.push_back(_idxL2);
      _auxIdxs.push_back(tmp);
    
    }
  }
  //======================================================

  // 0Tight any loose ====================================
  if(_tightLepsPtCutVeto.size()==0 && _fakableLepsPtCutVeto.size()==2) {
    vector<CandList> lepPairs=_susyMod->buildSSPairs( (&_fakableLepsPtCutVeto), true, false, false, 10, 15, idxs1, idxs2);
    
    for(unsigned int i=0;i<lepPairs.size();i++) {
      _isFake=true;

      _auxPairs.push_back(lepPairs[i]);
      _auxFlags.push_back(kIsDFake);

      _idxL1 = _fakableLepsPtCutVetoIdx[ idxs1[i] ];
      _idxL2 = _fakableLepsPtCutVetoIdx[ idxs2[i] ];
      vector<int> tmp;
      tmp.push_back(_idxL1);
      tmp.push_back(_idxL2);
      _auxIdxs.push_back(tmp);
      
    }
  }

  if(_isOS || _isFake) return true;
  return false;
}

void 
SSDL2015::wzCRSelection() {
  
  setWorkflow(kWZCR);
  
  if(!makeCut(_tightLepsPtCut.size()>=2,"Two leptons")) return;
  _isFake=false;
    
  CandList lepPair=_susyMod->bestSSPair( (&_tightLepsPtCut), true, false, false, 10,15, _idxL1, _idxL2);
  _l1Cand = lepPair[0];
  _l2Cand = lepPair[1];
      
  if(_l1Cand==nullptr || _l2Cand==nullptr) return; //case with less than two leptons or no valid pair
  _idxL1 = _tightLepsPtCutIdx[_idxL1];
  _idxL2 = _tightLepsPtCutIdx[_idxL2];
  
  if(!makeCut( _l1Cand->charge()*_l2Cand->charge()>0, "Same-Sign" ) ) return;
  
  if(!_susyMod->passMllMultiVeto( _l1Cand, &_looseLeps, 0, 12, true) ||
     !_susyMod->passMllMultiVeto( _l2Cand, &_looseLeps, 0, 12, true) ) return;
  
  if(!makeCut(_susyMod->passMllSingleVeto(_l1Cand, _l2Cand, 0, 8, false), "Z/g* veto") ) return;
  
  if(_susyMod->passMllMultiVeto( _l1Cand, &_looseLeps, 76, 106, true) &&
     _susyMod->passMllMultiVeto( _l2Cand, &_looseLeps, 76, 106, true) ) return;
  counter("Z selection");
    
  // now apply tighter requirements on MET, HT, MT... 
  if(!makeCut(_HT > 80., "H_{T} > 80 GeV")) return;
  if(!makeCut(_nJets>=2, "n_{jets} >= 2")) return;
  if(!makeCut(_nBJets==0,"n_{bjets} = 0")) return;

  // for the moment is not fully exclusive with 3L but can be easily done by uncommenting these
  //  if(!makeCut((_HT<200 && _met->pt()>50 && _met->pt()<100) ||
  //	      (_HT>200 && _met->pt()<50),"MET cut  ")) return;
  if(!makeCut(_met->pt()>50, "MET > 50 GeV")) return;


  //Scale factors =======================
  _susyMod->applySingleLepSF(_l1Cand, _weight);
  _susyMod->applySingleLepSF(_l2Cand, _weight);
  // ====================================

  fillhistos();//fill histos for kWZCR
    
  setWorkflow(kGlobal); 
}


//=====================================================================
// signal region selection

void 
SSDL2015::setSignalRegions() {
    
  //objects ===========================================
  _val["NB"]  = &(_nBJets);
  _val["MT"]  = &(_mTmin);
  _val["MET"] = &(_metPt);
  _val["NJ"]  = &(_nJets);
  _val["HT"]  = &(_HT);

  string HThighBound="1125";
  string METhighBound="300";

  //HH-regions =============================================================
  //0b-jet =================================================================
  if( _SR== "HH SR1" ) {
    setSelLine("LL:=:hh|NB:=:0|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:<:300");
  }
  else if( _SR== "HH SR2" ) {
    setSelLine("LL:=:hh|NB:=:0|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR3" ) {
    setSelLine("LL:=:hh|NB:=:0|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:<:300");
    setSelLine("LL:=:hh|NB:=:0|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:<:300");
    setSelLine("LL:=:hh|NB:=:0|MT:>=:120|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HH SR4" ) {
    setSelLine("LL:=:hh|NB:=:0|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR5" ) {
    setSelLine("LL:=:hh|NB:=:0|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR6" ) {
    setSelLine("LL:=:hh|NB:=:0|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR7" ) {
    setSelLine("LL:=:hh|NB:=:0|MT:>=:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR8" ) {
    setSelLine("LL:=:hh|NB:=:0|MT:>=:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
    setSelLine("LL:=:hh|NB:=:0|MT:>=:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:[]:300:"+HThighBound);
  }

 //1b-jet =================================================================
  else if( _SR== "HH SR9" ) {
    setSelLine("LL:=:hh|NB:=:1|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:<:300");
  }
  else if( _SR== "HH SR10" ) {
    setSelLine("LL:=:hh|NB:=:1|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR11" ) {
    setSelLine("LL:=:hh|NB:=:1|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:<:300");
    setSelLine("LL:=:hh|NB:=:1|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:<:300");
    setSelLine("LL:=:hh|NB:=:1|MT:>=:120|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HH SR12" ) {
    setSelLine("LL:=:hh|NB:=:1|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR13" ) {
    setSelLine("LL:=:hh|NB:=:1|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR14" ) {
    setSelLine("LL:=:hh|NB:=:1|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR15" ) {
    setSelLine("LL:=:hh|NB:=:1|MT:>=:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR16" ) {
    setSelLine("LL:=:hh|NB:=:1|MT:>=:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
    setSelLine("LL:=:hh|NB:=:1|MT:>=:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:[]:300:"+HThighBound);
  }
  
  //2b-jet =================================================================
 else if( _SR== "HH SR17" ) {
    setSelLine("LL:=:hh|NB:=:2|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:<:300");
  }
  else if( _SR== "HH SR18" ) {
    setSelLine("LL:=:hh|NB:=:2|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR19" ) {
    setSelLine("LL:=:hh|NB:=:2|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:<:300");
    setSelLine("LL:=:hh|NB:=:2|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:<:300");
    setSelLine("LL:=:hh|NB:=:2|MT:>=:120|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HH SR20" ) {
    setSelLine("LL:=:hh|NB:=:2|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR21" ) {
    setSelLine("LL:=:hh|NB:=:2|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR22" ) {
    setSelLine("LL:=:hh|NB:=:2|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR23" ) {
    setSelLine("LL:=:hh|NB:=:2|MT:>=:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR24" ) {
    setSelLine("LL:=:hh|NB:=:2|MT:>=:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
    setSelLine("LL:=:hh|NB:=:2|MT:>=:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:[]:300:"+HThighBound);
  }
  
  //3b-jet =================================================================
  else if( _SR== "HH SR25" ) {
    setSelLine("LL:=:hh|NB:>=:3|MT:<:120|MET:[]:50:200|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HH SR26" ) {
    setSelLine("LL:=:hh|NB:>=:3|MT:<:120|MET:[]:50:200|NJ:>=:2|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR27" ) {
    setSelLine("LL:=:hh|NB:>=:3|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HH SR28" ) {
    setSelLine("LL:=:hh|NB:>=:3|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HH SR29" ) {
    setSelLine("LL:=:hh|NB:>=:3|MT:>=:120|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HH SR30" ) {
    setSelLine("LL:=:hh|NB:>=:3|MT:>=:120|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:[]:300:"+HThighBound);
  }
  
  //inclusive H-MET ==========================================================
  else if( _SR== "HH SR31" ) {
    //setSelLine("LL:=:hh|MET:>=:500|NJ:>=:2|HT:>=:300"); //10fb-1
    setSelLine("LL:=:hh|MET:>=:300|NJ:>=:2|HT:>=:300"); //3 fb-1
  }

  //inclusive H-HT ==========================================================
  else if( _SR== "HH SR32" ) {
    //setSelLine("LL:=:hh|MET:[]:50:500|NJ:>=:2|HT:>=:1600"); //10fb-1
    setSelLine("LL:=:hh|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:>=:1125"); //3 fb-1
  }

  
  //HL-regions =============================================================
  //0b-jet =================================================================
  else if( _SR== "HL SR1" ) {
    setSelLine("LL:=:hl|NB:=:0|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:<:300");
  }
  else if( _SR== "HL SR2" ) {
    setSelLine("LL:=:hl|NB:=:0|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR3" ) {
    setSelLine("LL:=:hl|NB:=:0|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:<:300");
    setSelLine("LL:=:hl|NB:=:0|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HL SR4" ) {
    setSelLine("LL:=:hl|NB:=:0|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR5" ) {
    setSelLine("LL:=:hl|NB:=:0|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR6" ) {
    setSelLine("LL:=:hl|NB:=:0|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  
  //1b-jet =================================================================
 else if( _SR== "HL SR7" ) {
    setSelLine("LL:=:hl|NB:=:1|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:<:300");
  }
  else if( _SR== "HL SR8" ) {
    setSelLine("LL:=:hl|NB:=:1|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR9" ) {
    setSelLine("LL:=:hl|NB:=:1|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:<:300");
    setSelLine("LL:=:hl|NB:=:1|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HL SR10" ) {
    setSelLine("LL:=:hl|NB:=:1|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR11" ) {
    setSelLine("LL:=:hl|NB:=:1|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR12" ) {
    setSelLine("LL:=:hl|NB:=:1|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  
  //2b-jet =================================================================
  else if( _SR== "HL SR13" ) {
    setSelLine("LL:=:hl|NB:=:2|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:<:300");
  }
  else if( _SR== "HL SR14" ) {
    setSelLine("LL:=:hl|NB:=:2|MT:<:120|MET:[]:50:200|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR15" ) {
    setSelLine("LL:=:hl|NB:=:2|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:<:300");
    setSelLine("LL:=:hl|NB:=:2|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HL SR16" ) {
    setSelLine("LL:=:hl|NB:=:2|MT:<:120|MET:[]:50:200|NJ:>=:5|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR17" ) {
    setSelLine("LL:=:hl|NB:=:2|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:[]:2:4|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR18" ) {
    setSelLine("LL:=:hl|NB:=:2|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:5|HT:[]:300:"+HThighBound);
  }

  //3+b-jet =================================================================
  else if( _SR== "HL SR19" ) {
    setSelLine("LL:=:hl|NB:>=:3|MT:<:120|MET:[]:50:200|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HL SR20" ) {
    setSelLine("LL:=:hl|NB:>=:3|MT:<:120|MET:[]:50:200|NJ:>=:2|HT:[]:300:"+HThighBound);
  }
  else if( _SR== "HL SR21" ) {
    setSelLine("LL:=:hl|NB:>=:3|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HL SR22" ) {
    setSelLine("LL:=:hl|NB:>=:3|MT:<:120|MET:[]:200:"+METhighBound+"|NJ:>=:2|HT:[]:300:"+HThighBound);
  }

  //inclusive H-MT =============================================================
  else if( _SR== "HL SR23" ) {
    setSelLine("LL:=:hl|MT:>=:120|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:<:300");
  }
  else if( _SR== "HL SR24" ) {
    setSelLine("LL:=:hl|MT:>=:120|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:[]:300:"+HThighBound);
  }
  
  //inclusive H-MET ==========================================================
  else if( _SR== "HL SR25" ) {
    setSelLine("LL:=:hl|MET:>=:"+METhighBound+"|NJ:>=:2|HT:>=:300");
  }
  
  //inclusive H-HT ==========================================================
  else if( _SR== "HL SR26" ) {
    //setSelLine("LL:=:hl|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:>=:1600"); //10 fb-1
    setSelLine("LL:=:hl|MET:[]:50:"+METhighBound+"|NJ:>=:2|HT:>=:1125"); //3 fb-1
  }


  //LL-regions =============================================================
  else if( _SR== "LL SR1" ) {
    setSelLine("LL:=:ll|NB:=:0|MT:<:120|MET:[]:50:200|NJ:>=:2|HT:>:300");
  }
  else if( _SR== "LL SR2" ) {
    setSelLine("LL:=:ll|NB:=:0|MT:<:120|MET:>:200|NJ:>=:2|HT:>:300");
  }
  else if( _SR== "LL SR3" ) {
    setSelLine("LL:=:ll|NB:=:1|MT:<:120|MET:[]:50:200|NJ:>=:2|HT:>:300");
  }
  else if( _SR== "LL SR4" ) {
    setSelLine("LL:=:ll|NB:=:1|MT:<:120|MET:>:200|NJ:>=:2|HT:>:300");
  }
  else if( _SR== "LL SR5" ) {
    setSelLine("LL:=:ll|NB:=:2|MT:<:120|MET:[]:50:200|NJ:>=:2|HT:>:300");
  }
  else if( _SR== "LL SR6" ) {
    setSelLine("LL:=:ll|NB:=:2|MT:<:120|MET:>:200|NJ:>=:2|HT:>:300");
  }
 else if( _SR== "LL SR7" ) {
    setSelLine("LL:=:ll|NB:>=:3|MT:<:120|MET:>=:50|NJ:>=:2|HT:>:300");
  }
  else if( _SR== "LL SR8" ) {
    setSelLine("LL:=:ll|MT:>=:120|MET:>=:50|NJ:>=:2|HT:>:300");
  }



  //baselines =============================================================
  //so stupid.....
  else if( _SR== "BR0H" ) {
    setSelLine("LL:=:hh|NB:>=:0|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hh|NB:>=:0|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR0M" ) {
    setSelLine("LL:=:hl|NB:>=:0|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hl|NB:>=:0|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR0L" ) {
    setSelLine("LL:=:ll|NB:>=:0|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:ll|NB:>=:0|NJ:>=:2|HT:>=:500");
  }

 else if( _SR== "BR00H" ) {
    setSelLine("LL:=:hh|NB:=:0|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hh|NB:=:0|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR00M" ) {
    setSelLine("LL:=:hl|NB:=:0|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hl|NB:=:0|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR00L" ) {
    setSelLine("LL:=:ll|NB:=:0|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:ll|NB:=:0|NJ:>=:2|HT:>=:500");
  }

 else if( _SR== "BR10H" ) {
    setSelLine("LL:=:hh|NB:=:1|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hh|NB:=:1|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR10M" ) {
    setSelLine("LL:=:hl|NB:=:1|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hl|NB:=:1|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR10L" ) {
    setSelLine("LL:=:ll|NB:=:1|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:ll|NB:=:1|NJ:>=:2|HT:>=:500");
  }

  else if( _SR== "BR20H" ) {
    setSelLine("LL:=:hh|NB:=:2|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hh|NB:=:2|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR20M" ) {
    setSelLine("LL:=:hl|NB:=:2|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hl|NB:=:2|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR20L" ) {
    setSelLine("LL:=:ll|NB:=:2|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:ll|NB:=:2|NJ:>=:2|HT:>=:500");
  }

 else if( _SR== "BR30H" ) {
    setSelLine("LL:=:hh|NB:>=:3|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hh|NB:>=:3|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR30M" ) {
    setSelLine("LL:=:hl|NB:>=:3|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:hl|NB:>=:3|NJ:>=:2|HT:>=:500");
  }
  else if( _SR== "BR30L" ) {
    setSelLine("LL:=:ll|NB:>=:3|MET:>:30|NJ:>=:2|HT:<:500");
    setSelLine("LL:=:ll|NB:>=:3|NJ:>=:2|HT:>=:500");
  }




}

void
SSDL2015::setSelLine(string str) {

  //MM could be done in a better way

  //parsing full selection into variable selections
  stringstream ss(str);
  string item;
  string tk;
  
  vector<vector<string> > sel;
  while (std::getline(ss, item, '|')) {
    
    vector<string> vars(4,"");
    stringstream sssel( item );
  
    int n=0;
    while (std::getline(sssel, tk, ':')) {
      vars[n]= (tk);
      n++;
    }

    if(vars.size()==3)
      vars.push_back("");

    sel.push_back(vars);
  }

  _sels[_SR].push_back( sel );
}


//================================================
bool 
SSDL2015::genMatchedToFake(int idx) {

  if (_vc->get("isData")==1) return false;

  int id1  = _vc->get("LepGood_mcMatchId" ,idx); 
  if(id1==0 || id1==100) return true;

  return false;
}

bool
SSDL2015::genMatchedMisCharge() {

  if (_vc->get("isData")==1) return false;
  
  int mid1=_vc->get("LepGood_mcMatchId" ,_idxL1);
  int mid2=_vc->get("LepGood_mcMatchId" ,_idxL2);
  
  //DY case
  if(mid1==23 && mid2==23 && 
     _l1Cand->pdgId()*_l2Cand->pdgId()>0 ) {
    return true;
  }
  if(std::abs(mid1)==24 && std::abs(mid2)==24 &&
     _l1Cand->pdgId()*_l2Cand->pdgId()>0 ) {
    return true;
  }
   
  return false;
}

int 
SSDL2015::genMatchCateg(const Candidate* cand) {

  // //loop over the number of generated leptons
  // int nGenL = _vc->get("nGenPart");

  // for(int ig = 0; ig < nGenL; ++ig) {
	
  //   if(Tools::dR(cand->eta(), _vc->get("GenPart_eta", ig),
  // 		 cand->phi(), _vc->get("GenPart_phi", ig) ) < 0.05 ) { //to be tuned
		  		
  //     //if( genMatchedToFake(idx) ) return kMisMatchPdgId; //taus are exception to the rule
  //     else if(cand->pdgId()*_vc->get("GenPart_pdgId",ig) < 0 ) return kMisChargePdgId; //+*- = -...
  //     else return kGenMatched;
			
  //     break;
  //   } //dr matching
  // } //gen loop
	
  return kNoGenMatch;
}

bool
SSDL2015::passGenSelection() {

  if( _sampleName.find("DYJets")!=(size_t)-1 || _sampleName.find("TTJets")!=(size_t)-1 ) {
    
    if(_sampleName.find("charge")!=(size_t)-1) {
      if( !genMatchedMisCharge() )
	return false;
    }
    else if(_sampleName.find("fake")!=(size_t)-1) {
      if(!genMatchedToFake(_idxL1) && !genMatchedToFake(_idxL2) ) return false;
    }
    else {
      //if( genMatchedToFake(_idxL1) || genMatchedToFake(_idxL2) ) return false;
      //cout<<" passing prompt "<<endl;
    }

  }
  
  return true;
}


float 
SSDL2015::getFR(Candidate* cand, int idx) {
  string db;
  //int wp=SusyModule::kTight;
  float ptM=10;
  if( std::abs(cand->pdgId())==13) db="Mu";
  else { db="El"; ptM=15;}
  
  if(_HT<300) db+= "Iso";
  else db += "NIso";

  if(_vc->get("isData")!=1) db +="MC";

  float ptVal=cand->pt();
  float etaVal=std::abs(cand->eta());
  
  if(_FR.find("C")!=string::npos) ptVal=std::max(_susyMod->conePt(idx), (float)ptM);
  if(_FR.find("J")!=string::npos) ptVal/=_vc->get("LepGood_jetPtRatiov2", idx);

  ptVal=std::max(ptVal, ptM);
  // cout<<" ====> "<<cand->pt()<<" / "<<cand->eta()<<" => "<<_dbm->getDBValue(db, std::min( ptVal,(float)69.9),
  // 									    std::min(std::abs(cand->eta()),(float)2.49) )<<endl;

  // if(_dbm->getDBValue(db, std::min( ptVal,(float)69.9),
  // 		      std::min(std::abs(cand->eta()),(float)2.49) ) == 1)
  //   cout<<cand->pt()<<"  "<<ptVal<<"   "<<_dbm->getDBValue(db, std::min( ptVal,(float)69.9),
  // 							   std::min(std::abs(cand->eta()),(float)2.49) )<<endl;

  return _dbm->getDBValue(db, std::min( ptVal,(float)69.9),
			  std::min(etaVal,(float)2.49) );
}



void
SSDL2015::chargeFlipProb() {

  string db="chargeMId";
  if(!_vc->get("isData") ) db="chargeMIdMC";

  float w=0;
  for(unsigned int i=0;i<_auxPairs.size();i++) {

    if(_auxFlags[i]!=kIsOS) continue;

    float p1=_dbm->getDBValue(db, _auxPairs[i][0]->pt(), std::abs(_auxPairs[i][0]->eta()));
    float p2=_dbm->getDBValue(db, _auxPairs[i][1]->pt(), std::abs(_auxPairs[i][1]->eta()));

    if(p1>0.01) p1=0.0005;
    if(p2>0.01) p2=0.0005;

    w += (p1+p2-2*p1*p2)/(p1*p2+(1-p1)*(1-p2) );
  }
  
  _weight *= w;
}



//===============================================================
//===============================================================
bool
SSDL2015::testRegion() {

  bool passSel=true;

  for(size_t is=0;is<_sels[_SR].size();is++) {
    passSel=true;
    //cout<<"new region ================== "<<_SR<<endl;
    for(size_t ii=0;ii<_sels[_SR][is].size();ii++) {
    
      //cout<<_sels[_SR][is][ii][0]<<" >> "<<_l1Cand->pt()<<"  "<<_l2Cand->pt()<<"  "<<passHLT("DL")<<"  "<<passHLT("DLHT")<<endl;

      if(_sels[_SR][is][ii][0]=="LL") { //lepton pt scheme, specific case 
	if(_sels[_SR][is][ii][2]=="hh" && 
	   (_l1Cand->pt()<25 || _l2Cand->pt()<25) ) {passSel=false;break;} // || !passHLT("DL")
	if(_sels[_SR][is][ii][2]=="hl" &&
	   ( (_l1Cand->pt()<25 && _l2Cand->pt()<25) ||
	     (_l1Cand->pt()>=25 && _l2Cand->pt()>=25) ) ) {passSel=false;break;} // || !passHLT("DL")
	if(_sels[_SR][is][ii][2]=="ll" && 
	   (_l1Cand->pt()>=25 || _l2Cand->pt()>=25 ) ) {passSel=false;break;} // || !passHLT("DLHT")
      
      }
      else { //all other selections

	//cout<<":: "<<_sels[_SR][is][ii][0]<<" :: "<<(*(_val[_sels[_SR][is][ii][0] ]))<<" "<<_sels[_SR][is][ii][1]<<" "<<atof(_sels[_SR][is][ii][2].c_str() )<<"  "<<atof(_sels[_SR][is][ii][3].c_str())<<endl;

	//bool dec=(_au->simpleCut<float>( (*(_val[_sels[_SR][is][ii][0] ])) , atof(_sels[_SR][is][ii][2].c_str() ), _sels[_SR][is][ii][1], atof(_sels[_SR][is][ii][3].c_str()) ));
	if(!_au->simpleCut<float>( (*(_val[_sels[_SR][is][ii][0] ])) , atof(_sels[_SR][is][ii][2].c_str() ),
				   _sels[_SR][is][ii][1], atof(_sels[_SR][is][ii][3].c_str()) ) ) 
	  {passSel=false;break;}
      }
      
    }
    //cout<<" --> passing selection? "<<passSel<<endl;
    if(passSel) return true;
  }

  return false;
}


void
SSDL2015::categorize() {

  int offset=1;
  string categ="";
  for(size_t ic=0;ic< _categs.size();ic++) {
    _SR = _categs[ic];
    if(testRegion() ) {setWorkflow(ic+offset); return;}
  }
  std::cout << "WARNING: SSDL2015::categorize() did not find any workflow that matches this event. The workflow returns to kGlobal what may cause problems with the histograms" << std::endl;
  std::cout<<"====> "<<_looseLepsPtCut.size()<<" / "<<_tightLepsPtCut.size()<<" / "<<_nJets<<" / "<<_nBJets<<" / "<<hltSelection()<<" / "<<_met->pt()<<" / "<<_HT<<" / "<<_vc->get("evt")<<" / "<<_vc->get("lumi")<<std::endl;
  setWorkflow(kGlobal);
}

bool
SSDL2015::hltSelection() {
  _hltDLHT=false;
  if(passHLT("DL") ) {
    _hltDLHT=false;
    //  return true;
  }
  else {
    _hltDLHT=true;
    // return true;
  }
  //priority to DiLeps lines

  bool ee=false;
  bool mm=false;
  bool em=false;

  // cout<<_vc->get("HLT_MuEG")<<"  "<<(_HT>300)<<"  "<<((_vc->get("HLT_MuEG") || _HT>300))<<"  "<<_HT<<endl;
  // cout<<_vc->get("HLT_MuEGHT")<<"  "<<(_HT<300)<<"  "<<((_vc->get("HLT_MuEG") || _HT<300))<<endl;
  // cout<<((_vc->get("HLT_MuEG") || _HT>300) && (_vc->get("HLT_MuEGHT") || _HT<300))<<endl;

  // cout<<_vc->get("HLT_DoubleEl")<<"  "<<(_HT>300)<<"  "<<((_vc->get("HLT_DoubleEl") || _HT>300))<<"  "<<_HT<<endl;
  // cout<<_vc->get("HLT_DoubleElHT")<<"  "<<(_HT<300)<<"  "<<((_vc->get("HLT_DoubleEl") || _HT<300))<<endl;
  // cout<<((_vc->get("HLT_DoubleEl") || _HT>300) && (_vc->get("HLT_DoubleElHT") || _HT<300))<<endl;

  // cout<<_vc->get("HLT_DoubleMu")<<"  "<<(_HT>300)<<"  "<<((_vc->get("HLT_DoubleMu") || _HT>300))<<"  "<<_HT<<endl;
  // cout<<_vc->get("HLT_DoubleMuHT")<<"  "<<(_HT<300)<<"  "<<((_vc->get("HLT_DoubleMu") || _HT<300))<<endl;
  // cout<<((_vc->get("HLT_DoubleMu") || _HT>300) && (_vc->get("HLT_DoubleMuHT") || _HT<300))<<endl;




  ee= (_flav==22 && ((_vc->get("HLT_DoubleEl") || _HT>300) && (_vc->get("HLT_DoubleElHT") || _HT<300)));
  mm= (_flav==26 &&((_vc->get("HLT_DoubleMu") || _HT>300) && (_vc->get("HLT_DoubleMuHT") || _HT<300)) );
  em= (_flav==24 &&((_vc->get("HLT_MuEG") || _HT>300) && (_vc->get("HLT_MuEGHT") || _HT<300)));
  
  //cout<<_flav<<"  "<<ee<<"  "<<mm<<"  "<<em<<"  "<<_isOS<<endl;
  

  if(ee|| mm || em) return true;

  return false;
}

bool
SSDL2015::passHLT(string id) {

  if(id=="DL") { //pure dilepton triggers
    if(_vc->get("HLT_DoubleEl") ) return true;
    if(_vc->get("HLT_DoubleMu") ) return true;
    if(_vc->get("HLT_MuEG") ) return true;
  }
  else if(id=="DLHT") {
    if(_vc->get("HLT_DoubleElHT") ) return true;
    if(_vc->get("HLT_DoubleMuHT") ) return true;
    if(_vc->get("HLT_MuEGHT") ) return true;
  }

    return false;
}


bool 
SSDL2015::looseLepton(const Candidate* c, int idx, int pdgId) {

  if(abs(pdgId)==13) {//mu case
    if(!_susyMod->muIdSel(c, idx, SusyModule::kLoose) ) return false;
    if(!_susyMod->multiIsoSel(idx, SusyModule::kDenom) ) return false;
  }
  else {
    if(!_susyMod->elIdSel(c, idx, SusyModule::kLoose, SusyModule::kLoose) ) return false;
    if(!_susyMod->multiIsoSel(idx, SusyModule::kDenom) ) return false; //denom on purpose
    if(!_susyMod->elHLTEmulSel(idx, false ) ) return false; //_hltDLHT
  }

  return true;
}

bool 
SSDL2015::tightLepton(const Candidate*c, int idx, int pdgId) {

  if(abs(pdgId)==13) {//mu case
    if(!_susyMod->muIdSel(c, idx, SusyModule::kTight) ) return false;
    if(!_susyMod->multiIsoSel(idx, SusyModule::kMedium) ) return false;
  }
  else {
    //cout<<" 0 "<<endl;
    if(!_susyMod->elIdSel(c, idx, SusyModule::kTight, SusyModule::kTight) ) return false; //   cout<<" 1 "<<endl;
    if(!_susyMod->multiIsoSel(idx, SusyModule::kTight) ) return false;  //  cout<<" 2 "<<endl;
    if(!_susyMod->elHLTEmulSel(idx, (_HT<300) ) ) return false; //_hltDLHT
    //cout<<" 3 "<<endl;
  }

  return true;
}


bool 
SSDL2015::fakableLepton(const Candidate* c, int idx, int pdgId, bool bypass) {

  if(abs(pdgId)==13) {//mu case
    if(!_susyMod->muIdSel(c, idx, SusyModule::kTight) ) return false;
    if(!_susyMod->multiIsoSel(idx, SusyModule::kDenom) ) return false;
    
    if(_FR.find("FO4")!=string::npos && !_susyMod->invMultiIsoSel(idx, SusyModule::kSpecFakeMu) ) return false;
  }
  else {
    int elMva=(_HT<300)?SusyModule::kLooseHT:SusyModule::kLoose;
    if(bypass) elMva=SusyModule::kLoose;
    bool hltDLHT=bypass?false:(_HT<300);//_hltDLHT;
    
    // cout<<idx<<" ===> "<<_susyMod->multiIsoSel(idx, SusyModule::kDenom)<<"  "
    // 	<<_susyMod->elHLTEmulSel(idx, hltDLHT )<<"   "
    // 	<<_susyMod->elIdSel(idx, SusyModule::kTight, SusyModule::kTight )<<"  "
    // 	<<_susyMod->elIdSel(idx, SusyModule::kTight, elMva )<<endl;

  
    if(_FR.find("FO2")==string::npos && !_susyMod->elIdSel(c, idx, SusyModule::kTight, SusyModule::kTight )) return false;
    //cout<<" passing 1 "<<_hltDLHT<<" == "<<hltDLHT<<"   "<<(_HT<300)<<endl;
     if(_FR.find("FO2")!=string::npos && !_susyMod->elIdSel(c, idx, SusyModule::kTight, elMva )) return false;
     //cout<<" passing 2"<<endl;
     if(!_susyMod->multiIsoSel(idx, SusyModule::kDenom) ) return false;  //cout<<" passing 3"<<endl;
     if(!_susyMod->elHLTEmulSel(idx, hltDLHT ) ) return false;   //cout<<" passing 4"<<endl;
    
    if(_FR.find("FO4")!=string::npos && !_susyMod->invMultiIsoSel(idx, SusyModule::kSpecFakeEl) ) return false;
  }

  return true;
}




bool
SSDL2015::passCERNSelection() {

  if(!makeCut( _vc->get("nLepGood10_Mini"), "CERN lepmult" ) ) return false;
  if(!makeCut<float>( _vc->get("mZ1cut10TL_Mini"), 76 , "]![", "CERN Z veto",  106 ) ) return false;
  if(!makeCut<float>( _vc->get("minMllAFOSTL_Mini"), 0 , "]!]", "CERN g veto OS", 12) ) return false;
  if(!makeCut<float>( _vc->get("minMllAFASTL_Mini"), 8 , ">", "CERN g veto AS" ) ) return false;
     
// > = 2 good leptons: nLepGood10 >= 2
// minMllAS8:  minMllAFAS > 8
// minMllOS12: minMllAFOS <= 0 || minMllAFOS > 12
// zveto3l:    mZ1 < 76 || mZ1 > 106

     if(!makeCut( abs(_l1Cand->pdgId()) > 0 && abs(_l2Cand->pdgId()) > 0, "pdgId") ) return false;
     if(!makeCut( _l1Cand->charge()*_l2Cand->charge()>0, "charge") ) return false;
     if(!makeCut( _l1Cand->pt()>25 && _l2Cand->pt()>25, "pt") ) return false;
     
     //cout<<_l1Cand->pdgId()<<"  "<<_l2Cand->pdgId()<<"  "<<SusyModule::kMedium<<"  "<<SusyModule::kTight<<endl;

     int wp1 = SusyModule::kMedium;//((abs(_l1Cand->pdgId())==13)?(SusyModule::kMedium):SusyModule::kTight);
     int wp2 = SusyModule::kMedium;//((abs(_l2Cand->pdgId())==13)?(SusyModule::kMedium):SusyModule::kTight);
     if(abs(_l1Cand->pdgId())==13) wp1 = SusyModule::kTight;
     if(abs(_l2Cand->pdgId())==13) wp2 = SusyModule::kTight;


     // cout<<wp1<<"  "<<wp2<<"   "<<_idxL1<<"  "<<_idxL2<<"   "<< _susyMod->multiIsoSel(_idxL1, wp1 )
     // 	 <<"   "<<_susyMod->multiIsoSel(_idxL2, wp2 )<<endl;

     if(!makeCut( _susyMod->multiIsoSel(_idxL1, wp1 ), "iso1") ) return false;
     if(!makeCut( _susyMod->multiIsoSel(_idxL2, wp2 ), "iso2") ) return false;

     bool id= _vc->get("LepGood_mediumMuonId", _idxL1)>0 && 
              _vc->get("LepGood_mediumMuonId", _idxL2)>0;

     if(!makeCut(id, "id") ) return false;

     bool elId= ( _vc->get("LepGood_mvaIdPhys14",_idxL1) >=0.73+(0.57-0.73)*(abs(_l1Cand->eta())>0.8)+(+0.05-0.57)*(abs(_l1Cand->eta())>1.479) || abs(_l1Cand->pdgId()) == 13) && 
     ( _vc->get("LepGood_mvaIdPhys14",_idxL2) >=0.73+(0.57-0.73)*(abs(_l2Cand->eta())>0.8)+(+0.05-0.57)*(abs(_l2Cand->eta())>1.479) || abs(_l2Cand->pdgId()) == 13); 

     //cout<<_vc->get("LepGood_mvaIdPhys14",_idxL1)<<"   "<<_l1Cand->eta()<<"   "<<_vc->get("LepGood_mvaIdPhys14",_idxL2)<<"   "<<_l2Cand->eta()<<endl;

     if(!makeCut(elId, "elId") ) return false;

// exclusive:  nLepGood10 == 2
// anyll: abs(LepGood1_pdgId) > 0 && abs(LepGood2_pdgId) > 0
// same-sign: LepGood1_charge*LepGood2_charge > 0
// lep1_pt25: LepGood1_pt > 25 
// lep2_pt25: LepGood2_pt > 25 
// lep iso: multiIso_multiWP(LepGood1_pdgId,LepGood1_pt,LepGood1_eta,LepGood1_miniRelIso,LepGood1_jetPtRatio,LepGood1_jetPtRel,2) > 0 && 
//          multiIso_multiWP(LepGood2_pdgId,LepGood2_pt,LepGood2_eta,LepGood2_miniRelIso,LepGood2_jetPtRatio,LepGood2_jetPtRel,2) > 0
//lep mu id: LepGood1_mediumMuonId > 0 && LepGood2_mediumMuonId > 0 
// lep el id: ( LepGood1_mvaIdPhys14 >=0.73+(0.57-0.73)*(abs(LepGood1_eta)>0.8)+(+0.05-0.57)*(abs(LepGood1_eta)>1.479) || abs(LepGood1_pdgId) == 13) && 
//            ( LepGood2_mvaIdPhys14 >=0.73+(0.57-0.73)*(abs(LepGood2_eta)>0.8)+(+0.05-0.57)*(abs(LepGood2_eta)>1.479) || abs(LepGood2_pdgId) == 13) 

     // cout<<_idxL1<<"  "<<_idxL2<<"   "<<_vc->get("LepGood_sip3d",_idxL1)<<"   "<<_vc->get("LepGood_sip3d",_idxL2)<<endl;

     if(!makeCut( max(_vc->get("LepGood_sip3d",_idxL1),_vc->get("LepGood_sip3d",_idxL2)) < 4, "sip") ) return false;

     bool conv= (abs(_l1Cand->pdgId())==13 || (_vc->get("LepGood_convVeto",_idxL1) && _vc->get("LepGood_lostHits",_idxL1) == 0)) &&
                (abs(_l2Cand->pdgId())==13 || (_vc->get("LepGood_convVeto",_idxL2) && _vc->get("LepGood_lostHits",_idxL2) == 0));

     if(!makeCut(  conv, "conversion") ) return false;

     bool charge= (_vc->get("LepGood_tightCharge",_idxL1)> (abs(_l1Cand->pdgId())==11)) &&
		   (_vc->get("LepGood_tightCharge",_idxL2)> (abs(_l2Cand->pdgId())==11));

     if(!makeCut(  charge, "tight charge") ) return false;
     
  return true;

}
bool SSDL2015::ttbarSelection(){
  ///filters : hbheFilterNew25ns==1 && Flag_CSCTightHaloFilter==1 && Flag_eeBadScFilter==1
  ///trigger : HLT_DoubleMu || HLT_DoubleEl || HLT_MuEG
  ///nL : nLepGood >= 2
  ///EE_MuMu_MuE : LepGood1_pdgId == -LepGood2_pdgId || abs(LepGood1_pdgId+LepGood2_pdgId)==2
  ///pt2515 : LepGood1_pt>25 && LepGood2_pt>15
  ///mll > 12 : minMllAFAS > 12
  ///nJet40 : nJet40 >= 2
  ///nBJetMedium25 : nBJetMedium25 >= 1 || nBJetLoose25 == 2
  ///Z peak : abs(mZ1-91.2) > 10
  if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
  if (!(_vc->get("HLT_DoubleMu") || _vc->get("HLT_DoubleEl") || _vc->get("HLT_MuEG"))) return false;
  if (_vc->get("nLepGood") < 2) return false;
  _idxL1 = 0;
  _idxL2 = 1;
  if (!(_vc->get("LepGood_pdgId", _idxL1) == -_vc->get("LepGood_pdgId", _idxL2) || 
	abs(_vc->get("LepGood_pdgId", _idxL1)+_vc->get("LepGood_pdgId", _idxL2)) == 2)
      ) return false;
  if (_vc->get("LepGood_pt", _idxL1) < 25. || _vc->get("LepGood_pt", _idxL2) < 15.) return false;
  if (_vc->get("minMllAFAS") < 12.) return false;
  if (_vc->get("nJet40") < 2) return false;
  if (!(_vc->get("nBJetMedium25") >= 1 || _vc->get("nBJetLoose25") == 2)) return false; 
  if (abs(_vc->get("mZ1")-91.2) < 10.)  return false;
  
  return true;
}

bool SSDL2015::ZlSelection(){
  if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
  if (!(_vc->get("HLT_DoubleMu") || _vc->get("HLT_DoubleEl") || _vc->get("HLT_MuEG"))) return false;
  if (_vc->get("nLepGood10") !=3 ) return false;
  if (!(_vc->get("LepGood_pdgId", 0) == -_vc->get("LepGood_pdgId", 1))) return false;
  if (abs(_vc->get("mZ1")-91.2) > 15.) return false;
  
  Candidate* lep3=Candidate::create(_vc->get("LepGood_pt", 2),
				    _vc->get("LepGood_eta", 2),
				    _vc->get("LepGood_phi", 2),
				    _vc->get("LepGood_pdgId", 2),
				    _vc->get("LepGood_charge", 2),
				    0.105);
  float mT= Candidate::create(lep3, _met)->mass();
  
  if (mT > 55.) return false;
  if (_vc->get("minMllAFAS") < 12.) return false;
  if (_vc->get("LepGood_pt", 2) > 50.) return false;
  if (_vc->get("met_pt") > 60.) return false;

  _idxL1 = 0;
  _idxL2 = 2;
    
  return true;
}
bool SSDL2015::WlSelection(){
  if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
  if (!(_vc->get("HLT_SingleMu") || _vc->get("HLT_SingleEl"))) return false;
  if (_vc->get("nLepGood10") != 2) return false;
  if (_vc->get("LepGood_charge", 0)*_vc->get("LepGood_charge", 1) < 0) return false;
  
  _idxL1 = 0;
  _idxL2 = 1;
  
  bool charge= (_vc->get("LepGood_tightCharge",_idxL1) > (abs(_vc->get("LepGood_pdgId",_idxL1))==11))  && 
               (_vc->get("LepGood_tightCharge",_idxL2) > (abs(_vc->get("LepGood_pdgId",_idxL2))==11));
  
  if (!charge) return false;
  
  Candidate* lep=Candidate::create(_vc->get("LepGood_pt", _idxL1),
				   _vc->get("LepGood_eta", _idxL1),
				   _vc->get("LepGood_phi", _idxL1),
				   _vc->get("LepGood_pdgId", _idxL1),
				   _vc->get("LepGood_charge", _idxL1),
				   0.105);
  float mT= Candidate::create(lep, _met)->mass();

  if (_vc->get("LepGood_sip3d",_idxL1) > 4) return false;
  if (_vc->get("LepGood_relIso03",_idxL1) > 0.05) return false;
  if (_vc->get("LepGood_miniRelIso",_idxL1) > 0.05) return false;
  if (_vc->get("nBJetMedium25") != 0) return false;
  if (_vc->get("met_pt") < 30.) return false;
  if (mT < 40.) return false;

  if ((abs(_vc->get("LepGood_pdgId",_idxL1))==11 && abs(_vc->get("LepGood_pdgId",_idxL2))==11) && 
       (_vc->get("mZ1") > 76. && _vc->get("mZ1") < 106.))  return false;
  
  return true;
}

bool SSDL2015::ZMuMuSelection(){
  if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
  if (!(_vc->get("HLT_SingleMu"))) return false;
  if (_vc->get("nLepGood") < 2) return false;
  if (_vc->get("nLepGood10") != 2) return false;
  if (!(_vc->get("LepGood_pdgId", 0) == -_vc->get("LepGood_pdgId", 1))) return false;
  //  cout << _vc->get("LepGood_pdgId", 0)  << " = " << _vc->get("LepGood_pdgId", 1) << endl;
  if (abs(_vc->get("LepGood_pdgId", 0)) != 13) return false;
  if (_vc->get("mZ1") < 60. || _vc->get("mZ1") > 120.) return false;
  
  if (_vc->get("LepGood_charge", 0) < 0) {
    _idxL1 = 0;
    _idxL2 = 1;
  }
  else if (_vc->get("LepGood_charge", 1) < 0) {
    _idxL1 = 1;
    _idxL2 = 0;
  }
  
  if (_vc->get("LepGood_pt", _idxL1) < 20) return false;
  if (_vc->get("LepGood_relIso03", _idxL1) > 0.2 ) return false;
  if (abs(_vc->get("LepGood_eta", _idxL1)) > 2.1) return false;

  return true;
}

bool SSDL2015::ZEESelection(){
  if (_vc->get("hbheFilterNew25ns")==0 || _vc->get("Flag_CSCTightHaloFilter")==0 || _vc->get("Flag_eeBadScFilter")==0) return false;   
  if (!(_vc->get("HLT_SingleEl"))) return false;
  if (_vc->get("nLepGood") < 2) return false;
  if (!(_vc->get("LepGood_pdgId", 0) == -_vc->get("LepGood_pdgId", 1))) return false;
  if (abs(_vc->get("LepGood_pdgId", 0)) != 11) return false;
  if (_vc->get("mZ1") < 60. || _vc->get("mZ1") > 120.) return false;
  
  if (_vc->get("LepGood_charge", 0) < 0) {
    _idxL1 = 0;
    _idxL2 = 1;
  }
  else if (_vc->get("LepGood_charge", 1) < 0) {
    _idxL1 = 1;
    _idxL2 = 0;
  }
  
  if (_vc->get("LepGood_pt", _idxL1) < 30) return false;
  if (_vc->get("LepGood_relIso03", _idxL1) > 0.2 ) return false;
  if (abs(_vc->get("LepGood_eta", _idxL1)) > 2.1) return false;
  
  return true;
}

//===========================================================================
// void
// SSDL2015::selectLeptons() {

//   for(size_t il=0;il<_vc->get("nLepGood"); il++) {

//     bool isMu=std::abs(_vc->get("LepGood_pdgId", il))==13;

//     Candidate* cand=Candidate::create(_vc->get("LepGood_pt", il),
// 				      _vc->get("LepGood_eta", il),
// 				      _vc->get("LepGood_phi", il),
// 				      _vc->get("LepGood_pdgId", il),
// 				      _vc->get("LepGood_charge", il),
// 				      isMu?0.105:0.0005);
    
//      // cout<<il<<" ---> "<<" pt: "<<cand->pt()<<"  eta: "<<cand->eta()<<"   phi: "<<cand->phi()
//      // 	<<"  pdgId: "<<_vc->get("LepGood_pdgId", il)<<"   dxy: "
//      // 	<<_vc->get("LepGood_dxy",il)<<"  dz: "<<_vc->get("LepGood_dz",il)<<"   "<<_vc->get("LepGood_tightCharge", il)<<"   "<<_vc->get("LepGood_sip3d",il)<<endl;

//     if(!looseLepton(cand, il, cand->pdgId() ) ) continue;
//     _looseLeps.push_back(cand);
//     _looseLepsIdx.push_back(il);
    
//     //cout<<" -> selected"<<endl;
//     //continue;
//     //if((isMu && cand->pt()<10) || (!isMu && cand->pt()<15)) continue;
//     _looseLeps10.push_back(cand);
//     _looseLeps10Idx.push_back(il);
    
//   }

//   //Fake case with pt corrected ========================
//   //cout<<" =================== "<<endl;
//   for(size_t il=0;il<_vc->get("nLepGood"); il++) {

//     bool isMu=std::abs(_vc->get("LepGood_pdgId", il))==13;
//     Candidate* cand=Candidate::create( _susyMod->conePt(il),   //_vc->get("LepGood_pt", il),
// 				       _vc->get("LepGood_eta", il),
// 				       _vc->get("LepGood_phi", il),
// 				       _vc->get("LepGood_pdgId", il),
// 				       _vc->get("LepGood_charge", il),
// 				       isMu?0.105:0.0005);

//     Candidate* cand2=Candidate::create( _vc->get("LepGood_pt", il),
// 					_vc->get("LepGood_eta", il),
// 					_vc->get("LepGood_phi", il),
// 					_vc->get("LepGood_pdgId", il),
// 					_vc->get("LepGood_charge", il),
// 					isMu?0.105:0.0005);
    
//     if(!looseLepton(cand, il, cand2->pdgId() ) ) continue;

//     if((isMu && cand2->pt()<10) continue;
//     if((isMu && cand->pt()<10) || (!isMu && cand->pt()<15)) continue;
//     _looseLepsPtCorr10.push_back(cand);
//     _looseLepsPtCorr10Idx.push_back(il);    
//   }
//   //cout<<" =================== end"<<endl;

//   //OS case with no Z Veto!======================
//   for(size_t il=0;il<_looseLeps10.size();il++) {
//     if(!tightLepton(_looseLeps10[il], _looseLeps10Idx[il], _looseLeps10[il]->pdgId())) continue;
//     if(!_susyMod->passMllMultiVeto( _looseLeps10[il], &_looseLeps, 0, 12, true) ) continue;
    
//     _tightLepsOS10.push_back(_looseLeps10[il]);
//     _tightLepsOS10Idx.push_back(_looseLeps10Idx[il]);
//   }

//   //veto on loose leptons =====================
//   for(size_t il=0;il<_looseLeps.size();il++) {

//     // cout<<" pt:"<<_looseLeps[il]->pt()<<"  selected"<<"  "<<_susyMod->passMllMultiVeto( _looseLeps[il], &_looseLeps, 76, 106, true)<<"  "<<_susyMod->passMllMultiVeto( _looseLeps[il], &_looseLeps, 0, 12, true)<<endl;

//     if(!_susyMod->passMllMultiVeto( _looseLeps[il], &_looseLeps, 76, 106, true) ||
//        !_susyMod->passMllMultiVeto( _looseLeps[il], &_looseLeps, 0, 12, true) ) continue;
    
//     _looseLepsVeto.push_back( _looseLeps[il]);
//     _looseLepsVetoIdx.push_back(_looseLepsIdx[il]);
//   }
//   //  return;
//   //veto on loose leptons 10, likely the one to use for the fakes =====================
//   for(size_t il=0;il<_looseLeps10.size();il++) {
//     if(!_susyMod->passMllMultiVeto( _looseLeps10[il], &_looseLeps, 76, 106, true) ||
//        !_susyMod->passMllMultiVeto( _looseLeps10[il], &_looseLeps, 0, 12, true) ) continue;

//     _looseLepsVeto10.push_back(_looseLeps10[il]);
//     _looseLepsVeto10Idx.push_back(_looseLeps10Idx[il]);
//   }

//   for(size_t il=0;il<_looseLeps10.size();il++) {
//     if(!fakableLepton(_looseLeps10[il], _looseLeps10Idx[il], _looseLeps10[il]->pdgId(),true)) continue;
    
//     _jetCleanLeps10.push_back( _looseLeps10[il] );
//     _jetCleanLeps10Idx.push_back( _looseLeps10Idx[il] );
    
//     if(!_susyMod->passMllMultiVeto( _looseLeps10[il], &_looseLeps, 76, 106, true) ||
//        !_susyMod->passMllMultiVeto( _looseLeps10[il], &_looseLeps, 0, 12, true) ) continue;
//       _jetCleanLepsVeto10.push_back( _looseLeps10[il] );
//       _jetCleanLepsVeto10Idx.push_back( _looseLeps10Idx[il] );
//   }

//   _susyMod->cleanJets( &_jetCleanLeps10, _jets, _jetsIdx, _bJets, _bJetsIdx);//was looselep10 before
//   _HT=_susyMod->HT( &(_jets) );
  

//   //fakable leptons definitions ========================
//   //cout<<" =================== qui"<<endl;
//   for(size_t il=0;il<_looseLepsPtCorr10.size();il++) {
//     // cout<<" new lepton === "<<_looseLepsPtCorr10[il]->pt()<<"  "<<_vc->get("LepGood_pt",_looseLepsPtCorr10Idx[il])<<endl;
//     // cout<<"lepfake "<<il<<" : "<<_looseLepsPtCorr10[il]->pdgId()<<" ==>  "<<tightLepton(_looseLepsPtCorr10[il], _looseLepsPtCorr10Idx[il], _looseLepsPtCorr10[il]->pdgId())
//     // 	<<"    "<<fakableLepton(_looseLepsPtCorr10[il], _looseLepsPtCorr10Idx[il], _looseLepsPtCorr10[il]->pdgId(),false)
//     // 	<<"    "<<_susyMod->passMllMultiVeto( _looseLepsPtCorr10[il], &_looseLeps, 76, 106, true)
//     // 	<<"    "<<_susyMod->passMllMultiVeto( _looseLepsPtCorr10[il], &_looseLeps, 0, 12, true)<<endl;

//     if(!tightLepton(_looseLepsPtCorr10[il], _looseLepsPtCorr10Idx[il], _looseLepsPtCorr10[il]->pdgId())) {
//       if(!fakableLepton(_looseLepsPtCorr10[il], _looseLepsPtCorr10Idx[il], _looseLepsPtCorr10[il]->pdgId(),false)) continue; //not a fakable object

//       _fakableLeps10.push_back(_looseLepsPtCorr10[il]);
//       _fakableLeps10Idx.push_back(_looseLepsPtCorr10Idx[il]);
    
//       if(!_susyMod->passMllMultiVeto( _looseLepsPtCorr10[il], &_looseLeps, 76, 106, true) ||
// 	 !_susyMod->passMllMultiVeto( _looseLepsPtCorr10[il], &_looseLeps, 0, 12, true) ) continue;
//       _fakableLepsVeto10.push_back(_looseLepsPtCorr10[il]);
//       _fakableLepsVeto10Idx.push_back(_looseLepsPtCorr10Idx[il]);
    
//     }
//   }
  
//   //====================================================

 
//   //tight leptons definitions =================
//   //cout<<" =================== blu"<<endl;
//   for(size_t il=0;il<_looseLeps10.size();il++) {

//     if(!tightLepton(_looseLeps10[il], _looseLeps10Idx[il], _looseLeps10[il]->pdgId()))  continue;
//     if(std::abs(_looseLeps10Idx[il]->pdgId())==11 && _looseLeps10Idx[il]->pt()<15) continue;
    
//     _tightLeps10.push_back(_looseLeps10[il]);
//     _tightLeps10Idx.push_back(_looseLeps10Idx[il]);
    
//     if(!_susyMod->passMllMultiVeto( _looseLeps10[il], &_looseLeps, 76, 106, true) ||
//        !_susyMod->passMllMultiVeto( _looseLeps10[il], &_looseLeps, 0, 12, true) ) continue;
    
//     _tightLepsVeto10.push_back(_looseLeps10[il]);
//     _tightLepsVeto10Idx.push_back(_looseLeps10Idx[il]);
      
//   }// lepton loop
//   //cout<<" =================== blu end"<<endl;
//   //cout<<" size lepton ================== "<<_tightLepsVeto10.size()<<endl;
// }

void
SSDL2015::selectLeptons() {

  for(size_t il=0;il<_vc->get("nLepGood"); il++) {
    bool isMu=std::abs(_vc->get("LepGood_pdgId", il))==13;
    Candidate* cand=Candidate::create(_vc->get("LepGood_pt", il),
				      _vc->get("LepGood_eta", il),
				      _vc->get("LepGood_phi", il),
				      _vc->get("LepGood_pdgId", il),
				      _vc->get("LepGood_charge", il),
				      isMu?0.105:0.0005);
    
     // cout<<il<<" ---> "<<" pt: "<<cand->pt()<<"  eta: "<<cand->eta()<<"   phi: "<<cand->phi()
     // 	<<"  pdgId: "<<_vc->get("LepGood_pdgId", il)<<"   dxy: "
     // 	<<_vc->get("LepGood_dxy",il)<<"  dz: "<<_vc->get("LepGood_dz",il)<<"   "<<_vc->get("LepGood_tightCharge", il)<<"   "<<_vc->get("LepGood_sip3d",il)<<endl;

    if(!looseLepton(cand, il, cand->pdgId() ) ) continue;
    _looseLeps.push_back(cand);
    _looseLepsIdx.push_back(il);
    
    if(cand->pt()<10) continue;
    _looseLeps10.push_back(cand);
    _looseLeps10Idx.push_back(il);

    if((isMu && cand->pt()>10) || (!isMu && cand->pt()>15)) {
      _looseLepsPtCut.push_back(cand);
      _looseLepsPtCutIdx.push_back(il);
    }
    if((isMu && _susyMod->conePt(il)>10) || (!isMu && _susyMod->conePt(il)>15)) {
      _looseLepsPtCorrCut.push_back(cand);
      _looseLepsPtCorrCutIdx.push_back(il);
    }    
  }

   //OS case with no Z Veto!======================
  for(size_t il=0;il<_looseLepsPtCut.size();il++) {
    if(!tightLepton(_looseLepsPtCut[il], _looseLepsPtCutIdx[il], _looseLepsPtCut[il]->pdgId())) continue;
    if(!_susyMod->passMllMultiVeto( _looseLepsPtCut[il], &_looseLeps, 0, 12, true) ) continue;
    
     _tightLepsOSPtCut.push_back(_looseLepsPtCut[il]);
     _tightLepsOSPtCutIdx.push_back(_looseLepsPtCutIdx[il]);
  }

  //veto on loose leptons ptcut =====================
  for(size_t il=0;il<_looseLepsPtCut.size();il++) {
    
    if(!_susyMod->passMllMultiVeto( _looseLepsPtCut[il], &_looseLeps, 76, 106, true) ||
       !_susyMod->passMllMultiVeto( _looseLepsPtCut[il], &_looseLeps, 0, 12, true) ) continue;
    
    _looseLepsPtCutVeto.push_back( _looseLepsPtCut[il]);
    _looseLepsPtCutVetoIdx.push_back(_looseLepsPtCutIdx[il]);
  }

  //veto on loose leptons ptCorr cut ================
  for(size_t il=0;il<_looseLepsPtCorrCut.size();il++) {
    
    bool isMu=std::abs(_vc->get("LepGood_pdgId", il))==13;
    Candidate* cand=Candidate::create(_vc->get("LepGood_pt", _looseLepsPtCorrCutIdx[il]),
				      _vc->get("LepGood_eta", _looseLepsPtCorrCutIdx[il]),
				      _vc->get("LepGood_phi", _looseLepsPtCorrCutIdx[il]),
				      _vc->get("LepGood_pdgId", _looseLepsPtCorrCutIdx[il]),
				      _vc->get("LepGood_charge", _looseLepsPtCorrCutIdx[il]),
				      isMu?0.105:0.0005);

    if(!_susyMod->passMllMultiVeto( cand, &_looseLeps, 76, 106, true) ||
       !_susyMod->passMllMultiVeto( cand, &_looseLeps, 0, 12, true) ) continue;
    
    _looseLepsPtCorrCutVeto.push_back( _looseLepsPtCorrCut[il]);
    _looseLepsPtCorrCutVetoIdx.push_back(_looseLepsPtCorrCutIdx[il]);
  }

  //jet cleaning leptons =============================
  for(size_t il=0;il<_looseLeps10.size();il++) {
    if(!fakableLepton(_looseLeps10[il], _looseLeps10Idx[il], _looseLeps10[il]->pdgId(),true)) continue;
    
    _jetCleanLeps10.push_back( _looseLeps10[il] );
    _jetCleanLeps10Idx.push_back( _looseLeps10Idx[il] );
  }

  _susyMod->cleanJets( &_jetCleanLeps10, _jets, _jetsIdx, _bJets, _bJetsIdx, 40, 15);
  _HT=_susyMod->HT( &(_jets) );
  
  //fakable leptons definitions =======================
  for(size_t il=0;il<_looseLepsPtCorrCutVeto.size();il++) {
    if(tightLepton(_looseLepsPtCorrCutVeto[il], _looseLepsPtCorrCutVetoIdx[il],
		   _looseLepsPtCorrCutVeto[il]->pdgId())) continue;
    if(!fakableLepton(_looseLepsPtCorrCutVeto[il], _looseLepsPtCorrCutVetoIdx[il], _looseLepsPtCorrCutVeto[il]->pdgId(),false)) continue; //not a fakable object
    
    _fakableLepsPtCutVeto.push_back(_looseLepsPtCorrCutVeto[il]);
    _fakableLepsPtCutVetoIdx.push_back(_looseLepsPtCorrCutVetoIdx[il]);
  }

  //tight leptons definitions =========================
  for(size_t il=0;il<_looseLepsPtCut.size();il++) {

    if(!tightLepton(_looseLepsPtCut[il], _looseLepsPtCutIdx[il], _looseLepsPtCut[il]->pdgId()))  continue;
    
    _tightLepsPtCut.push_back(_looseLepsPtCut[il]);
    _tightLepsPtCutIdx.push_back(_looseLepsPtCutIdx[il]);

    if(!_susyMod->passMllMultiVeto( _looseLepsPtCut[il], &_looseLeps, 76, 106, true) ||
       !_susyMod->passMllMultiVeto( _looseLepsPtCut[il], &_looseLeps, 0, 12, true) ) continue;
    
    _tightLepsPtCutVeto.push_back(_looseLepsPtCut[il]);
    _tightLepsPtCutVetoIdx.push_back(_looseLepsPtCutIdx[il]);
      
  }



}


//==============================================
//MET uncertainty variation
TVector2
SSDL2015::varyMET() {

  unsigned int nJets=_vc->get("nJet");
  unsigned int nFwdJets=_vc->get("nJetFwd");
  if(!isInUncProc() ) {//first, store the jets
    _uncleanJets.clear();
    _uncleanFwdJets.clear();
    for(unsigned int ij=0;ij<nJets;ij++) { 
      TVector2 jet; jet.SetMagPhi( _vc->get("Jet_pt", ij), _vc->get("Jet_phi", ij)   );
      _uncleanJets.push_back(jet);
    }
    for(unsigned int ij=0;ij<nFwdJets;ij++) { 
      TVector2 jet; jet.SetMagPhi(_vc->get("JetFwd_pt", ij),_vc->get("JetFwd_phi", ij));
      _uncleanFwdJets.push_back(jet);
    }
  }
  
  TVector2 met; met.SetMagPhi(_vc->get("met_pt"), _vc->get("met_phi") );
  for(unsigned int ij=0;ij<nJets;ij++) { 
    //add back the standard jets
    met += _uncleanJets[ij];
    //JES varied jets
    TVector2 jet; jet.SetMagPhi( _vc->get("Jet_pt", ij), _vc->get("Jet_phi", ij)   );
    met -= jet;
  }
  for(unsigned int ij=0;ij<nFwdJets;ij++) { 
    //add back the standard jets
    met += _uncleanFwdJets[ij];
    //JES varied jets
    TVector2 jet; jet.SetMagPhi(_vc->get("JetFwd_pt", ij), _vc->get("JetFwd_phi", ij) );
    met -= jet;
  }
  
  return met;
}

void SSDL2015::fillhistos() {
  fill("l1Pt", (_idxFake==_idxL2)?(_l1Cand->pt()):_l2Cand->pt(), _weight );
  fill("l2Pt", (_idxFake==_idxL2)?(_l2Cand->pt()):_l1Cand->pt(), _weight );
  fill("HT"    , _HT       , _weight);
  fill("MET"   , _met->pt(), _weight);
  fill("MT"    , _mTmin        , _weight);
  fill("NBJets", _nBJets   , _weight);
  fill("NJets" , _nJets    , _weight);
}

void SSDL2015::fillValidationHistos(string reg){
  
  fill(reg+"_lep1_jetPtRatio", _vc->get("LepGood_jetPtRatiov2", _idxL1) , _weight);
  fill(reg+"_lep1_jetPtRel"  , _vc->get("LepGood_jetPtRelv2", _idxL1)               , _weight);
  fill(reg+"_lep1_miniRelIso", _vc->get("LepGood_miniRelIso", _idxL1)             , _weight);
  fill(reg+"_lep1_Pt"        , _vc->get("LepGood_pt", _idxL1)                     , _weight);
  fill(reg+"_lep1_Eta"       , fabs(_vc->get("LepGood_eta", _idxL1))              , _weight);
  fill(reg+"_lep1_SIP3D"     , _vc->get("LepGood_sip3d", _idxL1)                  , _weight);
  
  fill(reg+"_lep2_jetPtRatio", _vc->get("LepGood_jetPtRatiov2", _idxL2) , _weight);
  fill(reg+"_lep2_jetPtRel"  , _vc->get("LepGood_jetPtRelv2", _idxL2)               , _weight);
  fill(reg+"_lep2_miniRelIso", _vc->get("LepGood_miniRelIso", _idxL2)             , _weight);
  fill(reg+"_lep2_Pt"        , _vc->get("LepGood_pt", _idxL2)                     , _weight);
  fill(reg+"_lep2_Eta"       , fabs(_vc->get("LepGood_eta", _idxL2))              , _weight);
  fill(reg+"_lep2_SIP3D"     , _vc->get("LepGood_sip3d", _idxL2)                  , _weight);
   
  fill(reg+"_MET"            , _vc->get("met_pt")        , _weight);
  fill(reg+"_htJet40j"       , _vc->get("htJet40j")      , _weight);
  fill(reg+"_mZ1"            , _vc->get("mZ1")           , _weight);
  fill(reg+"_MTmin"          , _mTmin                    , _weight);
  fill(reg+"_NBJetsLoose25"  , _vc->get("nBJetLoose25")  , _weight);
  fill(reg+"_NBJetsMedium25" , _vc->get("nBJetMedium25") , _weight);
  fill(reg+"_NBJetsTight40"  , _vc->get("nBJetTight40")  , _weight);
  fill(reg+"_NJets40"        , _vc->get("nJet40")        , _weight);
}  


void
SSDL2015::fillEvents() {
// _events.push_back(1331274);
// _events.push_back(1860357);
//_events.push_back(4094628);//===
// _events.push_back(6000097);
// _events.push_back(6896086);
// _events.push_back(7729497);
// _events.push_back(7828608);
// _events.push_back(8053721);
// _events.push_back(8957199);
// _events.push_back(12178508);
// _events.push_back(12345756);
// _events.push_back(14329928);
// _events.push_back(14532696);
// _events.push_back(17800601);
// _events.push_back(20254586);
// _events.push_back(20860562);
// _events.push_back(23936240);
// _events.push_back(25929216);
// _events.push_back(26939364);
// _events.push_back(27332219);
// _events.push_back(28410914);
//_events.push_back(28910203);//===
// _events.push_back(32279981);
// _events.push_back(34525287);
//_events.push_back(34552720);//===
// _events.push_back(37553041);
// _events.push_back(38279201);
_events.push_back(41670828);//===
// _events.push_back(42499509);
// _events.push_back(43097002);
// _events.push_back(43139094);
// _events.push_back(44502365);
// _events.push_back(44711996);
// _events.push_back(45684115);
// _events.push_back(49452519);
// _events.push_back(51484564);
// _events.push_back(53418499);
// _events.push_back(53700482);
// _events.push_back(54635962);
// _events.push_back(56003125);
// _events.push_back(57622365);
//_events.push_back(62830693);//===
// _events.push_back(64505165);
// _events.push_back(64919594);
// _events.push_back(66450770);
// _events.push_back(66702675);
//_events.push_back(67804145);//===
// _events.push_back(69314356);
// _events.push_back(69990204);
// _events.push_back(71391223);
// _events.push_back(75325264);
// _events.push_back(76832152);
// _events.push_back(78632943);
// _events.push_back(85554780);
// _events.push_back(87643214);
// _events.push_back(88489265);
// _events.push_back(89102191);
// _events.push_back(91613825);
// _events.push_back(93606874);
// _events.push_back(95893452);
// _events.push_back(96438695);
// _events.push_back(100186367);
// _events.push_back(101906465);
// _events.push_back(103716364);
// _events.push_back(104031278);
// _events.push_back(105341710);
//_events.push_back(105857275);//===
// _events.push_back(110235537);
// _events.push_back(110723109);
// _events.push_back(111837109);
// _events.push_back(112281886);
// _events.push_back(113029657);
// _events.push_back(114858440);
// _events.push_back(115775184);
// _events.push_back(116606504);
// _events.push_back(116683124);
// _events.push_back(117654396);
// _events.push_back(122775293);
// _events.push_back(123730894);
// _events.push_back(124210711);
// _events.push_back(125659235);
// _events.push_back(127272170);
// _events.push_back(129508122);
//_events.push_back(129785483);//===
// _events.push_back(132001490);
// _events.push_back(134084501);
// _events.push_back(135382435);
// _events.push_back(135941923);
// _events.push_back(137653648);
// _events.push_back(139171125);
// _events.push_back(141909616);
// _events.push_back(142298027);
// _events.push_back(142821640);
// _events.push_back(143036233);
// _events.push_back(143481471);
// _events.push_back(143776242);
// _events.push_back(144000353);
// _events.push_back(145019121);
// _events.push_back(145711469);
// _events.push_back(146093398);
// _events.push_back(147293780);
// _events.push_back(147742290);
// _events.push_back(148376760);
// _events.push_back(148475994);
// _events.push_back(149195930);
// _events.push_back(150352010);
// _events.push_back(150496507);
// _events.push_back(154148347);
// _events.push_back(154240851);
// _events.push_back(155951853);
// _events.push_back(156439531);
// _events.push_back(156652831);
// _events.push_back(157459759);
// _events.push_back(167588262);
// _events.push_back(168300493);
// _events.push_back(170247707);
// _events.push_back(170569344);
// _events.push_back(172299855);
// _events.push_back(172987826);
// _events.push_back(173400911);
// _events.push_back(174198918);
// _events.push_back(175116290);
// _events.push_back(175323397);
// _events.push_back(175400241);
// _events.push_back(176448647);
// _events.push_back(178095239);
// _events.push_back(179181624);
// _events.push_back(179871044);
// _events.push_back(180745074);
// _events.push_back(180911876);
// _events.push_back(180946110);
// _events.push_back(183038953);
// _events.push_back(184014008);
// _events.push_back(186228327);
// _events.push_back(186676475);
// _events.push_back(191706176);
// _events.push_back(194910875);
// _events.push_back(195862214);
// _events.push_back(196853711);
// _events.push_back(198210931);
// _events.push_back(198405264);
// _events.push_back(198551847);
// _events.push_back(200081035);
// _events.push_back(201059053);
//_events.push_back(204175862);//===
// _events.push_back(208741072);
// _events.push_back(209605728);
// _events.push_back(211490444);
// _events.push_back(212278481);
// _events.push_back(213930242);
// _events.push_back(214440558);
// _events.push_back(214693398);
// _events.push_back(215711614);
// _events.push_back(222568243);
// _events.push_back(223606286);
// _events.push_back(224390098);
// _events.push_back(225289746);
// _events.push_back(226882728);
// _events.push_back(228434130);
// _events.push_back(230427564);
// _events.push_back(231008038);
// _events.push_back(232328777);
// _events.push_back(234030431);
// _events.push_back(234898423);
// _events.push_back(237605104);
// _events.push_back(243431990);
// _events.push_back(247167327);
// _events.push_back(251315970);
// _events.push_back(252778623);
// _events.push_back(256144502);
// _events.push_back(256554985);
// _events.push_back(260204571);
// _events.push_back(261542212);
// _events.push_back(264084284);
// _events.push_back(266114597);
// _events.push_back(269673912);
// _events.push_back(272669267);
// _events.push_back(273717411);
// _events.push_back(275726009);
// _events.push_back(277717896);
//_events.push_back(279812117);//===
// _events.push_back(279829322);
//_events.push_back(282590520);//===
// _events.push_back(282859921);
// _events.push_back(283086381);
// _events.push_back(283350576);
// _events.push_back(288987292);
// _events.push_back(290088881);
// _events.push_back(294067730);
// _events.push_back(294178609);
// _events.push_back(295077991);
//_events.push_back(298540660);//===
// _events.push_back(300464702);
// _events.push_back(304308844);
// _events.push_back(304347230);
// _events.push_back(304528702);
// _events.push_back(307147325);
// _events.push_back(307266129);
// _events.push_back(308443047);
// _events.push_back(310150909);
// _events.push_back(310493025);
// _events.push_back(312056304);
// _events.push_back(312512265);
// _events.push_back(315038738);
// _events.push_back(323710044);
// _events.push_back(323853220);
// _events.push_back(324195247);
// _events.push_back(333617928);
// _events.push_back(334681314);
// _events.push_back(335463451);
// _events.push_back(340391000);
// _events.push_back(342064801);
// _events.push_back(344796134);
// _events.push_back(346264918);
// _events.push_back(347081999);
// _events.push_back(349929810);
// _events.push_back(351913537);
// _events.push_back(355321199);
// _events.push_back(355797460);
// _events.push_back(356720560);
// _events.push_back(356781745);
// _events.push_back(358684823);
//_events.push_back(359985861);//===
// _events.push_back(360783267);
// _events.push_back(362527488);
// _events.push_back(366245496);
// _events.push_back(374376453);
// _events.push_back(378052141);
// _events.push_back(380894273);
// _events.push_back(387457310);
// _events.push_back(389574551);
//_events.push_back(390161294);//===
// _events.push_back(392569022);
// _events.push_back(393656765);
//_events.push_back(395654227);//===
// _events.push_back(396478392);
// _events.push_back(396723825);
// _events.push_back(398885382);
// _events.push_back(402476172);
// _events.push_back(406072305);
// _events.push_back(411764048);
// _events.push_back(414389200);
// _events.push_back(415552078);
// _events.push_back(421072700);
// _events.push_back(432724628);
// _events.push_back(437211991);
// _events.push_back(442200164);
// _events.push_back(443742829);
// _events.push_back(449520955);
// _events.push_back(455361628);
// _events.push_back(456654966);
// _events.push_back(460735951);
// _events.push_back(464026149);
// _events.push_back(466844957);
// _events.push_back(472142146);
// _events.push_back(473589594);
// _events.push_back(474147471);
// _events.push_back(474722621);
// _events.push_back(477275800);
// _events.push_back(478019637);
// _events.push_back(480943811);
// _events.push_back(487426910);
// _events.push_back(494052683);
// _events.push_back(496520517);
// _events.push_back(497149152);
// _events.push_back(499281419);
// _events.push_back(503858299);
// _events.push_back(504758093);
// _events.push_back(507090357);
// _events.push_back(509231380);
// _events.push_back(512009019);
// _events.push_back(516047243);
// _events.push_back(517988015);
// _events.push_back(527640107);
// _events.push_back(527759255);
// _events.push_back(527845354);
// _events.push_back(528697562);
// _events.push_back(533401119);
// _events.push_back(540176981);
// _events.push_back(546453280);
// _events.push_back(554343056);
// _events.push_back(569366193);
// _events.push_back(570538045);
// _events.push_back(579495286);
// _events.push_back(579648445);
// _events.push_back(581742888);
// _events.push_back(583172424);
// _events.push_back(586017378);
// _events.push_back(587079596);
// _events.push_back(589994934);
// _events.push_back(590916404);
// _events.push_back(593070534);
// _events.push_back(595605386);
// _events.push_back(596942563);
// _events.push_back(602111888);
// _events.push_back(603866158);
// _events.push_back(605105024);
// _events.push_back(607911096);
// _events.push_back(608806131);
// _events.push_back(615396600);
//_events.push_back(620691394);//===
// _events.push_back(622817539);
// _events.push_back(630231280);
// _events.push_back(631643814);
// _events.push_back(633390336);
// _events.push_back(640560734);
// _events.push_back(641621982);
// _events.push_back(650916046);
// _events.push_back(651236199);
// _events.push_back(651710754);
// _events.push_back(651885742);
// _events.push_back(653667552);
// _events.push_back(656624028);
// _events.push_back(663964953);
// _events.push_back(674552058);
// _events.push_back(676889360);
// _events.push_back(682445206);
// _events.push_back(690853250);
// _events.push_back(700924080);
// _events.push_back(701882359);
// _events.push_back(703663750);
// _events.push_back(707849069);
// _events.push_back(708761805);
// _events.push_back(712578306);
// _events.push_back(715041088);
// _events.push_back(715645174);
// _events.push_back(718842092);
// _events.push_back(725861965);
// _events.push_back(742443751);
// _events.push_back(743522399);
// _events.push_back(745003410);
// _events.push_back(746601549);
// _events.push_back(751492002);
// _events.push_back(755984797);
// _events.push_back(756833521);
// _events.push_back(764289373);
// _events.push_back(771802121);
// _events.push_back(773289567);
// _events.push_back(780190279);
// _events.push_back(796443338);
// _events.push_back(800428806);
// _events.push_back(805213514);
// _events.push_back(805707744);
// _events.push_back(816364906);
// _events.push_back(817052800);
// _events.push_back(827739745);
// _events.push_back(844760159);
// _events.push_back(848632675);
// _events.push_back(856895774);
// _events.push_back(858619928);
// _events.push_back(868592539);
// _events.push_back(875744382);
// _events.push_back(882349142);
// _events.push_back(906826045);
// _events.push_back(908927239);
// _events.push_back(914487106);
// _events.push_back(919601876);
// _events.push_back(920875586);
// _events.push_back(948825660);
// _events.push_back(957883468);
// _events.push_back(970910134);
// _events.push_back(973885891);
// _events.push_back(974971817);
// _events.push_back(986836050);
// _events.push_back(1000347317);
//_events.push_back(1002719591);//===
// _events.push_back(1006007346);
// _events.push_back(1009330326);
// _events.push_back(1009920621);
// _events.push_back(1017022119);
// _events.push_back(1049401651);
// _events.push_back(1051773927);
// _events.push_back(1065391213);
// _events.push_back(1069747745);
// _events.push_back(1076570460);
// _events.push_back(1081725694);
// _events.push_back(1086795015);
// _events.push_back(1087252333);
// _events.push_back(1087529625);
// _events.push_back(1095763179);
// _events.push_back(1111123283);
// _events.push_back(1120410610);
// _events.push_back(1122660619);
// _events.push_back(1129602034);
// _events.push_back(1143184518);
// _events.push_back(1143358728);
// _events.push_back(1147962333);
// _events.push_back(1148818907);
// _events.push_back(1158277580);
// _events.push_back(1169160045);
// _events.push_back(1171259675);
// _events.push_back(1182340134);
// _events.push_back(1186177131);
// _events.push_back(1189421089);
// _events.push_back(1201161311);
// _events.push_back(1231011115);
// _events.push_back(1247212923);
// _events.push_back(1258816156);
// _events.push_back(1411782924);
// _events.push_back(1424695132);
// _events.push_back(1437885113);
// _events.push_back(1441309553);
// _events.push_back(1443408045);
// _events.push_back(1447683845);
// _events.push_back(1511143126);
// _events.push_back(1532089884);
// _events.push_back(1536894706);
// _events.push_back(1560328263);
// _events.push_back(1594220271);
// _events.push_back(1602226705);
// _events.push_back(1602535573);
// _events.push_back(1606325836);
// _events.push_back(1606819848);
// _events.push_back(1607256848);
// _events.push_back(1618818705);
// _events.push_back(1619964478);
// _events.push_back(1630510904);
// _events.push_back(1639165004);
// _events.push_back(1659387605);
// _events.push_back(1669149626);
// _events.push_back(1679302902);
// _events.push_back(1700333538);
// _events.push_back(1716233011);
// _events.push_back(1718480138);
// _events.push_back(1732416923);
// _events.push_back(1760107277);
// _events.push_back(1832369763);
// _events.push_back(1859480457);
// _events.push_back(1889888226);
// _events.push_back(1927420608);
// _events.push_back(1958708727);
// _events.push_back(1968870257);
// _events.push_back(2070733437);
// _events.push_back(2077929541);
// _events.push_back(2099877074);
// _events.push_back(2127815492);
// _events.push_back(2135222886);
// _events.push_back(2161726539);
// _events.push_back(2164682397);
// _events.push_back(2215174560);
// _events.push_back(2245298726);
// _events.push_back(2258661207);
// _events.push_back(2293500450);
// _events.push_back(2455576182);
// _events.push_back(2485783744);
// _events.push_back(2489004462);
// _events.push_back(2502964461);
// _events.push_back(2517030287);
// _events.push_back(2521631475);
// _events.push_back(2540713621);
}


