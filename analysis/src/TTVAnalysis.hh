#ifndef TTVAnalysis_HH
#define TTVAnalysis_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"


struct plotVar{
  std::string name;
  std::string leg;
  int nBins;
  float xmin;
  float xmax;

public:
  plotVar(std::string name_,
	  int nBins_,
	  float xmin_,
	  float xmax_,
	  std::string leg_) {
    name=name_;
    nBins=nBins_;
    xmin=xmin_;
    xmax=xmax_;
    leg=leg_;
  };
  
};

class TTVAnalysis: public MPAF {

public:

  // Member Functions

  TTVAnalysis(std::string);
  virtual ~TTVAnalysis();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();

  void modifySkimming();

  void clearEvent();

  void fillPlots();
  void fillLeptonControl(size_t il, const string& coll);

  void validationPlots();
  void fillValidationPlots();
  float getValue(const string& flag,const Candidate* c, int idx=0, const string& coll="");
  
  void makeObjectListFast(const string& coll,const string& nObjTag, const string& tag,
			  CandWrapList& listObj, bool isJESVar=false, int dir=0, bool full4V=true);

  void makeLeptonList(const string& coll, CandWrapList& list, CandWrapList& listFake);
  void cleanJets(CandWrapList* leptons, CandWrapList& cleanJets,
		 CandWrapList& cleanBJets, CandWrapList& lepJets,
		 float thr, float bthr, float etac, bool isJESVar, int dir );
  
  float getFR(Candidate* cand, int idx, const string& type);

  bool isPrompt();
  bool passHLLine(string line);

  CandList buildZCands(const CandWrapList& leps);
  CandList buildWCands(const CandWrapList& leps, Candidate* met);
  void sortZCandidate(CandList& zList);

  int getNNCateg( float nnWz, float nnTZq, float nnTZW, float nnTTH);
  int getNNCategV2( float nnWz, float nnTZq, float nnTZW, float nnTTH, int opt=15);
  int getNNCategV3( float nnWz, float nnTZq, float nnTZW, float nnTTH);

  int getNNCategFall17Separated( float nnWZ, float nnTZq);
  int getNNCategFall17MultiClassifier( float nnWZ, float nnTZq);
  
  void ttWAnalysis();
  void ttZAnalysis();
  void ttZAnalysisFast();
  
  bool selectionGhent();
  bool passGenSelection();
  bool passGenSelectionFast();
  bool genAcceptanceSelection(int targetGLep);
  void topSolver3Jplus(const CandWrapList& jets, const CandWrapList& bjets);

  bool passTriggerLine();

  int u(int x, int N);
  int u2(int x, int N);
  int nnMultiBin(float valTTZ, float valWZ, float valTZq, int N);

  void dumpEvents();

  bool HLTEmul(int idx, const string& branch);
  bool looseTTVLepton(int idx, const string& branch);

  bool looseId(const Candidate* c, int idx, const string& branch);
  bool fakableId(const Candidate* c, int idx, const string& branch);
  bool tightId(const Candidate* c, int idx, const string& branch);
  
  bool elIdSelTTHLoose(const Candidate* c, int idx, const string& branch);
  bool elIdSelTTHFakable(const Candidate* c, int idx, const string& branch);
  bool elIdSelTTHTight(const Candidate* c, int idx, const string& branch);

  bool muIdSelTTHLoose(const Candidate* c, int idx, const string& branch);
  bool muIdSelTTHFakable(const Candidate* c, int idx, const string& branch);
  bool muIdSelTTHTight(const Candidate* c, int idx, const string& branch);

  bool elIdSelTTZLoose(const Candidate* c, int idx, const string& branch);
  bool elIdSelTTZFakable(const Candidate* c, int idx, const string& branch);
  bool elIdSelTTZTight(const Candidate* c, int idx, const string& branch);
  
  bool muIdSelTTZLoose(const Candidate* c, int idx, const string& branch);
  bool muIdSelTTZFakable(const Candidate* c, int idx, const string& branch);
  bool muIdSelTTZTight(const Candidate* c, int idx, const string& branch);

  bool elMvaIdFall17(const Candidate*c, int idx, int wp);

  
  float conePt(const Candidate* c, int idx, const string& branch);
  float conePtIllia(float lpt, float leta, int flavor, float isolation);
  
private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0,kGlobalFake};
  
  enum {kNULL=0,kVsWZ,kVsTZq,kVsTZW,kVsTTH,kVsWZandTZq,kVsWZandTZW,kVsWZandTTH,kVsWZandTZqandTZWandTTH,kMulti};

  enum {kTTW=1, kTTZ=2};
  
  SusyModule* _susyMod;

  int _an;
  
  bool _sync;
  bool _valid;
  int _nnScheme;
  bool _lheSystComputation;
  bool _fastAnalysis;
  
  string _id;
  int _pickEvt;
  
  CandWrapList _allLeps;
  CandWrapList _leps;
  CandWrapList _fakables;

  CandWrapList _cleanJets;
  CandWrapList _cleanJets25;
  CandWrapList _cleanBJets;
  CandWrapList _cleanJetsEta5;
  CandWrapList _lepJets;

  int _nJets;
  
  CandList _zCands;

  Candidate* _met;
  
  float _HT;
  float _HT25;
  float _HTB;

  // vector<int> _jetIdx;
  int _lepWIdx;
  // vector<int> _lepZIdx;
  
  int _jetIdx[10];
  int _lepZIdx[2];

  float _btagW;  

  ofstream* _ofileDump;
  bool _dumpEvents;

  vector<string> _var4V;
  vector<string> _varLep;
  vector<string> _varZ;
  vector<string> _varW;
  vector<string> _varJet;
  
  vector<string> _trgLines;

};


#endif
