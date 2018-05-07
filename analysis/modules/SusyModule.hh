#ifndef SusyModule_hh
#define SusyModule_hh

#include "analysis/core/VarClass.hh"
#include "analysis/core/MPAF.hh"
#include "analysis/modules/BTagCalibrationStandalone.hh"
#include "analysis/modules/HLTEfficiency.hh"
#include "analysis/tools/Candidate.hh"
#include "analysis/utils/KineUtils.hh"
#include "analysis/utils/mt2_bisect.h"
//#include "analysis/utils/Tools.hh"
//#include "analysis/utils/Debug.cc"

#include "tools/src/DataBaseManager.hh"
#include "tools/src/SystUtils.hh"
#include <cmath>

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

  bool elHLTEmulSel(int idx, int withIso, const string& branch="LepGood", bool v1=false) const;
  bool elHLTEmulSelIso(int idx, int mvaWP = kLooseHT, string branch="LepGood") const;
  bool elIdSel(const Candidate* c, int idx, int wp, int mvaWp=kTight, bool chCut=true,
	       bool invSIP=false, bool LepMVA=false, string branch="LepGood") const;
  bool elMvaSel(int elIdx, int wp, string branch = "LepGood") const;
  bool muIdSel(const Candidate* c, int idx, int wp, bool chCut = true, bool invSIP = false, bool LepMVA = false, string branch="LepGood") const;

  bool lepMVAIdSel(int idx, int wp, string branch="LepGood") const;
  bool lepMVAIdAuxFakableSel(int idx, int pdgId, string branch="LepGood") const;
  
  void configureLeptonId(int idType); 
  bool muIdSelV2(const Candidate* c, int idx, const string& branch, int lvl, bool chCut, bool invSIP);
  bool elIdSelV2(const Candidate* c, int idx, const string& branch, int lvl, bool isoEmul, bool chCut, bool invSIP);
  bool muIdSelTTH(const Candidate* c, int idx, const string& branch, int lvl);
  bool elIdSelTTH(const Candidate* c, int idx, const string& branch, int lvl);

  bool muIdSelTTHClean(const Candidate* c, int idx, const string& branch);
  bool elIdSelTTHClean(const Candidate* c, int idx, const string& branch);

  bool multiIsoSel(int idx, int wp, string branch = "LepGood") const;
  bool multiIsoSelCone(int idx, int wp, string branch = "LepGood") const;
  bool multiIsoSelInSitu(int idx, int wp, string branch = "LepGood") const;
  bool inSituFO(int idx, int wp, string branch = "LepGood") const;
  bool invMultiIsoSel(int idx, int wp, string branch = "LepGood") const;
  bool invPtRelSel(int idx, int wp, string branch = "LepGood") const;

  bool jetSel(int jetIdx) const;
  float HT(const CandList* jets);
  float HT(const CandWrapList& jets);

  void awayJets(CandList* leptons, 
		 CandList& cleanJets, vector<pair<string, unsigned int> >& jetIdxs, float dR = 1.0);
  void cleanJets(CandList* leptons, 
		 CandList& cleanJets, vector<pair<string, unsigned int> >& jetIdxs,
		 CandList& cleanBJets, vector<pair<string,unsigned int> >& bJetIdxs,
		 CandList& lepJets, vector<pair<string,unsigned int> >& lepJetsIdxs,
		 float thr, float bthr, bool isJESUnc = false, int dir = 0);
  void ptJets(const CandList* allJets, const vector<pair<string, unsigned int> >& allJetIdxs,
              CandList& jets, vector<pair<string, unsigned int> >& jetIdxs, float thr = 40);

  void cleanLeps(CandList& tightLeps, CandList* vetoLeps);
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
  
  double closestJetPt(int idx, string branch = "LepGood") const;
  double conePt(int idx, int isoWp = kTight, string branch = "LepGood") const; 
  double Mt(Candidate* c1, Candidate* c2, int idx1 = -1, int idx2 = -1, string branch1 = "LepGood", string branch2 = "LepGood", int isoWp = kTight) const;
  double rawMt(Candidate* c1, Candidate* c2) const;
  double coneMt(Candidate* c1, Candidate* c2, int idx1 = -1, int idx2 = -1, string branch1 = "LepGood", string branch2 = "LepGood", int isoWp = kTight) const;

  void correctFlipRate(float& rate, float eta);


  double getLHEweight(int LHEsysID);
  void applyHLTSF(const string& hltLine, float& weight);
  void applyHLTSF(const string& hltLine, const vector<Candidate*>& cands, float& weight);
  void applyLepSF(const CandList& cands, float& weight);
  void applySingleLepSF(const Candidate* cand, float& weight);
  float getFastSimLepSF(Candidate* lep1, Candidate* lep2, int nVert);
  float applyLepSfRA7(const CandList& cands, int var=0);
  float applyFastSimLepSfRA7(const CandList& cands);
  float applyLepSfRA5(const Candidate* cand, bool isoHLT, int var=0);

  CandList findZCand(const CandList* leps, float window, float MTcut);
  float bTagSF(CandList& jets , vector<pair<string, unsigned int> >& jetIdx ,
               CandList& bJets, vector<pair<string, unsigned int> >& bJetIdx,
	       int st, bool fastSim=false, int fssf=0);
  float bTagSF(const CandWrapList& jets, const CandWrapList& bJets,
	       int st, bool fastSim=false, int fssf=0);
  float bTagMediumEfficiency(Candidate* jet, unsigned int flavor);
  float bTagMediumScaleFactor(Candidate* jet, unsigned int flavor, int st);
  float bTagMediumScaleFactorFastSim(Candidate* jet, unsigned int flavor, int st);
  float bTagPt(float);

  float GCtriggerScaleFactor(int pdgId1, int pdgId2, float pt1, float pt2, float ht);
  float GCelectronScaleFactorHighHT(float pt, float eta);
  float GCelectronScaleFactorLowHT(float pt, float eta);
  float GCmuonScaleFactor(float pt, float eta);
  float GCleptonScaleFactor(int pdgId, float pt, float eta, float ht);
  float GCeventScaleFactor(int pdgId1, int pdgId2, float pt1, float pt2, float eta1, float eta2, float ht);
  double LTFastSimTriggerEfficiency(double HT, double l1_Pt, int l1_pdgId, double l2_Pt, int l2_pdgId);

  float getVarWeightFastSimLepSF(const Candidate* l1, const Candidate* l2, int dir);
  float getVarWeightFastSimLepSFRA7(const CandList& cands, int dir);

  float getWeightFastSimHltSFRA7(const CandList& cands, float HT);
  float getVarWeightFastSimHltSFRA7(const CandList& cands, float HT, int dir);
  
  float getPuWeight(unsigned int nvtx);

  void applyISRWeight(unsigned int process, int var, float& weight);
  void applyISRJetWeight(const vector<pair<string, unsigned int> >& jetIdxs,
			 int var, const string& signame, bool isRA5, float& weight );

  float bTagSF(string dbKeyEffB, string dbKeyEffL, string dbKeyCsv,
               CandList& jets , vector<unsigned int>& jetIdx ,
               CandList& bJets, vector<unsigned int>& bJetIdx, int st);
  float bTagMediumEfficiency(string dbKeyB, string dbKeyLight, Candidate* jet, int jetIdx, bool isBTagged);
  float bTagMediumScaleFactor(string dbKey, Candidate* jet, int jetIdx, bool isBTagged, int st);
  float bTagScaleFactor(string dbKey, unsigned int op, unsigned int mt, int st, unsigned int fl);

  float btagCSVSF(const CandWrapList& jets, const string& unc, const int& dir);
  
  void applyHLTWeight(float pt1, float eta1, int pdgId1,
		    float pt2, float eta2, int pdgId2, 
		    float ht, float& weight, int var=0);
  void applyHLTWeightRA7(float pt1, float eta1, int pdgId1,
			 float pt2, float eta2, int pdgId2, 
			 float pt3, float eta3, int pdgId3, 
			 float ht, float& weight, int var=0);

  bool vetoFSBadJetEvent(bool isJESVar, int dir, const CandList& leptons);
  
  float getFSMETWeight(int wf, const string& sname, const string& sp,
		       bool isRA5, int var );

  void applyLeptonSF(float pt, float eta, float pdgId, 
		     bool isEmuIso, float& weight, int var=0);
  float getSingleSF(const string& db, float v1, float v2, int var);

  enum {kDenom=0,
	kVLoose,
	kInSitu,
	kInSituHT,
	kLoose,
	kLooseHT,
	kFakable,
	kMedium,
	kTight,
	kVTight,
	kSpecFakeEl,
	kSpecFakeMu,
	kNWPs};

  enum {kMiniIso=0,kPtRatio,kPtRel};
  enum {kEBC=0,kEBF,kEE};
  enum {kPt5,kPt10,kPt25,kVarWP};
  enum {kEl=0,kMu};
  enum {kVeryLooseMu=0, kLooseMu, kMediumMu, kTightMu, kVeryTightMu, kExtraTightMu, 
	kVeryLooseEl, kLooseEl, kMediumEl, kTightEl, kVeryTightEl, kExtraTightEl, kNULL};
  
  enum {kEtaMu=0, kEtaEl, kDxy, kDz, kSIP, kTCharge, kMVAMu, kMVAEl, kMIsoMu, kMIsoEl, 
	kLepIdMu, kLepIdEl, kConVeto, kLostHits, kEmulIso, kPtRatioVar, kCSV, kNVars};

  enum {kCB=0,kMVA};

private:

  void defineLeptonWPS();
  void loadBTagFastSimReader();
  void loadBTagReader();
  void loadBTagReaderCSVDisc();
  void loadDBs();
  void initPUWeights(); 

  void isrWeight(int var, float pt, float& weight);
  CandList collectGenParticles(int pdgId, int status);

 //const
  VarClass* _vc;
  DataBaseManager* _dbm;

  HLTEfficiency* _hltEff;

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

  BTagCalibration* _calibFS;
  BTagCalibrationReader* _readerFS_b_cv;
  BTagCalibrationReader* _readerFS_b_up;
  BTagCalibrationReader* _readerFS_b_do;
  BTagCalibrationReader* _readerFS_c_cv;
  BTagCalibrationReader* _readerFS_c_up;
  BTagCalibrationReader* _readerFS_c_do;
  BTagCalibrationReader* _readerFS_l_cv;
  BTagCalibrationReader* _readerFS_l_up;
  BTagCalibrationReader* _readerFS_l_do;

  BTagCalibration* _calibCSV;
  BTagCalibrationReader* _readerCSV;
  BTagCalibrationReader* _readerCSV_JESUp;
  BTagCalibrationReader* _readerCSV_JESDown;
  BTagCalibrationReader* _readerCSV_LFUp;
  BTagCalibrationReader* _readerCSV_LFDown;
  BTagCalibrationReader* _readerCSV_HFUp;
  BTagCalibrationReader* _readerCSV_HFDown;
  BTagCalibrationReader* _readerCSV_HFStats1Up;
  BTagCalibrationReader* _readerCSV_HFStats1Down;
  BTagCalibrationReader* _readerCSV_HFStats2Up;
  BTagCalibrationReader* _readerCSV_HFStats2Down;
  BTagCalibrationReader* _readerCSV_LFStats1Up;
  BTagCalibrationReader* _readerCSV_LFStats1Down;
  BTagCalibrationReader* _readerCSV_LFStats2Up;
  BTagCalibrationReader* _readerCSV_LFStats2Down;
  BTagCalibrationReader* _readerCSV_CFErr1Up;
  BTagCalibrationReader* _readerCSV_CFErr1Down;
  BTagCalibrationReader* _readerCSV_CFErr2Up;
  BTagCalibrationReader* _readerCSV_CFErr2Down;
   
  vector<float> _cLostHitWP;
  vector<float> _tChWP;
  vector<float> _dxyWP;
  vector<float> _dzWP;
  vector<float> _isoWP;
  vector<float> _miniIsoWP;
  vector<float> _ptRelWP;
  vector<float> _sipWP;
  vector<float> _sipWPLepMVA;
  vector<float> _muIdWP;
  vector<float> _lepMVAIdWP;

  vector<vector<float> > _lepIdWPs;

  vector<vector<vector<float> > > _elMvaIdWP;
  vector<vector<float> > _multiIsoWP;
  vector<vector<float> > _ptWP;

  vector<float> _puWeights;

};

#endif
