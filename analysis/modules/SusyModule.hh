#ifndef SusyModule_hh
#define SusyModule_hh

#include "analysis/core/VarClass.hh"
#include "analysis/modules/BTagCalibrationStandalone.hh"
#include "analysis/tools/Candidate.hh"
#include "analysis/utils/KineUtils.hh"
#include "analysis/utils/mt2_bisect.h"

#include "tools/src/DataBaseManager.hh"
#include "tools/src/SystUtils.hh"

struct InternalCList{
  CandList list;
  int il1;
  int il2;
  bool operator<(const InternalCList& b) const {
    int fla= std::abs(list[0]->pdgId()) + std::abs(list[1]->pdgId());
    float sta=list[0]->pt()+list[1]->pt();
    int flb= std::abs(b.list[0]->pdgId()) + std::abs(b.list[1]->pdgId());
    float stb=b.list[0]->pt()+b.list[1]->pt();
  
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
  bool muIdSel(const Candidate* c, int idx, int wp, bool chCut=true ) const;
  bool elIdSel(const Candidate* c, int idx, int wp, int mvaWp = kTight, bool chCut=true ) const;
  bool elHLTEmulSel(int idx, bool withIso) const;
  bool multiIsoSel(int idx, int wp) const;
  bool multiIsoSelCone(int idx, int wp) const;
  bool invMultiIsoSel(int idx, int wp) const;
  bool jetSel(int jetIdx) const;
  float HT(const CandList* jets);

  void cleanJets(CandList* leptons, 
		 CandList& cleanJets, vector<pair<string, unsigned int> >& jetIdxs,
		 CandList& cleanBJets, vector<pair<string,unsigned int> >& bJetIdxs,
		 CandList& lepJets, vector<pair<string,unsigned int> >& lepJetsIdxs,
		 float thr, float bthr, bool isJESUnc, int dir);
  void ptJets(CandList allJets, vector<pair<string, unsigned int> > allJetIdxs,
              CandList& jets, vector<pair<string, unsigned int> >& jetIdxs, float thr);

  const Candidate* jetLepAware(const Candidate* lep);
  float pTRatio(const Candidate* lep, const Candidate* jet);
  float pTRel(const Candidate* lep, const Candidate* jet);

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
  vector<CandList> buildSSPairs(const CandList* leps, vector<unsigned int> idxs, bool byflav,
				bool bypassMV, bool os, float pTthrMu, float pTthrEl,
				vector<int>& idx1, vector<int>& idx2);
  vector<CandList> buildSSPairs(const CandList* leps1, const CandList* leps2,
				vector<unsigned int> idxs1,
				vector<unsigned int> idxs2,
				bool byflav,
				bool bypassMV, bool os, float pTthrMu, float pTthrEl,
				vector<int>& idx1, vector<int>& idx2);
  
  float closestJetPt(int idx) const;
  float conePt(int idx, int isoWp = kTight) const; 

  void correctFlipRate(float& rate, float eta);

  double getLHEweight(int LHEsysID);
  void applyHLTSF(const string& hltLine, float& weight);
  void applyHLTSF(const string& hltLine, const vector<Candidate*>& cands, float& weight);
  void applyLepSF(const CandList& cands, float& weight);
  void applySingleLepSF(const Candidate* cand, float& weight);
  float getFastSimLepSF(Candidate* lep1, Candidate* lep2, int nVert);


  float bTagSF(CandList& jets , vector<pair<string, unsigned int> >& jetIdx ,
               CandList& bJets, vector<pair<string, unsigned int> >& bJetIdx, int st);
  float bTagMediumEfficiency(Candidate* jet, unsigned int flavor);
  float bTagMediumScaleFactor(Candidate* jet, unsigned int flavor, int st);
  float bTagScaleFactor(unsigned int op, unsigned int mt, int st, unsigned int fl);
  float bTagPt(float);

  float GCtriggerScaleFactor(int pdgId1, int pdgId2, float pt1, float pt2, float ht);
  float GCelectronScaleFactorHighHT(float pt, float eta);
  float GCelectronScaleFactorLowHT(float pt, float eta);
  float GCmuonScaleFactor(float pt, float eta);
  float GCleptonScaleFactor(int pdgId, float pt, float eta, float ht);
  float GCeventScaleFactor(int pdgId1, int pdgId2, float pt1, float pt2, float eta1, float eta2, float ht);
  double LTFastSimTriggerEfficiency(double HT, double l1_Pt, int l1_pdgId, double l2_Pt, int l2_pdgId);

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
  void loadBTagReader();
  void loadDBs();
  //const
  VarClass* _vc;
  DataBaseManager* _dbm;

  BTagCalibration* _calib;
  BTagCalibrationReader* _reader_b_cv;
  BTagCalibrationReader* _reader_b_up;
  BTagCalibrationReader* _reader_b_do;
  BTagCalibrationReader* _reader_c_cv;
  BTagCalibrationReader* _reader_c_up;
  BTagCalibrationReader* _reader_c_do;
  BTagCalibrationReader* _reader_l_cv;
  BTagCalibrationReader* _reader_l_up;
  BTagCalibrationReader* _reader_l_do;

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
