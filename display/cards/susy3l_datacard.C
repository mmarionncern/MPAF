MPAFDisplay md;

void susy3l_datacard() {
  md.refresh();


  //general parameters ********************* general parameters
  string dir="SUSY3L";
  string fileName="test"; // not needed for statistics but provides the normalization
  string fileList="test"; // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=2200; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsSpring15.db");

  map<string,float> LumisXS;
    
  md.anConf.loadKFDB("kFactorsSpring15.db");

  //via XSect
  map<string,float> KFactors;

  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================

  md.addDataCardSigSample("T1tttt_mGo1200_mChi800","T1t4_1200");
  //md.addDataCardSigSample("T1tttt_mGo1500_mChi100","T1t4_1200");
  //md.addDataCardSigSample("T5ttttDeg_mGo1000_mStop300_mCh285_mChi280","T1t4_1200");
  //md.addDataCardSigSample("T6ttWW_mSbot600_mCh425_mChi50","T1t4_1200");
  //md.addDataCardSigSample("T6ttWW_mSbot650_mCh150_mChi50","T1t4_1200");
  
  md.addDataCardSample("TTWToLNu", "ttW");
  md.addDataCardSample("TTZToLLNuNu","ttZ");
  md.addDataCardSample("WZTo3LNu","WZ");
  md.addDataCardSample("ZZTo4L", "ZZ");
  md.addDataCardSample("WWZ", "VVV");
  md.addDataCardSample("WZZ","VVV");
  md.addDataCardSample("ZZZ", "VVV");
  md.addDataCardSample("GGHZZ4L", "rare");
  md.addDataCardSample("TTHnobb", "rare");
  md.addDataCardSample("VHToNonbb", "rare");
  md.addDataCardSample("WGToLNuG", "rare");
  md.addDataCardSample("WpWpJJ", "rare");
  md.addDataCardSample("WWDouble", "rare");
  md.addDataCardSample("ZGTo2LG", "rare");
  md.addDataCardSample("TT_pow", "fake");
  md.addDataCardSample("TTLLJets_m1to10", "fake");
  md.addDataCardSample("TTGJets", "fake");
  md.addDataCardSample("TGJets", "fake");
  md.addDataCardSample("TTTT", "fake");
  md.addDataCardSample("tZq_ll", "fake");
  
  //md.addDataCardSample("data","data");
  
  
  //shape uncertainties
  md.addNuisanceParameter("JES","ttW:ttZ:WZ:ZZ:VVV:rares:T1t4_1200","shape","");
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
  string cats[15]={
    "SR001","SR002", "SR003", "SR004", "SR005", "SR006", "SR007", "SR008", "SR009", "SR010", "SR011", "SR012", "SR013", "SR014", "SR015"};

  //vector<string> dss; 
  string dss[8]={"ttW","ttZ","WZ","ZZ","VVV","rare","fake","T1t4_1200"};
  

  
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
  md.addNuisanceParameter("sigUnc","T1t4_1200","lnN","1.10");
  md.addNuisanceParameter("promptUnc","ttW:ttZ:WZ:ZZ:VVV:rare","lnN","1.20:1.20:1.20:1.20:1.20:1.20");
  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
  
  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
   
  md.prepareDisplay();
  
  int ncategs=15;
  // vector<string> categs(
  string categs[15]={"global_SR001","global_SR002","global_SR003","global_SR004",
  "global_SR005","global_SR006","global_SR007","global_SR008","global_SR009",
  "global_SR010","global_SR011","global_SR012","global_SR013","global_SR014","global_SR015"
  };
  vector<string> vcategs;
  for(int i=0;i<15;i++) {
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
  
  for(size_t ic=0;ic<15;ic++) {
    for(size_t id=0;id<8;id++) {
        md.addExternalSystUnc(dss[id],"JES",0.05,-0.05,vcategs[ic],"selected");
    }
  }
  
  md.makeMultiDataCard("T1t4_1200", vcategs, "selected", "T1t4_1200");

 
  md.getStatistics();
  gROOT->ProcessLine(".q");

}
