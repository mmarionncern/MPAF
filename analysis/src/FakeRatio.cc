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


#include "analysis/src/FakeRatio.hh"





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
FakeRatio::FakeRatio(std::string cfg){
  /* 
     constructs the FakeRatio class 
     parameters: configuration_file
     return: none
  */
  
  startExecution(cfg);
  initialize();

}


//____________________________________________________________________________
FakeRatio::~FakeRatio(){
  /* 
     destructs the FakeRatio class 
     parameters: none
     return: none
  */

}


//____________________________________________________________________________
int FakeRatio::findBin(vector<float> list, float value){

  int idx = -1;
  float diff = 9999999999;
  for(unsigned int i = 0; i < list.size(); ++i){
    if(list[i] <= value && value - list[i] < diff){
      diff = value - list[i];
      idx = i;
    }
  }

  return idx;

}


//____________________________________________________________________________
vector<vector<vector<string> > > FakeRatio::findTriggerLines(vector<vector<string> > trigger_lines, \
                                                             vector<float> trigger_pts, vector<float> trigger_etas, \
                                                             vector<float> search_pts , vector<float> search_etas){

  vector<vector<vector<string> > > result_lines;
  result_lines.resize(search_etas.size());

  // CH: this is a bit nasty, we put in etaidxs and ptidxs only the last
  // bin, that we have found, we should be able to put more there

  string line = "";
  for(unsigned int ii = 0; ii < search_etas.size(); ++ii){
    result_lines[ii].resize(search_pts.size());
	vector<int> etaidxs;
    etaidxs.push_back(findBin(trigger_etas, search_etas[ii]));
    for(unsigned int ij = 0; ij < search_pts.size(); ++ij){
      vector<int> ptidxs;
      ptidxs.push_back(findBin(trigger_pts, search_pts[ij]));
      for(unsigned int ie = 0; ie < etaidxs.size(); ++ie)
        for(unsigned int ip = 0; ip < ptidxs.size(); ++ip)
          if(etaidxs[ie] == -1 || ptidxs[ip] == -1) line = "";
          else line = trigger_lines[etaidxs[ie]][ptidxs[ip]];
          result_lines[ii][ij].push_back(line);
    }
  } 

  return result_lines;

}


//____________________________________________________________________________
vector<float> FakeRatio::findTriggerPts(vector<vector<string> > trigger_lines, string name){

  vector<float> trigger_pts;
  for(unsigned int i = 0; i < trigger_lines[0].size(); ++i){
    unsigned int pos = trigger_lines[0][i].find(name) + name.size();
    string num = trigger_lines[0][i].substr(pos, trigger_lines[0][i].find("_", pos) - pos);
    trigger_pts.push_back(atof(num.c_str()));
  }

  return trigger_pts;

}


//____________________________________________________________________________
void FakeRatio::initialize(){
  /*
    initializes the FakeRatio class
    parameters: none
    return: none
  */


  // trigger lines
 
  //string TR_lines_el_non[1] = {"HLT_FR_Ele12_CaloIdM_TrackIdM_PFJet30"};
  //string TR_lines_el_iso[1] = {"HLT_FR_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30"};
  //string TR_lines_mu_non[1] = {"HLT_FR_Mu17"};
  //string TR_lines_mu_iso[1] = {"HLT_FR_Mu17_TrkIsoVVL"};


  string TR_lines_el_non[4] = {"HLT_FR_Ele8_CaloIdM_TrackIdM_PFJet30" , \
                               "HLT_FR_Ele12_CaloIdM_TrackIdM_PFJet30", \
                               "HLT_FR_Ele23_CaloIdM_TrackIdM_PFJet30", \
                               "HLT_FR_Ele33_CaloIdM_TrackIdM_PFJet30"};
  string TR_lines_el_iso[3] = {"HLT_FR_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30", \
                               "HLT_FR_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30", \
                               "HLT_FR_Ele33_CaloIdL_TrackIdL_IsoVL_PFJet30"};
  string TR_lines_mu_non[2] = {"HLT_FR_Mu8" , \
                               "HLT_FR_Mu17"};
  string TR_lines_mu_iso[2] = {"HLT_FR_Mu8_TrkIsoVVL" , \
                               "HLT_FR_Mu17_TrkIsoVVL"};
  //                             "HLT_FR_Ele18_CaloIdM_TrackIdM_PFJet30", \
  //                             "HLT_FR_Ele18_CaloIdL_TrackIdL_IsoVL_PFJet30", \
  //string TR_lines_mu_non[4] = {"HLT_FR_Mu8" , \
  //                             "HLT_FR_Mu17", \
  //                             "HLT_FR_Mu24", \
  //                             "HLT_FR_Mu34"};
  //string TR_lines_mu_iso[4] = {"HLT_FR_Mu8_TrkIsoVVL" , \
  //                             "HLT_FR_Mu17_TrkIsoVVL", \
  //                             "HLT_FR_Mu24_TrkIsoVVL", \
  //                             "HLT_FR_Mu34_TrkIsoVVL"};

  vector<string> veln = Tools::toVector(TR_lines_el_non);
  vector<string> veli = Tools::toVector(TR_lines_el_iso);
  vector<string> vmun = Tools::toVector(TR_lines_mu_non);
  vector<string> vmui = Tools::toVector(TR_lines_mu_iso);

  // trigger effective luminosities
  //float TR_efflum_el_non[1] = {getCfgVarF("LUMINOSITY_ELE12")};
  //float TR_efflum_el_iso[1] = {getCfgVarF("LUMINOSITY_ELE12_ISO")};
  //float TR_efflum_mu_non[1] = {getCfgVarF("LUMINOSITY_MU17")};
  //float TR_efflum_mu_iso[1] = {getCfgVarF("LUMINOSITY_MU17_ISO")};

  float TR_efflum_el_non[5] = {getCfgVarF("LUMINOSITY_ELE8") , \
                               getCfgVarF("LUMINOSITY_ELE12"), \
                               getCfgVarF("LUMINOSITY_ELE18"), \
                               getCfgVarF("LUMINOSITY_ELE23"), \
                               getCfgVarF("LUMINOSITY_ELE33")};
  float TR_efflum_el_iso[4] = {getCfgVarF("LUMINOSITY_ELE12_ISO"), \
                               getCfgVarF("LUMINOSITY_ELE18_ISO"), \
                               getCfgVarF("LUMINOSITY_ELE23_ISO"), \
                               getCfgVarF("LUMINOSITY_ELE33_ISO")};
  float TR_efflum_mu_non[2] = {getCfgVarF("LUMINOSITY_MU8") , \
                               getCfgVarF("LUMINOSITY_MU17")};
  float TR_efflum_mu_iso[2] = {getCfgVarF("LUMINOSITY_MU8_ISO") , \
                               getCfgVarF("LUMINOSITY_MU17_ISO")};
  //float TR_efflum_mu_non[4] = {getCfgVarF("LUMINOSITY_MU8") , \
  //                             getCfgVarF("LUMINOSITY_MU17"), \
  //                             getCfgVarF("LUMINOSITY_MU24"), \
  //                             getCfgVarF("LUMINOSITY_MU34")};
  //float TR_efflum_mu_iso[4] = {getCfgVarF("LUMINOSITY_MU8_ISO") , \
  //                             getCfgVarF("LUMINOSITY_MU17_ISO"), \
  //                             getCfgVarF("LUMINOSITY_MU24_ISO"), \
  //                             getCfgVarF("LUMINOSITY_MU34_ISO")};

  // trigger lines
  _vTR_lines_el_non.push_back(veln);
  _vTR_lines_el_iso.push_back(veli);
  _vTR_lines_mu_non.push_back(vmun);
  _vTR_lines_mu_iso.push_back(vmui);

  // trigger effective luminosities
  _vTR_efflum_el_non = Tools::toVector(TR_efflum_el_non);
  _vTR_efflum_el_iso = Tools::toVector(TR_efflum_el_iso);
  _vTR_efflum_mu_non = Tools::toVector(TR_efflum_mu_non);
  _vTR_efflum_mu_iso = Tools::toVector(TR_efflum_mu_iso);

  // trigger pt bins
  _vTR_bins_pt_el_non = findTriggerPts(_vTR_lines_el_non, "Ele");
  _vTR_bins_pt_el_iso = findTriggerPts(_vTR_lines_el_iso, "Ele");
  _vTR_bins_pt_mu_non = findTriggerPts(_vTR_lines_mu_non, "Mu");
  _vTR_bins_pt_mu_iso = findTriggerPts(_vTR_lines_mu_iso, "Mu");

  // trigger eta bins
  _vTR_bins_eta_el.push_back(0);
  _vTR_bins_eta_mu.push_back(0);

  
  // fake ratio pt bins
  float FR_bins_pt_el[6]  = {10.0, 15.0, 25.0, 35.0, 50.0, 70.0};
  float FR_bins_pt_mu[6]  = {10.0, 15.0, 25.0, 35.0, 50.0, 70.0};
  _vFR_bins_pt_el  = Tools::toVector(FR_bins_pt_el );
  _vFR_bins_pt_mu  = Tools::toVector(FR_bins_pt_mu );

  // fake ratio eta bins
  float FR_bins_eta_el[4] = { 0.0, 1.0, 2.0, 2.5};
  float FR_bins_eta_mu[4] = { 0.0, 1.0, 2.0, 2.4};
  _vFR_bins_eta_el = Tools::toVector(FR_bins_eta_el);
  _vFR_bins_eta_mu = Tools::toVector(FR_bins_eta_mu);


  // trigger - fake ratio correspondence lines
  // i.e. which trigger line do we need for a given fake ratio pt bin? 
  _vTR_lineperpteta_el_non = findTriggerLines(_vTR_lines_el_non, _vTR_bins_pt_el_non, _vTR_bins_eta_el, _vFR_bins_pt_el, _vFR_bins_eta_el);
  _vTR_lineperpteta_el_iso = findTriggerLines(_vTR_lines_el_iso, _vTR_bins_pt_el_iso, _vTR_bins_eta_el, _vFR_bins_pt_el, _vFR_bins_eta_el);
  _vTR_lineperpteta_mu_non = findTriggerLines(_vTR_lines_mu_non, _vTR_bins_pt_mu_non, _vTR_bins_eta_mu, _vFR_bins_pt_mu, _vFR_bins_eta_mu);
  _vTR_lineperpteta_mu_iso = findTriggerLines(_vTR_lines_mu_iso, _vTR_bins_pt_mu_iso, _vTR_bins_eta_mu, _vFR_bins_pt_mu, _vFR_bins_eta_mu);


  //Tree Variables
  _bvar  = "nBJetMedium25";
  _leps  = "LepGood";
  _jets  = "Jet"; 
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
  _vc->registerVar("n" + _leps                     );
  _vc->registerVar(_leps + "_pt"                   );
  _vc->registerVar(_leps + "_eta"                  );
  _vc->registerVar(_leps + "_phi"                  );
  _vc->registerVar(_leps + "_charge"               );
  _vc->registerVar(_leps + "_tightCharge"          );
  _vc->registerVar(_leps + "_mediumMuonId"         );
  _vc->registerVar(_leps + "_mvaIdPhys14"          );
  _vc->registerVar(_leps + "_mvaIdSpring15"        );
  _vc->registerVar(_leps + "_pdgId"                );
  _vc->registerVar(_leps + "_relIso03"             );
  _vc->registerVar(_leps + "_relIso04"             );
  _vc->registerVar(_leps + "_jetPtRatiov2"         );
  _vc->registerVar(_leps + "_jetPtRelv2"           );
  _vc->registerVar(_leps + "_jetRawPt"             );
  _vc->registerVar(_leps + "_jetCorrFactor_L1L2L3Res");
  _vc->registerVar(_leps + "_miniRelIso"           );
  _vc->registerVar(_leps + "_chargedHadRelIso03"   );
  _vc->registerVar(_leps + "_miniRelIso"           );
  _vc->registerVar(_leps + "_miniRelIso"           );
  _vc->registerVar(_leps + "_dxy"                  );
  _vc->registerVar(_leps + "_dz"                   );
  _vc->registerVar(_leps + "_sip3d"                );
  _vc->registerVar(_leps + "_pfMuonId"             );
  _vc->registerVar(_leps + "_tightId"              );
  _vc->registerVar(_leps + "_looseIdSusy"          );
  _vc->registerVar(_leps + "_convVeto"             );
  _vc->registerVar(_leps + "_lostHits"             );
  _vc->registerVar(_leps + "_eleCutIdCSA14_50ns_v1");
  _vc->registerVar(_leps + "_eleCutIdCSA14_50ns_v1");
  _vc->registerVar(_leps + "_eleCutId2012_full5x5" );
  _vc->registerVar(_leps + "_mvaSusyPHYS14"        );
  _vc->registerVar(_leps + "_mvaSusy"              );
  _vc->registerVar(_leps + "_mcMatchId"            );
  _vc->registerVar(_leps + "_mcMatchAny"           );
  _vc->registerVar(_leps + "_jetBTagCSV"           );
  _vc->registerVar(_leps + "_sigmaIEtaIEta"        );
  _vc->registerVar(_leps + "_hadronicOverEm"       );
  _vc->registerVar(_leps + "_eInvMinusPInv"        );
  _vc->registerVar(_leps + "_dEtaScTrkIn"          );
  _vc->registerVar(_leps + "_dPhiScTrkIn"          );
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
  registerTriggerVars();


  //additional counter categories
  _au->addCategory( kEwkSel  , "Ewk Enriched MR Sel"  );
  _au->addCategory( kQcdSel  , "Qcd Enriched MR Sel"  );
  _au->addCategory( kTrigger , "Trigger Sel"          );
  _au->addCategory( kSync    , "Sync Sel"             );
  _au->addCategory( kDenEls  , "Denominator Electrons");
  _au->addCategory( kNumEls  , "Numerator Electrons"  );
  _au->addCategory( kVetEls  , "Veto Electrons"       );
  _au->addCategory( kDenMus  , "Denominator Muons"    );
  _au->addCategory( kNumMus  , "Numerator Muons"      );
  _au->addCategory( kVetMus  , "Veto Muons"           );
  _au->addCategory( kGoodJets, "Good Jets"            );

  //SusyModule
  _susyMod = new SusyModule(_vc);

  //Databases
  _dbm -> loadDb("XS", "XSectionsSpring15.db");  
  _dbm -> loadDb("KF", "kFactorsSpring15.db");  

  //input Variables
  //_lumi   = getCfgVarF("LUMINOSITY");
  _norm   = getCfgVarS("NORMALIZATION");
  _ewkSub = getCfgVarS("EWKSUB"); // all, el, mu

  //default Variables
  _doEwkSub = false;

}


//____________________________________________________________________________
void FakeRatio::run(){


  _TR_lines.clear();
  _TR_idx = -1;

  _denEls .clear();
  _denLeps.clear();
  _denMus .clear();
  _numEls .clear();
  _numLeps.clear();
  _numMus .clear();
  _vetEls .clear();
  _vetLeps.clear();
  _vetMus .clear();

  _goodJets.clear();

  _denElsIdx .clear();
  _denLepsIdx.clear();
  _denMusIdx .clear();
  _numElsIdx .clear();
  _numLepsIdx.clear();
  _numMusIdx .clear();

  counter("denominator");
  counter("denominator", kEwkSel);
  counter("denominator", kQcdSel);

  counter("all events", kSync);

  // trigger selection
  triggerSelectionLite();
  //triggerSelection();
  if(_vc->get("HLT_FR_Mu17") != 1) return;
  counter("trigger", kSync);

  // prepare event selection
  _met = Candidate::create(_vc->get(_mets + "_pt"), _vc->get(_mets + "_phi") );
  collectKinematicObjects();
	
  // skimming
  //if(!skimSelection()) return;
  //fillSkimTree();
  //return;

  // ewk-enriched measurement region selection
  if(ewkSelection()) {
    fillEwkEventPlots();
    fillEwkLeptonPlots();
  }

  // qcd-enriched measurement region
  if(qcdSelection()){
    fillQcdEventPlots();
    fillQcdFakeRatioMaps();
  }

  // measurement region selection
  if(!mrSelection()) return;

  // calling the modules
  fillEventPlots   ();
  fillFakeRatioMaps();
  fillJetPlots     ();
  fillLeptonPlots  ();
	
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::defineOutput(){

  /*
    defines and reserves all output that is produced in this class
    parameters: none
    return: none
  */ 


  // leptons
  string MR_els[3]  = {"MR_DenEl", "MR_NumEl", "MR_RatEl"};
  string MR_leps[4] = {"MR_DenEl", "MR_NumEl", "MR_DenMu", "MR_NumMu"};
  string MR_mus[3]  = {"MR_DenMu", "MR_NumMu", "MR_RatMu"};

  string ER_leps[4] = {"ER_DenEl", "ER_NumEl", "ER_DenMu", "ER_NumMu"};

  string QR_els[6]  = {"QR_small_DenEl", "QR_small_NumEl", "QR_small_RatEl", "QR_large_DenEl", "QR_large_NumEl", "QR_large_RatEl"};
  string QR_leps[4] = {"QR_DenEl", "QR_NumEl", "QR_DenMu", "QR_NumMu"};
  string QR_mus[6]  = {"QR_small_DenMu", "QR_small_NumMu", "QR_small_RatMu", "QR_large_DenMu", "QR_large_NumMu", "QR_large_RatMu"};

  vector<string> vMR_els  = Tools::toVector(MR_els);
  vector<string> vMR_leps = Tools::toVector(MR_leps);
  vector<string> vMR_mus  = Tools::toVector(MR_mus);

  vector<string> vER_leps = Tools::toVector(ER_leps);

  vector<string> vQR_els  = Tools::toVector(QR_els);
  vector<string> vQR_leps = Tools::toVector(QR_leps);
  vector<string> vQR_mus  = Tools::toVector(QR_mus);

  // Setting Measurement Region
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


  // Electroweak-Enriched Region
  registerVariable("ER_HT"              , 1000,  0.0, 1000.0, "H_T [GeV]"                            ); 
  registerVariable("ER_MET"             , 1000,  0.0, 1000.0, "#slash{E}_T [GeV]"                    );
  
  registerLepPlots(vER_leps, "DXY"      , 5000,  0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(vER_leps, "DZ"       , 5000,  0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(vER_leps, "SIP"      , 1000,  0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(vER_leps, "Eta"      ,  240,  0.0,    2.4, "#||{#eta(lep)}"                       );
  registerLepPlots(vER_leps, "MiniIso"  ,   50,  0.0,    1.0, "PF MiniIso (lep)"                     );
  registerLepPlots(vER_leps, "MT"       ,   20,  0.0,  200.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(vER_leps, "MT0"      ,   20,  0.0,  200.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(vER_leps, "MT1"      ,   20,  0.0,  200.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(vER_leps, "Pt"       , 1000,  0.0, 1000.0, "P_T(lep) [GeV]"                       );

  // Electroweak-Enriched Region
  registerVariable("QR_HT"              , 1000,  0.0, 1000.0, "H_T [GeV]"                            ); 
  registerVariable("QR_MET"             , 1000,  0.0, 1000.0, "#slash{E}_T [GeV]"                    );
  registerVariable("QR_MET_small"       ,    1,  0.0,   20.0, "#slash{E}_T [GeV]"                    );
  registerVariable("QR_MET_large"       ,    1, 45.0,   80.0, "#slash{E}_T [GeV]"                    );

  registerLepPlots(vQR_leps, "DXY"      , 5000,  0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(vQR_leps, "DZ"       , 5000,  0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(vQR_leps, "SIP"      , 1000,  0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(vQR_leps, "Eta"      ,  240,  0.0,    2.4, "#||{#eta(lep)}"                       );
  registerLepPlots(vQR_leps, "MiniIso"  ,   50,  0.0,    1.0, "PF MiniIso (lep)"                     );
  registerLepPlots(vQR_leps, "MT"       ,   20,  0.0,  200.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(vQR_leps, "MT0"      ,   20,  0.0,  200.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(vQR_leps, "Pt"       , 1000,  0.0, 1000.0, "P_T(lep) [GeV]"                       );

  // fake ratio maps in both MET bins 
  registerLepPlots(vQR_els, "MapPt"     , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "P_T(e) [GeV]"                 , "#||{#eta}(e)"  ); 
  registerLepPlots(vQR_els, "MapPtJet"  , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "P_T(jet closest to e) [GeV]"  , "#||{#eta}(e)"  ); 
  registerLepPlots(vQR_els, "MapPtCorr" , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "cone corr. P_T(e) [GeV]"      , "#||{#eta}(e)"  ); 
  registerLepPlots(vQR_mus, "MapPt"     , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "P_T(#mu) [GeV]"               , "#||{#eta}(#mu)"); 
  registerLepPlots(vQR_mus, "MapPtJet"  , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "P_T(jet closest to #mu) [GeV]", "#||{#eta}(#mu)"); 
  registerLepPlots(vQR_mus, "MapPtCorr" , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "cone corr. P_T(#mu) [GeV]"    , "#||{#eta}(#mu)"); 
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

  registerLepPlots(vMR_leps, "eInvMinusPInvEB", 50,  0.0,  0.1, "#||{1/e-1/p}"                         );
  registerLepPlots(vMR_leps, "eInvMinusPInvEE", 50,  0.0,  0.1, "#||{1/e-1/p}"                         );
  registerLepPlots(vMR_leps, "DXY"      , 5000,  0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(vMR_leps, "DZ"       , 5000,  0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(vMR_leps, "SIP"      , 1000,  0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(vMR_leps, "Eta"      ,  240,  0.0,    2.4, "#||{#eta(lep)}"                       );
  registerLepPlots(vMR_leps, "RelIso"   ,   50,  0.0,    1.0, "PF RelIso (lep)"                      );
  registerLepPlots(vMR_leps, "MiniIso"  ,   50,  0.0,    1.0, "PF MiniIso (lep)"                     );
  registerLepPlots(vMR_leps, "MT"       , 1000,  0.0, 1000.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(vMR_leps, "Pt"       , 1000,  0.0, 1000.0, "P_T(lep) [GeV]"                       );
  registerLepPlots(vMR_leps, "PtJet"    , 1000,  0.0, 1000.0, "P_T(jet closest to lep) [GeV]"        );
  registerLepPlots(vMR_leps, "PtCorr"   , 1000,  0.0, 1000.0, "cone corr. P_T(lep) [GeV]"            );
  registerLepPlots(vMR_leps, "PtRel"    , 1000,  0.0, 1000.0, "PtRel(lep)"                           );

  // fake ratio maps electrons 
  registerLepPlots(vMR_els, "MapTrTest" , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "P_T(e) [GeV]"                 , "#||{#eta}(e)"); 
  registerLepPlots(vMR_els, "MapPt"     , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "P_T(e) [GeV]"                 , "#||{#eta}(e)"); 
  registerLepPlots(vMR_els, "MapPtJet"  , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "P_T(jet closest to e) [GeV]"  , "#||{#eta}(e)"); 
  registerLepPlots(vMR_els, "MapPtCorr" , _vFR_bins_pt_el .size()-1, _vFR_bins_pt_el , \
                                          _vFR_bins_eta_el.size()-1, _vFR_bins_eta_el, "cone corr. P_T(e) [GeV]"      , "#||{#eta}(e)"); 
  // fake ratio maps muons
  registerLepPlots(vMR_mus, "MapTrTest" , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "P_T(#mu) [GeV]"               , "#||{#eta}(#mu)"); 
  registerLepPlots(vMR_mus, "MapPt"     , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "P_T(#mu) [GeV]"               , "#||{#eta}(#mu)"); 
  registerLepPlots(vMR_mus, "MapPtJet"  , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu , \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "P_T(jet closest to #mu) [GeV]", "#||{#eta}(#mu)"); 
  registerLepPlots(vMR_mus, "MapPtCorr" , _vFR_bins_pt_mu .size()-1, _vFR_bins_pt_mu, \
                                          _vFR_bins_eta_mu.size()-1, _vFR_bins_eta_mu, "cone corr. P_T(#mu) [GeV]"    , "#||{#eta}(#mu)"); 
 
}


//____________________________________________________________________________
void FakeRatio::divideFRMap(string postpend){

  for(unsigned int i = 0; i < _numDS + _idxs.size(); ++i){
    if(i == _idx_datacorrCERN) continue;
    TH2F * denom = (TH2F*) _hm -> getHisto("MR_Den" + postpend, i);
    TH2F * num   = (TH2F*) _hm -> getHisto("MR_Rat" + postpend, i);
//if(i == _idx_datacorrETH){
//cout << "dividing MR_Rat" << postpend << endl;
//cout << denom -> GetName() << endl;
//cout << denom -> Integral() << endl;
//cout << num -> GetName() << endl;
//cout << num -> Integral() << endl;
//for(int i = 1; i <= num->GetNbinsX(); ++i)
//cout << "bin " << i << ": " << num->GetBinContent(i) << endl;
//}
    num -> Divide(denom);
  }
 
}


//____________________________________________________________________________
void FakeRatio::divideFRMaps(){

  vector<string> exts;
  exts.push_back("non");
  exts.push_back("iso");

  for(unsigned int i = 0; i < _vTR_lines_el_non[0].size(); ++i) exts.push_back("non" + Tools::intToString(i));
  for(unsigned int i = 0; i < _vTR_lines_mu_non[0].size(); ++i) exts.push_back("non" + Tools::intToString(i));
  for(unsigned int i = 0; i < _vTR_lines_el_iso[0].size(); ++i) exts.push_back("iso" + Tools::intToString(i));
  for(unsigned int i = 0; i < _vTR_lines_mu_iso[0].size(); ++i) exts.push_back("iso" + Tools::intToString(i));

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
void FakeRatio::doEwkSub(){


  bool foundData = false;
  bool foundEwk  = false;
  bool foundQcd  = false;

  for(int i = 0; i < _numDS; ++i){
    
    string sname = _datasets[i]->getName();

    if     (sname.find("data") != std::string::npos) foundData = true;
    else if(sname.find("ewk")  != std::string::npos) foundEwk  = true;
    else if(sname.find("qcd")  != std::string::npos) foundQcd  = true;

  }

  if(foundData && foundEwk && foundQcd) 
    _doEwkSub = true;

}


//  ____________________________________________________________________________
vector<float> FakeRatio::doubleFit(string ext, TH1* h_data, TH1* h_ewk, TH1* h_qcd, float hmin, float hmax){

  TH1* ch_data = (TH1*) h_data -> Clone();
  TH1* ch_ewk  = (TH1*) h_ewk  -> Clone();
  TH1* ch_qcd  = (TH1*) h_qcd  -> Clone();

  if(hmin == 0) hmin = h_data -> GetXaxis() -> GetXmin();
  if(hmax == 0) hmax = h_data -> GetXaxis() -> GetXmax();

  RooRealVar x("x", "x", hmin, hmax);

  string rdhd = "rdh_data" + ext;
  string rdhe = "rdh_ewk"  + ext;
  string rdhq = "rdh_qcd"  + ext;
  RooDataHist rdh_data(rdhd.c_str(), rdhd.c_str(), x, ch_data  );
  RooDataHist rdh_ewk (rdhe.c_str(), rdhe.c_str(), x, ch_ewk   );
  RooDataHist rdh_qcd (rdhq.c_str(), rdhq.c_str(), x, ch_qcd   );
              
  string pdfe = "pdf_ewk"  + ext;
  string pdfq = "pdf_qcd"  + ext;
  RooHistPdf  pdf_ewk (pdfe.c_str(), pdfe.c_str(), x, rdh_ewk );
  RooHistPdf  pdf_qcd (pdfq.c_str(), pdfq.c_str(), x, rdh_qcd );

  float int_data = h_data -> Integral(); //h_data -> GetXaxis() -> FindBin(hmin), h_data -> GetXaxis() -> FindBin(hmax));
  float int_ewk  = h_ewk  -> Integral(); //h_ewk  -> GetXaxis() -> FindBin(hmin), h_ewk  -> GetXaxis() -> FindBin(hmax));
  float int_qcd  = h_qcd  -> Integral(); //h_qcd  -> GetXaxis() -> FindBin(hmin), h_qcd  -> GetXaxis() -> FindBin(hmax));

  string rrve = "rrv_ewk" + ext;
  string rrvq = "rrv_qcd" + ext; 
  //RooRealVar  rrv_ewk ("rrv_ewk" + ext, "rrv_ewk" , int_ewk, 1400, 14695 );
  //RooRealVar  rrv_qcd ("rrv_qcd" + ext, "rrv_qcd" , int_qcd, 1400, 14695 );
  RooRealVar  rrv_ewk (rrve.c_str(), rrve.c_str(), int_ewk, int_data * 0.1, int_data );
  RooRealVar  rrv_qcd (rrvq.c_str(), rrvq.c_str(), int_qcd, int_data * 0.1, int_data );

  RooArgList pdfs (pdf_ewk, pdf_qcd); 
  RooArgList coeff(rrv_ewk, rrv_qcd); 

  string tot = "totPdf" + ext;
  RooAddPdf totPdf(tot.c_str(), tot.c_str(), pdfs, coeff);
  totPdf.fitTo(rdh_data, RooFit::SumW2Error(false)); //, RooFit::Extended(), RooFit::PrintLevel(-1));

  vector<float> central;
  central.push_back(rrv_ewk.getVal() / int_ewk);
  central.push_back(rrv_qcd.getVal() / int_qcd);

  return central;

}  


//____________________________________________________________________________
vector<float> FakeRatio::getScalesETH(string obs, float lumi){

  TH1 * h_data   = _hm -> getHisto(obs, _idx_datacorrETH);   
  TH1 * h_ewk    = _hm -> getHisto(obs, _idx_ewk        );   
  TH1 * h_qcd    = _hm -> getHisto(obs, _idx_qcd        );   

  vector<float> scales;
  scales.push_back(1.);
  scales.push_back(1.);

  if(lumi                   == 0) return scales;
  if(h_data -> GetEntries() == 0) return scales;
  if(h_data -> GetEntries() < 10) return scales;
  //if(h_data -> GetEntries() < h_ewk -> GetEntries() + h_qcd -> GetEntries()) return scales;

//DUMP(obs);
//cout << h_data->Integral() << endl;
//cout << h_ewk ->Integral() << endl;
//cout << h_qcd ->Integral() << endl;
  // first fit EWK and QCD together to data in range [0, infinity]
  string ext = obs.substr(obs.find_last_of("_"));
  vector<float> sc_first = doubleFit(ext, h_data, h_ewk, h_qcd);

  if(sc_first[0] >= 0 && sc_first[1] >= 0){
  // save plots after first fit
  string nobs  = obs.substr(0, obs.find_last_of("_")) + "1" + ext;
  TH1 * h_ewk1 = (TH1*) _hm -> getHisto(nobs, _idx_ewk);
  TH1 * h_qcd1 = (TH1*) _hm -> getHisto(nobs, _idx_qcd);
  h_ewk1 -> Scale(sc_first[0]);
  h_qcd1 -> Scale(sc_first[1]);
//cout << h_ewk1->Integral() << endl;
//cout << h_qcd1->Integral() << endl;

  // fix QCD and subtract from data
  TH1 * h_dataqcdsub = (TH1*) h_data -> Clone(); 
  h_dataqcdsub -> Add(h_qcd1, -1);
//cout << h_dataqcdsub->Integral() << endl;

  // fit EWK to QCD-subtracted-data in range [50,120]
  scales[0] = sc_first[0] * singleFit(ext, h_dataqcdsub, h_ewk1, 50, 120); // ewk scale
  scales[1] = sc_first[1];                                            // qcd scale
  }
DUMP(obs);
DUMPVECTOR(sc_first);
cout << "second " << (scales[0] / sc_first[0]) << endl;

  return scales;

}


//____________________________________________________________________________
void FakeRatio::modifySkimming(){
  // if adding variables in the skimming tree is needed...
  addSkimBranch("vtxWeight", &_vtxWeight); 

}


//____________________________________________________________________________
void FakeRatio::modifyWeight() {
  /*
    modifies the event weight for every entry in the tree
    parameters: none
    return: none
  */ 
	
  //_vtxWeight = _vc->get("vtxWeight");
  //_weight = (i->second)->Getweight();

  //if(_sampleName.find("data") == std::string::npos && _vc->get("puWeight") > 0)
  //  _weight *= _vc->get("puWeight");
  //else
  //  _weight = 1.;

  _isData=true;
  if(_sampleName.find("data")==std::string::npos && _sampleName.find("runs")==std::string::npos) {

    string sname = _sampleName;
    if(sname.find("ewk") != std::string::npos) sname = sname.erase(sname.find("ewk"), 3); 
    if(sname.find("qcd") != std::string::npos) sname = sname.erase(sname.find("qcd"), 3); 

    _weight *= _vc->get("vtxWeight")*_vc->get("genWeight");
    //_weight *= _vc->get("puWeight")*_vc->get("genWeight");
    //_weight *= _vc->get("puWeight");

    double nProc=getCurrentDS()->getSumProcWgts(); 
    if(sname.find("DYJets") != std::string::npos) nProc = 3.94876696821e+11;
    if(sname.find("WJets")  != std::string::npos) nProc = 2.77246219357e+12;
    if(sname.find("TTJets") != std::string::npos) nProc = 72744782594.8;

    if(nProc==-1) nProc=getCurrentDS()->getNProcEvents();
    double w=_dbm->getDBValue("XS", sname) * _dbm->getDBValue("KF", sname)/nProc * 1;//last number is lumi
    _weight *=w;
    _isData=false;

//DUMP(_weight);
//DUMP(_vc->get("vtxWeight"));
//DUMP(_vc->get("genWeight"));
//DUMP(_dbm->getDBValue("XS", sname));
//DUMP(_dbm->getDBValue("KF", sname));
//DUMP(nProc);
  }

}


//  ____________________________________________________________________________
vector<float> FakeRatio::prepareHists(TH1* h_data, TH1* h_ewk, TH1* h_qcd){

  vector<float> scales;
  scales.push_back(1.);
  scales.push_back(1.);

  if(h_data -> Integral() < h_ewk -> Integral())
    scales[0] = floor(h_data->Integral() / h_ewk->Integral() * 1000) / 1000;

  if(h_data -> Integral() < h_qcd -> Integral())
    scales[1] = floor(h_data->Integral() / h_qcd->Integral() * 1000) / 1000;

  return scales;

}


//____________________________________________________________________________
void FakeRatio::registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis){

  for(unsigned int i = 0; i < leps.size(); ++i)
    registerVariable(leps[i] + var, nbins, bmin, bmax, axis);
    //_hm->addVariable(leps[i] + var, nbins, bmin, bmax, axis);

} 


//____________________________________________________________________________
void FakeRatio::registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis){

  for(unsigned int i = 0; i < leps.size(); ++i)
    registerVariable(leps[i] + var, nxbins, xbins, nybins, ybins, xaxis, yaxis);
    //_hm->addVariable(leps[i] + var, nxbins, xbins, nybins, ybins, xaxis, yaxis);

}


//  ____________________________________________________________________________
void FakeRatio::registerTriggerVars(){

//DUMPVECTOR(_vTR_lines_el_non[0]);
//DUMPVECTOR(_vTR_lines_el_iso[0]);

  for(unsigned int i = 0; i < _vTR_lines_el_non[0].size(); ++i) {
    //DUMP(_vTR_lines_el_non[0][i]);
    _vc->registerVar(_vTR_lines_el_non[0][i]); 
  }
  for(unsigned int i = 0; i < _vTR_lines_el_iso[0].size(); ++i) _vc->registerVar(_vTR_lines_el_iso[0][i]); 
  for(unsigned int i = 0; i < _vTR_lines_mu_non[0].size(); ++i) _vc->registerVar(_vTR_lines_mu_non[0][i]); 
  for(unsigned int i = 0; i < _vTR_lines_mu_iso[0].size(); ++i) _vc->registerVar(_vTR_lines_mu_iso[0][i]); 

}


//  ____________________________________________________________________________
void FakeRatio::registerVariable(string var, int nBin, float min, float max, string Xleg, bool isglb, bool prof, string type){

  _hm->addVariable(var + "_non", nBin, min, max, Xleg, isglb, prof, type);
  _hm->addVariable(var + "_iso", nBin, min, max, Xleg, isglb, prof, type);

  for(unsigned int i = 0; i < _vTR_lines_el_non[0].size() + _vTR_lines_mu_non[0].size(); ++i)
    _hm->addVariable(var + "_non" + Tools::intToString(i), nBin, min, max, Xleg, isglb, prof, type);
  for(unsigned int i = 0; i < _vTR_lines_el_iso[0].size() + _vTR_lines_mu_iso[0].size(); ++i)
    _hm->addVariable(var + "_iso" + Tools::intToString(i), nBin, min, max, Xleg, isglb, prof, type);
  
}


//  ____________________________________________________________________________
void FakeRatio::registerVariable(string var, int nBinX, float minX, float maxX, int nBinY, float minY, float maxY, string Xleg, string Yleg, bool isglb, bool prof, string type){

  _hm->addVariable(var + "_non", nBinX, minX, maxX, nBinY, minY, maxY, Xleg, Yleg, isglb, prof, type);
  _hm->addVariable(var + "_iso", nBinX, minX, maxX, nBinY, minY, maxY, Xleg, Yleg, isglb, prof, type);

  for(unsigned int i = 0; i < _vTR_lines_el_non[0].size() + _vTR_lines_mu_non[0].size(); ++i)
    _hm->addVariable(var + "_non" + Tools::intToString(i), nBinX, minX, maxX, nBinY, minY, maxY, Xleg, Yleg, isglb, prof, type);
  for(unsigned int i = 0; i < _vTR_lines_el_iso[0].size() + _vTR_lines_mu_iso[0].size(); ++i)
    _hm->addVariable(var + "_iso" + Tools::intToString(i), nBinX, minX, maxX, nBinY, minY, maxY, Xleg, Yleg, isglb, prof, type);

}


//  ____________________________________________________________________________
void FakeRatio::registerVariable(string var, int nBinX, vector<float> binsX, int nBinY, vector<float> binsY, string Xleg, string Yleg, bool isglb, bool prof, string type){

  _hm->addVariable(var + "_non", nBinX, binsX, nBinY, binsY, Xleg, Yleg, isglb, prof, type);
  _hm->addVariable(var + "_iso", nBinX, binsX, nBinY, binsY, Xleg, Yleg, isglb, prof, type);

  for(unsigned int i = 0; i < _vTR_lines_el_non[0].size() + _vTR_lines_mu_non[0].size(); ++i)
    _hm->addVariable(var + "_non" + Tools::intToString(i), nBinX, binsX, nBinY, binsY, Xleg, Yleg, isglb, prof, type);
  for(unsigned int i = 0; i < _vTR_lines_el_iso[0].size() + _vTR_lines_mu_iso[0].size(); ++i)
    _hm->addVariable(var + "_iso" + Tools::intToString(i), nBinX, binsX, nBinY, binsY, Xleg, Yleg, isglb, prof, type);

}
 

//  ____________________________________________________________________________
float FakeRatio::singleFit(string ext, TH1* h_data, TH1* h_mc, float hmin, float hmax){

  TH1* ch_data = (TH1*) h_data -> Clone();
  TH1* ch_mc   = (TH1*) h_mc   -> Clone();

  if(hmin == 0) hmin = h_data -> GetXaxis() -> GetXmin();
  if(hmax == 0) hmax = h_data -> GetXaxis() -> GetXmax();

  RooRealVar x("x", "x", hmin, hmax);
  RooArgList rlist(x);
  RooArgSet  rset (x);

  string rdhd  = "rdhs_data" + ext;
  string rdhmc = "rdhs_mc" + ext;
  string pdfmc = "pdfs_mc" + ext;
  string rrvmc = "rrvs_mc" + ext;
  string tot   = "totPdfs" + ext;
  RooDataHist rdh_data(rdhd .c_str(), rdhd .c_str(), rlist, ch_data );
  RooDataHist rdh_mc  (rdhmc.c_str(), rdhmc.c_str(), rlist, ch_mc   );
  RooHistPdf  pdf_mc  (pdfmc.c_str(), pdfmc.c_str(), rset , rdh_mc  );

  float int_data = h_data -> Integral(h_data -> GetXaxis() -> FindBin(hmin), h_data -> GetXaxis() -> FindBin(hmax));
  float int_mc   = h_mc   -> Integral(h_mc   -> GetXaxis() -> FindBin(hmin), h_mc   -> GetXaxis() -> FindBin(hmax));

  RooRealVar  rrv_mc  (rrvmc.c_str(), rrvmc.c_str(), int_data, int_data * 0.5, int_data );

  RooArgList  pdfs    (pdf_mc); 
  RooArgList  coeff   (rrv_mc); 

  RooAddPdf   totPdf  (tot.c_str(), tot.c_str(), pdfs, coeff);
  totPdf.fitTo(rdh_data, RooFit::SumW2Error(false)); //, RooFit::Extended(), RooFit::PrintLevel(-1));

  return rrv_mc.getVal() / int_mc;

} 


//  ____________________________________________________________________________
void FakeRatio::subtractPlots(string lep, int idx, vector<float> scales, string postfix){
  //CH: only rescale ER and MR plots

  vector<string> obs = _hm -> getObservables(true);

  for(unsigned int i = 0; i < obs.size(); ++i) {

    if(obs[i].find("QR_")         != std::string::npos) continue;
    if(obs[i].find("MT0")         != std::string::npos) continue;
    if(obs[i].find("MT1")         != std::string::npos) continue;
    if(obs[i].find(lep)           == std::string::npos) continue;
    if(obs[i].find("_" + postfix) == std::string::npos) continue;

    TH1 * d = _hm -> getHisto(obs[i], idx     );
    TH1 * e = _hm -> getHisto(obs[i], _idx_ewk);
    TH1 * q = _hm -> getHisto(obs[i], _idx_qcd);

    e -> Scale(scales[0]);
    q -> Scale(scales[1]); 

    d -> Add(e, -1);
  }

}


//  ____________________________________________________________________________
void FakeRatio::subtractPlotsCERN(string lep, int idx, string postfix){


  int datas = _hm -> getHisto("QR_MET_small_" + postfix, _idx_data) -> GetEntries();
  int datal = _hm -> getHisto("QR_MET_large_" + postfix, _idx_data) -> GetEntries();

  int ewks  = _hm -> getHisto("QR_MET_small_" + postfix, _idx_ewk ) -> GetEntries();
  int ewkl  = _hm -> getHisto("QR_MET_large_" + postfix, _idx_ewk ) -> GetEntries();

  float rp = 0.;
  if( ewkl > 0 && datas > 0)
    rp = ( float(ewks) / float(ewkl) ) * ( float(datal) / float(datas) );
  float sp = float(1.0) / (1. - rp);

  vector<string> obs = _hm -> getObservables(true);
  vector<string> nobs;
  for(unsigned int i = 0; i < obs.size(); ++i)
    if(obs[i].find("MR_Rat" + lep + "Map") != std::string::npos && obs[i].find(postfix) != std::string::npos)
      nobs.push_back(obs[i]);

  for(unsigned int i = 0; i < nobs.size(); ++i) {

    size_t pos = nobs[i].find("Map") + 3;
    string ext = nobs[i].substr(pos, nobs[i].find("_", pos) - pos);

    TH1 * nums = _hm -> getHisto("QR_small_Num" + lep + "Map" + ext + "_" + postfix, _idx_data);
    TH1 * numl = _hm -> getHisto("QR_large_Num" + lep + "Map" + ext + "_" + postfix, _idx_data);

    TH1 * frs = (TH1*) nums -> Clone();
    TH1 * frl = (TH1*) numl -> Clone();

    frs -> Divide(_hm -> getHisto("QR_small_Den" + lep + "Map" + ext + "_" + postfix, _idx_data)); 
    frl -> Divide(_hm -> getHisto("QR_large_Den" + lep + "Map" + ext + "_" + postfix, _idx_data)); 

    TH1 * r = _hm -> getHisto(nobs[i], _idx_datacorrCERN);

    r -> Reset();
    r -> Add(frs);
    r -> Add(frl, rp * (-1));
    r -> Scale(sp);
  }

}



//  ____________________________________________________________________________
void FakeRatio::subtractPromptsCERN(){

  // non-isolated triggers

  vector<float> effs = _vTR_efflum_el_non;
  effs.insert(effs.end(), _vTR_efflum_mu_non.begin(), _vTR_efflum_mu_non.end());

  for(unsigned int i = 0; i < _vTR_lines_el_non[0].size() + _vTR_lines_mu_non[0].size(); ++i){
    if(_ewkSub == "all" || _ewkSub == "el")
      subtractPlotsCERN("El", _idx_datacorrCERN, "non" + Tools::intToString(i));
    if(_ewkSub == "all" || _ewkSub == "mu")
      subtractPlotsCERN("Mu", _idx_datacorrCERN, "non" + Tools::intToString(i));
  }


  // isolated triggers

  effs = _vTR_efflum_el_iso;
  effs.insert(effs.end(), _vTR_efflum_mu_iso.begin(), _vTR_efflum_mu_iso.end());

  for(unsigned int i = 0; i < _vTR_lines_el_iso[0].size() + _vTR_lines_mu_iso[0].size(); ++i){
    if(_ewkSub == "all" || _ewkSub == "el")
      subtractPlotsCERN("El", _idx_datacorrCERN, "iso" + Tools::intToString(i));
    if(_ewkSub == "all" || _ewkSub == "mu")
      subtractPlotsCERN("Mu", _idx_datacorrCERN, "iso" + Tools::intToString(i));
  }

}


void FakeRatio::testEwkSub(){


  TH1 * h_data   = (TH1*) _hm -> getHisto("ER_NumElMT_iso3", _idx_datacorrETH) -> Clone();   
  TH1 * h_ewk    = (TH1*) _hm -> getHisto("ER_NumElMT_iso3", _idx_ewk        ) -> Clone();   
  TH1 * h_qcd    = (TH1*) _hm -> getHisto("ER_NumElMT_iso3", _idx_qcd        ) -> Clone();   

  TH1 * h_ewk1   = (TH1*) h_ewk -> Clone();
  TH1 * h_ewk2   = (TH1*) h_ewk -> Clone();

  TH1 * h_qcd1   = (TH1*) h_qcd -> Clone();
  TH1 * h_qcd2   = (TH1*) h_qcd -> Clone();

  // first fit EWK and QCD together to data in range [0, infinity]
  vector<float> sc_first = doubleFit("iso3", h_data, h_ewk, h_qcd);
DUMPVECTOR(sc_first);

  h_ewk1 -> Scale(sc_first[0]); 
  h_ewk2 -> Scale(sc_first[0]); 
  h_qcd1 -> Scale(sc_first[1]); 
  h_qcd2 -> Scale(sc_first[1]); 

  TH1* h_dataqcdsub = (TH1*) h_data->Clone();
  h_dataqcdsub -> Add(h_qcd2, -1);

  float sc_second = singleFit("iso3", h_dataqcdsub, h_ewk2, 50, 120);
  DUMP(sc_second);

  h_ewk2 -> Scale(sc_second);

  TFile * f = new TFile("test.root", "recreate");

  h_data -> Write(); 
  h_ewk  -> Write(); 
  h_ewk1 -> Write(); 
  h_ewk2 -> Write(); 
  h_qcd  -> Write(); 
  h_qcd1 -> Write(); 
  h_qcd2 -> Write(); 

  //f -> Write();
  f -> Close();

}


//____________________________________________________________________________
void FakeRatio::subtractPrompts(){
  /*
    implements subtraction of prompt contamination (ETH method)
  */

  //if(!_doEwkSub) return; 


  // non-isolated triggers

  vector<float> effs = _vTR_efflum_el_non;
  effs.insert(effs.end(), _vTR_efflum_mu_non.begin(), _vTR_efflum_mu_non.end());

  //DUMPVECTOR(effs);
  //DUMPVECTOR(_vTR_lines_el_non[0]);
  //DUMPVECTOR(_vTR_lines_mu_non[0]);

  //subtractPlots("El", _idx_datacorrETH, getScalesETH("ER_NumElMT_iso3", effs[3]), "iso3");
  //return;


  for(unsigned int i = 0; i < _vTR_lines_el_non[0].size() + _vTR_lines_mu_non[0].size(); ++i){
    if(_ewkSub == "all" || _ewkSub == "el")
      subtractPlots("El", _idx_datacorrETH, getScalesETH("ER_NumElMT_non" + Tools::intToString(i), effs[i]), "non" + Tools::intToString(i));
    if(_ewkSub == "all" || _ewkSub == "mu")
      subtractPlots("Mu", _idx_datacorrETH, getScalesETH("ER_NumMuMT_non" + Tools::intToString(i), effs[i]), "non" + Tools::intToString(i));
  }


  // isolated triggers

  effs = _vTR_efflum_el_iso;
  effs.insert(effs.end(), _vTR_efflum_mu_iso.begin(), _vTR_efflum_mu_iso.end());

  for(unsigned int i = 0; i < _vTR_lines_el_iso[0].size() + _vTR_lines_mu_iso[0].size(); ++i){
    if(_ewkSub == "all" || _ewkSub == "el")
      subtractPlots("El", _idx_datacorrETH, getScalesETH("ER_NumElMT_iso" + Tools::intToString(i), effs[i]), "iso" + Tools::intToString(i));
    if(_ewkSub == "all" || _ewkSub == "mu")
      subtractPlots("Mu", _idx_datacorrETH, getScalesETH("ER_NumMuMT_iso" + Tools::intToString(i), effs[i]), "iso" + Tools::intToString(i));
  }

}   


//____________________________________________________________________________
void FakeRatio::sumMaps(){
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
          unsigned int idx = atoi(obs[j].substr(obs[j].rfind("_")+3).c_str());
          bool iso         = (obs[j].substr(obs[j].rfind("_"),3) == "iso");    
 
          vector<string> linesel = _vTR_lines_el_non[0]; 
          vector<float>  effsel  = _vTR_efflum_el_non; 
          vector<float>  effsmu  = _vTR_efflum_mu_non; 
          if(iso) {
            linesel = _vTR_lines_el_iso[0];
            effsel  = _vTR_efflum_el_iso;
            effsmu  = _vTR_efflum_mu_iso;
          }

          float lumi = 1;
          if(linesel.size() <= idx) lumi = effsmu[idx];
          else                      lumi = effsel[idx];
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
      for(int i = 0; i < _idxsmc.size(); ++i){
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

      for(int i = 0; i < _idxsmc.size(); ++i){
        TH1 * sobs = _hm -> getHisto(obs[j], _idxsmc[i]);
        sobs -> Scale(factor);
      }
    }
  }
 
}


//____________________________________________________________________________
void FakeRatio::sumTriggers(){

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
  for(int i = 0; i < _numDS + _idxs.size(); ++i){
    for(unsigned int j = 0; j < tobs.size(); ++j) {
      sumTriggerPlots(tobs[j], i, "non");
      sumTriggerPlots(tobs[j], i, "iso");
    }
  }
}


//____________________________________________________________________________
void FakeRatio::sumTriggerPlots(string obs, int ds, string ext){

  // CH: note: electrons and muons are in different observables
  // so for an electron observable, the muon trigger plots will be empty
  // we can sum over them as it doesn't make a difference
  unsigned int num = _vTR_lines_el_non[0].size() + _vTR_lines_mu_non[0].size();
  if(ext == "iso")
    num = _vTR_lines_el_iso[0].size() + _vTR_lines_mu_iso[0].size();

  TH1* sum = _hm -> getHisto(obs + ext, ds);
  for(unsigned int i = 0; i < num; ++i)
    sum -> Add(_hm -> getHisto(obs + ext + Tools::intToString(i), ds));


}
    

//  ____________________________________________________________________________
void FakeRatio::writeOutput(){
  /*
    writes all output of this class to the disk
    paramters: none
    return: none
  */

  // decide if we need EWK subtraction or not (if not, jump to divideFRMaps call)
  doEwkSub();
 
  // sum numerators and denominators in categories 'data', 'datacorr', 'ewk', 'qcd' 
  sumMaps();

  // subtract prompt contamination
  ////testEwkSub();
  //subtractPromptsCERN();
  //subtractPrompts();

  // sum the plots for the different triggers
  sumTriggers();

  // make FR maps from numerators and denominators
  divideFRMaps();

}




/*****************************************************************************
******************************************************************************
** OBJECT SELECTIONS                                                        **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::collectKinematicObjects(){
  /*
    collects all kinematic objects needed in the code, i.e. applies all object selections
    parameters: none
    return: none
  */
  
  for(int i = 0; i < _vc->get("n" + _leps); ++i){

    bool den = false;
    bool num = false;

    // electrons
    if(std::abs(_vc->get(_leps + "_pdgId", i)) == 11){		  
      if(denominatorElectronSelection(i)) {
        _denEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.0005) );
        _denElsIdx .push_back(i);
        _denLeps   .push_back( _denEls[ _denEls.size()-1 ] );
        _denLepsIdx.push_back(i);
        den = true;
      }
      if(numeratorElectronSelection(i)) {
        _numEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.0005) );
        _numElsIdx .push_back(i);
        _numLeps   .push_back( _numEls[ _numEls.size()-1 ] );
        _numLepsIdx.push_back(i);
        num = true;
      }
      if(!den && !num) {
        if(vetoElectronSelection(i))  {
          _vetEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					     _vc->get(_leps + "_eta", i),
					     _vc->get(_leps + "_phi", i),
					     _vc->get(_leps + "_pdgId", i),
					     _vc->get(_leps + "_charge", i),
					     0.0005) );
          _vetLeps.push_back( _vetEls[ _vetEls.size()-1 ] );
        }
      }		
    }

    // muons
    else if(std::abs(_vc->get(_leps + "_pdgId", i)) == 13){
      if(denominatorMuonSelection(i)) {
        _denMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.105) );
        _denMusIdx .push_back(i);
        _denLeps   .push_back( _denMus[ _denMus.size()-1 ] );
        _denLepsIdx.push_back(i);
        den = true;
      }
      if(numeratorMuonSelection(i)) {
        _numMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.105) );
        _numMusIdx .push_back(i);
        _numLeps   .push_back( _numMus[ _numMus.size()-1 ] );
        _numLepsIdx.push_back(i);
        num = true;
      }
      if(!den && !num) {
        if(vetoMuonSelection(i))  {
          _vetMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					     _vc->get(_leps + "_eta", i),
					     _vc->get(_leps + "_phi", i),
					     _vc->get(_leps + "_pdgId", i),
					     _vc->get(_leps + "_charge", i),
					     0.105) );
          _vetLeps.push_back( _vetMus[ _vetMus.size()-1 ] );
        }
      }
    }
  }

  _nDenEls  = _denEls .size();
  _nDenLeps = _denLeps.size();
  _nDenMus  = _denMus .size();
  _nNumEls  = _numEls .size();
  _nNumLeps = _numLeps.size();
  _nNumMus  = _numMus .size();
 
  for(int i = 0; i < _vc->get("n" + _jets); ++i){
    if(goodJetSelection(i)) {
      _goodJets.push_back( Candidate::create(_vc->get(_jets + "_pt", i),
					                     _vc->get(_jets + "_eta", i),
					                     _vc->get(_jets + "_phi", i) ) );
      
    }
  }

  _nJets  = _goodJets.size();
  
  _HT  = _susyMod -> HT( &(_goodJets) );
  //_met = Candidate::create(_vc->get(_mets + "_pt"), _vc->get(_mets + "_phi") );

}


//____________________________________________________________________________
bool FakeRatio::goodJetSelection(int jetIdx){
  /*
    does the selection of good jets, i.e. minimum selection of jets 
    parameters: jetIdx
    return: true (if the jet is good), false (else)
  */
  
  counter("GoodJets", kGoodJets);

  if(!makeCut<float>(         _vc->get(_jets + "_pt" , jetIdx) , 40.0, ">" , "pt selection"   , 0, kGoodJets)) return false;
  if(!makeCut<float>(std::abs(_vc->get(_jets + "_eta", jetIdx)),  2.4, "<" , "eta selection"  , 0, kGoodJets)) return false;
  if(!makeCut<float>(         _vc->get(_jets + "_id" , jetIdx) ,  1  , ">=", "pog pf loose id", 0, kGoodJets)) return false;
  
  // CH: away-jet requirement
  for(unsigned int il=0; il<_denLeps.size(); ++il){
    float dr = KineUtils::dR(_denLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _denLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(!makeCut<float>(dr, 1.0, ">", "dR selection", 0, kGoodJets) ) return false;
  }

  // CH: this is jet-lepton cleaning: removing the closest jet to the loose lepton if dR < 0.4
  float dr_cache = 999999.;
  for(unsigned int il=0; il<_denLeps.size(); ++il){
    float dr = KineUtils::dR(_denLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _denLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(dr < dr_cache)
      dr_cache = dr;
  }
  for(unsigned int il=0; il<_vetLeps.size(); ++il){
    float dr = KineUtils::dR(_vetLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _vetLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(dr < dr_cache)
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.4, ">", "dR selection, jet-lepton cleaning", 0, kGoodJets) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::denominatorElectronSelection(int elIdx){

  counter("DenominatorElectrons", kDenEls);

  // CH: FO2 selection for electrons
  // extrapolation in ElMvaId and mini isolation


  if(!makeCut<float>(   _susyMod -> conePt(elIdx, SusyModule::kTight), 10.   , ">"  , "pt selection"      , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 2.5   , "<"  , "eta selection"     , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 1.4442, "[!]", "eta selection veto", 1.566, kDenEls)) return false;
  //if((_datasets[_inds]->getName().find("qcd") != std::string::npos && _datasets[_inds]->getName().find("data") == std::string::npos) && 
  //   !makeCut<int>(           _vc->get("LepGood_mcMatchId"  , elIdx) ,  0    , "="  , "gen match fake"    , 0    , kDenEls)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"      , elIdx) , 4.0   , "<"  , "SIP 3D"            , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"         , elIdx)), 0.1   , "<"  , "dz selection"      , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"        , elIdx)), 0.05  , "<"  , "dxy selection"     , 0    , kDenEls)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge", elIdx) , 1     , ">"  , "charge selection"  , 0    , kDenEls)) return false;

  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);

  if(!makeCut( conv                                              , "conversion rejection", "=", kDenEls)) return false;
  if(!makeCut( _susyMod -> multiIsoSel(elIdx, SusyModule::kDenom), "isolation"           , "=", kDenEls)) return false; 
  if(!makeCut( _susyMod -> elMvaSel   (elIdx, SusyModule::kLoose), "electron mva"        , "=", kDenEls)) return false;    
  if(!makeCut( triggerEmulation(elIdx, kDenEls)                  , "trigger emulation"   , "=", kDenEls)) return false;    

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kDenEls) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::denominatorMuonSelection(int muIdx){

  counter("DenominatorMuons", kDenMus);
  
  //CH: FO1 for muons
  //extrapolation in isolation only

  //if(!makeCut( _susyMod -> multiIsoSel(muIdx, SusyModule::kDenom), "isolation", "=", kDenMus)) return false;

  //if(!makeCut<float>(   _susyMod -> conePt(muIdx, SusyModule::kMedium), 10.  , ">", "pt selection"     , 0  , kDenMus)) return false;
  //if(!makeCut<float>(         _vc->get("LepGood_eta"         , muIdx) ,  2.4 , "<", "eta selection"    , 0  , kDenMus)) return false;
  ////if((_datasets[_inds]->getName().find("qcd") != std::string::npos && _datasets[_inds]->getName().find("data") == std::string::npos) && 
  ////   !makeCut<int>(           _vc->get("LepGood_mcMatchId"   , muIdx) ,  0   , "=", "gen match fake", 0, kDenMus)) return false;
  //if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx) ,  0   , ">", "medium muon ID"   , 0  , kDenMus)) return false;
  //if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx) ,  1   , ">", "error/pt < 20"    , 0  , kDenMus)) return false;
  //if(!makeCut<float>(         _vc->get("LepGood_sip3d"       , muIdx) ,  4.0 , "<", "SIP 3D"           , 0  , kDenMus)) return false;
  //if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"          , muIdx)),  0.1 , "<", "dz selection"     , 0  , kDenMus)) return false;
  //if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"         , muIdx)),  0.05, "<", "dxy selection"    , 0  , kDenMus)) return false;
  //if(!makeCut( triggerEmulation(muIdx, kDenMus)                                   , "trigger emulation", "=", kDenMus)) return false;    
  if(!makeCut( _susyMod -> multiIsoSel(muIdx, SusyModule::kDenom), "mini-isolation < 0.4", "=", kSync)) return false;

  if(!makeCut<float>(   _susyMod -> conePt(muIdx, SusyModule::kMedium), 10.  , ">", "pt > 10"     , 0  , kSync)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_eta"         , muIdx) ,  2.4 , "<", "abs(eta) < 2.4"    , 0  , kSync)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx) ,  0   , ">", "medium muon ID"   , 0  , kSync)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx) ,  1   , ">", "error/pt < 20"    , 0  , kSync)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"       , muIdx) ,  4.0 , "<", "SIP 3D"           , 0  , kSync)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"          , muIdx)),  0.1 , "<", "dz selection"     , 0  , kSync)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"         , muIdx)),  0.05, "<", "dxy selection"    , 0  , kSync)) return false;
  Candidate* MT = nullptr;
  Candidate* lep = nullptr;
  lep = Candidate::create(_vc->get(_leps + "_pt", muIdx),
					  _vc->get(_leps + "_eta", muIdx),
					  _vc->get(_leps + "_phi", muIdx),
					  _vc->get(_leps + "_pdgId", muIdx),
					  _vc->get(_leps + "_charge", muIdx),
					  0.105);
  MT = Candidate::create( lep, _met);
  if(!makeCut<float>( MT->mass() , 20.0, "<" , "MT selection"                  , 0, kSync)) return false;


  return true;

}


//____________________________________________________________________________
bool FakeRatio::numeratorElectronSelection(int elIdx){

  counter("NumeratorElectrons", kNumEls);

  if(!makeCut<float>(   _susyMod -> conePt(elIdx, SusyModule::kTight), 10.   , ">"  , "pt selection"      , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 2.5   , "<"  , "eta selection"     , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 1.4442, "[!]", "eta selection veto", 1.566, kNumEls)) return false;
  //if((_datasets[_inds]->getName().find("qcd") != std::string::npos && _datasets[_inds]->getName().find("data") == std::string::npos) && 
  //   !makeCut<int>(           _vc->get("LepGood_mcMatchId"  , elIdx) ,  0    , "="  , "gen match fake"    , 0    , kNumEls)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"      , elIdx) , 4.0   , "<"  , "SIP 3D"            , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"         , elIdx)), 0.1   , "<"  , "dz selection"      , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"        , elIdx)), 0.05  , "<"  , "dxy selection"     , 0    , kNumEls)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge", elIdx) , 1     , ">"  , "charge selection"  , 0    , kNumEls)) return false;

  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);

  if(!makeCut( conv                                              , "conversion rejection", "=", kNumEls)) return false;
  if(!makeCut( _susyMod -> multiIsoSel(elIdx, SusyModule::kTight), "isolation"           , "=", kNumEls)) return false; 
  if(!makeCut( _susyMod -> elMvaSel   (elIdx, SusyModule::kTight), "electron mva"        , "=", kNumEls)) return false;    
  if(!makeCut( triggerEmulation(elIdx, kNumEls)                  , "trigger emulation"   , "=", kNumEls)) return false;    

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kNumEls) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::numeratorMuonSelection(int muIdx){

  counter("NumeratorMuons", kNumMus);

  if(!makeCut( _susyMod -> multiIsoSel(muIdx, SusyModule::kMedium), "isolation", "=", kNumMus)) return false;

  if(!makeCut<float>(   _susyMod -> conePt(muIdx, SusyModule::kMedium), 10.  , ">", "pt selection"     , 0  , kNumMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_eta"         , muIdx) ,  2.4 , "<", "eta selection"    , 0  , kNumMus)) return false;
  //if((_datasets[_inds]->getName().find("qcd") != std::string::npos && _datasets[_inds]->getName().find("data") == std::string::npos) && 
  //   !makeCut<int>(           _vc->get("LepGood_mcMatchId"   , muIdx) ,  0   , "=", "gen match fake", 0, kNumMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx) ,  0   , ">", "medium muon ID"   , 0  , kNumMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx) ,  1   , ">", "error/pt < 20"    , 0  , kNumMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"       , muIdx) ,  4.0 , "<", "SIP 3D"           , 0  , kNumMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"          , muIdx)),  0.1 , "<", "dz selection"     , 0  , kNumMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"         , muIdx)),  0.05, "<", "dxy selection"    , 0  , kNumMus)) return false;
  if(!makeCut( triggerEmulation(muIdx, kNumMus)                                   , "trigger emulation", "=", kNumMus)) return false;    
 
  return true;

}


//____________________________________________________________________________
bool FakeRatio::vetoElectronSelection(int elIdx){
  // selection of veto electrons

  counter("VetoElectrons", kVetEls);

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("n" + _leps); ++il){
    float dr = KineUtils::dR(_vc->get(_leps + "_eta", il), _vc->get(_leps + "_eta", elIdx),
			                 _vc->get(_leps + "_phi", il), _vc->get(_leps + "_phi", elIdx));
    if(std::abs(_vc->get(_leps + "_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kVetEls) ) return false;
  
  return true;

}


//____________________________________________________________________________
bool FakeRatio::vetoMuonSelection(int muIdx){
  // selection of veto muons

  counter("VetoMuons", kVetMus);
  
  return true;

}




/*****************************************************************************
******************************************************************************
** KINEMATIC REGION DEFINITIONS                                             **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::setCut(std::string var, float valCut, std::string cType, float upValCut) {
  /*
    sets the parameters (valCut, cType, upValCut) for a specific cut on a variable (var)
    parameters: var, valCut (the cut value), cType (the cut type), upValCut (the upper value
    in case one cuts the variable in a range)
    return: none
  */


  // measurement region

  if(var == "NBJetsMR") {
    _valCutNBJetsMR   = valCut;
    _cTypeNBJetsMR    = cType;
    _upValCutNBJetsMR = upValCut;
  } 
	

}



//____________________________________________________________________________
void FakeRatio::setMeasurementRegion() {
  /*
    sets the cuts of the measurement region (MR)
    parameters: none
    return: none
  */


  // CH: currently not used, keep it for later
  //if(_MR == "all") {
  //  setCut("NBJetsMR", 0, ">=");
  //} 
  //else if(_MR == "MR00") {
  //  setCut("NBJetsMR", 0, "=");
  //}
  //else if(_MR == "MR01") {
  //  setCut("NBJetsMR", 1, "=");
  //}
  //else if(_MR == "MR02") {
  //  setCut("NBJetsMR", 2, "=");
  //}
  //else if(_MR == "MR03") {
  //  setCut("NBJetsMR", 3, ">=");
  //}


}



/*****************************************************************************
******************************************************************************
** EVENT SELECTIONS                                                         **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool FakeRatio::ewkSelection(){
  // CH: fake ratio measurement for RA5 sync exercise May 2015

  // lepton multiplicity
  if(!makeCut<int>( _nDenLeps         , 1   , "=" , "lepton multiplicity", 0, kEwkSel)) return false;

  // remainders of the trigger
  if     (!makeCut( _nDenEls == 1 || !_trel, "lepton flavor", "=",  kEwkSel)) return false;
  else if(!makeCut( _nDenMus == 1 || !_trmu, "lepton flavor", "=",  kEwkSel)) return false;
 
  //CH: RA5 guys select muon pt later on
  if     (_sampleName.find("Mu15") != std::string::npos && _denLeps[0] -> pt() < 15.) return false;
  else if(_sampleName.find("Mu5")  != std::string::npos && _denLeps[0] -> pt() > 15.) return false;

  // MET INVERTED! 
  if(!makeCut<float>( _met->pt() , 20.0, ">" , "MET selection"                 , 0, kEwkSel)) return false;

  // jet multiplicity
  if(!makeCut<int>( _nJets       , 1   , ">=", "jet multiplicity"              , 0, kEwkSel)) return false; 

  return true;

}


//____________________________________________________________________________
bool FakeRatio::mrSelection(){
  // CH: fake ratio measurement for RA5 sync exercise May 2015

  // lepton multiplicity
  if(!makeCut<int>( _nDenLeps    , 1   , "=" , "lepton multiplicity and flavor")) return false;

  // remainders of the trigger
  if     (!makeCut( _nDenEls == 1 || !_trel, "lepton flavor", "=")) return false;
  else if(!makeCut( _nDenMus == 1 || !_trmu, "lepton flavor", "=")) return false;
  counter("nFO == 1", kSync);

  //QCD muon samples
  if     (_sampleName.find("Mu15") != std::string::npos && _denLeps[0] -> pt() < 15.) return false;
  else if(_sampleName.find("Mu5")  != std::string::npos && _denLeps[0] -> pt() > 15.) return false;

  // MET 
  if(!makeCut<float>( _met->pt() , 20.0, "<" , "MET selection"                 )) return false;
  counter("MET < 20", kSync);

  // MT
  //Candidate* MT = nullptr;
  //MT = Candidate::create( _denLeps[0], _met);
  //if(!makeCut<float>( MT->mass() , 20.0, "<" , "MT selection"                  )) return false;

  // jet multiplicity
  if(!makeCut<int>( _nJets       , 1   , ">=", "jet multiplicity"              )) return false; 
  counter("nJets >= 1", kSync);

  //fillTriggerTestPlots();

  return true;

}


//____________________________________________________________________________
bool FakeRatio::qcdSelection(){
  // CH: fake ratio measurement for RA5 sync exercise May 2015

  // lepton multiplicity
  if(!makeCut<int>( _nDenLeps    , 1   , "=" , "lepton multiplicity and flavor", 0, kQcdSel)) return false;

  // remainders of the trigger
  if     (!makeCut( _nDenEls == 1 || !_trel, "lepton flavor", "=",  kQcdSel)) return false;
  else if(!makeCut( _nDenMus == 1 || !_trmu, "lepton flavor", "=",  kQcdSel)) return false;

  //CH: RA5 guys select muon pt later on
  if     (_sampleName.find("Mu15") != std::string::npos && _denLeps[0] -> pt() < 15.) return false;
  else if(_sampleName.find("Mu5")  != std::string::npos && _denLeps[0] -> pt() > 15.) return false;

  // jet multiplicity
  if(!makeCut<int>( _nJets       , 1   , ">=", "jet multiplicity"              , 0, kQcdSel)) return false; 
     
  return true;


}


//____________________________________________________________________________
bool FakeRatio::skimSelection(){

  if(!makeCut<int>( _nDenLeps, 1, "=", "lepton multiplicity and flavor") ) return false;
  if(!makeCut<int>( _nJets   , 1, ">=", "jet multiplicity"              ) ) return false; 

  return true;

}


//____________________________________________________________________________
bool FakeRatio::triggerEmulation(int idx, int label){


  //trigger emulation cuts
  if(std::abs(_vc->get(_leps + "_pdgId", idx)) == 11){

    //central
    if(std::abs(_vc->get(_leps + "_eta", idx)) < 1.479){
      counter("central electron to emu", label);
      if(_iso) counter("central electron to emu Ele12iso", label);
      else     counter("central electron to emu Ele12non", label);
      if(!makeCut<float>(         _vc->get(_leps + "_sigmaIEtaIEta" , idx) , 0.011, "<", "central emu: sigmaIEtaIEta selection", 0, label)) return false;
      if(_iso) counter("central emu: sigmaIEtaIEta selection Ele12iso", label);
      else     counter("central emu: sigmaIEtaIEta selection Ele12non", label);
      if(!makeCut<float>(         _vc->get(_leps + "_hadronicOverEm", idx) , 0.08 , "<", "central emu: H / E selection"        , 0, label)) return false;
      if(_iso) counter("central emu: H / E selection Ele12iso", label);
      else     counter("central emu: H / E selection Ele12non", label);
      if(!makeCut<float>(std::abs(_vc->get(_leps + "_dEtaScTrkIn"   , idx)), 0.01 , "<", "central emu: dEta selection"         , 0, label)) return false;
      if(_iso) counter("central emu: dEta selection Ele12iso", label);
      else     counter("central emu: dEta selection Ele12non", label);
      if(!makeCut<float>(std::abs(_vc->get(_leps + "_dPhiScTrkIn"   , idx)), 0.04 , "<", "central emu: dPhi selection"         , 0, label)) return false;
      if(_iso) counter("central emu: dPhi selection Ele12iso", label);
      else     counter("central emu: dPhi selection Ele12non", label);
      string ext = "non1";
      if(_iso) ext = "iso0";
      fill("MR_DenEleInvMinusPInvEB_" + ext, std::abs(_vc->get(_leps + "_eInvMinusPInv", idx)), _weight);
      if(!makeCut<float>(std::abs(_vc->get(_leps + "_eInvMinusPInv" , idx)), 0.01 , "<", "forward emu: 1/E - 1/P selection"    , 0, label)) return false;
      if(_iso) counter("central emu: 1/E - 1/P selection Ele12iso", label);
      else     counter("central emu: 1/E - 1/P selection Ele12non", label);
    }
    //forward
    else {
      counter("forward electron to emu", label);
      if(_iso) counter("forward electron to emu Ele12iso", label);
      else     counter("forward electron to emu Ele12non", label);
      if(!makeCut<float>(         _vc->get(_leps + "_sigmaIEtaIEta" , idx) , 0.031, "<", "forward emu: sigmaIEtaIEta selection", 0, label)) return false;
      if(_iso) counter("forward emu: sigmaIEtaIEta selection Ele12iso", label);
      else     counter("forward emu: sigmaIEtaIEta selection Ele12non", label);
      if(!makeCut<float>(         _vc->get(_leps + "_hadronicOverEm", idx) , 0.08 , "<", "forward emu: H / E selection"        , 0, label)) return false;
      if(_iso) counter("forward emu: H / E selection Ele12iso", label);
      else     counter("forward emu: H / E selection Ele12non", label);
      if(!makeCut<float>(std::abs(_vc->get(_leps + "_dEtaScTrkIn"   , idx)), 0.01 , "<", "forward emu: dEta selection"         , 0, label)) return false;
      if(_iso) counter("forward emu: dEta selection Ele12iso", label);
      else     counter("forward emu: dEta selection Ele12non", label);
      if(!makeCut<float>(std::abs(_vc->get(_leps + "_dPhiScTrkIn"   , idx)), 0.08 , "<", "forward emu: dPhi selection"         , 0, label)) return false;
      if(_iso) counter("forward emu: dPhi selection Ele12iso", label);
      else     counter("forward emu: dPhi selection Ele12non", label);
      string ext = "non1";
      if(_iso) ext = "iso0";
      fill("MR_DenEleInvMinusPInvEE_" + ext, std::abs(_vc->get(_leps + "_eInvMinusPInv", idx)), _weight);
      if(!makeCut<float>(std::abs(_vc->get(_leps + "_eInvMinusPInv" , idx)), 0.01 , "<", "forward emu: 1/E - 1/P selection"    , 0, label)) return false;
      if(_iso) counter("forward emu: 1/E - 1/P selection Ele12iso", label);
      else     counter("forward emu: 1/E - 1/P selection Ele12non", label);
    }

    // non-isolated trigger only
    if(!_iso){
      //if(!makeCut(_susyMod -> elMvaSel(idx, SusyModule::kSpecFakeElNon), "non-isolated mva id", "=", label)) return false;
    }
    // isolated trigger only
    else {
      //if(!makeCut(_susyMod -> elMvaSel(idx, SusyModule::kSpecFakeElIso), "isolated mva id", "=", label)) return false;

      //if(!makeCut<float>(         _vc->get(_leps + "_sigmaIEtaIEta" , _denElsIdx[0]) , 0.031, "<", "isolated emu: sigmaIEtaIEta selection", 0, kTrigger)) return false;
      //if(!makeCut<float>(         _vc->get(_leps + "_hadronicOverEm", _denElsIdx[0]) , 0.08 , "<", "isolated emu: H / E selection"        , 0, kTrigger)) return false;
      //if(!makeCut<float>(         _vc->get(_leps + "_hadronicOverEm", _denElsIdx[0]) , 0.08 , "<", "isolated emu: H / E selection"        , 0, kTrigger)) return false;
    }
  //Plus for isolated triggers only: EcalPFClusterIso<0.45, HcalPFClusterIso<0.25, TrackIso<0.2
  }

  return true;

}

//____________________________________________________________________________
bool FakeRatio::triggerSelectionLite(){ 

  counter("TriggerSelection", kTrigger);

  bool any  = false; //passed at least one of any trigger
      _iso  = false; //passed at least one of the isolated triggers
      _trel = false;
      _trmu = false;
  _exts.clear();


  if(_vc->get("HLT_FR_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30") == 1) {
    any   = true; 
    _trel = true;
    _iso  = true; 
    _exts.push_back("iso0");
  }
  if(_vc->get("HLT_FR_Ele12_CaloIdM_TrackIdM_PFJet30") == 1) {
    any = true;
    _trel = true;
    _exts.push_back("non1");
  }
  if(_vc->get("HLT_FR_Mu17_TrkIsoVVL") == 1) {
    any = true; 
    _trmu = true;
    _iso = true; 
    _exts.push_back("iso3");
  }
  if(_vc->get("HLT_FR_Mu17") == 1) {
    any = true;
    _trmu = true;
    _exts.push_back("non4");
  }

  //if     (std::abs(_denLeps[0]->pdgId()) == 11) {
  //  if(_vc->get("HLT_FR_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30") == 1) {
  //    any = true; 
  //    _iso = true; 
  //    _exts.push_back("iso0");
  //  }
  //  if(_vc->get("HLT_FR_Ele12_CaloIdM_TrackIdM_PFJet30") == 1) {
  //    any = true;
  //    _exts.push_back("non1");
  //  }
  //}
  //else if(std::abs(_denLeps[0]->pdgId()) == 13) {
  //  if(_vc->get("HLT_FR_Mu17_TrkIsoVVL") == 1) {
  //    any = true; 
  //    _iso = true; 
  //    _exts.push_back("iso3");
  //  }
  //  if(_vc->get("HLT_FR_Mu17") == 1) {
  //    any = true;
  //    _exts.push_back("non4");
  //  }
  //}


  // at least one auxiliary trigger per pt bin to be passed
  if(!makeCut(any, "at least one trigger path", "=", kTrigger)) return false;

  if(!makeCut(triggerEmulation(_iso, kTrigger), "full trigger emulation cuts", "=", kTrigger)) return false;


  return true;
}


//____________________________________________________________________________
bool FakeRatio::triggerSelection(){ 

  counter("TriggerSelection", kTrigger);

  bool any = false; //passed at least one of any trigger
      _iso = false; //passed at least one of the isolated triggers
  vector<string> trlines; 
  _TR_lines.clear();

  if     (std::abs(_denLeps[0]->pdgId()) == 11) {
    int etabin = findBin(_vFR_bins_eta_el, std::abs(_denLeps[0]->eta()));
    int ptbin  = findBin(_vFR_bins_pt_el ,          _denLeps[0]->pt ()) ;
    if(etabin > -1 && ptbin > -1){
      vector<string> lines_non = _vTR_lineperpteta_el_non[etabin][ptbin];
      vector<string> lines_iso = _vTR_lineperpteta_el_iso[etabin][ptbin];
      trlines = Tools::insertIntoVectorS(trlines, lines_non);
      trlines = Tools::insertIntoVectorS(trlines, lines_iso);
    }
  }
  else if(std::abs(_denLeps[0]->pdgId()) == 13) {
    int etabin = findBin(_vFR_bins_eta_mu, std::abs(_denLeps[0]->eta()));
    int ptbin  = findBin(_vFR_bins_pt_mu ,          _denLeps[0]->pt ()) ;
    if(etabin > -1 && ptbin > -1){
      vector<string> lines_non = _vTR_lineperpteta_mu_non[findBin(_vFR_bins_eta_mu, std::abs(_denLeps[0]->eta()))]
                                                         [findBin(_vFR_bins_pt_mu ,          _denLeps[0]->pt ()) ];
      vector<string> lines_iso = _vTR_lineperpteta_mu_iso[findBin(_vFR_bins_eta_mu, std::abs(_denLeps[0]->eta()))]
                                                         [findBin(_vFR_bins_pt_mu ,          _denLeps[0]->pt ()) ];
      trlines = Tools::insertIntoVectorS(trlines, lines_non);
      trlines = Tools::insertIntoVectorS(trlines, lines_iso);
    }
  }

  if(trlines.size() > 0){
    for(unsigned int i = 0; i < trlines.size(); ++i){

      if(Tools::trim(trlines[i]) != ""){
        if(_vc->get(Tools::trim(trlines[i])) == 1) {
          any     = true;
          _TR_lines.push_back(trlines[i]);
          if(trlines[i].find("IsoVL") != std::string::npos || trlines[i].find("IsoVVL") != std::string::npos) 
            _iso = true;
        }
      }
    }
    //if(trlines.size() == 1 && trlines[0] == "")
    //  any = true;

  }


  // at least one auxiliary trigger per pt bin to be passed
  if(!makeCut(any, "at least one trigger path", "=", kTrigger)) return false;

  if(!makeCut(triggerEmulation(_iso, kTrigger), "full trigger emulation cuts", "=", kTrigger)) return false;


  _exts.clear();
  _exts = findTriggerExts();


  return true;

}




/*****************************************************************************
******************************************************************************
** EXECUTING TASKS                                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::fillEventPlots(){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill("MR_HT_"         + _exts[i], _HT                 , _weight);
    fill("MR_MET_"        + _exts[i], _met->pt()          , _weight);
    fill("MR_NumBJets_"   + _exts[i], _vc->get(_bvar)     , _weight);
    fill("MR_NumDenEls_"  + _exts[i], _denEls .size()     , _weight);
    fill("MR_NumDenLeps_" + _exts[i], _denLeps.size()     , _weight);
    fill("MR_NumDenMus_"  + _exts[i], _denMus .size()     , _weight);
    fill("MR_NumJets_"    + _exts[i], _nJets              , _weight);
    fill("MR_NumNumEls_"  + _exts[i], _numEls .size()     , _weight);
    fill("MR_NumNumLeps_" + _exts[i], _numLeps.size()     , _weight);
    fill("MR_NumNumMus_"  + _exts[i], _numMus .size()     , _weight);
    fill("MR_NumVrtx_"    + _exts[i], _vc->get(_nvert)    , _weight);
  }

}


//____________________________________________________________________________
void FakeRatio::fillEwkEventPlots(){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill("ER_HT_"  + _exts[i], _HT                 , _weight);
    fill("ER_MET_" + _exts[i], _met->pt()          , _weight);
  }

}


//____________________________________________________________________________
void FakeRatio::fillEwkLepPlots(string prepend, Candidate * lep, int lepIdx, int wp){
  /*
    fills the control plots for leptons PER LEPTON
  */  

  Candidate * mt = Candidate::create( lep, _met);

  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill(prepend + "Pt_"      + _exts[i],          _vc->get(_leps + "_pt"        , lepIdx) , _weight);
    fill(prepend + "Eta_"     + _exts[i], std::abs(_vc->get(_leps + "_eta"       , lepIdx)), _weight);
    fill(prepend + "DXY_"     + _exts[i], std::abs(_vc->get(_leps + "_dxy"       , lepIdx)), _weight);
    fill(prepend + "DZ_"      + _exts[i], std::abs(_vc->get(_leps + "_dz"        , lepIdx)), _weight);
    fill(prepend + "SIP_"     + _exts[i],          _vc->get(_leps + "_sip3d"     , lepIdx) , _weight);
    fill(prepend + "MiniIso_" + _exts[i],          _vc->get(_leps + "_miniRelIso", lepIdx) , _weight);
    fill(prepend + "MT_"      + _exts[i], mt -> mass()                                     , _weight);
    fill(prepend + "MT0_"     + _exts[i], mt -> mass()                                     , _weight);
    fill(prepend + "MT1_"     + _exts[i], mt -> mass()                                     , _weight);
  }

}


//____________________________________________________________________________
void FakeRatio::fillEwkLeptonPlots(){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  for(unsigned int i = 0; i < _denEls.size(); ++i) { fillEwkLepPlots("ER_DenEl"  , _denEls[i]  , _denElsIdx[i], SusyModule::kTight ); }
  for(unsigned int i = 0; i < _denMus.size(); ++i) { fillEwkLepPlots("ER_DenMu"  , _denMus[i]  , _denMusIdx[i], SusyModule::kMedium); }
  for(unsigned int i = 0; i < _numEls.size(); ++i) { fillEwkLepPlots("ER_NumEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
  for(unsigned int i = 0; i < _numMus.size(); ++i) { fillEwkLepPlots("ER_NumMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }

}


//____________________________________________________________________________
void FakeRatio::fillFRMaps(string prepend, Candidate * lep, int lepIdx, int wp){

  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill(prepend + "MapPt_"     + _exts[i], overflowPt(_vc->get(_leps + "_pt", lepIdx)) , std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);
    fill(prepend + "MapPtJet_"  + _exts[i], overflowPt(_susyMod -> closestJetPt(lepIdx)), std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);
    fill(prepend + "MapPtCorr_" + _exts[i], overflowPt(_susyMod -> conePt(lepIdx, wp))  , std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);
  }

}


//____________________________________________________________________________
void FakeRatio::fillFakeRatioMaps(){
  /*
    fills the fake ratio maps for leptons
    parameters: none
    return: none
  */

  for(unsigned int i = 0; i < _denEls.size(); ++i) { fillFRMaps("MR_DenEl", _denEls[i]  , _denElsIdx[i], SusyModule::kTight ); }
  for(unsigned int i = 0; i < _denMus.size(); ++i) { fillFRMaps("MR_DenMu", _denMus[i]  , _denMusIdx[i], SusyModule::kMedium); }
  for(unsigned int i = 0; i < _numEls.size(); ++i) { fillFRMaps("MR_NumEl", _numEls[i]  , _numElsIdx[i], SusyModule::kTight );
                                                     fillFRMaps("MR_RatEl", _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
  for(unsigned int i = 0; i < _numMus.size(); ++i) { fillFRMaps("MR_NumMu", _numMus[i]  , _numMusIdx[i], SusyModule::kMedium);
                                                     fillFRMaps("MR_RatMu", _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }

}

void FakeRatio::fillTriggerTestPlots(){

  if(std::abs(_denLeps[0]->pdgId()) == 11){
    for(unsigned j = 0; j < _vTR_lines_el_non[0].size(); ++j)
      if(_vc->get(_vTR_lines_el_non[0][j]) == 1 && triggerEmulation(false, kTrigger)) 
        fill("MR_DenElMapTrTest_non" + Tools::intToString(j), overflowPt(_denLeps[0]->pt()), std::abs(_denLeps[0]->eta()));
    for(unsigned j = 0; j < _vTR_lines_el_iso[0].size(); ++j)
      if(_vc->get(_vTR_lines_el_iso[0][j]) == 1 && triggerEmulation(true, kTrigger)) 
        fill("MR_DenElMapTrTest_iso" + Tools::intToString(j), overflowPt(_denLeps[0]->pt()), std::abs(_denLeps[0]->eta()));
  }
  else {
    for(unsigned j = _vTR_lines_el_non[0].size(); j < _vTR_lines_el_non[0].size() + _vTR_lines_mu_non[0].size(); ++j)
      if(_vc->get(_vTR_lines_mu_non[0][j - _vTR_lines_el_non[0].size()]) == 1) 
        fill("MR_DenMuMapTrTest_non" + Tools::intToString(j), overflowPt(_denLeps[0]->pt()), std::abs(_denLeps[0]->eta()));
    for(unsigned j = _vTR_lines_el_iso[0].size(); j < _vTR_lines_el_iso[0].size() + _vTR_lines_mu_iso[0].size(); ++j)
      if(_vc->get(_vTR_lines_mu_iso[0][j - _vTR_lines_el_iso[0].size()]) == 1) 
        fill("MR_DenMuMapTrTest_iso" + Tools::intToString(j), overflowPt(_denLeps[0]->pt()), std::abs(_denLeps[0]->eta()));
  }

}


//____________________________________________________________________________
void FakeRatio::fillLepPlots(string prepend, Candidate * lep, int lepIdx, int wp){
  /*
    fills the control plots for leptons PER LEPTON
  */  

  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill(prepend + "Pt_"      + _exts[i],          _vc->get(_leps + "_pt"        , lepIdx) , _weight);
    fill(prepend + "Eta_"     + _exts[i], std::abs(_vc->get(_leps + "_eta"       , lepIdx)), _weight);
    fill(prepend + "DXY_"     + _exts[i], std::abs(_vc->get(_leps + "_dxy"       , lepIdx)), _weight);
    fill(prepend + "DZ_"      + _exts[i], std::abs(_vc->get(_leps + "_dz"        , lepIdx)), _weight);
    fill(prepend + "SIP_"     + _exts[i],          _vc->get(_leps + "_sip3d"     , lepIdx) , _weight);
    fill(prepend + "RelIso_"  + _exts[i],          _vc->get(_leps + "_relIso03"  , lepIdx) , _weight);
    fill(prepend + "MiniIso_" + _exts[i],          _vc->get(_leps + "_miniRelIso", lepIdx) , _weight);
    fill(prepend + "PtRel_"   + _exts[i],          _vc->get(_leps + "_jetPtRelv2", lepIdx) , _weight);
    fill(prepend + "MT_"      + _exts[i], Candidate::create( lep, _met) -> mass()          , _weight);
    fill(prepend + "PtJet_"   + _exts[i], _susyMod -> closestJetPt(lepIdx)                 , _weight);
    fill(prepend + "PtCorr_"  + _exts[i], _susyMod -> conePt(lepIdx, wp)                   , _weight);
  }

}


//____________________________________________________________________________
void FakeRatio::fillLeptonPlots(){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  for(unsigned int i = 0; i < _denEls.size(); ++i) { fillLepPlots("MR_DenEl"  , _denEls[i]  , _denElsIdx[i], SusyModule::kTight ); }
  for(unsigned int i = 0; i < _denMus.size(); ++i) { fillLepPlots("MR_DenMu"  , _denMus[i]  , _denMusIdx[i], SusyModule::kMedium); }
  for(unsigned int i = 0; i < _numEls.size(); ++i) { fillLepPlots("MR_NumEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
  for(unsigned int i = 0; i < _numMus.size(); ++i) { fillLepPlots("MR_NumMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }

}


//____________________________________________________________________________
void FakeRatio::fillJetPlots(){
  /*
    fills the control plots for jets
    parameters: none
    return: none
  */

  for(unsigned int i = 0; i < _exts.size(); ++i){
    for(unsigned int j = 0; j < _goodJets.size(); ++j){
      fill("MR_JetPt_" + _exts[i], _goodJets[j]->pt(), _weight);
    }
  }
}


//____________________________________________________________________________
void FakeRatio::fillQcdEventPlots(){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  //vector<string> exts = _findTriggerExts();
  for(unsigned int i = 0; i < _exts.size(); ++i){
    fill("QR_HT_"  + _exts[i], _HT                 , _weight);
    fill("QR_MET_" + _exts[i], _met->pt()          , _weight);
    if(_met -> pt() < 20) 
      fill("QR_MET_small_" + _exts[i], 1);
    if(_met -> pt() < 80 && _met -> pt() > 45) 
      fill("QR_MET_large_" + _exts[i], 1);
  }

}


//____________________________________________________________________________
void FakeRatio::fillQcdFakeRatioMaps(){
  /*
    fills the fake ratio maps for leptons
    parameters: none
    return: none
  */

  if(_met -> pt() < 20){
    for(unsigned int i = 0; i < _denEls.size(); ++i)   fillFRMaps("QR_small_DenEl", _denEls[i]  , _denElsIdx[i], SusyModule::kTight );
    for(unsigned int i = 0; i < _denMus.size(); ++i)   fillFRMaps("QR_small_DenMu", _denMus[i]  , _denMusIdx[i], SusyModule::kMedium);
    for(unsigned int i = 0; i < _numEls.size(); ++i) { fillFRMaps("QR_small_NumEl", _numEls[i]  , _numElsIdx[i], SusyModule::kTight );
                                                       fillFRMaps("QR_small_RatEl", _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
    for(unsigned int i = 0; i < _numMus.size(); ++i) { fillFRMaps("QR_small_NumMu", _numMus[i]  , _numMusIdx[i], SusyModule::kMedium);
                                                       fillFRMaps("QR_small_RatMu", _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }
  }

  if(_met -> pt() > 45 && _met -> pt() < 80){
    for(unsigned int i = 0; i < _denEls.size(); ++i)   fillFRMaps("QR_large_DenEl", _denEls[i]  , _denElsIdx[i], SusyModule::kTight );
    for(unsigned int i = 0; i < _denMus.size(); ++i)   fillFRMaps("QR_large_DenMu", _denMus[i]  , _denMusIdx[i], SusyModule::kMedium);
    for(unsigned int i = 0; i < _numEls.size(); ++i) { fillFRMaps("QR_large_NumEl", _numEls[i]  , _numElsIdx[i], SusyModule::kTight );
                                                       fillFRMaps("QR_large_RatEl", _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
    for(unsigned int i = 0; i < _numMus.size(); ++i) { fillFRMaps("QR_large_NumMu", _numMus[i]  , _numMusIdx[i], SusyModule::kMedium);
                                                       fillFRMaps("QR_large_RatMu", _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }
  }

}


//____________________________________________________________________________
vector<string> FakeRatio::findTriggerExts(){

  vector<string> result;

  //cout << "searching for trigger extensions" << endl;
  //DUMPVECTOR(_TR_lines);
  for(unsigned int i = 0; i < _TR_lines.size(); ++i){

    vector<string>::iterator pos = find(_vTR_lines_el_non[0].begin(), _vTR_lines_el_non[0].end(), _TR_lines[i]);
    if(pos != _vTR_lines_el_non[0].end()){
      result.push_back("non" + Tools::intToString(pos - _vTR_lines_el_non[0].begin()));
      continue;
    }

    pos = find(_vTR_lines_el_iso[0].begin(), _vTR_lines_el_iso[0].end(), _TR_lines[i]);
    if(pos != _vTR_lines_el_iso[0].end()){
      result.push_back("iso" + Tools::intToString(pos - _vTR_lines_el_iso[0].begin()));
      continue;
    }

    pos = find(_vTR_lines_mu_non[0].begin(), _vTR_lines_mu_non[0].end(), _TR_lines[i]);
    if(pos != _vTR_lines_mu_non[0].end()){
      result.push_back("non" + Tools::intToString(pos - _vTR_lines_mu_non[0].begin()));
      continue;
    }

    pos = find(_vTR_lines_mu_iso[0].begin(), _vTR_lines_mu_iso[0].end(), _TR_lines[i]);
    if(pos != _vTR_lines_mu_iso[0].end()){
      result.push_back("iso" + Tools::intToString(pos - _vTR_lines_mu_iso[0].begin()));
      continue;
    }
  }

  //cout << "found trigger extensions:" << endl;
  //DUMPVECTOR(result);

  return result;

}


//____________________________________________________________________________
vector<int> FakeRatio::findTriggerIdxs(){
 
  vector<int> result;

  string fix = "non";
  vector<string> els = _vTR_lines_el_non[0];
  vector<string> mus = _vTR_lines_mu_non[0];
  if(_iso){
    fix = "iso";
    els = _vTR_lines_el_iso[0];
    mus = _vTR_lines_mu_iso[0];
  }

  for(unsigned int i = 0; i < _TR_lines.size(); ++i){
    vector<string>::iterator pos = find(els.begin(), els.end(), _TR_lines[i]);
    if(pos != els.end()){
      result.push_back(pos - els.begin());
    }
    else {
      pos = find(mus.begin(), mus.end(), _TR_lines[i]);
      if(pos != mus.end()){
        result.push_back(els.size() + pos - mus.begin());
      }
    }
  }

  return result;

}


//____________________________________________________________________________
float FakeRatio::overflowPt(float rawPt){

	if(rawPt >= 70.) return 60.;

	return rawPt;
}

