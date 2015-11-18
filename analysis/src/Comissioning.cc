#include "analysis/src/Comissioning.hh"

#include <algorithm>

Comissioning::Comissioning(std::string cfg){
  
  startExecution(cfg);
  initialize();

  _elMvaIdWP.resize(3);
  _elMvaIdWP[0]=0.87;
  _elMvaIdWP[1]=0.60;
  _elMvaIdWP[2]=0.17;

  _hltLines.push_back("HLT_DoubleMu");
  _hltLines.push_back("HLT_DoubleEl");
  // _hltLines.push_back("HLT_MuEG");
  // _hltLines.push_back("HLT_DoubleMuHT");
  // _hltLines.push_back("HLT_DoubleElHT");
  
  // _hltLines.push_back("HLT_SingleMu");
  // _hltLines.push_back("HLT_SingleEl");

  _au->addCategory(kElSel,"elSel");

  _susyMod = new SusyModule(_vc, _dbm);

  //_dbm->loadDb("chargeMId","comissioning_data.root","chargeMisId");
  _dbm->loadDb("chargeMId","ChargeMisIdProb_MC.root","chargeMisId");

}

Comissioning::~Comissioning(){
 
}

void
Comissioning::initialize(){

  _vc->registerVar("nVert");

  _vc->registerVar("nLepGood");
  _vc->registerVar("LepGood_pdgId");
  _vc->registerVar("LepGood_pt");
  _vc->registerVar("LepGood_eta");
  _vc->registerVar("LepGood_phi");
  _vc->registerVar("LepGood_mass");
  _vc->registerVar("LepGood_charge");
  _vc->registerVar("LepGood_tightCharge");
  _vc->registerVar("LepGood_mvaIdSpring15");
  _vc->registerVar("LepGood_mediumMuonId");
  _vc->registerVar("LepGood_convVeto");
  _vc->registerVar("LepGood_lostHits");
  _vc->registerVar("LepGood_miniIso");
  _vc->registerVar("LepGood_sip3d");
  _vc->registerVar("LepGood_dz");
  _vc->registerVar("LepGood_dxy");
  _vc->registerVar("LepGood_miniRelIso");

  _vc->registerVar("LepGood_jetPtRatio_LepAwareJEC");
  _vc->registerVar("LepGood_jetPtRatiov2");
  _vc->registerVar("LepGood_jetCorrFactor_L1");

  _vc->registerVar("LepGood_jetPtRatio_LepAwareJECv2");
  _vc->registerVar("LepGood_jetPtRelv2");

  _vc->registerVar("LepGood_mcMatchId");

  _vc->registerVar("run");
  _vc->registerVar("lumi");
  _vc->registerVar("event");

  _vc->registerVar("HLT_DoubleMu");
  _vc->registerVar("HLT_SingleMu");
  _vc->registerVar("HLT_DoubleEl");
  _vc->registerVar("HLT_SingleEl");
  _vc->registerVar("HLT_MuEG");
  _vc->registerVar("HLT_DoubleMuHT");
  _vc->registerVar("HLT_DoubleElHT");

  _vc->registerVar("met_pt");
  _vc->registerVar("met_phi");
  _vc->registerVar("met_sumEt");

  _vc->registerVar("metNoHF_pt");
  _vc->registerVar("metNoHF_phi");
  _vc->registerVar("metNoHF_sumEt");

  _vc->registerVar("nJet");
  _vc->registerVar("Jet_pt");
  _vc->registerVar("Jet_eta");
  _vc->registerVar("Jet_phi");
  _vc->registerVar("Jet_id");
  _vc->registerVar("Jet_area");
  

  _vc->registerVar("rhoCN");
  // _vc->registerVar("");
  // _vc->registerVar("");
  // _vc->registerVar("");
  // _vc->registerVar("");
  _vc->registerVar("nGenPart");
  _vc->registerVar("GenPart_eta");
  _vc->registerVar("GenPart_phi");
  _vc->registerVar("GenPart_pdgId");

  _vc->registerVar("vtxWeight");
  _vc->registerVar("genWeight");

  _dbm->loadDb("puw","PileupWeigth.root","puWeight");

  _dbm->loadDb("XSections","XSectionsSpring15.db");
  _dbm->loadDb("KFactors","kFactorsSpring15.db");

  // _dbm->loadDb("L1D","L1_data.db");
  // _dbm->loadDb("L1MC","L1_MC.db");

  //_L1NC.resize(2);
}

void
Comissioning::modifyWeight() {

  // if(_sampleName.find("runs")==(size_t)-1)
  // _weight *= _dbm->getDBValue("puw",_vc->get("nVert") );
    _isData=true;
  if(_sampleName.find("Double")==(size_t)-1) {
    _weight *= _vc->get("vtxWeight")*_vc->get("genWeight"); //_vc->get("vtxWeight")*
    _puW = _vc->get("vtxWeight")*_vc->get("genWeight"); //_vc->get("vtxWeight")*

    
    double nProc=getCurrentDS()->getSumProcWgts(); //ugly
    if(nProc==-1) nProc=getCurrentDS()->getNProcEvents();
    double w=_dbm->getDBValue("XSections",_sampleName)*_dbm->getDBValue("KFactors",_sampleName)/nProc * 100;//last number is lumi
    //cout<<w<<"  "<<_dbm->getDBValue("XSections",_sampleName)<<"  "<<nProc<<"  "<<_dbm->getDBValue("KFactors",_sampleName)<<endl;
    _puW *=w;

    //_weight *=_dbm->getDBValue("XSections",_sampleName)*_dbm->getDBValue("KFactors",_sampleName)/nProc * 848;

    _isData=false;
  }
  //cout<<_vc->get("vtxWeight")<<endl;
}

void
Comissioning::modifySkimming() {

  addSkimBranch("mass",&_mass);
  addSkimBranch("charge",&_charge);
  addSkimBranch("channel",&_channel);
  addSkimBranch("fidu",&_fidu);
  addSkimBranch("weight",&_puW);
  addSkimBranch("categ",&_categ);
  //  addSkimBranch("L1NC",&_L1NC);
}


void
Comissioning::defineOutput() {

  //Leptons
 string leps[2]={"l1","l2"};
 for(int il=0;il<2;il++) {
   _hm->addVariable(leps[il]+"Pt", 200, 0., 200.0,"p_{T}("+leps[il]+") [GeV]");
   _hm->addVariable(leps[il]+"Eta", 60, -3.0, 3.0,"#eta("+leps[il]+") ");
   _hm->addVariable(leps[il]+"Phi", 60, 0, 3.1416926524*2,"#phi("+leps[il]+") ");
 }

 _hm->addVariable("nVert", 50, 0., 50,"# vertices ");
 _hm->addVariable("lepPtRatio",120,0,1.2,"lepPtRatio(B2G) ");

 //_hm->addVariable("lepPtRatio",120,0,1.2,"lepPtRatio(B2G) ");


 //MET
 _hm->addVariable("MetPt", 200, 0., 200.0,"#slash{E}_{T} [GeV]");
 _hm->addVariable("MetPhi", 60, 0, 3.1416926524*2,"#phi(#slash{E}_{T}) [rad]");
 _hm->addVariable("MetSumEt", 1000, 0, 2000,"#Sigma E_{T} [GeV]");

 _hm->addVariable("MetNoHFPt", 200, 0., 200.0,"#slash{E}_{T}_{noHF} [GeV]");
 _hm->addVariable("MetNoHFPhi", 60, 0, 3.1416926524*2,"#phi(#slash{E}_{T}_{noHF}) [rad]");
 _hm->addVariable("MetNoHFSumEt", 1000, 0, 2000,"#Sigma E_{T}_{noHF} [GeV]");

 //W
 _hm->addVariable("MetWPt", 200, 0., 200.0,"#slash{E}_{T} [GeV]");
 _hm->addVariable("MetWPhi", 60, 0, 3.1416926524*2,"#phi(#slash{E}_{T}) [rad]");
 _hm->addVariable("MTMuPt", 200, 0., 200.0,"#M_{T}(#mu) [GeV]");
 _hm->addVariable("MTElPt", 200, 0., 200.0,"#M_{T}(e) [GeV]");
 _hm->addVariable("MTMuPtMETSel", 200, 0., 200.0,"#M_{T}(#mu) [GeV]");
 _hm->addVariable("MTElPtMETSel", 200, 0., 200.0,"#M_{T}(e) [GeV]");

 _hm->addVariable("muWPt", 200, 0., 200.0,"p_{T}(#mu) [GeV]");
 _hm->addVariable("elWPt", 200, 0., 200.0,"p_{T}(#mu) [GeV]");


 //Jets
 _hm->addVariable("nJets", 20, 0., 20.0,"# jets ");
 _hm->addVariable("Jet1Pt", 200, 0., 500.0,"#p_{T}(j1) [GeV]");
 _hm->addVariable("Jet2Pt", 200, 0., 500.0,"#p_{T}(j2) [GeV]");

 _hm->addVariable("massee",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSee",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSee",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massmm",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSmm",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSmm",200,0,200,"m_{ll} [GeV]");

 _hm->addVariable("masseeBB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSeeBB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSeeBB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massmmBB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSmmBB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSmmBB",200,0,200,"m_{ll} [GeV]");

 _hm->addVariable("masseeEB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSeeEB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSeeEB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massmmEB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSmmEB",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSmmEB",200,0,200,"m_{ll} [GeV]");

 _hm->addVariable("masseeEE",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSeeEE",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSeeEE",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massmmEE",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSmmEE",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSmmEE",200,0,200,"m_{ll} [GeV]");


 _hm->addVariable("massem",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massOSem",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("massSSem",200,0,200,"m_{ll} [GeV]");

 _hm->addVariable("nLepton",10,0,10,"# leptons ");


 _hm->addVariable("CCMassOS",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("CCMassSS",200,0,200,"m_{ll} [GeV]");
 _hm->addVariable("CCMassSSGen",200,0,200,"m_{ll} [GeV]");

 string tags[3]={"OS","SS","SSGen"};
 for(int k=0;k<3;k++) {
   
   _hm->addVariable("CCLepPt"+tags[k], 200, 0., 200.0,"p_{T} [GeV]");
   _hm->addVariable("CCLepEta"+tags[k], 60, -3.0, 3.0,"#eta ");

   for(int il=0;il<2;il++) {
     _hm->addVariable("CC"+leps[il]+"Pt"+tags[k], 200, 0., 200.0,"p_{T}("+leps[il]+") [GeV]");
     _hm->addVariable("CC"+leps[il]+"Eta"+tags[k], 60, -3.0, 3.0,"#eta("+leps[il]+") ");
     _hm->addVariable("CC"+leps[il]+"Phi"+tags[k], 60, 0, 3.1416926524*2,"#phi("+leps[il]+") ");
   }
 }

 vector<float> binsPt({10,40,60,80,100,200,300});//lim sup mise par defaut
 vector<float> binsEta({0,0.8,1.479,2.5});//lim sup mise par defaut
 _binsPt = binsPt;
 _binsEta = binsEta;
  buildCategs();

  // for(size_t i=0; i<_categs.size(); i++) {
  //   _hm->addVariable(_categs[i],1,0,1,"");
  // }

  // float bPts[6]={10,25,50,100,1000};
  // float bEtas[4]={0,0.8,1.479, 2.5};
  
  _hm->addVariable("GenChMidEl",6,binsPt,3,binsEta,"","");
  _hm->addVariable("GenChPrtEl",6,binsPt,3,binsEta,"","");
  _hm->addVariable("GenChMidMu",6,binsPt,3,binsEta,"","");
  _hm->addVariable("GenChPrtMu",6,binsPt,3,binsEta,"","");
}


void
Comissioning::writeOutput() {
 
}


void
Comissioning::run() {

  counter("denominator");

  fill("nVert",_vc->get("nVert"),_weight);
  selectObjects();
  if(!passMultiLine(false)) return;
  counter("HLT");
  if(!passMultiLine(true)) return;
  counter("HLTDouble");



  fill("nLepton",_vc->get("nLepGood"), _weight);

 if(_leptons.size()==1) { //W selection
   counter("leptonsel");
  

   float mt=Candidate::create(_met, _leptons[0])->mass();

   fill("MetWPt", _met->pt(), _weight);
   fill("MetWPhi", _met->phi(), _weight);
 
   if(std::abs(_leptons[0]->pdgId())==11) {
     fill("elWPt", _leptons[0]->pt(), _weight);
     fill("MTElPt", mt , _weight);
   }
   else {
     fill("muWPt", _leptons[0]->pt() , _weight);
     fill("MTMuPt", mt , _weight);
   }


   if(_met->pt()>25) {
     if(std::abs(_leptons[0]->pdgId())==11) 
       fill("MTElPtMETSel", mt , _weight);
     else
       fill("MTMuPtMETSel", mt , _weight);       
   }
   
 }
 if(_leptons.size()!=2) return; //not enough leptons to be interesting
 if(_leptons[0]->pt()<20 && _leptons[1]->pt()<20) return;
 //if(_vc->get("nLepGood")!=2) return; 
 counter("leptonsel");
 // if(!passMultiLine(true)) return;
 // counter("HLTDouble");
 
 fill("MetPt", _met->pt(), _weight);
 fill("MetPhi", _met->phi(), _weight);
 fill("MetSumEt", _vc->get("met_sumEt"), _weight);

 // if(_met->pt()>50) return;
 // counter("metcut");

 // fill("MetNoHFPt", _metNoHF->pt(), _weight);
 // fill("MetNoHFPhi", _metNoHF->phi(), _weight);
 // fill("MetNoHFSumEt", _vc->get("metNoHF_sumEt"), _weight);

 //cout<<_met->phi()<<"   "<<_vc->get("met_phi")<<endl;

 fill("l1Pt", _leptons[0]->pt(), _weight );
 fill("l2Pt", _leptons[1]->pt(), _weight );
 fill("l1Eta", _leptons[0]->eta(), _weight );
 fill("l2Eta", _leptons[1]->eta(), _weight );
 fill("l1Phi", _leptons[0]->phi(), _weight );
 fill("l2Phi", _leptons[1]->phi(), _weight );

 Candidate* Zcand=Candidate::create(_leptons[0], _leptons[1]);


 if(Zcand->mass()>120 || Zcand->mass()<60) return;
 //fillSkimTree();

 //computeL1NC();

 //return;


 fill("nJets", _jets.size() , _weight );
 if(_jets.size()!=0)
   fill("Jet1Pt", _jets[0]->pt() , _weight );
 if(_jets.size()>=2)
   fill("Jet2Pt", _jets[1]->pt() , _weight );

 int typeEE= (std::abs(_leptons[0]->eta())<1.5) + (std::abs(_leptons[1]->eta())<1.5);
 int typeMM= (std::abs(_leptons[0]->eta())<1.3) + (std::abs(_leptons[1]->eta())<1.3);
   

 if(std::abs(_leptons[0]->pdgId())+std::abs(_leptons[1]->pdgId()) == 22 ) {
  fill("massee", Zcand->mass() , _weight );
  if(_leptons[0]->charge()!= _leptons[1]->charge()) {
  fill("massOSee", Zcand->mass() , _weight );

     if(typeEE==0) fill("massOSeeBB", Zcand->mass() , _weight );
     if(typeEE==1) fill("massOSeeEB", Zcand->mass() , _weight );
     if(typeEE==2) fill("massOSeeEE", Zcand->mass() , _weight );
   }
   else {
     fill("massSSee", Zcand->mass() , _weight );
  
     if(typeEE==0) fill("massSSeeBB", Zcand->mass() , _weight );
     if(typeEE==1) fill("massSSeeEB", Zcand->mass() , _weight );
     if(typeEE==2) fill("massSSeeEE", Zcand->mass() , _weight );
   }
 }
 if(std::abs(_leptons[0]->pdgId())+std::abs(_leptons[1]->pdgId()) == 26 ) {
   fill("massmm", Zcand->mass() , _weight );
   fill("lepPtRatio", 1./(1.+ 1./_vc->get("LepGood_jetPtRatiov2", _leptonsIdx[0]) ) , _weight);
   fill("lepPtRatio", 1./(1.+ 1./_vc->get("LepGood_jetPtRatiov2", _leptonsIdx[1]) ) , _weight);
   
   if(_leptons[0]->charge()!= _leptons[1]->charge()) {
     fill("massOSmm", Zcand->mass() , _weight );

     if(typeMM==0) fill("massOSmmBB", Zcand->mass() , _weight );
     if(typeMM==1) fill("massOSmmEB", Zcand->mass() , _weight );
     if(typeMM==2) fill("massOSmmEE", Zcand->mass() , _weight );
   }
   else {
     fill("massSSmm", Zcand->mass() , _weight );
   
     if(typeMM==0) fill("massSSmmBB", Zcand->mass() , _weight );
     if(typeMM==1) fill("massSSmmEB", Zcand->mass() , _weight );
     if(typeMM==2) fill("massSSmmEE", Zcand->mass() , _weight );
   }
 }
 if(std::abs(_leptons[0]->pdgId())+std::abs(_leptons[1]->pdgId()) == 24 ) {
   fill("massem", Zcand->mass() , _weight );
   if(_leptons[0]->charge()!= _leptons[1]->charge()) {
     fill("massOSem", Zcand->mass() , _weight );
   
   }
   else {
     fill("massSSem", Zcand->mass() , _weight );
   
   }
 }
 

 //skimming part
 //if( std::abs(_leptons[0]->pdgId())+std::abs(_leptons[1]->pdgId()) == 24) return;

 _mass = Zcand->mass();
 _channel=std::abs(_leptons[0]->pdgId())+std::abs(_leptons[1]->pdgId());
 _charge = (_leptons[0]->charge()!= _leptons[1]->charge() );
 _fidu=typeEE;
 if(_channel==26) _fidu=typeMM;


 bool OS=_leptons[0]->charge()!= _leptons[1]->charge();
 float pt1=_leptons[0]->pt();
 float pt2=_leptons[1]->pt();
 float eta1=_leptons[0]->eta();
 float eta2=_leptons[1]->eta();

 //_categ= _categs[ getCateg(OS, pt1, pt2, eta1,eta2, _mass) ];

 fillSkimTree();


 //cross check============================
 float p1=_dbm->getDBValue("chargeMId", _leptons[0]->pt(), std::abs(_leptons[0]->eta()));
 float p2=_dbm->getDBValue("chargeMId", _leptons[1]->pt(), std::abs(_leptons[1]->eta()));

  if(p1>0.01) p1=0.0005;
  if(p2>0.01) p2=0.0005;

  float w=(p1+p2-2*p1*p2)/(p1*p2+(1-p1)*(1-p2) );

  
  if(OS) { 
    fill("CCMassOS", _mass, _weight*w );
    
    fill("CCLepPtOS",_leptons[0]->pt(), _weight*w);
    fill("CCLepPtOS",_leptons[1]->pt(), _weight*w);
    fill("CCLepEtaOS",_leptons[0]->eta(), _weight*w);
    fill("CCLepEtaOS",_leptons[1]->eta(), _weight*w);
    
    fill("CCl1PtOS",_leptons[0]->pt(), _weight*w);
    fill("CCl2PtOS",_leptons[1]->pt(), _weight*w);
    fill("CCl1EtaOS",_leptons[0]->eta(), _weight*w);
    fill("CCl2EtaOS",_leptons[1]->eta(), _weight*w);
    fill("CCl1EtaOS",_leptons[0]->phi(), _weight*w);
    fill("CCl2EtaOS",_leptons[1]->phi(), _weight*w);

  }
  if(!OS) {
    fill("CCMassSS", _mass, _weight );

    fill("CCLepPtSS",_leptons[0]->pt(), _weight);
    fill("CCLepPtSS",_leptons[1]->pt(), _weight);
    fill("CCLepEtaSS",_leptons[0]->eta(), _weight);
    fill("CCLepEtaSS",_leptons[1]->eta(), _weight);
    
    fill("CCl1PtSS",_leptons[0]->pt(), _weight);
    fill("CCl2PtSS",_leptons[1]->pt(), _weight);
    fill("CCl1EtaSS",_leptons[0]->eta(), _weight);
    fill("CCl2EtaSS",_leptons[1]->eta(), _weight);
    fill("CCl1EtaSS",_leptons[0]->phi(), _weight);
    fill("CCl2EtaSS",_leptons[1]->phi(), _weight);
  }
  if(!OS && _vc->get("LepGood_mcMatchId" ,0)==23 && _vc->get("LepGood_mcMatchId" ,0)==23 ) {
    fill("CCMassSSGen", _mass, _weight );

    fill("CCLepPtSSGen",_leptons[0]->pt(), _weight);
    fill("CCLepPtSSGen",_leptons[1]->pt(), _weight);
    fill("CCLepEtaSSGen",_leptons[0]->eta(), _weight);
    fill("CCLepEtaSSGen",_leptons[1]->eta(), _weight);
    
    fill("CCl1PtSSGen",_leptons[0]->pt(), _weight);
    fill("CCl2PtSSGen",_leptons[1]->pt(), _weight);
    fill("CCl1EtaSSGen",_leptons[0]->eta(), _weight);
    fill("CCl2EtaSSGen",_leptons[1]->eta(), _weight);
    fill("CCl1EtaSSGen",_leptons[0]->phi(), _weight);
    fill("CCl2EtaSSGen",_leptons[1]->phi(), _weight);
  }

  fill("CCMassSSGen", _mass, _weight );

  //cout<<_leptons[0]->pdgId()<<"  "<<_leptons[1]->pdgId()<<endl;

  // int cc1=isGenChMisId(_leptons[0]);
  // int cc2=isGenChMisId(_leptons[1]);
  //cout<<" lepton size "<<_leptons.size()<<endl;
  // if(cc1==0) {
  //   if(std::abs(_leptons[0]->pdgId())==11) fill("GenChMidEl",_leptons[0]->pt(),std::abs(_leptons[0]->eta()),_weight);
  //   if(std::abs(_leptons[0]->pdgId())==13) fill("GenChMidMu",_leptons[0]->pt(),std::abs(_leptons[0]->eta()),_weight);
  // } else if(cc1==1) {
  //   if(std::abs(_leptons[0]->pdgId())==11) fill("GenChPrtEl",_leptons[0]->pt(),std::abs(_leptons[0]->eta()),_weight);
  //   if(std::abs(_leptons[0]->pdgId())==13) fill("GenChPrtMu",_leptons[0]->pt(),std::abs(_leptons[0]->eta()),_weight);
  // }
  // if(cc2==0) {
  //   if(std::abs(_leptons[0]->pdgId())==11) fill("GenChMidEl",_leptons[1]->pt(),std::abs(_leptons[1]->eta()),_weight);
  //   if(std::abs(_leptons[0]->pdgId())==13) fill("GenChMidMu",_leptons[1]->pt(),std::abs(_leptons[1]->eta()),_weight);
  // } else if(cc2==1) {
  //   if(std::abs(_leptons[0]->pdgId())==11) fill("GenChPrtEl",_leptons[1]->pt(),std::abs(_leptons[1]->eta()),_weight);
  //   if(std::abs(_leptons[0]->pdgId())==13) fill("GenChPrtMu",_leptons[1]->pt(),std::abs(_leptons[1]->eta()),_weight);
  // }

}


int
Comissioning::isGenChMisId(const Candidate* c) {
  
  int nGenL=_vc->get("nGenPart");
  float dr=10, drTmp=10000;
  int idxB=-1;
  for(int ig=0;ig<nGenL;++ig) {
    dr=KineUtils::dR(c->eta(), _vc->get("GenPart_eta", ig),
		     c->phi(), _vc->get("GenPart_phi", ig) );
    if(dr<drTmp) {
      drTmp=dr;
      idxB=ig;
    }

  }

  //cout<<dr<<"  "<<(c->pdgId())<<"  "<<(std::abs(_vc->get("GenPart_pdgId",idxB)))<<endl;

  if(dr<0.1 && c->pdgId()==-_vc->get("GenPart_pdgId",idxB) ) {
    //cout<<" found misId "<<endl;
    return 0;
  }
  if(dr<0.1 && c->pdgId()==_vc->get("GenPart_pdgId",idxB) ) {
    //cout<<" found other "<<endl;
    return 1;
  }

  return -1;
}

void
Comissioning::selectObjects() {

  _leptons.clear();
  _leptonsIdx.clear();
  
  _jets.clear();
  _jetsIdxs.clear();

  _jetMatch.clear(); 
  _jetMatch.resize(25);

  _lepMatch.clear(); _lepMatch.resize(24);
  _lepMatch[0]=false;  _lepMatch[1]=false;

  for(size_t il=0;il<_vc->get("nLepGood"); il++) {

    bool isMu=std::abs(_vc->get("LepGood_pdgId", il))==13;
    //if(isMu) continue;
    //cout<<"0"<<endl;
    Candidate* cand=Candidate::create(_vc->get("LepGood_pt", il),
				      _vc->get("LepGood_eta", il),
				      _vc->get("LepGood_phi", il),
				      _vc->get("LepGood_pdgId", il),
				      _vc->get("LepGood_charge", il),
				      isMu?0.105:0.0005);
    //cout<<" youpi cand "<<cand->pdgId()<<endl;
    counter("denom",kElSel);
    if( _vc->get("LepGood_pt" , il)<10) continue;
    counter("pt",kElSel);

    // if(isMu) {//mu case
    //   if(!_susyMod->muIdSel(il, SusyModule::kTight) ) continue;
    //   if(!_susyMod->multiIsoSel(il, SusyModule::kMedium) ) continue;
    // }
    // else {
    //   if(!_susyMod->elIdSel(il, SusyModule::kTight, SusyModule::kTight) ) continue;
    //   if(!_susyMod->multiIsoSel(il, SusyModule::kDenom) ) continue;
    // }

    if(!tightLepton(cand, il, cand->pdgId()) ) continue;

    int cc1=isGenChMisId(cand);
    if(cc1==0) {
      if(std::abs(cand->pdgId())==11) fill("GenChMidEl",cand->pt(),std::abs(cand->eta()),_weight);
      if(std::abs(cand->pdgId())==13) fill("GenChMidMu",cand->pt(),std::abs(cand->eta()),_weight);
    } else if(cc1==1) {
      if(std::abs(cand->pdgId())==11) fill("GenChPrtEl",cand->pt(),std::abs(cand->eta()),_weight);
      if(std::abs(cand->pdgId())==13) fill("GenChPrtMu",cand->pt(),std::abs(cand->eta()),_weight);
    }
    

    //muons
    // if(isMu) {  
    
    //   if(_susyMod->

    //   if( std::abs(_vc->get("LepGood_eta" , il))>2.4) continue;
    //   if( _vc->get("LepGood_mediumMuonId", il)<=0 ) continue;
    //   if( _vc->get("LepGood_tightCharge" , il)<=1 ) continue;
    //   if(_vc->get("LepGood_sip3d", il)>4) continue;
    //   if( std::abs(_vc->get("LepGood_dz", il))>0.1) continue;
    //   if( std::abs(_vc->get("LepGood_dxy", il))>0.05) continue;
    //   if( _vc->get("LepGood_miniRelIso", il)>0.1) continue;
    
    // }
    // else { //electrons
   
    //   if(std::abs(_vc->get("LepGood_eta", il))>2.5) continue;
    //   if(std::abs(_vc->get("LepGood_eta", il))>1.4442 &&
    // 	 std::abs(_vc->get("LepGood_eta", il))<1.566) continue;
    //   counter("eta",kElSel);
   
    //   if(_vc->get("LepGood_convVeto", il)!=1) continue;   counter("conv",kElSel);
    //   if(_vc->get("LepGood_lostHits", il)>0) continue; counter("lostHit",kElSel);
    //   if(_vc->get("LepGood_tightCharge", il)<=1) continue;  counter("charge",kElSel);
      
    //   int etaBin=-1;
    //   if(std::abs(_vc->get("LepGood_eta", il)) < 0.8) etaBin=0;
    //   else if(std::abs(_vc->get("LepGood_eta", il)) < 1.479) etaBin=1;
    //   else if(std::abs(_vc->get("LepGood_eta", il)) < 2.5) etaBin=2;
      
    //   if(_vc->get("LepGood_mvaIdSpring15", il) <  _elMvaIdWP[etaBin] ) continue;
    //   counter("mvaId",kElSel);
    //   if(_vc->get("LepGood_sip3d", il)>4) continue; counter("sip3d",kElSel);
    //   if( std::abs(_vc->get("LepGood_dz", il))>0.1) continue; counter("dz",kElSel);
    //   if( std::abs(_vc->get("LepGood_dxy", il))>0.05) continue; counter("dxy",kElSel);
    //   if( _vc->get("LepGood_miniRelIso", il)>0.1) continue;counter("isolation",kElSel);
    // } 


    //cout<<" super cand "<<cand->pdgId()<<endl;
    _leptons.push_back(cand);
    _leptonsIdx.push_back(il);

    // float tmp=100000;
    // bool match=false;
    // //cout<<_vc->get("nJet")<<endl;
    // for(size_t ij=0;ij<_vc->get("nJet");ij++) { //super ugly
    //   //cout<<ij<<endl;
    //   if(_vc->get("Jet_id",ij)<1) continue;
    //   Candidate* jet=Candidate::create(_vc->get("Jet_pt", ij),
    // 				       _vc->get("Jet_eta", ij),
    // 				       _vc->get("Jet_phi", ij) );

    //   float dr=_leptons[il]->dR( jet );
    //   if( dr<tmp) {
    // 	tmp = dr;
    // 	  _jetMatch[il]=ij;
    // 	  //cout<<il<<"   "<<ij<<"  "<<dr<<endl;
    // 	  match=true;
    //   }
    // }
    // if(match)
    //   _lepMatch[il]=true;

  }//lep loop



  for(size_t ij=0;ij<_vc->get("nJet");ij++) {
    
    if(_vc->get("Jet_id",ij)<1) continue;

    Candidate* jet=Candidate::create(_vc->get("Jet_pt", ij),
				     _vc->get("Jet_eta", ij),
				     _vc->get("Jet_phi", ij) );
    
    bool findLep=false;
    for(unsigned int il=0;il<_leptons.size();il++) {
      // //cout<<"\t ====> "<<leptons->at(il)->pt()<<"   "
      // 	  <<leptons->at(il)->eta()<<"  "<<leptons->at(il)->phi()<<" --> "<<leptons->at(il)->dR( jet )<<endl;

      if( _leptons[il]->dR( jet )<0.4 ) {findLep=true; 
	continue;} 
    }
    if(findLep) continue;
    
    if(jet->pt()<25) continue;
    _jets.push_back(jet);
    _jetsIdxs.push_back(ij);
  }

  _met = Candidate::create( _vc->get("met_pt"), _vc->get("met_phi") );  
  //  _metNoHF = Candidate::create( _vc->get("metNoHF_pt"), _vc->get("metNoHF_phi") );

}

bool
Comissioning::passHLLine(string line) {
  if(_vc->get(line)) return true;
  else return false;
}

bool
Comissioning::passMultiLine(bool doubleOnly) {
  //return true;
  for(size_t ih=0;ih<_hltLines.size();ih++) {
    //if(doubleOnly && ih>5) continue;
    if(passHLLine(_hltLines[ih])) return true;
  }

  return false;
}

void
Comissioning::computeL1NC() {

  for(size_t il=0;il<2;il++) {
    int ij=_jetMatch[il];
  
    float a=_vc->get("Jet_area",ij);
    float pt= _vc->get("Jet_pt",ij);
    float eta= _vc->get("Jet_eta",ij);
    float rho= _vc->get("rhoCN");
    float c0=_dbm->getDBValue( _isData?("L1D"):("L1MC"),eta);
    float c1=_dbm->getDBErrH( _isData?("L1D"):("L1MC"),eta);
    float c2=_dbm->getDBErrL( _isData?("L1D"):("L1MC"), eta );

    _L1NC[il]=max(0.0001,1.-a*(c0+(c1*rho)*(1+c2*log(pt)))/pt);
    if(!_lepMatch[il]) _L1NC[il]=1;
    // cout<<ij<<"  "<<il<<"  --> "<<_L1NC[il]<<"   "<<a<<"   "<<rho<<"  "<<pt<<"  "<<eta
    // 	<<"  "<<_vc->getSize("Jet_area")<<"  "<<_leptons[il]->eta()<<endl;
  }


}


void
Comissioning::buildCategs() {

  int N= pow( _binsPt.size()-1, 2)*2*pow( _binsEta.size()-1, 2 );// *pow( _binsEta.size()-1, 2 )*2;// * pow( _binsPt.size()-1, 2) ;//pow( _binsPt.size(), 2 )*pow( _binsEta.size(), 2 ) *2;
  vector<float> ct({0,1,2});
  
  map<string, vector<float> > bins;
  bins["os"] = ct;
  bins["l1pt"] = _binsPt;
  bins["l1eta"] = _binsEta;
  bins["L2pt"] = _binsPt;
  bins["L2eta"] = _binsEta;
  
  string cname;
  map<string, int> vars; 
  bool flag=false;
  int k=0;
  for(int ic=0;ic<N;ic++) {
    
    //building the name and the categories;
    string cname = "";
    int n=ic;
    for(map<string,vector<float> >::const_iterator it=bins.begin();
	it!=bins.end();++it) {
      int N=it->second.size()-1;
      //if(it->first=="OS") N=it->second.size()-1;
      vars[ it->first ] = n%N;
      n=(int)(n/N);
      flag=false;

      // if(it->first=="L2pt") {

      // 	int pt1B=atoi( cname.substr(cname.find("l1pt")+4,1).c_str() );
      // 	//int eta1B=atoi( cname.substr(cname.find("l1eta")+5,1).c_str() );
      // 	if(vars[ it->first ] > pt1B )
      // 	  flag=true;
      // 	//cout<<cname<<"  "<<vars[ it->first ]<<"  "<<pt1B<<" --> "<<flag<<endl;
      // }
      // if(it->first=="L2eta") {
      // 	int eta1B=atoi( cname.substr(cname.find("l1eta")+5,1).c_str() );
      // 	if( vars[ it->first ] > eta1B)
      // 	  flag=true;
      // }

      cname += it->first;
      ostringstream os;
      os<<vars[ it->first ];
      cname+=os.str()+"_";
    }

    int eta1B=atoi( cname.substr(cname.find("l1eta")+5,1).c_str() );
    int eta2B=atoi( cname.substr(cname.find("L2eta")+5,1).c_str() );
    int pt1B=atoi( cname.substr(cname.find("l1pt")+4,1).c_str() );
    int pt2B=atoi( cname.substr(cname.find("L2pt")+4,1).c_str() );

    if(pt2B>pt1B) continue;
    if(eta2B<eta1B && pt2B==pt1B) continue;

    if(flag) continue;
    //cout<<ic<<"  "<<cname<<endl;
   
    _categs[cname]=k;//.push_back(cname);

    
    ostringstream o1, o2, e1, e2;
    o1 << _binsPt[vars["l1pt"]];
    o2 << _binsPt[vars["L2pt"]];
    e1 << _binsEta[vars["l1eta"]];
    e2 << _binsEta[vars["L2eta"]];
    string name="l1Pt_"+o1.str()+"_l1Eta_"+e1.str()+"_l2Pt_"+o2.str()+"_l2Eta_"+e2.str();
    if(vars["os"]==1) name+="_OS";
    else name +="_SS";
    _hm->addVariable(name, 60,0,120, "m_{ll} [GeV] ");

    cout<<k<<"\t"<<vars["os"]<<"\t"<<_binsPt[vars["l1pt"]]<<"\t"<<_binsEta[vars["l1eta"]]<<"\t"<<_binsPt[vars["L2pt"]]<<"\t"<<_binsEta[vars["L2eta"]]<<" =====> "<<name<<endl;

    k++;
  }//idx




}

string
Comissioning::getCateg(bool OS, float pt1, float pt2, float eta1, float eta2, float mass) {
  
  int pt1b=StatUtils::findBin<float>(pt1, _binsPt);
  int pt2b=StatUtils::findBin<float>(pt2, _binsPt);
  int eta1b=StatUtils::findBin<float>(std::abs(eta1), _binsEta );
  int eta2b=StatUtils::findBin<float>(std::abs(eta2), _binsEta );

  int tmp;
  if(pt2b>pt1b) {
    tmp=pt2b;
    pt2b=pt1b;
    pt1b=tmp;
  }
  if(pt2b==pt1b && eta2b<eta1b) {
    tmp=eta2b;
    eta2b=eta1b;
    eta1b=tmp;
  }

  // cout<<"("<<pt1<<","<<pt2<<","<<eta1<<","<<eta2<<") ==> ("
  //     <<pt1b<<","<<pt2b<<","<<eta1b<<","<<eta2b<<")"<<endl;

  ostringstream op1, op2, oe1, oe2, oo;
  oo << (int)OS;
  op1 << pt1b;// StatUtils::findBin<float>(pt1, _binsPt);
  op2 << pt2b;//StatUtils::findBin<float>(pt2, _binsPt);
  oe1 << eta1b;//StatUtils::findBin<float>(std::abs(eta1), _binsEta );
  oe2 << eta2b;//StatUtils::findBin<float>(std::abs(eta2), _binsEta );
  
  string cname="L2eta"+oe2.str()+"_L2pt"+op2.str()+"_l1eta"+oe1.str()+"_l1pt"+op1.str()+"_os"+oo.str()+"_";
    //"OS"+oo.str()+"_l1eta"+oe1.str()+"_l1pt"+op1.str()+"_l2eta"+oe2.str()+"_l2pt"+op2.str()+"_";
  

  ostringstream o1, o2, e1, e2;
  o1 << _binsPt[pt1b];
  o2 << _binsPt[pt2b];
  e1 << _binsEta[eta1b];
  e2 << _binsEta[eta2b];
  string name="l1Pt_"+o1.str()+"_l1Eta_"+e1.str()+"_l2Pt_"+o2.str()+"_l2Eta_"+e2.str();
  if(OS) name+="_OS";
  else name+="_SS";

  // cout<<name<<endl;
    fill(name, mass, _weight);

  return cname;
}



// THnSparseF*
// Comissioning::computeProbChargeMisId() {

//   int* nBins=new int(4);
//   double* min=new double(4);
//   double* max=new double(4);

//   for(int i=0;i<4;i++) {
//     if(i%2==0) { //ptLep
//       nBins[i] = _binsPt.size()-1;
//       min[i] = _binsPt[0];
//       max[i] = _binsPt.back();
//     }
//     else {
//       nBins[i] = _binsEta.size()-1;
//       min[i] = _binsEta[0];
//       max[i] = _binsEta.back();
//     }
//   }

//   THnSparseF* db=new THnSparseF("chargeMisId","chargeMisId", nBins, min, max);
//   //THnSparseF* db=new THnSparseF("chargeMisId","chargeMisId", nBins, min, max);

//   string cname="";
//   string rname;
//   for(size_t ic=0;ic<_categs.size(); ic++) {
//     cname=_categs[i];
//     rname=cname.substr(4,cname.size()-5);

//     bool os=(bool)( atoi( cname.substr(2,1).c_str() ) );
//     if(os) continue;
    
//     int eta1=atoi( cname.substr(9,1).c_str() );
//     int pt1=atoi( cname.substr(15,1).c_str() );
//     int eta2=atoi( cname.substr(22,1).c_str() );
//     int pt2=atoi( cname.substr(28,1).c_str() );
      
//     rname="OS1_"+rname;

//     TH1* den=_hm->getHisto(cname, 0);
//     TH1* num=_hm->getHisto(rname, 0);

//   }
  
  

// }



bool 
Comissioning::tightLepton(const Candidate*c, int idx, int pdgId) {

  if(abs(pdgId)==13) {//mu case
    if(!_susyMod->muIdSel(c, idx, SusyModule::kTight) ) return false;
    if(!_susyMod->multiIsoSel(idx, SusyModule::kMedium) ) return false;
  }
  else {
    //cout<<" 0 "<<endl;
    if(!_susyMod->elIdSel(c, idx, SusyModule::kTight, SusyModule::kTight) ) return false; //   cout<<" 1 "<<endl;
    if(!_susyMod->multiIsoSel(idx, SusyModule::kTight) ) return false;  //  cout<<" 2 "<<endl;
    //if(!_susyMod->elHLTEmulSel(idx, (_HT<300) ) ) return false; //_hltDLHT
    //cout<<" 3 "<<endl;
  }

  return true;
}
