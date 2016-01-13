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

#include <string>

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

  int findBin(vector<float> list, float value);
  unsigned int findTriggerIdx(vector<string> trigger_lines, string name);
  vector<vector<vector<string> > > findTriggerLines(vector<vector<string> > trigger_lines, vector<float> trigger_pts, vector<float> trigger_ets, \
                                                                                           vector<float> search_pts , vector<float> search_eta);
  vector<float> findTriggerPts(vector<vector<string> > trigger_lines, string name);
  void initialize();
  void loadLeptonId();
  void run();

  void defineOutput(); 
  void divideFRMap(string postpend);
  void divideFRMaps();
  void doEwkSub();
  vector<float> doubleFit(string ext, TH1* h_data, TH1* h_ewk, TH1* h_qcd, float hmin = 0, float hmax = 0); 
  void doubleFit(vector<float>& scales, string ext, TH1* h_data, TH1* h_ewk, TH1* h_qcd, float hmin = 0, float hmax = 0); 
  float errorProp(float central1, float central2, float error1, float error2);
  vector<float> getScalesETH (string obs, float lumi);
  vector<float> getScalesUCSX(string obs, float lumi);
  vector<float> getScalesUCSXlite(string obs, float lumi);
  void modifySkimming();
  void modifyWeight();
  vector<float> prepareHists(TH1* h_data, TH1* h_ewk, TH1* h_qcd);
  void registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis);
  void registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, string xaxis);
  void registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis);
  void registerLepVars();
  void registerTriggerVars();
  void registerVariable(string var, int nBin, float min, float max, string Xleg, bool isglb=true, bool prof=false, string type="m");
  void registerVariable(string var, int nBinX, float minX, float maxX, int nBinY, float minY, float maxY, string Xleg, string Yleg, bool isglb=true, bool prof=false, string type="m");
  void registerVariable(string var, int nBinX, vector<float> binsX, string Xleg, bool isglb=true, bool prof=false, string type="m");
  void registerVariable(string var, int nBinX, vector<float> binsX, int nBinY, vector<float> binsY, string Xleg, string Yleg, bool isglb=true, bool prof=false, string type="m");
  void setBinErrors(TH1*, TH1*, TH1*);
  void setSystematics();
  void setSystError(string obs, string postfix, int idx);
  float singleFit(string ext, TH1* h_data, TH1* h_mc, float hmin = 0, float hmax = 0);
  void singleFit(vector<float>& scales, string ext, TH1* h_data, TH1* h_mc, float hmin = 0, float hmax = 0);
  void subtractEwk(TH1* d, TH1* e, vector<float> scales, string obs, string postfix, int idx);
  //void subtractEwkStat(TH1* d, TH1* e, vector<float> scales, string obs, string postfix, int idx);
  //void subtractEwkSyst(TH1* d, TH1* e, vector<float> scales);
  void subtractPlots(string lep, int idx, vector<float> scales, string postfix);
  void subtractPlotsCERN(string lep, int idx, string postfix);
  void subtractPromptsCERN();
  void subtractPromptsETH();
  void subtractPromptsUCSX();
  void sumMaps();
  void sumTriggers();
  void sumTriggerPlots(string obs, int ds, string ext);
  void writeOutput();

  void collectKinematicObjects();
  void collectLeptons(int, string);
  bool denominatorElectronSelection(Candidate*, int, string);
  bool denominatorMuonSelection    (Candidate*, int, string);
  bool numeratorElectronSelection  (Candidate*, int, string);
  bool numeratorMuonSelection      (Candidate*, int, string);

  void setCut(std::string, float, std::string, float = 0);
  void setMeasurementRegion();

  bool baseSelection();
  bool ewkSelection();
  bool mrSelection();
  bool qcdSelection();
  bool skimSelection();
  bool triggerSelection();
  bool triggerSelectionLite();
  bool ucsxEwkSelection();

  void fillEventPlots();
  void fillEwkEventPlots();
  void fillEwkLepPlots(std::string, Candidate*, int, string, int = SusyModule::kTight);
  void fillEwkLeptonPlots();
  void fillFakeRatioMaps();
  void fillFRMaps(std::string, Candidate*, int, string, int = SusyModule::kTight);
  void fillLepPlots(std::string, Candidate*, int, string, int = SusyModule::kTight);
  void fillLeptonPlots();
  void fillJetPlots();
  void fillQcdEventPlots();
  void fillQcdFakeRatioMaps();
  void fillQcdLepPlots(std::string, Candidate*, int, string, int = SusyModule::kTight);
  void fillQcdLeptonPlots();
  void fillUcsxEwkEventPlots();
  void fillUcsxEwkLepPlots(std::string, Candidate*, int, string, int = SusyModule::kTight);
  void fillUcsxEwkLeptonPlots();
  void findTriggerExts();
  float overflowPt(float);
  void eventListSyncRA5();

  void testEwkSub();
  bool triggerEmulation(int idx, int label);
  void fillTriggerTestPlots();
  vector<int> findTriggerIdxs();


private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0, kEwkSel, kUcsSel, kQcdSel, kTrigger, kSync, kDenEls, kDenMus, kNumEls, kNumMus, kVetEls, kVetMus, kGoodJets};

  enum {kElIdWP, kElIsoWP, kElMvaWP, kElChCut, kElTrEmu, kMuIdWP, kMuIsoWP, kMuChCut};

  enum {kNoGenMatch=0, kMisMatchPdgId,
	kMisChargePdgId, kGenMatched};

  vector<int> _id;

  float _vtxWeight;

  int _idx_data;
  int _idx_datacorrETH;
  int _idx_datacorrUCSX;
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

  bool _trel;
  bool _trmu;
  bool _iso;
  vector<string> _TR_lines;
  vector<string> _exts;
  vector<float> _trws;
  int _TR_idx;

  vector<vector<string> > _vTR_lines_el_non;
  vector<vector<string> > _vTR_lines_el_iso;
  vector<vector<string> > _vTR_lines_mu_non;
  vector<vector<string> > _vTR_lines_mu_iso;
  vector<string> _vTR_psbh_el_non;
  vector<string> _vTR_psbh_el_iso;
  vector<string> _vTR_psbh_mu_non;
  vector<string> _vTR_psbh_mu_iso;
  vector<string> _vTR_psbl_el_non;
  vector<string> _vTR_psbl_el_iso;
  vector<string> _vTR_psbl_mu_non;
  vector<string> _vTR_psbl_mu_iso;
  vector<float> _vTR_efflum_el_non;
  vector<float> _vTR_efflum_el_iso;
  vector<float> _vTR_efflum_mu_non;
  vector<float> _vTR_efflum_mu_iso;
  vector<float> _vTR_bins_pt_el_non;
  vector<float> _vTR_bins_pt_el_iso;
  vector<float> _vTR_bins_pt_mu_non;
  vector<float> _vTR_bins_pt_mu_iso;
  vector<float> _vTR_bins_eta_el;
  vector<float> _vTR_bins_eta_mu;
  vector<float> _vFR_bins_pt_el;
  vector<float> _vFR_bins_pt_mu;
  vector<float> _vFR_bins_eta_el;
  vector<float> _vFR_bins_eta_mu;
  vector<vector<vector<string> > > _vTR_lineperpteta_el_non;
  vector<vector<vector<string> > > _vTR_lineperpteta_el_iso;
  vector<vector<vector<string> > > _vTR_lineperpteta_mu_non;
  vector<vector<vector<string> > > _vTR_lineperpteta_mu_iso;

  string _idS;
  string _norm;
  string _ewkSub;
  string _ewkMet;
  bool _doEwkSubCERN;
  bool _doEwkSubETH;
  bool _doEwkSubUCSX;

  float _valCutNBJetsMR;
  std::string _cTypeNBJetsMR;
  float _upValCutNBJetsMR;

  unsigned int _nDenEls;
  unsigned int _nDenLeps;
  unsigned int _nDenMus;
  unsigned int _nNumEls;
  unsigned int _nNumLeps;
  unsigned int _nNumMus;
  unsigned int _nVetEls;
  unsigned int _nVetLeps;
  unsigned int _nVetMus;
  unsigned int _nJets;

  CandList _denEls;
  CandList _denLeps;
  CandList _denMus;
  CandList _numEls;
  CandList _numLeps;
  CandList _numMus;
  CandList _vetEls;
  CandList _vetLeps;
  CandList _vetMus;

  vector<pair<unsigned int, string> > _denElsIdx;
  vector<pair<unsigned int, string> > _denLepsIdx;
  vector<pair<unsigned int, string> > _denMusIdx;
  vector<pair<unsigned int, string> > _numElsIdx;
  vector<pair<unsigned int, string> > _numLepsIdx;
  vector<pair<unsigned int, string> > _isoLepsIdx;
  vector<pair<unsigned int, string> > _numMusIdx;
  vector<pair<unsigned int, string> > _vetElsIdx;
  vector<pair<unsigned int, string> > _vetLepsIdx;
  vector<pair<unsigned int, string> > _vetMusIdx;

  CandList _bJets;
  CandList _goodJets;
  CandList _lepJets;

  vector<pair<string, unsigned int> > _bJetsIdx;
  vector<pair<string, unsigned int> > _goodJetsIdx;
  vector<pair<string, unsigned int> > _lepJetsIdx;

  Candidate * _met;
  float _HT;

  string _bvar;
  string _nvert;
  vector<string> _leps;
  string _jets;
  string _djets;
  string _mets;

  SusyModule* _susyMod;

};


#endif
