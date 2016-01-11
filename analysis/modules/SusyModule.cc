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
  _muIdWP.resize(kNWPs);
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
  
  //muId
  _muIdWP[kDenom] = 0; 
  _muIdWP[kLoose] = 0;//1000. 
  _muIdWP[kTight] = 1; 
  

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
  _sipWP[kLoose] = 1000.0;//1000. 
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
  //_multiIsoWP[kMiniIso][kDenom]      = 0.6 ; _multiIsoWP[kPtRatio][kDenom]      = 0   ; _multiIsoWP[kPtRel][kDenom]      = 0  ;
  //_multiIsoWP[kMiniIso][kDenom]      = 0.8; _multiIsoWP[kPtRatio][kDenom]      = 0   ; _multiIsoWP[kPtRel][kDenom]      = 0  ;
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
SusyModule::multiIsoSel(int idx, int wp, string branch) const {

  if(_vc->get(branch + "_miniRelIso"  , idx) < _multiIsoWP[kMiniIso][wp] &&
    (_vc->get(branch + "_jetPtRatiov2", idx) > _multiIsoWP[kPtRatio][wp] ||
     _vc->get(branch + "_jetPtRelv2"  , idx) > _multiIsoWP[kPtRel]  [wp] )) return true;
  
  return false;
}


bool
SusyModule::multiIsoSelInSitu(int idx, int wp, string branch) const {

  // CH: wasn't my idea...
  if(_vc->get(branch + "_miniRelIso"  , idx) < _multiIsoWP[kMiniIso][wp] &&
     _vc->get(branch + "_jetPtRatiov2", idx) > _multiIsoWP[kPtRatio][wp]) return true;
  
  return false;
}


bool
SusyModule::multiIsoSelCone(int idx, int wp, string branch) const {

  if( _vc->get(branch + "_miniRelIso", idx)<_multiIsoWP[kMiniIso][wp] &&
      (conePt(idx, wp, branch)*_vc->get(branch + "_pt",idx) *_vc->get(branch + "_jetPtRatiov2", idx)>_multiIsoWP[kPtRatio][wp] ||
       _vc->get(branch + "_jetPtRelv2", idx)>_multiIsoWP[kPtRel][wp]) ) return true;
  
  return false;
}

bool
SusyModule::invMultiIsoSel(int idx, int wp, string branch) const {
  
  if( _vc->get(branch + "_miniRelIso", idx)>_multiIsoWP[kMiniIso][wp]) return false;
  if( 1./_vc->get(branch + "_jetPtRelv2", idx) > (1/_multiIsoWP[kPtRel][wp] + _vc->get(branch + "_miniRelIso", idx)) ) return false;
  return true;
}

bool 
SusyModule::elMvaSel(int idx, int wp, string branch) const {

  int etaBin=-1;

  //if(_vc->get("evt") == 930292 && idx == 0) cout << _elMvaIdWP[0][wp] << ":" << _elMvaIdWP[1][wp] << ":" << _elMvaIdWP[2][wp] << endl;

  if     (std::abs(_vc->get(branch + "_eta", idx)) < 0.8  ) etaBin=0;
  else if(std::abs(_vc->get(branch + "_eta", idx)) < 1.479) etaBin=1;
  else if(std::abs(_vc->get(branch + "_eta", idx)) < 2.5  ) etaBin=2;

  if(_vc->get(branch + "_mvaIdSpring15", idx) <  _elMvaIdWP[etaBin][wp]  ) return false;
    
  return true;
}

bool
SusyModule::inSituFO(int idx, int wp, string branch) const {

  if(_vc->get(branch + "_miniRelIso", idx) > 0.4) return false;
  if(1 / _vc->get(branch + "_jetPtRatiov2", idx) >= 1 / _multiIsoWP[kPtRatio][wp] + _vc->get(branch + "_miniRelIso", idx)) return false;
  //if(1 / _vc->get("LepGood_jetPtRatiov2", idx) >= 1 / _multiIsoWP[kPtRatio][wp] + _vc->get("LepGood_miniRelIso", idx) && _vc->get("LepGood_jetPtRelv2", idx) < _multiIsoWP[kPtRel][wp]) return false;

  return true;
}


bool
SusyModule::muIdSel(int idx, int wp, bool chCut, bool invSIP, string branch) const {

  int wpIso = kDenom;

  if(         _vc->get(branch + "_pt"          , idx)  < _ptWP[kMu][wp]) return false;
  if(std::abs(_vc->get(branch + "_eta"         , idx)) >  2.4          ) return false;
  if(         _vc->get(branch + "_mediumMuonId", idx)  <= 0            ) return false;
  if(chCut && _vc->get(branch + "_tightCharge" , idx)  <= 1            ) return false;
  if(std::abs(_vc->get(branch + "_dxy"         , idx)) > _dxyWP[wp]    ) return false;
  if(std::abs(_vc->get(branch + "_dz"          , idx)) > _dzWP[wp]     ) return false;
  if(!multiIsoSel(idx, wpIso, branch)                                  ) return false;

  if(invSIP){
    if(       _vc->get(branch + "_sip3d"       , idx)  < _sipWP[wp]    ) return false;
  }
  else {
    if(       _vc->get(branch + "_sip3d"       , idx)  > _sipWP[wp]    ) return false;
  }

  return true;

}

bool
SusyModule::elIdSel(int idx, int wp, int mvaWp, bool chCut, bool invSIP, string branch) const {

  int wpIso=kDenom;
  if(         _vc->get(branch + "_pt"         , idx)  < _ptWP[kEl][wp] ) return false; //cout<<" pt "<<endl;
  if(std::abs(_vc->get(branch + "_eta"        , idx)) > 2.5            ) return false; 
  if(         _vc->get(branch + "_convVeto"   , idx)  != 1             ) return false;//cout<<" conv "<<endl;
  if(         _vc->get(branch + "_lostHits"   , idx)  > _cLostHitWP[wp]) return false;//cout<<" losthit "<<endl;

  if(chCut && _vc->get(branch + "_tightCharge", idx)  <= _tChWP[wp]    ) return false;//cout<<" charge "<<_tChWP[wp]<<endl;
  if(std::abs(_vc->get(branch + "_dxy"        , idx)) > _dxyWP[wp]     ) return false;//cout<<" dx "<<endl;
  if(std::abs(_vc->get(branch + "_dz"         , idx)) > _dzWP[wp]      ) return false;//cout<<" dz "<<endl;
  if(!elMvaSel(idx, mvaWp, branch)                                     ) return false;//cout<<" mvaId "<<endl;
  if(!multiIsoSel(idx, wpIso, branch)                                  ) return false;//cout<<" iso "<<endl;

  if(invSIP){
    if(       _vc->get(branch + "_sip3d"       , idx)  < _sipWP[wp]    ) return false;
  }
  else {
    if(       _vc->get(branch + "_sip3d"       , idx)  > _sipWP[wp]    ) return false;
  }

  return true;

}

bool
SusyModule::elHLTEmulSel(int idx, bool withIso, string branch) const {

  if(std::abs(_vc->get(branch + "_eta", idx)) < 1.479) {
    if(         _vc->get(branch + "_sigmaIEtaIEta" , idx)  > 0.011 ) return false;
    if(std::abs(_vc->get(branch + "_dEtaScTrkIn"   , idx)) > 0.01  ) return false;
    if(std::abs(_vc->get(branch + "_dPhiScTrkIn"   , idx)) > 0.04  ) return false;
    if(         _vc->get(branch + "_hadronicOverEm", idx)  > 0.08  ) return false;
    if(std::abs(_vc->get(branch + "_eInvMinusPInv" , idx)) > 0.01  ) return false;
  }
  else {
    if(         _vc->get(branch + "_sigmaIEtaIEta" , idx)  > 0.031 ) return false;
    if(std::abs(_vc->get(branch + "_dEtaScTrkIn"   , idx)) > 0.01  ) return false;
    if(std::abs(_vc->get(branch + "_dPhiScTrkIn"   , idx)) > 0.08  ) return false;
    if(         _vc->get(branch + "_hadronicOverEm", idx)  > 0.08  ) return false;
    if(std::abs(_vc->get(branch + "_eInvMinusPInv" , idx)) > 0.01  ) return false;
  }
  if(!elMvaSel(idx, kLoose, branch)                                ) return false;
  
  if(withIso) {
    if(!elHLTEmulSelIso(idx, kLooseHT, branch)) return false;
  }

  return true;
}


bool
SusyModule::elHLTEmulSelIso(int idx, int mvaWP, string branch) const {

  if(_vc->get(branch + "_ecalPFClusterIso", idx) > 0.45 * _vc->get(branch + "_pt", idx) ) return false;
  if(_vc->get(branch + "_hcalPFClusterIso", idx) > 0.25 * _vc->get(branch + "_pt", idx) ) return false;
  if(_vc->get(branch + "_dr03TkSumPt"     , idx) > 0.2  * _vc->get(branch + "_pt", idx) ) return false;
  if(!elMvaSel(idx, mvaWP, branch)                                                      ) return false;

  return true;
}

bool
SusyModule::invPtRelSel(int idx, int wp, string branch) const {

  if(_vc->get(branch + "_jetPtRelv2", idx) < _multiIsoWP[kPtRel][wp]) return true;
  return false;

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
    //cout<<" ==> aqui "<<c2->uid()<<"   "<<c1->uid()<<endl;
    
    float mll = Candidate::create(c1,c2)->mass();
    //cout<<" ==> aqui! "<<endl;
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
		       bool bypassMV, bool os, 
		       float pTthrMu, float pTthrEl,
		       int& idx1, int& idx2) {

//HACK: replaced nullptr with NULL

  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;

  float pTthr1,pTthr2;
  
  for(unsigned int il1=0;il1<leps->size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps->size();il2++) {
      
      //conditional pt threshold, could evolve in CERN code 
 
      pTthr1 = (std::abs(leps->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      //conditional pt threshold, could evolve in CERN code 
      if(leps->at(il1)->pt()<pTthr1 || leps->at(il2)->pt()<pTthr2) continue; 
      
      if(!passMllSingleVeto(leps->at(il1), leps->at(il2), 0, 8, false) && !bypassMV) continue;
      
      if( (leps->at(il1)->charge()!=leps->at(il2)->charge())!=os ) continue;
      
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
SusyModule::bestSSPair(const CandList* leps1, const CandList* leps2, bool byflav,
		       bool bypassMV, bool os, float pTthrMu, float pTthrEl,
		       int& idx1, int& idx2) {

  //LISTS HAVE TO BE COMPLEMENTARY, NO OVERLAPS!

  //HACK: replaced nullptr with NULL
  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;

  float pTthr1,pTthr2;

  for(unsigned int il1=0;il1<leps1->size();il1++) {
    for(unsigned int il2=0;il2<leps2->size();il2++) {
      
      pTthr1 = (std::abs(leps1->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps2->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      //conditional pt threshold, could evolve in CERN code 
      if(leps1->at(il1)->pt()<pTthr1 || leps2->at(il2)->pt()<pTthr2) continue; 
      if(!passMllSingleVeto(leps1->at(il1), leps2->at(il2), 0, 8, false) && !bypassMV) continue;

      if( (leps1->at(il1)->charge()!=leps2->at(il2)->charge())!=os ) continue;
      int flav= (byflav?(std::abs(leps1->at(il1)->pdgId()) + std::abs(leps2->at(il2)->pdgId())):0);
      int st=leps1->at(il1)->pt()+leps2->at(il2)->pt();

      if(flav<tmpFlav) continue;
      if(flav>tmpFlav) tmpSt=0;
      tmpFlav=flav;
      if(st<tmpSt) continue;

      tmpSt=st;
      clist[0]=leps1->at(il1);
      clist[1]=leps2->at(il2);
      idx1 = il1;
      idx2 = il2;
    
    }//il2
  }//il1
  return clist;
}


CandList
SusyModule::bestSSPair(Candidate* c1, const CandList* leps, bool byflav,
		       bool bypassMV, bool os, float pTthrMu, float pTthrEl, 
		       int& idx1, int& idx2) {

  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;
 
  float pTthr1,pTthr2;

  for(unsigned int il=0;il<leps->size();il++) {
      
    pTthr1 = (std::abs(c1->pdgId())==11)?pTthrEl:pTthrMu;
    pTthr2 = (std::abs(leps->at(il)->pdgId())==11)?pTthrEl:pTthrMu;

    //conditional pt threshold, could evolve in CERN code 
    if(c1->pt()<pTthr1 || leps->at(il)->pt()<pTthr2) continue; 

    if(!passMllSingleVeto(c1, leps->at(il), 0, 8, false) && !bypassMV) continue;

    if((c1->charge()!=leps->at(il)->charge())!=os) continue;

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



vector<CandList>
SusyModule::buildSSPairs(const CandList* leps, bool byflav,
			 bool bypassMV, bool os, 
			 float pTthrMu, float pTthrEl,
			 vector<int>& idx1, vector<int>& idx2) {

  vector<CandList> clist;
  float pTthr1,pTthr2;

  for(unsigned int il1=0;il1<leps->size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps->size();il2++) {
      pTthr1 = (std::abs(leps->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      //conditional pt threshold, could evolve in CERN code 
      if(leps->at(il1)->pt()<pTthr1 || leps->at(il2)->pt()<pTthr2) continue; 
      //cout<<" cands => "<<leps->at(il2)->uid()<<endl;
      if(!passMllSingleVeto(leps->at(il1), leps->at(il2), 0, 8, false) && !bypassMV) continue;
      
      if( (leps->at(il1)->charge()!=leps->at(il2)->charge())!=os ) continue;
    
      CandList tmp(2,NULL);
     
      tmp[0]=leps->at(il1);
      tmp[1]=leps->at(il2);

      clist.push_back(tmp);

      idx1.push_back(il1);
      idx2.push_back(il2);
      
    }//il2
  }//il1

  return clist;
}


vector<CandList>
SusyModule::buildSSPairs(const CandList* leps1, const CandList* leps2, bool byflav,
			 bool bypassMV, bool os, float pTthrMu, float pTthrEl,
			 vector<int>& idx1, vector<int>& idx2) {

  //LISTS HAVE TO BE COMPLEMENTARY, NO OVERLAPS!

  vector<CandList> clist;
  float pTthr1,pTthr2;

  vector<InternalCList> iCList;

  for(unsigned int il1=0;il1<leps1->size();il1++) {
    for(unsigned int il2=0;il2<leps2->size();il2++) {
      
      pTthr1 = (std::abs(leps1->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps2->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      //conditional pt threshold, could evolve in CERN code 
      if(leps1->at(il1)->pt()<pTthr1 || leps2->at(il2)->pt()<pTthr2) continue; 
      if(!passMllSingleVeto(leps1->at(il1), leps2->at(il2), 0, 8, false) && !bypassMV) continue;
      if( (leps1->at(il1)->charge()!=leps2->at(il2)->charge())!=os ) continue;
      
      CandList tmp(2,NULL);
     
      tmp[0]=leps1->at(il1);
      tmp[1]=leps2->at(il2);

      InternalCList iclist;
      iclist.list = tmp;
      iclist.il1 = il1;
      iclist.il2 = il2;
      
      iCList.push_back(iclist);
    
    
    }//il2
  }//il1
  
  //ordering ================
  std::sort( iCList.begin(), iCList.end() );
  // if(iCList.size()>=2)
  //   cout<<" ===================== new pair ===================== "<<endl;
  for(unsigned int il=0;il<iCList.size();++il) {
    // if(iCList.size()>=2)
    //   cout<<" sorting pairs!!!!!! "<<il<<" -->  "<<iCList[il].list[0]->pdgId()
    // 	  <<"  "<<iCList[il].list[1]->pdgId()<<" --> "
    // 	  <<iCList[il].list[0]->pt()<<"  "<<iCList[il].list[1]->pt()<<endl;

    clist.push_back(iCList[il].list);
    idx1.push_back(iCList[il].il1);
    idx2.push_back(iCList[il].il2);
  }

  //=========================
  

  return clist;
}


double
SusyModule::closestJetPt(int idx, string branch) const {

  return _vc->get(branch + "_pt", idx) / _vc->get(branch + "_jetPtRatiov2", idx);

}


double
SusyModule::conePt(int idx, int isoWp, string branch) const {

  if(_vc->get(branch + "_jetPtRelv2", idx) > _multiIsoWP[kPtRel][isoWp] ) {
    return _vc->get(branch + "_pt", idx)*(1 + std::max((double) 0., _vc->get(branch + "_miniRelIso", idx) - _multiIsoWP[kMiniIso][isoWp] ) );
  }
  return std::max(_vc->get(branch + "_pt", idx), (double) closestJetPt(idx, branch) * _multiIsoWP[kPtRatio][isoWp] );

}

double
SusyModule::Mt(Candidate* c1, Candidate* c2, int idx1, int idx2, string branch1, string branch2, int isoWp) const {

  return rawMt(c1, c2);
  //return coneMt(idx1, isoWp, c2);

}

double
SusyModule::rawMt(Candidate* c1, Candidate* c2) const {

  return coneMt(c1, c2, -1, -1);

}

double
SusyModule::coneMt(Candidate* c1, Candidate* c2, int idx1, int idx2, string branch1, string branch2, int isoWp) const {

  float pt1 = c1 -> pt();
  float pt2 = c2 -> pt();
  if(idx1 > -1) pt1 = conePt(idx1, isoWp, branch1);
  if(idx2 > -1) pt2 = conePt(idx2, isoWp, branch2);

  return sqrt(2 * pt1 * pt2 * (1. - cos(Tools::AngleSubtraction( c1 -> phi(), c2 -> phi())))); 
  //return sqrt(2 * conePt(idx, isoWp) * met -> pt() * (1. - cos(Tools::AngleSubtraction(_vc->get("LepGood_phi", idx), met -> phi()))));

}

//double
//SusyModule::coneMt(int idx, Candidate* lep, Candidate* met) const {
//
//  int wp = kTight;
//  if(std::abs(lep->pdgId()) == 13) wp = kMedium;
//  return coneMt(idx, wp, met);
//
//}


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
SusyModule::cleanLeps(CandList& tightLeps, CandList* vetoLeps) {

  for(CandList::iterator it = tightLeps.begin(); it != tightLeps.end();) {
    int i = it - tightLeps.begin();
    if(!passMllMultiVeto( tightLeps[i], vetoLeps, 76, 106, true) ||
       !passMllMultiVeto( tightLeps[i], vetoLeps,  0,  12, true) ) 
      it = tightLeps.erase(it);
    else
      ++it;
  }
}


void
SusyModule::cleanJets(CandList* leptons, 
		      CandList& cleanJets, vector<unsigned int>& jetIdxs,
		      CandList& cleanBJets, vector<unsigned int>& bJetIdxs, float thr, float bthr ) {

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

    if(jets[ij]->pt()<bthr) continue;
    
    if(jets[ij]->pt()>thr) {
      cleanJets.push_back(jets[ij] );
      jetIdxs.push_back(ij);
    }
    
    if(bvals[ij]) continue;
    
    cleanBJets.push_back(jets[ij]);
    bJetIdxs.push_back(ij);
  } //loop jets

}


void
SusyModule::correctFlipRate(float& rate, float eta){

  if( -2.0 < eta && eta < -1.5) rate *= 3.6;
  else                          rate *= 1.15;

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

//float
//SusyModule::puWeight(int idx) {
//
//  if nVert >= 60: return 1.;
//  return _dbm -> getDBValue("PUdb", _vc->get("nVert")); 
//
//// put this stuff into the database:
////array = [1.0, 3.153000427291265, 2.4535501340758543, 2.353696182351581, 2.3718057802881676, 2.3508262193470397, 2.291773427755106, 2.129929297304804, 1.9422796094930384, 1.7126175249202766, 1.4622401225778663, 1.2063711142884181, 0.9608504360968657, 0.7484941355600901, 0.5769889517104192, 0.4315759540480359, 0.3195820162866148, 0.2306052595765186, 0.1691819686464576, 0.12324466445693416, 0.08833641123547825, 0.06306193566475429, 0.047857788612281564, 0.034655984107483044, 0.02358209210941948, 0.019535383939466185, 0.01500976654907348, 0.009407396052837736, 0.006332906010381258, 0.008524617116368491, 0.003145186350322339, 0.0, 0.0, 0.006930381551001214, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0] 
//
//
//}


float
SusyModule::bTagSF(string dbKeyEffB, string dbKeyEffL, string dbKeyCsv, 
                   CandList& jets , vector<unsigned int>& jetIdx ,
                   CandList& bJets, vector<unsigned int>& bJetIdx, int st){
  // put st = -1 / 0 / +1 for down / central / up

  float pdata = 1.0;
  float pmc   = 1.0;

  for(unsigned int i = 0; i < jets.size(); ++i) {
    if(find(bJetIdx.begin(), bJetIdx.end(), jetIdx[i]) != bJetIdx.end()){
      pdata *= bTagMediumEfficiency (dbKeyEffB, dbKeyEffL, jets[i], jetIdx[i], true) * 
               bTagMediumScaleFactor(dbKeyCsv            , jets[i], jetIdx[i], true, st);
      pmc   *= bTagMediumEfficiency (dbKeyEffB, dbKeyEffL, jets[i], jetIdx[i], true);
    }
    else {
      pdata *= (1 - bTagMediumEfficiency (dbKeyEffB, dbKeyEffL, jets[i], jetIdx[i], false) * 
                    bTagMediumScaleFactor(dbKeyCsv            , jets[i], jetIdx[i], false, st));
      pmc   *= (1 - bTagMediumEfficiency (dbKeyEffB, dbKeyEffL, jets[i], jetIdx[i], false));
    }
  }

  if(pmc != 0) return pdata/pmc;
  return 1.0;

}

float
SusyModule::bTagMediumEfficiency(string dbKeyB, string dbKeyLight, Candidate* jet, int jetIdx, bool isBTagged){

  if(isBTagged) return _dbm -> getDBValue(dbKeyB, jet -> pt(), std::abs(jet -> eta()));
  return _dbm -> getDBValue(dbKeyLight, jet -> pt(), std::abs(jet -> eta()));

} 

float
SusyModule::bTagMediumScaleFactor(string dbKey, Candidate* jet, int jetIdx, bool isBTagged, int st){

  //CH: this is not yet complete, for non-medium bTags, there are formula's to evaluate using pt and eta
  //float pt  = std::min( std::max(jet -> pt() , 30.001), 669.999);
  //float eta = std::min( std::max(jet -> eta(), -2.399),   2.399);

  if(isBTagged) return bTagScaleFactor(dbKey, 1, 0, st, 0); // mujets
  return bTagScaleFactor(dbKey, 1, 1, st, 2); // comb

} 


float
SusyModule::bTagScaleFactor(string dbKey, unsigned int op, unsigned int mt, int st, unsigned int fl){ 
  // op = 0 (loose), 1 (medium), 2 (tight)
  // mt = 0 (mujets), 1 (comb)
  // st = -1 (lower), 0 (central), +1 (upper)
  // fl = 0 (b), 1 (c), 2 (other)

  string mts = "mujets";
  if(mt == 1) mts = "comb";

  string sts = "central";
  if(st == -1) sts = "down";
  if(st ==  1) sts = "up";

  vector<pair<int, string> > sCheck;
  sCheck.push_back(pair<int, string>(1, mts));
  sCheck.push_back(pair<int, string>(2, sts));

  vector<pair<int, float> > fCheck;
  fCheck.push_back(pair<int, float>(0,   op));
  fCheck.push_back(pair<int, float>(3,   fl));
  fCheck.push_back(pair<int, float>(4, -2.4));
  fCheck.push_back(pair<int, float>(5,  2.4));
  fCheck.push_back(pair<int, float>(6,   30));
  fCheck.push_back(pair<int, float>(7,  670));

  return _dbm -> getDBValueCSV(dbKey, fCheck, sCheck, 10); 

}



