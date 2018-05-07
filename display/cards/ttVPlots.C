MPAFDisplay md;

void ttVPlots(){
  md.refresh();

  //general parameters ********************* general parameters
  string dir="TTVAnalysis";
  string fileName="ttvAnalysisNNMulti"; //ttvAnalysisNNTest
  vector<string> fileList; fileList.push_back("ttvAnalysisNNMulti");

  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  //}
  
  //observables **********************
  md.setObservables("elMvaTTHBarrel");//"NN2DWZtZq","NN2DWZtZW","NN2DWZttH");
  //"NN2DtZqtZW","NN2DtZqttH","NN2DtZWttH");//,"nJets25","HT"); "JetCateg", "NeuralNet"
  
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=1;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0.,0};
  double rangeX[2]={-1,100};
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

  // string autoBinFile="ttvBinning";
  // md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=true;
  bool mcStatSyst=false;
  bool uncDet=false;
  vector<string> systSources ({"jes",
	"btag:LF:HF:CSVHFStats1:CSVHFStats2:CSVLFStats1:CSVLFStats2:CSVCFErr1:CSVCFErr2"});
	//"btag:btagJ"})
			     
  
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

  // md.anConf.addSample( "WGToLNuG"      , "EWK", kAzure-4 );
  // md.anConf.addSample( "WpWpJJ"        , "EWK", kAzure-4 );
  // md.anConf.addSample( "WWDouble" , "EWK", kAzure-4 );
  // // md.anConf.addSample( "WWG"           , "EWK", kAzure-4 );
  // // md.anConf.addSample( "WWTo2L2Nu"     , "EWK", kAzure-4 );
  // md.anConf.addSample( "WWW"           , "EWK", kAzure-4 );
  // // md.anConf.addSample( "WZG"           , "EWK", kAzure-4 );
  // md.anConf.addSample( "WZZ"           , "EWK", kAzure-4 );
  // md.anConf.addSample( "ZGTo2LG"       , "EWK", kAzure-4 );
  // // md.anConf.addSample( "ZZTo2L2Nu"     , "EWK", kAzure-4 );
  // md.anConf.addSample( "ZZTo4L"        , "EWK", kAzure-4 );
  // md.anConf.addSample( "ZZZ"           , "EWK", kAzure-4 );
  
  // md.anConf.addSample( "Fake:DYJetsToLL_M10to50_LO"               , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:DYJetsToLL_M50_LO"                   , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TBar_tch_powheg"                  , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TGJets"                           , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:T_tch_powheg"                     , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTGJets"                          , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_DiLepton"                  , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_DiLepton_ext"              , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromTbar_ext"  , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromT_ext"     , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromT"         , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTZToQQ"                          , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:WJetsToLNu"                       , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:WZTo2L2Q"                         , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTWToQQ"                          , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:WGToLNuG"                         , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:WpWpJJ"                           , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:WWDouble"                    , "fake (MC)", kGray+1 );
  // // md.anConf.addSample( "Fake:WWG"                              , "fake (MC)", kGray+1 );
  // // md.anConf.addSample( "Fake:WWTo2L2Nu"                        , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:WWW"                              , "fake (MC)", kGray+1 );
  // // md.anConf.addSample( "Fake:WZG"                              , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:WZZ"                              , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:ZGTo2LG"                          , "fake (MC)", kGray+1 );
  // // md.anConf.addSample( "Fake:ZZTo2L2Nu"                        , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:ZZTo4L"                           , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:ZZZ"                              , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTTT"                             , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTLLJets_m1to10"                  , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:tZq_ll_HS"                        , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:tZW_ll_ext_HS"                    , "fake (MC)", kGray+1 );
  // // md.anConf.addSample( "Fake:TTWToLNu_ext1"                    , "fake (MC)", kGray+1 );
  // // md.anConf.addSample( "Fake:TTWToLNu_ext2_part1"              , "fake (MC)", kGray+1 );
  // // md.anConf.addSample( "Fake:TTWToLNu_ext2_part2"              , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTHnobb_pow_HS"                      , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:VHToNonbb"                        , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:WZTo3LNu_amcatnlo_HS"                , "fake (MC)", kGray+1 );
  // md.anConf.addSample( "Fake:TTZToLLNuNu_ext2_HS"              , "fake (MC)", kGray+1 );

  // md.anConf.addSample( "TTLLJets_m1to10" , "ttll", kViolet-4 );
  // md.anConf.addSample( "TTTT"            , "4t", kViolet-3 );

  // md.anConf.addSample( "tZq_ll"          , "tZq", kViolet+4 );
  // md.anConf.addSample( "tZW_ll_ext_HS"      , "tZW", kViolet+8 );
  
  // md.anConf.addSample( "TTWToLNu_ext1"       , "ttW", kMagenta+3 );
  // md.anConf.addSample( "TTWToLNu_ext2_part1" , "ttW", kMagenta+3 );
  // md.anConf.addSample( "TTWToLNu_ext2_part2" , "ttW", kMagenta+3 );

  // md.anConf.addSample( "TTHnobb_pow_HS" , "ttH", kOrange+7 );
  // md.anConf.addSample( "VHToNonbb"   , "higgs", kOrange+4 );
  
  //md.anConf.addSample( "WZTo3LNu_amcatnlo" , "WZ", kOrange-4 );
  
  //md.anConf.addSample( "TTZToLLNuNu_ext2","ttZ sig", kRed+1 );

  md.anConf.addSample( "TTZToLLNuNu_ext2","ttZ", kRed+1 );
  md.anConf.addSample( "TTZToLLNuNu_ext2","ttZ", kRed+1 );
  md.anConf.addSample( "TTZToLLNuNu_ext2","ttZ", kRed+1 );
  md.anConf.addSample( "TTZToLLNuNu_ext2","ttZ", kRed+1 );

  // == pseudo data =====================================
  // md.anConf.addSample( "WGToLNuG"      , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "WpWpJJ"        , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "WW2L2NuDouble" , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "WWG"           , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "WWTo2L2Nu"     , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "WWW"           , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "WZG"           , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "WZZ"           , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "ZGTo2LG"       , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "ZZTo2L2Nu"     , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "ZZTo4L"        , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "ZZZ"           , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:DYJetsToLL_M10to50"               , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:DYJetsToLL_M50"                   , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TBar_tch_powheg"                  , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TGJets"                           , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:T_tch_powheg"                     , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTGJets"                          , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTJets_DiLepton"                  , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTJets_DiLepton_ext"              , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromTbar_ext"  , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromT_ext"     , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromT"         , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTZToQQ"                          , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WJetsToLNu"                       , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WZTo2L2Q"                         , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTWToQQ"                          , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WGToLNuG"                         , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WpWpJJ"                           , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WW2L2NuDouble"                    , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WWG"                              , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WWTo2L2Nu"                        , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WWW"                              , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WZG"                              , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WZZ"                              , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:ZGTo2LG"                          , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:ZZTo2L2Nu"                        , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:ZZTo4L"                           , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:ZZZ"                              , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTTT"                             , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTLLJets_m1to10"                  , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:tZq_ll"                           , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:tZW_ll"                           , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTWToLNu_ext1"                    , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTWToLNu_ext2_part1"              , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTWToLNu_ext2_part2"              , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTHnobb_pow"                      , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:VHToNonbb"                        , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:WZTo3LNu_amcatnlo"                , "pseudodataPoisson", kBlack );
  // // //md.anConf.addSample( "Fake:WZTo3LNu"                         , "pseudodataPoisson", kBlack );
  // // //md.anConf.addSample( "Fake:TTZToLLNuNu_ext2"                 , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "Fake:TTZToLLNuNu"                      , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "TTLLJets_m1to10" , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "tZq_ll"          , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "tZW_ll_ext"          , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "TTTT"          , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "TTWToLNu_ext1"       , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "TTWToLNu_ext2_part1" , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "TTWToLNu_ext2_part2" , "pseudodataPoisson", kBlack );
  //  md.anConf.addSample( "TTHnobb_pow" , "pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "VHToNonbb"   , "pseudodataPoisson", kBlack );
  // md.anConf.addSample( "WZTo3LNu_amcatnlo" , "pseudodataPoisson", kBlack );
  // // //md.anConf.addSample( "WZTo3LNu"    , "pseudodataPoisson", kBlack ); //kOrange-4
  // md.anConf.addSample( "TTZToLLNuNu_ext2","pseudodataPoisson", kBlack );
  // // md.anConf.addSample( "TTZToLLNuNu"   , "pseudodataPoisson", kBlack );


  
 
  
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
  //md.savePlot("TTVAnalysis");
  //gROOT->ProcessLine(".q");
}
