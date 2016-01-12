MPAFDisplay md;

void ssdl2015Plot(){
  md.refresh();

  //general parameters ********************* general parameters
  string dir="SSDL2015";
  string fileName="fakeEstim_test";
  string fileList="fakeEstim_test";
  
  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  //}
  
  //observables **********************
  md.dp.setObservables("jetPtRelVsPtRatio");
    
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=4;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0,200};
  double rangeX[2]={0,200};
  int xDiv[3]={8,6,0};
  int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
  bool logYScale=false;
  bool overFlowBin=false;
  bool underFlowBin=false;
  bool showDMCRatio=true;
  bool showGrid=false;
  float markerSize=0.8;
  float lineWidth=2;

  bool summedSignal=false;
  bool stacking=true;

  bool cmsPrel=true;

  float xt=0.68;
  float yt=0.48;
  float st=0.039;
  string addText="";

  //string autoBinFile="susybinninghigh";
  //md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=false;
  
  bool mcStatSyst=true;
  string systSources="";

  bool uncDet=false;

  string Norm="";
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=10000; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsPhys14.db");

  map<string,float> LumisXS;

  //via XSect
  
  map<string,float> KFactors;
 
  // if( md.isInitStatus() )
  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
  

  //control categories ==============================
  //md.anConf.setControlCategs("Fake");
  //===============================================================
  
  md.anConf.addSample( "TTJetsfake", "fake", kBlack); 
  //md.anConf.addSample( "TTJets", "t#bar{t}", kGray+2); 

  // md.anConf.addSample( "T1ttbbWW_mGo1300_mCh300_mChi290", "T1ttbbWW(1.3/0.3/0.29)", kRed+1); 
  // md.anConf.addSample( "T5qqqqWW_mGo1500_mCh800_mChi100", "T5qqqq()", kOrange+7); 
  // md.anConf.addSample( "T6ttWW_mSbot600_mCh425_mChi50", "T6t2W264", kOrange-3); 
  // md.anConf.addSample( "T6ttWW_mSbot650_mCh150_mChi50", "T6t2W261", kGreen-3); 
  // md.anConf.addSample( "SMS_T1tttt_2J_mGl1500_mLSP100", "T1t415", kBlue+1); 
  // md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280_dil", "T5t4Deg", kViolet+1); 
  //md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280_dil", "T5t4Deg", kBlack); 
  //md.anConf.addSample( "TTJets", "t#bar{t}", kWhite); 
  
  //md.anConf.addSample( "TTJets=80", "fake0", kBlue+1); // manual norm
  //md.anConf.addSample( "SR1A:TTJets", "fake1", kOrange-3); //both shape and norm from Fake workflow
  // md.anConf.addSample( "Fake:TTJets=120", "fake2", kBlue+1); //shape from Fake workflow, manual norm

  // md.anConf.addSample( "data:TTJets", "fake3", kBlue+1); //data driven process
  // md.anConf.addSample( "data:Fake:TTJets", "fake4", kBlue+1); //data driven process from Fake workflow
  // md.anConf.addSample( "data:Fake:TTJets=50", "fake5", kBlue+1); //data driven process, Fake workflow, manual norm
  

  //===============================================================

  //*********************************************************************²

  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
  md.dp.setNormalization( Norm );
  md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
			 yDiv, binning, addBinBkg, overFlowBin,
			 underFlowBin, showDMCRatio, showGrid, 
			 stacking, addSystematics, mcStatSyst,
			 markerSize, lineWidth,summedSignal, 
			 mcOnly,cmsPrel, uncDet);
  
  md.prepareDisplay();
  md.doPlot();
  //md.getStatistics("nominal");

  //md.drawStatistics("global_BR00H", "selected");

  //md.savePlot("SUSY3L");
  // md.dp.addText(xt,yt,st,addText);

}
