#include "analysis/src/UncertaintyTest.hh"

#include <algorithm>

UncertaintyTest::UncertaintyTest(std::string cfg){
  
  startExecution(cfg);
  initialize();

}

UncertaintyTest::~UncertaintyTest(){
 
}

void
UncertaintyTest::initialize(){

 _vc->registerVar("nLepGood");
 _vc->registerVar("LepGood_pdgId");
 _vc->registerVar("LepGood_pt");
 _vc->registerVar("LepGood_eta");
 _vc->registerVar("LepGood_phi");
 _vc->registerVar("LepGood_mass");

 //additional counter categories
 _au->addCategory( kDumCat, "dummy category");

 //additional workflow
 //addWorkflow( kAltWF, "altWF" );

 vector<string> mpts;
 mpts.push_back("LepGood_pt");
 //mpts.push_back("pt_m2");
 //addSystSource("MES",SystUtils::kNone,"%", mpts, 0.1 );
 addWSystSource("Tru",SystUtils::kNone,"%", 0.1);
}

void
UncertaintyTest::modifyWeight() {

}

void
UncertaintyTest::modifySkimming() {

}


void
UncertaintyTest::defineOutput() {

 string leps[2]={"l1","l2"};
 for(int il=0;il<2;il++) {
   _hm->addVariable(leps[il]+"Pt", 200, 0., 200.0,"p_{T}("+leps[il]+") [GeV]");
   // _hm->addVariable(leps[il]+"Eta", 60, -3.0, 3.0,"#eta("+leps[il]+") ");
   // _hm->addVariable(leps[il]+"Phi", 60, -3.1416, 3.1416,"#phi("+leps[il]+") ");
 }

}


void
UncertaintyTest::writeOutput() {
 
}


void
UncertaintyTest::run() {


  counter("denominator");
  

  //  cout<<_vc->get("LepGood_pt",0)<<endl;
  // if( _vc->get("LepGood_pt",0) >50 ) setWorkflow(kAltWF);
  // else setWorkflow(kGlobal);

  
  //if(!makeCut( _vc->get("nLepGood")==2,"nLep") ) return;

 if(!makeCut<int>( _vc->get("nLepGood"), 2, "=", "nLep") ) return;

 if(!makeCut( _vc->get("LepGood_pt",0)>50,"ptsel") ) return;

 fill("l1Pt", _vc->get("LepGood_pt") );
 // fill("l2Pt", _vc->get("LepGood_pt",1) );

 //example of shape variation 
 fillUnc("l1Pt", "LES", _vc->get("LepGood_pt",0)*0.90, 1., "Do");
 fillUnc("l1Pt", "LES", _vc->get("LepGood_pt",0)*1.10, 1., "Up");

 //error on normalization (e.g scale factor uncertainties)
 fillUnc("l1Pt", "SFEff", _vc->get("LepGood_pt",0), 0.9, "Do");
 fillUnc("l1Pt", "SFEff", _vc->get("LepGood_pt",0), 1.1, "Up");
 // //can also be done that way if the central value is not already defined and we have everything under the hand
 // fillUnc("l1Pt", "SFOther", _vc->get("LepGood_pt",0), 1, 1.1, 0.9);

}
