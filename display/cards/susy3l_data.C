MPAFDisplay md;

void susy3l_data() {
    md.refresh();



    //general parameters ********************* general parameters
    string dir="SUSY3L";
    string fileName="limits_160119_2"; //was treeName in LUNE susy_cut_lowpt
    string fileList="limits_160119_2"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
    string hName="";

    bool mcOnly = false;
  
    //if(md.isInitStatus()) {
    md.anConf.configureNames( dir, fileName, fileList );//, hName );
    md.anConf.configureData(false, 0, mcOnly);
    //}
 
    string obs = "VARIABLE" ;    //njets, nbjets, met, ht, pt1, pt2, pt3, srs
    //string obs = "njets" ;    //njets, nbjets, met, ht, pt1, pt2, pt3, srs
    string sigs = "none"; 
    bool data = true;

    //Binning & title ************************* Binning & titre
    string yTitle="number of events";
    //int binning=1;
    int addBinBkg=1; //BinB = binning*AddBin
    double rangeY[2]={0,0};
    bool logYScale=true;
    //double rangeX[2]={0,7};
    int xDiv[3]={8,6,0};
    int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
    bool logYScale=true;
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
        md.dp.setObservables("NJets");
        int binning=1;
        double rangeX[2]={2,9};
        //bool logYScale=true;
    }
    if(obs == "nbjets"){
        md.dp.setObservables("NBJets");
        int binning=1;
        double rangeX[2]={0,4};
        //bool logYScale=true;
    }
    if(obs == "met"){
        md.dp.setObservables("MET");
        int binning=50;
        double rangeX[2]={0,500};
        //bool logYScale=true;
    }
    if(obs == "ht"){
        md.dp.setObservables("HT");
        int binning=60;
        double rangeX[2]={0,1000};
        //bool logYScale=true;
    }
    if(obs == "pt1"){
        md.dp.setObservables("pt_1st_lepton");
        int binning=10;
        double rangeX[2]={0,200};
        //bool logYScale=true;
    }
    if(obs == "pt2"){
        md.dp.setObservables("pt_2nd_lepton");
        int binning=10;
        double rangeX[2]={0,150};
        //bool logYScale=true;
    }   
    if(obs == "pt3"){
        md.dp.setObservables("pt_3rd_lepton");
        int binning=10;
        double rangeX[2]={0,100};
        //bool logYScale=true;
    }
    if(obs == "ftype"){
        md.dp.setObservables("fake_type");
        int binning=1;
        double rangeX[2]={0,5};
        //bool logYScale=true;
    }
    if(obs == "srs"){
        md.dp.setObservables("SRS");
        int binning=1;
        double rangeX[2]={0,16};
        bool logYScale=false;
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
    float lumi=1285.2; //pb-1 19470
    float energy=13; //TeV

    bool useXS=false;

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
 
    //rare
    md.anConf.addSample( "GGHZZ4L"                              ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "VHToNonbb"                            ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "ZZTo4L"                               ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "WWZ"                                  ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "WZZ"                                  ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "ZZZ"                                  ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "TTTT"                                 ,  "rare"        , kMagenta-7    );
    md.anConf.addSample( "tZq_ll"                               ,  "rare"        , kMagenta-7    );

    //WZ
    md.anConf.addSample( "WZTo3LNu"                             ,  "WZ"          , kOrange       );

    //X+gamma
    md.anConf.addSample( "TGJets"                               ,  "X+#gamma"    , kViolet+2     );
    md.anConf.addSample( "TTGJets"                              ,  "X+#gamma"    , kViolet+2     );
    md.anConf.addSample( "WGToLNuG"                             ,  "X+#gamma"    , kViolet+2     );
    md.anConf.addSample( "ZGTo2LG"                              ,  "X+#gamma"    , kViolet+2     );

    //TTZ/H
    md.anConf.addSample( "TTZToLLNuNu"                          ,  "t#bar{t}Z/H" , kGreen-6      );
    md.anConf.addSample( "TTHnobb"                              ,  "t#bar{t}Z/H" , kGreen-6      );
    md.anConf.addSample( "TTLLJets_m1to10"                      ,  "t#bar{t}Z/H" , kGreen-6      );
    
    //TTW
    md.anConf.addSample( "TTWToLNu"                             ,  "t#bar{t}W"   , kGreen+3      );
 
    //fakes
    //md.anConf.addSample( "TT_pow"                               ,  "fakes"       , 18            );
    //md.anConf.addSample( "DYJetsToLL_M10to50"                   ,  "fakes"       , 18            );
    //md.anConf.addSample( "DYJetsToLL_M50"                       ,  "fakes"       , 18            );
    //md.anConf.addSample( "Fake:TT_pow"                             ,  "fakes"    , 18      );
    //md.anConf.addSample( "TbarToLeptons_tch"                    ,  "fakes"       , 18      );
    //md.anConf.addSample( "TBar_tWch"                            ,  "fakes"       , 18      );
    //md.anConf.addSample( "T_tWch"                               ,  "fakes"       , 18      );
    //md.anConf.addSample( "TToLeptons_sch_amcatnlo"              ,  "fakes"       , 18      );
    //md.anConf.addSample( "TToLeptons_tch"                       ,  "fakes"       , 18      );
//    md.anConf.addSample( "TTJets"                           ,  "fakes"       , 18      );
    //md.anConf.addSample( "WJetsToLNu"                           ,  "fakes"       , 18      );

    //fakes predicted
    md.anConf.addSample( "data:Fake:DoubleEG_Run2015C_Oct05_runs_254231_254914"           , "fakes"          , 18    );
    md.anConf.addSample( "data:Fake:DoubleEG_Run2015D_Oct05_runs_256630_258158"           , "fakes"          , 18    );
    md.anConf.addSample( "data:Fake:DoubleEG_Run2015D_PromptV4_runs_258159_260627"        , "fakes"          , 18    );
    md.anConf.addSample( "data:Fake:DoubleMuon_Run2015C_Oct05_runs_254231_254914"         , "fakes"          , 18    );
    md.anConf.addSample( "data:Fake:DoubleMuon_Run2015D_Oct05_runs_256630_258158"         , "fakes"          , 18    );
    md.anConf.addSample( "data:Fake:DoubleMuon_Run2015D_PromptV4_runs_258159_260627"      , "fakes"          , 18    );
    md.anConf.addSample( "data:Fake:MuonEG_Run2015C_Oct05_runs_254231_254914"             , "fakes"          , 18    );
    md.anConf.addSample( "data:Fake:MuonEG_Run2015D_Oct05_runs_256630_258158"             , "fakes"          , 18    );
    md.anConf.addSample( "data:Fake:MuonEG_Run2015D_PromptV4_runs_258159_260627"          , "fakes"          , 18    );

    //signal
    if(sigs=="t"){
    md.anConf.addSample( "T1tttt_mGo1200_mChi800"                       ,  "T1tttt (1200) x10 sig"     , kBlue-3 );
    md.anConf.addSample( "T1tttt_mGo1500_mChi100"                       ,  "T1tttt (1500) x10 sig"     , kBlue-3  );
    md.anConf.addSample( "T6ttWW_mSbot600_mCh425_mChi50"                ,  "T6ttWW (600) x10 sig"     , kMagenta+2 );
    md.anConf.addSample( "T6ttWW_mSbot650_mCh150_mChi50"                ,  "T6ttWW (650) x10 sig"     , kMagenta+2 );
    //md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280"    ,  "T5t410 sig"     , kOrange+10  );
    }
    
    if(sigs=="q"){
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4WZ315 sig"  , kGreen+2  );
    md.anConf.addSample( "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4WZ325 sig"  , kMagenta  );
    md.anConf.addSample( "T5qqqqWZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4WZ12 sig"   , kRed-6  );
    md.anConf.addSample( "T5qqqqWZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4WZ15 sig"   , kRed+3  );
    //md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh315_mChi300_dilep"     ,  "T5q4ZZ315 sig"  , kGreen+3  );
    //md.anConf.addSample( "T5qqqqZZDeg_mGo1000_mCh325_mChi300_dilep"     ,  "T5q4ZZ325 sig"  , kMagenta+2  );
    //md.anConf.addSample( "T5qqqqZZ_mGo1200_mCh1000_mChi800_dilep"       ,  "T5q4ZZ12 sig"   , kRed-9  );
    //md.anConf.addSample( "T5qqqqZZ_mGo1500_mCh800_mChi100_dilep"        ,  "T5q4ZZ15 sig"   , kRed+1  );
    }
    
    //data
    if(data){
    md.anConf.addSample( "DoubleEG_Run2015C_Oct05_runs_254231_254914"           , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015D_Oct05_runs_256630_258158"           , "data"          , kBlack    );
    md.anConf.addSample( "DoubleEG_Run2015D_PromptV4_runs_258159_260627"        , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015C_Oct05_runs_254231_254914"         , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_Oct05_runs_256630_258158"         , "data"          , kBlack    );
    md.anConf.addSample( "DoubleMuon_Run2015D_PromptV4_runs_258159_260627"      , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015C_Oct05_runs_254231_254914"             , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_Oct05_runs_256630_258158"             , "data"          , kBlack    );
    md.anConf.addSample( "MuonEG_Run2015D_PromptV4_runs_258159_260627"          , "data"          , kBlack    );
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
    gROOT->ProcessLine(".q");
 
}
