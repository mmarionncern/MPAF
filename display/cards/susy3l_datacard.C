MPAFDisplay md;

void susy3l_datacard() {
  md.refresh();


  //general parameters ********************* general parameters
  string dir="SUSY3L";
  string fileName="limits_160126_OnAndOffZ"; // not needed for statistics but provides the normalization
  string fileList="limits_160126_OnAndOffZ"; // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=2260; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsSpring15.db");

  map<string,float> LumisXS;
    
  md.anConf.loadKFDB("kFactorsSpring15.db");

  //via XSect
  map<string,float> KFactors;

  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================


  string signal = "T1t4_1200"; md.addDataCardSigSample("T1tttt_mGo1200_mChi800",                     signal);
  //string signal = "T1t4_1500"; md.addDataCardSigSample("T1tttt_mGo1500_mChi100",                     signal);
  //string signal = "T54q_deg"; md.addDataCardSigSample("T5ttttDeg_mGo1000_mStop300_mCh285_mChi280",  signal);
  //string signal = "T6t2W2_600"; md.addDataCardSigSample("T6ttWW_mSbot600_mCh425_mChi50",              signal);
  //string signal = "T6t2W2_650"; md.addDataCardSigSample("T6ttWW_mSbot650_mCh150_mChi50",              signal);
  //string signal = "T54qWZ_315"; md.addDataCardSigSample("T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep",   signal);
  //string signal = "T54qWZ_325"; md.addDataCardSigSample("T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep",   signal);
  //string signal = "T54qWZ_800"; md.addDataCardSigSample("T5qqqqWZ_mGo1500_mCh800_mChi100_lep",        signal);
  //string signal = "T54qWZ_1000"; md.addDataCardSigSample("T5qqqqWZ_mGo1200_mCh1000_mChi800_lep",       signal);
  
  md.addDataCardSample("GGHZZ4L", "rare");
  md.addDataCardSample("VHToNonbb", "rare");
  md.addDataCardSample("ZZTo4L", "rare");
  md.addDataCardSample("WWZ", "rare");
  md.addDataCardSample("WZZ","rare");
  md.addDataCardSample("ZZZ", "rare");
  md.addDataCardSample("TTTT", "rare");
  md.addDataCardSample("tZq_ll", "rare");

  md.addDataCardSample("WZTo3LNu","WZ");

  md.addDataCardSample("TGJets", "XG");
  md.addDataCardSample("TTGJets", "XG");
  md.addDataCardSample("WGToLNuG", "XG");
  md.addDataCardSample("ZGTo2LG", "XG");
  
  md.addDataCardSample("TTZToLLNuNu","ttZH");
  md.addDataCardSample("TTHnobb", "ttZH");
  md.addDataCardSample("TTLLJets_m1to10", "ttZH");
  
  md.addDataCardSample("TTWToLNu", "ttW");
  
  md.addDataCardSample("TT_pow", "fake");
  md.addDataCardSample("DYJetsToLL_M50", "fake");
  md.addDataCardSample("DYJetsToLL_M10to50", "fake");
  md.addDataCardSample("TbarToLeptons_tch", "fake");
  md.addDataCardSample("TBar_tWch", "fake");
  md.addDataCardSample("TToLeptons_sch_amcatnlo", "fake");
  md.addDataCardSample("TToLeptons_tch", "fake");
  md.addDataCardSample("T_tWch", "fake");
  md.addDataCardSample("WJetsToLNu", "fake");
 
 
  
  //md.addDataCardSample("data","data");
  
  
  //shape uncertainties
  string nuis = "rare:WZ:XG:ttZH:ttW:fake:";
  nuis += signal;
  
  md.addNuisanceParameter("JES",nuis,"shape","");
  /*md.addNuisanceParameter("BTAG","ttW:ttZH:WZ:WW:XG:rares:T1ttttBENCH","shape","");
  md.addNuisanceParameter("tHTE","ttW:ttZH:WZ:WW:XG:rares:T1ttttBENCH","shape","");

  md.addNuisanceParameter("Ewk","fake","shape","");

  md.addNuisanceParameter("ttWAcc","ttW","shape","");
  md.addNuisanceParameter("ttHZAcc","ttHZ","shape","");

  md.addNuisanceParameter("BTAGFS","T1ttttBENCH","shape","");
  md.addNuisanceParameter("LepEffFS","T1ttttBENCH","shape","");
  md.addNuisanceParameter("ISR","T1ttttBENCH","shape","");

  md.addNuisanceParameter("QCDScale","T1ttttBENCH","shape","");
  */

  //vector<string> cats(
  string cats[30]={
    "OnZSR001","OnZSR002", "OnZSR003", "OnZSR004", "OnZSR005", "OnZSR006", "OnZSR007", "OnZSR008", "OnZSR009", "OnZSR010", "OnZSR011", "OnZSR012", "OnZSR013", "OnZSR014", "OnZSR015", 
    "OffZSR001","OffZSR002", "OffZSR003", "OffZSR004", "OffZSR005", "OffZSR006", "OffZSR007", "OffZSR008", "OffZSR009", "OffZSR010", "OffZSR011", "OffZSR012", "OffZSR013", "OffZSR014", "OffZSR015" };

  //vector<string> dss; 
  string dss[7]={"rare","WZ","XG","ttZH","ttW","fake",signal};
  

  
  //for(int isr=0;isr<66/*cats.size()*/;isr++) {
  //  md.addNuisanceParameter("pdfS"+cats[isr],"T1ttttBENCH","shape","");

    //md.addNuisanceParameter("flip"+cats[isr]+"stat","flip","shape","");
    //md.addNuisanceParameter("fake"+cats[isr]+"stat","fake","shape","");
    //for(size_t id=0;id<7/*dss.size()*/;id++) {
    //  md.addNuisanceParameter(dss[id]+cats[isr]+"stat",dss[id],"shape","");
    //}
  //}  

 /* 
  //Flat uncertanties =================================
  //lumi
  md.addNuisanceParameter("lumi","ttW:ttHZ:WW:XG:rares:T1ttttBENCH","lnN","1.046:1.046:1.046:1.046:1.046:1.046:1.046");
  //md.addNuisanceParameter("lumi","ttW:ttHZ:WW:XG:rares:T1ttttBENCH","lnN","1.12:1.12:1.12:1.12:1.12:1.12:1.12");
  //experimental uncertainties
  md.addNuisanceParameter("lEff","ttW:ttHZ:WW:XG:rares:T1ttttBENCH","lnN","1.04:1.04:1.04:1.04:1.04:1.04");
  md.addNuisanceParameter("tEff","ttW:ttHZ:WW:XG:rares:T1ttttBENCH","lnN","1.02:1.02:1.02:1.02:1.02:1.02");
  //Data-driven methods
  md.addNuisanceParameter("chMID","flip","lnN","1.30");
  md.addNuisanceParameter("fratio","fake","lnN","1.30");
  //theoretical uncertainties
  md.addNuisanceParameter("wzTh","WZ","lnN","1.30");
  md.addNuisanceParameter("WWTh","ttW","lnN","1.50");
  md.addNuisanceParameter("TGTh","XG","lnN","1.50");
  md.addNuisanceParameter("rareTh","rares","lnN","1.50");
  
  md.addNuisanceParameter("ttWPdf","ttW","lnN","1.04");
  md.addNuisanceParameter("ttHZPdf","ttHZ","lnN","1.04");
  md.addNuisanceParameter("ttWXs","ttW","lnN","1.13");
  md.addNuisanceParameter("ttHZXs","ttHZ","lnN","1.11");
  md.addNuisanceParameter("fsHLT","T1ttttBENCH","lnN","1.05");
*/
  md.addNuisanceParameter("fakeUnc","fake","lnN","1.30");
  md.addNuisanceParameter("sigUnc",signal,"lnN","1.10");
  md.addNuisanceParameter("promptUnc","rare:WZ:XG:ttZH:ttW","lnN","1.20:1.20:1.20:1.20:1.20");
  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
  
  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
   
  md.prepareDisplay();
  
  int ncategs=30;
  // vector<string> categs(
  string categs[30]={"global_OnZSR001","global_OnZSR002","global_OnZSR003","global_OnZSR004",
  "global_OnZSR005","global_OnZSR006","global_OnZSR007","global_OnZSR008","global_OnZSR009",
  "global_OnZSR010","global_OnZSR011","global_OnZSR012","global_OnZSR013","global_OnZSR014","global_OnZSR015",
  "global_OffZSR001","global_OffZSR002","global_OffZSR003","global_OffZSR004",
  "global_OffZSR005","global_OffZSR006","global_OffZSR007","global_OffZSR008","global_OffZSR009",
  "global_OffZSR010","global_OffZSR011","global_OffZSR012","global_OffZSR013","global_OffZSR014","global_OffZSR015"
  };
  vector<string> vcategs;
  for(int i=0;i<30;i++) {
    vcategs.push_back( categs[i] );
  }

/*
  //external uncertainties ===================================
  //vector<float> AccTTW
  float AccTTW[66]={
      0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
      0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
      0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
      0.03,0.08,0.03,0.08,0.03,0.08,0.08,0.08,
    
      0.03,0.08,0.03,0.08,0.08,0.08,0.03,0.08,
      0.03,0.08,0.08,0.08,0.03,0.08,0.03,0.08,
      0.08,0.08,0.03,0.08,0.03,0.08,0.03,0.08,
      0.08,0.08,
    
      0.08,0.08,0.08,0.08,0.08,0.08,0.08,0.08,
  };
  
  //vector<float> AccTTHZ
  float AccTTHZ[66]={
    0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
    0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
    0.03,0.08,0.03,0.08,0.08,0.08,0.08,0.08,
    0.03,0.08,0.03,0.08,0.03,0.08,0.08,0.08,
    
    0.03,0.08,0.03,0.08,0.08,0.08,0.03,0.08,
    0.03,0.08,0.08,0.08,0.03,0.08,0.03,0.08,
    0.08,0.08,0.03,0.08,0.03,0.08,0.03,0.08,
    0.08,0.08,

    0.08,0.08,0.08,0.08,0.08,0.08,0.08,0.08,
  };
  
  // vector<float> EWKFake({
  //     0.10,0.06,0.10,0.03,0.09,0.10,0.05,0.10,
  // 	0.09,0.11,0.11,0.09,0.09,0.02,0.10,0.10,
  // 	0.20,0.03,0.10,0.05,0.05,0.10,0.10,0.10,
  // 	0.10,0.10,0.10,0.10,0.10,0.10,0.10,0.10,

  // 	0.03,0.01,0.10,0.02,0.01,0.10,0.02,0.01,
  // 	0.01,0.01,0.01,0.01,0.02,0.01,0.10,0.10,
  // 	0.01,0.10,0.10,0.10,0.10,0.10,0.10,0.10,
  // 	0.10,0.10,

  // 	0.10,0.01,0.10,0.10,0.10,0.10,0.10,0.10,
  // 	});

  //vector<float> HLTEff
  float HLTEff[66]={
    0,0.02,0,0.02,0.02,0.02,0.02,0.02,
    0,0.02,0,0.02,0.02,0.02,0.02,0.02,
    0,0.02,0,0.02,0.02,0.02,0.02,0.02,
    0,0.02,0,0.02,0,0.02,0.02,0.02,
    
    0,0.02,0,0.02,0.02,0.02,0,0.02,
    0,0.02,0.02,0.02,0,0.02,0,0.02,
    0.02,0.02,0,0.02,0,0.02,0,0.02,
    0.02,0.02,

    0.02,0.02,0.02,0.02,0.02,0.02,0.02,0.02
  };

  
  //  int nCateg=66; //47
  //  vector<string> _categs(nCateg,"");
 
  //qcd scale for signal
  TFile* iQCDFile=new TFile("/shome/mmarionn/MPAF/workdir/QCDScales/scaleUncMASS-.root","read");
  TH1F* hQCDUp=(TH1F*)iQCDFile->Get("MASS-ScaleUp");
  TH1F* hQCDDown=(TH1F*)iQCDFile->Get("MASS-ScaleDown");
  */

  //for(size_t ic=0;ic<66/*categs.size()*/;ic++) {
  //   for(int isr=0;isr<66/*cats.size()*/;isr++) {
  //     if(categs[ic].substr(7, categs[ic].size()-7)==cats[isr])
	// md.addExternalSystUnc("T1ttttBENCH","pdfS"+cats[isr],0.1, -0.1, categs[ic], "selected");
     //  else
	 //md.addExternalSystUnc("T1ttttBENCH","pdfS"+cats[isr],0., 0., categs[ic], "selected");
     //}
     //md.addExternalSystUnc("T1ttttBENCH","QCDScale",hQCDUp->GetBinContent(ic+1), hQCDDown->GetBinContent(ic+1), categs[ic], "selected");

    //md.addExternalSystUnc("fake","frEwk",EWKFake[ic], -1*EWKFake[ic], categs[ic], "selected");
    //md.addExternalSystUnc("ttW","ttWAcc",AccTTW[ic], -1*AccTTW[ic], categs[ic], "selected");
    //md.addExternalSystUnc("ttHZ","ttHZAcc",AccTTHZ[ic], -1*AccTTHZ[ic], categs[ic], "selected");
    //for(size_t id=0;id<7/*dss.size()*/;id++) {
     // md.addExternalSystUnc(dss[id],"tHTE",HLTEff[ic], -1*HLTEff[ic], categs[ic], "selected");
    //}
  //}
  
  for(size_t ic=0;ic<30;ic++) {
    for(size_t id=0;id<7;id++) {
        md.addExternalSystUnc(dss[id],"JES",0.05,-0.05,vcategs[ic],"selected");
    }
  }
  
  md.makeMultiDataCard(signal, vcategs, "selected", signal);

 
  md.getStatistics("global");
  gROOT->ProcessLine(".q");

}
