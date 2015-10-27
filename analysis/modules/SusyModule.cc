#include "analysis/modules/SusyModule.hh"


SusyModule::SusyModule(VarClass* vc):
  _vc(vc),_dbm(nullptr)
{
  defineLeptonWPS();
  
}

SusyModule::SusyModule(VarClass* vc, DataBaseManager* dbm):
  _vc(vc), _dbm(dbm)
{
  defineLeptonWPS();
  loadDBs();
}

SusyModule::~SusyModule() {

  delete _vc;
}

void
SusyModule::loadDBs() {

  //_dbm->loadDb("PileupWeights.root",""); -> done with trees

  //HLT scale factors
  _dbm->loadDb("hltDEG","hltSFDoubleEG.db");
  _dbm->loadDb("hltDMu","hltSFDoubleMu.db");
  _dbm->loadDb("hltSEle","hltSFSingleEle.db");
  _dbm->loadDb("hltSMu","hltSFSingleMu.db");
  
  //lepton scale factors
  _dbm->loadDb("eleSFDb","electronSF.db");
  _dbm->loadDb("muSFDb","muonSF.db");
  _dbm->loadDb("tauSFDb","tauSF.db");
  
}

void
SusyModule::defineLeptonWPS() {

  _cLostHitWP.resize(kNWPs);
  _tChWP.resize(kNWPs);
  _sipWP.resize(kNWPs);
  _dxyWP.resize(kNWPs);
  _dzWP.resize(kNWPs);
  _elMvaIdWP.resize(3);
  _multiIsoWP.resize(3);
  _ptWP.resize(2);

  for(int i=0;i<3;++i) {
    _elMvaIdWP[i].resize(kNWPs);
    _multiIsoWP[i].resize(kNWPs);
    if(i!=2) _ptWP[i].resize(kNWPs);
  }
  
  //conv rej ====================
  _cLostHitWP[kDenom] = 1; 
  _cLostHitWP[kLoose] = 1; 
  _cLostHitWP[kTight] = 0; 

  //pt ============================
  _ptWP[kEl][kDenom] = 7 ; _ptWP[kMu][kDenom] = 5 ;
  _ptWP[kEl][kLoose] = 7 ; _ptWP[kMu][kLoose] = 5 ;
  _ptWP[kEl][kTight] = 10; _ptWP[kMu][kTight] = 10;

  //sip & IP ======================
  _sipWP[kDenom] = 4.0; 
  _sipWP[kLoose] = 1000.0; 
  _sipWP[kTight] = 4.0; 
  
  _dxyWP[kDenom] = 0.05; //cm
  _dxyWP[kLoose] = 0.05; //cm
  _dxyWP[kTight] = 0.05; //cm
  
  _dzWP[kDenom] = 0.1; //cm
  _dzWP[kLoose] = 0.1; //cm
  _dzWP[kTight] = 0.1; //cm

  //tight charge
  _tChWP[kLoose]=-1;
  _tChWP[kTight]=1;


  //el mva id ======================
  //Phys14 50ns?
  // _elMvaIdWP[kEBC][kLoose] = -0.11;
  // _elMvaIdWP[kEBF][kLoose] = -0.35;
  // _elMvaIdWP[kEE ][kLoose] = -0.55;

  // _elMvaIdWP[kEBC][kTight] = 0.73;
  // _elMvaIdWP[kEBF][kTight] = 0.57;
  // _elMvaIdWP[kEE ][kTight] = 0.05;

  // emulator for non-isolated and isolated triggers  
  //_elMvaIdWP[kEBC][kSpecFakeElNon] = -0.70;
  //_elMvaIdWP[kEBF][kSpecFakeElNon] = -0.83;
  //_elMvaIdWP[kEE ][kSpecFakeElNon] = -0.92;

  // emulator for isolated triggers only
  //_elMvaIdWP[kEBC][kSpecFakeElIso] = -0.155;
  //_elMvaIdWP[kEBF][kSpecFakeElIso] = -0.56;
  //_elMvaIdWP[kEE ][kSpecFakeElIso] = -0.76;

  _elMvaIdWP[kEBC][kInSitu] = -0.363;
  _elMvaIdWP[kEBF][kInSitu] = -0.579;
  _elMvaIdWP[kEE ][kInSitu] = -0.623;

  _elMvaIdWP[kEBC][kInSituHT] = 0.051;
  _elMvaIdWP[kEBF][kInSituHT] = -0.261;
  _elMvaIdWP[kEE ][kInSituHT] = -0.403;

  _elMvaIdWP[kEBC][kLoose] = -0.70;
  _elMvaIdWP[kEBF][kLoose] = -0.83;
  _elMvaIdWP[kEE ][kLoose] = -0.92;

  _elMvaIdWP[kEBC][kLooseHT] = -0.155;
  _elMvaIdWP[kEBF][kLooseHT] = -0.56;
  _elMvaIdWP[kEE ][kLooseHT] = -0.76;

  _elMvaIdWP[kEBC][kTight] = 0.87;
  _elMvaIdWP[kEBF][kTight] = 0.60;
  _elMvaIdWP[kEE ][kTight] = 0.17;

  //multiIso =======================
  _multiIsoWP[kMiniIso][kDenom]      = 0.4 ; _multiIsoWP[kPtRatio][kDenom]      = 0   ; _multiIsoWP[kPtRel][kDenom]      = 0  ;
  _multiIsoWP[kMiniIso][kVLoose]     = 0.25; _multiIsoWP[kPtRatio][kVLoose]     = 0.67; _multiIsoWP[kPtRel][kVLoose]     = 6.0;
  _multiIsoWP[kMiniIso][kLoose]      = 0.20; _multiIsoWP[kPtRatio][kLoose]      = 0.69; _multiIsoWP[kPtRel][kLoose]      = 6.0;
  _multiIsoWP[kMiniIso][kMedium]     = 0.16; _multiIsoWP[kPtRatio][kMedium]     = 0.76; _multiIsoWP[kPtRel][kMedium]     = 7.2; 
  _multiIsoWP[kMiniIso][kTight]      = 0.12; _multiIsoWP[kPtRatio][kTight]      = 0.80; _multiIsoWP[kPtRel][kTight]      = 7.2;
  _multiIsoWP[kMiniIso][kVTight]     = 0.09; _multiIsoWP[kPtRatio][kVTight]     = 0.84; _multiIsoWP[kPtRel][kVTight]     = 7.2;

  _multiIsoWP[kMiniIso][kSpecFakeEl] = 0.4 ; _multiIsoWP[kPtRatio][kSpecFakeEl] = 0.80; _multiIsoWP[kPtRel][kSpecFakeEl] = 7.2;
  _multiIsoWP[kMiniIso][kSpecFakeMu] = 0.4 ; _multiIsoWP[kPtRatio][kSpecFakeMu] = 0.76; _multiIsoWP[kPtRel][kSpecFakeMu] = 7.2;
}


//=====================================================
// lepton selection

bool
SusyModule::multiIsoSel(int idx, int wp) const {

  if(_vc->get("LepGood_miniRelIso"  , idx) < _multiIsoWP[kMiniIso][wp] &&
    (_vc->get("LepGood_jetPtRatiov2", idx) > _multiIsoWP[kPtRatio][wp] ||
     _vc->get("LepGood_jetPtRelv2"  , idx) > _multiIsoWP[kPtRel]  [wp] )) return true;
  
  return false;
}


bool
SusyModule::multiIsoSelCone(int idx, int wp) const {

  if( _vc->get("LepGood_miniRelIso", idx)<_multiIsoWP[kMiniIso][wp] &&
      (conePt(idx, wp)*_vc->get("LepGood_pt",idx) *_vc->get("LepGood_jetPtRatiov2", idx)>_multiIsoWP[kPtRatio][wp] ||
       _vc->get("LepGood_jetPtRelv2", idx)>_multiIsoWP[kPtRel][wp]) ) return true;
  
  return false;
}

bool
SusyModule::invMultiIsoSel(int idx, int wp) const {
  
  if( _vc->get("LepGood_miniRelIso", idx)>_multiIsoWP[kMiniIso][wp]) return false;
  if( 1./_vc->get("LepGood_jetPtRelv2", idx) > (1/_multiIsoWP[kPtRel][wp] + _vc->get("LepGood_miniRelIso", idx)) ) return false;
  return true;
}

bool 
SusyModule::elMvaSel(int idx, int wp) const {

  int etaBin=-1;

  if     (std::abs(_vc->get("LepGood_eta", idx)) < 0.8  ) etaBin=0;
  else if(std::abs(_vc->get("LepGood_eta", idx)) < 1.479) etaBin=1;
  else if(std::abs(_vc->get("LepGood_eta", idx)) < 2.5  ) etaBin=2;

  if(_vc->get("LepGood_mvaIdSpring15", idx) <  _elMvaIdWP[etaBin][wp]  ) return false;
    
  return true;
}

bool
SusyModule::inSituFO(int idx, int wp) const {

  if(_vc->get("LepGood_miniRelIso", idx) > 0.4) return false;
  if(1 / _vc->get("LepGood_jetPtRatiov2", idx) >= 1 / _multiIsoWP[kPtRatio][wp] + _vc->get("LepGood_miniRelIso", idx) && _vc->get("LepGood_jetPtRelv2", idx) < _multiIsoWP[kPtRel][wp]) return false;

  return true;
}


bool
SusyModule::muIdSel(int idx, int wp, bool invSIP) const {

  int wpIso = kDenom;

  if(         _vc->get("LepGood_pt"          , idx)  < _ptWP[kMu][wp]) return false;
  if(std::abs(_vc->get("LepGood_eta"         , idx)) >  2.4          ) return false;
  if(         _vc->get("LepGood_mediumMuonId", idx)  <= 0            ) return false;
  if(         _vc->get("LepGood_tightCharge" , idx)  <= 1            ) return false;
  if(std::abs(_vc->get("LepGood_dxy"         , idx)) > _dxyWP[wp]    ) return false;
  if(std::abs(_vc->get("LepGood_dz"          , idx)) > _dzWP[wp]     ) return false;
  if(!multiIsoSel(idx, wpIso)                                        ) return false;

  if(invSIP){
    if(       _vc->get("LepGood_sip3d"       , idx)  < _sipWP[wp]    ) return false;
  }
  else {
    if(       _vc->get("LepGood_sip3d"       , idx)  > _sipWP[wp]    ) return false;
  }

  return true;

}

bool
SusyModule::elIdSel(int idx, int wp, int mvaWp, bool invSIP) const {

  int wpIso=kDenom;
  if(         _vc->get("LepGood_pt"         , idx)  < _ptWP[kEl][wp] ) return false; //cout<<" pt "<<endl;
  if(std::abs(_vc->get("LepGood_eta"        , idx)) > 2.5            ) return false; 
  if(         _vc->get("LepGood_convVeto"   , idx)  != 1             ) return false;//cout<<" conv "<<endl;
  if(         _vc->get("LepGood_lostHits"   , idx)  > _cLostHitWP[wp]) return false;//cout<<" losthit "<<endl;

  if(         _vc->get("LepGood_tightCharge", idx)  <= _tChWP[wp]    ) return false;//cout<<" charge "<<_tChWP[wp]<<endl;
  if(std::abs(_vc->get("LepGood_dxy"        , idx)) > _dxyWP[wp]     ) return false;//cout<<" dx "<<endl;
  if(std::abs(_vc->get("LepGood_dz"         , idx)) > _dzWP[wp]      ) return false;//cout<<" dz "<<endl;
  if(!elMvaSel(idx, mvaWp)                                           ) return false;//cout<<" mvaId "<<endl;
  if(!multiIsoSel(idx, wpIso)                                        ) return false;//cout<<" iso "<<endl;

  if(invSIP){
    if(       _vc->get("LepGood_sip3d"       , idx)  < _sipWP[wp]    ) return false;
  }
  else {
    if(       _vc->get("LepGood_sip3d"       , idx)  > _sipWP[wp]    ) return false;
  }

  return true;

}

bool
SusyModule::elHLTEmulSel(int idx, bool withIso) const {

  if(std::abs(_vc->get("LepGood_eta", idx)) < 1.479) {
    if(         _vc->get("LepGood_sigmaIEtaIEta" , idx)  > 0.011 ) return false;
    if(std::abs(_vc->get("LepGood_dEtaScTrkIn"   , idx)) > 0.01  ) return false;
    if(std::abs(_vc->get("LepGood_dPhiScTrkIn"   , idx)) > 0.04  ) return false;
    if(         _vc->get("LepGood_hadronicOverEm", idx)  > 0.08  ) return false;
    if(std::abs(_vc->get("LepGood_eInvMinusPInv" , idx)) > 0.01  ) return false;
  }
  else {
    if(         _vc->get("LepGood_sigmaIEtaIEta" , idx)  > 0.031 ) return false;
    if(std::abs(_vc->get("LepGood_dEtaScTrkIn"   , idx)) > 0.01  ) return false;
    if(std::abs(_vc->get("LepGood_dPhiScTrkIn"   , idx)) > 0.08  ) return false;
    if(         _vc->get("LepGood_hadronicOverEm", idx)  > 0.08  ) return false;
    if(std::abs(_vc->get("LepGood_eInvMinusPInv" , idx)) > 0.01  ) return false;
  }
  if(!elMvaSel(idx, kLoose)                                      ) return false;
  
  if(withIso) {
    if(!elHLTEmulSelIso(idx)) return false;
  }

  return true;
}


bool
SusyModule::elHLTEmulSelIso(int idx, int mvaWP) const {

  if(_vc->get("LepGood_ecalPFClusterIso", idx) > 0.45 * _vc->get("LepGood_pt", idx) ) return false;
  if(_vc->get("LepGood_hcalPFClusterIso", idx) > 0.25 * _vc->get("LepGood_pt", idx) ) return false;
  if(_vc->get("LepGood_dr03TkSumPt"     , idx) > 0.2  * _vc->get("LepGood_pt", idx) ) return false;
  if(!elMvaSel(idx, mvaWP)                                                          ) return false;

  return true;
}





//===========================================================
bool
SusyModule::jetSel( int jetIdx) const {
  
  if(_vc->get("Jet_pt", jetIdx)<40.0) return false;
  return true;
}

float 
SusyModule::HT(const CandList* jets){
  float ht = 0;
  unsigned int nJets=jets->size();
  for(unsigned int i=0; i<nJets; ++i) 
    ht += jets->at(i)->pt();
  
  return ht;
}


//=============================================================
bool
SusyModule::mllVetoSelection(const Candidate* l1, const Candidate* l2,
			     const CandList* allLeps) const {
  
  for(unsigned int i = 0; i < allLeps->size(); ++i) {
    if(l1!=allLeps->at(i) && mllZVeto(l1, allLeps->at(i))) return false;
    if(l2!=allLeps->at(i) && mllZVeto(l2, allLeps->at(i))) return false;
    if(l1!=allLeps->at(i) && mllLMGVeto(l1, allLeps->at(i))) return false;
    if(l2!=allLeps->at(i) && mllLMGVeto(l2, allLeps->at(i))) return false;
  }
  
  return true;
}

bool 
SusyModule::mllLMGVeto(const Candidate* cand, const Candidate* veto) const {
  
  float mll = Candidate::create(cand, veto)->mass();

  if(mll <= 8.0) return true;
  if(cand->charge()==veto->charge() ) return false;
  if(mll <= 12.0) return true;

  return false;
}


bool 
SusyModule::mllZVeto(const Candidate* cand, const Candidate* veto) const {
 
  if(veto->pt() < 10) return false;
  float mll = Candidate::create(cand, veto)->mass();
  
  if(cand->charge()==veto->charge() ) return false;
  if(std::abs(cand->pdgId())==std::abs(veto->pdgId()) ) {
    if(mll >= 76.0 && mll <= 106.0) return true;
  }

  return false;
}


bool
SusyModule::passMllSingleVeto(const Candidate* c1, const Candidate* c2, 
			      float mllm, float mllM, bool ossf) {

  //cout<<"Id "<<c1->pdgId()<<"  "<<c2->pdgId()<<"  "<< Candidate::create(c1,c2)->mass()<<"  "<<mllm<<"  "<<mllM<<endl;
  if( (c1->pdgId()== -c2->pdgId()) || !ossf) {
    float mll = Candidate::create(c1,c2)->mass();
    if(mll>mllm && mll<mllM) return false; 
  }
  return true;
}


bool
SusyModule::passMllMultiVeto(const Candidate* c1, const CandList* cands, 
			     float mllm, float mllM, bool ossf) {

  for(size_t il=0;il<cands->size();il++) {
    if( c1==cands->at(il) ) continue;
    //cout<<" passng veto? "<<passMllSingleVeto(c1, cands->at(il), mllm, mllM, ossf)<<endl;
    if(!passMllSingleVeto(c1, cands->at(il), mllm, mllM, ossf)) return false;
  }
  return true;
}

CandList
SusyModule::bestSSPair(const CandList* leps, bool byflav,
		       bool bypassMV, float pTthr, int& idx1, int& idx2) {

//HACK: replaced nullptr with NULL

  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;

  if(leps->size()<=2) return (*leps);
  
  for(unsigned int il1=0;il1<leps->size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps->size();il2++) {
      
      //conditional pt threshold, could evolve in CERN code 
 
      if(leps->at(il1)->pt()<pTthr || leps->at(il2)->pt()<pTthr) continue; 

      if(!passMllSingleVeto(leps->at(il1), leps->at(il2), 0, 8, false) && !bypassMV) continue;

      if(leps->at(il1)->charge()!=leps->at(il2)->charge()) continue;

      int flav= (byflav?(std::abs(leps->at(il1)->pdgId()) + std::abs(leps->at(il2)->pdgId())):0);
      int st=leps->at(il1)->pt()+leps->at(il2)->pt();

      if(flav<tmpFlav) continue;

      if(flav>tmpFlav) tmpSt=0;
      tmpFlav=flav;
      if(st<tmpSt) continue;

      tmpSt=st;
      clist[0]=leps->at(il1);
      clist[1]=leps->at(il2);
      idx1 = il1;
      idx2 = il2;
    
    }//il2
  }//il1

  return clist;
}


CandList
SusyModule::bestSSPair(Candidate* c1, const CandList* leps, bool byflav,
		       bool bypassMV, float pTthr, int& idx1, int& idx2) {

  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;
  if(leps->size()<=1) {
    clist[0] = c1;
    clist[1] = leps->at(0);
    return clist;
  }
  
  for(unsigned int il=0;il<leps->size();il++) {
     //conditional pt threshold, could evolve in CERN code 

      if(c1->pt()<pTthr || leps->at(il)->pt()<pTthr) continue; 

      if(!passMllSingleVeto(c1, leps->at(il), 0, 8, false) && !bypassMV) continue;

      if(c1->charge()!=leps->at(il)->charge()) continue;

      int flav= (byflav?(std::abs(c1->pdgId()) + std::abs(leps->at(il)->pdgId())):0);
      int st=c1->pt()+leps->at(il)->pt();

      if(flav<tmpFlav) continue;

      if(flav>tmpFlav) tmpSt=0;
      tmpFlav=flav;
      if(st<tmpSt) continue;

      tmpSt=st;
      clist[0]=c1;
      clist[1]=leps->at(il);
      idx1 = 0;
      idx2 = il;
    
  }//il

  return clist;
}


float
SusyModule::closestJetPt(int idx) const {

  return _vc->get("LepGood_pt", idx) / _vc->get("LepGood_jetPtRatiov2", idx);

}


float 
SusyModule::conePt(int idx, int isoWp) const {

  if(_vc->get("LepGood_jetPtRelv2", idx) > _multiIsoWP[kPtRel][isoWp] ) {
    return _vc->get("LepGood_pt", idx)*(1 + std::max((double) 0., _vc->get("LepGood_miniRelIso", idx) - _multiIsoWP[kMiniIso][isoWp] ) );
  }
  return std::max(_vc->get("LepGood_pt", idx), (double) closestJetPt(idx) * _multiIsoWP[kPtRatio][isoWp] );

}


void 
SusyModule::awayJets(CandList* leptons, CandList& jets, vector<unsigned int>& jetIdxs, float dR) {

  for(unsigned int il = 0; il < leptons -> size(); ++il) {
    for(unsigned int ij = 0; ij < jets.size(); ++ij) {
      float dr = leptons->at(il)->dR( jets[ij] );
      if(dr < dR){
        jets   .erase(jets   .begin() + ij);
        jetIdxs.erase(jetIdxs.begin() + ij);
      }
    }
  }
}


void
SusyModule::cleanJets(CandList* leptons, 
		      CandList& cleanJets, vector<unsigned int>& jetIdxs,
		      CandList& cleanBJets, vector<unsigned int>& bJetIdxs) {

  cleanJets.clear();
  cleanBJets.clear();
  jetIdxs.clear();
  bJetIdxs.clear();

  string types[2] = {"Jet","DiscJet"};
  vector<string> jetTypes;
  jetTypes = Tools::toVector(types);
  CandList jets;
  vector<bool> bvals;
  for(size_t it=0;it<jetTypes.size();it++) {
    string jType=jetTypes[it];
    
    for(int ij=0;ij<_vc->get("n"+jType);ij++) {
      if(_vc->get(jType+"_id",ij)<1) continue;
      
      Candidate* jet=Candidate::create(_vc->get(jType+"_pt", ij),
				       _vc->get(jType+"_eta", ij),
				       _vc->get(jType+"_phi", ij) );

      jets.push_back(jet);
      bvals.push_back( _vc->get(jType+"_btagCSV",ij)<0.814 );
    }
  }


  map<Candidate*, std::pair<float,Candidate*> > cmap;
  map<Candidate*, std::pair<float,Candidate*> >::const_iterator it;

  for(unsigned int il=0;il<leptons->size();il++) {
    for(unsigned int ij=0;ij<jets.size();ij++) {
      float dR=leptons->at(il)->dR( jets[ij] );
      it = cmap.find(leptons->at(il));
      if(it==cmap.end() ) {
        cmap[ leptons->at(il) ] =std::make_pair(dR, jets[ij] );
      }
      else if(dR<it->second.first) {
        cmap[ leptons->at(il) ] =std::make_pair(dR, jets[ij] );
      }
    }
  }

  bool pass=true;
  for(unsigned int ij=0;ij<jets.size();ij++) {

    pass=true;
    for(unsigned int il=0;il<leptons->size();il++) {
      it = cmap.find(leptons->at(il));
      if(it->second.first > 0.4 ) continue;
      if(it->second.second == jets[ij] ) {pass=false; break;}
    }

    if(!pass) continue;

    if(jets[ij]->pt()<25) continue;
    
    if(jets[ij]->pt()>40) {
      cleanJets.push_back(jets[ij] );
      jetIdxs.push_back(ij);
    }
    
    if(bvals[ij]) continue;
    
    cleanBJets.push_back(jets[ij]);
    bJetIdxs.push_back(ij);
  } //loop jets

}


// Scale factors ====================================
void 
SusyModule::applyHLTSF(const string& hltLine, const CandList& cands, float& weight) {

  if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}

  if(hltLine=="HLT_DoubleEG") {
    weight *= _dbm->getDBValue("hltDEG", std::abs(cands[0]->eta()), cands[0]->pt(), cands[1]->eta(), cands[1]->pt() );
  }
  else if(hltLine=="HLT_DoubleMu") {
    weight *= _dbm->getDBValue("hltDMu", std::abs(cands[0]->eta()), cands[0]->pt(), cands[1]->eta(), cands[1]->pt() );
  }
  else if(hltLine=="HLT_SingleEle") {
    weight *= _dbm->getDBValue("hltSEle", std::abs(cands[0]->eta()), cands[0]->pt() );
  }
  else if(hltLine=="HLT_SingleMu") {
    weight *= _dbm->getDBValue("hltSMu", std::abs(cands[0]->eta()), cands[0]->pt() );
  }


}

void 
SusyModule::applyLepSF(const CandList& cands, float& weight) {

  for(unsigned int ic=0;ic<cands.size();ic++) {
    applySingleLepSF(cands[ic], weight);
  }

}


void 
SusyModule::applySingleLepSF(const Candidate* cand, float& weight) {

  if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}

  switch(std::abs(cand->pdgId())) {
  case 11: {weight *= _dbm->getDBValue("eleSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  case 13: {weight *= _dbm->getDBValue("muSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  case 15: {weight *= _dbm->getDBValue("tauSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  }

}
