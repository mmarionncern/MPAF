MPAFDisplay md;

void ssdl2015JES(){
  md.refresh();

  //general parameters ********************* general parameters
  string dir="SSDL2015";
  string fileName="ssdlUncProd";
  string fileList="ssdlUncProd";
  
  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  //}
  
  //observables **********************
  md.setObservables("MET");
    
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=1;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0,0};
  double rangeX[2]={0,200};
  int xDiv[3]={8,6,0};
  int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
  bool logYScale=false;
  bool overFlowBin=true;
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
  bool addSystematics=true;
  
  bool mcStatSyst=false;
  string systSources="";

  bool uncDet=true;

  string Norm="";
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=1; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  //md.anConf.loadXSDB("XSectionsSpring15.db");

  map<string,float> LumisXS;

  //via XSect
  
  map<string,float> KFactors;
 
  // if( md.isInitStatus() )
  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
  

  //control categories ==============================
  //md.anConf.setControlCategs("Fake");
  //===============================================================
  
  //md.anConf.addSample( "TTJets", "TTJets", kBlack); 

  // md.anConf.addSample( "TTHnobb", "rare", kOrange-2); 
  //md.anConf.addSample( "TTWToLNu", "rare", kOrange-2); 
  //md.anConf.addSample( "TTZToLLNuNu", "rare", kOrange-2); 

  //md.anConf.addSample( "_standard_prompt_ttW", "ttW", kOrange-2);

  md.anConf.addSample( "WZTo3LNu", "_standard_prompt_WZ", kOrange-2); 

  md.anConf.addSample( "TTWToLNu", "_standard_prompt_ttW", kOrange-2); 
  md.anConf.addSample( "TTZToLLNuNu", "_standard_prompt_ttZH", kOrange-2); 
  md.anConf.addSample( "TTHnobb", "_standard_prompt_ttZH", kOrange-2); 
  md.anConf.addSample( "GGHZZ4L", "_standard_prompt_Rares", kOrange-2); 
  // md.anConf.addSample( "TBar_tWch", "_standard_prompt_Rares", kOrange-2); 
  // md.anConf.addSample( "TToLeptons_sch_amcatnlo", "_standard_prompt_Rares", kOrange-2); 
  // md.anConf.addSample( "TToLeptons_tch", "_standard_prompt_Rares", kOrange-2); 
  // md.anConf.addSample( "T_tWch", "_standard_prompt_Rares", kOrange-2); 
  // md.anConf.addSample( "TbarToLeptons_tch", "_standard_prompt_Rares", kOrange-2); 
  md.anConf.addSample( "VHToNonbb", "_standard_prompt_Rares", kOrange-2); 
  md.anConf.addSample( "WWTo2L2Nu", "_standard_prompt_Rares", kOrange-2); 
  md.anConf.addSample( "WWZ", "_standard_prompt_Rares", kOrange-2); 
  md.anConf.addSample( "WZZ", "_standard_prompt_Rares", kOrange-2); 
  md.anConf.addSample( "ZZTo4L", "_standard_prompt_Rares", kOrange-2); 
  md.anConf.addSample( "ZZZ", "_standard_prompt_Rares", kOrange-2); 
  md.anConf.addSample( "WWDouble", "_standard_prompt_Rares", kOrange-2); 

  md.anConf.addSample( "WpWpJJ", "WWss", kOrange-2); 

  md.anConf.addSample( "TGJets", "XG",  kOrange-2); 
  md.anConf.addSample( "TTGJets", "XG",  kOrange-2);
  md.anConf.addSample( "WGToLNuG", "XG",  kOrange-2);

  md.anConf.addSample( "T1tttt_mGo1200_mChi800", "_sig_T1t_1200_800",  kOrange-2); 
  md.anConf.addSample( "T1tttt_mGo1500_mChi100", "_sig_T1t_1500_100",  kOrange-2); 
  md.anConf.addSample( "T5qqqqWWDeg_mGo1000_mCh315_mChi300_dilep", "sig_T5Deg",  kOrange-2); 
  md.anConf.addSample( "T5qqqqWW_mGo1200_mCh1000_mChi800_dilep", "_sig_T5q",  kOrange-2); 
  md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280", "_sig_T5t",  kOrange-2); 
  md.anConf.addSample( "T6ttWW_mSbot600_mCh425_mChi50", "_sig_T6_600_425",  kOrange-2); 
  md.anConf.addSample( "T6ttWW_mSbot650_mCh150_mChi50", "_sig_T6_650_150",  kOrange-2); 

  // md.anConf.addSample( "T1ttbbWW_mGo1300_mCh300_mChi290", "T1ttbbWW", kBlack); 
  // md.anConf.addSample( "T5qqqqWW_mGo1500_mCh800_mChi100", "T5qqqqWW", kBlack); 
  // md.anConf.addSample( "T6ttWW_mSbot600_mCh425_mChi50", "T6ttWW64", kBlack); 
  // md.anConf.addSample( "T6ttWW_mSbot650_mCh150_mChi50", "T6ttWW61", kBlack); 
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
  //md.doPlot();
  //md.getStatistics("nominal");
  //md.addExternalSystUnc("rare","btag",30,-30);
  
  // md.addExternalSystUnc("rare","btag",+0.53, -0.52,"global_HHSR1","selected");
  // md.addExternalSystUnc("rare","btag",+0.83, -0.82,"global_HHSR2","selected");
  // md.addExternalSystUnc("rare","btag", +0.52, -0.52,"global_HHSR3","selected");
  // md.addExternalSystUnc("rare","btag", +1.03, -1.02,"global_HHSR4","selected");
  // md.addExternalSystUnc("rare","btag", +0.85, -0.85,"global_HHSR5","selected");
  // md.addExternalSystUnc("rare","btag", +1.23, -1.21,"global_HHSR6","selected");
  // md.addExternalSystUnc("rare","btag", +0.68, -0.68,"global_HHSR7","selected");
  // md.addExternalSystUnc("rare","btag", +1.05, -1.04,"global_HHSR8","selected");
  // md.addExternalSystUnc("rare","btag",-5.20, +5.16,"global_HHSR9","selected");
  // md.addExternalSystUnc("rare","btag",-6.54, +6.46,"global_HHSR10","selected");
  // md.addExternalSystUnc("rare","btag",-5.29, +5.25,"global_HHSR11","selected");
  // md.addExternalSystUnc("rare","btag",-5.61, +5.50,"global_HHSR12","selected");
  // md.addExternalSystUnc("rare","btag",-6.55, +6.46,"global_HHSR13","selected");
  // md.addExternalSystUnc("rare","btag",-5.60, +5.49,"global_HHSR14","selected");
  // md.addExternalSystUnc("rare","btag",-6.87, +6.77,"global_HHSR15","selected");
  // md.addExternalSystUnc("rare","btag",-5.53, +5.42,"global_HHSR16","selected");
  // md.addExternalSystUnc("rare","btag",-10.42, +10.96,"global_HHSR17","selected");
  // md.addExternalSystUnc("rare","btag",-13.06, +13.91,"global_HHSR18","selected");
  // md.addExternalSystUnc("rare","btag",-10.72, +11.30,"global_HHSR19","selected");
  // md.addExternalSystUnc("rare","btag",-11.64, +12.25,"global_HHSR20","selected");
  // md.addExternalSystUnc("rare","btag",-13.40, +14.27,"global_HHSR21","selected");
  // md.addExternalSystUnc("rare","btag",-12.97, +13.66,"global_HHSR22","selected");
  // md.addExternalSystUnc("rare","btag",-16.12, +17.54,"global_HHSR23","selected");
  // md.addExternalSystUnc("rare","btag",-13.98, +14.96,"global_HHSR24","selected");
  // md.addExternalSystUnc("rare","btag",-14.47, +15.97,"global_HHSR25","selected");
  // md.addExternalSystUnc("rare","btag",-17.29, +19.25,"global_HHSR26","selected");
  // md.addExternalSystUnc("rare","btag",-9.34, +9.67,"global_HHSR27","selected");
  // md.addExternalSystUnc("rare","btag",-19.62, +22.12,"global_HHSR28","selected");
  // md.addExternalSystUnc("rare","btag",-16.09, +17.96,"global_HHSR29","selected");
  // md.addExternalSystUnc("rare","btag",-13.79, +14.98,"global_HHSR30","selected");
  // md.addExternalSystUnc("rare","btag",-6.11, +6.32,"global_HHSR31","selected");
  // md.addExternalSystUnc("rare","btag",-8.86, +9.47,"global_HHSR32","selected");
  // md.addExternalSystUnc("rare","btag",+0.55, -0.55,"global_HLSR1","selected");
  // md.addExternalSystUnc("rare","btag",+0.89, -0.88,"global_HLSR2","selected");
  // md.addExternalSystUnc("rare","btag",+0.61, -0.61,"global_HLSR3","selected");
  // md.addExternalSystUnc("rare","btag",+1.01, -1.00,"global_HLSR4","selected");
  // md.addExternalSystUnc("rare","btag",+0.83, -0.83,"global_HLSR5","selected");
  // md.addExternalSystUnc("rare","btag",+1.53, -1.51,"global_HLSR6","selected");
  // md.addExternalSystUnc("rare","btag",-5.17, +5.13,"global_HLSR7","selected");
  // md.addExternalSystUnc("rare","btag",-6.01, +5.93,"global_HLSR8","selected");
  // md.addExternalSystUnc("rare","btag",-6.96, +6.85,"global_HLSR9","selected");
  // md.addExternalSystUnc("rare","btag",-6.85, +6.73,"global_HLSR10","selected");
  // md.addExternalSystUnc("rare","btag",-6.95, +6.86,"global_HLSR11","selected");
  // md.addExternalSystUnc("rare","btag",-7.50, +7.35,"global_HLSR12","selected");
  // md.addExternalSystUnc("rare","btag",-10.63, +11.19,"global_HLSR13","selected");
  // md.addExternalSystUnc("rare","btag",-13.36, +14.27,"global_HLSR14","selected");
  // md.addExternalSystUnc("rare","btag",-13.94, +15.05,"global_HLSR15","selected");
  // md.addExternalSystUnc("rare","btag",-10.84, +11.35,"global_HLSR16","selected");
  // md.addExternalSystUnc("rare","btag",-14.77, +15.91,"global_HLSR17","selected");
  // md.addExternalSystUnc("rare","btag",-11.49, +12.00,"global_HLSR18","selected");
  // md.addExternalSystUnc("rare","btag",-14.44, +15.96,"global_HLSR19","selected");
  // md.addExternalSystUnc("rare","btag",-20.67, +24.32,"global_HLSR20","selected");
  // md.addExternalSystUnc("rare","btag",-100.00, -100.00,"global_HLSR21","selected");
  // md.addExternalSystUnc("rare","btag",-17.75, +19.57,"global_HLSR22","selected");
  // md.addExternalSystUnc("rare","btag",+0.24, -0.77,"global_HLSR23","selected");
  // md.addExternalSystUnc("rare","btag",-3.21, +3.76,"global_HLSR24","selected");
  // md.addExternalSystUnc("rare","btag",-7.38, +7.82,"global_HLSR25","selected");
  // md.addExternalSystUnc("rare","btag",-7.23, +7.45,"global_HLSR26","selected");
  // md.addExternalSystUnc("rare","btag",+0.61, -0.61,"global_LLSR1","selected");
  // md.addExternalSystUnc("rare","btag",+1.19, -1.17,"global_LLSR2","selected");
  // md.addExternalSystUnc("rare","btag",-7.67, +7.55,"global_LLSR3","selected");
  // md.addExternalSystUnc("rare","btag",-11.20, +11.00,"global_LLSR4","selected");
  // md.addExternalSystUnc("rare","btag",-14.26, +15.20,"global_LLSR5","selected");
  // md.addExternalSystUnc("rare","btag",-6.67, +6.27,"global_LLSR6","selected");
  // md.addExternalSystUnc("rare","btag",-25.41, +30.13,"global_LLSR7","selected");
  // md.addExternalSystUnc("rare","btag",-100.00, -100.00,"global_LLSR8","selected");

  
  md.getCategSystematic("BTAG","HH","selected");
  md.getCategSystematic("BTAG","HL","selected");
  md.getCategSystematic("BTAG","LL","selected");
  gROOT->ProcessLine(".q");
    //md.drawStatistics("global_BR00H", "selected");

  //md.savePlot("SUSY3L");
  // md.dp.addText(xt,yt,st,addText);

}
