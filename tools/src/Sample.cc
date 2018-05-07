#include "src/Sample.hh"
#include <iostream>

using namespace std;

ClassImp(Sample)

Sample::Sample() {
}

Sample::Sample(SampleId sId,
	       int nPE, double sumPW, float xSect,
	       float kfact, float eqLumi) {

  _sId = sId;
  //_nEvents=n;
  _nProcEvents=nPE;
  _sumProcWgts=sumPW;
  
  _xSection=xSect;
  _kFactor=kfact;
  _eqLumi=eqLumi;

  _weight=1.;
  _linking=false;

  computeWeight();

}

Sample::~Sample() {
}


void
Sample::computeWeight() {
  //means that Xsection used for reweigthing instead of equivalentLumi
  // and means that the number of processed events is available
  
  if((_eqLumi==-1 || _linking) && _nProcEvents!=-1) {
    _linking=false;
    _eqLumi = _nProcEvents/_xSection;
    if(_sumProcWgts != -1) _eqLumi = _sumProcWgts/_xSection;
  }
  if(_nProcEvents==-1) _eqLumi=1; //avoid negative weights for already normalized yields, to be checked
 
  _weight =(1./_eqLumi)*_kFactor;
}
