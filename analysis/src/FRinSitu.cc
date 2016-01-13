/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, Matthieu Marionneau                                **
** CERN, Fall 2014                                                          **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/


#include "analysis/src/FRinSitu.hh"





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
FRinSitu::FRinSitu(std::string cfg){
  /* 
     constructs the FRinSitu class 
     parameters: configuration_file
     return: none
  */
  
  startExecution(cfg);
  initialize();

}


//____________________________________________________________________________
FRinSitu::~FRinSitu(){
  /* 
     destructs the FRinSitu class 
     parameters: none
     return: none
  */

}


//____________________________________________________________________________
void FRinSitu::initialize(){
  /*
    initializes the FRinSitu class
    parameters: none
    return: none
  */

  // trigger lines
  string TR_lines_non[3] = {"HLT_BIT_HLT_DoubleMu8_Mass8_PFHT300_v"                    , \
                            "HLT_BIT_HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v"  , \
                            "HLT_BIT_HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v"      };

  string TR_lines_iso[5] = {"HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v"            , \
                            "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"          , \
                            "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"      , \ 
                            "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v" , \
                            "HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v"  };

  _vTR_lines_non = Tools::toVector(TR_lines_non);
  _vTR_lines_iso = Tools::toVector(TR_lines_iso);

 
  // tree branches containing trigger prescales per event
  string TR_psb_non[3] = {"HLT_DoubleMu8_Mass8_PFHT300_PS"                    , \
                          "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_PS"  , \
                          "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_PS"      };
  string TR_psb_iso[5] = {"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_PS"            , \
                          "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_PS"          , \
                          "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_PS"         , \
                          "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_PS" , \
                          "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_PS"  };
  _vTR_psb_non  = Tools::toVector(TR_psb_non);
  _vTR_psb_iso  = Tools::toVector(TR_psb_iso);

 
  // trigger effective luminosities
  float TR_efflum_non[3] = {getCfgVarF("LUMINOSITY_DOUBLEMU8"     , 1.0), \
                            getCfgVarF("LUMINOSITY_DOUBLEELE8"    , 1.0), \
                            getCfgVarF("LUMINOSITY_MU8ELE3"       , 1.0)  };
  float TR_efflum_iso[5] = {getCfgVarF("LUMINOSITY_MU17MU8_ISO"   , 1.0), \
                            getCfgVarF("LUMINOSITY_MU17TKMU8_ISO" , 1.0), \
                            getCfgVarF("LUMINOSITY_ELE17ELE12_ISO", 1.0), \
                            getCfgVarF("LUMINOSITY_MU8ELE17_ISO"  , 1.0), \
                            getCfgVarF("LUMINOSITY_MU17ELE12_ISO" , 1.0)  };
  _vTR_efflum_non = Tools::toVector(TR_efflum_non);
  _vTR_efflum_iso = Tools::toVector(TR_efflum_iso);


  // fake ratio pt bins
  float FR_bins_pt_el[6]  = {10.0, 15.0, 25.0, 35.0, 50.0, 70.0};
  float FR_bins_pt_mu[6]  = {10.0, 15.0, 25.0, 35.0, 50.0, 70.0};
  _vFR_bins_pt_el  = Tools::toVector(FR_bins_pt_el );
  _vFR_bins_pt_mu  = Tools::toVector(FR_bins_pt_mu );


  // fake ratio eta bins
  //float FR_bins_eta_el[4] = { 0.0, 1.0, 2.0, 2.5};
  //float FR_bins_eta_mu[4] = { 0.0, 1.0, 2.0, 2.4};
  float FR_bins_eta_el[4] = { 0.0, 0.8, 1.479, 2.5};
  float FR_bins_eta_mu[4] = { 0.0, 1.2, 2.1, 2.4};
  _vFR_bins_eta_el = Tools::toVector(FR_bins_eta_el);
  _vFR_bins_eta_mu = Tools::toVector(FR_bins_eta_mu);


  //Tree Variables
 string ls[1] = {"LepGood"};
  _bvar  = "nBJetMedium25";
  _leps = Tools::toVector(ls);
  _jets  = "Jet";
  _djets = "DiscJet";
  _mets  = "met";
  _nvert = "nVert";

  //Tree Branches
  _vc->registerVar("run"                           );
  _vc->registerVar("lumi"                          );
  _vc->registerVar("evt"                           );
  _vc->registerVar(_nvert                          );
  _vc->registerVar("nTrueInt"                      );
  _vc->registerVar("vtxWeight"                     );
  _vc->registerVar("genWeight"                     );
  _vc->registerVar(_mets + "_pt"                   );
  _vc->registerVar(_mets + "_eta"                  );
  _vc->registerVar(_mets + "_phi"                  );
  _vc->registerVar(_mets + "_mass"                 );
  _vc->registerVar("n" + _jets                     );
  _vc->registerVar(_jets + "_id"                   );
  _vc->registerVar(_jets + "_pt"                   );
  _vc->registerVar(_jets + "_rawPt"                );
  _vc->registerVar(_jets + "_eta"                  );
  _vc->registerVar(_jets + "_phi"                  );
  _vc->registerVar(_jets + "_mass"                 );
  _vc->registerVar(_jets + "_btagCSV"              );
  _vc->registerVar("n" + _djets                    );
  _vc->registerVar(_djets + "_id"                  );
  _vc->registerVar(_djets + "_pt"                  );
  _vc->registerVar(_djets + "_rawPt"               );
  _vc->registerVar(_djets + "_eta"                 );
  _vc->registerVar(_djets + "_phi"                 );
  _vc->registerVar(_djets + "_mass"                );
  _vc->registerVar(_djets + "_btagCSV"             );

  //generator informations
  _vc->registerVar("nGenPart"                      );
  _vc->registerVar("GenPart_pt"                    );
  _vc->registerVar("GenPart_eta"                   );
  _vc->registerVar("GenPart_phi"                   );
  _vc->registerVar("GenPart_pdgId"                 );
  _vc->registerVar("GenPart_motherId"              );
  _vc->registerVar("GenPart_grandmotherId"         );

  _vc->registerVar("nGenBHad"                      );
  _vc->registerVar("GenBHad_pt"                    );
  _vc->registerVar("GenBHad_eta"                   );
  _vc->registerVar("GenBHad_phi"                   );
  _vc->registerVar("GenBHad_pdgId"                 );

  //bjets
  _vc->registerVar("nBJetLoose25"                  );
  _vc->registerVar("nBJetMedium40"                 );
  _vc->registerVar("nBJetMedium25"                 );
  _vc->registerVar("nSoftBJetMedium25"             );

  //triggers
  registerLepVars();
  registerTriggerVars();

  //additional counter categories
  _au->addCategory( kTrigger , "Trigger Sel"            );
  _au->addCategory( kDenEls  , "Denominator Electrons"  );
  _au->addCategory( kNumEls  , "Numerator Electrons"    );
  _au->addCategory( kSigEls  , "Signal Region Electrons");
  _au->addCategory( kVetEls  , "Veto Electrons"         );
  _au->addCategory( kClEls   , "Clean Electrons"        );
  _au->addCategory( kDenMus  , "Denominator Muons"      );
  _au->addCategory( kNumMus  , "Numerator Muons"        );
  _au->addCategory( kSigMus  , "Signal Region Muons"    );
  _au->addCategory( kVetMus  , "Veto Muons"             );
  _au->addCategory( kClMus   , "Clean Muons"            );
  _au->addCategory( kGoodJets, "Good Jets"              );


  //extra input variables
  //_MR          = getCfgVarS("MR"           );
  _norm        = getCfgVarS("NORMALIZATION", "data"); // data, lumi
  _genMatching = getCfgVarF("GENMATCHING"  , 0     ); // 1, 0

  //SusyModule
  _susyMod = new SusyModule(_vc); 

  //Databases
  _dbm -> loadDb("XS", "XSectionsSpring15.db");
  _dbm -> loadDb("KF", "kFactorsSpring15.db");

 
}


//____________________________________________________________________________
void FRinSitu::run(){

  _denEls  .clear();
  _denLeps .clear();
  _denMus  .clear();
  _numEls  .clear();
  _numLeps .clear();
  _numMus  .clear();
  _sigLeps .clear();
  _vetLeps .clear();
  _clLeps  .clear();

  _denElsIdx  .clear();
  _denLepsIdx .clear();
  _denMusIdx  .clear();
  _numElsIdx  .clear();
  _numLepsIdx .clear();
  _numMusIdx  .clear();
  _sigLepsIdx .clear();
  _vetLepsIdx .clear();
  _clLepsIdx  .clear();
  _isoLepsIdx .clear();

  _bJets   .clear();
  _goodJets.clear();
  _lepJets .clear();

  _bJetsIdx   .clear();
  _goodJetsIdx.clear();
  _lepJetsIdx .clear();

  _exts    .clear();
  _trws    .clear();
  _TR_lines.clear();

  counter("denominator");

	
  // prepare event selection
  collectKinematicObjects();

  //skimming
  //if(!skimSelection()) return;
  //fillSkimTree();
  //return;


  // basic event selection (triggers, 2 ss leptons, veto)
  if(!baseSelection()) return;


  // mr event selection
  if(!mrSelection()) return;

	
  // calling the modules
  fillEventPlots   ();
  fillFakeRatioMaps();
  fillLeptonPlots  ();

	
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FRinSitu::defineOutput(){
  /*
    defines and reserves all output that is produced in this class
    parameters: none
    return: none
  */ 


  // leptons
  string MR_els[3]  = {"MR_DenEl", "MR_NumEl", "MR_RatEl"};
  string MR_leps[4] = {"MR_DenEl", "MR_NumEl", "MR_DenMu", "MR_NumMu"};
  string MR_mus[3]  = {"MR_DenMu", "MR_NumMu", "MR_RatMu"};

  vector<string> vMR_els  = Tools::toVector(MR_els);
  vector<string> vMR_leps = Tools::toVector(MR_leps);
  vector<string> vMR_mus  = Tools::toVector(MR_mus);

  // this is now here but should be somewhere else!!!
  setMeasurementRegion();

  // Special feature of this class: it produces FR maps for 'data', 'datacorr', 'ewk', 'qcd'
  _hm -> addDataset("data");
  _hm -> addDataset("datacorrETH");
  _hm -> addDataset("datacorrCERN");
  _hm -> addDataset("ewk");
  _hm -> addDataset("ewk_dy");
  _hm -> addDataset("ewk_tt");
  _hm -> addDataset("ewk_wj");
  _hm -> addDataset("qcd");
  _hm -> addDataset("qcd_bc");
  _hm -> addDataset("qcd_em");
  _hm -> addDataset("qcd_mu15");
  _hm -> addDataset("qcd_mu5");
  _idx_data         = _numDS;
  _idx_datacorrETH  = _numDS+1;
  _idx_datacorrCERN = _numDS+2;
  _idx_ewk          = _numDS+3;
  _idx_ewk_dy       = _numDS+4;
  _idx_ewk_tt       = _numDS+5;
  _idx_ewk_wj       = _numDS+6;
  _idx_qcd          = _numDS+7;
  _idx_qcd_bc       = _numDS+8;
  _idx_qcd_em       = _numDS+9;
  _idx_qcd_mu15     = _numDS+10;
  _idx_qcd_mu5      = _numDS+11;
  int idxs[12] = {_idx_data, _idx_datacorrETH, _idx_datacorrCERN, _idx_ewk, _idx_ewk_dy, _idx_ewk_tt, _idx_ewk_wj, _idx_qcd, _idx_qcd_bc, _idx_qcd_em, _idx_qcd_mu15, _idx_qcd_mu5};
  _idxs  = Tools::toVector(idxs);
  _idxsmc.push_back(_idx_ewk);
  _idxsmc.push_back(_idx_qcd);

  // Measurement Region
  registerVariable("MR_HT"              , 1000,  0.0, 1000.0, "H_T [GeV]"                            );
  registerVariable("MR_MET"             , 1000,  0.0, 1000.0, "#slash{E}_T [GeV]"                    );
  registerVariable("MR_NumJets"         ,   20,  0.0,   20.0, "jet multiplicity"                     );
  registerVariable("MR_NumBJets"        ,   20,  0.0,   20.0, "b-jet multiplicity"                   );
  registerVariable("MR_NumDenEls"       ,   20,  0.0,   20.0, "denominator electron multiplicity"    );
  registerVariable("MR_NumDenLeps"      ,   20,  0.0,   20.0, "denominator lepton multiplicity"      );
  registerVariable("MR_NumDenMus"       ,   20,  0.0,   20.0, "denominator muon multiplicity"        );
  registerVariable("MR_NumNumEls"       ,   20,  0.0,   20.0, "numerator electron multiplicity"      );
  registerVariable("MR_NumNumLeps"      ,   20,  0.0,   20.0, "numerator lepton multiplicity"        );
  registerVariable("MR_NumNumMus"       ,   20,  0.0,   20.0, "numerator muon multiplicity"          );
  registerVariable("MR_NumVrtx"         ,   40,  0.0,   40.0, "vertex multiplicity"                  );
  registerVariable("MR_JetCSVBTag"      ,   50,  0.0,    1.0, "jet CSV B-Tag"                        );
  registerVariable("MR_JetPt"           , 1000,  0.0, 1000.0, "P_T(jet) [GeV]"                       );
  
  registerLepPlots(vMR_leps, "DXY"      , 5000,  0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(vMR_leps, "DZ"       , 5000,  0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(vMR_leps, "Eta"      ,  250,  0.0,    2.5, "#||{#eta(lep)}"                       );
  registerLepPlots(vMR_leps, "SIP"      , 1000,  0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(vMR_leps, "RelIso"   ,   50,  0.0,    1.0, "PF RelIso (lep)"                      );
  registerLepPlots(vMR_leps, "MiniIso"  ,   50,  0.0,    1.0, "PF MiniIso (lep)"                     );
  registerLepPlots(vMR_leps, "MT"       , 1000,  0.0, 1000.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(vMR_leps, "Pt"       , 1000,  0.0, 1000.0, "P_T(lep) [GeV]"                       );
  registerLepPlots(vMR_leps, "PtJet"    , 1000,  0.0, 1000.0, "P_T(jet closest to lep) [GeV]"        );
  registerLepPlots(vMR_leps, "PtCorr"   , 1000,  0.0, 1000.0, "cone corr. P_T(lep) [GeV]"            );
  registerLepPlots(vMR_leps, "PtRel"    , 1000,  0.0, 1000.0, "PtRel(lep)"                           );

  // fake ratio projections
  registerLepPlots(vMR_els , "EtaFR"    , _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "#||{#eta(e)}"            );
  registerLepPlots(vMR_mus , "EtaFR"    , _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "#||{#eta(#mu)}"          );
  registerLepPlots(vMR_els , "PtCorrFR" , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , "cone corr. P_T(e) [GeV]" );
  registerLepPlots(vMR_mus , "PtCorrFR" , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , "cone corr. P_T(e) [GeV]" );

  // fake ratio maps electrons 
  registerLepPlots(vMR_els, "MapPt"     , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "P_T(e) [GeV]"                 , "#||{#eta}(e)");
  registerLepPlots(vMR_els, "MapPtJet"  , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "P_T(jet closest to e) [GeV]"  , "#||{#eta}(e)");
  registerLepPlots(vMR_els, "MapPtCorr" , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "cone corr. P_T(e) [GeV]"      , "#||{#eta}(e)");
  // fake ratio maps muons
  registerLepPlots(vMR_mus, "MapPt"     , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "P_T(#mu) [GeV]"               , "#||{#eta}(#mu)");
  registerLepPlots(vMR_mus, "MapPtJet"  , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "P_T(jet closest to #mu) [GeV]", "#||{#eta}(#mu)");
  registerLepPlots(vMR_mus, "MapPtCorr" , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu, \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "cone corr. P_T(#mu) [GeV]"    , "#||{#eta}(#mu)");

}


//____________________________________________________________________________
void FRinSitu::divideFRMap(string postpend){

  for(int i = 0; i < _numDS; ++i){
    TH1 * denom = _hm -> getHisto("MR_Den" + postpend, i);
    TH1 * num   = _hm -> getHisto("MR_Rat" + postpend, i);
    num -> Divide(denom);
  } 
  
}


//____________________________________________________________________________
void FRinSitu::divideFRMaps(){

  vector<string> exts;
  exts.push_back("non");
  exts.push_back("iso");

  for(unsigned int i = 0; i < _vTR_lines_non.size(); ++i) exts.push_back("non" + Tools::intToString(i));
  for(unsigned int i = 0; i < _vTR_lines_iso.size(); ++i) exts.push_back("iso" + Tools::intToString(i));

  for(unsigned int i = 0; i < exts.size(); ++i){
    divideFRMap("ElMapPt_"     + exts[i]);
    divideFRMap("ElMapPtJet_"  + exts[i]);
    divideFRMap("ElMapPtCorr_" + exts[i]);
    divideFRMap("MuMapPt_"     + exts[i]);
    divideFRMap("MuMapPtJet_"  + exts[i]);
    divideFRMap("MuMapPtCorr_" + exts[i]);
  }
} 


//____________________________________________________________________________
void FRinSitu::registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis){

  for(unsigned int i = 0; i < leps.size(); ++i)
    registerVariable(leps[i] + var, nbins, bmin, bmax, axis);

}


//____________________________________________________________________________
void FRinSitu::registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, string xaxis){

  for(unsigned int i = 0; i < leps.size(); ++i)
    registerVariable(leps[i] + var, nxbins, xbins, xaxis);

}


//____________________________________________________________________________
void FRinSitu::registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis){

  for(unsigned int i = 0; i < leps.size(); ++i)
    registerVariable(leps[i] + var, nxbins, xbins, nybins, ybins, xaxis, yaxis);

}


//____________________________________________________________________________
void FRinSitu::registerLepVars(){

  for(unsigned int i = 0; i < _leps.size(); ++i){
    _vc->registerVar("n" + _leps[i]                     );
    _vc->registerVar(_leps[i] + "_pt"                   );
    _vc->registerVar(_leps[i] + "_eta"                  );
    _vc->registerVar(_leps[i] + "_phi"                  );
    _vc->registerVar(_leps[i] + "_charge"               );
    _vc->registerVar(_leps[i] + "_tightCharge"          );
    _vc->registerVar(_leps[i] + "_mediumMuonId"         );
    _vc->registerVar(_leps[i] + "_mvaIdPhys14"          );
    _vc->registerVar(_leps[i] + "_mvaIdSpring15"        );
    _vc->registerVar(_leps[i] + "_pdgId"                );
    _vc->registerVar(_leps[i] + "_relIso03"             );
    _vc->registerVar(_leps[i] + "_relIso04"             );
    _vc->registerVar(_leps[i] + "_jetPtRatiov2"         );
    _vc->registerVar(_leps[i] + "_jetPtRelv2"           );
    _vc->registerVar(_leps[i] + "_jetRawPt"             );
    _vc->registerVar(_leps[i] + "_jetCorrFactor_L1L2L3Res");
    _vc->registerVar(_leps[i] + "_miniRelIso"           );
    _vc->registerVar(_leps[i] + "_chargedHadRelIso03"   );
    _vc->registerVar(_leps[i] + "_miniRelIso"           );
    _vc->registerVar(_leps[i] + "_miniRelIso"           );
    _vc->registerVar(_leps[i] + "_dxy"                  );
    _vc->registerVar(_leps[i] + "_dz"                   );
    _vc->registerVar(_leps[i] + "_sip3d"                );
    _vc->registerVar(_leps[i] + "_pfMuonId"             );
    _vc->registerVar(_leps[i] + "_tightId"              );
    _vc->registerVar(_leps[i] + "_looseIdSusy"          );
    _vc->registerVar(_leps[i] + "_convVeto"             );
    _vc->registerVar(_leps[i] + "_lostHits"             );
    _vc->registerVar(_leps[i] + "_eleCutIdCSA14_50ns_v1");
    _vc->registerVar(_leps[i] + "_eleCutIdCSA14_50ns_v1");
    _vc->registerVar(_leps[i] + "_eleCutId2012_full5x5" );
    _vc->registerVar(_leps[i] + "_mvaSusyPHYS14"        );
    _vc->registerVar(_leps[i] + "_mvaSusy"              );
    _vc->registerVar(_leps[i] + "_mcMatchId"            );
    _vc->registerVar(_leps[i] + "_mcMatchAny"           );
    _vc->registerVar(_leps[i] + "_jetBTagCSV"           );
    _vc->registerVar(_leps[i] + "_sigmaIEtaIEta"        );
    _vc->registerVar(_leps[i] + "_hadronicOverEm"       );
    _vc->registerVar(_leps[i] + "_eInvMinusPInv"        );
    _vc->registerVar(_leps[i] + "_dEtaScTrkIn"          );
    _vc->registerVar(_leps[i] + "_dPhiScTrkIn"          );
    _vc->registerVar(_leps[i] + "_ecalPFClusterIso"     );
    _vc->registerVar(_leps[i] + "_hcalPFClusterIso"     );
    _vc->registerVar(_leps[i] + "_dr03TkSumPt"          );
  }
}

//  ____________________________________________________________________________
void FRinSitu::registerTriggerVars(){

  for(unsigned int i = 0; i < _vTR_lines_non.size(); ++i) {_vc->registerVar(_vTR_lines_non[i]); _vc->registerVar(_vTR_psb_non[i]);}
  for(unsigned int i = 0; i < _vTR_lines_iso.size(); ++i) {_vc->registerVar(_vTR_lines_iso[i]); _vc->registerVar(_vTR_psb_iso[i]);}

}


//  ____________________________________________________________________________
void FRinSitu::registerVariable(string var, int nBin, float min, float max, string Xleg, bool isglb, bool prof, string type){

  _hm->addVariable(var + "_non", nBin, min, max, Xleg, isglb, prof, type);
  _hm->addVariable(var + "_iso", nBin, min, max, Xleg, isglb, prof, type);

  for(unsigned int i = 0; i < _vTR_lines_non.size(); ++i)
    _hm->addVariable(var + "_non" + Tools::intToString(i), nBin, min, max, Xleg, isglb, prof, type);
  for(unsigned int i = 0; i < _vTR_lines_iso.size(); ++i)
    _hm->addVariable(var + "_iso" + Tools::intToString(i), nBin, min, max, Xleg, isglb, prof, type);

}


//  ____________________________________________________________________________
void FRinSitu::registerVariable(string var, int nBinX, float minX, float maxX, int nBinY, float minY, float maxY, string Xleg, string Yleg, bool isglb, bool prof, string type){

  _hm->addVariable(var + "_non", nBinX, minX, maxX, nBinY, minY, maxY, Xleg, Yleg, isglb, prof, type);
  _hm->addVariable(var + "_iso", nBinX, minX, maxX, nBinY, minY, maxY, Xleg, Yleg, isglb, prof, type);

  for(unsigned int i = 0; i < _vTR_lines_non.size(); ++i)
    _hm->addVariable(var + "_non" + Tools::intToString(i), nBinX, minX, maxX, nBinY, minY, maxY, Xleg, Yleg, isglb, prof, type);
  for(unsigned int i = 0; i < _vTR_lines_iso.size(); ++i)
    _hm->addVariable(var + "_iso" + Tools::intToString(i), nBinX, minX, maxX, nBinY, minY, maxY, Xleg, Yleg, isglb, prof, type);

}


//  ____________________________________________________________________________
void FRinSitu::registerVariable(string var, int nBinX, vector<float> binsX, string Xleg, bool isglb, bool prof, string type){

  _hm->addVariable(var + "_non", nBinX, binsX, Xleg, isglb, prof, type);
  _hm->addVariable(var + "_iso", nBinX, binsX, Xleg, isglb, prof, type);

  for(unsigned int i = 0; i < _vTR_lines_non.size(); ++i)
    _hm->addVariable(var + "_non" + Tools::intToString(i), nBinX, binsX, Xleg, isglb, prof, type);
  for(unsigned int i = 0; i < _vTR_lines_iso.size(); ++i)
    _hm->addVariable(var + "_iso" + Tools::intToString(i), nBinX, binsX, Xleg, isglb, prof, type);

}


//  ____________________________________________________________________________
void FRinSitu::registerVariable(string var, int nBinX, vector<float> binsX, int nBinY, vector<float> binsY, string Xleg, string Yleg, bool isglb, bool prof, string type){

  _hm->addVariable(var + "_non", nBinX, binsX, nBinY, binsY, Xleg, Yleg, isglb, prof, type);
  _hm->addVariable(var + "_iso", nBinX, binsX, nBinY, binsY, Xleg, Yleg, isglb, prof, type);

  for(unsigned int i = 0; i < _vTR_lines_non.size(); ++i)
    _hm->addVariable(var + "_non" + Tools::intToString(i), nBinX, binsX, nBinY, binsY, Xleg, Yleg, isglb, prof, type);
  for(unsigned int i = 0; i < _vTR_lines_iso.size(); ++i)
    _hm->addVariable(var + "_iso" + Tools::intToString(i), nBinX, binsX, nBinY, binsY, Xleg, Yleg, isglb, prof, type);

}


//____________________________________________________________________________
void FRinSitu::sumMaps(){
  /*
    adds weighted numerators and denominators for different samples with same prefix
  */


  vector<string> obs = _hm -> getObservables(true);
  vector<float> ints_data;
  ints_data.resize(obs.size(), 0);

  for(int i = 0; i < _numDS; ++i){
    if(_datasets[i]->getName().find("data") != std::string::npos) {
      for(unsigned int j = 0; j < obs.size(); ++j) {
        ints_data[j] += _hm -> getHisto(obs[j], i)->Integral();
      }
    }
  }

  for(int i = 0; i < _numDS; ++i){

    string sname = _datasets[i]->getName();
    bool normalize = false;

    int nevts = _datasets[i]->getNProcEvents();
    float xs = 0;
    vector<unsigned int> idxs;
    if     (sname.find("data") != std::string::npos) {
      idxs.push_back(_idx_data        );
      idxs.push_back(_idx_datacorrETH );
      idxs.push_back(_idx_datacorrCERN);
    }
    else if(sname.find("ewk")  != std::string::npos) {
      idxs.push_back(_idx_ewk);
      sname.erase(sname.find("ewk"), 3);
      if     (sname.find("DYJets") != std::string::npos) idxs.push_back(_idx_ewk_dy);
      else if(sname.find("TTJets") != std::string::npos) idxs.push_back(_idx_ewk_tt);
      else if(sname.find("WJets" ) != std::string::npos) idxs.push_back(_idx_ewk_wj);
      xs = _dbm -> getDBValue("XS", sname);
      normalize = true;
    }
    else if(sname.find("qcd")  != std::string::npos) {
      idxs.push_back(_idx_qcd);
      sname.erase(sname.find("qcd"), 3);
      if     (sname.find("bcToE"     ) != std::string::npos) idxs.push_back(_idx_qcd_bc);
      else if(sname.find("EMEnriched") != std::string::npos) idxs.push_back(_idx_qcd_em);
      else if(sname.find("Mu15"      ) != std::string::npos) idxs.push_back(_idx_qcd_mu15);
      else if(sname.find("Mu5"       ) != std::string::npos) idxs.push_back(_idx_qcd_mu5);
      xs = _dbm -> getDBValue("XS", sname);
      normalize = true;
    }

    for(unsigned int j = 0; j < obs.size(); ++j) {
      TH1 * sobs = _hm -> getHisto(obs[j], i);
      TH1 * cobs = (TH1*) sobs -> Clone();

      float factor = 1;

      if(normalize){
        if(_norm == "lumi"){

          //vector<string> linesel = _vTR_lines_el_non[0];
          //vector<float>  effsel  = _vTR_efflum_el_non;
          //vector<float>  effsmu  = _vTR_efflum_mu_non;
          //if(iso) {
          //  linesel = _vTR_lines_el_iso[0];
          //  effsel  = _vTR_efflum_el_iso;
          //  effsmu  = _vTR_efflum_mu_iso;
          //}

          float lumi = 1;
          //if(linesel.size() <= idx) lumi = effsmu[idx];
          //else                      lumi = effsel[idx];
          //factor = lumi;
          factor = xs * lumi / nevts;
        }
      }

      for(unsigned int k = 0; k < idxs.size(); ++k) {
        TH1 * robs = _hm -> getHisto(obs[j], idxs[k]);
        robs -> Add(cobs, factor);
      }
    }
  }

  if(_norm == "data"){
    for(unsigned int j = 0; j < obs.size(); ++j) {
      float factor = 0.;
      for(unsigned int i = 0; i < _idxsmc.size(); ++i){
        TH1 * sobs = _hm -> getHisto(obs[j], _idxsmc[i]);
        factor += sobs->Integral();
      }

      if(ints_data[j] > 0 && factor > 0){
        factor /= float(ints_data[j]);
        factor = 1. / factor;
      }
      else {
        factor = 1.;
      }

      for(unsigned int i = 0; i < _idxsmc.size(); ++i){
        TH1 * sobs = _hm -> getHisto(obs[j], _idxsmc[i]);
        sobs -> Scale(factor);
      }
    }
  }
}


//____________________________________________________________________________
void FRinSitu::sumTriggerPlots(string obs, int ds, string ext){

  // CH: note: electrons and muons are in different observables
  // so for an electron observable, the muon trigger plots will be empty
  // we can sum over them as it doesn't make a difference
  unsigned int num = _vTR_lines_non.size();
  if(ext == "iso")
    num = _vTR_lines_iso.size();

  TH1* sum = _hm -> getHisto(obs + ext, ds);
  for(unsigned int i = 0; i < num; ++i)
    sum -> Add(_hm -> getHisto(obs + ext + Tools::intToString(i), ds));

}


//____________________________________________________________________________
void FRinSitu::sumTriggers(){

  // get all observables
  vector<string> obs = _hm -> getObservables(true);

  // get observables which exists multiply for different triggers
  vector<string> tobs;
  for(unsigned int j = 0; j < obs.size(); ++j) {
    string oname = obs[j];
    if(oname.find("non") != std::string::npos) oname = oname.substr(0, oname.find("non"));
    if(oname.find("iso") != std::string::npos) oname = oname.substr(0, oname.find("iso"));

    if(find(tobs.begin(), tobs.end(), oname) == tobs.end())
      tobs.push_back(oname);
  }

  // sum trigger maps
  for(unsigned int i = 0; i < _numDS + _idxs.size(); ++i){
    for(unsigned int j = 0; j < tobs.size(); ++j) {
      sumTriggerPlots(tobs[j], i, "non");
      sumTriggerPlots(tobs[j], i, "iso");
    }
  }
}



//____________________________________________________________________________
void FRinSitu::writeOutput(){
  /*
    writes all output of this class to the disk
    paramters: none
    return: none
  */

  // sum numerators and denominators in categories 'data', 'datacorr', 'ewk', 'qcd' 
  sumMaps();

  // sum plots over all triggers
  sumTriggers();

  // make FR maps from numerators and denominators
  divideFRMaps();

}


//____________________________________________________________________________
void FRinSitu::modifySkimming(){
  // if adding variables in the skimming tree is needed...

  addSkimBranch("vtxWeight", &_vtxWeight);

}


//____________________________________________________________________________
void FRinSitu::modifyWeight() {
  /*
    modifies the event weight for every entry in the tree
    parameters: none
    return: none
  */

  //_weight = (i->second)->Getweight();

  //if(_sampleName.find("data") == std::string::npos && _vc->get("puWeight") > 0)
  //  _weight *= _vc->get("puWeight");
  //else
  //  _weight = 1.;

  _isData = true;
  if(_sampleName.find("data")==std::string::npos && _sampleName.find("runs")==std::string::npos) {

    _vtxWeight = _vc->get("vtxWeight");

    string sname = _sampleName;
    if(sname.find("ewk") != std::string::npos) sname = sname.erase(sname.find("ewk"), 3);
    if(sname.find("qcd") != std::string::npos) sname = sname.erase(sname.find("qcd"), 3);

    _weight *= _vc->get("vtxWeight")*_vc->get("genWeight");
    //_weight *= _vc->get("puWeight")*_vc->get("genWeight");
    //_weight *= _vc->get("puWeight");

    double nProc=getCurrentDS()->getSumProcWgts();
    //if(sname.find("DYJets") != std::string::npos) nProc = 3.94876696821e+11;
    //if(sname.find("WJets")  != std::string::npos) nProc = 2.77246219357e+12;
    //if(sname.find("TTJets") != std::string::npos) nProc = 72744782594.8;

    if(nProc==-1) nProc=getCurrentDS()->getNProcEvents();

    //if(sname.find("QCD_Pt20to30_Mu5")    != std::string::npos) nProc = 1271383. / 1629978. * nProc;  // basket bug
    //if(sname.find("QCD_Pt_20to30_bcToE") != std::string::npos) nProc = 950000.  / 1496051. * nProc;  // basket bug
    //if(sname.find("TTJets")              != std::string::npos) nProc = 8405382. / 16164196. * 7.96328e+10;  // basket bug

    double w=_dbm->getDBValue("XS", sname) * _dbm->getDBValue("KF", sname)/nProc * 1;//last number is lumi
    _weight *=w;
    _isData=false;
//DUMP(sname);
//DUMP(_weight);
//DUMP(_vc->get("vtxWeight"));
//DUMP(_vc->get("genWeight"));
//DUMP(_dbm->getDBValue("XS", sname));
//DUMP(_dbm->getDBValue("KF", sname));
//DUMP(nProc);
  }

}




/*****************************************************************************
******************************************************************************
** OBJECT SELECTIONS                                                        **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FRinSitu::collectKinematicObjects(){
  /*
    collects all kinematic objects needed in the code, i.e. applies all object selections
    parameters: none
    return: none
  */
 

  for(int i = 0; i < _leps.size(); ++i)
    for(int j = 0; j < _vc -> get("n" + _leps[i]); ++j)
      collectLeptons(j, _leps[i]);

  _nDenEls    = _denEls   .size();
  _nDenLeps   = _denLeps  .size();
  _nDenMus    = _denMus   .size();
  _nNumEls    = _numEls   .size();
  _nNumLeps   = _numLeps  .size();
  _nNumMus    = _numMus   .size();
  _nSigLeps   = _sigLeps  .size();
  _nVetLeps   = _vetLeps  .size();

  _susyMod -> cleanJets( &_clLeps ,  _goodJets, _goodJetsIdx, _bJets, _bJetsIdx, _lepJets, _lepJetsIdx, 40, 25);
  _susyMod -> cleanLeps(  _sigLeps, &_vetLeps );

  _nGoodJets = _goodJets.size();
  _nBJets    = _bJets   .size();
  _HT        = _susyMod -> HT( &(_goodJets) );
  _met       = Candidate::create(_vc->get(_mets + "_pt"), _vc->get(_mets + "_phi") );

}


//____________________________________________________________________________
void FRinSitu::collectLeptons(int idx, string branch){
 
  Candidate * c = nullptr;

  // electrons
  if(std::abs(_vc->get(branch + "_pdgId", idx)) == 11){		  

    c  = Candidate::create(_vc->get(branch + "_pt"    , idx),
                           _vc->get(branch + "_eta"   , idx),
                           _vc->get(branch + "_phi"   , idx),
                           _vc->get(branch + "_pdgId" , idx),
                           _vc->get(branch + "_charge", idx),
                           0.0005);

    // sip > 4.0
    if(denominatorElectronSelection(c, idx, branch)){
      _denEls    .push_back( c );
      _denElsIdx .push_back(pair<int, string>(idx, branch));
      _denLeps   .push_back( _denEls[ _denEls.size()-1 ] );
      _denLepsIdx.push_back(pair<int, string>(idx, branch));
      if(_susyMod -> elHLTEmulSelIso(idx, SusyModule::kInSituHT, branch)) 
        _isoLepsIdx.push_back(pair<int, string>(idx, branch));

      if(numeratorElectronSelection(c, idx, branch)) {
        _numEls    .push_back( c );
        _numElsIdx .push_back(pair<int, string>(idx, branch));
        _numLeps   .push_back( _numEls[ _numEls.size()-1 ] );
        _numLepsIdx.push_back(pair<int, string>(idx, branch));
      }
    }
    // sip < 4.0
    else {
      if(signalRegionElectronSelection(c, idx, branch)){
        _sigLeps   .push_back( c );
        _sigLepsIdx.push_back(pair<int, string>(idx, branch));
      }
      if(cleanElectronSelection(c, idx, branch))  {
        _clLeps   .push_back( c );
        _clLepsIdx.push_back(pair<int, string>(idx, branch));
      }
    }
    // sip < 1000.
    if(vetoElectronSelection(c, idx, branch))  {
      _vetLeps   .push_back( c );
      _vetLepsIdx.push_back(pair<int, string>(idx, branch));
    }
  }

  // muons
  else if(std::abs(_vc->get(branch + "_pdgId", idx)) == 13){
    c = Candidate::create(_vc->get(branch + "_pt"    , idx),
                          _vc->get(branch + "_eta"   , idx),
                          _vc->get(branch + "_phi"   , idx),
                          _vc->get(branch + "_pdgId" , idx),
                          _vc->get(branch + "_charge", idx),
                          0.105);

    // sip > 4.0
    if(denominatorMuonSelection(c, idx, branch)) {
      _denMus    .push_back( c );
      _denMusIdx .push_back(pair<int, string>(idx, branch));
      _denLeps   .push_back( _denMus[ _denMus.size()-1 ] );
      _denLepsIdx.push_back(pair<int, string>(idx, branch));
      _isoLepsIdx.push_back(pair<int, string>(idx, branch));

      if(numeratorMuonSelection(c, idx, branch)) {
        _numMus    .push_back( c );
        _numMusIdx .push_back(pair<int, string>(idx, branch));
        _numLeps   .push_back( _numMus[ _numMus.size()-1 ] );
        _numLepsIdx.push_back(pair<int, string>(idx, branch));
      }
    }
    // sip < 4.0
    else {
      if(signalRegionMuonSelection(c, idx, branch)) {
        _sigLeps   .push_back( c );
        _sigLepsIdx.push_back(pair<int, string>(idx, branch));
      }
      if(cleanMuonSelection(c, idx, branch)) {
        _clLeps   .push_back( c );
        _clLepsIdx.push_back(pair<int, string>(idx, branch));
      }
    }
    // sip < 1000.
    if(vetoMuonSelection(c, idx, branch)) {
      _vetLeps   .push_back( c );
      _vetLepsIdx.push_back(pair<int, string>(idx, branch));
    }
  }
}


//____________________________________________________________________________
bool FRinSitu::cleanElectronSelection(Candidate* c, unsigned int elIdx, string branch){
  // veto electron -> jet lepton cleaning only
  //               -> default FO selection

  counter("CleanElectrons", kClEls);

  if(!_susyMod -> elIdSel     (c, elIdx, SusyModule::kTight, SusyModule::kLoose, true, false, branch) ) return false;
  if(!_susyMod -> elHLTEmulSel(   elIdx, false, branch                                              ) ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::cleanMuonSelection(Candidate* c, unsigned int muIdx, string branch){
  // veto muon -> jet lepton cleaning only
  //           -> default FO selection

  counter("CleanMuons", kClMus);

  if(!_susyMod -> muIdSel(c, muIdx, SusyModule::kTight, true, false, branch) ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::denominatorElectronSelection(Candidate* c, unsigned int elIdx, string branch){
  /*
    does the selection of loose electrons
    parameters: elIdx
    return: true (if the electron is a loose electron), false (else)
  */

  counter("DenominatorElectrons", kDenEls);

  if(!_susyMod -> elIdSel     (c, elIdx, SusyModule::kTight, SusyModule::kInSitu, true, true, branch)) return false;
  if(!_susyMod -> inSituFO    (   elIdx, SusyModule::kTight, branch                                 )) return false;
  if(!_susyMod -> elHLTEmulSel(   elIdx, false, branch                                              )) return false;
  //if(!_susyMod -> invPtRelSel (elIdx, SusyModule::kTight                             )) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::denominatorMuonSelection(Candidate* c, unsigned int muIdx, string branch){
  /*
    does the selection of loose muons
    parameters: muIdx
    return: true (if the muon is a loose muon), false (else)
  */

  counter("DenominatorMuons", kDenMus);

  if(!_susyMod -> muIdSel(c, muIdx, SusyModule::kTight , true, true, branch)) return false;
  if(!_susyMod -> inSituFO  (muIdx, SusyModule::kMedium, branch            )) return false;
  //if(!_susyMod -> invPtRelSel(muIdx, SusyModule::kMedium        )) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::numeratorElectronSelection(Candidate* c, unsigned int elIdx, string branch){
  /*
    does the selection of tight electrons
    parameters: elIdx
    return: true (if the electron is a tight electron), false (else)
  */


  counter("NumeratorElectrons", kNumEls);

  if(!makeCut( _susyMod -> elIdSel       (c, elIdx, SusyModule::kTight, SusyModule::kLoose, true, true, branch), "electron id "  , "=", kNumEls)) return false;
  if(!makeCut( _susyMod -> elMvaSel         (elIdx, SusyModule::kTight, branch                                ), "electron mva"  , "=", kNumEls)) return false;
  if(!makeCut( _susyMod -> multiIsoSelInSitu(elIdx, SusyModule::kTight, branch                                ), "isolation"     , "=", kNumEls)) return false;
  if(!makeCut( _susyMod -> elHLTEmulSel     (elIdx, false, branch                                             ), "electron emu"  , "=", kNumEls)) return false;
  //if(!makeCut( _susyMod -> multiIsoSel (elIdx, SusyModule::kTight                            ), "isolation"     , "=", kNumEls)) return false;
  //if(!makeCut( _susyMod -> invPtRelSel (elIdx, SusyModule::kTight                            ), "only low pTrel", "=", kNumEls)) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::numeratorMuonSelection(Candidate* c, unsigned int muIdx, string branch){
  /*
    does the selection of tight muons
    parameters: muIdx
    return: true (if the muon is a tight muon), false (else)
  */

  counter("NumeratorMuons", kNumMus);

  if(!makeCut( _susyMod -> muIdSel       (c, muIdx, SusyModule::kTight , true, true, branch), "mu id selection", "=", kNumMus)) return false;
  if(!makeCut( _susyMod -> multiIsoSelInSitu(muIdx, SusyModule::kMedium, branch            ), "isolation"      , "=", kNumMus)) return false;
  //if(!makeCut( _susyMod -> multiIsoSel(muIdx, SusyModule::kMedium      ), "isolation"      , "=", kNumMus)) return false;
  //if(!makeCut( _susyMod -> invPtRelSel(muIdx, SusyModule::kMedium      ), "only low pTrel" , "=", kNumMus)) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::signalRegionElectronSelection(Candidate* c, unsigned int elIdx, string branch){

  counter("SignalRegionElectrons", kSigEls);

  if(!_susyMod -> elIdSel     (c, elIdx, SusyModule::kTight, SusyModule::kTight, true, false, branch) ) return false;
  if(!_susyMod -> multiIsoSel (   elIdx, SusyModule::kTight, branch                                 ) ) return false;
  if(!_susyMod -> elHLTEmulSel(   elIdx, (_HT < 300), branch                                        ) ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::signalRegionMuonSelection(Candidate* c, unsigned int muIdx, string branch){

  counter("SignalRegionMuons", kSigMus);

  if(!_susyMod -> muIdSel    (c, muIdx, SusyModule::kTight, true, false, branch) ) return false;
  if(!_susyMod -> multiIsoSel(   muIdx, SusyModule::kMedium, branch            ) ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::vetoElectronSelection(Candidate* c, unsigned int elIdx, string branch){
  // veto electron -> for Z and gamma* veto

  counter("VetoElectrons", kVetEls);

  if(!_susyMod -> elIdSel     (c, elIdx, SusyModule::kLoose, SusyModule::kLoose, true, false, branch) ) return false;
  if(!_susyMod -> multiIsoSel (   elIdx, SusyModule::kDenom, branch                                 ) ) return false;
  if(!_susyMod -> elHLTEmulSel(   elIdx, false, branch                                              ) ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::vetoMuonSelection(Candidate* c, unsigned int muIdx, string branch){
  // veto muon -> for Z and gamma* veto

  counter("VetoMuons", kVetMus);

  if(!_susyMod -> muIdSel    (c, muIdx, SusyModule::kLoose, true, false, branch) ) return false;
  if(!_susyMod -> multiIsoSel(   muIdx, SusyModule::kDenom, branch             ) ) return false;

  return true;

}




/*****************************************************************************
******************************************************************************
** KINEMATIC REGION DEFINITIONS                                             **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FRinSitu::setCut(std::string var, float valCut, std::string cType, float upValCut) {
  /*
    sets the parameters (valCut, cType, upValCut) for a specific cut on a variable (var)
    parameters: var, valCut (the cut value), cType (the cut type), upValCut (the upper value
    in case one cuts the variable in a range)
    return: none
  */


  // FRinSitu region
	
  if(var == "HTSB") {
    _valCutHTSB   = valCut;
    _cTypeHTSB    = cType;
    _upValCutHTSB = upValCut;
  }

  else if(var == "METSB") {
    _valCutMETSB   = valCut;
    _cTypeMETSB    = cType;
    _upValCutMETSB = upValCut;
  }

  else if(var == "HTCondSB") {
    _valCutHTCondSB   = valCut;
    _cTypeHTCondSB    = cType;
    _upValCutHTCondSB = upValCut;
  }
  
  else if(var == "METLowSB") {
    _valCutMETLowSB   = valCut;
    _cTypeMETLowSB    = cType;
    _upValCutMETLowSB = upValCut;
  }
  
  else if(var == "METHighSB") {
    _valCutMETHighSB   = valCut;
    _cTypeMETHighSB    = cType;
    _upValCutMETHighSB = upValCut;
  }

  else if(var == "NJetsSB") {
    _valCutNJetsSB   = valCut;
    _cTypeNJetsSB    = cType;
    _upValCutNJetsSB = upValCut;
  } 
	
  else if(var == "NBJetsSB") {
    _valCutNBJetsSB   = valCut;
    _cTypeNBJetsSB    = cType;
    _upValCutNBJetsSB = upValCut;
  } 
	

}



//____________________________________________________________________________
void FRinSitu::setMeasurementRegion() {
  /*
    sets the cuts of the measurement region (_MR)
    parameters: none
    return: none
  */

  
  setCut("HTSB"     ,   80, ">" );
  setCut("METSB"    , -100, ">" );
  setCut("HTCondSB" ,  500, "<" );
  setCut("METHighSB",   30, ">" );
  setCut("METLowSB" ,    0, ">" );
  setCut("NBJetsSB" ,    0, ">=");

  //else if(_MR == "all") {
  //  setCut("HTSB"     ,   80, ">" );
  //  setCut("METSB"    , -100, ">" );
  //  setCut("HTCondSB" ,  500, "<" );
  //  setCut("METHighSB",   30, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //  setCut("NJetsSB"  ,    2, ">=");
  //  setCut("NBJetsSB" ,    0, ">=");
  //}
  //else if(_MR == "SB00") {
  //  setCut("HTSB"     ,   80, ">" );
  //  setCut("METSB"    , -100, ">" );
  //  setCut("HTCondSB" ,  500, "<" );
  //  setCut("METHighSB",   30, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //  setCut("NJetsSB"  ,    2, ">=");
  //  setCut("NBJetsSB" ,    0, "=" );
  //}
  //
  //else if(_MR == "SB10") {
  //  setCut("HTSB"     ,   80, ">" );
  //  setCut("METSB"    , -100, ">" );
  //  setCut("HTCondSB" ,  500, "<" );
  //  setCut("METHighSB",   30, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //  setCut("NJetsSB"  ,    2, ">=");
  //  setCut("NBJetsSB" ,    1, "=" );
  //}
  //
  //else if(_MR == "SB20") {
  //  setCut("HTSB"     ,   80, ">" );
  //  setCut("METSB"    , -100, ">" );
  //  setCut("HTCondSB" ,  500, "<" );
  //  setCut("METHighSB",   30, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //  setCut("NJetsSB"  ,    2, ">=");
  //  setCut("NBJetsSB" ,    2, "=" );
  //}
  //else if(_MR == "SB30") {
  //  setCut("HTSB"     ,   80, ">" );
  //  setCut("METSB"    , -100, ">" );
  //  setCut("HTCondSB" ,  500, "<" );
  //  setCut("METHighSB",   30, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //  setCut("NJetsSB"  ,    2, ">=");
  //  setCut("NBJetsSB" ,    3, ">=");
  //}

  //// CH: SUS-13-013 cuts
  //else if(_MR == "SB01") {
  //  setCut("HTSB"     ,  200, "[]", 400);
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    0, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB02") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    0, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB03") {
  //  setCut("HTSB"     ,  200, "[]", 400 );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    0, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB04") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    0, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB05") {
  //  setCut("HTSB"     ,  200, "[]", 400);
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    0, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB06") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    0, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB07") {
  //  setCut("HTSB"     ,  200, "[]", 400 );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    0, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB08") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    0, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
 

  //else if(_MR == "SB11") {
  //  setCut("HTSB"     ,  200, "[]", 400);
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    1, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB12") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    1, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB13") {
  //  setCut("HTSB"     ,  200, "[]", 400 );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    1, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB14") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    1, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB15") {
  //  setCut("HTSB"     ,  200, "[]", 400);
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    1, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB16") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    1, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB17") {
  //  setCut("HTSB"     ,  200, "[]", 400 );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    1, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB18") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    1, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
 

  //else if(_MR == "SB21") {
  //  setCut("HTSB"     ,  200, "[]", 400);
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    2, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB22") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    2, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB23") {
  //  setCut("HTSB"     ,  200, "[]", 400 );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    2, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB24") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,   50, "[]", 120);
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    2, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB25") {
  //  setCut("HTSB"     ,  200, "[]", 400);
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    2, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB26") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    2, "[]",   3);
  //  setCut("NBJetsSB" ,    2, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB27") {
  //  setCut("HTSB"     ,  200, "[]", 400 );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    2, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}
  //else if(_MR == "SB28") {
  //  setCut("HTSB"     ,  400, ">" );
  //  setCut("METSB"    ,  120, ">" );
  //  setCut("NJetsSB"  ,    4, ">=");
  //  setCut("NBJetsSB" ,    2, "=" );
  //  setCut("HTCondSB" ,    0, "<" );
  //  setCut("METHighSB", -100, ">" );
  //  setCut("METLowSB" , -100, ">" );
  //}

 


}





/*****************************************************************************
******************************************************************************
** EVENT SELECTIONS                                                         **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool FRinSitu::baseSelection(){
  /*
    implements the base selection that is fundamental for both the baseline 
    and the signal region selections
    parameters: none
    return: true (if event passes selection), false (else)
  */

  // triggers
  if(!makeCut(triggerSelection()         , "trigger selection"             )) return false;

  // lepton multiplicity
  if(!makeCut<int>( _nSigLeps            , 1, "=", "exactly one tight lep")) return false;
  if(!makeCut<int>( _nDenLeps            , 1, "=", "exactly one FO"       )) return false;

  // jet multiplicity
  //if(!makeCut<int>( _nGoodJets           , 2, ">=", "jet multiplicity"     )) return false;

  _lep1 = _sigLeps[0];
  _lep2 = _denLeps[0];
  _lep1idx = _sigLepsIdx[0];
  _lep2idx = _denLepsIdx[0];

  // gen matching if required
  if(_genMatching == 1) {
    if(!makeCut(genMatchedToFake(_lep2idx)                                 , "gen matching to fake" )) return false;
  }

  // same sign
  if(!makeCut( _lep1 -> charge() * _lep2 -> charge() > 0                   , "same sign requirement")) return false;

  // cross flavor for single lepton dataset
  if(_sampleName.find("datasl") != std::string::npos) {
    if(_sampleName.find("SingleElectron") != std::string::npos){
      if(!makeCut( std::abs(_lep1 -> pdgId()) == 11 && std::abs(_lep2 -> pdgId()) == 13, "cross flavor for single lepton dataset")) return false;
    }
    else if(_sampleName.find("SingleMuon") != std::string::npos){
      if(!makeCut( std::abs(_lep1 -> pdgId()) == 13 && std::abs(_lep2 -> pdgId()) == 11, "cross flavor for single lepton dataset")) return false;
    }
  }

  // mll veto
  if(!makeCut(_susyMod -> passMllSingleVeto(_lep1, _lep2,  0,   8, false)     , "low mass veto"        )) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::mrSelection(){



  int isotr = -1;
  int nontr = -1;
  for(int i = 0; i < _TR_lines.size(); ++i){
    if(_TR_lines[i].find("IsoVVL") != std::string::npos || _TR_lines[i].find("IsoVL") != std::string::npos)
      isotr = i;
    else
      nontr = i;
  }

  if(_iso){
    if(_nDenEls == 1)
      cout << Form("%d %6.2f %6.2f %5.2f %.2f %.2f %5.2f %5.2f %5.2f %1.2f %1i %6.0f", int(_vc->get("evt")), _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0].first, SusyModule::kTight, _denLepsIdx[0].second), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0].first), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0].first), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0].first), _vc->get("LepGood_mvaIdSpring15", _denLepsIdx[0].first), _met->pt(), _met->phi(), _nNumLeps, _trws[isotr]) << endl;
    //if(_nDenMus == 1)
    //  cout << Form("%d %6.2f %6.2f %5.2f %.2f %.2f %5.2f %5.2f %1.2f %1i %6.0f", int(_vc->get("evt")), _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kMedium), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _met->pt(), _met->phi(), _nNumLeps, _trws[isotr]) << endl;
  }

  //if(!_iso){
    //if(_nDenEls == 1)
    //  cout << Form("%d %6.2f %6.2f %5.2f %.2f %.2f %5.2f %5.2f %5.2f %1.2f %1i %6.0f", int(_vc->get("evt")), _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kTight), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _vc->get("LepGood_mvaIdSpring15", _denLepsIdx[0]), _met->pt(), _met->phi(), _nNumLeps, 1) << endl;
    //if(_nDenMus == 1)
    //  cout << Form("%d %6.2f %6.2f %5.2f %.2f %.2f %5.2f %5.2f %1.2f %1i %6.0f", int(_vc->get("evt")), _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kMedium), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _met->pt(), _met->phi(), _nNumLeps, 1) << endl;
   //}



  //if(_iso){
  //  if(_nDenEls == 1)
  //    cout << Form("Electron RunNb=%8.f LumiSc=%4.f EventNb=%10.f Trigger=%s PS=%5.f FO raw pt=%6.2f corr pt=%6.2f eta=%5.2f miniiso=%.2f ptratio     =%.2f ptrel=%5.2f mva=%5.2f MET=%5.2f isNum=%1i", _vc->get("run"), _vc->get("lumi"), _vc->get("evt"), _TR_lines[isotr].c_str(), _trws[isotr], _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kTight), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _vc->get("LepGood_mvaIdSpring15", _denLepsIdx[0]), _met->pt(), _nNumLeps) << endl;
  //  if(_nDenMus == 1)
  //    cout << Form("Muon RunNb=%8.f LumiSc=%4.f EventNb=%10.f Trigger=%s PS=%5.f FO raw pt=%6.2f corr pt=%6.2f eta=%5.2f miniiso=%.2f ptratio=%.2f ptrel=%5.2f MET=%5.2f isNum=%1i", _vc->get("run"), _vc->get("lumi"), _vc->get("evt"), _TR_lines[isotr].c_str(), _trws[isotr], _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kMedium), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _met->pt(), _nNumLeps) << endl;
  //}

  //if(!_iso){
  //  if(_nDenEls == 1)
  //    cout << Form("Electron RunNb=%8.f LumiSc=%4.f EventNb=%12.f Trigger=none PS=1 FO raw pt=%6.2f corr pt=%6.2f eta=%5.2f miniiso=%.2f ptratio=%.2f ptrel=%5.2f mva=%5.2f MET=%5.2f isNum=%1i", _vc->get("run"), _vc->get("lumi"), _vc->get("evt"), _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kTight), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _vc->get("LepGood_mvaIdSpring15", _denLepsIdx[0]), _met->pt(), _nNumLeps) << endl;
    //if(_nDenMus == 1)
    //  cout << Form("Muon RunNb=%8.f LumiSc=%4.f EventNb=%10.f Trigger=none PS=1 FO raw pt=%6.2f corr pt=%6.2f eta=%5.2f miniiso=%.2f ptratio=%.2f ptrel=%5.2f MET=%5.2f isNum=%1i", _vc->get("run"), _vc->get("lumi"), _vc->get("evt"), _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kMedium), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _met->pt(), _nNumLeps) << endl;
  //}
  
  //if(!_iso){
  //  if(_nDenEls == 1)
  //    cout << Form("Electron RunNb=%8.f LumiSc=%4.f EventNb=%12.f Trigger=%s PS=%5.f FO raw pt=%6.2f corr pt=%6.2f eta=%5.2f miniiso=%.2f ptratio     =%.2f ptrel=%5.2f mva=%5.2f MET=%5.2f isNum=%1i", _vc->get("run"), _vc->get("lumi"), _vc->get("evt"), _TR_lines[isotr].c_str(), _trws[isotr], _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kTight), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _vc->get("LepGood_mvaIdSpring15", _denLepsIdx[0]), _met->pt(), _nNumLeps) << endl;
  //  if(_nDenMus == 1)
  //    cout << Form("Muon RunNb=%8.f LumiSc=%4.f EventNb=%10.f Trigger=%s PS=%5.f FO raw pt=%6.2f corr pt=%6.2f eta=%5.2f miniiso=%.2f ptratio=%.2f ptrel=%5.2f MET=%5.2f isNum=%1i", _vc->get("run"), _vc->get("lumi"), _vc->get("evt"), _TR_lines[isotr].c_str(), _trws[isotr], _denLeps[0]->pt(), _susyMod->conePt(_denLepsIdx[0], SusyModule::kMedium), _denLeps[0]->eta(), _vc->get("LepGood_miniRelIso", _denLepsIdx[0]), _vc->get("LepGood_jetPtRatiov2", _denLepsIdx[0]), _vc->get("LepGood_jetPtRelv2", _denLepsIdx[0]), _met->pt(), _nNumLeps) << endl;
  //}

return true;

  // HT
  if(!makeCut<float>( _HT       , _valCutHTSB    , _cTypeHTSB  , "SB HT selection" , _upValCutHTSB      ) ) return false;

  // MET
  if(!makeCut<float>( _met->pt(), _valCutMETSB   , _cTypeMETSB , "SB MET selection", _upValCutMETSB      ) ) return false;

  if(_au->simpleCut( _HT, _valCutHTCondSB, _cTypeHTCondSB) ) {
    if(!makeCut<float>( _met->pt(), _valCutMETHighSB, _cTypeMETHighSB, "SB MET (HT<500) selection", _upValCutMETHighSB ) ) return false;
  }
  else {
    if(!makeCut<float>( _met->pt(), _valCutMETLowSB , _cTypeMETLowSB , "SB MET (HT>500) selection" , _upValCutMETLowSB ) ) return false;
  }

  //if(!makeCut<int>(_vc->get(_btag), _valCutNBJetsSB, _cTypeNBJetsSB, "SB b-jet multiplicity", _upValCutNBJetsSB) ) return false;


  return true;

} 


//____________________________________________________________________________
bool FRinSitu::skimSelection(){


  // lepton multiplicity
  if(!makeCut(  _nDenLeps >= 1                   ,          "FO multiplicity"    ) ) return false;
  if(!makeCut( (_nSigLeps == 1 || _nDenLeps >= 2),          "lepton multiplicity") ) return false;
  if(!makeCut<int>( _nGoodJets                   , 2, ">=", "jet multiplicity"   ) ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::triggerSelection(){

  counter("TriggerSelection", kTrigger);

  // Lesya's super-duper non-iso measurement without triggers on single lepton dataset
  if(_sampleName.find("datasl") != std::string::npos) {
    _iso = false;
    _exts    .push_back("non0");
    _trws    .push_back(1.0);
    _TR_lines.push_back("non");
    return true;
  }

  bool any = false; //passed at least one of any trigger
      _iso = false; //passed at least one of the isolated triggers
  vector<string> trlines;

  trlines = Tools::insertIntoVectorS(trlines, _vTR_lines_non);
  trlines = Tools::insertIntoVectorS(trlines, _vTR_lines_iso);
//DUMPVECTOR(_denLepsIdx);
//DUMPVECTOR(trlines);

  if(trlines.size() > 0){
    for(unsigned int i = 0; i < trlines.size(); ++i){

      if(Tools::trim(trlines[i]) != ""){
//cout << "testing " << trlines[i] << endl;
        bool testiso = false;
        if(trlines[i].find("IsoVL") != std::string::npos || trlines[i].find("IsoVVL") != std::string::npos) 
          testiso = true;
//DUMP(testiso);
//DUMP(_vc->get(Tools::trim(trlines[i])));
//DUMPVECTOR(_denLepsIdx);
//DUMPVECTOR(_isoLepsIdx);
        if(_vc->get(Tools::trim(trlines[i])) == 1) {
          if(testiso){
           if(_isoLepsIdx.size() == 0 || _isoLepsIdx[0] != _denLepsIdx[0])
             continue;
           _iso = true;
          }
          any = true;
          _TR_lines.push_back(Tools::trim(trlines[i]));
//DUMP(_iso);
//DUMP(any);
        }
      }

      //if(Tools::trim(trlines[i]) != ""){
      //  if(_vc->get(Tools::trim(trlines[i])) == 1) {
      //    any = true;
      //    _TR_lines.push_back(trlines[i]);
      //    if(trlines[i].find("IsoVL") != std::string::npos || trlines[i].find("IsoVVL") != std::string::npos){
      //      if(_isoLepsIdx.size() > 0 && _isoLepsIdx[0] == _denLepsIdx[0])
      //        _iso = true;
      //    }
      //  }
      //}
    }
  }

//DUMPVECTOR(trlines);
//DUMPVECTOR(_TR_lines);
  // at least one auxiliary trigger per pt bin to be passed
  if(!makeCut(any, "at least one trigger path", "=", kTrigger)) return false;


  // trigger extensions
  findTriggerExts();


  return true;

}



/*****************************************************************************
******************************************************************************
** EXECUTING TASKS                                                          **
******************************************************************************
*****************************************************************************/



//____________________________________________________________________________
void FRinSitu::fillEventPlots(){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill("MR_HT_"         + _exts[i], _HT                 , _weight * _trws[i]);
    fill("MR_MET_"        + _exts[i], _met->pt()          , _weight * _trws[i]);
    fill("MR_NumBJets_"   + _exts[i], _vc->get(_bvar)     , _weight * _trws[i]);
    fill("MR_NumDenEls_"  + _exts[i], _denEls .size()     , _weight * _trws[i]);
    fill("MR_NumDenLeps_" + _exts[i], _denLeps.size()     , _weight * _trws[i]);
    fill("MR_NumDenMus_"  + _exts[i], _denMus .size()     , _weight * _trws[i]);
    fill("MR_NumJets_"    + _exts[i], _nGoodJets          , _weight * _trws[i]);
    fill("MR_NumNumEls_"  + _exts[i], _numEls .size()     , _weight * _trws[i]);
    fill("MR_NumNumLeps_" + _exts[i], _numLeps.size()     , _weight * _trws[i]);
    fill("MR_NumNumMus_"  + _exts[i], _numMus .size()     , _weight * _trws[i]);
    fill("MR_NumVrtx_"    + _exts[i], _vc->get(_nvert)    , _weight * _trws[i]);
  }

}


//____________________________________________________________________________
void FRinSitu::fillFRMaps(string prepend, pair<unsigned int, string> lepIdx, int wp){

  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill(prepend + "MapPt_"     + _exts[i], overflowPt(_vc->get(lepIdx.second + "_pt", lepIdx.first            )), std::abs(_vc->get(lepIdx.second + "_eta", lepIdx.first)), _weight * _trws[i]);
    fill(prepend + "MapPtJet_"  + _exts[i], overflowPt(_susyMod -> closestJetPt(lepIdx.first, lepIdx.second    )), std::abs(_vc->get(lepIdx.second + "_eta", lepIdx.first)), _weight * _trws[i]);
    fill(prepend + "MapPtCorr_" + _exts[i], overflowPt(_susyMod -> conePt      (lepIdx.first, wp, lepIdx.second)), std::abs(_vc->get(lepIdx.second + "_eta", lepIdx.first)), _weight * _trws[i]);
  }

}


//____________________________________________________________________________
void FRinSitu::fillFakeRatioMaps(){
  /*
    fills the fake ratio maps for leptons
    parameters: none
    return: none
  */


  fillFRMaps("MR_Den" + findLepAbbr(_lep2), _lep2idx, findLepWP(_lep2));
  if(find(_numLepsIdx.begin(), _numLepsIdx.end(), _lep2idx) != _numLepsIdx.end()){ 
    fillFRMaps("MR_Num" + findLepAbbr(_lep2), _lep2idx, findLepWP(_lep2));
    fillFRMaps("MR_Rat" + findLepAbbr(_lep2), _lep2idx, findLepWP(_lep2));
  }

  if(_nSigLeps == 0){
    fillFRMaps("MR_Den" + findLepAbbr(_lep1), _lep1idx, findLepWP(_lep1));
    if(find(_numLepsIdx.begin(), _numLepsIdx.end(), _lep1idx) != _numLepsIdx.end()){ 
      fillFRMaps("MR_Num" + findLepAbbr(_lep1), _lep1idx, findLepWP(_lep1));
      fillFRMaps("MR_Rat" + findLepAbbr(_lep1), _lep1idx, findLepWP(_lep1));
    }
  }

}

 
//____________________________________________________________________________ 
void FRinSitu::fillLepPlots(string prepend, Candidate * lep, pair<unsigned int, string> lepIdx, int wp){ 
  /* 
    fills the control plots for leptons PER LEPTON 
  */   

  float MT = _susyMod -> Mt(lep, _met, lepIdx.first, -1, lepIdx.second, "", findLepWP(lep));

  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill(prepend + "Pt_"       + _exts[i],          _vc->get(lepIdx.second + "_pt"        , lepIdx.first) , _weight * _trws[i]);
    fill(prepend + "Eta_"      + _exts[i], std::abs(_vc->get(lepIdx.second + "_eta"       , lepIdx.first)), _weight * _trws[i]);
    fill(prepend + "EtaFR_"    + _exts[i], std::abs(_vc->get(lepIdx.second + "_eta"       , lepIdx.first)), _weight * _trws[i]);
    fill(prepend + "DXY_"      + _exts[i], std::abs(_vc->get(lepIdx.second + "_dxy"       , lepIdx.first)), _weight * _trws[i]);
    fill(prepend + "DZ_"       + _exts[i], std::abs(_vc->get(lepIdx.second + "_dz"        , lepIdx.first)), _weight * _trws[i]);
    fill(prepend + "SIP_"      + _exts[i],          _vc->get(lepIdx.second + "_sip3d"     , lepIdx.first) , _weight * _trws[i]);
    fill(prepend + "RelIso_"   + _exts[i],          _vc->get(lepIdx.second + "_relIso03"  , lepIdx.first) , _weight * _trws[i]);
    fill(prepend + "MiniIso_"  + _exts[i],          _vc->get(lepIdx.second + "_miniRelIso", lepIdx.first) , _weight * _trws[i]);
    fill(prepend + "PtRel_"    + _exts[i],          _vc->get(lepIdx.second + "_jetPtRelv2", lepIdx.first) , _weight * _trws[i]);
    fill(prepend + "MT_"       + _exts[i], MT                                                             , _weight * _trws[i]);
    fill(prepend + "PtJet_"    + _exts[i], _susyMod -> closestJetPt(lepIdx.first, lepIdx.second)          , _weight * _trws[i]);
    fill(prepend + "PtCorr_"   + _exts[i], _susyMod -> conePt(lepIdx.first, wp, lepIdx.second)            , _weight * _trws[i]);
    fill(prepend + "PtCorrFR_" + _exts[i], overflowPt(_susyMod -> conePt(lepIdx.first, wp, lepIdx.second)), _weight * _trws[i]);
  }
 
} 


//____________________________________________________________________________
void FRinSitu::fillLeptonPlots(){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  fillLepPlots("MR_Den" + findLepAbbr(_lep2), _lep2, _lep2idx, findLepWP(_lep2));
  if(find(_numLepsIdx.begin(), _numLepsIdx.end(), _lep2idx) != _numLepsIdx.end()){ 
    fillLepPlots("MR_Num" + findLepAbbr(_lep2), _lep2, _lep2idx, findLepWP(_lep2));
  }

  if(_nSigLeps == 0){
    fillLepPlots("MR_Den" + findLepAbbr(_lep1), _lep1, _lep1idx, findLepWP(_lep1));
    if(find(_numLepsIdx.begin(), _numLepsIdx.end(), _lep1idx) != _numLepsIdx.end()){ 
      fillLepPlots("MR_Num" + findLepAbbr(_lep1), _lep1, _lep1idx, findLepWP(_lep1));
    }
  }

}


//____________________________________________________________________________
string FRinSitu::findLepAbbr(Candidate* lep){

  if(std::abs(lep->pdgId()) == 11) return "El";
  return "Mu";

}


//____________________________________________________________________________
string FRinSitu::findLepAbbr(pair<unsigned int, string> idx){

  if(std::abs(_vc->get(idx.second + "_pdgId", idx.first)) == 11) return "El";
  return "Mu";

}


//____________________________________________________________________________
int FRinSitu::findLepWP(Candidate* lep){

  if(std::abs(lep->pdgId()) == 11) return SusyModule::kTight;
  return SusyModule::kMedium;

}


//____________________________________________________________________________
int FRinSitu::findLepWP(pair<unsigned int, string> idx){

  if(std::abs(_vc->get(idx.second + "_pdgId", idx.first)) == 11) return SusyModule::kTight;
  return SusyModule::kMedium;

}


//____________________________________________________________________________
void FRinSitu::findTriggerExts(){

  for(unsigned int i = 0; i < _TR_lines.size(); ++i){
    vector<string>::iterator pos = find(_vTR_lines_non.begin(), _vTR_lines_non.end(), _TR_lines[i]);
    if(pos != _vTR_lines_non.end()){
      _exts.push_back("non" + Tools::intToString(pos - _vTR_lines_non.begin()));
      _trws.push_back(1.0);
      //_trws.push_back(_vc->get(_vTR_psb_non[pos - _vTR_lines_non.begin()]));
    }
  }

  if(_iso){
    for(unsigned int i = 0; i < _TR_lines.size(); ++i){
      vector<string>::iterator pos = find(_vTR_lines_iso.begin(), _vTR_lines_iso.end(), _TR_lines[i]);
      if(pos != _vTR_lines_iso.end()){
        _exts.push_back("iso" + Tools::intToString(pos - _vTR_lines_iso.begin()));
        _trws.push_back(1.0);
        //_trws.push_back(_vc->get(_vTR_psb_iso[pos - _vTR_lines_iso.begin()]));
      }
    }
  }
}


//____________________________________________________________________________
bool FRinSitu::genMatchedToFake(pair<unsigned int, string> idx) {

  if (_vc->get("isData") == 1) return false;

  int id1  = _vc->get(idx.second + "_mcMatchId" , idx.first); 
  if(id1==0) return true;

  return false;
}


//____________________________________________________________________________
float FRinSitu::overflowPt(float rawPt){

    if(rawPt >= 70.) return 60.;

    return rawPt;
}


