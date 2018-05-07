MPAFDisplay md;

void testTTV(){
  md.refresh();

  //general parameters ********************* general parameters
  string dir="TTVAnalysis";
  string fileName="test"; //ttvAnalysisNNTest
  vector<string> fileList; fileList.push_back("test");

  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  //}
  
  //observables **********************
  md.setObservables("MetPt");//,"nJets25","HT"); "JetCateg", "NeuralNet"
  
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=0;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0,0};
  double rangeX[2]={0,500};
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

  bool summedSignal=false;
  bool stacking=true;

  bool cmsPrel=true;

  float xt=0.13;
  float yt=0.91;
  float st=0.1;
  string addText="CMS Simulation";

  string autoBinFile="ttvBinning";
  md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=false;
  bool mcStatSyst=false;
  bool uncDet=false;
  vector<string> systSources({"jes",
	"btag:LF:HF:CSVHFStats1:CSVHFStats2:CSVLFStats1:CSVLFStats2:CSVCFErr1:CSVCFErr2"
	//"btag:btagJ"
	});
  
  string Norm="norm";
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=35900; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsSpring16.db");

  map<string,float> LumisXS;

  //via XSect
  
  map<string,float> KFactors;
 
  // if( md.isInitStatus() )
  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

   // md.anConf.addSample( "TTLLJets_m1to10" , "tt#gamma", kViolet-4 );
   // md.anConf.addSample( "tZW_ll"          , "tZW", kAzure-4 );
  //md.anConf.addSample( "tZq_ll"          , "tZq", kBlue+1 );
   
   //md.anConf.addSample( "TTTT"            , "4t", kGreen+1 );
  
  //md.anConf.addSample( "TTWToLNu_ext1"       , "ttW", kMagenta+3 );
  // md.anConf.addSample( "TTWToLNu_ext2_part1" , "ttW", kMagenta+3 );
  // md.anConf.addSample( "TTWToLNu_ext2_part2" , "ttW", kMagenta+3 );

  // md.anConf.addSample( "TTHnobb_pow" , "higgs", kOrange+7 );
  //md.anConf.addSample( "VHToNonbb"   , "higgs", kOrange+7 );
  
  //md.anConf.addSample( "WZTo3LNu_amcatnlo" , "WZ", kOrange-4 );
  // //md.anConf.addSample( "WZTo3LNu"    , "WZ", kOrange-4 ); //kOrange-4
  
  // //md.anConf.addSample( "TTZToLLNuNu_ext2","ttZ", kRed+1 );
  //md.anConf.addSample( "TTZToLLNuNu"   , "ttZ", kRed+1 );
 
  
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
  //md.drawDetailSyst(1);
  //md.drawDetailSyst(0);
  //md.dp.addText(xt,yt,st,addText);
  md.savePlot("TTVAnalysis");
  //gROOT->ProcessLine(".q");
}
