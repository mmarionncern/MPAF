MPAFDisplay md;

void dataCardProd_CATTAG_SIGTAG() {
  md.refresh();


  //general parameters ********************* general parameters
  string dir="SSDL2015";
  string fileName="ssdl2fb_oct"; // not needed for statistics but provides the normalization
  string fileList="ssdl2fb_oct"; // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=1; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  //md.anConf.loadXSDB("XSectionsSpring15.db");

  map<string,float> LumisXS;

  //via XSect
  map<string,float> KFactors;
  

  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================

  md.addDataCardSigSample("CATTAG:SIGNAME","SIGTAG");
  
  md.addDataCardSample("CATTAG:_standard_prompt_WZ", "WZ");
  md.addDataCardSample("CATTAG:_standard_prompt_ttW","ttW");
  md.addDataCardSample("CATTAG:_standard_prompt_ttZH","ttHZ");
  md.addDataCardSample("CATTAG:_standard_prompt_WW", "WW");
  md.addDataCardSample("CATTAG:_standard_prompt_TG", "XG");
  md.addDataCardSample("CATTAG:_standard_prompt_VG", "XG");
  md.addDataCardSample("CATTAG:_standard_prompt_Rares","rares");
  md.addDataCardSample("CATTAG:_flipsappl_data", "flip");
  md.addDataCardSample("CATTAG:_fakesappl_data", "fake");

  md.addDataCardSample("CATTAG:_standard_prompt_ttZH","pseudodata");
  
  
  //lumi
  md.addNuisanceParameter("lumi","WZ:ttW:ttHZ:WW:XG:rares","lnN","1.08:1.08:1.08:1.08:1.08:1.08");

  //experimental uncertainties
  md.addNuisanceParameter("jes","ttW:ttZH:WW:XG:rares:SIGTAG","lnN","JESTAG");
  md.addNuisanceParameter("btag","ttW:ttZH:WW:XG:rares:SIGTAG","lnN","BTAGTAG");
  md.addNuisanceParameter("lEff","ttW:ttZH:WW:XG:rares","lnN","1.04:1.04:1.04:1.04:1.04");
  md.addNuisanceParameter("tEff","ttW:ttZH:WW:XG:rares","lnN","1.02:1.02:1.02:1.02:1.02");
  md.addNuisanceParameter("tHTE","ttW:ttZH:WW:XG:rares","lnN","HLTEFFTAG");
  
  
  //Data-driven methods
  md.addNuisanceParameter("chMID","flip","lnN","1.30");
  md.addNuisanceParameter("fratio","fake","lnN","1.30");
  md.addNuisanceParameter("frEwk","fake","lnN","FREWKTAG");

  //theoretical uncertainties
  md.addNuisanceParameter("wzTh","WZ","lnN","1.30");
  md.addNuisanceparameter("WWTh","ttW","lnN","1.50");
  md.addNuisanceparameter("TGTh","XG","lnN","1.50");
  md.addNuisanceparameter("rareTh","rare","lnN","1.50");
  //md.addNuisanceParameter("sigTh","SIGTAG","lnN","SIGTHTAG");

  md.addNuisanceparameter("ttWPdf","ttW","lnN","1.04");
  md.addNuisanceparameter("ttHZPdf","ttHZ","lnN","1.04");
  md.addNuisanceparameter("ttWXs","ttW","lnN","1.13");
  md.addNuisanceparameter("ttHZXs","ttHZ","lnN","1.11");
  md.addNuisanceparameter("ttWAcc","ttW","lnN","TTWACCTAG");
  md.addNuisanceparameter("ttHZAcc","ttHZ","lnN","TTHZACCTAG");


  string srs[66]={ 
    "HHSR1", "HHSR2", "HHSR3", "HHSR4", "HHSR5", "HHSR6", "HHSR7", "HHSR8",
    "HHSR9", "HHSR10", "HHSR11", "HHSR12", "HHSR13", "HHSR14", "HHSR15", "HHSR16",
    "HHSR17", "HHSR18", "HHSR19", "HHSR20", "HHSR21", "HHSR22", "HHSR23", "HHSR24",
    "HHSR25", "HHSR26", "HHSR27", "HHSR28", "HHSR29", "HHSR30", "HHSR31", "HHSR32",
    
    "HLSR1", "HLSR2", "HLSR3", "HLSR4", "HLSR5", "HLSR6", "HLSR7", "HLSR8",
    "HLSR9", "HLSR10", "HLSR11", "HLSR12", "HLSR13", "HLSR14", "HLSR15", "HLSR16",
    "HLSR17", "HLSR18", "HLSR19", "HLSR20", "HLSR21", "HLSR22", "HLSR23", "HLSR24",
    "HLSR25","HLSR26",
    
    "LLSR1", "LLSR2", "LLSR3", "LLSR4", "LLSR5", "LLSR6", "LLSR7", "LLSR8"
  };

  //statistical uncertainties
  for(int isr=0;isr<66;isr++) {
    if(srs[isr]=="CATTAG") {
      md.addNuisanceParameter("ttW"+srs[isr]+"stat","ttW","lnN","");
      md.addNuisanceParameter("ttHZ"+srs[isr]+"stat","ttHZ","lnN","");
      md.addNuisanceParameter("WW"+srs[isr]+"stat","WW","lnN","");
      md.addNuisanceParameter("XG"+srs[isr]+"stat","XG","lnN","STATXGTAG");
      md.addNuisanceParameter("rares"+srs[isr]+"stat","rares","lnN","");
      md.addNuisanceParameter("fake"+srs[isr]+"stat","fake","lnN","STATFAKETAG");
      md.addNuisanceParameter("flip"+srs[isr]+"stat","flip","lnN","");
      md.addNuisanceParameter("SIGTAG"+srs[isr]+"stat","SIGTAG","lnN","");
      
    }
    else {
      md.addNuisanceParameter("ttW"+srs[isr]+"stat","ttW","lnN","-");
      md.addNuisanceParameter("ttHZ"+srs[isr]+"stat","ttHZ","lnN","-");
      md.addNuisanceParameter("WW"+srs[isr]+"stat","WW","lnN","-");
      md.addNuisanceParameter("XG"+srs[isr]+"stat","XG","lnN","-");
      md.addNuisanceParameter("rares"+srs[isr]+"stat","rares","lnN","-");
      md.addNuisanceParameter("fake"+srs[isr]+"stat","fake","lnN","-");
      md.addNuisanceParameter("flip"+srs[isr]+"stat","flip","lnN","-");
      md.addNuisanceParameter("SIGTAG"+srs[isr]+"stat","SIGTAG","lnN","-");
    }
  }//signal regions  




  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
  
  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
   
  md.prepareDisplay();
  
  md.makeSingleDataCard("SIGTAG", "CATTAG", "selected", "ssdl2015_CATTAG_SIGTAG");


  gROOT->ProcessLine(".q");

}
