MPAFDisplay md;

void ttVPlotFacility(){
  md.refresh();

  //general parameters ********************* general parameters
  string dir="TTVAnalysis";
  string fileName="looseLepID/ttvAnalysisFall17_all"; //ttvAnalysisNNTest
  vector<string> fileList; fileList.push_back("ttvAnalysisFall17");

  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  //}
  
  //observables **********************
  md.setObservables("lepFlavor");//"NN2DWZtZq","NN2DWZtZW","NN2DWZttH");
  //"NN2DtZqtZW","NN2DtZqttH","NN2DtZWttH");//,"nJets25","HT"); "JetCateg", "NeuralNet"
  
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=1;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0.,0};
  double rangeX[2]={-10,500};
  int xDiv[3]={8,6,0};
  int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
  bool logYScale=false;
  bool overFlowBin=true;
  bool underFlowBin=false;
  bool showDMCRatio=true;
  bool showGrid=false;
  bool largePad=true;
  float markerSize=0.8;
  float lineWidth=2;

  bool summedSignal=true;
  bool stacking=true;

  bool cmsPrel=true;

  float xt=0.13;
  float yt=0.91;
  float st=0.1;
  string addText="CMS Simulation";

  string autoBinFile="ttvBinningFall17";
  // md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=false;
  bool mcStatSyst=false;
  bool uncDet=false;
  vector<string> systSources ({"jes",
   	"btag:LF:HF:CSVHFStats1:CSVHFStats2:CSVLFStats1:CSVLFStats2:CSVCFErr1:CSVCFErr2"});
	//"btag:btagJ"})
			     
  
  string Norm="";
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=35900; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsSpring16.db");

  map<string,float> LumisXS;
  //via XSect
  map<string,float> KFactors;
  KFactors["TTJets"]=8.86651e-09;

  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
  
 
  md.anConf.addSample( "Fake:TTJets",                    "fakes", kGray+1);
  md.anConf.addSample( "Fake:T_tWch_noFullHad",          "fakes", kGray+1);
  md.anConf.addSample( "Fake:T_tch_powheg",              "fakes", kGray+1);
  md.anConf.addSample( "Fake:DYJetsToLL_M50_chunk0",     "fakes", kGray+1);
  md.anConf.addSample( "Fake:DYJetsToLL_M50_chunk1",     "fakes", kGray+1);
  md.anConf.addSample( "Fake:DYJetsToLL_M50_chunk2",     "fakes", kGray+1);
  md.anConf.addSample( "Fake:TBar_tWch_noFullHad_0",     "fakes", kGray+1);
  md.anConf.addSample( "Fake:TBar_tWch_noFullHad_1",     "fakes", kGray+1);
  md.anConf.addSample( "Fake:TBar_tWch_noFullHad_ext_0", "fakes", kGray+1);
  md.anConf.addSample( "Fake:TBar_tWch_noFullHad_ext_1", "fakes", kGray+1);
  md.anConf.addSample( "Fake:TBar_tch_powheg",           "fakes", kGray+1);
  md.anConf.addSample( "Fake:TToLeptons_sch_0",          "fakes", kGray+1);
  md.anConf.addSample( "Fake:TToLeptons_sch_1",          "fakes", kGray+1);
  md.anConf.addSample( "Fake:WJetsToLNu_LO",             "fakes", kGray+1);
  md.anConf.addSample( "Fake:WWTo1L1Nu2Q_0",             "fakes", kGray+1);
  md.anConf.addSample( "Fake:WWTo2L2Nu_0",               "fakes", kGray+1);
  md.anConf.addSample( "Fake:ZZTo2L2Nu",                 "fakes", kGray+1);

  md.anConf.addSample( "WWW_4F",          "ewk", kAzure-4);
  md.anConf.addSample( "WZG",             "ewk", kAzure-4);
  md.anConf.addSample( "WZZ",             "ewk", kAzure-4);
  md.anConf.addSample( "ZZZ",             "ewk", kAzure-4);
  md.anConf.addSample( "GGHZZ4L_0",       "ewk", kAzure-4);
  md.anConf.addSample( "GGHZZ4L_ext_0",   "ewk", kAzure-4);
  md.anConf.addSample( "VBF_HToZZTo4L_0", "ewk", kAzure-4);
  md.anConf.addSample( "ZZTo4L_0",        "ewk", kAzure-4);
  md.anConf.addSample( "ZZTo4L_1",        "ewk", kAzure-4);


  md.anConf.addSample( "TTGJets_0",       "ttX", kViolet+4);
  md.anConf.addSample( "TTGJets_1",       "ttX", kViolet+4);
  md.anConf.addSample( "TTLLJets_m1to10", "ttX", kViolet+4);
  md.anConf.addSample( "TTWZ",            "ttX", kViolet+4);
  md.anConf.addSample( "TTZH",            "ttX", kViolet+4);
  md.anConf.addSample( "TTZZ",            "ttX", kViolet+4);
  md.anConf.addSample( "TTTT_ext",        "ttX", kViolet+4);
  md.anConf.addSample( "TTWW",            "ttX", kViolet+4);

  md.anConf.addSample( "TTWToLNu", "ttW", kViolet+8);
  // ///md.anConf.addSample( "TTW_LO"

  md.anConf.addSample( "TTHnobb", "ttH", kMagenta+3);
  // //md.anConf.addSample( "TTHnobb_pow"

  md.anConf.addSample( "tZq_ll",  "tZq", kRed+1);

  md.anConf.addSample( "WZTo3LNu_amcatnlo", "WZ", kOrange+7);

  md.anConf.addSample( "TTZToLLNuNu", "ttZ", kOrange-4);

  

  

  //md.anConf.addSample( "Fake:TTJets",                    "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:T_tWch_noFullHad",          "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:T_tch_powheg",              "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:DYJetsToLL_M50_chunk0",     "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:DYJetsToLL_M50_chunk1",     "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:DYJetsToLL_M50_chunk2",     "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:TBar_tWch_noFullHad_0",     "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:TBar_tWch_noFullHad_1",     "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:TBar_tWch_noFullHad_ext_0", "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:TBar_tWch_noFullHad_ext_1", "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:TBar_tch_powheg",           "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:TToLeptons_sch_0",          "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:TToLeptons_sch_1",          "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:WJetsToLNu_LO",             "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:WWTo1L1Nu2Q_0",             "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:WWTo2L2Nu_0",               "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "Fake:ZZTo2L2Nu",                 "pseudodataPoisson", kGray+1);
  // md.anConf.addSample( "WWW_4F",          "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "WZG",             "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "WZZ",             "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "ZZZ",             "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "GGHZZ4L_0",       "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "GGHZZ4L_ext_0",   "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "VBF_HToZZTo4L_0", "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "ZZTo4L_0",        "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "ZZTo4L_1",        "pseudodataPoisson", kAzure-4);
  // md.anConf.addSample( "TTGJets_0",       "pseudodataPoisson", kViolet+4);
  // md.anConf.addSample( "TTGJets_1",       "pseudodataPoisson", kViolet+4);
  // md.anConf.addSample( "TTLLJets_m1to10", "pseudodataPoisson", kViolet+4);
  // md.anConf.addSample( "TTWZ",            "pseudodataPoisson", kViolet+4);
  // md.anConf.addSample( "TTZH",            "pseudodataPoisson", kViolet+4);
  // md.anConf.addSample( "TTZZ",            "pseudodataPoisson", kViolet+4);
  // md.anConf.addSample( "TTTT_ext",        "pseudodataPoisson", kViolet+4);
  // md.anConf.addSample( "TTWW",            "pseudodataPoisson", kViolet+4);
  // md.anConf.addSample( "TTWToLNu", "pseudodataPoisson", kViolet+8);
  // md.anConf.addSample( "TTHnobb", "pseudodataPoisson", kMagenta+3);
  // md.anConf.addSample( "tZq_ll",  "pseudodataPoisson", kRed+1);
  // md.anConf.addSample( "WZTo3LNu_amcatnlo", "pseudodataPoisson", kOrange+7);
  // md.anConf.addSample( "TTZToLLNuNu", "pseudodataPoisson", kOrange-4);



 
  
  //examples ===========================================================================
  //md.anConf.addSample( "TTJets=80", "fake0", kBlue+1); // manual norm
  //md.anConf.addSample( "SR1A:TTJets", "fake1", kOrange-3); //both shape and norm from Fake workflow
  // md.anConf.addSample( "Fake:TTJets=120", "fake2", kBlue+1); //shape from Fake workflow, manual norm

  // md.anConf.addSample( "data:TTJets", "fake3", kBlue+1); //data driven process
  // md.anConf.addSample( "data:Fake:TTJets", "fake4", kBlue+1); //data driven process from Fake workflow
  // md.anConf.addSample( "data:Fake:TTJets=50", "fake5", kBlue+1); //data driven process, Fake workflow, manual norm
  //examples ===========================================================================

  //===============================================================

  //*********************************************************************²

  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
  md.dp.setNormalization( Norm );
  md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
			 yDiv, binning, addBinBkg, overFlowBin,
			 underFlowBin, showDMCRatio, showGrid, 
			 stacking, addSystematics, mcStatSyst,
			 largePad, markerSize, lineWidth,summedSignal, 
			 mcOnly,cmsPrel, uncDet, systSources);
  
  md.prepareDisplay();
 

  md.doPlot();
  //md.producePlots("tiamattZFall17");
  //md.drawDetailSyst(1);
  //md.drawDetailSyst(0);
  //md.dp.addText(xt,yt,st,addText);
  //md.savePlot("TTVAnalysis");
  //gROOT->ProcessLine(".q");
}
