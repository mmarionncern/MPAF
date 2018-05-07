MPAFDisplay md;

void ttVCardMaker(){
  md.refresh();

  //general parameters ********************* general parameters
  string dir="TTVAnalysis";
  string fileName="ttvAnalysisNNMulti";
  vector<string> fileList; fileList.push_back("ttvAnalysisNNMulti");

  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  //}
  
  //observables **********************
  //md.setObservables("JetCateg");
  //,"nJets25","HT");"JetCateg","NeuralNetSignal","NNCateg","NNMulti" TiamattZCateg
  
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=1;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0,0};
  double rangeX[2]={0,10};
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

  float xt=0.13;
  float yt=0.91;
  float st=0.1;
  string addText="CMS Simulation";

  string autoBinFile="ttvBinning";
  md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=true;
  bool mcStatSyst=false;
  bool uncDet=true;
  vector<string> systSources; //({"jes"})
  
  string Norm="";
  
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
  // md.anConf.addSample( "WW2L2NuDouble" , "EWK", kAzure-4 );
  // md.anConf.addSample( "WWG"           , "EWK", kAzure-4 );
  // md.anConf.addSample( "WWTo2L2Nu"     , "EWK", kAzure-4 );
  // md.anConf.addSample( "WWW"           , "EWK", kAzure-4 );
  // md.anConf.addSample( "WZG"           , "EWK", kAzure-4 );
  // md.anConf.addSample( "WZZ"           , "EWK", kAzure-4 );
  // md.anConf.addSample( "ZGTo2LG"       , "EWK", kAzure-4 );
  // md.anConf.addSample( "ZZTo2L2Nu"     , "EWK", kAzure-4 );
  // md.anConf.addSample( "ZZTo4L"        , "EWK", kAzure-4 );
  // md.anConf.addSample( "ZZZ"           , "EWK", kAzure-4 );

  // md.anConf.addSample( "Fake:DYJetsToLL_M10to50"               , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:DYJetsToLL_M50"                   , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TBar_tch_powheg"                  , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TGJets"                           , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:T_tch_powheg"                     , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTGJets"                          , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_DiLepton"                  , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_DiLepton_ext"              , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromTbar_ext"  , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromT_ext"     , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromT"         , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTZToQQ"                          , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WJetsToLNu"                       , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WZTo2L2Q"                         , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTWToQQ"                          , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WGToLNuG"                         , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WpWpJJ"                           , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WW2L2NuDouble"                    , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WWG"                              , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WWTo2L2Nu"                        , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WWW"                              , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WZG"                              , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WZZ"                              , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:ZGTo2LG"                          , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:ZZTo2L2Nu"                        , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:ZZTo4L"                           , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:ZZZ"                              , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTTT"                             , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTLLJets_m1to10"                  , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:tZq_ll"                           , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:tZW_ll"                           , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTWToLNu_ext1"                    , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTWToLNu_ext2_part1"              , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTWToLNu_ext2_part2"              , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTHnobb_pow"                      , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:VHToNonbb"                        , "fake", kGray+1 );
  // //md.anConf.addSample( "Fake:WZTo3LNu_amcatnlo"                , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:WZTo3LNu"                         , "fake", kGray+1 );
  // //md.anConf.addSample( "Fake:TTZToLLNuNu_ext2"                 , "fake", kGray+1 );
  // md.anConf.addSample( "Fake:TTZToLLNuNu"                      , "fake", kGray+1 );

  //md.anConf.addSample( "TTLLJets_m1to10" , "ttX", kViolet-4 );
  md.anConf.addSample( "tZq_ll"          , "ttX", kViolet-4 );
  md.anConf.addSample( "tZW_ll_ext"          , "tZW", kViolet-1 );
  //md.anConf.addSample( "TTTT"            , "ttX", kViolet-4 );
  
   // md.anConf.addSample( "TTWToLNu_ext1"       , "ttW", kMagenta+3 );
   // md.anConf.addSample( "TTWToLNu_ext2_part1" , "ttW", kMagenta+3 );
   // md.anConf.addSample( "TTWToLNu_ext2_part2" , "ttW", kMagenta+3 );
   
   md.anConf.addSample( "TTHnobb_pow" , "higgs", kOrange+7 );
   //md.anConf.addSample( "VHToNonbb"   , "higgs", kOrange+7 );
  
   md.anConf.addSample( "WZTo3LNu_amcatnlo" , "WZ", kOrange-4 );
   // //md.anConf.addSample( "WZTo3LNu"    , "WZ", kOrange-4 ); //kOrange-4
   
   md.anConf.addSample( "TTZToLLNuNu_ext2","ttZ", kRed+1 );
   //md.anConf.addSample( "TTZToLLNuNu"   , "ttZ", kRed+1 );
   

  // == Pseudo data ======================
  // md.anConf.addSample( "WGToLNuG"      , "pseudodata", kBlack );
  // md.anConf.addSample( "WpWpJJ"        , "pseudodata", kBlack );
  // md.anConf.addSample( "WW2L2NuDouble" , "pseudodata", kBlack );
  // md.anConf.addSample( "WWG"           , "pseudodata", kBlack );
  // md.anConf.addSample( "WWTo2L2Nu"     , "pseudodata", kBlack );
  // md.anConf.addSample( "WWW"           , "pseudodata", kBlack );
  // md.anConf.addSample( "WZG"           , "pseudodata", kBlack );
  // md.anConf.addSample( "WZZ"           , "pseudodata", kBlack );
  // md.anConf.addSample( "ZGTo2LG"       , "pseudodata", kBlack );
  // md.anConf.addSample( "ZZTo2L2Nu"     , "pseudodata", kBlack );
  // md.anConf.addSample( "ZZTo4L"        , "pseudodata", kBlack );
  // md.anConf.addSample( "ZZZ"           , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:DYJetsToLL_M10to50"               , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:DYJetsToLL_M50"                   , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TBar_tch_powheg"                  , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TGJets"                           , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:T_tch_powheg"                     , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTGJets"                          , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTJets_DiLepton"                  , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTJets_DiLepton_ext"              , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromTbar_ext"  , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromT_ext"     , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTJets_SingleLeptonFromT"         , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTZToQQ"                          , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WJetsToLNu"                       , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WZTo2L2Q"                         , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTWToQQ"                          , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WGToLNuG"                         , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WpWpJJ"                           , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WW2L2NuDouble"                    , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WWG"                              , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WWTo2L2Nu"                        , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WWW"                              , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WZG"                              , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WZZ"                              , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:ZGTo2LG"                          , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:ZZTo2L2Nu"                        , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:ZZTo4L"                           , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:ZZZ"                              , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTTT"                             , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTLLJets_m1to10"                  , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:tZq_ll"                           , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:tZW_ll"                           , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTWToLNu_ext1"                    , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTWToLNu_ext2_part1"              , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTWToLNu_ext2_part2"              , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTHnobb_pow"                      , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:VHToNonbb"                        , "pseudodata", kBlack );
  // //md.anConf.addSample( "Fake:WZTo3LNu_amcatnlo"                , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:WZTo3LNu"                         , "pseudodata", kBlack );
  // //md.anConf.addSample( "Fake:TTZToLLNuNu_ext2"                 , "pseudodata", kBlack );
  // md.anConf.addSample( "Fake:TTZToLLNuNu"                      , "pseudodata", kBlack );
   //md.anConf.addSample( "TTLLJets_m1to10" , "pseudodata", kBlack );
  md.anConf.addSample( "tZq_ll"          , "pseudodata", kBlack );
  md.anConf.addSample( "tZW_ll_ext"          , "pseudodata", kBlack );
  // md.anConf.addSample( "TTTT"            , "pseudodata", kBlack );
  // md.anConf.addSample( "TTWToLNu_ext1"       , "pseudodata", kBlack );
  // md.anConf.addSample( "TTWToLNu_ext2_part1" , "pseudodata", kBlack );
  // md.anConf.addSample( "TTWToLNu_ext2_part2" , "pseudodata", kBlack );
  md.anConf.addSample( "TTHnobb_pow" , "pseudodata", kBlack );
  //md.anConf.addSample( "VHToNonbb"   , "pseudodata", kBlack );
  md.anConf.addSample( "WZTo3LNu_amcatnlo" , "pseudodata", kBlack );
  // // md.anConf.addSample( "WZTo3LNu"    , "pseudodata", kBlack ); //kOrange-4
  md.anConf.addSample( "TTZToLLNuNu_ext2","pseudodata", kBlack );
  //md.anConf.addSample( "TTZToLLNuNu"   , "pseudodata", kBlack );
  



  //Nuisance parameters ========================================================
  string obscard="TiamattZCateg"; //TiamattZCategV2
  string cardname=obscard;//"JetCateg";
  
  //  md.addNuisanceParameter("jes","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
   if(obscard!="JetCateg") {
     md.addNuisanceParameter("LF","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
     md.addNuisanceParameter("HF","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
     md.addNuisanceParameter("CSVHFStats1","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
     md.addNuisanceParameter("CSVHFStats2","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
     md.addNuisanceParameter("CSVLFStats1","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
     md.addNuisanceParameter("CSVLFStats2","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
     md.addNuisanceParameter("CSVCFErr1","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
     md.addNuisanceParameter("CSVCFErr2","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
   } else {
     md.addNuisanceParameter("btagJ","EWK:t4:fake:ttX:ttW:higgs:WZ:ttZ","shape","");
   }
     
  //  md.addNuisanceParameter("ttWXs"   ,"ttW"   ,"lnN","1.30");
  // md.addNuisanceParameter("WZXs"    ,"WZ"    ,"lnN","1.15");
  // md.addNuisanceParameter("higXs"   ,"higgs" ,"lnN","1.50");
  // md.addNuisanceParameter("EWKXs"   ,"EWK"   ,"lnN","1.50");
  // md.addNuisanceParameter("t4Xs"    ,"t4"    ,"lnN","1.50");
  // md.addNuisanceParameter("fakeLvl" ,"fake"  ,"lnN","1.30");
  // md.addNuisanceParameter("ttXXs"   ,"ttX"   ,"lnN","1.50");

  // md.addNuisanceParameter("ttZstat" ,"ttZ"   ,"shape","");
  // md.addNuisanceParameter("ttWstat" ,"ttW"   ,"shape","");
  // md.addNuisanceParameter("WZstat"  ,"WZ"    ,"shape","");
  // md.addNuisanceParameter("higstat" ,"higgs" ,"shape","");
  // md.addNuisanceParameter("EWKstat" ,"EWK"   ,"shape","");
  // md.addNuisanceParameter("t4stat"  ,"t4"    ,"shape","");
  // md.addNuisanceParameter("fakestat","fake"  ,"shape","");
  // md.addNuisanceParameter("ttXstat" ,"ttX"   ,"shape","");

  // md.addNuisanceParameter("ttZstat" ,"ttZ"   ,"shape","");
  // md.addNuisanceParameter("ttXstat" ,"ttX"   ,"shape","");
  // md.addNuisanceParameter("tZWstat" ,"tZW"   ,"shape","");
  // md.addNuisanceParameter("higgsstat" ,"higgs" ,"shape","");
  // md.addNuisanceParameter("WZstat" ,"WZ"     ,"shape","");

  // md.addNuisanceParameter("WZXs"    ,"WZ"    ,"lnN","1.15");
  // //md.addNuisanceParameter("ttZXs"   ,"ttZ"   ,"lnN","1.20");
  // md.addNuisanceParameter("ttHXs"   ,"higgs"   ,"lnN","1.30");
  // md.addNuisanceParameter("tZWXs"   ,"tZW"   ,"lnN","1.50");
  // md.addNuisanceParameter("tZqXs"   ,"ttX"   ,"lnN","1.50");

  // md.addNuisanceParameter("WZAcc"    ,"WZ"    ,"lnN","1.30");
  // md.addNuisanceParameter("ttZAcc"   ,"ttZ"   ,"lnN","1.30");
  // md.addNuisanceParameter("ttHXs"   ,"ttH"   ,"lnN","1.30");
  // md.addNuisanceParameter("tZWXs"   ,"tZW"   ,"lnN","1.30");
  // md.addNuisanceParameter("tZqXs"   ,"tZq"   ,"lnN","1.30");
  
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
  // md.dp.setNormalization( Norm );
  // md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
  // 			 yDiv, binning, addBinBkg, overFlowBin,
  // 			 underFlowBin, showDMCRatio, showGrid, 
  // 			 stacking, addSystematics, mcStatSyst,
  // 			 largePad, markerSize, lineWidth,summedSignal, 
  // 			 mcOnly,cmsPrel, uncDet, systSources);
  
  md.prepareDisplay();
  md.loadHistograms();

  // for(int i=0;i<20;i++) {
  //   for(int j=0;j<20;j++) {
  //     ostringstream os; os<<i/2.;
  //     ostringstream os2; os2<<j/2.;
  //     string name="NNBin"+os.str()+os2.str();
  //     md.makeMultiDataCard("ttZ",vector<string>(0,""),name,name);
  //   }
  // }
  //md.makeMultiDataCard("ttZ",vector<string>(0,""),"JetCateg","JetCateg");
  //md.makeMultiDataCard("ttZ",vector<string>(0,""),"TiamattZCategV2noC","TiamattZCategV2");
  md.makeMultiDataCard("ttZ", vector<string>(0,""), obscard, cardname);
  //md.makeMultiDataCard("ttZ", vector<string>(0,""), "JetCateg", "ttVJet");

  // vector<string> cs({
  //     "JetCateg",
  // 	"TiamattZCateg",
  // 	"TiamattZCategV2noC" ,
  // 	"TiamattZCategV2C1"  ,
  // 	"TiamattZCategV2C2"  ,
  // 	"TiamattZCategV2C3"  ,
  // 	"TiamattZCategV2C4"  ,
  // 	"TiamattZCategV2C23" ,
  // 	"TiamattZCategV2C234",
  // 	"TiamattZCategV2C1Mod",
  // 	"TiamattZCategV2C12",
  // 	"TiamattZCategV2C13",
  // 	"TiamattZCategV2C14",
  // 	"TiamattZCategV2C24",
  // 	"TiamattZCategV2C123",
  // 	"TiamattZCategV2C124",
  // 	"TiamattZCategV2C134"
  // 	});
  // for(unsigned int i=0;i<cs.size();i++) {
  //   md.makeMultiDataCard("ttZ", vector<string>(0,""),cs[i],cs[i]);
  // }
  
  // md.doPlot();
  // //md.drawDetailSyst(1);
  // //md.drawDetailSyst(0);
  // //md.dp.addText(xt,yt,st,addText);
  // md.savePlot("TTVAnalysis");
  //gROOT->ProcessLine(".q");
}
