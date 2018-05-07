#include "analysis/src/Skimmer.hh"

#include <algorithm>

Skimmer::Skimmer(std::string cfg){
  
  //startExecution(cfg);
 

  // ifstream ifile("/mnt/t3nfs01/data01/shome/mmarionn/MPAF/eventDumpTaus.txt", ios::in);
  
  // if(ifile) {
  //   string line;
  //   while(getline(ifile, line)) {
  //     istringstream iss(line);
  //     vector<string> tks;
  //     copy(istream_iterator<string>(iss),
  // 	   istream_iterator<string>(),
  // 	   back_inserter<vector<string> >(tks));
   
  //     // cout<<":"<<line<<":"<<endl;
      
  //     int run = atoi(tks[0].c_str());
  //     int lumi = atoi(tks[1].c_str());
  //     unsigned long event = ((unsigned)atol(tks[2].c_str() ));

  //     _eventsskip[run][std::make_pair(lumi,event)]=true;
  //   }
  // }

  _anSkim=(bool)(getCfgVarI("AnalysisSkim",1));
  _susyMod=new SusyModule(_vc);
  
  initialize();
}

Skimmer::~Skimmer(){
 
}

void
Skimmer::initialize(){

 _vc->registerVar("nLepGood");
 _vc->registerVar("LepGood_pdgId");
 _vc->registerVar("LepGood_pt");
 _vc->registerVar("LepGood_eta");
 _vc->registerVar("LepGood_phi");
 _vc->registerVar("LepGood_charge");
 _vc->registerVar("LepGood_tightCharge"          );
 _vc->registerVar("LepGood_mvaIdSpring15"        );
 _vc->registerVar("LepGood_pdgId"                );
 _vc->registerVar("LepGood_relIso03"             );
 _vc->registerVar("LepGood_relIso04"             );
 _vc->registerVar("LepGood_etaSc"                );
 _vc->registerVar("LepGood_energySc"             );
 _vc->registerVar("LepGood_jetPtRatiov2"         );
 _vc->registerVar("LepGood_jetPtRelv2"           );
 _vc->registerVar("LepGood_jetBTagCSV"           );
 _vc->registerVar("LepGood_jetRawPt"             );
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

 if(_anSkim) {
   _vc->registerVar("nTauGood");
   _vc->registerVar("TauGood_pt");
   _vc->registerVar("TauGood_eta");
   _vc->registerVar("TauGood_phi");
 
   _vc->registerVar("nTauOther");
   _vc->registerVar("TauOther_pt");
   _vc->registerVar("TauOther_eta");
   _vc->registerVar("TauOther_phi");
 
 
   _vc->registerVar("Jet_jecDown_pt");
   _vc->registerVar("Jet_jecUp_pt");
   _vc->registerVar("Jet_btagCSV");
 
   _vc->registerVar("DiscJet_jecDown_pt");
   _vc->registerVar("DiscJet_jecUp_pt");
   _vc->registerVar("DiscJet_btagCSV");
 
   _vc->registerVar("met_pt");
   _vc->registerVar("met_jecDown_pt");
   _vc->registerVar("met_jecUp_pt");
 }

 _vc->registerVar("lumi");
 _vc->registerVar("run");
 _vc->registerVar("evt");
 _vc->registerVar("nTrueInt");
 _vc->registerVar("nVtx");


 //triggers
 vector<string> prescaleHLT({"HLT_FR_Ele8_CaloIdM_TrackIdM_PFJet30",
       "HLT_FR_Ele17_CaloIdM_TrackIdM_PFJet30",
       "HLT_FR_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30",
       "HLT_FR_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30",
       "HLT_FR_Mu8",
       "HLT_FR_Mu17",
       "HLT_FR_Mu8_TrkIsoVVL",
       "HLT_FR_Mu17_TrkIsoVVL"});
 // _prescaleHLTs=prescaleHLT;

 for(unsigned int i=0;i<prescaleHLT.size();i++) {
   _vc->registerVar(prescaleHLT[i]);
 }


}

void
Skimmer::modifyWeight() {

}

void
Skimmer::modifySkimming() {
  if(!_anSkim) {
    addSkimBranch<float>("mZ",&_mZ);
  }
}


void
Skimmer::defineOutput() {

}


void
Skimmer::writeOutput() {
 
}


void
Skimmer::run() {
  
  _leps.clear();
  _tausG.clear();
  _tausO.clear();
  _jets.clear();
  _djets.clear();

  
  // if(!_anSkim) {
  //   makeCandList("LepGood", _leps );
  //   if(_leps.size()!=2) return;
  //   Candidate* z=Candidate::create(_leps[0],_leps[1]);
  //   _mZ=z->mass();
  //   if(_mZ<50 || _mZ > 130) return;
  //   fillSkimTree();
  //   return;
  // }

  int run=_vc->get("run");
  int lumi=_vc->get("lumi");
  unsigned long event=_vc->get("evt");
  _it=_eventsskip.find(run);
  if(_it!=_eventsskip.end() ) {
    _itM=_it->second.find(std::make_pair(lumi,event));
    if(_itM!=_it->second.end()) { 
      //cout<<"rejecting event "<<run<<"  "<<lumi<<"  "<<event<<endl;
      return;
    }
    else {
      _eventsskip[run][std::make_pair(lumi,event)]=true;
    }
  } else {
    _eventsskip[run][std::make_pair(lumi,event)]=true;
  }
  //cout<<run<<"\t"<<lumi<<"\t"<<event<<endl;
  fillSkimTree(); 
  return;


  makeCandList("LepGood", _leps );
  makeCandList("TauGood", _tausG );
  makeCandList("TauOther", _tausO );
  makeCandList("Jet", _jets );
  makeCandList("DiscJet", _djets );
  




  //cout<<_leps.size()<<"  "<<(_tausG.size()+_tausO.size())<<"  "<<(_jets.size()+_djets.size())<<" / "<<(_vc->get("met_pt"))<<"  "<<_vc->get("met_jecDown_pt")<<"  "<<_vc->get("met_jecUp_pt")<<endl;

  if(_leps.size()>=3) {
    fillSkimTree(); 
    return;
  }
  // if(_leps.size()==1) {
  //   bool preHLT=firePrescaleHLT(_leps[0]->pdgId());
  //   if(preHLT) { fillSkimTree(); return; }
  // }

  else if(  (  (_leps.size()>=1 && ((_tausG.size()+_tausO.size())>=1)) || _leps.size()>=2) &&
	  (_vc->get("met_pt")>35 || _vc->get("met_jecDown_pt")>35 || 
	   _vc->get("met_jecUp_pt")>35) && ( (_jets.size()+_djets.size())<=1 ) ) {
    fillSkimTree();
  }

}

void
Skimmer::makeCandList(const string& coll, CandList& list) {

  size_t nLep=_vc->get("n"+coll);
  for(size_t il=0;il<nLep;il++) {
    Candidate* obj=Candidate::create(KineUtils::et(_vc->get(coll+"_energySc", il),_vc->get(coll+"_etaSc", il)),
				     _vc->get(coll+"_etaSc", il),
				     _vc->get(coll+"_phi", il) );

    if(coll.find("Tau")!=string::npos) {
      bool unclean=false;
      for(size_t ill=0;ill<_leps.size();ill++) {
	if(obj->dR(_leps[ill])<0.4) {
	  unclean=true;
	  break;
	}
      }
      if(unclean) continue;
    } else if(coll.find("Jet")!=string::npos) {

      if(std::abs(obj->eta())>2.4) continue;
      if(obj->pt()<25 && _vc->get(coll+"_jecDown_pt", il)<25 && _vc->get(coll+"_jecUp_pt", il)<25 ) continue;
      if(_vc->get(coll+"_btagCSV",il)<0.935 ) continue;

    } else {
      if(_vc->get(coll+"_pt", il)<10) continue;
      if(!_anSkim && std::abs(_vc->get(coll+"_pdgId",il) ) ) {
	  if(!_susyMod->elIdSel(obj, il, SusyModule::kTight, SusyModule::kTight) ) continue;
	  if(!_susyMod->multiIsoSel(il, SusyModule::kTight) ) continue;
	  if(!_susyMod->elHLTEmulSel(il, false ) ) continue;
	}

    }

    list.push_back(obj);
  }
  
}

// void
// Skimmer::firePrescaleHLT() {
  
//   for(unsigned int i=0;i<_prescaleHLTs.size();i++) {
//     if(_vc->get(prescaleHLTs[i]) ) return true;
//   }

//   return false;
// }
