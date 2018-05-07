#include "analysis/src/FakeRatioV3.hh"

#include <algorithm>

FakeRatioV3::FakeRatioV3(std::string cfg){
  
  //startExecution(cfg);
  initialize();
  if(_dumpEvent)
    _ofileDump=new ofstream("/mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/eventDumpFRV3.txt", ios::out | ios::trunc );
}

FakeRatioV3::~FakeRatioV3(){
  if(_dumpEvent)
    _ofileDump->close();
}


void
FakeRatioV3::initialize() {

  initTriggerLines();
  initVariables();
      
  //SusyModule
  _susyMod = new SusyModule(_vc, _dbm);

  _dbm->loadDb("XS", "XSectionsSpring16.db");  
  _dbm->loadDb("KF", "kFactorsSpring16.db" );  

  //input Variables
  //_norm  = getCfgVarS("NORMALIZATION", "lumi"); // data, lumi
  _lepId = getCfgVarS("LEPID"       , "RA5" ); // all, el, mu
  _dumpEvent = (bool)getCfgVarI("dump", 0);
  _storeTrees = (bool)getCfgVarI("storeTree", 0);
  _susyMod->configureLeptonId( SusyModule::kCB );

  _controlPlots=false;
  _projPlots=false;
  
  string plotVar=getCfgVarS("SAVEPLOTS","");
  vector<string> plots=Tools::split(plotVar,':');
  for(unsigned int is=0;is<plots.size();is++) {
    if(plots[is]=="control") _controlPlots=true;
    if(plots[is]=="proj") _projPlots=true;
  }

  _flavors=vector<string>({"el","mu"});

  // _targetLumi = 1;
  // if(_norm=="lumi") _targetLumi = getCfgVarF("targetLumi" , 1.0);
}


void
FakeRatioV3::modifyWeight() {

  if(!_vc->get("isData")) {
    float vtxWeight = _susyMod->getPuWeight(_vc->get("nVert"));

    string sname = _sampleName;
    // if(sname.find("ewk") != std::string::npos) sname=sname.erase(sname.find("ewk"), 3); 
    // if(sname.find("qcd") != std::string::npos) sname=sname.erase(sname.find("qcd"), 3); 

    _weight *= vtxWeight*_vc->get("genWeight");

    double nProc=getCurrentDS()->getSumProcWgts(); 
    if(nProc==-1) nProc=getCurrentDS()->getNProcEvents();

    double w=_dbm->getDBValue("XS", sname) * _dbm->getDBValue("KF", sname)/nProc * 1;
    //w*=_targetLumi;

    if(_ie==0) {
      cout<<_sampleName<<" : "<<_dbm->getDBValue("XS", sname)<<"  "<<_dbm->getDBValue("KF", sname)<<"   "<<nProc<<"  -->  "<<w<<endl;
    }
    _weight *=w;
    _isData=false;
  }

}

void
FakeRatioV3::modifySkimming() {
  addSkimBranch<float>("mT",&_mt);
  addSkimBranch<float>("w",&_weight);
  addSkimBranch<float>("pt",&_lepPt);
  addSkimBranch<float>("eta",&_lepEta);
  addSkimBranch<float>("phi",&_lepPhi);
  addSkimBranch<int>("pdgId",&_lepPdgId);
  addSkimBranch<bool>("iso",&_lepIso);
  addSkimBranch<float>("activity",&_lepAct);
  addSkimBranch<float>("btag",&_lepBTag);
}

void
FakeRatioV3::defineOutput() {

  vector<string> types({"EwkNorm_ECOP","EwkNorm_UCSX",
	"QCDNorm_ECOP", "MR_ECOP","MR_UCSX"});
  
  _hm->addVariable("MZelJet",   200,  0.0,  200.0, "m_{ll} [GeV]");
  for(size_t il=0;il<kNFlavs;il++) {
    for(size_t ii=0;ii<kCats;ii++) {
      for(_itHlt=_hltLines[ii].begin();_itHlt!=_hltLines[ii].end();_itHlt++) {
	string trigger=_itHlt->first;
	if( (il==kEl && trigger.substr(1,2)=="Mu") || 
	    (il==kMu && trigger.substr(1,2)=="El") ) continue;
	_hm->addVariable("MZ_Den_"+trigger,   200,  0.0,  200.0, "m_{ll} [GeV]");
	_hm->addVariable("MZ_Num_"+trigger,   200,  0.0,  200.0, "m_{ll} [GeV]");
      }
    }
  }

  for(size_t it=0;it<types.size();it++) {
    for(size_t il=0;il<kNFlavs;il++) {
      for(size_t ii=0;ii<kCats;ii++) {
	for(_itHlt=_hltLines[ii].begin();_itHlt!=_hltLines[ii].end();_itHlt++) {
	  string trigger=_itHlt->first;
	  if( (il==kEl && trigger.substr(1,2)=="Mu") || 
	      (il==kMu && trigger.substr(1,2)=="El") ) continue;
	  //for(size_t ih=0;ih<_triggers[il].size();ih++) {
	
	  string post="_"+types[it]+"_"+trigger; //"_"+_flavors[il]+
	  if(_controlPlots) {
	    _hm->addVariable("HT"+post     , 1000,  0.0, 1000.0, "H_{T} [GeV]"); 
	    _hm->addVariable("MET"+post    , 1000,  0.0, 1000.0, "#slash{E}_{T} [GeV]");
	    _hm->addVariable("DXY_Den"+post    , 5000,  0.0,   10.0, "#||{dxy}(lep) [cm]");
	    _hm->addVariable("DZ_Den"+post     , 5000,  0.0,   10.0, "#||{dz}(lep) [cm]");
	    _hm->addVariable("SIP_Den"+post    , 1000,  0.0,   10.0, "SIP3d(lep)");
	    _hm->addVariable("MiniIso_Den"+post,   50,  0.0,    1.0, "PF MiniIso (lep)");
	    _hm->addVariable("DXY_Num"+post    , 5000,  0.0,   10.0, "#||{dxy}(lep) [cm]");
	    _hm->addVariable("DZ_Num"+post     , 5000,  0.0,   10.0, "#||{dz}(lep) [cm]");
	    _hm->addVariable("SIP_Num"+post    , 1000,  0.0,   10.0, "SIP3d(lep)");
	    _hm->addVariable("MiniIso_Num"+post,   50,  0.0,    1.0, "PF MiniIso (lep)");
	  }
	  if(_projPlots) {
	    _hm->addVariable("Eta_Den"+post    ,  250,  0.0,    2.5, "#||{#eta(lep)}");
	    _hm->addVariable("Pt_Den"+post     , 1000,  0.0, 1000.0, "p_{T}(lep) [GeV]");
	    _hm->addVariable("PtCorr_Den"+post , 1000,  0.0, 1000.0, "p_{T}(lep) [GeV]");
	    _hm->addVariable("Eta_Num"+post    ,  250,  0.0,    2.5, "#||{#eta(lep)}");
	    _hm->addVariable("Pt_Num"+post     , 1000,  0.0, 1000.0, "p_{T}(lep) [GeV]");
	    _hm->addVariable("PtCorr_Num"+post , 1000,  0.0, 1000.0, "p_{T}(lep) [GeV]");

	  }
	  //cout<<" -->> "<<post<<endl;
	  _hm->addVariable("MT_Den"+post,   40,  0.0,  200.0, "M_{T} [GeV]");
	  _hm->addVariable("MapPt_Den"+post, _frPtBins[il].size()-1, _frPtBins[il] ,
			   _frEtaBins[il].size()-1, _frEtaBins[il],
			   "p_{T}("+_flavors[il]+") [GeV]",
			   "#||{#eta}("+_flavors[il]+")"  );
	  _hm->addVariable("MapPtCorr_Den"+post, _frPtBins[il].size()-1, _frPtBins[il] ,
			   _frEtaBins[il].size()-1, _frEtaBins[il],
			   "p_{T}^{corr}("+_flavors[il]+") [GeV]",
			   "#||{#eta}("+_flavors[il]+")"  ); 
	  _hm->addVariable("MT_Num"+post,   40,  0.0,  200.0, "M_{T} [GeV]");
	  _hm->addVariable("MapPt_Num"+post, _frPtBins[il].size()-1, _frPtBins[il] ,
			   _frEtaBins[il].size()-1, _frEtaBins[il],
			   "p_{T}("+_flavors[il]+") [GeV]",
			   "#||{#eta}("+_flavors[il]+")"  );
	  _hm->addVariable("MapPtCorr_Num"+post, _frPtBins[il].size()-1, _frPtBins[il] ,
			   _frEtaBins[il].size()-1, _frEtaBins[il],
			   "p_{T}^{corr}("+_flavors[il]+") [GeV]",
			   "#||{#eta}("+_flavors[il]+")"  ); 
	}//triggers
      } //categs
    }//flavors
  }//types
	
}

void
FakeRatioV3::writeOutput() {

}


void
FakeRatioV3::reset() {

  _extsHLT.clear();
  
  _looseLeps.clear();
  _denLeps.clear();
  _numLeps.clear();
  _looseLepsIdx.clear();
  _denLepsIdx.clear();
  _numLepsIdx.clear();
  
  _bJets.clear();
  _goodJets.clear();
  _lepJets.clear();

  _bJetsIdx.clear();
  _goodJetsIdx.clear();
  _lepJetsIdx.clear();

  _nDenEls=0;
  _nDenMus=0;

}


void
FakeRatioV3::run() {

  counter("denominator");
  reset();
  
  selectObjects();

  if(_nDenLeps==0) return;
  _mt=KineUtils::M_T(_denLeps[0]->pt(), _met->pt(), _denLeps[0]->phi(), _met->phi());
 
  
  ZSelection();

  if(!baseSelection()) return;

  if(_skim) {
    //cout<<" storage "<<endl;
    _lepPt  = _denLeps[0]->pt();
    _lepEta = _denLeps[0]->eta();
    _lepPhi = _denLeps[0]->phi();
    _lepPdgId = _denLeps[0]->pdgId();
    _lepIso = (bool)_numLeps.size();
    _lepAct = _vc->get("LepGood_relIsoAnM",_denLepsIdx[0]);
    _lepBTag= _vc->get("LepGood_jetBTagCSV",_denLepsIdx[0]);
    fillSkimTree();
    return;
  }


  if(qcdSelection()) {
    if(_nDenEls==1)
      fill("MZelJet", Candidate::create(_denLeps[0],_goodJets[0])->mass(), _weight);
    fillPlots("QCDNorm_ECOP");
  } 

  if(ewkSelection()) {
    counter("ewksel");
    fillPlots("EwkNorm_ECOP");
  }

  if(ucsxEwkSelection()) {
    fillPlots("EwkNorm_UCSX");
  }

  if(mrSelection(20)) {
    fillPlots("MR_ECOP");
    fillPlots("MR_UCSX");
  }
 
}


void 
FakeRatioV3::selectObjects() {

  _isIso=false;
  
  for(int idx=0; idx<_vc->get("nLepGood"); ++idx) {
    bool isMu=std::abs(_vc->get("LepGood_pdgId",idx))==13;
    Candidate* c=Candidate::create(_vc->get("LepGood_pt", idx),
				   _vc->get("LepGood_eta"   , idx),
				   _vc->get("LepGood_phi"   , idx),
				   _vc->get("LepGood_pdgId" , idx),
				   _vc->get("LepGood_charge", idx),
				   0.0005);
    
    
    //loose leptons for jet removal
    //if(!looseLepton(c, idx, "LepGood") ) continue;
    _looseLeps.push_back(c);
    _looseLepsIdx.push_back(idx);

    //fakable leptons ======================
    if(!fakableLepton(c, idx, "LepGood") ) continue;

    _denLeps.push_back(c);
    _denLepsIdx.push_back(idx);

    if(isMu) _nDenMus+=1;
    else _nDenEls+=1;

    if(_susyMod->elHLTEmulSelIso(idx,SusyModule::kLooseHT,"LepGood") ) //isMu || (!isMu && 
      _isIso=true;
    
    //tight leptons ======================
    if(!tightLepton(c, idx, "LepGood") ) continue;

    _numLeps.push_back(c);
    _numLepsIdx.push_back(idx);

    
  }//lepgood loop

  _nDenLeps=_denLeps.size();
  _nNumLeps=_numLeps.size();
  if(_nDenLeps==0) return;
  
  //cout<<"leptons :"<<_vc->get("nLepGood")<<" > "<<_looseLeps.size()<<" > "<<_denLeps.size()<<endl;

  _susyMod->cleanJets( &_looseLeps, _goodJets, _goodJetsIdx, _bJets, _bJetsIdx, _lepJets, _lepJetsIdx, 30, 25);
  _susyMod->awayJets ( &_denLeps, _goodJets, _goodJetsIdx, 1.0);
  
  _nJets=_goodJets.size();
  _HT=_susyMod->HT( &(_goodJets) );
  _met=Candidate::create(_vc->get("met_pt"), _vc->get("met_phi") );
}



bool 
FakeRatioV3::looseLepton(Candidate* c, int idx, const string& branch) {
  if(c->pt()<10) return false;
  
  if(std::abs(c->pdgId())==11) {
    if(!_susyMod->elIdSelV2(c, idx, branch, SusyModule::kLoose, 
			    false, true, false) ) return false;
    
    float dr_cache = 999.;
    for(unsigned int il=idx+1; il<_vc->get("nLepGood"); ++il){
      float dr = KineUtils::dR(_vc->get("LepGood_eta",il),_vc->get("LepGood_eta",idx),
			       _vc->get("LepGood_phi",il),_vc->get("LepGood_phi",idx));
      if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache)
	dr_cache = dr;
    }
    if(dr_cache<0.05) return false;
    
  }
  else {
    if(!_susyMod->muIdSelV2(c, idx, branch, SusyModule::kLoose,
			    true, false) ) return false;
  }

  return true;
}

bool 
FakeRatioV3::fakableLepton(Candidate* c, int idx, const string& branch) {
  if(c->pt()<10) return false;
  
  if(std::abs(c->pdgId())==11) {
    if(!_susyMod->elIdSelV2(c, idx, branch, SusyModule::kFakable, 
			    false, true, false) ) return false;
    
    float dr_cache = 999.;
    for(unsigned int il=idx+1; il<_vc->get("nLepGood"); ++il){
      float dr = KineUtils::dR(_vc->get("LepGood_eta",il),_vc->get("LepGood_eta",idx),
			       _vc->get("LepGood_phi",il),_vc->get("LepGood_phi",idx));
      if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache)
	dr_cache = dr;
    }
    if(dr_cache<0.05) return false;
    
  }
  else {
    if(!_susyMod->muIdSelV2(c, idx, branch, SusyModule::kFakable,
			    true, false) ) return false;
  }

  return true;
}

//____________________________________________________________________________
bool 
FakeRatioV3::tightLepton(Candidate* c, int idx, const string& branch) {

  if(c->pt()<10) return false;

  if(std::abs(c->pdgId())==11) {
    if(!_susyMod->elIdSelV2(c, idx, branch, SusyModule::kTight,
			    false, true, false) ) return false;

    float dr_cache = 999.;
    for(unsigned int il=idx+1; il<_vc->get("nLepGood"); ++il){
      float dr = KineUtils::dR(_vc->get("LepGood_eta",il),_vc->get("LepGood_eta",idx),
			       _vc->get("LepGood_phi",il),_vc->get("LepGood_phi",idx));
      if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache)
	dr_cache = dr;
    }
    if(dr_cache<0.05) return false;
  }
  else {
    if(!_susyMod->muIdSelV2(c, idx, branch, SusyModule::kTight,
			    true, false) ) return false;
  }
  
  return true;
}



// Trigger functions ========================
void
FakeRatioV3::initTriggerLines() {
  

  //trigger lines
  _hltLines.resize(kCats);
  _hltLines[kElN]["NEl8" ].line="HLT_FR_Ele8_CaloIdM_TrackIdM_PFJet30";
  _hltLines[kElN]["NEl17"].line="HLT_FR_Ele17_CaloIdM_TrackIdM_PFJet30";
  _hltLines[kElI]["IEl8" ].line="HLT_FR_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30";
  _hltLines[kElI]["IEl17"].line="HLT_FR_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30";
  _hltLines[kMuN]["NMu8" ].line="HLT_FR_Mu8";
  _hltLines[kMuN]["NMu17"].line="HLT_FR_Mu17";
  _hltLines[kMuI]["IMu8" ].line="HLT_FR_Mu8_TrkIsoVVL";
  _hltLines[kMuI]["IMu17"].line="HLT_FR_Mu17_TrkIsoVVL";

  //trigger pt bins =========
  findTriggerPts();
  
  // _hltPtBins.resize(kCats);
  // _hltPtBins[kElN]=findTriggerPts(_hltLines[kElN], "Ele");
  // _hltPtBins[kElI]=findTriggerPts(_hltLines[kElI], "Ele");
  // _hltPtBins[kMuN]=findTriggerPts(_hltLines[kMuN], "Mu");
  // _hltPtBins[kMuI]=findTriggerPts(_hltLines[kMuI], "Mu");

  //trigger eta bins ========
  // _hltEtaBins.resize(kNFlavs);
  // _hltEtaBins[kEl]=vector<float>({0});
  // _hltEtaBins[kMu]=vector<float>({0});
  for(unsigned ic=0;ic<kCats;ic++) {
    for(_itHlt=_hltLines[ic].begin();_itHlt!=_hltLines[ic].end();_itHlt++) {
      _itHlt->second.setEtas(0,2.5);
    }
  }

  //fake ratio pt bins ======
  _frPtBins.resize(kNFlavs);
  _frPtBins[kEl]=vector<float>({10.0, 15.0, 25.0, 35.0, 50.0, 70.0, 120.0});
  _frPtBins[kMu]=vector<float>({10.0, 15.0, 25.0, 35.0, 50.0, 70.0, 120.0});

  //fake ratio eta bins =====
  _frEtaBins.resize(kNFlavs);
  _frEtaBins[kEl]=vector<float>({0.0, 0.8, 1.479, 2.5});
  _frEtaBins[kMu]=vector<float>({0.0, 1.2, 2.1, 2.4});

  //get trigger lines for each FR type bin =======
  // _hltLinesFR.resize(kCats);
  // for(unsigned int it=0;it<kCats;it++) {
  //   _hltLinesFR[it] = findTriggerLines( _hltLines[it], _hltPtBins[it], it );
  //   // _hltEtaBins[it/2], _frPtBins[it/2], _frEtaBins[it/2]
  // }
  
}



//Other functions =====================================
void
FakeRatioV3::initVariables() {

  //Tree Branches
  _vc->registerVar("nLepGood");
  _vc->registerVar("LepGood_pdgId");
  _vc->registerVar("LepGood_pt");
  _vc->registerVar("LepGood_eta");
  _vc->registerVar("LepGood_phi");
  _vc->registerVar("LepGood_relIsoAnM");
  _vc->registerVar("LepGood_jetBTagCSV");
  _vc->registerVar("isData");
  _vc->registerVar("run");
  _vc->registerVar("lumi");
  _vc->registerVar("evt");
  _vc->registerVar("nVert");
  _vc->registerVar("nTrueInt");
  _vc->registerVar("vtxWeight");
  _vc->registerVar("genWeight");
  _vc->registerVar("met_pt");
  _vc->registerVar("met_eta");
  _vc->registerVar("met_phi");
  _vc->registerVar("met_mass");
  _vc->registerVar("nJet");
  _vc->registerVar("Jet_id");
  _vc->registerVar("Jet_pt");
  _vc->registerVar("Jet_rawPt");
  _vc->registerVar("Jet_eta");
  _vc->registerVar("Jet_phi");
  _vc->registerVar("Jet_mass");
  _vc->registerVar("Jet_btagCSV");
  _vc->registerVar("nDiscJet");
  _vc->registerVar("DiscJet_id");
  _vc->registerVar("DiscJet_pt");
  _vc->registerVar("DiscJet_rawPt");
  _vc->registerVar("DiscJet_eta");
  _vc->registerVar("DiscJet_phi");
  _vc->registerVar("DiscJet_mass");
  _vc->registerVar("DiscJet_btagCSV");


  //generatorinformations
  _vc->registerVar("nGenPart");
  _vc->registerVar("GenPart_pt");
  _vc->registerVar("GenPart_eta");
  _vc->registerVar("GenPart_phi");
  _vc->registerVar("GenPart_pdgId");
  _vc->registerVar("GenPart_motherId");
  _vc->registerVar("GenPart_grandmotherId");

  _vc->registerVar("nGenBHad");
  _vc->registerVar("GenBHad_pt");
  _vc->registerVar("GenBHad_eta");
  _vc->registerVar("GenBHad_phi");
  _vc->registerVar("GenBHad_pdgId");

  //bjets
  _vc->registerVar("nBJetLoose25");
  _vc->registerVar("nBJetMedium40");
  _vc->registerVar("nBJetMedium25");
  _vc->registerVar("nSoftBJetMedium25");


  //triggers
  registerLepVars();
  registerTriggerVars();



}


void 
FakeRatioV3::registerLepVars() {

  vector<string> leps({"LepGood"});

  for(unsigned int i = 0; i < leps.size(); ++i){
    _vc->registerVar("n" + leps[i]                     );
    _vc->registerVar(leps[i] + "_pt"                   );
    _vc->registerVar(leps[i] + "_eta"                  );
    _vc->registerVar(leps[i] + "_etaSc"                );
    _vc->registerVar(leps[i] + "_phi"                  );
    _vc->registerVar(leps[i] + "_charge"               );
    _vc->registerVar(leps[i] + "_tightCharge"          );
    _vc->registerVar(leps[i] + "_mediumMuonId"         );
    _vc->registerVar(leps[i] + "_mediumMuonID2016"     );
    _vc->registerVar(leps[i] + "_mvaIdPhys14"          );
    _vc->registerVar(leps[i] + "_mvaIdSpring15"        );
    _vc->registerVar(leps[i] + "_mvaIdSpring16GP"      );
    _vc->registerVar(leps[i] + "_pdgId"                );
    _vc->registerVar(leps[i] + "_relIso03"             );
    _vc->registerVar(leps[i] + "_relIso04"             );
    _vc->registerVar(leps[i] + "_jetPtRatiov2"         );
    _vc->registerVar(leps[i] + "_jetPtRelv2"           );
    _vc->registerVar(leps[i] + "_jetRawPt"             );
    _vc->registerVar(leps[i] + "_jetCorrFactor_L1L2L3Res");
    _vc->registerVar(leps[i] + "_miniRelIso"           );
    _vc->registerVar(leps[i] + "_chargedHadRelIso03"   );
    _vc->registerVar(leps[i] + "_miniRelIso"           );
    _vc->registerVar(leps[i] + "_miniRelIso"           );
    _vc->registerVar(leps[i] + "_dxy"                  );
    _vc->registerVar(leps[i] + "_dz"                   );
    _vc->registerVar(leps[i] + "_sip3d"                );
    _vc->registerVar(leps[i] + "_pfMuonId"             );
    _vc->registerVar(leps[i] + "_tightId"              );
    _vc->registerVar(leps[i] + "_looseIdSusy"          );
    _vc->registerVar(leps[i] + "_convVeto"             );
    _vc->registerVar(leps[i] + "_lostHits"             );
    _vc->registerVar(leps[i] + "_eleCutId2012_full5x5" );
    _vc->registerVar(leps[i] + "_mvaSusyPHYS14"        );
    _vc->registerVar(leps[i] + "_mvaSUSY"              );
    _vc->registerVar(leps[i] + "_mcMatchId"            );
    _vc->registerVar(leps[i] + "_mcMatchAny"           );
    _vc->registerVar(leps[i] + "_jetBTagCSV"           );
    _vc->registerVar(leps[i] + "_sigmaIEtaIEta"        );
    _vc->registerVar(leps[i] + "_hadronicOverEm"       );
    _vc->registerVar(leps[i] + "_eInvMinusPInv"        );
    _vc->registerVar(leps[i] + "_dEtaScTrkIn"          );
    _vc->registerVar(leps[i] + "_dPhiScTrkIn"          );
    _vc->registerVar(leps[i] + "_ecalPFClusterIso"     );
    _vc->registerVar(leps[i] + "_hcalPFClusterIso"     );
    _vc->registerVar(leps[i] + "_dr03TkSumPt"          );
    _vc->registerVar(leps[i] + "_isFO_Mini"            );
    _vc->registerVar(leps[i] + "_isFOL_Mini"            );
    _vc->registerVar(leps[i] + "_isFOT_Mini"            );
    _vc->registerVar(leps[i] + "_isTight_Mini"         );
    _vc->registerVar(leps[i] + "_isTightL_Mini"         );
    _vc->registerVar(leps[i] + "_isTightT_Mini"         );
  }

}


void 
FakeRatioV3::registerTriggerVars() {

  for(unsigned int it=0;it<kCats;it++) {
    for(_itHlt=_hltLines[it].begin();_itHlt!=_hltLines[it].end();_itHlt++) {
      _vc->registerVar( _itHlt->second.line ); 
    }
  }
}
 
bool
FakeRatioV3::baseSelection() {

  // lepton multiplicity
  if(_nDenLeps!=1) return false;
  // if( (_sampleName.find("datael")!=std::string::npos) && _nDenEls!=1 ) return false;
  // if( (_sampleName.find("datamu")!=std::string::npos) && _nDenMus!=1 ) return false;
  counter("denLepSel");
  //QCD muon samples
  if( (_sampleName.find("Mu15")!=std::string::npos) && _denLeps[0]->pt()<15 ) return false;
  else if( (_sampleName.find("Mu5")!=std::string::npos) && _denLeps[0]->pt()>15 ) return false;
 
  // jet multiplicity
  if(_nJets<1) return false;
  counter("nJetsSel");
  // triggers per FO
  if(!triggerSelection() ) return false;
  counter("hltSel");
  return true;
}

bool
FakeRatioV3::triggerSelection() {
  // trigger selection: combination of triggers per fake ratio bin of pt
  
  int etabin, ptbin;
  unsigned int m=0,M=0;
  float etam=0, etaM=2.5;
  float ptm=0, ptM=1000;
    
  if(std::abs(_denLeps[0]->pdgId())==11) {
    etabin=StatUtils::findBin<float>(std::abs(_denLeps[0]->eta()), _frEtaBins[kEl]);
    ptbin=StatUtils::findBin<float>(_denLeps[0]->pt(), _frPtBins[kEl]); 
    etam=_frEtaBins[kEl][etabin];
    etaM=_frEtaBins[kEl][etabin+1];
    ptm=_frPtBins[kEl][ptbin];
    ptM=(ptbin==(int)_frPtBins[kEl].size())?1000:_frPtBins[kEl][ptbin+1];
      
    m=kElN;
    M=_isIso?kElI:kElN;
  }
  else if(std::abs(_denLeps[0]->pdgId())==13) {
    etabin=StatUtils::findBin<float>(std::abs(_denLeps[0]->eta()), _frEtaBins[kMu]);
    ptbin=StatUtils::findBin<float>(_denLeps[0]->pt(), _frPtBins[kMu]);
    etam=_frEtaBins[kMu][etabin];
    etaM=_frEtaBins[kMu][etabin+1];
    ptm=_frPtBins[kMu][ptbin];
    ptM=(ptbin==(int)_frPtBins[kMu].size())?1000:_frPtBins[kMu][ptbin+1];

    m=kMuN;
    M=_isIso?kMuI:kMuN;
  }

  //cout<<" new event test "<<m<<"  "<<M<<"  "<<_denLeps[0]->pt()<<"  "<<_denLeps[0]->eta()<<"  "<<ptm<<"  "<<ptM<<endl;
  for(unsigned int i=m;i<M+1;i++) {
    for(_itHlt=_hltLines[i].begin();_itHlt!=_hltLines[i].end();_itHlt++) {
      //cout<<" ========>> "<<_itHlt->second.validEtaBin(etam,etaM)<<"  "<<_itHlt->second.validPtBin(ptm,ptM)<<endl;
      if(_itHlt->second.validEtaBin(etam,etaM) && _itHlt->second.validPtBin(ptm,ptM) ) {
	//cout<<" selected line "<<_itHlt->second.line<<endl;
	if(!_vc->get("isData") || _vc->get(_itHlt->second.line) )
	  _extsHLT.push_back(_itHlt->first);
      }
    }
  }
  
  if(_extsHLT.size()==0) return false;
  return true;
}



bool
FakeRatioV3::qcdSelection() {

  return true;

}


bool
FakeRatioV3::ewkSelection() {

  // MET INVERTED! 
  if(_met->pt()<20.0) return false;
  
  return true;
}


bool
FakeRatioV3::ucsxEwkSelection() {
  // MET INVERTED! 
  if(_met->pt()<20.0) return false;
 
  return true;
}


bool
FakeRatioV3::mrSelection(float mtCut) {
  if(_met->pt()>20.0) return false;
  if(_mt>mtCut) return false;
  return true;
}

void
FakeRatioV3::ZSelection() {

  if(_nDenLeps!=2) return;
  if(_nDenEls==1) return;
  if(_denLeps[0]->pdgId()!=(-_denLeps[1]->pdgId())) return;

  int etabin, ptbin;
  unsigned int m=0,M=0;
  float etam=0, etaM=2.5;
  float ptm=0, ptM=1000;
    
  int idx=0;
  if(_denLeps[0]->pt()<_denLeps[1]->pt()) idx=1;

  if(std::abs(_denLeps[idx]->pdgId())==11) {
    etabin=StatUtils::findBin<float>(std::abs(_denLeps[0]->eta()), _frEtaBins[kEl]);
    ptbin=StatUtils::findBin<float>(_denLeps[0]->pt(), _frPtBins[kEl]); 
    etam=_frEtaBins[kEl][etabin];
    etaM=_frEtaBins[kEl][etabin+1];
    ptm=_frPtBins[kEl][ptbin];
    ptM=(ptbin==(int)_frPtBins[kEl].size())?1000:_frPtBins[kEl][ptbin+1];
      
    m=kElN;
    M=(_isIso)?kElI:kElN;
  }
  else if(std::abs(_denLeps[0]->pdgId())==13) {
    etabin=StatUtils::findBin<float>(std::abs(_denLeps[0]->eta()), _frEtaBins[kMu]);
    ptbin=StatUtils::findBin<float>(_denLeps[0]->pt(), _frPtBins[kMu]);
    etam=_frEtaBins[kMu][etabin];
    etaM=_frEtaBins[kMu][etabin+1];
    ptm=_frPtBins[kMu][ptbin];
    ptM=(ptbin==(int)_frPtBins[kMu].size())?1000:_frPtBins[kMu][ptbin+1];

    m=kMuN;
    M=(_isIso)?kMuI:kMuN;
  }
  
  // if(!_isIso)
  //cout<<"MZ "<<m<<"  "<<M<<" -> "<<_denLeps[0]->pt()<<"  "<<_denLeps[0]->eta()<<"  "<<_denLeps[0]->pdgId()<<" / "<<_denLeps[1]->pt()<<"  "<<_denLeps[1]->eta()<<"  "<<_denLeps[1]->pdgId()<<" ==>> "<<Candidate::create(_denLeps[0],_denLeps[1])->mass()<<endl;

  for(unsigned int i=m;i<M+1;i++) {
    //cout<<" -->> "<<i<<"  "<<_hltLines[i].size()<<endl;
    for(_itHlt=_hltLines[i].begin();_itHlt!=_hltLines[i].end();_itHlt++) {
      if(_itHlt->second.validEtaBin(etam,etaM) && _itHlt->second.validPtBin(ptm,ptM) ) {
	//cout<<_itHlt->second.line<<"   "<<_vc->get("isData")<<"   "<<_itHlt->first<<endl;
	if(!_vc->get("isData") || _vc->get(_itHlt->second.line) ) {
	  fill("MZ_Den_"+_itHlt->first,
	       Candidate::create(_denLeps[0],_denLeps[1])->mass(), _weight);
	  if(_nNumLeps!=2) continue;
	  fill("MZ_Num_"+_itHlt->first,
	       Candidate::create(_numLeps[0],_numLeps[1])->mass(), _weight);
	}
      }
    }
  }

}


//====================================================================================

void
FakeRatioV3::findTriggerPts() {
  
  for(unsigned int i=0;i<_hltLines.size();i++) {
    string flav="Ele";
    if(i>kElI) flav="Mu";

    //retrieve all boundaries
    vector<float> trigger_pts;
    for(_itHlt=_hltLines[i].begin();_itHlt!=_hltLines[i].end();_itHlt++) {
      string name=_itHlt->second.line;
      unsigned int pos = name.find(flav)+flav.size();
      string num = name.substr(pos, name.find("_", pos) - pos);
      trigger_pts.push_back( atof(num.c_str()) );
    }
    sort(trigger_pts.begin(), trigger_pts.end() );

    //assign boundaries
    for(_itHlt=_hltLines[i].begin();_itHlt!=_hltLines[i].end();_itHlt++) {
      string name=_itHlt->second.line;
      unsigned int pos = name.find(flav)+flav.size();
      string num = name.substr(pos, name.find("_", pos) - pos);
      
      size_t bin=StatUtils::findBin<float>(atof(num.c_str()), trigger_pts ); 
    
      if(bin<0) _itHlt->second.setPts(0, trigger_pts[0] );
      else if(bin==trigger_pts.size() ) _itHlt->second.setPts(trigger_pts.back(),100000);
      else _itHlt->second.setPts(trigger_pts[bin], trigger_pts[bin+1]);
    }
  }
 
}



void
FakeRatioV3::fillPlots(const string& region) {

  //int fl=((std::abs(_denLeps[0]->pdgId())==13)?kMu:kEl);
  string post="_"+region+"_"; //+"_"+_flavors[fl]

  for(unsigned int ih=0;ih<_extsHLT.size();ih++) {
    
    if(_controlPlots) {
      fill("HT"+post+_extsHLT[ih], _HT , _weight);
      fill("MET"+post+_extsHLT[ih], _met->pt() , _weight);
    }
    

    //denominator plot =======================================================================================
    for(unsigned int il=0;il<_nDenLeps;il++) {

      int lepIdx=_denLepsIdx[0];
      // float MT=KineUtils::M_T( _denLeps[0]->pt(), _met->pt(),
      // 			       _denLeps[0]->phi(), _met->phi());

      if(_controlPlots) {
	fill("DXY_Den"+post+_extsHLT[ih]    , std::abs(_vc->get("LepGood_dxy", lepIdx)), _weight);         
	fill("DZ_Den"+post+_extsHLT[ih]     , std::abs(_vc->get("LepGood_dz", lepIdx)), _weight);
	fill("SIP_Den"+post+_extsHLT[ih]    , _vc->get("LepGood_sip3d", lepIdx), _weight);
	fill("MiniIso_Den"+post+_extsHLT[ih], _vc->get("LepGood_miniRelIso", lepIdx), _weight);    
      }

      if(_projPlots) {
	fill("Eta_Den"+post+_extsHLT[ih]   , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
	fill("Pt_Den"+post+_extsHLT[ih]    , _vc->get("LepGood_pt", lepIdx), _weight);
	fill("PtCorr_Den"+post+_extsHLT[ih], _susyMod->conePt(lepIdx, SusyModule::kMedium, "LepGood"), _weight);
      }
      
      //cout<<post+_extsHLT[ih]<<endl;
      fill("MT_Den"+post+_extsHLT[ih]       , _mt , _weight);
      fill("MapPt_Den"+post+_extsHLT[ih]    , overflowPt(_vc->get("LepGood_pt", lepIdx)), std::abs(_vc->get("LepGood_eta", lepIdx)) , _weight);
      fill("MapPtCorr_Den"+post+_extsHLT[ih], overflowPt(_susyMod->conePt(lepIdx, SusyModule::kMedium, "LepGood")),std::abs(_vc->get("LepGood_eta",lepIdx)), _weight); 
    }

    //numerator plot =======================================================================================
    for(unsigned int il=0;il<_nNumLeps;il++) {

      int lepIdx=_numLepsIdx[0];
      // float MT=KineUtils::M_T( _numLeps[0]->pt(), _met->pt(),
      // 			       _numLeps[0]->phi(), _met->phi());

      if(_controlPlots) {
	fill("DXY_Num"+post+_extsHLT[ih]    , std::abs(_vc->get("LepGood_dxy", lepIdx)), _weight);
	fill("DZ_Num"+post+_extsHLT[ih]     , std::abs(_vc->get("LepGood_dz", lepIdx)), _weight);          
	fill("SIP_Num"+post+_extsHLT[ih]    , _vc->get("LepGood_sip3d", lepIdx), _weight);          
	fill("MiniIso_Num"+post+_extsHLT[ih], _vc->get("LepGood_miniRelIso", lepIdx), _weight);  
      }
    
      if(_projPlots) {
	fill("Eta_Num"+post+_extsHLT[ih]   , std::abs(_vc->get("LepGood_eta", lepIdx)), _weight);
	fill("Pt_Num"+post+_extsHLT[ih]    , _vc->get("LepGood_pt", lepIdx), _weight);
	fill("PtCorr_Num"+post+_extsHLT[ih], overflowPt(_susyMod->conePt(lepIdx, SusyModule::kTight, "LepGood")) , _weight);
      }
    
      fill("MT_Num"+post+_extsHLT[ih]       , _mt, _weight);
      fill("MapPt_Num"+post+_extsHLT[ih]    , overflowPt(_vc->get("LepGood_pt", lepIdx)), std::abs(_vc->get("LepGood_eta", lepIdx)) , _weight);
      fill("MapPtCorr_Num"+post+_extsHLT[ih], overflowPt(_susyMod->conePt(lepIdx, SusyModule::kTight, "LepGood")),std::abs(_vc->get("LepGood_eta",lepIdx)), _weight);  
    }

  }//triggers

}



float 
FakeRatioV3::overflowPt(float rawPt){
  if(rawPt >= 70.) return 60.;
  return rawPt;
}
