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

  _vc->registerVar("run"                          , "I" );
  _vc->registerVar("lumi"                         , "I" );
  _vc->registerVar("evt"                          , "I" );
  _vc->registerVar("HLT_SingleMu"                 , "F" );
  _vc->registerVar("HLT_MuEG"                     , "F" );
  _vc->registerVar("HLT_TripleEl"                 , "F" );
  _vc->registerVar("HLT_DoubleEl"                 , "F" );
  _vc->registerVar("HLT_DoubleMu"                 , "F" );
  _vc->registerVar("nVert"                        , "I" );
  _vc->registerVar("nTrueInt"                     , "I" );
  _vc->registerVar("nTrueInt"                     , "I" );
  _vc->registerVar("nBJetPt40Medium"              , "I" );
  _vc->registerVar("puWeight"                     , "F" );
  _vc->registerVar("genWeight"                    , "F" );
  _vc->registerVar("nLepGood"                     , "I" );
  _vc->registerVar("LepGood_pt"                   , "AF");
  _vc->registerVar("LepGood_eta"                  , "AF");
  _vc->registerVar("LepGood_phi"                  , "AF");
  _vc->registerVar("LepGood_charge"               , "AI");
  _vc->registerVar("LepGood_tightCharge"          , "AI");
  _vc->registerVar("LepGood_mediumMuonId"         , "AI");
  _vc->registerVar("LepGood_mvaIdPhys14"          , "AF");
  _vc->registerVar("LepGood_pdgId"                , "AI");
  _vc->registerVar("LepGood_relIso03"             , "AF");
  _vc->registerVar("LepGood_relIso04"             , "AF");
  _vc->registerVar("LepGood_jetPtRatio"           , "AF");
  _vc->registerVar("LepGood_jetPtRel"             , "AF");
  _vc->registerVar("LepGood_jetBTagCSV"           , "AF");
  _vc->registerVar("LepGood_miniRelIso"           , "AF");
  _vc->registerVar("LepGood_dxy"                  , "AF");
  _vc->registerVar("LepGood_dz"                   , "AF");
  _vc->registerVar("LepGood_ip3d"                 , "AF");
  _vc->registerVar("LepGood_sip3d"                , "AF");
  _vc->registerVar("LepGood_edxy"                 , "AF");
  _vc->registerVar("LepGood_edz"                  , "AF");
  _vc->registerVar("LepGood_convVeto"             , "AI");
  _vc->registerVar("LepGood_lostHits"             , "AI");
  _vc->registerVar("LepGood_mvaSusy"              , "AF");
  _vc->registerVar("LepGood_mcMatchId"            , "AI");
  _vc->registerVar("LepGood_mcMatchAny"           , "AI");
  _vc->registerVar("met_pt"                       , "F" );
  _vc->registerVar("met_eta"                      , "F" );
  _vc->registerVar("met_phi"                      , "F" );
  _vc->registerVar("met_mass"                     , "F" );
  _vc->registerVar("nJet25"                       , "I" );
  _vc->registerVar("nJet40"                       , "I" );
  _vc->registerVar("nJet"                         , "I" );
  _vc->registerVar("Jet_id"                       , "AI");
  _vc->registerVar("Jet_pt"                       , "AF");
  _vc->registerVar("Jet_rawPt"                    , "AF");
  _vc->registerVar("Jet_eta"                      , "AF");
  _vc->registerVar("Jet_phi"                      , "AF");
  _vc->registerVar("Jet_mass"                     , "AF");
  _vc->registerVar("Jet_btagCSV"                  , "AF");

  _vc->registerVar("htJet40j"                     , "F" );
  _vc->registerVar("minMllAFAS"                   , "F" );
  _vc->registerVar("minMllAFOS"                   , "F" );
  _vc->registerVar("mZ1"                          , "F" );
  _vc->registerVar("nLepGood10"                   , "I" );

 
  //generator informations
  _vc->registerVar("nGenPart"                     , "I" );
  _vc->registerVar("GenPart_eta"                  , "AF");
  _vc->registerVar("GenPart_phi"                  , "AF");
  _vc->registerVar("GenPart_pdgId"                , "AI");
  
  //bjets
  _vc->registerVar("nBJetLoose25"                 , "I" );
  _vc->registerVar("nBJetMedium40"                , "I" );
  _vc->registerVar("nBJetMedium25"                , "I" );
  _vc->registerVar("nSoftBJetMedium25"            , "I" );

  //additional counter categories
  _au->addCategory( kLElId        , "loose El Id"     );
  _au->addCategory( kTElId        , "tight El Id"     );
  _au->addCategory( kVElId        , "veto El Id"      );
  _au->addCategory( kLMuId        , "loose Mu Id"     );
  _au->addCategory( kTMuId        , "tight Mu Id"     );
  _au->addCategory( kVMuId        , "veto Mu Id"      );
  _au->addCategory( kJetId        , "jet Id"          );
  _au->addCategory( kLMGVetoLepSel, "vetoLMGLepSel"   );
  _au->addCategory( kZVetoLepSel  , "vetoZLepSel"     );

  //extra input variables

  _lepptcut = getCfgVarS("LEPPTCUT"); // lepton pt cut, if none given, we take default > 10GeV
  _lepflav  = getCfgVarS("LEPFLAV");
  _lepid    = getCfgVarS("LEPID"  );
  _lepiso   = getCfgVarS("LEPISO" );
  _leppt    = getCfgVarS("LEPPT"  );
  _xpol     = getCfgVarS("XPOL"   );
  _MR       = getCfgVarS("MR"     );
  _fakes    = getCfgVarS("FAKES"  );
  _etabin   = getCfgVarS("ETABIN" );
  
}


//____________________________________________________________________________
void FRinSitu::modifyWeight() {
  /*
    modifies the event weight for every entry in the tree
    parameters: none
    return: none
  */ 
	
  //_weight = (i->second)->Getweight();
  // if(_PUReweighting) 
  //   _weight *= _vc->get("puWeight");

}


//____________________________________________________________________________
void FRinSitu::run(){

  _lEls   .clear();
  _lLeps  .clear();
  _lMus   .clear();
  _lntEls .clear();
  _lntLeps.clear();
  _lntMus .clear();
  _tEls   .clear();
  _tLeps  .clear();
  _tMus   .clear();
  _vEls   .clear();
  _vLeps  .clear();
  _vMus   .clear();

  _lElIdx   .clear();
  _lLepIdx  .clear();
  _lMuIdx   .clear();
  _lntElIdx .clear();
  _lntLepIdx.clear();
  _lntMuIdx .clear();
  _tElIdx   .clear();
  _tLepIdx  .clear();
  _tMuIdx   .clear();
  _vElIdx   .clear();
  _vLepIdx  .clear();
  _vMuIdx   .clear();

  _jets  .clear();

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
  fillEventPlots("MR");
  fillFakeRatioMaps("MR");
  fillLeptonPlots("MR");

	
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
void FRinSitu::divideFRMap(string kr, string postpend){

  for(unsigned int i=0; i<_numDS; ++i){
    TH1 * denom = _hm -> getHisto(kr + "_L" + postpend, i);
    TH1 * num   = _hm -> getHisto(kr + "_R" + postpend, i);
    num -> Divide(denom);
  } 
  
}


//____________________________________________________________________________
void FRinSitu::divideFRMaps(string kr, string lep){

  divideFRMap(kr, lep + "SyncMapPt"     );
  divideFRMap(kr, lep + "SyncMapPtJet"  );
  divideFRMap(kr, lep + "SyncMapPtMIso" );
  divideFRMap(kr, lep + "SyncMapPtMIso2");
} 


//____________________________________________________________________________
void FRinSitu::registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis){

  for(int i = 0; i < leps.size(); ++i)
    _hm->addVariable(leps[i] + var, nbins, bmin, bmax, axis);

}


//____________________________________________________________________________
void FRinSitu::registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis){

  for(int i = 0; i < leps.size(); ++i)
    _hm->addVariable(leps[i] + var, nxbins, xbins, nybins, ybins, xaxis, yaxis);

}


//____________________________________________________________________________
void FRinSitu::defineOutput(){
  /*
    defines and reserves all output that is produced in this class
    parameters: none
    return: none
  */ 

  // bins
  float FR_bins_eta_el_sync[4] = { 0.0, 1.0, 2.0, 2.5};
  float FR_bins_eta_mu_sync[4] = { 0.0, 1.0, 2.0, 2.4};
  float FR_bins_pt_lep_sync[6] = {10.0, 15.0, 25.0, 35.0, 50.0, 70.0};
  
  vector<float> bins_eta_el_sync = Tools::toVector(FR_bins_eta_el_sync);
  vector<float> bins_eta_mu_sync = Tools::toVector(FR_bins_eta_mu_sync); 
  vector<float> bins_pt_lep_sync = Tools::toVector(FR_bins_pt_lep_sync);
  
  // leptons
  string MR_leps_den[6]        = {"MR_LEl", "MR_LNTEl", "MR_LLep", "MR_LNTLep", "MR_LMu", "MR_LNTMu"};
  string MR_leps_num[3]        = {"MR_TEl", "MR_TLep", "MR_TMu"};
  string MR_leps_rat[3]        = {"MR_REl", "MR_RLep" , "MR_RMu"};
  string MR_els[4]             = {"MR_LEl", "MR_LNTEl", "MR_TEl", "MR_REl"};
  string MR_mus[4]             = {"MR_LMu", "MR_LNTMu", "MR_TMu", "MR_RMu"};
  
  vector<string> leps_den      = Tools::toVector(MR_leps_den);
  vector<string> leps_num      = Tools::toVector(MR_leps_num);
  vector<string> leps_rat      = Tools::toVector(MR_leps_rat);
  vector<string> els_r         = Tools::toVector(MR_els     );
  vector<string> mus_r         = Tools::toVector(MR_mus     );

  vector<string> leps          = leps_den;
                 leps.insert(leps.end(), leps_num.begin(), leps_num.end());
  vector<string> leps_r        = leps;
                 leps_r.insert(leps_r.end(), leps_rat.begin(), leps_rat.end());

  // this is now here but should be somewhere else!!!
  setMeasurementRegion();

  // MR Region
  _hm->addVariable("MR_HT"        , 1000,   0.0, 1000.0, "H_T [GeV]"                            );
  _hm->addVariable("MR_MET"       , 1000,   0.0, 1000.0, "#slash{E}_T [GeV]"                    );
  _hm->addVariable("MR_NBJets"    ,   20,   0.0,   20.0, "b-jet multiplicity"                   );
  _hm->addVariable("MR_NLEls"     ,   20,   0.0,   20.0, "loose electron multiplicity"          );
  _hm->addVariable("MR_NLNTEls"   ,   20,   0.0,   20.0, "loose not tight electron multiplicity");
  _hm->addVariable("MR_NTEls"     ,   20,   0.0,   20.0, "tight electron multiplicity"          );
  _hm->addVariable("MR_NVEls"     ,   20,   0.0,   20.0, "veto electron multiplicity"           );
  _hm->addVariable("MR_NJets"     ,   20,   0.0,   20.0, "jet multiplicity"                     );
  _hm->addVariable("MR_NLLeps"    ,   20,   0.0,   20.0, "loose lepton multiplicity"            );
  _hm->addVariable("MR_NLNTLeps"  ,   20,   0.0,   20.0, "loose not tight lepton multiplicity"  );
  _hm->addVariable("MR_NTLeps"    ,   20,   0.0,   20.0, "tight lepton multiplicity"            );
  _hm->addVariable("MR_NVLeps"    ,   20,   0.0,   20.0, "veto lepton multiplicity"             );
  _hm->addVariable("MR_NLMus"     ,   20,   0.0,   20.0, "loose muon multiplicity"              );
  _hm->addVariable("MR_NLNTMus"   ,   20,   0.0,   20.0, "loose not tight muon multiplicity"    );
  _hm->addVariable("MR_NTMus"     ,   20,   0.0,   20.0, "tight muon multiplicity"              );
  _hm->addVariable("MR_NVMus"     ,   20,   0.0,   20.0, "veto muon multiplicity"               );
  _hm->addVariable("MR_NVrtx"     ,   40,   0.0,   40.0, "vertex multiplicity"                  );
  _hm->addVariable("MR_JetCSVBTag",   50,   0.0,    1.0, "jet CSV B-Tag"                        );
  _hm->addVariable("MR_JetPt"     , 1000,   0.0, 1000.0, "P_T(jet) [GeV]"                       );

  registerLepPlots(leps_r, "DXY"    , 5000,   0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(leps_r, "DZ"     , 5000,   0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(leps_r, "IP"     , 5000,   0.0,   10.0, "#||{ip3d}(lep) [cm]"                  );
  registerLepPlots(leps_r, "SIP"    , 1000,   0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(leps_r, "SDXY"   , 1000,   0.0,   10.0, "SDXY(lep)"                            );
  registerLepPlots(leps_r, "SDZ"    , 1000,   0.0,   10.0, "SDZ(lep)"                             );
  registerLepPlots(leps_r, "Eta"    ,  240,   0.0,    2.4, "#||{#eta(lep)}"                       );
  registerLepPlots(leps_r, "Iso"    ,   50,   0.0,    1.0, "PF Iso (lep)"                         );
  registerLepPlots(leps_r, "MT"     , 1000,   0.0, 1000.0, "M_T(lep) [GeV]"                       );
  registerLepPlots(leps_r, "Pt"     , 1000,   0.0, 1000.0, "P_T(lep) [GeV]"                       );
  registerLepPlots(leps_r, "PtJet"  , 1000,   0.0, 1000.0, "P_T(jet closest to lep) [GeV]"        );
  registerLepPlots(leps_r, "PtRel"  , 1000,   0.0, 1000.0, "PtRel(lep)"                           );


  // electron maps
  registerLepPlots(els_r, "SyncMapPt"     , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_el_sync.size()-1, bins_eta_el_sync, "P_T(e) [GeV]"                   , "#||{#eta}(e)");
  registerLepPlots(els_r, "SyncMapPtJet"  , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_el_sync.size()-1, bins_eta_el_sync, "P_T(jet closest to e) [GeV]"    , "#||{#eta}(e)");
  registerLepPlots(els_r, "SyncMapPtMIso" , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_el_sync.size()-1, bins_eta_el_sync, "P_T(e)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(e)");
  registerLepPlots(els_r, "SyncMapPtMIso2", bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_el_sync.size()-1, bins_eta_el_sync, "P_T(e)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(e)");
  
  // muon maps

  registerLepPlots(mus_r, "SyncMapPt"     , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_mu_sync.size()-1, bins_eta_mu_sync, "P_T(#mu) [GeV]"                   , "#||{#eta}(#mu)");
  registerLepPlots(mus_r, "SyncMapPtJet"  , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_mu_sync.size()-1, bins_eta_mu_sync, "P_T(jet closest to #mu) [GeV]"    , "#||{#eta}(#mu)");
  registerLepPlots(mus_r, "SyncMapPtMIso" , bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_mu_sync.size()-1, bins_eta_mu_sync, "P_T(#mu)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(#mu)");
  registerLepPlots(mus_r, "SyncMapPtMIso2", bins_pt_lep_sync.size()-1, bins_pt_lep_sync, bins_eta_mu_sync.size()-1, bins_eta_mu_sync, "P_T(#mu)*(1+(miniIso-cut)) [GeV]" , "#||{#eta}(#mu)");


}


//____________________________________________________________________________
void FRinSitu::loadInput(){
  /*
    loads all input from the cache or from the database
    parameters: none
    return: none
  */


  // define function in MPAF for loading histograms, text files, histograms from database 

}


//____________________________________________________________________________
void FRinSitu::writeOutput(){
  /*
    writes all output of this class to the disk
    paramters: none
    return: none
  */

  divideFRMaps("MR", "El");
  divideFRMaps("MR", "Mu");

  //_hm->saveHistos ("FRinSitu", _cfgName);
  //_au->saveNumbers("FRinSitu", _cfgName);

}


//____________________________________________________________________________
void FRinSitu::modifySkimming(){
  // if adding variables in the skimming tree is needed...
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
  
  for(int i = 0; i < _vc->get("nLepGood"); ++i){

    bool loose = false;
    bool tight = false;

    // electrons
    if(std::abs(_vc->get("LepGood_pdgId", i)) == 11){		  
      if(looseElectronSelection(i)) {
//cout << "pushing " << i << " into loose electrons" << endl;
        _lEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.0005) );
        _lElIdx.push_back(i);
        _lLeps.push_back( _lEls[ _lEls.size()-1 ] );
        _lLepIdx.push_back(i);
        loose = true; 
      }
      if(tightElectronSelection(i)) {
//cout << "pushing " << i << " into tight electrons" << endl;
        _tEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.0005) );
        _tElIdx.push_back(i);
        _tLeps.push_back( _tEls[ _tEls.size()-1 ] );
        _tLepIdx.push_back(i);
        tight = true;
      }
      if(loose && !tight){
        _lntEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.0005) );
        _lntElIdx.push_back(i);
        _lntLeps.push_back( _lntEls[ _lntEls.size()-1 ] );
        _lntLepIdx.push_back(i);
      }
      if(!loose && !tight){
        if(vetoElectronSelection(i))  {
          _vEls.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					     _vc->get("LepGood_eta", i),
					     _vc->get("LepGood_phi", i),
					     _vc->get("LepGood_pdgId", i),
					     _vc->get("LepGood_charge", i),
					     0.0005) );
          _vElIdx.push_back(i);
          _vLeps.push_back( _vEls[ _vEls.size()-1 ] );
          _vLepIdx.push_back(i);
        }
      }
    }

    // muons
    else if(std::abs(_vc->get("LepGood_pdgId", i)) == 13){
      if(looseMuonSelection(i)) {
        _lMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.105) );
        _lMuIdx.push_back(i);
        _lLeps.push_back( _lMus[ _lMus.size()-1 ] );
        _lLepIdx.push_back(i);
        loose = true;
      }
      if(tightMuonSelection(i)) {
        _tMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.105) );
        _tMuIdx.push_back(i);
        _tLeps.push_back( _tMus[ _tMus.size()-1 ] );
        _tLepIdx.push_back(i);
        tight = true;
      }
      if(loose && !tight){
        _lntMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					  _vc->get("LepGood_eta", i),
					  _vc->get("LepGood_phi", i),
					  _vc->get("LepGood_pdgId", i),
					  _vc->get("LepGood_charge", i),
					  0.105) );
        _lntMuIdx.push_back(i);
        _lntLeps.push_back( _lntMus[ _lntMus.size()-1 ] );
        _lntLepIdx.push_back(i);
      }
      if(!loose && !tight) {
        if(vetoMuonSelection(i))  {
          _vMus.push_back( Candidate::create(_vc->get("LepGood_pt", i),
					     _vc->get("LepGood_eta", i),
					     _vc->get("LepGood_phi", i),
					     _vc->get("LepGood_pdgId", i),
					     _vc->get("LepGood_charge", i),
					     0.105) );
          _vMuIdx.push_back(i);
          _vLeps.push_back( _vMus[ _vMus.size()-1 ] );
          _vLepIdx.push_back(i);
        }
      }
    }
  }
 
  _nLEls    = _lEls   .size();
  _nLLeps   = _lLeps  .size();
  _nLMus    = _lMus   .size();
  _nLNTEls  = _lntEls .size();
  _nLNTLeps = _lntLeps.size();
  _nLNTMus  = _lntMus .size();
  _nTEls    = _tEls   .size();
  _nTLeps   = _tLeps  .size();
  _nTMus    = _tMus   .size();
  _nVEls    = _vEls   .size();
  _nVLeps   = _vLeps  .size();
  _nVMus    = _vMus   .size();
  
  for(int i = 0; i < _vc->get("nJet40"); ++i){
    if(goodJetSelection(i)) {
      _jets.push_back( Candidate::create(_vc->get("Jet_pt", i),
					 _vc->get("Jet_eta", i),
					 _vc->get("Jet_phi", i) ) );
      
    }
  }

  _nJets  = _jets.size();

  _HT  = HT();
  _met = Candidate::create(_vc->get("met_pt"), _vc->get("met_phi") );

}


//____________________________________________________________________________
bool FRinSitu::goodJetSelection(int jetIdx){
  /*
    does the selection of good jets, i.e. minimum selection of jets 
    parameters: jetIdx
    return: true (if the jet is good), false (else)
  */
  
  counter("JetDenominator", kJetId);

  if(!makeCut<float>(_vc->get("Jet_pt", jetIdx)       , 40.0, ">", "pt selection" , 0, kJetId) ) return false;
  //if(!makeCut<float>(fabs(_vc->get("Jet_eta", jetIdx)),  2.4, "<", "eta selection", 0, kJetId) ) return false;

  //// SF: here we require dR(j,every loose lepton) > 0.4
  //for(unsigned int il=0; il<_lLeps.size(); ++il){
  //  float dr = KineUtils::dR(_leps[il]->eta(), _vc->get("Jet_eta", jetIdx),
  //  		     _leps[il]->phi(), _vc->get("Jet_phi", jetIdx));
  //  if(!makeCut<float>(dr, 0.4, ">", "dR selection", 0, kJetId) ) return false;
  //}

  //for(unsigned int il=0; il<_vLeps.size(); ++il){
  //  float dr = KineUtils::dR(_vLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
  //  		     _vLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
  //  if(!makeCut<float>(dr, 0.4, ">", "dR selection", 0, kJetId) ) return false;
  //}

  return true;

}


//____________________________________________________________________________
bool FRinSitu::looseElectronSelection(int elIdx){
  /*
    does the selection of loose electrons
    parameters: elIdx
    return: true (if the electron is a loose electron), false (else)
  */


  counter("LooseElectronDenominator", kLElId);

  float pt  = _vc->get("LepGood_pt", elIdx);
  float cut = 10.;
  string ct = ">";
  float  up = 0;
  if(_lepptcut == "c10")
    pt = ptMIso2(elIdx);

  //if(!makeCut<float>( _vc->get("LepGood_mcMatchId", elIdx) , 0  , "="  , "fakes", 0    , kLElId)) return false;
 
  if(!makeCut<float>( pt                                      , cut   , ct   , "pt selection"      , up   , kLElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx)), 2.5   , "<"  , "eta selection"     , 0    , kLElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx)), 1.4442, "[!]", "eta selection veto", 1.566, kLElId)) return false;

  //if(!makeCut(electronMvaCut(elIdx, false)    , "loose mva", "=", kLElId)) return false;
  //if(!makeCut(_vc->get("LepGood_convVeto", elIdx) > 0 , "convVeto", "=", kLElId)) return false;  
  //if(!makeCut(_vc->get("LepGood_lostHits", elIdx)==0 , "lost hits", "=", kLElId)) return false;  
  //bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  //if(!makeCut( conv, "conversion rejection", "=", kLElId)) return false;  

  //CH: denominator is cut-based denominator for all IDs
  bool lepid = false;
  if(_xpol == "isoid") lepid = electronCutId(elIdx, kLElId, 4.0, false, false, false); 
  else                 lepid = electronCutId(elIdx, kLElId, 4.0, false, true , false); 
  if(!makeCut( lepid, "lepton id", "=", kLElId)) return false;

  if(!makeCut<int>( _vc->get("LepGood_tightCharge", elIdx)    , 1     , ">"  , "charge selection"  , 0    , kLElId)) return false; 
  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  if(!makeCut( conv, "conversion rejection", "=", kLElId)) return false;  
  
  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=0; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
                             _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId", il)) == 13 && dr_cache > dr)
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kLElId)) return false;

  // additional ETA selection
  if     (_etabin == "0"   && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, "<", "additional ETA bin", 0  , kLElId) ) return false;
  else if(_etabin == "09"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, ">", "additional ETA bin", 1.2, kLElId) ) return false;
  else if(_etabin == "12"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, ">", "additional ETA bin", 1.5, kLElId) ) return false;
  else if(_etabin == "15"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, ">", "additional ETA bin", 2.4, kLElId) ) return false;
  else if(_etabin == "09-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, "<", "additional ETA bin", 0  , kLElId) ) return false;
  else if(_etabin == "09+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, ">", "additional ETA bin", 0  , kLElId) ) return false;
  else if(_etabin == "12-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, "<", "additional ETA bin", 0  , kLElId) ) return false;
  else if(_etabin == "12+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, ">", "additional ETA bin", 0  , kLElId) ) return false;
  else if(_etabin == "15-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, "<", "additional ETA bin", 0  , kLElId) ) return false;
  else if(_etabin == "15+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, ">", "additional ETA bin", 0  , kLElId) ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::looseMuonSelection(int muIdx){
  /*
    does the selection of loose muons
    parameters: muIdx
    return: true (if the muon is a loose muon), false (else)
  */

  counter("LooseMuonDenominator", kLMuId);
  float pt  = _vc->get("LepGood_pt", muIdx);
  float cut = 10.;
  string ct = ">";
  float  up = 0;
  if(_lepptcut == "c10")
    pt = ptMIso2(muIdx);
 
  if(!makeCut<float>( _vc->get("LepGood_mcMatchId", muIdx) , 0  , "="  , "fakes", 0    , kLMuId)) return false;
  if(!makeCut<float>( pt                            , cut, ct , "pt selection" , up, kLMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_eta", muIdx), 2.4, "<", "eta selection", 0 , kLMuId)) return false;

  //CH: denominator is cut-based denominator for all IDs
  bool lepid = false;
  lepid = muonCutId(muIdx, kLMuId, 4.0, false, false); 
  if(!makeCut( lepid, "lepton id", "=", kLMuId)) return false;

  // additional ETA selection
  if     (_etabin == "0"   && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, ">", "additional ETA bin", 1.2) ) return false;
  else if(_etabin == "12"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, ">", "additional ETA bin", 1.5) ) return false;
  else if(_etabin == "15"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, ">", "additional ETA bin", 2.4) ) return false;
  else if(_etabin == "09-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, ">", "additional ETA bin") ) return false;
  else if(_etabin == "12-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, "<", "additional ETA bin") ) return false;
  else if(_etabin == "12+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, ">", "additional ETA bin") ) return false;
  else if(_etabin == "15-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, "<", "additional ETA bin") ) return false;
  else if(_etabin == "15+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, ">", "additional ETA bin") ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::tightElectronSelection(int elIdx){
  /*
    does the selection of tight electrons
    parameters: elIdx
    return: true (if the electron is a tight electron), false (else)
  */


  counter("TightElectronDenominator", kTElId);
  float pt  = _vc->get("LepGood_pt", elIdx);
  float cut = 10.;
  string ct = ">";
  float  up = 0;
  if(_lepptcut == "c10")
    pt = ptMIso2(elIdx);
 
  if(!makeCut<float>( pt                                      , cut   , ct   , "pt selection"      , up   , kTElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx)), 2.5   , "<"  , "eta selection"     , 0    , kTElId)) return false;
  if(!makeCut<float>( std::abs(_vc->get("LepGood_eta", elIdx)), 1.4442, "[!]", "eta selection veto", 1.566, kTElId)) return false;

  //CH: denominator is cut-based denominator for all IDs
  bool lepid = false;
  if(_lepid == "mva") lepid = electronMvaId(elIdx, kTElId);
  else                lepid = electronCutId(elIdx, kTElId, 4.0, true, true);
  if(!makeCut( lepid, "lepton id", "=", kTElId)) return false;

  if(!makeCut<int>(   _vc->get("LepGood_tightCharge", elIdx)  , 1     , ">"  , "charge selection"  , 0    , kTElId)) return false; 
  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);
  if(!makeCut( conv, "conversion rejection", "=", kTElId)) return false;  
  
  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=0; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
                             _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId", il)) == 13 && dr_cache > dr)
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kTElId)) return false;

  // additional ETA selection
  if     (_etabin == "0"   && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, "<", "additional ETA bin", 0  , kTElId) ) return false;
  else if(_etabin == "09"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, ">", "additional ETA bin", 1.2, kTElId) ) return false;
  else if(_etabin == "12"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, ">", "additional ETA bin", 1.5, kTElId) ) return false;
  else if(_etabin == "15"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, ">", "additional ETA bin", 2.4, kTElId) ) return false;
  else if(_etabin == "09-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, "<", "additional ETA bin", 0  , kTElId) ) return false;
  else if(_etabin == "09+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 0.9, ">", "additional ETA bin", 0  , kTElId) ) return false;
  else if(_etabin == "12-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, "<", "additional ETA bin", 0  , kTElId) ) return false;
  else if(_etabin == "12+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.2, ">", "additional ETA bin", 0  , kTElId) ) return false;
  else if(_etabin == "15-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, "<", "additional ETA bin", 0  , kTElId) ) return false;
  else if(_etabin == "15+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", elIdx)), 1.5, ">", "additional ETA bin", 0  , kTElId) ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::tightMuonSelection(int muIdx){
  /*
    does the selection of tight muons
    parameters: muIdx
    return: true (if the muon is a tight muon), false (else)
  */

  counter("TightMuonDenominator", kTMuId);

  float pt  = _vc->get("LepGood_pt", muIdx);
  float cut = 10.;
  string ct = ">";
  float  up = 0;
  if(_lepptcut == "c10")
    pt = ptMIso2(muIdx);
 
  if(!makeCut<float>( pt                            , cut, ct , "pt selection" , up, kTMuId)) return false;
  if(!makeCut<float>( _vc->get("LepGood_eta", muIdx), 2.4, "<" , "eta selection", 0, kTMuId)) return false;

  //CH: two different IDs: cut-based and MVA-based
  bool lepid = false;

  if(_lepid == "mva") lepid = muonMvaId(muIdx, kTMuId);
  else                lepid = muonCutId(muIdx, kTMuId, 4.0, true);
  if(!makeCut( lepid, "lepton id", "=", kTMuId)) return false;

  // additional ETA selection
  if     (_etabin == "0"   && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, ">", "additional ETA bin", 1.2) ) return false;
  else if(_etabin == "12"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, ">", "additional ETA bin", 1.5) ) return false;
  else if(_etabin == "15"  && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, ">", "additional ETA bin", 2.4) ) return false;
  else if(_etabin == "09-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, "<", "additional ETA bin") ) return false;
  else if(_etabin == "09+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 0.9, ">", "additional ETA bin") ) return false;
  else if(_etabin == "12-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, "<", "additional ETA bin") ) return false;
  else if(_etabin == "12+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.2, ">", "additional ETA bin") ) return false;
  else if(_etabin == "15-" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, "<", "additional ETA bin") ) return false;
  else if(_etabin == "15+" && !makeCut<float>(std::abs(_vc->get("LepGood_eta", muIdx)), 1.5, ">", "additional ETA bin") ) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::vetoElectronSelection(int elIdx){
  /*
    does the selection of veto electrons
    parameters: elIdx
    return: true (if the electron is a veto electron), false (else)
  */

  counter("VetoElectronDenominator", kVElId);

  return true;

}


//____________________________________________________________________________
bool FRinSitu::vetoMuonSelection(int muIdx){
  /*
    does the selection of veto muons
    parameters: muIdx     
    return: true (if the muon is a veto muon), false (else)
  */

  counter("VetoMuonDenominator", kVMuId);

  return true;

}





/*****************************************************************************
******************************************************************************
** LEPTON IDs                                                               **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool FRinSitu::barrelEtaCut(Candidate * lep){

  // muons
  if(std::abs(lep->pdgId()) == 13){
    if(std::abs(lep->eta()) < 1.2) return true;
  }

  // electrons
  else {
	if(std::abs(lep->eta()) < 1.5) return true;
  }

  return false;

}


//____________________________________________________________________________
bool FRinSitu::electronCutId(int elIdx, int cat, float sip, bool tight, bool mvatight, bool sipdo){

  // CH: we do not extrapolate in ID, only sip and isolation 
  if(!makeCut(electronMvaCut(elIdx, mvatight)    , "electron MVA Id", "=", cat)) return false;
  if(!makeCut(isolationCut  (elIdx, tight   , 11), "isolation"      , "=", cat)) return false;

  string ct = "<";
  if(sipdo == false) ct = ">";
  if(!makeCut<float>(         _vc->get("LepGood_sip3d", elIdx) , sip , ct , "SIP 3D"       , 0, cat)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"   , elIdx)), 0.1 , "<", "dz selection" , 0, cat)) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::electronMvaCut(int elIdx, bool tight){

  float lepcut = 999.0;
  if(tight == true){
    if     (std::abs(_vc->get("LepGood_eta", elIdx)) < 0.8  ) lepcut =  0.73;
    else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 1.479) lepcut =  0.57;
    else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 2.5  ) lepcut =  0.05;
  }
  else {
    if     (std::abs(_vc->get("LepGood_eta", elIdx)) < 0.8  ) lepcut = -0.11;
    else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 1.479) lepcut = -0.35;
    else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 2.5  ) lepcut = -0.55;
    // CH: old denominator
    //if     (std::abs(_vc->get("LepGood_eta", elIdx)) < 0.8  ) lepcut =  0.35; 
    //else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 1.479) lepcut =  0.20; 
    //else if(std::abs(_vc->get("LepGood_eta", elIdx)) < 2.4  ) lepcut = -0.52;
  }

  if(_vc->get("LepGood_mvaIdPhys14", elIdx) < lepcut) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::electronMvaId(int elIdx, int cat){

  bool mvawp = false;
  if((_vc->get("LepGood_pt", elIdx) > 25 && _vc->get("LepGood_mvaSusy", elIdx) > 0   )
                                          || _vc->get("LepGood_mvaSusy", elIdx) > 0.53) mvawp = true;

  if(!makeCut( mvawp, "MVA WP", "=", cat)) return false;

  return true;

}


//____________________________________________________________________________
bool FRinSitu::isolationCut(int lepIdx, bool tight, int pdg){
  /*
    does the isolation cut in different quantities: pfRelIso, pTrel, miniiso
  */

  if     (_lepiso == "pTrel"){
    if(tight  && (_vc->get("LepGood_jetPtRel", lepIdx) > 14. || _vc->get("LepGood_relIso03", lepIdx) < 0.1)) return true;
    if(!tight && (_vc->get("LepGood_jetPtRel", lepIdx) > 5.  || _vc->get("LepGood_relIso03", lepIdx) < 0.4)) return true;
  }

  else if(_lepiso == "miniiso"){
    if(tight  && _vc->get("LepGood_miniRelIso", lepIdx) < 0.05) return true;
    if(!tight && _vc->get("LepGood_miniRelIso", lepIdx) < 0.4 ) return true;
  }

  else if(_lepiso == "mixiso" ){
    // muons: Gio's M workingpoint
    float miniiso = 0.14;
    float ptratio = 0.68;
    float ptrel   = 6.7;

    // electrons: Gio's T workingpoint
    if(std::abs(pdg) == 11){
      miniiso = 0.1;
      ptratio = 0.7;
      ptrel   = 7.0;
    }

    if(tight  && (_vc->get("LepGood_miniRelIso", lepIdx) < miniiso &&
                 (_vc->get("LepGood_jetPtRel"  , lepIdx) > ptrel || _vc->get("LepGood_jetPtRatio", lepIdx) > ptratio))) return true;
    if(!tight && _xpol == "isofo3" && (_vc->get("LepGood_miniRelIso", lepIdx) < miniiso &&
                 (_vc->get("LepGood_jetPtRel", lepIdx) > ptrel ||
                  _vc->get("LepGood_jetPtRatio", lepIdx) * ptMIso(lepIdx) / _vc->get("LepGood_pt", lepIdx) > ptratio))) return true; 
    if(!tight && _xpol == "isofo4" && (_vc->get("LepGood_miniRelIso", lepIdx) < 0.4 &&
                  (1. / _vc->get("LepGood_jetPtRatio", lepIdx) < 1. / ptratio + _vc->get("LepGood_miniRelIso", lepIdx) ||
                  _vc->get("LepGood_jetPtRel", lepIdx) > ptrel))) return true; 
    if(!tight && (_xpol != "isofo3" && _xpol != "isofo4") && 
                 _vc->get("LepGood_miniRelIso", lepIdx) < 0.4) return true;
  }

  else {
    if(tight  && _vc->get("LepGood_relIso03", lepIdx) < 0.1) return true;
    if(!tight && _vc->get("LepGood_relIso03", lepIdx) < 0.5) return true;
  }

  return false;

}

//____________________________________________________________________________
bool
FRinSitu::muonCutId(int muIdx, int cat, float sip, bool tight, bool sipdo){

  if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx), 0   , ">", "medium muon ID"   , 0  , cat)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx), 1   , ">", "CUT error/pt < 20", 0  , cat)) return false;
  if(!makeCut(isolationCut(muIdx, tight, 13)                                    , "isolation"        , "=", cat)) return false;
  string ct = "<";
  if(sipdo == false) ct = ">";
  if(!makeCut<float>(         _vc->get("LepGood_sip3d", muIdx)       , sip , ct , "SIP 3D"           , 0  , cat)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"   , muIdx))      , 0.1 , "<", "dz selection"     , 0  , cat)) return false;

  return true;

}


//____________________________________________________________________________
bool
FRinSitu::muonMvaId(int muIdx, int cat){

  bool mvawp = false;
  if((_vc->get("LepGood_pt", muIdx) > 25 && _vc->get("LepGood_mvaSusy", muIdx) > 0   )
                                          || _vc->get("LepGood_mvaSusy", muIdx) > 0.53) mvawp = true;

  if(!makeCut(mvawp, "MVA WP", "=", cat)) return false;
  if(!makeCut<int>(_vc->get("LepGood_mediumMuonId", muIdx), 0, ">", "MVA medium muon ID"  , 0, cat)) return false;
  if(!makeCut<int>(_vc->get("LepGood_tightCharge" , muIdx), 1, ">", "MVA error/pt < 20", 0, cat))    return false;

  return true;

}




/*****************************************************************************
******************************************************************************
** MATCHING FUNCTIONS                                                       **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
int FRinSitu::findHadrTau(){
  /*
    looks for Z->tautau, W->taunu decays in the gen particle collection of the event
    where all the taus decay hadronically
    parameters: none
    return: -1 (if no tau found), 
             0 (one or more taus found but at least one of them decays leptonically), 
             1 (hadr Z->tautau), 
             2 (hadr W+->tau+nu), 
             3 (hadr W-->tau-nu)
  */

  vector<int> ZIdx;
  vector<int> WIdx;
  vector<int> AntiWIdx;
  vector<int> TauIdx;
  vector<int> AntiTauIdx;
  vector<int> TauNuIdx;
  vector<int> AntiTauNuIdx;

  for(int i = 0; i < _vc->get("nGenPart"); ++i){
    if(_vc->get("GenPart_pdgId", i) ==  23) ZIdx        .push_back(i);
    if(_vc->get("GenPart_pdgId", i) ==  24) WIdx        .push_back(i);
    if(_vc->get("GenPart_pdgId", i) == -24) AntiWIdx    .push_back(i);
    if(_vc->get("GenPart_pdgId", i) ==  15) TauIdx      .push_back(i);
    if(_vc->get("GenPart_pdgId", i) == -15) AntiTauIdx  .push_back(i);
    if(_vc->get("GenPart_pdgId", i) ==  16) TauNuIdx    .push_back(i);
    if(_vc->get("GenPart_pdgId", i) == -16) AntiTauNuIdx.push_back(i);
  }

  if(TauIdx.size() == 0 && AntiTauIdx.size() == 0) return -1;

  for(int i = 0; i < TauIdx.size(); ++i)
    if(!noLeptonicDecay("GenPart", TauIdx[i]))
      return 0;

  for(int i = 0; i < AntiTauIdx.size(); ++i)
    if(!noLeptonicDecay("GenPart", AntiTauIdx[i]))
      return 0;

  if(ZIdx    .size() == TauIdx    .size() && ZIdx    .size() == AntiTauIdx  .size()) return 1;
  if(WIdx    .size() == AntiTauIdx.size() && WIdx    .size() == TauNuIdx    .size()) return 2;
  if(AntiWIdx.size() == TauIdx    .size() && AntiWIdx.size() == AntiTauNuIdx.size()) return 3;

  return -1;

}


//____________________________________________________________________________
bool FRinSitu::fromHadrTau(int lepIdx){
  /*
    looks if a lepton most-likely comes from a hadronic tau decay
    attention: this function assumes that every tau decays hadronically, make sure that it is so
  */

  if(findHadrTau() <= 0) return false;

  for(int i = 0; i < _vc->get("nGenPart"); ++i){
    int pdg = _vc->get("GenPart_pdgId", i);
    if(std::abs(pdg) == 15){
      float dr = KineUtils::dR(_vc->get("LepGood_eta", lepIdx), _vc->get("GenPart_eta", i),
                               _vc->get("LepGood_phi", lepIdx), _vc->get("GenPart_phi", i));
      if(dr < 0.3)
        return true;
    }
  }

  return false;

}


//____________________________________________________________________________
bool FRinSitu::heppyFake(int lepIdx){
  /*
    does the matching to the fake source flavor via heppy's mcMatchAny
  */

  if     (_fakes == "b"    ) return (_vc->get("LepGood_mcMatchAny", lepIdx) == 5);
  else if(_fakes == "c"    ) return (_vc->get("LepGood_mcMatchAny", lepIdx) == 4);
  else if(_fakes == "light") return (_vc->get("LepGood_mcMatchAny", lepIdx) <= 3);

  return true;

}


//____________________________________________________________________________
bool FRinSitu::noLeptonicDecay(string collection, int partIdx){
  /*
    looks in a collection if a particle decays into leptons or not in terms of dR
  */

  for(int i = 0; i < _vc->get("n" + collection); ++i){
    unsigned int pdg = std::abs(_vc->get(collection + "_pdgId", i));
    float dr = KineUtils::dR(_vc->get(collection + "_eta", partIdx), _vc->get(collection + "_eta", partIdx),
                             _vc->get(collection + "_phi", i      ), _vc->get(collection + "_phi", i      ));
    if(pdg >= 11 && pdg <= 14 && dr < 0.3)
      return false;
  }

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

  _btag = "nBJetMedium25";
  
  if(_MR == "sync") {
    setCut("HTSB"     ,   80, ">" );
    setCut("METSB"    , -100, ">" );
    setCut("HTCondSB" ,  500, "<" );
    setCut("METHighSB",   30, ">" );
    setCut("METLowSB" ,    0, ">" );
    setCut("NJetsSB"  ,    2, ">=");
    setCut("NBJetsSB" ,    0, ">=");
  }
  else if(_MR == "all") {
    setCut("HTSB"     ,   80, ">" );
    setCut("METSB"    , -100, ">" );
    setCut("HTCondSB" ,  500, "<" );
    setCut("METHighSB",   30, ">" );
    setCut("METLowSB" , -100, ">" );
    setCut("NJetsSB"  ,    2, ">=");
    setCut("NBJetsSB" ,    0, ">=");
  }
  else if(_MR == "SB00") {
    setCut("HTSB"     ,   80, ">" );
    setCut("METSB"    , -100, ">" );
    setCut("HTCondSB" ,  500, "<" );
    setCut("METHighSB",   30, ">" );
    setCut("METLowSB" , -100, ">" );
    setCut("NJetsSB"  ,    2, ">=");
    setCut("NBJetsSB" ,    0, "=" );
  }
  
  else if(_MR == "SB10") {
    setCut("HTSB"     ,   80, ">" );
    setCut("METSB"    , -100, ">" );
    setCut("HTCondSB" ,  500, "<" );
    setCut("METHighSB",   30, ">" );
    setCut("METLowSB" , -100, ">" );
    setCut("NJetsSB"  ,    2, ">=");
    setCut("NBJetsSB" ,    1, "=" );
  }
  
  else if(_MR == "SB20") {
    setCut("HTSB"     ,   80, ">" );
    setCut("METSB"    , -100, ">" );
    setCut("HTCondSB" ,  500, "<" );
    setCut("METHighSB",   30, ">" );
    setCut("METLowSB" , -100, ">" );
    setCut("NJetsSB"  ,    2, ">=");
    setCut("NBJetsSB" ,    2, "=" );
  }
  else if(_MR == "SB30") {
    setCut("HTSB"     ,   80, ">" );
    setCut("METSB"    , -100, ">" );
    setCut("HTCondSB" ,  500, "<" );
    setCut("METHighSB",   30, ">" );
    setCut("METLowSB" , -100, ">" );
    setCut("NJetsSB"  ,    2, ">=");
    setCut("NBJetsSB" ,    3, ">=");
  }

  // CH: SUS-13-013 cuts
  else if(_MR == "SB01") {
    setCut("HTSB"     ,  200, "[]", 400);
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    0, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB02") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    0, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB03") {
    setCut("HTSB"     ,  200, "[]", 400 );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    0, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB04") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    0, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB05") {
    setCut("HTSB"     ,  200, "[]", 400);
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    0, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB06") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    0, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB07") {
    setCut("HTSB"     ,  200, "[]", 400 );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    0, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB08") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    0, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
 

  else if(_MR == "SB11") {
    setCut("HTSB"     ,  200, "[]", 400);
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    1, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB12") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    1, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB13") {
    setCut("HTSB"     ,  200, "[]", 400 );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    1, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB14") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    1, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB15") {
    setCut("HTSB"     ,  200, "[]", 400);
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    1, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB16") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    1, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB17") {
    setCut("HTSB"     ,  200, "[]", 400 );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    1, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB18") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    1, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
 

  else if(_MR == "SB21") {
    setCut("HTSB"     ,  200, "[]", 400);
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    2, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB22") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    2, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB23") {
    setCut("HTSB"     ,  200, "[]", 400 );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    2, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB24") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,   50, "[]", 120);
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    2, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB25") {
    setCut("HTSB"     ,  200, "[]", 400);
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    2, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB26") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    2, "[]",   3);
    setCut("NBJetsSB" ,    2, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB27") {
    setCut("HTSB"     ,  200, "[]", 400 );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    2, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }
  else if(_MR == "SB28") {
    setCut("HTSB"     ,  400, ">" );
    setCut("METSB"    ,  120, ">" );
    setCut("NJetsSB"  ,    4, ">=");
    setCut("NBJetsSB" ,    2, "=" );
    setCut("HTCondSB" ,    0, "<" );
    setCut("METHighSB", -100, ">" );
    setCut("METLowSB" , -100, ">" );
  }

 


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
  if(_isData && !makeCut<int>(_vc->get("HLT_DoubleMu"), 1, "=", "HLT DoubleMu") ) return false;	
  if(_isData && !makeCut<int>(_vc->get("HLT_DoubleEl"), 1, "=", "HLT DoubleEl") ) return false;	
  if(_isData && !makeCut<int>(_vc->get("HLT_MuEG")    , 1, "=", "HLT MuEG"    ) ) return false;	

  // only one FO!
  if(!makeCut(_nTLeps == 1 && _nLLeps == 1, "one tight, one loose lepton", "=") ) return false;

  // selecting best same-sign pair 
  bool is_ss_event = ssEventSelection();
  if(!makeCut( is_ss_event , "same-sign selection", "=") ) return false;

  // veto on third lepton using all selected leptons
  if(!makeCut( mllVetoSelection(), "mll vetos", "=") ) return false;


  return true;

}


//____________________________________________________________________________
bool FRinSitu::genSelection(){
  /*
	does the gen matching
  */

  if(_fakes == "none") return true;

  int id1  = _vc->get("LepGood_mcMatchId" , _lep_idx1); 
  int id2  = _vc->get("LepGood_mcMatchId" , _lep_idx2); 
  int any1 = _vc->get("LepGood_mcMatchAny", _lep_idx1); 
  int any2 = _vc->get("LepGood_mcMatchAny", _lep_idx2); 
//cout << "searching for a fake" << endl;
  if(_sampleName.find("fake") != (size_t) -1){
    if(id1 == 0 && id2 == 0) return false;
    if(id1 != 0 && id2 != 0) return false;
  }

//cout << "only one is fake and it is: ";
  int fany = any1;
  int fidx = _lep_idx1;
  if(id2 == 0) {
    fany = any2;
    fidx = _lep_idx2;
  }

//cout << id1 << "." << id2 << endl;

  bool fromTau = fromHadrTau(fidx);
  bool source  = heppyFake(fidx);

//if(_vc->get("run") == 1 && _vc->get("lumi") == 460037 && _vc->get("evt") == 45665427){ 
//cout << fany << ":" << source << ":" << fromTau << endl;
//DUMPVECTOR(_lntLepIdx);
//DUMPVECTOR(_tLepIdx);
//}

  if     (fromTau  ) counter("fakes from tau");
  else if(fany == 5) counter("fakes from b");
  else if(fany == 4) counter("fakes from c");
  else if(fany <= 3) counter("fakes from light");

  if     (fromTau  ) {
    if(std::abs(_vc->get("LepGood_pdgId", fidx)) == 13) counter("muon fakes from tau");
    else counter("electron fakes from tau");
  }
  else if(fany == 5) {
    if(std::abs(_vc->get("LepGood_pdgId", fidx)) == 13) counter("muon fakes from b");
    else counter("electron fakes from b");
  }
  else if(fany == 4) {
    if(std::abs(_vc->get("LepGood_pdgId", fidx)) == 13) counter("muon fakes from c");
    else counter("electron fakes from c");
  }
  else if(fany <= 3) {
    if(std::abs(_vc->get("LepGood_pdgId", fidx)) == 13) counter("muon fakes from light");
    else counter("electron fakes from light");
  }

  if(_fakes == "tau")
    source = fromTau;
  if(_fakes != "all" && _fakes != "tau" && source)
    source = !fromTau;

  return source;

}


//____________________________________________________________________________
bool FRinSitu::skimSelection(){


  // lepton multiplicity
  if(!makeCut<int>( _nLLeps, 2, ">=", "loose lepton multiplicity and flavor" ) ) return false; 
  if(!makeCut<int>( _nJets , 2, ">=", "jet multiplicity"                     ) ) return false;

  return true;

}

//____________________________________________________________________________
bool FRinSitu::mrSelection(){


  if(!makeCut<float>( _HT       , _valCutHTSB    , _cTypeHTSB  , "SB HT selection" , _upValCutHTSB      ) ) return false;
  if(!makeCut<float>( _met->pt(), _valCutMETSB   , _cTypeMETSB , "SB MET selection", _upValCutMETSB      ) ) return false;

  if(_au->simpleCut( _HT, _valCutHTCondSB, _cTypeHTCondSB) ) {
    if(!makeCut<float>( _met->pt(), _valCutMETHighSB, _cTypeMETHighSB, "SB MET (HT<500) selection", _upValCutMETHighSB ) ) return false;
  }
  else {
    if(!makeCut<float>( _met->pt(), _valCutMETLowSB , _cTypeMETLowSB , "SB MET (HT>500) selection" , _upValCutMETLowSB ) ) return false;
  }

  if(!makeCut<int>( _nJets         , _valCutNJetsSB , _cTypeNJetsSB , "SB jet multiplicity"  , _upValCutNJetsSB ) ) return false;
  if(!makeCut<int>(_vc->get(_btag), _valCutNBJetsSB, _cTypeNBJetsSB, "SB b-jet multiplicity", _upValCutNBJetsSB) ) return false;


  return true;

} 



//____________________________________________________________________________
bool FRinSitu::ssEventSelection(){
  /*
    checks, if the leptons that have been found in the kinematic region are same-sign
    parameters: none
    return: true (if the leptons all have same-sign), false (else)
  */

  // SF: CHOOSE a SS PAIR, maximizing the number of muons and then pT
  // CH: one tight and one loose lepton should make the pair, the loose is the fake, the tight is the prompt
  int charge = 0;
  int flavor = 0;
  int flavortmp = 0;
  bool isSS = false;
  for(unsigned int il1 = 0; il1 < _tLeps.size(); ++il1){
    for(unsigned int il2 = 0; il2 < _lLeps.size(); ++il2){
      charge    = _tLeps[il1]->charge() * _lLeps[il2]->charge();
      flavortmp = std::abs(_tLeps[il1]->pdgId()) + std::abs( _lLeps[il2]->pdgId());
   
      float mll = 0;
      mll = Candidate::create(_tLeps[il1], _lLeps[il2]) -> mass();

      if (mll < 8) continue; // low mass veto

      if (charge < 0)         continue; // if the pair is OS skip

      if (flavor > flavortmp) continue; // if the new pair has less muons skip.

      // lepton pt: high-high, high-low, low-low selection
      // CH: for the sync exercise we do not care about pT categories, gen match categories or whatnot
      //if (_leppt == "hh" && _lLeps[il1]->pt() < 25.) continue;
      //if (_leppt == "hh" && _lLeps[il2]->pt() < 25.) continue;
      //
      //if (_leppt == "hl" && _lLeps[il1]->pt() < 25.) continue;
      //if (_leppt == "hl" && _lLeps[il2]->pt() > 25.) continue;

      //if (_leppt == "ll" && _lLeps[il1]->pt() > 25.) continue;
      //if (_leppt == "ll" && _lLeps[il2]->pt() > 25.) continue;
   
 
      // the loose one is the fake, the tight one the prompt
      if(_vc->get("LepGood_mcMatchId", _tLepIdx[il1]) == 0 || _vc->get("LepGood_mcMatchId", _lLepIdx[il2]) != 0) continue;

      // lepton eta: barrel-barrel, barrel-endcap, endcap-endcap selection
      if (_etabin == "bb" &&  (!barrelEtaCut(_lLeps[il1]) || !barrelEtaCut(_lLeps[il2]))) continue; 
      if (_etabin == "be" && (( barrelEtaCut(_lLeps[il1]) &&  barrelEtaCut(_lLeps[il2])) ||
                              (!barrelEtaCut(_lLeps[il1]) && !barrelEtaCut(_lLeps[il2])))) continue; 
      if (_etabin == "ee" &&  ( barrelEtaCut(_lLeps[il1]) &&  barrelEtaCut(_lLeps[il2])))  continue; 

      // save this pair
      flavor = flavortmp;
      _first  = _tLeps[il1];   _lep_idx1 = il1;
      _second = _lLeps[il2];   _lep_idx2 = il2; 
      _promptId = _tLepIdx[il1];
      _fakeId   = _lLepIdx[il2];
      isSS = true;
    }
  }


  // any other (also tight) lepton is pushed into the veto
  for(unsigned int il = 0; il < _tLeps.size(); ++il){
    if(_tLepIdx[il] != _promptId)
      _vLeps.push_back(_tLeps[il]);
  }
  for(unsigned int il = 0; il < _lLeps.size(); ++il){
    if(_lLepIdx[il] != _fakeId)
      _vLeps.push_back(_lLeps[il]);
  }

  
  if      (_lepflav=="mm"  && flavor==26 && isSS) return true;
  else if (_lepflav=="em"  && flavor==24 && isSS) return true;
  else if (_lepflav=="ee"  && flavor==22 && isSS) return true;
  else if (_lepflav=="all" && isSS)               return true;

  return false;
}


//____________________________________________________________________________
bool FRinSitu::mllVetoSelection(){
  /*
	does the three mll vetos for all selected leptons
  */

  if(mllZVeto  (_first, _second)) return false;
  if(mllLMGVeto(_first, _second)) return false;

  for(unsigned int i = 0; i < _vLeps.size(); ++i){
    if(mllZVeto  (_first , _vLeps[i])) return false;
    //if(mllZVeto  (_second, _vLeps[i])) return false;
    if(mllLMGVeto(_first , _vLeps[i])) return false;
    //if(mllLMGVeto(_second, _vLeps[i])) return false;
  }

  return true;

}


//____________________________________________________________________________
bool FRinSitu::mllLMGVeto(Candidate * cand, Candidate * veto){
  /*
	return true if the invariant mass of the two particles is not good and
	the event needs to be rejected
  */

  // veto lepton pt
  if((std::abs(veto->pdgId()) == 11 && veto->pt() < 7) || (std::abs(veto->pdgId()) == 13 && veto->pt() < 5)) return false;

  float mll = 0;
  mll = Candidate::create(cand, veto) -> mass();

  // any sign -> low-mass veto
  //if(mll <= 8.0) return true;

  // opposite sign, same flavor
  if(_au -> simpleCut(cand->charge(), veto->charge(), "=") || 
     _au -> simpleCut(std::abs(cand->pdgId()), std::abs(veto->pdgId()), "!=")) return false;

  // opposite sign, same flavor -> gamma star veto
  if(mll <= 12.0) return true;

  return false;

}


//____________________________________________________________________________
bool FRinSitu::mllZVeto(Candidate * cand, Candidate * veto){
  /*
	return true if the invariant mass of the two particles is not good and
	the event needs to be rejected
  */

  // this stuff gives seg fault
  //counter("ZVetoLepSel", kZVetoLepSel);

  // veto lepton pt
  if(cand->pt() < 10 || veto->pt() < 10) return false;

  // opposite sign, same flavor
  if(_au -> simpleCut(cand->charge(), veto->charge(), "=") || 
     _au -> simpleCut(std::abs(cand->pdgId()), std::abs(veto->pdgId()), "!=")) return false;

  float mll = 0;
  mll = Candidate::create(cand, veto) -> mass();

  // Z veto
  if(mll >= 76.0 && mll <= 106.0) return true;

  return false;

}



//____________________________________________________________________________
bool FRinSitu::vetoEventSelection(){
  /*
    performs an essential part of the event selection in the 3l case, i.e.
    events are rejected if there are 3 leptons where two leptons form an
    opposite-sign same-flavor pair with some condition on mll and pt
    parameters: electron_label, muon_label (the labels of the selected electron and muon objects)
    return: true (if the event has such a pair, i.e. if the event shall be rejected), false (else)
  */

  counter("denominator", kVetoLepSel);

  for(unsigned int i = 0; i < _vLeps.size(); ++i){

    // search for OS pair with high-pt lepton
    if (_first->charge() == _vLeps[i] -> charge()) continue;

    float mll = 0;
    mll = Candidate::create(_vLeps[i], _first) -> mass();
    //fill("test_vetoMll"        , mll                  , _weight);

    // same flavor -> Z veto
    if(_au->simpleCut( fabs(_vLeps[i] -> pdgId()), fabs(_first -> pdgId()), "=") ) {
      if(makeCut(mll > 76.0 && mll < 106.0, "Z veto selection", "=", kVetoLepSel) ) return true;
    }

    // any flavor -> gamma star veto
    if(makeCut(mll < 12.0, "gamma star veto selection", "=", kVetoLepSel) ) return true;

    mll = Candidate::create(_vLeps[i], _second) -> mass(); 
    //fill("test_vetoMll"        , mll                  , _weight);
 
    // same flavor -> Z veto 
    if(_au->simpleCut( fabs(_vLeps[i] -> pdgId()), fabs(_second -> pdgId()), "=") ) {   
      if(makeCut(mll > 76.0 && mll < 106.0, "Z veto selection", "=", kVetoLepSel) ) return true; 
    } 
 
    // any flavor -> gamma star veto 
    if(makeCut(mll < 12.0, "gamma star veto selection", "=", kVetoLepSel) ) return true; 
 
  } 
 
  makeCut(true, "no veto event", "=", kVetoLepSel); 

  return false;

}





/*****************************************************************************
******************************************************************************
** EXECUTING TASKS                                                          **
******************************************************************************
*****************************************************************************/



//____________________________________________________________________________
void FRinSitu::fillEventPlots(std::string kr){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  fill(kr + "_HT"           , _HT                  , _weight);
  fill(kr + "_MET"          , _met->pt()           , _weight);
  fill(kr + "_NBJets"       , _vc->get(_btag)     , _weight);
  fill(kr + "_NJets"        , _nJets               , _weight);
  fill(kr + "_NLEls"        , _nLEls               , _weight);
  fill(kr + "_NLLeps"       , _nLLeps              , _weight);
  fill(kr + "_NLMus"        , _nLMus               , _weight);
  fill(kr + "_NLNTEls"      , _nLNTEls             , _weight);
  fill(kr + "_NLNTLeps"     , _nLNTLeps            , _weight);
  fill(kr + "_NLNTMus"      , _nLNTMus             , _weight);
  fill(kr + "_NTEls"        , _nTEls               , _weight);
  fill(kr + "_NTLeps"       , _nTLeps              , _weight);
  fill(kr + "_NTMus"        , _nTMus               , _weight);
  fill(kr + "_NVEls"        , _nVEls               , _weight);
  fill(kr + "_NVLeps"       , _nVLeps              , _weight);
  fill(kr + "_NVMus"        , _nVMus               , _weight);
  fill(kr + "_NVrtx"        , _vc->get("nVert")   , _weight);

  //Candidate* Z = nullptr;
  //Z = Candidate::create( _first, _second);
  //fill(kr + "_MLL"          , Z->mass()            , _weight);

}


//____________________________________________________________________________
void FRinSitu::fillFRMaps(string prepend, int lepIdx){

  fill(prepend + "SyncMapPt"     , overflowPt(_vc->get("LepGood_pt", lepIdx)), std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "SyncMapPtJet"  , overflowPt(closestJetPt(lepIdx))          , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "SyncMapPtMIso" , overflowPt(ptMIso(lepIdx))                , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
  fill(prepend + "SyncMapPtMIso2", overflowPt(ptMIso2(lepIdx))               , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);

}


//____________________________________________________________________________
void FRinSitu::fillFakeRatioMaps(std::string kr){
  /*
    fills the fake ratio maps for leptons
    parameters: none
    return: none
  */

  int pdg = std::abs(_vc->get("LepGood_pdgId", _fakeId));
  string prepend = "El";
  if(pdg==13) prepend = "Mu";

  int indx = find(_lLepIdx.begin(), _lLepIdx.end(), _fakeId) - _lLepIdx.begin();

  // denominator
  fillFRMaps("MR_L" + prepend, _fakeId);
  fillLepPlots("MR_L" + prepend, _lLeps[indx], _fakeId);

  // numerator
  if(isolationCut(_fakeId, true, pdg)){
//cout << "filling numerator for " << _vc->get("LepGood_pt", _fakeId) << " and " << _vc->get("LepGood_eta", _fakeId) << endl;
    fillFRMaps("MR_T" + prepend, _fakeId);
    fillFRMaps("MR_R" + prepend, _fakeId);
    fillLepPlots("MR_T" + prepend, _lLeps[indx], _fakeId);
    fillLepPlots("MR_R" + prepend, _lLeps[indx], _fakeId);
  }



  //for(int i = 0; i < _lEls  .size(); ++i) { fillFRMaps(kr + "_LEl"  , _lEls[i]  , _lElIdx[i]  ); }
  //for(int i = 0; i < _lntEls.size(); ++i) { fillFRMaps(kr + "_LNTEl", _lntEls[i], _lntElIdx[i]); }
  //for(int i = 0; i < _tEls  .size(); ++i) { fillFRMaps(kr + "_TEl"  , _tEls[i]  , _tElIdx[i]  );
  //                                          fillFRMaps(kr + "_REl"  , _tEls[i]  , _tElIdx[i]  ); }
  //for(int i = 0; i < _lMus  .size(); ++i) { fillFRMaps(kr + "_LMu"  , _lMus[i]  , _lMuIdx[i]  ); }
  //for(int i = 0; i < _lntMus.size(); ++i) { fillFRMaps(kr + "_LNTMu", _lntMus[i], _lntMuIdx[i]); }
  //for(int i = 0; i < _tMus  .size(); ++i) { fillFRMaps(kr + "_TMu"  , _tMus[i]  , _tMuIdx[i]  );
  //                                          fillFRMaps(kr + "_RMu"  , _tMus[i]  , _tMuIdx[i]  ); }

}



 
//____________________________________________________________________________ 
void FRinSitu::fillLepPlots(string prepend, Candidate * lep, int lepIdx){ 
  /* 
    fills the control plots for leptons PER LEPTON 
  */   

  fill(prepend + "DXY"  , fabs(_vc->get("LepGood_dxy"     , lepIdx)) , _weight); 
  fill(prepend + "DZ"   , fabs(_vc->get("LepGood_dz"      , lepIdx)) , _weight); 
  fill(prepend + "IP"   , fabs(_vc->get("LepGood_ip3d"    , lepIdx)) , _weight); 
  fill(prepend + "SIP"  ,      _vc->get("LepGood_sip3d"   , lepIdx)  , _weight); 
  fill(prepend + "Eta"  , fabs(_vc->get("LepGood_eta"     , lepIdx)) , _weight); 
  fill(prepend + "Iso"  ,      _vc->get("LepGood_relIso03", lepIdx)  , _weight); 
  fill(prepend + "Pt"   ,      _vc->get("LepGood_pt"      , lepIdx)  , _weight); 
  fill(prepend + "PtRel",      _vc->get("LepGood_jetPtRel", lepIdx)  , _weight); 
  fill(prepend + "PtJet", closestJetPt(lepIdx)                        , _weight); 
  fill(prepend + "MT"   , Candidate::create( lep, _met) -> mass()     , _weight); 
 
} 


//____________________________________________________________________________
void FRinSitu::fillLeptonPlots(std::string kr){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  //for(int i = 0; i < _lEls   .size(); ++i) fillLepPlots(kr + "_LEl"   , _lEls   [i], i); 
  //for(int i = 0; i < _lntEls .size(); ++i) fillLepPlots(kr + "_LNTEl" , _lntEls [i], i); 
  //for(int i = 0; i < _tEls   .size(); ++i) fillLepPlots(kr + "_TEl"   , _tEls   [i], i); 
  //for(int i = 0; i < _lLeps  .size(); ++i) fillLepPlots(kr + "_LLep"  , _lLeps  [i], i); 
  //for(int i = 0; i < _lntLeps.size(); ++i) fillLepPlots(kr + "_LNTLep", _lntLeps[i], i); 
  //for(int i = 0; i < _tLeps  .size(); ++i) fillLepPlots(kr + "_TLep"  , _tLeps  [i], i); 
  //for(int i = 0; i < _lMus   .size(); ++i) fillLepPlots(kr + "_LMu"   , _lMus   [i], i); 
  //for(int i = 0; i < _lntMus .size(); ++i) fillLepPlots(kr + "_LNTMu" , _lntMus [i], i); 
  //for(int i = 0; i < _tMus   .size(); ++i) fillLepPlots(kr + "_TMu"   , _tMus   [i], i);

}


//____________________________________________________________________________
float 
FRinSitu::HT(){
  /*
    computes HT for a given list of selected jets
    parameters: jet_label
    return: HT
  */

  float ht = 0;

  for(int i = 0; i < _nJets; ++i) 
    ht += _jets[i]->pt();

  return ht;

}


//____________________________________________________________________________
float FRinSitu::ptMIso(int lepIdx){

  //CH: this is pure miniIso corrected pt

  double min = 0.;
  float miniiso = 0.14;
  if(std::abs(_vc->get("LepGood_pdgId", lepIdx)) == 11) miniiso = 0.1;

  return _vc->get("LepGood_pt", lepIdx) * (1.0 + std::max(min, _vc->get("LepGood_miniRelIso", lepIdx) - miniiso));

}


//____________________________________________________________________________
float FRinSitu::ptMIso2(int lepIdx){

  //CH: Giuseppe's cone correction see RA5 meeting 15th April

  double min = 0.;

  float miniiso = 0.14;
  float ptratio = 0.68;
  float ptrel = 6.7;
  if(std::abs(_vc->get("LepGood_pdgId", lepIdx)) == 11) {
    miniiso = 0.1;
    ptratio = 0.7;
    ptrel = 7.0;
  }

  bool miso = false;
  if(_vc->get("LepGood_jetPtRel", lepIdx) > ptrel)
    miso = true;

  if(!miso)
    return std::max(_vc->get("LepGood_pt", lepIdx), (double) closestJetPt(lepIdx) * ptratio);

  return _vc->get("LepGood_pt", lepIdx) * (1.0 + std::max(min, _vc->get("LepGood_miniRelIso", lepIdx) - miniiso));

}



//____________________________________________________________________________
float FRinSitu::closestJetPt(int lepIdx){

  return _vc->get("LepGood_pt", lepIdx) / _vc->get("LepGood_jetPtRatio", lepIdx);

}


//____________________________________________________________________________
float FRinSitu::overflowPt(float rawPt){

    if(rawPt >= 70.) return 60.;

    return rawPt;
}


//____________________________________________________________________________
int FRinSitu::eventCharge(){
  /*
    returns the total charge in the event as calculated from the electrons and
    leptons that have been selected
    parameters: electron_label, muon_label
    return: the total charge as int
  */

  int charge = 0;
  charge += _first->charge();
  charge += _second->charge();

  return charge; 

}

