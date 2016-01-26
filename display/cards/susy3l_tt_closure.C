MPAFDisplay md;

void susy3l_tt_closure() {
    md.refresh();



    //general parameters ********************* general parameters
    string dir="SUSY3L";
    string fileName="ttbar_closure_MuEl_qcd_Powheg_newPU"; //was treeName in LUNE susy_cut_lowpt
    string fileList="ttbar_closure_MuEl_qcd_Powheg_newPU"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
    string hName="";

    bool mcOnly = false;
  
    //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList );//, hName );
    md.anConf.configureData(false, 0, mcOnly);
    //}
 
   
    string sigs = "none"; 
    bool data = false;
    bool manual = false;
    string region = "OffZBaseline";

    if(!manual){string obs = "VARIABLE" ;}    //njets, nbjets, met, ht, lep, zpeak, zpt, mt, pt1, pt2, pt3, mll
    else{string obs = "njets";}
 
    //Binning & title ************************* Binning & titre
    string yTitle="number of events";
    //int binning=1;
    int addBinBkg=1; //BinB = binning*AddBin
    double rangeY[2]={0,0};
    bool logYScale=true;
    //double rangeX[2]={0,7};
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

    if(obs == "njets"){
        md.dp.setObservables("NJets" + region);
        int binning=1;
        double rangeX[2]={2,10};
        //bool logYScale=true;
    }
    if(obs == "nbjets"){
        md.dp.setObservables("NBJets" + region);
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "met"){
        md.dp.setObservables("MET" + region);
        int binning=50;
        double rangeX[2]={0,500};
        //bool logYScale=true;
    }
    if(obs == "ht"){
        md.dp.setObservables("HT" + region);
        int binning=60;
        double rangeX[2]={0,1000};
        //bool logYScale=true;
    }
    if(obs == "pt1"){
        md.dp.setObservables("pt_1st_lepton" + region);
        int binning=10;
        double rangeX[2]={0,200};
        //bool logYScale=true;
    }
    if(obs == "pt2"){
        md.dp.setObservables("pt_2nd_lepton" + region);
        int binning=10;
        double rangeX[2]={0,150};
        //bool logYScale=true;
    }   
    if(obs == "pt3"){
        md.dp.setObservables("pt_3rd_lepton" + region);
        int binning=10;
        double rangeX[2]={0,100};
        //bool logYScale=true;
    }
    if(obs == "ftype"){
        md.dp.setObservables("fake_type" + region);
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "flavor"){
        md.dp.setObservables("flavor" + region);
        int binning=1;
        double rangeX[2]={0,4};
        //bool logYScale=true;
    }
    if(obs == "srs"){
        md.dp.setObservables("SRS" + region);
        int binning=1;
        double rangeX[2]={1,16};
        //bool logYScale=true;
    }
    if(obs == "mu_multi"){
        md.dp.setObservables("mu_multiplicity" + region);
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }
    if(obs == "el_multi"){
        md.dp.setObservables("el_multiplicity" + region);
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }
    if(obs == "lep_multi"){
        md.dp.setObservables("lep_multiplicity" + region);
        int binning=1;
        double rangeX[2]={0,6};
        //bool logYScale=true;
    }





    //string autoBinFile="susybinninghigh";
    //md.dp.loadAutoBinning(autoBinFile);

    //Systematic uncertainties ********************************
    bool addSystematics=true;
  
    bool mcStatSyst=true;
    string systSources="";

    bool uncDet=false;

    string Norm="";
  
    //Lumis( or XSections ) pb-1 & KFactors ************************************
    float lumi=3000; //pb-1 19470
    float energy=13; //TeV

    bool useXS=true;

    md.anConf.loadXSDB("XSectionsSpring15.db");
    
    map<string,float> LumisXS;
    
    md.anConf.loadKFDB("kFactorsSpring15.db");
    
    //via XSect
  
    map<string,float> KFactors;
    // if( md.isInitStatus() )
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

    
    
    
    //===============================================================
    // SDYJetsM50_HT600toInf_PU_S14_POSTLS170_skimamples **************************  samples
    //if( md.isInitStatus() ) {
 
    //TTV
//    md.anConf.addSample( "TTWToLNu"                             ,  "ttW"          , kYellow   );
//    md.anConf.addSample( "TTZToLLNuNu"                          ,  "ttZ"          , kBlue     );
 
    //di-boson
//    md.anConf.addSample( "WZTo3LNu"                             ,  "WZ"              , kGreen    );
//    md.anConf.addSample( "ZZTo4L"                               ,  "ZZ"              , kGreen+3  );
 
    //VVV   
//    md.anConf.addSample( "WWZ"                                  ,  "VVV"             , kGreen+4   );
//    md.anConf.addSample( "WZZ"                                  ,  "VVV"             , kGreen+4   );
//    md.anConf.addSample( "ZZZ"                                  ,  "VVV"             , kGreen+4   );

    //rare
//    md.anConf.addSample( "GGHZZ4L"                              ,  "rare SM"             , kCyan     );
//    md.anConf.addSample( "TTHnobb"                              ,  "rare SM"             , kCyan      );
//    md.anConf.addSample( "VHToNonbb"                            ,  "rare SM"             , kCyan      );

//    md.anConf.addSample( "WGToLNuG"                             ,  "rare SM"             , kCyan      );
//    md.anConf.addSample( "WpWpJJ"                               ,  "rare SM"             , kCyan      );
//    md.anConf.addSample( "WWDouble"                             ,  "rare SM"             , kCyan      );
//    md.anConf.addSample( "WWTo2L2Nu"                            ,  "rare SM"             , kCyan      );
    //md.anConf.addSample( "ZGTo2LG"                              ,  "rare SM"             , kCyan      );

    //top production
//    md.anConf.addSample( "TbarToLeptons_tch"                ,  "single t"    , kRed+3      );
//    md.anConf.addSample( "TBar_tWch"                        ,  "single t"    , kRed+3      );
//    md.anConf.addSample( "T_tWch"                           ,  "single t"    , kRed+3      );
 //   md.anConf.addSample( "TToLeptons_sch_amcatnlo"          ,  "single t"    , kRed+3      );
//    md.anConf.addSample( "TToLeptons_tch"                   ,  "single t"    , kRed+3      );
//    md.anConf.addSample( "TGJets"                           ,  "single t"    , kRed+3      );
    //md.anConf.addSample( "tZqll"                            ,  "single t"    , kRed+3      );
//    md.anConf.addSample( "TTJets"                           ,  "TT"    , kRed+2      );
//    md.anConf.addSample( "TTGJets"                          ,  "TT"    , kRed+2      );
//    md.anConf.addSample( "TTLLJets_m1to10"                  ,  "TT"    , kRed+2      );
//    md.anConf.addSample( "TTTT"                             ,  "TT"    , kRed+2      );
    md.anConf.addSample( "TT_pow"                             ,  "TT"    , kRed-6      );
    md.anConf.addSample( "_Fake:TT_pow"                        ,  "predicted sig"    , kBlack      );
//    md.anConf.addSample( "TTJets_DiLepton"                      ,  "TT"    , kRed-6      );
//    md.anConf.addSample( "Fake:TTJets_DiLepton"                 ,  "predicted sig"    , kBlack      );


    //W+Jets
//    md.anConf.addSample( "WJetsToLNu"            ,  "WJets"    , kRed-6      );

    //Drell-Yan
//    md.anConf.addSample( "DYJetsToLL_M10to50"          ,  "DY"    , kRed     );
//    md.anConf.addSample( "DYJetsToLL_M50"              ,  "DY"    , kRed     );


    //signal
    //if(sigs=="t"){
    //md.anConf.addSample( "T1tttt_mGo1200_mChi800"                       ,  "T1t412 sig"     , kBlue-3 );
    //md.anConf.addSample( "T1tttt_mGo1500_mChi100"                       ,  "T1t415 sig"     , kBlue-7  );
    //md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"    ,  "T5t410 sig"     , kOrange+10  );
    //}
    if(sigs=="q"){
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4WZ315 sig"  , kGreen+2  );
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4WZ325 sig"  , kMagenta  );
    md.anConf.addSample( "T5qqqqWZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4WZ12 sig"   , kRed-6  );
    md.anConf.addSample( "T5qqqqWZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4WZ15 sig"   , kRed+3  );
    md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4ZZ315 sig"  , kGreen+3  );
    md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4ZZ325 sig"  , kMagenta+2  );
    md.anConf.addSample( "T5qqqqZZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4ZZ12 sig"   , kRed-9  );
    md.anConf.addSample( "T5qqqqZZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4ZZ15 sig"   , kRed+1  );
    }
    
    //data
    if(data){
    md.anConf.addSample( "DoubleEG_Run2015D_v3_runs_256630_257599"              , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015D_v3_runs_257600_258158"              , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015D_v4_runs_258159_258714_excl"         , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015D_v4_runs_258211_258750"              , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v3_runs_256630_257599"            , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v3_runs_257600_258158"            , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v4_runs_258159_258714_excl"       , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_v4_runs_258211_258750"            , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v3_runs_256630_257599"                , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v3_runs_257600_258158"                , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v4_runs_258159_258714_excl"           , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_v4_runs_258211_258750"                , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v3_runs_256630_257599"        , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v3_runs_257600_258158"        , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v4_runs_258159_258714_excl"   , "data"          , kBlack    );
    md.anConf.addSample( "SingleElectron_Run2015D_v4_runs_258211_258750"        , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v3_runs_256630_257599"            , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v3_runs_257600_258158"            , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v4_runs_258159_258714_excl"       , "data"          , kBlack    );
    md.anConf.addSample( "SingleMuon_Run2015D_v4_runs_258211_258750"            , "data"          , kBlack    );
    }


//    md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280_skim"  ,  "T5tttt (1000) * 20 sig" , kOrange-3 );
  //md.anConf.addSample( "T5ttttDeg_mGo1300_mStop300_mCh285_mChi280_skim"  ,  "T5tttt (1300) #cdot 20 sig" , kOrange+6 );
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
    md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
			 yDiv, binning, addBinBkg, overFlowBin,
			 underFlowBin, showDMCRatio, showGrid, 
			 stacking, addSystematics, mcStatSyst,
			 markerSize, lineWidth,summedSignal,
             mcOnly,cmsPrel, uncDet);
    md.prepareDisplay();
    md.doPlot();
    //md.doStatisticsPlot();
    md.savePlot("SUSY3L");
    // md.dp.addText(xt,yt,st,addText);
    if(!manual) gROOT->ProcessLine(".q");
 
}
