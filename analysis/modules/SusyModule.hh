#ifndef SusyModule_hh
#define SusyModule_hh

#include "analysis/core/VarClass.hh"
#include "analysis/tools/Candidate.hh"
#include "analysis/utils/KineUtils.hh"
#include "analysis/utils/mt2_bisect.h"

#include "tools/src/DataBaseManager.hh"

struct InternalCList{
  CandList list;
  int il1;
  int il2;
  bool operator<(const InternalCList& b) const {
    int fla= std::abs(list[0]->pdgId()) + std::abs(list[1]->pdgId());
    float sta=list[0]->pt()+list[1]->pt();
    int flb= std::abs(b.list[0]->pdgId()) + std::abs(b.list[1]->pdgId());
    float stb=b.list[0]->pt()+b.list[1]->pt();
  
    //  cout<<flb<<"  "<<fla<<"     "<<sta<<"   "<<stb<<endl;

    if(flb>fla) return false;
    else if(flb==fla) {
      if(stb>sta) return false;
    }
    return true;
  };
};


class SusyModule {

public:

  SusyModule(VarClass* vc);
  SusyModule(VarClass* vc, DataBaseManager* dbm);
  ~SusyModule();

  
  bool elMvaSel(int elIdx, int wp) const;
  bool muIdSel(const Candidate* c, int idx, int wp, bool chCut=true) const;
  bool elIdSel(const Candidate* c, int idx, int wp, int mvaWp = kTight, bool chCut=true) const;
  bool elHLTEmulSel(int idx, bool withIso) const;
  bool multiIsoSel(int idx, int wp) const;
  bool multiIsoSelCone(int idx, int wp) const;
  bool invMultiIsoSel(int idx, int wp) const;
  bool jetSel(int jetIdx) const;
  float HT(const CandList* jets);

  void cleanJets(CandList* leptons, 
		 CandList& cleanJets, vector<unsigned int>& jetIdxs,
		 CandList& cleanBJets, vector<unsigned int>& bJetIdxs,
		 float thr, float bthr);

  bool mllVetoSelection(const Candidate* l1, const Candidate* l2,
			const CandList* allLeps) const ;
  bool mllLMGVeto(const Candidate* cand, const Candidate* veto) const;
  bool mllZVeto(const Candidate* cand, const Candidate* veto) const;
  
  bool passMllSingleVeto(const Candidate* c1, const Candidate* c2, 
			 float mllm, float mllM, bool ossf);
  bool passMllMultiVeto(const Candidate* c1, const CandList* cands, 
			float mllm, float mllM, bool ossf);
  
  CandList bestSSPair(const CandList* leps, bool byflav,
		      bool bypassMV, bool os, float pTthrMu, float pTthrEl,
		      int& idx1, int& idx2);
  CandList bestSSPair(const CandList* leps1, const CandList* leps2, bool byflav,
		      bool bypassMV, bool os, float pTthrMu, float pTthrEl,
		      int& idx1, int& idx2);
  CandList bestSSPair(Candidate* c1, const CandList* leps, bool byflav,
		      bool bypassMV, bool os, float pTthrMu, float pTthrEl,
		      int& idx1, int& idx2);
  vector<CandList> buildSSPairs(const CandList* leps, bool byflav,
				bool bypassMV, bool os, float pTthrMu, float pTthrEl,
				vector<int>& idx1, vector<int>& idx2);
  vector<CandList> buildSSPairs(const CandList* leps1, const CandList* leps2,bool byflav,
				bool bypassMV, bool os, float pTthrMu, float pTthrEl,
				vector<int>& idx1, vector<int>& idx2);
  
  float closestJetPt(int idx) const;
  float conePt(int idx, int isoWp = kTight) const; 

  void applyHLTSF(const string& hltLine, const vector<Candidate*>& cands, float& weight);
  void applyLepSF(const CandList& cands, float& weight);
  void applySingleLepSF(const Candidate* cand, float& weight);

  enum {kDenom=0,
	kVLoose,
	kLoose,
	kLooseHT,
	kMedium,
	kTight,
	kVTight,
	kSpecFakeEl,
	kSpecFakeMu,
	kNWPs};

  enum {kMiniIso=0,kPtRatio,kPtRel};
  enum {kEBC=0,kEBF,kEE};
  enum {kEl=0,kMu};

  

private:

  void defineLeptonWPS();
  void loadDBs();
  //const
  VarClass* _vc;
  DataBaseManager* _dbm;

  vector<float> _cLostHitWP;
  vector<float> _tChWP;
  vector<float> _dxyWP;
  vector<float> _dzWP;
  vector<float> _isoWP;
  vector<float> _miniIsoWP;
  vector<float> _ptRelWP;
  vector<float> _sipWP;
  vector<float> _muIdWP;

  vector<vector<float> > _elMvaIdWP;
  vector<vector<float> > _multiIsoWP;
  vector<vector<float> > _ptWP;

};

#endif
