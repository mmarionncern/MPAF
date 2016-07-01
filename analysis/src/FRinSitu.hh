/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, CERN, Summer 2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef FRinSitu_HH
#define FRinSitu_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

class FRinSitu: public MPAF {

public:


  // Member Functions

  FRinSitu(std::string);
  virtual ~FRinSitu();


private:

  void initialize();

  void run();
  void defineOutput();
  void loadInput();
  void modifyWeight();
  void writeOutput();
  void modifySkimming();

  void divideFRMap(string postpend);
  void divideFRMaps();
  void registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis);
  void registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, string xaxis);
  void registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis);
  void registerLepVars();
  void registerTriggerVars();
  void registerVariable(string var, int nBin, float min, float max, string Xleg, bool isglb=true, bool prof=false, string type="m");
  void registerVariable(string var, int nBinX, float minX, float maxX, int nBinY, float minY, float maxY, string Xleg, string Yleg, bool isglb=true, bool prof=false, string type="m");
  void registerVariable(string var, int nBinX, vector<float> binsX, string Xleg, bool isglb=true, bool prof=false, string type="m");
  void registerVariable(string var, int nBinX, vector<float> binsX, int nBinY, vector<float> binsY, string Xleg, string Yleg, bool isglb=true, bool prof=false, string type="m");

  void sumMaps();
  void sumTriggers();
  void sumTriggerPlots(string obs, int ds, string ext);

  void collectKinematicObjects();
  void collectLeptons(int, string);

  bool cleanElectronSelection       (Candidate*, unsigned int, string);
  bool cleanMuonSelection           (Candidate*, unsigned int, string);
  bool denominatorElectronSelection (Candidate*, unsigned int, string);
  bool denominatorMuonSelection     (Candidate*, unsigned int, string);
  bool goodJetSelection             (unsigned int);
  bool numeratorElectronSelection   (Candidate*, unsigned int, string);
  bool numeratorMuonSelection       (Candidate*, unsigned int, string);
  bool signalRegionElectronSelection(Candidate*, unsigned int, string);
  bool signalRegionMuonSelection    (Candidate*, unsigned int, string);
  bool vetoElectronSelection        (Candidate*, unsigned int, string);
  bool vetoMuonSelection            (Candidate*, unsigned int, string);

  void setCut(std::string, float, std::string, float = 0); 
  void setMeasurementRegion();

  bool baseSelection();
  bool mrSelection();
  bool skimSelection();
  bool triggerSelection();

  void fillEventPlots();
  void fillLepPlots(std::string, Candidate*, pair<unsigned int, string>, int);
  void fillLeptonPlots();
  void fillFRMaps(std::string, pair<unsigned int, string>, int);
  void fillFakeRatioMaps();

  string findLepAbbr(Candidate*);
  string findLepAbbr(pair<unsigned int, string>);
  int findLepWP(Candidate*);
  int findLepWP(pair<unsigned int, string>);
  void findTriggerExts();
  bool genMatchedToFake(pair<unsigned int, string>);
  float overflowPt(float);

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later)
  enum {kGlobal=0, kTrigger, kDenEls, kDenMus, kNumEls, kNumMus, kSigEls, kSigMus, kVetEls, kVetMus, kClEls, kClMus, kGoodJets};

  enum {kNoGenMatch=0, kMisMatchPdgId,
	kMisChargePdgId, kGenMatched};

  float _vtxWeight;

  int _idx_data;
  int _idx_datacorrETH;
  int _idx_datacorrCERN;
  int _idx_ewk;
  int _idx_ewk_dy;
  int _idx_ewk_tt;
  int _idx_ewk_wj;
  int _idx_qcd;
  int _idx_qcd_em;
  int _idx_qcd_bc;
  int _idx_qcd_mu15;
  int _idx_qcd_mu5;

  vector<int> _idxs;
  vector<int> _idxsmc;

  bool _iso;
  vector<string> _TR_lines;
  vector<string> _exts;
  vector<float> _trws;
  
  vector<string> _vTR_lines_non;
  vector<string> _vTR_lines_iso;
  vector<string> _vTR_psb_non;
  vector<string> _vTR_psb_iso;
  vector<float> _vTR_efflum_non;
  vector<float> _vTR_efflum_iso;

  vector<float> _vFR_bins_pt_el;
  vector<float> _vFR_bins_pt_mu;
  vector<float> _vFR_bins_eta_el;
  vector<float> _vFR_bins_eta_mu;

  float _valCutHTSB;
  float _valCutMETSB;
  float _valCutHTCondSB;
  float _valCutMETHighSB;
  float _valCutMETLowSB;
  float _valCutNJetsSB;
  float _valCutNBJetsSB;

  std::string _cTypeHTSB;
  std::string _cTypeMETSB;
  std::string _cTypeHTCondSB;
  std::string _cTypeMETHighSB;
  std::string _cTypeMETLowSB;
  std::string _cTypeNJetsSB;
  std::string _cTypeNBJetsSB;

  float _upValCutHTSB;
  float _upValCutMETSB;
  float _upValCutHTCondSB;
  float _upValCutMETHighSB;
  float _upValCutMETLowSB;
  float _upValCutNJetsSB;
  float _upValCutNBJetsSB;
	
  std::vector<pair<unsigned int, string> > _denElsIdx;
  std::vector<pair<unsigned int, string> > _denLepsIdx;
  std::vector<pair<unsigned int, string> > _denMusIdx;
  std::vector<pair<unsigned int, string> > _isoLepsIdx;
  std::vector<pair<unsigned int, string> > _numElsIdx;
  std::vector<pair<unsigned int, string> > _numLepsIdx;
  std::vector<pair<unsigned int, string> > _numMusIdx;
  std::vector<pair<unsigned int, string> > _sigLepsIdx;
  std::vector<pair<unsigned int, string> > _vetLepsIdx;
  std::vector<pair<unsigned int, string> > _clLepsIdx;

  std::vector<pair<string, unsigned int> > _bJetsIdx;
  std::vector<pair<string, unsigned int> > _goodJetsIdx;
  std::vector<pair<string, unsigned int> > _lepJetsIdx;

  unsigned int _nDenEls;
  unsigned int _nDenLeps;
  unsigned int _nDenMus;
  unsigned int _nNumEls;
  unsigned int _nNumLeps;
  unsigned int _nNumMus;
  unsigned int _nSigLeps;
  unsigned int _nVetLeps;
  unsigned int _nClLeps;
  unsigned int _nGoodJets;
  unsigned int _nBJets;

  CandList _denEls;
  CandList _denLeps;
  CandList _denMus;
  CandList _numEls;
  CandList _numLeps;
  CandList _numMus;
  CandList _sigLeps;
  CandList _vetLeps;
  CandList _clLeps;

  CandList _bJets;
  CandList _goodJets;
  CandList _lepJets;

  Candidate * _met;
  Candidate * _lep1;
  Candidate * _lep2;

  pair<unsigned int, string> _lep1idx;
  pair<unsigned int, string> _lep2idx;
 
  float _HT;

  string _MR;
  string _norm;
  float _genMatching;

  string _bvar;
  string _nvert;
  vector<string> _leps;
  string _jets;
  string _djets;
  string _mets;

  SusyModule* _susyMod;

};


#endif
