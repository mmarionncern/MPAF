MPAFDisplay md;

void susy3l_scanSigBENCH(){
    md.refresh();

    //general parameters ********************* general parameters
    //string sig="fs_t1ttttBENCH";
    string sig="fs_t1ttttBENCH";
    bool allSR = true;

    string dir="SUSY3L";
    string fileName="merged_4fb";
    if(sig=="fs_t1ttttBENCH") string fileList="merged_v2_4fb_T1tttt_MASS"; //susy3lUnc
    if(sig=="fs_t6ttww_50BENCH") string fileList="merged_2fb_T6ttWWMASS"; //susy3lUnc
    if(sig=="fs_t5qqqqvvBENCH") string fileList="merged_2fb_T5qqqqVVMASS"; //susy3lUnc
    if(sig=="fs_t5tttt_degenBENCH") string fileList="merged_2fb_T5ttttMASS"; //susy3lUnc
  
    bool mcOnly = false;
  
    md.anConf.configureNames( dir, fileName, fileList );
    md.anConf.configureData(false, 0, mcOnly);
     
    //Lumis( or XSections ) pb-1 & KFactors ************************************
    float lumi=4300; //pb-1 19470  
    float energy=13; //TeV

    bool useXS=true;

    md.anConf.loadXSDB("XSectionsSpring16.db");

    map<string,float> LumisXS;

    //via XSect
  
    map<string,float> KFactors;
  
    md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
 
    //===============================================================
  
    float kfac = 0.55555555;

    if(sig=="fs_t1ttttBENCH") md.addDataCardSigSample("T1tttt_MASS",sig);
    if(sig=="fs_t6ttww_50BENCH") md.addDataCardSigSample("T6ttWWMASS",sig);
    if(sig=="fs_t5qqqqvvBENCH") md.addDataCardSigSample("T5qqqqVVMASS",sig, kfac);
    if(sig=="fs_t5tttt_degenBENCH") md.addDataCardSigSample("T5ttttMASS",sig);

    md.addDataCardSample( "TGJets", "xg"); 
    md.addDataCardSample( "TTGJets", "xg"); 
    md.addDataCardSample( "ZGTo2LG", "xg"); 
    md.addDataCardSample( "WGToLNuG", "xg"); 

    md.addDataCardSample( "TTHnobb_pow", "ttzh"); 
    md.addDataCardSample( "TTZ_LO", "ttzh"); 

    md.addDataCardSample( "TTLLJets_m1to10", "ttzlowM"); 

    md.addDataCardSample( "TTW_LO", "ttw"); 
   
    md.addDataCardSample( "WZTo3LNu", "wz"); 
    
    md.addDataCardSample( "GGHZZ4L", "rares"); 
    md.addDataCardSample( "VHToNonbb", "rares"); 
    md.addDataCardSample( "ZZTo4L", "rares"); 
    md.addDataCardSample( "WWW", "rares"); 
    md.addDataCardSample( "WWZ", "rares"); 
    md.addDataCardSample( "WZZ", "rares"); 
    md.addDataCardSample( "ZZZ", "rares"); 
    md.addDataCardSample( "TTTT", "rares"); 
    md.addDataCardSample( "tZq_ll", "rares"); 

    md.addDataCardSample( "data:Fake:DoubleEG_Run2016B_PromptReco_v2_runs_273150_275125", "fakes"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2016B_PromptReco_v2_runs_273150_275125", "fakes"); 
    md.addDataCardSample( "data:Fake:MuonEG_Run2016B_PromptReco_v2_runs_273150_275125", "fakes"); 

    /*
    md.addDataCardSample( "TGJets", "pseudodata"); 
    md.addDataCardSample( "TTGJets", "pseudodata"); 
    md.addDataCardSample( "ZGTo2LG", "pseudodata"); 
    md.addDataCardSample( "WGToLNuG", "pseudodata"); 

    md.addDataCardSample( "TTHnobb_pow", "pseudodata"); 
    md.addDataCardSample( "TTZ_LO", "pseudodata"); 

    md.addDataCardSample( "TTLLJets_m1to10", "pseudodata"); 

    md.addDataCardSample( "TTW_LO", "pseudodata"); 
   
    md.addDataCardSample( "WZTo3LNu", "pseudodata"); 
    
    md.addDataCardSample( "GGHZZ4L", "pseudodata"); 
    md.addDataCardSample( "VHToNonbb", "pseudodata"); 
    md.addDataCardSample( "ZZTo4L", "pseudodata"); 
    md.addDataCardSample( "WWZ", "pseudodata"); 
    md.addDataCardSample( "WZZ", "pseudodata"); 
    md.addDataCardSample( "ZZZ", "pseudodata"); 
    md.addDataCardSample( "TTTT", "pseudodata"); 
    md.addDataCardSample( "tZq_ll", "pseudodata"); 

    md.addDataCardSample( "data:Fake:DoubleEG_Run2016B_PromptReco_v2_runs_273150_27512", "pseudodata"); 
    md.addDataCardSample( "data:Fake:DoubleMuon_Run2016B_PromptReco_v2_runs_273150_275125", "pseudodata"); 
    md.addDataCardSample( "data:Fake:MuonEG_Run2016B_PromptReco_v2_runs_273150_275125", "pseudodata"); 
    */

 
    md.addDataCardSample( "DoubleEG_Run2016B_PromptReco_v2_runs_273150_275125", "data"); 
    md.addDataCardSample( "DoubleMuon_Run2016B_PromptReco_v2_runs_273150_275125", "data"); 
    md.addDataCardSample( "MuonEG_Run2016B_PromptReco_v2_runs_273150_275125", "data"); 




    //===============================================================
    //UNCERTANITIES

    md.addNuisanceParameter("jes"               ,"ttw:ttzh:ttzlowM:wz:xg:rares:"+sig    ,"shape","");
    md.addNuisanceParameter("btag"              ,"ttw:ttzh:ttzlowM:wz:xg:rares:"+sig    ,"shape","");
    md.addNuisanceParameter("pu"                ,"ttw:ttzh:ttzlowM:wz:xg:rares:"+sig    ,"shape","");
    md.addNuisanceParameter("fakes_EWK"         ,"fakes"                                ,"shape","");

    //fastSim related uncertainties
    md.addNuisanceParameter("fs_btag"           ,sig                                    ,"shape","");
    //md.addNuisanceParameter("fs_lep"            ,sig                                    ,"shape","");
	//md.addNuisanceParameter("fs_hlt"            ,sig                                    ,"shape","");
    md.addNuisanceParameter("isr"               ,sig                                    ,"shape","");
	md.addNuisanceParameter("scale"             ,sig                                    ,"shape","");


    //flat uncertanties
    md.addNuisanceParameter("lumi"              ,"ttw:ttzh:ttzlowM:xg:rares:"+sig       ,"shape","");
    md.addNuisanceParameter("HLTEff"            ,"ttw:ttzh:ttzlowM:xg:rares:"+sig       ,"shape","");
    md.addNuisanceParameter("LepEff"            ,"ttw:ttzh:ttzlowM:xg:rares:"+sig       ,"shape","");
    md.addNuisanceParameter("rare"              ,"rares"                                ,"shape","");
    md.addNuisanceParameter("XG"                ,"xg"                                   ,"shape","");
    md.addNuisanceParameter("ra7_WZ"            ,"wz"                                   ,"shape","");
    md.addNuisanceParameter("ttzh_pdf"          ,"ttzh:ttZlowM"                         ,"shape","");
    md.addNuisanceParameter("ttw_pdf"           ,"ttw"                                  ,"shape","");
    md.addNuisanceParameter("TTW"               ,"ttw"                                  ,"shape","");
    md.addNuisanceParameter("TTZH"              ,"ttzh:ttzlowM"                         ,"shape","");
    md.addNuisanceParameter("fakes"             ,"fakes"                                ,"shape","");
    md.addNuisanceParameter("ttzh_extr_htl"     ,"ttzh"                                 ,"shape","");
    md.addNuisanceParameter("ttzh_extr_hth"     ,"ttzh"                                 ,"shape","");
    md.addNuisanceParameter("ttz_lowM_extr_htl" ,"ttzlowM"                              ,"shape","");
    md.addNuisanceParameter("ttz_lowM_extr_hth" ,"ttzlowM"                              ,"shape","");
    md.addNuisanceParameter("ttw_extr_htl"      ,"ttw"                                  ,"shape","");
    md.addNuisanceParameter("ttw_extr_hth"      ,"ttw"                                  ,"shape","");
    md.addNuisanceParameter("wz_extr"           ,"wz"                                   ,"shape","");
    md.addNuisanceParameter("ttzLO"             ,"ttzh"                                 ,"shape","");
    md.addNuisanceParameter("ttwLO"             ,"ttw"                                  ,"shape","");
    

    vector<string> vcategs;
    int nBins = 32;
    string categs[32]={
        "OnZSR001", "OnZSR002", "OnZSR003", "OnZSR004",
        "OnZSR005", "OnZSR006", "OnZSR007", "OnZSR008",
        "OnZSR009", "OnZSR010", "OnZSR011", "OnZSR012",
        "OnZSR013", "OnZSR014", "OnZSR015", "OnZSR016", "OnZSR017",
    
        "OffZSR001", "OffZSR002", "OffZSR003", "OffZSR004", 
        "OffZSR005", "OffZSR006", "OffZSR007", "OffZSR008", 
        "OffZSR009", "OffZSR010", "OffZSR011", "OffZSR012",
        "OffZSR013", "OffZSR014", "OffZSR016"
    };

    if(allSR == true){
        for(int i=0;i<nBins;i++) {
            vcategs.push_back( categs[i] );
        }
    }
    else{
        //section for datacards with one SR only
        nBins = 1;
        int testSR = NUMBER;
        vcategs.push_back( categs[testSR-1] );
        cout << "making datacard for SR " << categs[testSR-1] << endl;
    }
 

    //*********************************************************************²

    //plotting ================
    md.dp.setLumiAndEnergy( lumi, energy );
   
    md.prepareDisplay();
   
   	//datasets
    string dss[8]={sig,"xg","ttzh","ttzlowM","ttw","wz","rares","fakes"};

    //statistical uncertainties for all processes
    for(int isr=0;isr<nBins;isr++) {
        for(size_t id=0;id<8;id++) {
            md.addNuisanceParameter(dss[id]+vcategs[isr]+"stat",dss[id],"shape","");
        }
    }

    for(int i=0;i<nBins;i++){
        vcategs[i] = "global_" + vcategs[i];
    }

    md.makeMultiDataCard(sig, vcategs, "selected", "ra7_"+sig);

    gROOT->ProcessLine(".qqqqqqqqqqqqqq");
}
