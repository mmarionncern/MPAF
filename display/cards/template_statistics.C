MPAFDisplay md;

void susy_FLAVVAL_SRVAL_ISOVAL(){
  // if(Recompute) {
  //   MPAFDisplay md;
 
  //   //Bloody René Brun
  //   bool * rtmp= const_cast<bool*> pr;
  //   *rtmp = false;

  // }
  // else
  md.refresh();


  //general parameters ********************* general parameters
  string dir="FakeEstim";
  string fileName="susy_FLAVVAL_SRVAL_ISOVAL"; // not needed for statistics
  string fileList="susy_FLAVVAL_SRVAL_ISOVAL"; // put command line that gives all files as in a "ls" command
  //string fileList="phys14exerc_SIGNALREGION_PTSCENARIO_FLAVORS"; // put command line that gives all files as in a "ls" command
  string hName=""; // not needed for statistics

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList, hName );
  md.anConf.configureData(false, 0, mcOnly);
 
  //Systematic uncertainties ********************************
  // bool addSystematics=true;
  
  // bool mcStatSyst=true;
  // string systSources="";

  // bool uncDet=false;

  string Norm="";
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=10000; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  map<string,float> LumisXS;

  LumisXS["SMS_T1tttt_2J_mGl1200_mLSP800"] = 100322/(0.0856418);
  LumisXS["SMS_T1tttt_2J_mGl1500_mLSP100"] = 105679/(0.0141903);
  LumisXS["T5ttttDeg_mGo1000_mStop300_mCh285_mChi280_dil"] = 75914/(0.325388);
  LumisXS["T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"] = 52499/(0.325388);
  //  LumisXS["T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"] = ;
  LumisXS["TTH"] = 199700/0.5085;
  LumisXS["TTJets"] = 25446993/809.1;
  LumisXS["TTWJets"] = 246521/0.6647;
  LumisXS["TTZJets"] = 249275/0.8565;
  LumisXS["WJetsToLNu_HT100to200"] = 5262265/(1817.0*1.23);
  LumisXS["WJetsToLNu_HT200to400"] = 4936077/(471.6*1.23);
  LumisXS["WJetsToLNu_HT400to600"] = 4640594/(55.61*1.23);
  LumisXS["WJetsToLNu_HT600toInf"] = 4581841/(18.81*1.23);
  LumisXS["WZJetsTo3LNu"] = 237484/2.29;
  LumisXS["DYJetsToLL_M50_HT100to200"] = 4054159/(194.3*1.27);
  LumisXS["DYJetsToLL_M50_HT200to400"] = 4666496/(52.24*1.27);
  LumisXS["DYJetsToLL_M50_HT400to600"] = 4931372/( 6.546*1.27);
  LumisXS["DYJetsToLL_M50_HT600toInf"] = 4493574/( 2.179*1.27);


  //via XSect
  
  map<string,float> KFactors;
  // if( md.isInitStatus() )
  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================
  //md.anConf.addSample( "WJetsToLNu_13TeV-madgraph-pythia8-tauola_skim"                    , "W+Jets", kAzure-2); 

  md.anConf.addSample( "TTJets"                                         , "t\\bar{t}", kAzure-2); 

  md.anConf.addSample( "WJetsToLNu_HT100to200"                          , "WJ", kAzure-2); 
  md.anConf.addSample( "WJetsToLNu_HT200to400"                          , "WJ", kAzure-2); 
  md.anConf.addSample( "WJetsToLNu_HT400to600"                          , "WJ", kAzure-2); 
  md.anConf.addSample( "WJetsToLNu_HT600toInf"                          , "WJ", kAzure-2); 

  md.anConf.addSample( "DYJetsToLL_M50_HT100to200"                      , "DY", kAzure-2);
  md.anConf.addSample( "DYJetsToLL_M50_HT200to400"                      , "DY", kAzure-2);
  md.anConf.addSample( "DYJetsToLL_M50_HT400to600"                      , "DY", kAzure-2);
  md.anConf.addSample( "DYJetsToLL_M50_HT600toInf"                      , "DY", kAzure-2);

  md.anConf.addSample( "WZJetsTo3LNu"                                   , "rare", kAzure-2);
  md.anConf.addSample( "TTH"                                            , "rare", kAzure-2);
  md.anConf.addSample( "TTWJets"                                        , "rare", kAzure-2);
  md.anConf.addSample( "TTZJets"                                        , "rare", kAzure-2);

  md.anConf.addSample( "SMS_T1tttt_2J_mGl1200_mLSP800"                  , "T14t12", kAzure-2);
  md.anConf.addSample( "SMS_T1tttt_2J_mGl1500_mLSP100"                  , "T14t15", kAzure-2);
  md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"  , "T54tDeg", kAzure-2);
  //md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"

  
   

  // }
  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
 
  //Configuration ================
  //if( md.isInitStatus() ) {
  
  //md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
  // }

  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
  md.dp.setNormalization( Norm );
  // md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
  //         yDiv, binning, addBinBkg, overFlowBin,
  //         underFlowBin, showDMCRatio, showGrid,
  //         stacking, addSystematics, mcStatSyst,
  //         markerSize, lineWidth,summedSignal,
  //         mcOnly,cmsPrel, uncDet);

  md.prepareDisplay();
  //md.doPlot();
  md.getStatistics();
  //md.makeDataCard(fileList, "global", "SR b-jet multiplicity");
  //md.savePlot("phys14exerc");
  // md.dp.addText(xt,yt,st,addText);

  gROOT->ProcessLine(".q");

}
