#include "analysis/src/DoubleCounterChecker.hh"

#include <algorithm>

DoubleCounterChecker::DoubleCounterChecker(std::string cfg){
  
  //startExecution(cfg);
  initialize();

}

DoubleCounterChecker::~DoubleCounterChecker(){
 
}

void
DoubleCounterChecker::initialize(){

 _vc->registerVar("run");
 _vc->registerVar("lumi");
 _vc->registerVar("evt");
}

void
DoubleCounterChecker::modifyWeight() {

}

void
DoubleCounterChecker::modifySkimming() {

}


void
DoubleCounterChecker::defineOutput() {

}


void
DoubleCounterChecker::writeOutput() {
 
}


void
DoubleCounterChecker::run() {

  //manual doublecounting protection
  if( _sampleName.find("Run2016D_PromptReco_v2_runs_276284_276811")!=string::npos && _vc->get("run")<=276384) return;


  unsigned long event=_vc->get("evt");
  int run=_vc->get("run");
  int lumi=_vc->get("lumi");

  _it=_runs.find(run);
  if(_it==_runs.end()) {
    _runs[ run ][std::make_pair(lumi, event)]=true;
    return;
  }

  _itM=_it->second.find(std::make_pair(lumi, event));
  if(_itM==_it->second.end()) {
    _it->second[ std::make_pair(lumi, event) ]=true;
  }
  else {
    //    if(_sampleName!="SingleMuon_Run2016B_PromptReco_v2_runs_271350_275783")
      cout<<_sampleName<<"\t"<<run<<"\t"<<lumi<<"\t"<<event<<endl;
  }

}
