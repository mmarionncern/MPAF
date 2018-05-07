MPAFDisplay md;

void chargeFlip() {
  md.refresh();

  //general parameters ********************* general parameters
  string dir="ChargeFlipAnalyzer";
  string fileName="totalFlip_dataFlip"; // not needed for statistics but provides the normalization
  vector<string> fileList; fileList.push_back("totalFlip");
  //fileList.push_back(""); // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  
  //observables **********************
  md.setObservables("l1PtMVAVT");
    
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=0;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0,0};
  double rangeX[2]={-3,120};
  int xDiv[3]={8,6,0};
  int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
  bool logYScale=false;
  bool overFlowBin=true;
  bool underFlowBin=false;
  bool showDMCRatio=true;
  bool showGrid=false;
  bool largePad=false;
  float markerSize=0.8;
  float lineWidth=2;

  bool summedSignal=false;
  bool stacking=true;

  bool cmsPrel=true;

  float xt=0.68;
  float yt=0.48;
  float st=0.039;
  string addText="";

  string autoBinFile="chargeFlipBinning";
  md.loadAutoBinning(autoBinFile);
  
  //Systematic uncertainties ********************************
  bool addSystematics=false;
  bool mcStatSyst=true;
  bool uncDet=true;
  vector<string> systSources;
  // systSources.push_back("hlt_eff");
  // systSources.push_back("btag");
  //systSources.push_back("theory");

  string Norm="";
  

  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=36700; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsSpring16.db");

  map<string,float> LumisXS;

  //via XSect
  map<string,float> KFactors;
  
  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================
  
  //md.anConf.addSample("","", );
  
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016B_23Sep2016_v3_runs_273150_275376_part1","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016B_23Sep2016_v3_runs_273150_275376_part2","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016C_23Sep2016_v1_runs_271036_284044","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016D_23Sep2016_v1_runs_271036_284044","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016E_23Sep2016_v1_runs_271036_284044","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016F_23Sep2016_v1_runs_271036_284044","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016G_23Sep2016_v1_runs_271036_284044_part1","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016G_23Sep2016_v1_runs_271036_284044_part2","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016H-PromptReco-v2_runs_281207_284035_part1","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016H-PromptReco-v2_runs_281207_284035_part2","pred. data", kOrange-2);
  // md.anConf.addSample("data:SSW:DoubleEG_Run2016H-PromptReco-v3_runs_284036_284044","pred. data", kOrange-2);
  
  md.anConf.addSample("data:SSW:DoubleEG_Run2016B_03Feb2017_ver2_v2_runs_273150_275376","pred. data", kOrange-2);
  md.anConf.addSample("data:SSW:DoubleEG_Run2016C_03Feb2017_v1_runs_271036_284044","pred. data", kOrange-2);
  md.anConf.addSample("data:SSW:DoubleEG_Run2016D_03Feb2017_v1_runs_271036_284044","pred. data", kOrange-2);
  md.anConf.addSample("data:SSW:DoubleEG_Run2016E_03Feb2017_v1_runs_271036_284044","pred. data", kOrange-2);
  md.anConf.addSample("data:SSW:DoubleEG_Run2016F_03Feb2017_v1_runs_271036_284044","pred. data", kOrange-2);
  md.anConf.addSample("data:SSW:DoubleEG_Run2016G_03Feb2017_v1_runs_271036_284044","pred. data", kOrange-2);
  md.anConf.addSample("data:SSW:DoubleEG_Run2016H_03Feb2017_ver2_v1_runs_281085_284035","pred. data", kOrange-2);
  md.anConf.addSample("data:SSW:DoubleEG_Run2016H_03Feb2017_ver3_v1_runs_284036_284044","pred. data", kOrange-2);



  // md.anConf.addSample("SSW:DYJetsToLL_M10to50_LO_treeProducerSusyMultilepton_tree","MCW", kRed+1);
  // md.anConf.addSample("SSW:DYJetsToLL_M50_LO_part1_treeProducerSusyMultilepton_tree","MCW", kRed+1);
  // md.anConf.addSample("SSW:DYJetsToLL_M50_LO_part2_treeProducerSusyMultilepton_tree","MCW", kRed+1);
  // md.anConf.addSample("SSW:DYJetsToLL_M50_LO_part3_treeProducerSusyMultilepton_tree","MCW", kRed+1);
  // md.anConf.addSample("SSW:DYJetsToLL_M50_LO_part4_treeProducerSusyMultilepton_tree","MCW", kRed+1);
  // md.anConf.addSample("SSW:DYJetsToLL_M50_LO_part5_treeProducerSusyMultilepton_tree","MCW", kRed+1);


  // md.anConf.addSample("DYJetsToLL_M10to50_LO_treeProducerSusyMultilepton_tree","MC sig", kBlue+1);
  // md.anConf.addSample("DYJetsToLL_M50_LO_part1_treeProducerSusyMultilepton_tree","MC sig", kBlue+1);
  // md.anConf.addSample("DYJetsToLL_M50_LO_part2_treeProducerSusyMultilepton_tree","MC sig", kBlue+1);
  // md.anConf.addSample("DYJetsToLL_M50_LO_part3_treeProducerSusyMultilepton_tree","MC sig", kBlue+1);
  // md.anConf.addSample("DYJetsToLL_M50_LO_part4_treeProducerSusyMultilepton_tree","MC sig", kBlue+1);
  // md.anConf.addSample("DYJetsToLL_M50_LO_part5_treeProducerSusyMultilepton_tree","MC sig", kBlue+1);


  // md.anConf.addSample("DoubleEG_Run2016B_23Sep2016_v3_runs_273150_275376_part1","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016B_23Sep2016_v3_runs_273150_275376_part2","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016C_23Sep2016_v1_runs_271036_284044","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016D_23Sep2016_v1_runs_271036_284044","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016E_23Sep2016_v1_runs_271036_284044","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016F_23Sep2016_v1_runs_271036_284044","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016G_23Sep2016_v1_runs_271036_284044_part1","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016G_23Sep2016_v1_runs_271036_284044_part2","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016H-PromptReco-v2_runs_281207_284035_part1","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016H-PromptReco-v2_runs_281207_284035_part2","data", kBlack);
  // md.anConf.addSample("DoubleEG_Run2016H-PromptReco-v3_runs_284036_284044","data", kBlack);
  

  md.anConf.addSample("DoubleEG_Run2016B_03Feb2017_ver2_v2_runs_273150_275376","data", kBlack);
  md.anConf.addSample("DoubleEG_Run2016C_03Feb2017_v1_runs_271036_284044","data", kBlack);
  md.anConf.addSample("DoubleEG_Run2016D_03Feb2017_v1_runs_271036_284044","data", kBlack);
  md.anConf.addSample("DoubleEG_Run2016E_03Feb2017_v1_runs_271036_284044","data", kBlack);
  md.anConf.addSample("DoubleEG_Run2016F_03Feb2017_v1_runs_271036_284044","data", kBlack);
  md.anConf.addSample("DoubleEG_Run2016G_03Feb2017_v1_runs_271036_284044","data", kBlack);
  md.anConf.addSample("DoubleEG_Run2016H_03Feb2017_ver2_v1_runs_281085_284035","data", kBlack);
  md.anConf.addSample("DoubleEG_Run2016H_03Feb2017_ver3_v1_runs_284036_284044","data", kBlack);


  //shape uncertainties

 

  //*********************************************************************²
  //Execution macro ******************************************************
  
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
  
 //md.prepareDisplay();
 //md.doPlot();
 md.producePlots("chargeFlipJan18");
 //md.savePlot("chargeFlip");
 //gROOT->ProcessLine(".q");
}
