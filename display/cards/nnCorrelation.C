MPAFDisplay md;

void nnCorrelation() {
  md.refresh();

  //general parameters ********************* general parameters
  string dir="CorrelationAnalysis";
  string fileName="correlation_jets"; // not needed for statistics but provides the normalization
  vector<string> fileList; fileList.push_back("correlation_jets");
  //fileList.push_back(""); // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  
  //observables **********************
  md.setObservables("Jet_btagCSV[jetIdx]0VsoutputLayerlstm_btag_lstm2_nnl0");
    
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=1;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={-1,1.02};
  double rangeX[2]={-1,1.02};
  int xDiv[3]={8,6,0};
  int yDiv[3]={8,6,0}; //Nlabel /  sous-Div /ssdiv
  bool logYScale=true;
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

  string autoBinFile="NNCorrelationBinning";
  //md.loadAutoBinning(autoBinFile);
  
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
  // md.anConf.addSample("TTZToLLNuNu_ext2","all", kBlack);
  // md.anConf.addSample("WZTo3LNu_amcatnlo","all", kBlack);

  md.anConf.addSample("TTZToLLNuNu_ext2","ttZ", kBlack);
  // md.anConf.addSample("WZTo3LNu_amcatnlo","WZ", kBlack);
  
  //md.anConf.addSample("TTZToLLNuNu_ext2","poisson", kBlack);
  // md.anConf.addSample("WZTo3LNu_amcatnlo","pseudodata", kBlack);
  



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
 md.doPlot();
 //md.producePlots("nnCorrelationBTag");
 //md.savePlot("chargeFlip");
 //gROOT->ProcessLine(".q");
}
