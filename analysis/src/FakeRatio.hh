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

#ifndef FakeRatio_HH
#define FakeRatio_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooRealVar.h"

class FakeRatio: public MPAF {

public:


  // Member Functions

  FakeRatio(string);
  virtual ~FakeRatio();


private:

  void initialize();
  void run();

  void defineOutput(); 
  void divideFRMap(string postpend);
  void divideFRMaps();
  void doEwkSub();
  vector<float> doubleFit(TH1* h_data, TH1* h_ewk, TH1* h_qcd, float hmin = 0, float hmax = 0); 
  void modifySkimming();
  void modifyWeight();
  void registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis);
  void registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis);
  float singleFit(TH1* h_data, TH1* h_mc, float hmin = 0, float hmax = 0);
  void subtractPrompts();
  void sumMaps();
  void writeOutput();

  void collectKinematicObjects();
  bool goodJetSelection(int);
  bool denominatorElectronSelection(int);
  bool denominatorMuonSelection(int);
  bool numeratorElectronSelection(int);
  bool numeratorMuonSelection(int);
  bool vetoElectronSelection(int);
  bool vetoMuonSelection(int);

  void setCut(std::string, float, std::string, float = 0);
  void setMeasurementRegion();

  bool ewkSelection();
  bool mrSelection();
  bool skimSelection();

  void fillEwkLepPlots(std::string, Candidate*, int, int = SusyModule::kTight);
  void fillEwkLeptonPlots();
  void fillEventPlots();
  void fillLepPlots(std::string, Candidate*, int, int = SusyModule::kTight);
  void fillLeptonPlots();
  void fillJetPlots();
  void fillFRMaps(std::string, Candidate*, int, int = SusyModule::kTight);
  void fillFakeRatioMaps();

  float overflowPt(float);

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0, kEwkSel, kDenEls, kDenMus, kNumEls, kNumMus, kVetEls, kVetMus, kGoodJets};

  enum {kNoGenMatch=0, kMisMatchPdgId,
	kMisChargePdgId, kGenMatched};

  int _idx_data;
  int _idx_datacorr;
  int _idx_ewk;
  int _idx_qcd;

  float _lumi;
  bool _doEwkSub;

  float _valCutNBJetsMR;
  std::string _cTypeNBJetsMR;
  float _upValCutNBJetsMR;

  int _nDenEls;
  int _nDenLeps;
  int _nDenMus;
  int _nNumEls;
  int _nNumLeps;
  int _nNumMus;
  int _nVetEls;
  int _nVetLeps;
  int _nVetMus;
  int _nJets;

  CandList _denEls;
  CandList _denLeps;
  CandList _denMus;
  CandList _numEls;
  CandList _numLeps;
  CandList _numMus;
  CandList _vetEls;
  CandList _vetLeps;
  CandList _vetMus;
  CandList _goodJets;

  vector<int> _denElsIdx;
  vector<int> _denLepsIdx;
  vector<int> _denMusIdx;
  vector<int> _numElsIdx;
  vector<int> _numLepsIdx;
  vector<int> _numMusIdx;
  vector<int> _vetElsIdx;
  vector<int> _vetLepsIdx;
  vector<int> _vetMusIdx;

  Candidate * _met;
  float _HT;

  string _bvar;
  string _nvert;
  string _leps;
  string _jets;
  string _mets;

  SusyModule* _susyMod;

};


#endif
