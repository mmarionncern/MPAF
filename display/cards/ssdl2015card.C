MPAFDisplay md;

void ssdl2015card() {
  md.refresh();


  //general parameters ********************* general parameters
  string dir="SSDL2015";
  string fileName="fakeEstim_SR"; // not needed for statistics but provides the normalization
  string fileList="fakeEstim_SR"; // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=10000; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsPhys14.db");

  map<string,float> LumisXS;

  //via XSect
  map<string,float> KFactors;
  

  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================

  // md.addDataCardBkgSample("TTJets", "fake");

  // md.addDataCardBkgSample("WJetsToLNu_HT100to200", "fake");
  // md.addDataCardBkgSample("WJetsToLNu_HT200to400", "fake");
  // md.addDataCardBkgSample("WJetsToLNu_HT400to600", "fake");
  // md.addDataCardBkgSample("WJetsToLNu_HT600toInf", "fake");

  // md.addDataCardBkgSample("DYJetsToLL_M50_HT100to200", "fake");
  // md.addDataCardBkgSample("DYJetsToLL_M50_HT200to400", "fake");
  // md.addDataCardBkgSample("DYJetsToLL_M50_HT400to600", "fake");
  // md.addDataCardBkgSample("DYJetsToLL_M50_HT600toInf", "fake");

  md.addDataCardSigSample("SR1A:SMS_T1tttt_2J_mGl1200_mLSP800","T1t412");
  
  md.addDataCardSample("SR1A:WZJetsTo3LNu", "wz");
  md.addDataCardSample("SR1A:TTH", "tth");
  md.addDataCardSample("SR1A:TTZJets", "ttz");
  md.addDataCardSample("SR1A:TTWJets", "ttw");
  
  md.addDataCardSample("SR1A:TTJetscharge", "chMId");
  md.addDataCardSample("SR1A:DYJetsToLL_M50_HT100to200charge", "chMId");
  md.addDataCardSample("SR1A:DYJetsToLL_M50_HT200to400charge", "chMId");
  md.addDataCardSample("SR1A:DYJetsToLL_M50_HT400to600charge", "chMId");
  md.addDataCardSample("SR1A:DYJetsToLL_M50_HT600toInfcharge", "chMId");

  md.addDataCardSample("SR1A_Fake:TTJets", "fake");
  md.addDataCardSample("SR1A_Fake:WJetsToLNu_HT100to200", "fake");
  md.addDataCardSample("SR1A_Fake:WJetsToLNu_HT200to400", "fake");
  md.addDataCardSample("SR1A_Fake:WJetsToLNu_HT400to600", "fake");
  md.addDataCardSample("SR1A_Fake:WJetsToLNu_HT600toInf", "fake");
  md.addDataCardSample("SR1A_Fake:DYJetsToLL_M50_HT100to200", "fake");
  md.addDataCardSample("SR1A_Fake:DYJetsToLL_M50_HT200to400", "fake");
  md.addDataCardSample("SR1A_Fake:DYJetsToLL_M50_HT400to600", "fake");
  md.addDataCardSample("SR1A_Fake:DYJetsToLL_M50_HT600toInf", "fake");

  
  md.addDataCardSample("SR1A:WZJetsTo3LNu", "pseudodata");
  md.addDataCardSample("SR1A:TTH", "pseudodata");
  md.addDataCardSample("SR1A:TTZJets", "pseudodata");
  md.addDataCardSample("SR1A:TTWJets", "pseudodata");

   
  
  md.addNuisanceParameter("wzstat","wz","lnN","");
  md.addNuisanceParameter("tthstat","tth","lnN","");
  md.addNuisanceParameter("ttwstat","ttw","lnN","");
  md.addNuisanceParameter("ttzstat","ttz","lnN","");
  md.addNuisanceParameter("fakestat","fake","lnN","");
  md.addNuisanceParameter("chMIdstat","chMId","lnN","");
  md.addNuisanceParameter("T1t412stat","T1t412","lnN","");

  md.addNuisanceParameter("jes","wz:tth","lnN","1.1:1.2");

  // }
  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
  
  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
   
  md.prepareDisplay();
  
  //md.makeSingleDataCard("T1t412", "nominal", "selected", "test"); //global_SR1A
 

  // gROOT->ProcessLine(".q");

}
