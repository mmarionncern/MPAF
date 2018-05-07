#include "analysis/src/ChargeFlipAnalyzer.hh"

#include <algorithm>

ChargeFlipAnalyzer::ChargeFlipAnalyzer(std::string cfg){
  
  //startExecution(cfg);
 
  _susyMod=new SusyModule(_vc);
  
  _dbm->loadDb("ElNIso"    , "frUCSX.root", "elNon");
  _dbm->loadDb("MuNIso"    , "frUCSX.root", "muNon");
  _dbm->loadDb("ElNIsoUp"  , "db2016/FakeRatio2016_ETH.root", "MR_RatElMapPtCorrHI_non/datacorrUCSX");
  _dbm->loadDb("MuNIsoUp"  , "db2016/FakeRatio2016_ETH.root", "MR_RatMuMapPtCorrHI_non/datacorrUCSX");
  _dbm->loadDb("ElNIsoDo"  , "db2016/FakeRatio2016_ETH.root", "MR_RatElMapPtCorrLO_non/datacorrUCSX");
  _dbm->loadDb("MuNIsoDo"  , "db2016/FakeRatio2016_ETH.root", "MR_RatMuMapPtCorrLO_non/datacorrUCSX");

  _dbm->loadDb("ElIso"    , "frUCSX.root", "elIso");
  _dbm->loadDb("MuIso"    , "frUCSX.root", "MuIso");
  _dbm->loadDb("ElIsoUp"  , "db2016/FakeRatio2016_ETH.root", "MR_RatElMapPtCorrHI_iso/datacorrUCSX");
  _dbm->loadDb("MuIsoUp"  , "db2016/FakeRatio2016_ETH.root", "MR_RatMuMapPtCorrHI_iso/datacorrUCSX");
  _dbm->loadDb("ElIsoDo"  , "db2016/FakeRatio2016_ETH.root", "MR_RatElMapPtCorrLO_iso/datacorrUCSX");
  _dbm->loadDb("MuIsoDo"  , "db2016/FakeRatio2016_ETH.root", "MR_RatMuMapPtCorrLO_iso/datacorrUCSX");

  _dbm->loadDb("ElNIsoMC"    , "db2016/qcd_FR.root", "ElMapPtCorr_non");
  _dbm->loadDb("ElIsoMC"     , "db2016/qcd_FR.root", "ElMapPtCorr_iso");


  _dbm->loadDb("ElIsoMCMVAM"    , "fr_susy_data_v2.2_310117.root","FR_susy_wpM_el_data_comb");
  // _dbm->loadDb("ElIsoUpMVAM"    , "fr_susy_data_v2.0_041216.root","FR_susy_wpV_el_data_comb_up");
  // _dbm->loadDb("ElIsoDoMVAM"    , "fr_susy_data_v2.0_041216.root","FR_susy_wpV_el_data_comb_down");

  _dbm->loadDb("ElIsoMCMVAVT"    , "fr_susy_data_v2.2_310117.root","FR_susy_wpV_el_data_comb");
  // _dbm->loadDb("ElIsoUpMVAVT"    , "fr_susy_data_v2.0_041216.root","FR_susy_wpV_el_data_comb_up");
  // _dbm->loadDb("ElIsoDoMVAVT"    , "fr_susy_data_v2.0_041216.root","FR_susy_wpV_el_data_comb_down");


  _susyMod->configureLeptonId(SusyModule::kCB);
  initialize();
}

ChargeFlipAnalyzer::~ChargeFlipAnalyzer(){
 
}

void
ChargeFlipAnalyzer::initialize(){

  _vc->registerVar("nLepGood");
  _vc->registerVar("LepGood_pdgId");
  _vc->registerVar("LepGood_pt");
  _vc->registerVar("LepGood_eta");
  _vc->registerVar("LepGood_phi");
  _vc->registerVar("LepGood_charge");
  _vc->registerVar("LepGood_tightCharge"          );
  _vc->registerVar("LepGood_mvaIdSpring15"        );
  _vc->registerVar("LepGood_mvaIdSpring16GP"        );
  _vc->registerVar("LepGood_pdgId"                );
  _vc->registerVar("LepGood_relIso03"             );
  _vc->registerVar("LepGood_relIso04"             );
  _vc->registerVar("LepGood_etaSc"                );
  _vc->registerVar("LepGood_energySc"             );
  _vc->registerVar("LepGood_jetPtRatiov2"         );
  _vc->registerVar("LepGood_jetPtRelv2"           );
  _vc->registerVar("LepGood_jetBTagCSV"           );
  //_vc->registerVar("LepGood_jetRawPt"             );
  _vc->registerVar("LepGood_jetCorrFactor_L1L2L3Res");
  _vc->registerVar("LepGood_miniRelIso"           );
  _vc->registerVar("LepGood_dxy"                  );
  _vc->registerVar("LepGood_dz"                   );
  _vc->registerVar("LepGood_sip3d"                );
  _vc->registerVar("LepGood_convVeto"             );
  _vc->registerVar("LepGood_lostHits"             );
  _vc->registerVar("LepGood_mvaSusy"              );
  _vc->registerVar("LepGood_mcMatchId"            );
  _vc->registerVar("LepGood_mcMatchPdgId"         );
  _vc->registerVar("LepGood_mcUCSXMatchId"        );
  _vc->registerVar("LepGood_mcMatchAny"           );
  _vc->registerVar("LepGood_sigmaIEtaIEta"        );
  _vc->registerVar("LepGood_dEtaScTrkIn"          );
  _vc->registerVar("LepGood_dPhiScTrkIn"          );
  _vc->registerVar("LepGood_hadronicOverEm"       );
  _vc->registerVar("LepGood_eInvMinusPInv"        );
  _vc->registerVar("LepGood_ecalPFClusterIso"     );
  _vc->registerVar("LepGood_hcalPFClusterIso"     );
  _vc->registerVar("LepGood_dr03TkSumPt"          );
  //_vc->registerVar("LepGood_jetDecPtRatio"        );
  _vc->registerVar("LepGood_mvaSUSY"              );

  _vc->registerVar("HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

  //MVA variables
  _vc->registerVar("LepGood_isFO_Recl");
  _vc->registerVar("LepGood_isTight_Recl");
  _vc->registerVar("LepGood_isFO_Mini");
  _vc->registerVar("LepGood_isTight_Mini");

  // _vc->registerVar("nDiscLep");
  // _vc->registerVar("DiscLep_pdgId");
  // _vc->registerVar("DiscLep_pt");
  // _vc->registerVar("DiscLep_eta");
  // _vc->registerVar("DiscLep_phi");
  // _vc->registerVar("DiscLep_charge");
  // _vc->registerVar("DiscLep_tightCharge"          );
  // _vc->registerVar("DiscLep_mvaIdSpring15"        );
  // _vc->registerVar("DiscLep_pdgId"                );
  // _vc->registerVar("DiscLep_relIso03"             );
  // _vc->registerVar("DiscLep_relIso04"             );
  // _vc->registerVar("DiscLep_etaSc"                );
  // _vc->registerVar("DiscLep_energySc"             );
  // _vc->registerVar("DiscLep_jetPtRatiov2"         );
  // _vc->registerVar("DiscLep_jetPtRelv2"           );
  // _vc->registerVar("DiscLep_jetBTagCSV"           );
  // _vc->registerVar("DiscLep_jetRawPt"             );
  // _vc->registerVar("DiscLep_jetCorrFactor_L1L2L3Res");
  // _vc->registerVar("DiscLep_miniRelIso"           );
  // _vc->registerVar("DiscLep_dxy"                  );
  // _vc->registerVar("DiscLep_dz"                   );
  // _vc->registerVar("DiscLep_sip3d"                );
  // _vc->registerVar("DiscLep_convVeto"             );
  // _vc->registerVar("DiscLep_lostHits"             );
  // _vc->registerVar("DiscLep_mvaSusy"              );
  // _vc->registerVar("DiscLep_mcMatchId"            );
  // _vc->registerVar("DiscLep_mcMatchPdgId"         );
  // _vc->registerVar("DiscLep_mcUCSXMatchId"        );
  // _vc->registerVar("DiscLep_mcMatchAny"           );
  // _vc->registerVar("DiscLep_sigmaIEtaIEta"        );
  // _vc->registerVar("DiscLep_dEtaScTrkIn"          );
  // _vc->registerVar("DiscLep_dPhiScTrkIn"          );
  // _vc->registerVar("DiscLep_hadronicOverEm"       );
  // _vc->registerVar("DiscLep_eInvMinusPInv"        );
  // _vc->registerVar("DiscLep_ecalPFClusterIso"     );
  // _vc->registerVar("DiscLep_hcalPFClusterIso"     );
  // _vc->registerVar("DiscLep_dr03TkSumPt"          );



  _vc->registerVar("isData");

  _vc->registerVar("nJet");
  _vc->registerVar("Jet_pt");
  _vc->registerVar("Jet_eta");
  _vc->registerVar("Jet_phi");

  _vc->registerVar("nDiscJet");
  _vc->registerVar("DiscJet_pt");
  _vc->registerVar("DiscJet_eta");
  _vc->registerVar("DiscJet_phi");

  _vc->registerVar("met_pt");
  _vc->registerVar("met_phi");

  _vc->registerVar("lumi");
  _vc->registerVar("run");
  _vc->registerVar("evt");
  _vc->registerVar("nTrueInt");
  _vc->registerVar("nVert");
  _vc->registerVar("genWeight");

  //Databases
  _dbm->loadDb("XS", "XSectionsSpring16.db");  
  _dbm->loadDb("KF", "kFactorsSpring16.db" );  
  _dbm->loadDb("puWeights","puWeights_37fb.root","puw");
  //_dbm->loadDb("fliprate"  , "chargeMId_80X_2016.root", "elChMId");
  _dbm->loadDb("fliprate"  , "chargeMId_80X_data_Moriond.root", "chargeMisId");
  _dbm->loadDb("fliprateMVAM"  , "chargeMId_80X_2016_AllMVA.root", "elChMId");
  _dbm->loadDb("fliprateMVAVT"  , "chargeMId_80X_2016_AllMVA.root", "elChMId");

  _valid=(bool)getCfgVarI("validation", 0);

  addWorkflow( 1, "SSW" );
}

void
ChargeFlipAnalyzer::modifyWeight() {
  _weight=1;
  _weightMVAM=1;
  _weightMVAVT=1;
  if(!_vc->get("isData") && !_valid ) {
    _weight = _dbm->getDBValue("puWeights", _vc->get("nTrueInt"))*_vc->get("genWeight");
    double nProc=getCurrentDS()->getSumProcWgts(); 
    if(nProc==-1) nProc=getCurrentDS()->getNProcEvents();
    double w=_dbm->getDBValue("XS", _sampleName) * _dbm->getDBValue("KF", _sampleName)/nProc * 1;//last number is lumi
    w*=36500;
    _weight *=w;
  }
  _weightMVAM=_weight;
  _weightMVAVT=_weight;
}

void
ChargeFlipAnalyzer::modifySkimming() {
  addSkimBranch<float>("mZ",&_mZ);
  addSkimBranch<float>("w",&_weight);
  addSkimBranch<int>("aux",&_aux);
  addSkimBranch<int>("sample",&_IS);
  
  addSkimBranch<float>("mZMVAM",&_mZMVAM);
  addSkimBranch<float>("wMVAM",&_weightMVAM);
  addSkimBranch<int>("auxMVAM",&_auxMVAM);
  
  addSkimBranch<float>("mZMVAVT",&_mZMVAVT);
  addSkimBranch<float>("wMVAVT",&_weightMVAVT);
  addSkimBranch<int>("auxMVAVT",&_auxMVAVT);
  //addSkimBranch<int>("sample",&_IS);

}


void
ChargeFlipAnalyzer::defineOutput() {

  _hm->addVariable("LSRGen" , 100, 0., 1.,"LSR ");
  _hm->addVariable("LSRFake", 100, 0., 1.,"LSR ");

  _hm->addVariable("IsoGen" , 2, 0., 2.,"Iso ");
  _hm->addVariable("IsoFake", 2, 0., 2.,"Iso ");

  _hm->addVariable("StdIsoGen" , 100, 0., 1.,"relIso03 ");
  _hm->addVariable("StdIsoFake", 100, 0., 1.,"relIso03 ");

  _hm->addVariable("MVAGen" , 100, 0., 1.,"mva ");
  _hm->addVariable("MVAFake", 100, 0., 1.,"mva ");


  string type[3]={"","MVAM","MVAVT"};
  for(int it=0;it<3;it++) {

    string leps[2]={"l1","l2"};
    for(int il=0;il<2;il++) {
      _hm->addVariable(leps[il]+"Pt"+type[it], 200, 0., 200.0,"p_{T}("+leps[il]+") [GeV]");
      _hm->addVariable(leps[il]+"Eta"+type[it], 60, -3.0, 3.0,"#eta("+leps[il]+") ");
      _hm->addVariable(leps[il]+"Phi"+type[it], 60, 0, 3.1416926524*2,"#phi("+leps[il]+") ");
    }
    _hm->addVariable("nVert"+type[it], 50, 0., 50,"# vertices ");
    _hm->addVariable("MetPt"+type[it], 200, 0., 200.0,"#slash{E}_{T} [GeV]");
    _hm->addVariable("nJets"+type[it], 20, 0., 20.0,"# jets ");
    _hm->addVariable("mass"+type[it],200,0,200,"m_{ll} [GeV]");

    vector<float> binsPt({10,20,50,100,200,300});//lim sup mise par defaut
    vector<float> binsEta({0,0.8,1.479,2.5});//lim sup mise par defaut
    vector<float> binsEtaMu({0,1.2,2.4});
    _binsPt = binsPt;
    _binsEta = binsEta;
    
    _hm->addVariable("GenChMidEl"+type[it],5,binsPt,3,binsEta,"","");
    _hm->addVariable("GenChPrtEl"+type[it],5,binsPt,3,binsEta,"","");
    _hm->addVariable("GenChMidElAll"+type[it],5,binsPt,3,binsEta,"","");
    _hm->addVariable("GenChPrtElAll"+type[it],5,binsPt,3,binsEta,"","");

  }

}

void
ChargeFlipAnalyzer::writeOutput() {
 
}


void
ChargeFlipAnalyzer::run() {
  //_weight=1;
  _leps.clear();
  _fakables.clear();
  _idFakables.clear();
  _idLeps.clear();
  _lepsMVAM.clear();
  _fakablesMVAM.clear();
  _idFakablesMVAM.clear();
  _idLepsMVAM.clear();
  _lepsMVAVT.clear();
  _fakablesMVAVT.clear();
  _idFakablesMVAVT.clear();
  _idLepsMVAVT.clear();
  _aux=1;
  _auxMVAM=1;
  _auxMVAVT=1;
  _IS=0;
  
  if(_vc->get("isData") && 
     !passHLLine("HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") ) return;

  if(_vc->get("nLepGood")!=2) return;
  if(std::abs(_vc->get("LepGood_pdgId",0))!=11 || std::abs(_vc->get("LepGood_pdgId",1))!=11) return;

  if(_sampleName.find("DY")!=string::npos) _IS=1;
  if(_sampleName.find("TT")!=string::npos) _IS=2;
  

  makeCandList("LepGood", _leps, _idLeps,_fakables, _idFakables, "");
  makeCandList("LepGood", _lepsMVAM, _idLepsMVAM,_fakablesMVAM, _idFakablesMVAM, "MVAM");
  makeCandList("LepGood", _lepsMVAVT, _idLepsMVAVT,_fakablesMVAVT, _idFakablesMVAVT, "MVAVT");

  // cout<<" -> "<<_leps.size()<<"   "<<_fakables.size()<<" <> "
  //     <<_lepsMVAM.size()<<"   "<<_fakablesMVAM.size()<<" <> "
  //     <<_lepsMVAVT.size()<<"   "<<_fakablesMVAVT.size()<<" <> "
  //     <<_weight<<"  "<<_weightMVAM<<"  "<<_weightMVAVT<<endl;

  _mZ=-1;
  _mZMVAM=-1;
  _mZMVAVT=-1;
  // cout<<" // "<<_mZ<<" > "<<_mZMVAM<<" > "<<_mZMVAVT<<endl;
  if((_leps.size()+_fakables.size())==2)
    skimming("", _leps, _idLeps, _fakables, _idFakables, _aux, _IS, _mZ, _weight );
  if((_lepsMVAM.size()+_fakablesMVAM.size())==2)
    skimming("MVAM", _lepsMVAM, _idLepsMVAM, _fakablesMVAM, _idFakablesMVAM, _auxMVAM, _ISMVAM, _mZMVAM, _weightMVAM );
  if((_lepsMVAVT.size()+_fakablesMVAVT.size())==2)
    skimming("MVAVT", _lepsMVAVT, _idLepsMVAVT, _fakablesMVAVT, _idFakablesMVAVT, _auxMVAVT, _ISMVAVT, _mZMVAVT, _weightMVAVT );

  // cout<<_mZ<<" > "<<_mZMVAM<<" > "<<_mZMVAVT<<endl;
  if( !(_mZ>50 && _mZ<130) && !(_mZMVAM>50 && _mZMVAM<130) && !(_mZMVAVT>50 && _mZMVAVT<130) ) return;
  if(!_valid) fillSkimTree();
  //cout<<" selected "<<endl;

  if(_vc->get("met_pt")>50) return;
  //cout<<_valid<<"  "<<_leps.size()<<"  "<<_lepsMVAM.size()<<"  "<<_lepsMVAVT.size()<<"  ->  "<<(!_valid && (_leps.size()==2 || _lepsMVAM.size()==2 || _lepsMVAVT.size()==2))<<endl;
  if(!( (_leps.size()==2 || _lepsMVAM.size()==2 || _lepsMVAVT.size()==2)) ) return;
  //_valid
  //cout<<" ------------------------ "<<_leps.size()<<"   "<<_lepsMVA.size()<<endl;

  if(_leps.size()==2)
    fillChargeFlipPlots("",_leps, _idLeps);
  if(_lepsMVAM.size()==2)
    fillChargeFlipPlots("MVAM",_lepsMVAM, _idLepsMVAM);
  if(_lepsMVAVT.size()==2)
    fillChargeFlipPlots("MVAVT",_lepsMVAVT, _idLepsMVAVT);
  

  // int run=_vc->get("run");
  // int lumi=_vc->get("lumi");
  // unsigned long event=_vc->get("evt");
  // _it=_eventsskip.find(run);
  // if(_it!=_eventsskip.end() ) {
  //   _itM=_it->second.find(std::make_pair(lumi,event));
  //   if(_itM!=_it->second.end()) { 
  //     //cout<<"rejecting event "<<run<<"  "<<lumi<<"  "<<event<<endl;
  //     return;

  //   }
  // }


}

void
ChargeFlipAnalyzer::makeCandList(const string& coll, 
				 CandList& listLeps, 
				 vector<int>& idxLeps,
				 CandList& listFakes, 
				 vector<int>& idxFakes,
				 const string& type) {
 
  size_t nLep=_vc->get("n"+coll);
  //cout<<" new list ==================================================== "<<nLep<<endl;
  for(size_t il=0;il<nLep;il++) {
    
   
    
    Candidate* obj=Candidate::create(KineUtils::et(_vc->get(coll+"_energySc", il),
						   _vc->get(coll+"_etaSc", il)),
				     _vc->get(coll+"_etaSc", il),
				     _vc->get(coll+"_phi", il),
				     _vc->get(coll+"_pdgId",il),
				     _vc->get(coll+"_charge",il) );

    float ptCorr=_susyMod->conePt(il,SusyModule::kTight)/_vc->get(coll+"_pt", il)*obj->pt();
    Candidate* objPtCorr=Candidate::create( ptCorr,
					    _vc->get("LepGood_eta", il),
					    _vc->get("LepGood_phi", il)
					    );
 
     if(std::abs(_vc->get(coll+"_pdgId",il))!=11) continue;

     bool passTightId=( (type==""    && _susyMod->elIdSelV2(obj, il, "LepGood", SusyModule::kTight, true, true, false) ) ||
			(type=="MVAM" && _vc->get("LepGood_isTight_Mini",il) && _vc->get("LepGood_tightCharge",il)>1 ) ||
			(type=="MVAVT" && _vc->get("LepGood_isTight_Recl",il) )
			);
     bool passFakableId=( (type==""    && _susyMod->elIdSelV2(obj, il, "LepGood", SusyModule::kFakable, true, true, false) ) ||
			  (type=="MVAM" && _vc->get("LepGood_isFO_Mini",il) && _vc->get("LepGood_tightCharge",il)>1 ) ||
			  (type=="MVAVT" && _vc->get("LepGood_isFO_Recl",il) )
			  );
     

    if(_vc->get(coll+"_pt",il)>10 && !_vc->get("isData") && passTightId ) {

      // if(type=="MVA")
      // 	cout<<" --<>> "<<_vc->get("LepGood_convVeto", il)<<"  "
      // 	    <<_vc->get("LepGood_lostHits", il)<<"   "<<_vc->get("LepGood_tightCharge",il)<<endl;

      int cc1=_vc->get("LepGood_mcUCSXMatchId",il) ;
      if(cc1==0) {
	fill("GenChPrtElAll"+type,_vc->get("LepGood_pt",il), std::abs(_vc->get("LepGood_eta",il)), 1);
      } else if(cc1==1) {
	fill("GenChMidElAll"+type,_vc->get("LepGood_pt",il), std::abs(_vc->get("LepGood_eta",il)), 1);
      }
    }
    

    if( (_valid&&obj->pt()<10) || (!_valid&&_vc->get(coll+"_pt",il)<10) ) continue;
    if( !passFakableId ) continue; //!_susyMod->elIdSelV2(obj, il, "LepGood", SusyModule::kFakable, true, true, false)
    
    if(passTightId) {
      listLeps.push_back(obj);
      idxLeps.push_back(il);
    } else {
      listFakes.push_back(objPtCorr);
      idxFakes.push_back(il);
    }
    
  } //loop
  

}


float 
ChargeFlipAnalyzer::getFR(Candidate* cand, int idx, const string& type) {
  string db;
  float ptM=10;
  if( std::abs(cand->pdgId())==13) db="Mu";
  else { db="El"; ptM=15;}
  
  // // if(_HT<300) db+= "Iso";
  // // else
  //   db += "NIso";
  db+= "Iso";

  if(_vc->get("isData")!=1) db +="MC";


  if(isInUncProc() && getUncName()=="ewk_fr" && getUncDir()==SystUtils::kUp ) db+="Up";
  if(isInUncProc() && getUncName()=="ewk_fr" && getUncDir()==SystUtils::kDown ) db+="Do";

  float ptVal=cand->pt();
  float etaVal=std::abs(cand->eta());

  int wp=SusyModule::kTight;

  ptVal=std::max(_susyMod->conePt(idx,wp), (double)ptM);
  //if(_FR.find("J")!=string::npos) ptVal/=_vc->get("LepGood_jetPtRatiov2", idx);

  ptVal=std::max(ptVal, ptM);

  //return max((float)0.,_dbm->getDBValue(db+type, std::min( ptVal,(float)69.9),
  //std::min(etaVal,(float)((std::abs(cand->pdgId())==11)?2.49:2.39) ) ) );

  float fr =(std::abs(cand->pdgId())==13)?muonFakeRate(ptVal,etaVal):electronFakeRate(ptVal,etaVal);
  if(type!="") {
    fr=_dbm->getDBValue(db+type, std::min( ptVal,(float)69.9),std::min(etaVal,(float)((std::abs(cand->pdgId())==11)?2.49:2.39) ) );
  }

  return fr; 
}

bool
ChargeFlipAnalyzer::isPrompt() {

  if(_vc->get("isData")==1) return false;

  if( _vc->get("LepGood_mcUCSXMatchId",0)<=1 &&
      _vc->get("LepGood_mcUCSXMatchId",1)<=1 ) return true;
  else return false;
  
}



// bool
// ChargeFlipAnalyzer::passMultiLine(bool doubleOnly) {
//   //return true;
//   for(size_t ih=0;ih<_hltLines.size();ih++) {
//     if( (doubleOnly && ih==0) || (!doubleOnly && ih==1)) continue;
//     if(passHLLine(_hltLines[ih])) return true;
//   }

//   return false;
// }


bool
ChargeFlipAnalyzer::passHLLine(string line) {
  if(_vc->get(line)) return true;
  else return false;
}


void 
ChargeFlipAnalyzer::skimming(const string& type, vector<Candidate*> leps,
			     vector<int> idLeps, vector<Candidate*> fakables,
			     vector<int> idFakables, int& aux, int& IS, float& mZ, float& weight ) {

  //if(leps.size() && !=2) return;
  mZ=-1;
  Candidate* z=nullptr;
  if(leps.size()==2) {
    aux=1;
    z=Candidate::create(leps[0],leps[1]);
  }
  else if(leps.size()==0) {
    aux=0;
    float fr1=getFR(fakables[0],idFakables[0], type);
    float fr2=getFR(fakables[1],idFakables[1], type);
    weight*=fr1/(1-fr1)*fr2/(1-fr2);
    z=Candidate::create(fakables[0],fakables[1]);
  }
  else {
    aux=0;
    float fr=getFR(fakables[0],idFakables[0], type);
    weight*=fr/(1-fr);
    z=Candidate::create(leps[0],fakables[0]); 
  }
  if(z!=nullptr)
    mZ=z->mass();
  
}



void
ChargeFlipAnalyzer::fillChargeFlipPlots(const string& type, vector<Candidate*> leps,
					vector<int> idLeps) {

  if(leps.size()!=2) return;

  Candidate* z=Candidate::create(leps[0],leps[1]);
  if(z->mass()<60 || z->mass() > 120) return;
  

  //cout<<type<<"\t"<<z->mass()<<"  "<<leps[0]->pt()<<"  "<<leps[1]->pt()<<endl;

  if(leps[0]->charge()==leps[1]->charge() ) {
    setWorkflow(0);
    
    if(!_vc->get("isData") && (_vc->get("LepGood_mcUCSXMatchId",idLeps[0])!=1 && 
			       _vc->get("LepGood_mcUCSXMatchId",idLeps[1])!=1 ) ) return;

    
    fill("l1Pt"+type, leps[0]->pt() , _weight);
    fill("l1Eta"+type, leps[0]->eta() , _weight);
    fill("l1Phi"+type, leps[0]->phi() , _weight);

    fill("l2Pt"+type, leps[1]->pt() , _weight);
    fill("l2Eta"+type, leps[1]->eta() , _weight);
    fill("l2Phi"+type, leps[1]->phi() , _weight);

    fill("nVert"+type, _vc->get("nVert") , _weight);
    fill("MetPt"+type, _vc->get("met_pt") , _weight);
    fill("nJets"+type, _vc->get("nJet") , _weight);

    fill("mass"+type, z->mass() , _weight);
  } else {
    setWorkflow(1);

    if(!_vc->get("isData") && (_vc->get("LepGood_mcUCSXMatchId",idLeps[0])!=0 || 
			       _vc->get("LepGood_mcUCSXMatchId",idLeps[1])!=0 ) ) return;

    float p1=_dbm->getDBValue("fliprate"+type, _vc->get("LepGood_pt",idLeps[0]), std::abs(leps[0]->eta()) );
    float p2=_dbm->getDBValue("fliprate"+type, _vc->get("LepGood_pt",idLeps[1]), std::abs(leps[1]->eta()) );
      
    if(p1>0.01) p1=0.0005;
    if(p2>0.01) p2=0.0005;
    float p=(p1+p2-2*p1*p2)/(p1*p2+(1-p1)*(1-p2) );
    //cout<<" ---->>>> "<<p1<<"  "<<p2<<"  "<<p<<endl;
    
    fill("l1Pt"+type, leps[0]->pt() , _weight*p);
    fill("l1Eta"+type, leps[0]->eta() , _weight*p);
    fill("l1Phi"+type, leps[0]->phi() , _weight*p);

    fill("l2Pt"+type, leps[1]->pt() , _weight*p);
    fill("l2Eta"+type, leps[1]->eta() , _weight*p);
    fill("l2Phi"+type, leps[1]->phi() , _weight*p);

    fill("nVert"+type, _vc->get("nVert") , _weight*p);
    fill("MetPt"+type, _vc->get("met_pt") , _weight*p);
    fill("nJets"+type, _vc->get("nJet") , _weight*p);

    fill("mass"+type, z->mass() , _weight*p);
  }

  setWorkflow(0);
  if(_vc->get("isData")) return;
  int cc1=_vc->get("LepGood_mcUCSXMatchId",idLeps[0]) ;
  if(cc1==0) {
    fill("GenChPrtEl"+type,_vc->get("LepGood_pt",idLeps[0]),
	 std::abs(_vc->get("LepGood_eta",idLeps[0])), _weight);
  } else if(cc1==1) {
    fill("GenChMidEl"+type,_vc->get("LepGood_pt",idLeps[0]),
	 std::abs(_vc->get("LepGood_eta",idLeps[0])), _weight);
  }
  cc1=_vc->get("LepGood_mcUCSXMatchId",idLeps[1]) ;
  if(cc1==0) {
    fill("GenChPrtEl"+type,_vc->get("LepGood_pt",idLeps[1]),
	 std::abs(_vc->get("LepGood_eta",idLeps[1])), _weight);
  } else if(cc1==1) {
    fill("GenChMidEl"+type,_vc->get("LepGood_pt",idLeps[1]), std::abs(_vc->get("LepGood_eta",idLeps[1])), _weight);
  }
  
    
}


float 
ChargeFlipAnalyzer::electronFakeRate(float pt, float eta) {
   if (pt>=10 && pt<15 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.213109;
   if (pt>=10 && pt<15 && std::abs(eta)>=0.8 && std::abs(eta)<1.479 ) return 0.191284;
   if (pt>=10 && pt<15 && std::abs(eta)>=1.479 && std::abs(eta)<2.5 ) return 0.114628;
   if (pt>=15 && pt<25 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.0601667;
   if (pt>=15 && pt<25 && std::abs(eta)>=0.8 && std::abs(eta)<1.479 ) return 0.0588169;
   if (pt>=15 && pt<25 && std::abs(eta)>=1.479 && std::abs(eta)<2.5 ) return 0.0488661;
   if (pt>=25 && pt<35 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.0508101;
   if (pt>=25 && pt<35 && std::abs(eta)>=0.8 && std::abs(eta)<1.479 ) return 0.0558932;
   if (pt>=25 && pt<35 && std::abs(eta)>=1.479 && std::abs(eta)<2.5 ) return 0.0557031;
   if (pt>=35 && pt<50 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.0632371;
   if (pt>=35 && pt<50 && std::abs(eta)>=0.8 && std::abs(eta)<1.479 ) return 0.0720639;
   if (pt>=35 && pt<50 && std::abs(eta)>=1.479 && std::abs(eta)<2.5 ) return 0.0708515;
   if (pt>=50 && std::abs(eta)>=0 && std::abs(eta)<0.8 ) return 0.141916;
   if (pt>=50 && std::abs(eta)>=0.8 && std::abs(eta)<1.479 ) return 0.132915;
   if (pt>=50 && std::abs(eta)>=1.479 && std::abs(eta)<2.5 ) return 0.144344;
   return 0.;
}




float 
ChargeFlipAnalyzer::muonFakeRate(float pt, float eta) {
   if (pt>=10 && pt<15 && std::abs(eta)>=0 && std::abs(eta)<1.2 ) return 0.30318;
   if (pt>=10 && pt<15 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.357706;
   if (pt>=10 && pt<15 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.379742;
   if (pt>=15 && pt<25 && std::abs(eta)>=0 && std::abs(eta)<1.2 ) return 0.0712294;
   if (pt>=15 && pt<25 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.0774284;
   if (pt>=15 && pt<25 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.08627;
   if (pt>=25 && pt<35 && std::abs(eta)>=0 && std::abs(eta)<1.2 ) return 0.0423947;
   if (pt>=25 && pt<35 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.0449793;
   if (pt>=25 && pt<35 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.0509235;
   if (pt>=35 && pt<50 && std::abs(eta)>=0 && std::abs(eta)<1.2 ) return 0.0439154;
   if (pt>=35 && pt<50 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.0426292;
   if (pt>=35 && pt<50 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.0417188;
   if (pt>=50 && std::abs(eta)>=0 && std::abs(eta)<1.2 ) return 0.0604471;
   if (pt>=50 && std::abs(eta)>=1.2 && std::abs(eta)<2.1 ) return 0.0540926;
   if (pt>=50 && std::abs(eta)>=2.1 && std::abs(eta)<2.4 ) return 0.0120945;
   return 0.;
}
