
#ifndef FakeRatioV2_HH
#define FakeRatioV2_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

#include <string>

#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooRealVar.h"

struct hltLine{

  std::string line;
  
  float ptMin;
  float etaMin;
  float ptMax;
  float etaMax;
  
  void setPts(float min, float max) {
    //cout<<" -->><> "<<min<<"  "<<max<<endl;
    ptMin=min;
    ptMax=max;
  };

  void setEtas(float min, float max) {
    etaMin=min;
    etaMax=max;
  }

  bool validPtBin(float ptm, float ptM) {
    //cout<<ptMin<<" / "<<ptMax<<"   <>  "<<ptm<<" / "<<ptM<<" :: "<<(ptm>=ptMin)<<"  "<<(ptm<ptMax)<<"  "<<(ptM<ptMax)<<endl;
    if(ptm>=ptMin && ptm<ptMax && ptM<=ptMax) return true;
    return false;
  }

  bool validEtaBin(float etam, float etaM) {
    // cout<<etaMin<<" / "<<etaMax<<"   <>  "<<etam<<" / "<<etaM<<" :: "<<(etam>=etaMin)<<"  "<<(etam<etaMax)<<"  "<<(etaM<etaMax)<<endl;
    if(etam>=etaMin && etam<etaMax && etaM<=etaMax) return true;
    return false;
  }

};



class FakeRatioV3: public MPAF {

public:


  // Member Functions
  FakeRatioV3(string);
  virtual ~FakeRatioV3();


private:

  void initialize();
  void reset();

  void defineOutput();
  void modifyWeight();
  void run();
  void writeOutput();
  void modifySkimming();

  void selectObjects();
  bool looseLepton(Candidate* c, int idx, const string& branch);
  bool fakableLepton(Candidate* c, int idx, const string& branch);
  bool tightLepton(Candidate* c, int idx, const string& branch);
  
  void initTriggerLines();
  void initVariables();
  void registerLepVars();
  void registerTriggerVars();

  bool baseSelection();
  bool triggerSelection();
  bool qcdSelection();
  bool ewkSelection();
  bool ucsxEwkSelection();
  bool mrSelection(float mtCut);

  void ZSelection();

  float overflowPt(float);

  void findTriggerPts();
  
  void fillPlots(const string& region);

private: 

  enum {kElN=0, kElI, kMuN, kMuI, kCats};
  
  enum { kEl=0, kMu, kNFlavs};
  
  //float _targetLumi;
  vector<string> _flavors;
  vector<string> _extsHLT;

  std::map<string,hltLine>::iterator _itHlt;
  vector<std::map<string,hltLine> > _hltLines; //categs, pt
  //vector<vector<string> > _hltPrescales;
  //vector<vector<float> > _hltEqLumi;
  vector<vector<float> > _hltPtBins;
  vector<vector<float> > _hltEtaBins;
  vector<vector<float> > _frPtBins;
  vector<vector<float> > _frEtaBins;
  vector<vector<vector<vector<string> > > > _hltLinesFR;
  
  vector<vector<string> > _hltSN;

  string _lepId;

  bool _controlPlots;
  bool _projPlots;

  bool _dumpEvent;
  bool _storeTrees;
 
  unsigned int _nDenLeps;
  unsigned int _nNumLeps;

  unsigned int _nDenMus;
  unsigned int _nDenEls;
 
  CandList _looseLeps;
  CandList _denLeps;
  CandList _numLeps;
 
  vector<unsigned int> _looseLepsIdx;
  vector<unsigned int> _denLepsIdx;
  vector<unsigned int> _numLepsIdx;
 
  bool _isIso;

  CandList _bJets;
  CandList _goodJets;
  CandList _lepJets;

  unsigned int _nJets;

  vector<pair<string, unsigned int> > _bJetsIdx;
  vector<pair<string, unsigned int> > _goodJetsIdx;
  vector<pair<string, unsigned int> > _lepJetsIdx;

  Candidate * _met;
  float _HT;
  float _mt;
  
  SusyModule* _susyMod;

  ofstream* _ofileDump;

  float _lepPt;
  float _lepEta;
  float _lepPhi;
  int   _lepPdgId;
  bool  _lepIso;
  float _lepAct;
  float _lepBTag;


};


#endif
