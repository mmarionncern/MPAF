/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, Matthieu Marionneau                                **
** CERN, Fall 2014                                                          **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/


#include "analysis/src/FakeRatio.hh"





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
FakeRatio::FakeRatio(std::string cfg){
  /* 
     constructs the FakeRatio class 
     parameters: configuration_file
     return: none
  */
  
  startExecution(cfg);
  initialize();

}


//____________________________________________________________________________
FakeRatio::~FakeRatio(){
  /* 
     destructs the FakeRatio class 
     parameters: none
     return: none
  */

}


//____________________________________________________________________________
void FakeRatio::initialize(){
  /*
    initializes the FakeRatio class
    parameters: none
    return: none
  */

  //Tree Variables
  _bvar  = "nBJetMedium25";
  _leps  = "LepGood";
  _jets  = "Jet"; 
  _mets  = "met";
  _nvert = "nVert";

  //Tree Branches
  _vc->registerVar("run"                           );
  _vc->registerVar("lumi"                          );
  _vc->registerVar("evt"                           );
  _vc->registerVar("HLT_SingleMu"                  );
  _vc->registerVar("HLT_MuEG"                      );
  _vc->registerVar("HLT_TripleEl"                  );
  _vc->registerVar("HLT_DoubleEl"                  );
  _vc->registerVar("HLT_DoubleMu"                  );
  _vc->registerVar(_nvert                          );
  _vc->registerVar("nTrueInt"                      );
  _vc->registerVar("puWeight"                      );
  _vc->registerVar("genWeight"                     );
  _vc->registerVar("n" + _leps                     );
  _vc->registerVar(_leps + "_pt"                   );
  _vc->registerVar(_leps + "_eta"                  );
  _vc->registerVar(_leps + "_phi"                  );
  _vc->registerVar(_leps + "_charge"               );
  _vc->registerVar(_leps + "_tightCharge"          );
  _vc->registerVar(_leps + "_mediumMuonId"         );
  _vc->registerVar(_leps + "_mvaIdPhys14"          );
  _vc->registerVar(_leps + "_pdgId"                );
  _vc->registerVar(_leps + "_relIso03"             );
  _vc->registerVar(_leps + "_relIso04"             );
  _vc->registerVar(_leps + "_jetPtRatio"           );
  _vc->registerVar(_leps + "_jetPtRel"             );
  _vc->registerVar(_leps + "_miniRelIso"           );
  _vc->registerVar(_leps + "_dxy"                  );
  _vc->registerVar(_leps + "_dz"                   );
  _vc->registerVar(_leps + "_sip3d"                );
  _vc->registerVar(_leps + "_pfMuonId"             );
  _vc->registerVar(_leps + "_tightId"              );
  _vc->registerVar(_leps + "_looseIdSusy"          );
  _vc->registerVar(_leps + "_convVeto"             );
  _vc->registerVar(_leps + "_lostHits"             );
  _vc->registerVar(_leps + "_eleCutIdCSA14_50ns_v1");
  _vc->registerVar(_leps + "_eleCutIdCSA14_50ns_v1");
  _vc->registerVar(_leps + "_eleCutId2012_full5x5" );
  _vc->registerVar(_leps + "_mvaSusyPHYS14"        );
  _vc->registerVar(_leps + "_mvaSusy"              );
  _vc->registerVar(_leps + "_mcMatchId"            );
  _vc->registerVar(_leps + "_mcMatchAny"           );
  _vc->registerVar(_leps + "_jetBTagCSV"           );
  _vc->registerVar(_leps + "_sigmaIEtaIEta"        );
  _vc->registerVar(_leps + "_hadronicOverEm"       );
  _vc->registerVar(_leps + "_eInvMinusPInv"        );
  _vc->registerVar(_leps + "_dEtaScTrkIn"          );
  _vc->registerVar(_leps + "_dPhiScTrkIn"          );
  _vc->registerVar(_mets + "_pt"                   );
  _vc->registerVar(_mets + "_eta"                  );
  _vc->registerVar(_mets + "_phi"                  );
  _vc->registerVar(_mets + "_mass"                 );
  _vc->registerVar("n" + _jets                     );
  _vc->registerVar(_jets + "_id"                   );
  _vc->registerVar(_jets + "_pt"                   );
  _vc->registerVar(_jets + "_rawPt"                );
  _vc->registerVar(_jets + "_eta"                  );
  _vc->registerVar(_jets + "_phi"                  );
  _vc->registerVar(_jets + "_mass"                 );
  _vc->registerVar(_jets + "_btagCSV"              );
  
  //generator informations
  _vc->registerVar("nGenPart"                      );
  _vc->registerVar("GenPart_pt"                    );
  _vc->registerVar("GenPart_eta"                   );
  _vc->registerVar("GenPart_phi"                   );
  _vc->registerVar("GenPart_pdgId"                 );
  _vc->registerVar("GenPart_motherId"              );
  _vc->registerVar("GenPart_grandmotherId"         );

  _vc->registerVar("nGenBHad"                      );
  _vc->registerVar("GenBHad_pt"                    ); 
  _vc->registerVar("GenBHad_eta"                   ); 
  _vc->registerVar("GenBHad_phi"                   ); 
  _vc->registerVar("GenBHad_pdgId"                 ); 
 
  //bjets
  _vc->registerVar("nBJetLoose25"                  );
  _vc->registerVar("nBJetMedium40"                 );
  _vc->registerVar("nBJetMedium25"                 );
  _vc->registerVar("nSoftBJetMedium25"             );

  //additional counter categories
  _au->addCategory( kEwkSel  , "Ewk Enriched MR Sel"  );
  _au->addCategory( kDenEls  , "Denominator Electrons");
  _au->addCategory( kNumEls  , "Numerator Electrons"  );
  _au->addCategory( kVetEls  , "Veto Electrons"       );
  _au->addCategory( kDenMus  , "Denominator Muons"    );
  _au->addCategory( kNumMus  , "Numerator Muons"      );
  _au->addCategory( kVetMus  , "Veto Muons"           );
  _au->addCategory( kGoodJets, "Good Jets"            );

  //SusyModule
  _susyMod = new SusyModule(_vc);

  //Databases
  _dbm -> loadDb("XS", "XSectionsSpring15.db");  

  //input Variables
  _lumi   = getCfgVarF("LUMINOSITY");
  _ewkSub = getCfgVarS("EWKSUB"); // all, el, mu

  //default Variables
  _doEwkSub = false;

}


//____________________________________________________________________________
void FakeRatio::run(){


  _denEls .clear();
  _denLeps.clear();
  _denMus .clear();
  _numEls .clear();
  _numLeps.clear();
  _numMus .clear();
  _vetEls .clear();
  _vetLeps.clear();
  _vetMus .clear();

  _goodJets.clear();

  _denElsIdx .clear();
  _denLepsIdx.clear();
  _denMusIdx .clear();
  _numElsIdx .clear();
  _numLepsIdx.clear();
  _numMusIdx .clear();

  counter("denominator");
  counter("denominator", kEwkSel);

	
  // prepare event selection
  collectKinematicObjects();
	
	
  // skimming
  //if(!skimSelection()) return;
  //fillSkimTree();
  //return;

  // ewk-enriched measurement region selection
  if(ewkSelection()) {
    fillEwkEventPlots();
    fillEwkLeptonPlots();
  }


  // measurement region selection
  if(!mrSelection()) return;

	
  // calling the modules
  fillEventPlots   ();
  fillFakeRatioMaps();
  fillJetPlots     ();
  fillLeptonPlots  ();

	
}



/*****************************************************************************
******************************************************************************
** DEFINE INPUTS AND OUTPUTS                                                **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::defineOutput(){
  /*
    defines and reserves all output that is produced in this class
    parameters: none
    return: none
  */ 


  // bins
  float FR_bins_eta_el[4] = { 0.0, 1.0, 2.0, 2.5};
  float FR_bins_eta_mu[4] = { 0.0, 1.0, 2.0, 2.4};
  float FR_bins_pt[6]     = {10.0, 15.0, 25.0, 35.0, 50.0, 70.0};

  vector<float> bins_eta_el = Tools::toVector(FR_bins_eta_el);
  vector<float> bins_eta_mu = Tools::toVector(FR_bins_eta_mu);
  vector<float> bins_pt     = Tools::toVector(FR_bins_pt    );

  // leptons
  string MR_els[3]  = {"MR_DenEl", "MR_NumEl", "MR_RatEl"};
  string MR_leps[4] = {"MR_DenEl", "MR_NumEl", "MR_DenMu", "MR_NumMu"};
  string MR_mus[3]  = {"MR_DenMu", "MR_NumMu", "MR_RatMu"};

  vector<string> els  = Tools::toVector(MR_els);
  vector<string> leps = Tools::toVector(MR_leps);
  vector<string> mus  = Tools::toVector(MR_mus);


  // Setting Measurement Region
  setMeasurementRegion();

  // Special feature of this class: it produces FR maps for 'data', 'datacorr', 'ewk', 'qcd'
  _hm -> addDataset("data");
  _hm -> addDataset("datacorr");
  _hm -> addDataset("ewk");
  _hm -> addDataset("qcd");
  _idx_data     = _numDS;
  _idx_datacorr = _numDS+1;
  _idx_ewk      = _numDS+2;
  _idx_qcd      = _numDS+3;

  // Measurement Region
  _hm->addVariable("MR_HT"         , 1000,   0.0, 1000.0, "H_T [GeV]"                            ); 
  _hm->addVariable("MR_HTinvMET"   , 1000,   0.0, 1000.0, "H_T [GeV]"                            ); 
  _hm->addVariable("MR_MET"        , 1000,   0.0, 1000.0, "#slash{E}_T [GeV]"                    );
  _hm->addVariable("MR_METinvMET"  , 1000,   0.0, 1000.0, "#slash{E}_T [GeV]"                    );
  _hm->addVariable("MR_NumJets"    ,   20,   0.0,   20.0, "jet multiplicity"                     );
  _hm->addVariable("MR_NumBJets"   ,   20,   0.0,   20.0, "b-jet multiplicity"                   );
  _hm->addVariable("MR_NumDenEls"  ,   20,   0.0,   20.0, "denominator electron multiplicity"    );
  _hm->addVariable("MR_NumDenLeps" ,   20,   0.0,   20.0, "denominator lepton multiplicity"      );
  _hm->addVariable("MR_NumDenMus"  ,   20,   0.0,   20.0, "denominator muon multiplicity"        );
  _hm->addVariable("MR_NumNumEls"  ,   20,   0.0,   20.0, "numerator electron multiplicity"      );
  _hm->addVariable("MR_NumNumLeps" ,   20,   0.0,   20.0, "numerator lepton multiplicity"        );
  _hm->addVariable("MR_NumNumMus"  ,   20,   0.0,   20.0, "numerator muon multiplicity"          );
  _hm->addVariable("MR_NumVrtx"    ,   40,   0.0,   40.0, "vertex multiplicity"                  );
  _hm->addVariable("MR_JetCSVBTag" ,   50,   0.0,    1.0, "jet CSV B-Tag"                        );
  _hm->addVariable("MR_JetPt"      , 1000,   0.0, 1000.0, "P_T(jet) [GeV]"                       );

  registerLepPlots(leps, "DXY"          , 5000, 0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(leps, "DXYinvMET"    , 5000, 0.0,   10.0, "#||{dxy}(lep) [cm]"                   );
  registerLepPlots(leps, "DZ"           , 5000, 0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(leps, "DZinvMET"     , 5000, 0.0,   10.0, "#||{dz}(lep) [cm]"                    );
  registerLepPlots(leps, "SIP"          , 1000, 0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(leps, "SIPinvMET"    , 1000, 0.0,   10.0, "SIP3d(lep)"                           );
  registerLepPlots(leps, "Eta"          ,  240, 0.0,    2.4, "#||{#eta(lep)}"                       );
  registerLepPlots(leps, "EtainvMET"    ,  240, 0.0,    2.4, "#||{#eta(lep)}"                       );
  registerLepPlots(leps, "RelIso"       ,   50, 0.0,    1.0, "PF RelIso (lep)"                      );
  registerLepPlots(leps, "MiniIso"      ,   50, 0.0,    1.0, "PF MiniIso (lep)"                     );
  registerLepPlots(leps, "MiniIsoinvMET",   50, 0.0,    1.0, "PF MiniIso (lep)"                     );
  registerLepPlots(leps, "MT"           , 1000, 0.0, 1000.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(leps, "MTinvMET"     ,   20, 0.0,  200.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(leps, "MTinvMET0"    ,   20, 0.0,  200.0, "M_T(lep, MET) [GeV]"                  );
  registerLepPlots(leps, "Pt"           , 1000, 0.0, 1000.0, "P_T(lep) [GeV]"                       );
  registerLepPlots(leps, "PtinvMET"     , 1000, 0.0, 1000.0, "P_T(lep) [GeV]"                       );
  registerLepPlots(leps, "PtJet"        , 1000, 0.0, 1000.0, "P_T(jet closest to lep) [GeV]"        );
  registerLepPlots(leps, "PtCorr"       , 1000, 0.0, 1000.0, "cone corr. P_T(lep) [GeV]"            );
  registerLepPlots(leps, "PtRel"        , 1000, 0.0, 1000.0, "PtRel(lep)"                           );


  // electron maps

  // FO2 electrons
  // FO1 muons
 
  registerLepPlots(els, "MapPt"     , bins_pt.size()-1, bins_pt, bins_eta_el.size()-1, bins_eta_el, "P_T(e) [GeV]"               , "#||{#eta}(e)"); 
  registerLepPlots(els, "MapPtJet"  , bins_pt.size()-1, bins_pt, bins_eta_el.size()-1, bins_eta_el, "P_T(jet closest to e) [GeV]", "#||{#eta}(e)"); 
  registerLepPlots(els, "MapPtCorr" , bins_pt.size()-1, bins_pt, bins_eta_el.size()-1, bins_eta_el, "cone corr. P_T(e) [GeV]"    , "#||{#eta}(e)"); 

  registerLepPlots(mus, "MapPt"     , bins_pt.size()-1, bins_pt, bins_eta_mu.size()-1, bins_eta_mu, "P_T(#mu) [GeV]"               , "#||{#eta}(#mu)"); 
  registerLepPlots(mus, "MapPtJet"  , bins_pt.size()-1, bins_pt, bins_eta_mu.size()-1, bins_eta_mu, "P_T(jet closest to #mu) [GeV]", "#||{#eta}(#mu)"); 
  registerLepPlots(mus, "MapPtCorr" , bins_pt.size()-1, bins_pt, bins_eta_mu.size()-1, bins_eta_mu, "cone corr. P_T(#mu) [GeV]"    , "#||{#eta}(#mu)"); 
 
}


//____________________________________________________________________________
void FakeRatio::divideFRMap(string postpend){

  for(unsigned int i=0; i<_numDS + 4; ++i){
    TH1 * denom = _hm -> getHisto("MR_Den" + postpend, i);
    TH1 * num   = _hm -> getHisto("MR_Rat" + postpend, i);
    num -> Divide(denom);
  }
 
}


//____________________________________________________________________________
void FakeRatio::divideFRMaps(){

  divideFRMap("ElMapPt"    );
  divideFRMap("ElMapPtJet" );
  divideFRMap("ElMapPtCorr");
  divideFRMap("MuMapPt"    );
  divideFRMap("MuMapPtJet" );
  divideFRMap("MuMapPtCorr");
} 


//____________________________________________________________________________
void FakeRatio::doEwkSub(){


  bool foundData = false;
  bool foundEwk  = false;
  bool foundQcd  = false;

  for(unsigned int i=0; i<_numDS; ++i){
    
    string sname = _datasets[i]->getName();

    if     (sname.find("data") != std::string::npos) foundData = true;
    else if(sname.find("ewk")  != std::string::npos) foundEwk  = true;
    else if(sname.find("qcd")  != std::string::npos) foundQcd  = true;

  }

  if(foundData && foundEwk && foundQcd) 
    _doEwkSub = true;

}


//  ____________________________________________________________________________
vector<float> FakeRatio::doubleFit(TH1* h_data, TH1* h_ewk, TH1* h_qcd, float s_ewk, float s_qcd, float hmin, float hmax){

  if(hmin == 0) hmin = h_data -> GetXaxis() -> GetXmin();
  if(hmax == 0) hmax = h_data -> GetXaxis() -> GetXmax();

  RooRealVar x("x", "x", hmin, hmax);
  RooArgList rlist(x);
  RooArgSet  rset (x);

  RooDataHist rdh_data("data", "data", rlist, h_data  );
  RooDataHist rdh_ewk ("ewk" , "ewk" , rlist, h_ewk   );
  RooDataHist rdh_qcd ("qcd" , "qcd" , rlist, h_qcd   );
              
  RooHistPdf  pdf_ewk ("ewk" , "ewk" , rset , rdh_ewk );
  RooHistPdf  pdf_qcd ("qcd" , "qcd" , rset , rdh_qcd );

  float int_data = h_data -> Integral(h_data -> GetXaxis() -> FindBin(hmin), h_data -> GetXaxis() -> FindBin(hmax));
  float int_ewk  = h_ewk  -> Integral(h_ewk  -> GetXaxis() -> FindBin(hmin), h_ewk  -> GetXaxis() -> FindBin(hmax));
  float int_qcd  = h_qcd  -> Integral(h_qcd  -> GetXaxis() -> FindBin(hmin), h_qcd  -> GetXaxis() -> FindBin(hmax));
              
  RooRealVar  rrv_ewk ("ewk" , "ewk" , int_ewk * s_ewk, 0.0           , int_data );
  RooRealVar  rrv_qcd ("qcd" , "qcd" , int_qcd * s_qcd, int_data * 0.1, int_data );

  RooArgList pdfs (pdf_ewk, pdf_qcd); 
  RooArgList coeff(rrv_ewk, rrv_qcd); 

  RooAddPdf totPdf("totPdf", "totPdf", pdfs, coeff);
  RooFitResult* result = totPdf.fitTo(rdh_data, RooFit::SumW2Error(false), RooFit::Extended(), RooFit::PrintLevel(-1));

  vector<float> central;
  central.push_back(rrv_ewk.getVal() / int_ewk);
  central.push_back(rrv_qcd.getVal() / int_qcd);

  return central;

}  


//____________________________________________________________________________
void FakeRatio::modifySkimming(){
  // if adding variables in the skimming tree is needed...
}


//____________________________________________________________________________
void FakeRatio::modifyWeight() {
  /*
    modifies the event weight for every entry in the tree
    parameters: none
    return: none
  */ 
	
  //_weight = (i->second)->Getweight();

  if(_sampleName.find("data") == std::string::npos && _vc->get("puWeight") > 0)
    _weight *= _vc->get("puWeight");
  else
    _weight = 1.;

}


//  ____________________________________________________________________________
vector<float> FakeRatio::prepareHists(TH1* h_data, TH1* h_ewk, TH1* h_qcd){

  vector<float> scales;
  scales.push_back(1.);
  scales.push_back(1.);

  if(h_data -> Integral() < h_ewk -> Integral())
    scales[0] = floor(h_data->Integral() / h_ewk->Integral() * 1000) / 1000;

  if(h_data -> Integral() < h_qcd -> Integral())
    scales[1] = floor(h_data->Integral() / h_qcd->Integral() * 1000) / 1000;

  DUMPVECTOR(scales);

  return scales;

}


//____________________________________________________________________________
void FakeRatio::registerLepPlots(vector<string> leps, string var, int nbins, float bmin, float bmax, string axis){

  for(int i = 0; i < leps.size(); ++i)
    _hm->addVariable(leps[i] + var, nbins, bmin, bmax, axis);

} 


//____________________________________________________________________________
void FakeRatio::registerLepPlots(vector<string> leps, string var, int nxbins, vector<float> xbins, int nybins, vector<float> ybins, string xaxis, string yaxis){

  for(int i = 0; i < leps.size(); ++i)
    _hm->addVariable(leps[i] + var, nxbins, xbins, nybins, ybins, xaxis, yaxis);

}
 

//  ____________________________________________________________________________
float FakeRatio::singleFit(TH1* h_data, TH1* h_mc, float hmin, float hmax){

  if(hmin == 0) hmin = h_data -> GetXaxis() -> GetXmin();
  if(hmax == 0) hmax = h_data -> GetXaxis() -> GetXmax();

  RooRealVar x("x", "x", hmin, hmax);
  RooArgList rlist(x);
  RooArgSet  rset (x);

  RooDataHist rdh_data("data", "data", rlist, h_data  );
  RooDataHist rdh_mc  ("mc"  , "mc"  , rlist, h_mc    );
  RooHistPdf  pdf_mc  ("mc"  , "mc"  , rset , rdh_mc  );

  float int_data = h_data -> Integral(h_data -> GetXaxis() -> FindBin(hmin), h_data -> GetXaxis() -> FindBin(hmax));
  float int_mc   = h_mc   -> Integral(h_mc   -> GetXaxis() -> FindBin(hmin), h_mc   -> GetXaxis() -> FindBin(hmax));

  RooRealVar  rrv_mc  ("mc"  , "mc"  , int_data, int_data * 0.8, int_data );

  RooArgList  pdfs    (pdf_mc); 
  RooArgList  coeff   (rrv_mc); 

  RooAddPdf   totPdf  ("totPdf", "totPdf", pdfs, coeff);
  RooFitResult* result = totPdf.fitTo(rdh_data, RooFit::SumW2Error(false), RooFit::Extended(), RooFit::PrintLevel(-1));

  return rrv_mc.getVal() / int_mc;

} 


//____________________________________________________________________________
void FakeRatio::subtractPrompts(){
  /*
    implements subtraction of prompt contamination (ETH method)
  */

  if(!_doEwkSub) return; 

  float scales_ewk_el = 1.0;
  float scales_ewk_mu = 1.0;
  float scales_qcd_el = 1.0;
  float scales_qcd_mu = 1.0;

  bool subel = false;
  bool submu = false;

  if(_ewkSub == "all" || _ewkSub == "el") {

    TH1 * el_mt_data   = _hm -> getHisto("MR_NumElMTinvMET", _idx_datacorr);   
    TH1 * el_mt_ewk    = _hm -> getHisto("MR_NumElMTinvMET", _idx_ewk );   
    TH1 * el_mt_qcd    = _hm -> getHisto("MR_NumElMTinvMET", _idx_qcd );   

    // prepare the histograms
    vector<float> el_init  = prepareHists(el_mt_data, el_mt_ewk, el_mt_qcd);

    // first fit EWK and QCD together to data in range [0, infinity]
    vector<float> el_first = doubleFit(el_mt_data, el_mt_ewk, el_mt_qcd, el_init[0], el_init[1]);

    // fix QCD and subtract from data
    TH1 * el_mt_dataqcdsub = (TH1*) el_mt_data -> Clone(); 
    el_mt_dataqcdsub -> Add(el_mt_qcd, el_first[1] * (-1));

    TH1 * ewk = (TH1*) el_mt_ewk -> Clone();
    ewk -> Scale(el_first[0]);

    // for debugging
    cout << "ewk first scale is " << el_first[0] << endl;
    cout << "qcd first scale is " << el_first[1] << endl;

    // fit EWK to QCD-subtracted-data in range [50,120]

    scales_qcd_el = el_init[1] * el_first[1];
    scales_ewk_el = el_init[0] * el_first[0] * singleFit(el_mt_dataqcdsub, ewk, 50, 120);

    subel = true;


  }

  if(_ewkSub == "all" || _ewkSub == "mu") {

    TH1 * mu_mt_data = _hm -> getHisto("MR_NumMuMTinvMET", _idx_datacorr);   
    TH1 * mu_mt_ewk  = _hm -> getHisto("MR_NumMuMTinvMET", _idx_ewk );   
    TH1 * mu_mt_qcd  = _hm -> getHisto("MR_NumMuMTinvMET", _idx_qcd );   

    // prepare the histograms
    vector<float> mu_init  = prepareHists(mu_mt_data, mu_mt_ewk, mu_mt_qcd);

    // first fit EWK and QCD together to data in range [0, infinity]
    vector<float> mu_first = doubleFit(mu_mt_data, mu_mt_ewk, mu_mt_qcd, mu_init[0], mu_init[1]);

    // fix QCD and subtract from data
    TH1 * mu_mt_dataqcdsub = (TH1*) mu_mt_data -> Clone();
    mu_mt_dataqcdsub -> Add(mu_mt_qcd, mu_first[1] * (-1));

    TH1 * ewk = (TH1*) mu_mt_ewk -> Clone();
    ewk -> Scale(mu_first[0]);

	cout << "overall qcd scale: " << (mu_init[1] * mu_first[1]) << endl;

    // fit EWK to QCD-subtracted-data in range [50,120]
    scales_qcd_mu = mu_init[1] * mu_first[1];
    scales_ewk_mu = mu_init[0] * mu_first[0] * singleFit(mu_mt_dataqcdsub, ewk, 50, 120);

    submu = true;

  }

  // fix scales of the summed "qcd" and "ewk" numerators and denominators
  // subtract ewk from all "datacorr" numerators and denominators

  vector<string> obs = _hm -> getObservables(true);
  vector<string> nobs;
  for(unsigned int i = 0; i < obs.size(); ++i)
    if(obs[i].find("MTinvMET0") == std::string::npos)
      nobs.push_back(obs[i]);

  for(unsigned int i = 0; i < nobs.size(); ++i) {

    cout << "correcting " << nobs[i] << endl;

    float s_ewk = 1.0;
	float s_qcd = 1.0;
    if(nobs[i].find("El") != std::string::npos){
      if(!subel) continue;
      s_ewk = scales_ewk_el;
      s_qcd = scales_qcd_el;
    }
    if(nobs[i].find("Mu") != std::string::npos){
      if(!submu) continue;
      s_ewk = scales_ewk_mu;
      s_qcd = scales_qcd_mu;
    }

    TH1 * d = _hm -> getHisto(nobs[i], _idx_datacorr);
    TH1 * e = _hm -> getHisto(nobs[i], _idx_ewk     );
    TH1 * q = _hm -> getHisto(nobs[i], _idx_qcd     );

    e -> Scale(s_ewk);
    q -> Scale(s_qcd); 

    d -> Add(e, -1);
  } 

  //// subtract ewk contamination from all numerators and denominators  
  //string amaps[3] = {"MapPt", "MapPtJet", "MapPtCorr"};
  //string asels[3] = {"Den", "Num", "Rat"};

  //vector<string> maps = Tools::toVector(amaps);
  //vector<string> sels = Tools::toVector(asels);

  //for(unsigned int i = 0; i < leps.size(); ++i){
  //  for(unsigned int j = 0; j < maps.size(); ++j) {
  //    for(unsigned int k = 0; k < sels.size(); ++k) {
  //      cout << "subtracting MR_" << sels[k] << leps[i] << maps[j] << " for " << _idx_datacorr << endl;
  //      TH1 * d = _hm -> getHisto("MR_" + sels[k] + leps[i] + maps[j], _idx_datacorr);
  //      TH1 * e = _hm -> getHisto("MR_" + sels[k] + leps[i] + maps[j], _idx_ewk     );
  //      //TH1 * ewk = (TH1*) e -> Clone();
  //      //ewk -> Scale(scales[i]);
  //      d -> Add(e, scales[i] * (-1));
  //    }
  //  }
  //}
}   




//____________________________________________________________________________
void FakeRatio::sumMaps(){
  /*
    adds weighted numerators and denominators for different samples with same prefix
  */


  if(!_doEwkSub) return; 


  for(unsigned int i=0; i<_numDS; ++i){
    
    string sname = _datasets[i]->getName();

    int nevts = _datasets[i]->getNProcEvents(0);
	float xs = 0;
	vector<unsigned int> idxs;
    if     (sname.find("data") != std::string::npos) {
		idxs.push_back(_idx_data); 
		idxs.push_back(_idx_datacorr);
    } 
    else if(sname.find("ewk")  != std::string::npos) {
		idxs.push_back(_idx_ewk);
		sname.erase(sname.find("ewk"), 3);
    	xs = _dbm -> getDBValue("XS", sname); 
	} 
    else if(sname.find("qcd")  != std::string::npos) {
		idxs.push_back(_idx_qcd);
		sname.erase(sname.find("qcd"), 3);
    	xs = _dbm -> getDBValue("XS", sname); 
	} 

    vector<string> obs = _hm -> getObservables(true);

    for(unsigned int j = 0; j < obs.size(); ++j) {
      TH1 * sobs = _hm -> getHisto(obs[j], i);
      TH1 * cobs = (TH1*) sobs -> Clone();

      float factor = 1;

      if(xs > 0){
        factor = xs * _lumi / nevts;
        //DUMP(factor);
        //cobs -> Scale(xs * _lumi / nevts);
	    //cout << "did a rescale with " << (xs * _lumi / nevts) << endl;
      }        

      for(unsigned int k = 0; k < idxs.size(); ++k) {
        TH1 * robs = _hm -> getHisto(obs[j], idxs[k]);
        robs -> Add(cobs, factor);
      }
    }
  }
}
    

//  ____________________________________________________________________________
void FakeRatio::writeOutput(){
  /*
    writes all output of this class to the disk
    paramters: none
    return: none
  */

  // decide if we need EWK subtraction or not (if not, jump to divideFRMaps call)
  doEwkSub();
 
  // sum numerators and denominators in categories 'data', 'datacorr', 'ewk', 'qcd' 
  sumMaps();

  // subtract prompt contamination
  subtractPrompts();

  // make FR maps from numerators and denominators
  divideFRMaps();

}




/*****************************************************************************
******************************************************************************
** OBJECT SELECTIONS                                                        **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::collectKinematicObjects(){
  /*
    collects all kinematic objects needed in the code, i.e. applies all object selections
    parameters: none
    return: none
  */
  
  for(int i = 0; i < _vc->get("n" + _leps); ++i){

    bool den = false;
    bool num = false;

    // electrons
    if(std::abs(_vc->get(_leps + "_pdgId", i)) == 11){		  
      if(denominatorElectronSelection(i)) {
        _denEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.0005) );
        _denElsIdx .push_back(i);
        _denLeps   .push_back( _denEls[ _denEls.size()-1 ] );
        _denLepsIdx.push_back(i);
        den = true;
      }
      if(numeratorElectronSelection(i)) {
        _numEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.0005) );
        _numElsIdx .push_back(i);
        _numLeps   .push_back( _numEls[ _numEls.size()-1 ] );
        _numLepsIdx.push_back(i);
        num = true;
      }
      if(!den && !num) {
        if(vetoElectronSelection(i))  {
          _vetEls.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					     _vc->get(_leps + "_eta", i),
					     _vc->get(_leps + "_phi", i),
					     _vc->get(_leps + "_pdgId", i),
					     _vc->get(_leps + "_charge", i),
					     0.0005) );
          _vetLeps.push_back( _vetEls[ _vetEls.size()-1 ] );
        }
      }		
    }

    // muons
    else if(std::abs(_vc->get(_leps + "_pdgId", i)) == 13){
      if(denominatorMuonSelection(i)) {
        _denMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.105) );
        _denMusIdx .push_back(i);
        _denLeps   .push_back( _denMus[ _denMus.size()-1 ] );
        _denLepsIdx.push_back(i);
        den = true;
      }
      if(numeratorMuonSelection(i)) {
        _numMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					  _vc->get(_leps + "_eta", i),
					  _vc->get(_leps + "_phi", i),
					  _vc->get(_leps + "_pdgId", i),
					  _vc->get(_leps + "_charge", i),
					  0.105) );
        _numMusIdx .push_back(i);
        _numLeps   .push_back( _numMus[ _numMus.size()-1 ] );
        _numLepsIdx.push_back(i);
        num = true;
      }
      if(!den && !num) {
        if(vetoMuonSelection(i))  {
          _vetMus.push_back( Candidate::create(_vc->get(_leps + "_pt", i),
					     _vc->get(_leps + "_eta", i),
					     _vc->get(_leps + "_phi", i),
					     _vc->get(_leps + "_pdgId", i),
					     _vc->get(_leps + "_charge", i),
					     0.105) );
          _vetLeps.push_back( _vetMus[ _vetMus.size()-1 ] );
        }
      }
    }
  }

  _nDenEls  = _denEls .size();
  _nDenLeps = _denLeps.size();
  _nDenMus  = _denMus .size();
  _nNumEls  = _numEls .size();
  _nNumLeps = _numLeps.size();
  _nNumMus  = _numMus .size();
 
  for(int i = 0; i < _vc->get("n" + _jets); ++i){
    if(goodJetSelection(i)) {
      _goodJets.push_back( Candidate::create(_vc->get(_jets + "_pt", i),
					                     _vc->get(_jets + "_eta", i),
					                     _vc->get(_jets + "_phi", i) ) );
      
    }
  }

  _nJets  = _goodJets.size();
  
  _HT  = _susyMod -> HT( &(_goodJets) );
  _met = Candidate::create(_vc->get(_mets + "_pt"), _vc->get(_mets + "_phi") );

}


//____________________________________________________________________________
bool FakeRatio::goodJetSelection(int jetIdx){
  /*
    does the selection of good jets, i.e. minimum selection of jets 
    parameters: jetIdx
    return: true (if the jet is good), false (else)
  */
  
  counter("GoodJets", kGoodJets);

  if(!makeCut<float>(         _vc->get(_jets + "_pt" , jetIdx) , 40.0, ">" , "pt selection"   , 0, kGoodJets)) return false;
  if(!makeCut<float>(std::abs(_vc->get(_jets + "_eta", jetIdx)),  2.4, "<" , "eta selection"  , 0, kGoodJets)) return false;
  if(!makeCut<float>(         _vc->get(_jets + "_id" , jetIdx) ,  1  , ">=", "pog pf loose id", 0, kGoodJets)) return false;
  
  // CH: away-jet requirement
  for(unsigned int il=0; il<_denLeps.size(); ++il){
    float dr = KineUtils::dR(_denLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _denLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(!makeCut<float>(dr, 1.0, ">", "dR selection", 0, kGoodJets) ) return false;
  }

  // CH: this is jet-lepton cleaning: removing the closest jet to the loose lepton if dR < 0.4
  float dr_cache = 999999.;
  for(unsigned int il=0; il<_denLeps.size(); ++il){
    float dr = KineUtils::dR(_denLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _denLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(dr < dr_cache)
      dr_cache = dr;
  }
  for(unsigned int il=0; il<_vetLeps.size(); ++il){
    float dr = KineUtils::dR(_vetLeps[il]->eta(), _vc->get("Jet_eta", jetIdx),
			                 _vetLeps[il]->phi(), _vc->get("Jet_phi", jetIdx));
    if(dr < dr_cache)
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.4, ">", "dR selection, jet-lepton cleaning", 0, kGoodJets) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::denominatorElectronSelection(int elIdx){

  counter("DenominatorElectrons", kDenEls);

  // CH: FO2 selection for electrons
  // extrapolation in ElMvaId and mini isolation

  // additional cuts for trigger
  if(std::abs(_vc->get("LepGood_eta", elIdx)) < 1.479){
    if(!makeCut<float>(         _vc->get(_leps + "_sigmaIEtaIEta" , elIdx) , 0.011, "<", "sigmaIEtaIEta selection", 0, kDenEls)) return false;
    if(!makeCut<float>(         _vc->get(_leps + "_hadronicOverEm", elIdx) , 0.08 , "<", "H / E selection"        , 0, kDenEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_dEtaScTrkIn"   , elIdx)), 0.01 , "<", "dEta selection"         , 0, kDenEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_dPhiScTrkIn"   , elIdx)), 0.04 , "<", "dPhi selection"         , 0, kDenEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_eInvMinusPInv" , elIdx)), 0.01 , "<", "1/E - 1/P selection"    , 0, kDenEls)) return false;
  }
  else {
    if(!makeCut<float>(         _vc->get(_leps + "_sigmaIEtaIEta" , elIdx) , 0.031, "<", "sigmaIEtaIEta selection", 0, kDenEls)) return false;
    if(!makeCut<float>(         _vc->get(_leps + "_hadronicOverEm", elIdx) , 0.08 , "<", "H / E selection"        , 0, kDenEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_dEtaScTrkIn"   , elIdx)), 0.01 , "<", "dEta selection"         , 0, kDenEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_dPhiScTrkIn"   , elIdx)), 0.08 , "<", "dPhi selection"         , 0, kDenEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_eInvMinusPInv" , elIdx)), 0.01 , "<", "1/E - 1/P selection"    , 0, kDenEls)) return false;
  }
  //CH: still need to write this!
  //Plus for isolated triggers only: EcalPFClusterIso<0.45, HcalPFClusterIso<0.25, TrackIso<0.2

  if(!makeCut<float>(   _susyMod -> conePt(elIdx, SusyModule::kTight), 10.   , ">"  , "pt selection"      , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 2.5   , "<"  , "eta selection"     , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 1.4442, "[!]", "eta selection veto", 1.566, kDenEls)) return false;
  if((_datasets[_inds]->getName().find("qcd") != std::string::npos && _datasets[_inds]->getName().find("data") == std::string::npos) && 
     !makeCut<int>(           _vc->get("LepGood_mcMatchId"  , elIdx) ,  0    , "="  , "gen match fake"    , 0    , kDenEls)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"      , elIdx) , 4.0   , "<"  , "SIP 3D"            , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"         , elIdx)), 0.1   , "<"  , "dz selection"      , 0    , kDenEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"        , elIdx)), 0.05  , "<"  , "dxy selection"     , 0    , kDenEls)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge", elIdx) , 1     , ">"  , "charge selection"  , 0    , kDenEls)) return false;

  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);

  if(!makeCut( conv                                              , "conversion rejection", "=", kDenEls)) return false;
  if(!makeCut( _susyMod -> multiIsoSel(elIdx, SusyModule::kDenom), "isolation"           , "=", kDenEls)) return false; 
  if(!makeCut( _susyMod -> elMvaSel   (elIdx, SusyModule::kLoose), "electron mva"        , "=", kDenEls)) return false;    

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kDenEls) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::denominatorMuonSelection(int muIdx){

  counter("DenominatorMuons", kDenMus);
  
  //CH: FO1 for muons
  //extrapolation in isolation only

  if(!makeCut( _susyMod -> multiIsoSel(muIdx, SusyModule::kDenom), "isolation", "=", kDenMus)) return false;

  if(!makeCut<float>(   _susyMod -> conePt(muIdx, SusyModule::kMedium), 10.  , ">", "pt selection"  , 0, kDenMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_eta"         , muIdx) ,  2.4 , "<", "eta selection" , 0, kDenMus)) return false;
  if((_datasets[_inds]->getName().find("qcd") != std::string::npos && _datasets[_inds]->getName().find("data") == std::string::npos) && 
     !makeCut<int>(           _vc->get("LepGood_mcMatchId"   , muIdx) ,  0   , "=", "gen match fake", 0, kDenMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx) ,  0   , ">", "medium muon ID", 0, kDenMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx) ,  1   , ">", "error/pt < 20" , 0, kDenMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"       , muIdx) ,  4.0 , "<", "SIP 3D"        , 0, kDenMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"          , muIdx)),  0.1 , "<", "dz selection"  , 0, kDenMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"         , muIdx)),  0.05, "<", "dxy selection" , 0, kDenMus)) return false;


  return true;

}


//____________________________________________________________________________
bool FakeRatio::numeratorElectronSelection(int elIdx){

  counter("NumeratorElectrons", kNumEls);

  // additional cuts for trigger
  if(std::abs(_vc->get("LepGood_eta", elIdx)) < 1.479){
    if(!makeCut<float>(         _vc->get(_leps + "_sigmaIEtaIEta" , elIdx) , 0.011, "<", "sigmaIEtaIEta selection", 0, kNumEls)) return false;
    if(!makeCut<float>(         _vc->get(_leps + "_hadronicOverEm", elIdx) , 0.08 , "<", "H / E selection"        , 0, kNumEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_dEtaScTrkIn"   , elIdx)), 0.01 , "<", "dEta selection"         , 0, kNumEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_dPhiScTrkIn"   , elIdx)), 0.04 , "<", "dPhi selection"         , 0, kNumEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_eInvMinusPInv" , elIdx)), 0.01 , "<", "1/E - 1/P selection"    , 0, kNumEls)) return false;
  }
  else {
    if(!makeCut<float>(         _vc->get(_leps + "_sigmaIEtaIEta" , elIdx) , 0.031, "<", "sigmaIEtaIEta selection", 0, kNumEls)) return false;
    if(!makeCut<float>(         _vc->get(_leps + "_hadronicOverEm", elIdx) , 0.08 , "<", "H / E selection"        , 0, kNumEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_dEtaScTrkIn"   , elIdx)), 0.01 , "<", "dEta selection"         , 0, kNumEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_dPhiScTrkIn"   , elIdx)), 0.08 , "<", "dPhi selection"         , 0, kNumEls)) return false;
    if(!makeCut<float>(std::abs(_vc->get(_leps + "_eInvMinusPInv" , elIdx)), 0.01 , "<", "1/E - 1/P selection"    , 0, kNumEls)) return false;
  }
  //CH: still need to write this!
  //Plus for isolated triggers only: EcalPFClusterIso<0.45, HcalPFClusterIso<0.25, TrackIso<0.2

  if(!makeCut<float>(   _susyMod -> conePt(elIdx, SusyModule::kTight), 10.   , ">"  , "pt selection"      , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 2.5   , "<"  , "eta selection"     , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_eta"        , elIdx)), 1.4442, "[!]", "eta selection veto", 1.566, kNumEls)) return false;
  if((_datasets[_inds]->getName().find("qcd") != std::string::npos && _datasets[_inds]->getName().find("data") == std::string::npos) && 
     !makeCut<int>(           _vc->get("LepGood_mcMatchId"  , elIdx) ,  0    , "="  , "gen match fake"    , 0    , kNumEls)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"      , elIdx) , 4.0   , "<"  , "SIP 3D"            , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"         , elIdx)), 0.1   , "<"  , "dz selection"      , 0    , kNumEls)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"        , elIdx)), 0.05  , "<"  , "dxy selection"     , 0    , kNumEls)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge", elIdx) , 1     , ">"  , "charge selection"  , 0    , kNumEls)) return false;

  bool conv = (_vc->get("LepGood_convVeto", elIdx) > 0 && _vc->get("LepGood_lostHits", elIdx)==0);

  if(!makeCut( conv                                              , "conversion rejection", "=", kNumEls)) return false;
  if(!makeCut( _susyMod -> multiIsoSel(elIdx, SusyModule::kTight), "isolation"           , "=", kNumEls)) return false; 
  if(!makeCut( _susyMod -> elMvaSel   (elIdx, SusyModule::kTight), "electron mva"        , "=", kNumEls)) return false;    

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("nLepGood"); ++il){
    float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", elIdx),
			                 _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", elIdx));
    if(std::abs(_vc->get("LepGood_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kNumEls) ) return false;

  return true;

}


//____________________________________________________________________________
bool FakeRatio::numeratorMuonSelection(int muIdx){

  counter("NumeratorMuons", kNumMus);

  if(!makeCut( _susyMod -> multiIsoSel(muIdx, SusyModule::kMedium), "isolation", "=", kNumMus)) return false;

  if(!makeCut<float>(   _susyMod -> conePt(muIdx, SusyModule::kMedium), 10.  , ">", "pt selection"  , 0, kNumMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_eta"         , muIdx) ,  2.4 , "<", "eta selection" , 0, kNumMus)) return false;
  if((_datasets[_inds]->getName().find("qcd") != std::string::npos && _datasets[_inds]->getName().find("data") == std::string::npos) && 
     !makeCut<int>(           _vc->get("LepGood_mcMatchId"   , muIdx) ,  0   , "=", "gen match fake", 0, kNumMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_mediumMuonId", muIdx) ,  0   , ">", "medium muon ID", 0, kNumMus)) return false;
  if(!makeCut<int>(           _vc->get("LepGood_tightCharge" , muIdx) ,  1   , ">", "error/pt < 20" , 0, kNumMus)) return false;
  if(!makeCut<float>(         _vc->get("LepGood_sip3d"       , muIdx) ,  4.0 , "<", "SIP 3D"        , 0, kNumMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dz"          , muIdx)),  0.1 , "<", "dz selection"  , 0, kNumMus)) return false;
  if(!makeCut<float>(std::abs(_vc->get("LepGood_dxy"         , muIdx)),  0.05, "<", "dxy selection" , 0, kNumMus)) return false;
 
  return true;

}


//____________________________________________________________________________
bool FakeRatio::vetoElectronSelection(int elIdx){
  // selection of veto electrons

  counter("VetoElectrons", kVetEls);

  // electron cleaning 
  float dr_cache = 999.;
  for(unsigned int il=elIdx+1; il<_vc->get("n" + _leps); ++il){
    float dr = KineUtils::dR(_vc->get(_leps + "_eta", il), _vc->get(_leps + "_eta", elIdx),
			                 _vc->get(_leps + "_phi", il), _vc->get(_leps + "_phi", elIdx));
    if(std::abs(_vc->get(_leps + "_pdgId")) == 13 && dr < dr_cache) 
      dr_cache = dr;
  }
  if(!makeCut<float>(dr_cache, 0.05, ">", "electron cleaning selection", 0, kVetEls) ) return false;
  
  return true;

}


//____________________________________________________________________________
bool FakeRatio::vetoMuonSelection(int muIdx){
  // selection of veto muons

  counter("VetoMuons", kVetMus);
  
  return true;

}




/*****************************************************************************
******************************************************************************
** KINEMATIC REGION DEFINITIONS                                             **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::setCut(std::string var, float valCut, std::string cType, float upValCut) {
  /*
    sets the parameters (valCut, cType, upValCut) for a specific cut on a variable (var)
    parameters: var, valCut (the cut value), cType (the cut type), upValCut (the upper value
    in case one cuts the variable in a range)
    return: none
  */


  // measurement region

  if(var == "NBJetsMR") {
    _valCutNBJetsMR   = valCut;
    _cTypeNBJetsMR    = cType;
    _upValCutNBJetsMR = upValCut;
  } 
	

}



//____________________________________________________________________________
void FakeRatio::setMeasurementRegion() {
  /*
    sets the cuts of the measurement region (MR)
    parameters: none
    return: none
  */


  // CH: currently not used, keep it for later
  //if(_MR == "all") {
  //  setCut("NBJetsMR", 0, ">=");
  //} 
  //else if(_MR == "MR00") {
  //  setCut("NBJetsMR", 0, "=");
  //}
  //else if(_MR == "MR01") {
  //  setCut("NBJetsMR", 1, "=");
  //}
  //else if(_MR == "MR02") {
  //  setCut("NBJetsMR", 2, "=");
  //}
  //else if(_MR == "MR03") {
  //  setCut("NBJetsMR", 3, ">=");
  //}


}



/*****************************************************************************
******************************************************************************
** EVENT SELECTIONS                                                         **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
bool FakeRatio::ewkSelection(){
  // CH: fake ratio measurement for RA5 sync exercise May 2015


  // lepton multiplicity
  if(!makeCut<int>( _nDenLeps    , 1   , "=" , "lepton multiplicity and flavor", 0, kEwkSel)) return false;

  //CH: RA5 guys select muon pt later on
  if     (_sampleName.find("Mu15") != std::string::npos && _denLeps[0] -> pt() < 15.) return false;
  else if(_sampleName.find("Mu5")  != std::string::npos && _denLeps[0] -> pt() > 15.) return false;

  // MET INVERTED! 
  if(!makeCut<float>( _met->pt() , 20.0, ">" , "MET selection"                 , 0, kEwkSel)) return false;

  // jet multiplicity
  if(!makeCut<int>( _nJets       , 1   , ">=", "jet multiplicity"              , 0, kEwkSel)) return false; 

  return true;

}


//____________________________________________________________________________
bool FakeRatio::mrSelection(){
  // CH: fake ratio measurement for RA5 sync exercise May 2015


  // lepton multiplicity
  if(!makeCut<int>( _nDenLeps    , 1   , "=" , "lepton multiplicity and flavor")) return false;

  //CH: RA5 guys select muon pt later on
  if     (_sampleName.find("Mu15") != std::string::npos && _denLeps[0] -> pt() < 15.) return false;
  else if(_sampleName.find("Mu5")  != std::string::npos && _denLeps[0] -> pt() > 15.) return false;

  //if(_nDenMus == 1)
  //  counter("muon multiplicity"); 

  // MET 
  if(!makeCut<float>( _met->pt() , 20.0, "<" , "MET selection"                 )) return false;
  //if(_nDenMus == 1)
  //  counter("muon MET"); 

  // MT
  Candidate* MT = nullptr;
  MT = Candidate::create( _denLeps[0], _met);
  if(!makeCut<float>( MT->mass() , 20.0, "<" , "MT selection"                  )) return false;
  //if(_nDenMus == 1)
  //  counter("muon MT"); 

  // jet multiplicity
  if(!makeCut<int>( _nJets       , 1   , ">=", "jet multiplicity"              )) return false; 
  //if(_nDenMus == 1)
  //  counter("muon Jet"); 

  return true;

}


//____________________________________________________________________________
bool FakeRatio::skimSelection(){

  if(!makeCut<int>( _nDenLeps, 1, ">=", "lepton multiplicity and flavor") ) return false;
  if(!makeCut<int>( _nJets   , 1, ">=", "jet multiplicity"              ) ) return false; 

  return true;

}




/*****************************************************************************
******************************************************************************
** EXECUTING TASKS                                                          **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void FakeRatio::fillEventPlots(){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  fill("MR_HT"        , _HT                 , _weight);
  fill("MR_MET"       , _met->pt()          , _weight);
  fill("MR_NumBJets"  , _vc->get(_bvar)     , _weight);
  fill("MR_NumDenEls" , _denEls .size()     , _weight);
  fill("MR_NumDenLeps", _denLeps.size()     , _weight);
  fill("MR_NumDenMus" , _denMus .size()     , _weight);
  fill("MR_NumJets"   , _nJets              , _weight);
  fill("MR_NumNumEls" , _numEls .size()     , _weight);
  fill("MR_NumNumLeps", _numLeps.size()     , _weight);
  fill("MR_NumNumMus" , _numMus .size()     , _weight);
  fill("MR_NumVrtx"   , _vc->get(_nvert)    , _weight);

}


//____________________________________________________________________________
void FakeRatio::fillEwkEventPlots(){
  /*
    fills the control plots for event quantities
    parameters: none
    return: none
  */

  fill("MR_HTinvMET"  , _HT                 , _weight);
  fill("MR_METinvMET" , _met->pt()          , _weight);

}


//____________________________________________________________________________
void FakeRatio::fillEwkLepPlots(string prepend, Candidate * lep, int lepIdx, int wp){
  /*
    fills the control plots for leptons PER LEPTON
  */  

  Candidate * mt = Candidate::create( lep, _met);

  fill(prepend + "PtinvMET"     ,          _vc->get(_leps + "_pt"        , lepIdx) , _weight);
  fill(prepend + "EtainvMET"    , std::abs(_vc->get(_leps + "_eta"       , lepIdx)), _weight);
  fill(prepend + "DXYinvMET"    , std::abs(_vc->get(_leps + "_dxy"       , lepIdx)), _weight);
  fill(prepend + "DZinvMET"     , std::abs(_vc->get(_leps + "_dz"        , lepIdx)), _weight);
  fill(prepend + "SIPinvMET"    ,          _vc->get(_leps + "_sip3d"     , lepIdx) , _weight);
  fill(prepend + "MiniIsoinvMET",          _vc->get(_leps + "_miniRelIso", lepIdx) , _weight);
  fill(prepend + "MTinvMET"     , mt -> mass()                                     , _weight);
  fill(prepend + "MTinvMET0"    , mt -> mass()                                     , _weight);

}


//____________________________________________________________________________
void FakeRatio::fillEwkLeptonPlots(){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  for(int i = 0; i < _denEls.size(); ++i) { fillEwkLepPlots("MR_DenEl"  , _denEls[i]  , _denElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _denMus.size(); ++i) { fillEwkLepPlots("MR_DenMu"  , _denMus[i]  , _denMusIdx[i], SusyModule::kMedium); }
  for(int i = 0; i < _numEls.size(); ++i) { fillEwkLepPlots("MR_NumEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _numMus.size(); ++i) { fillEwkLepPlots("MR_NumMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }

}


//____________________________________________________________________________
void FakeRatio::fillFRMaps(string prepend, Candidate * lep, int lepIdx, int wp){

  fill(prepend + "MapPt"    , overflowPt(_vc->get(_leps + "_pt", lepIdx)) , std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);
  fill(prepend + "MapPtJet" , overflowPt(_susyMod -> closestJetPt(lepIdx)), std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);
  fill(prepend + "MapPtCorr", overflowPt(_susyMod -> conePt(lepIdx, wp))  , std::abs(_vc->get(_leps + "_eta", lepIdx)), _weight);

}


//____________________________________________________________________________
void FakeRatio::fillFakeRatioMaps(){
  /*
    fills the fake ratio maps for leptons
    parameters: none
    return: none
  */

  for(int i = 0; i < _denEls.size(); ++i) { fillFRMaps("MR_DenEl"  , _denEls[i]  , _denElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _denMus.size(); ++i) { fillFRMaps("MR_DenMu"  , _denMus[i]  , _denMusIdx[i], SusyModule::kMedium); }
  for(int i = 0; i < _numEls.size(); ++i) { fillFRMaps("MR_NumEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight );
                                            fillFRMaps("MR_RatEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _numMus.size(); ++i) { fillFRMaps("MR_NumMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium);
                                            fillFRMaps("MR_RatMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }

}


//____________________________________________________________________________
void FakeRatio::fillLepPlots(string prepend, Candidate * lep, int lepIdx, int wp){
  /*
    fills the control plots for leptons PER LEPTON
  */  

  fill(prepend + "Pt"     ,          _vc->get(_leps + "_pt"        , lepIdx) , _weight);
  fill(prepend + "Eta"    , std::abs(_vc->get(_leps + "_eta"       , lepIdx)), _weight);
  fill(prepend + "DXY"    , std::abs(_vc->get(_leps + "_dxy"       , lepIdx)), _weight);
  fill(prepend + "DZ"     , std::abs(_vc->get(_leps + "_dz"        , lepIdx)), _weight);
  fill(prepend + "SIP"    ,          _vc->get(_leps + "_sip3d"     , lepIdx) , _weight);
  fill(prepend + "RelIso" ,          _vc->get(_leps + "_relIso03"  , lepIdx) , _weight);
  fill(prepend + "MiniIso",          _vc->get(_leps + "_miniRelIso", lepIdx) , _weight);
  fill(prepend + "PtRel"  ,          _vc->get(_leps + "_jetPtRel"  , lepIdx) , _weight);
  fill(prepend + "MT"     , Candidate::create( lep, _met) -> mass()          , _weight);
  fill(prepend + "PtJet"  , _susyMod -> closestJetPt(lepIdx)                 , _weight);
  fill(prepend + "PtCorr" , _susyMod -> conePt(lepIdx, wp)                   , _weight);

}


//____________________________________________________________________________
void FakeRatio::fillLeptonPlots(){
  /*
    fills the control plots for leptons
    parameters: none
    return: none
  */

  for(int i = 0; i < _denEls.size(); ++i) { fillLepPlots("MR_DenEl"  , _denEls[i]  , _denElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _denMus.size(); ++i) { fillLepPlots("MR_DenMu"  , _denMus[i]  , _denMusIdx[i], SusyModule::kMedium); }
  for(int i = 0; i < _numEls.size(); ++i) { fillLepPlots("MR_NumEl"  , _numEls[i]  , _numElsIdx[i], SusyModule::kTight ); }
  for(int i = 0; i < _numMus.size(); ++i) { fillLepPlots("MR_NumMu"  , _numMus[i]  , _numMusIdx[i], SusyModule::kMedium); }

}


//____________________________________________________________________________
void FakeRatio::fillJetPlots(){
  /*
    fills the control plots for jets
    parameters: none
    return: none
  */


  for(int i = 0; i < _nJets; ++i){
    fill("MR_JetPt"     , _goodJets[i]->pt(), _weight);
  }

}




//____________________________________________________________________________
float FakeRatio::overflowPt(float rawPt){

	if(rawPt >= 70.) return 60.;

	return rawPt;
}

