#ifndef _Format_
#define _Format_

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "TH1.h"
#include <TLorentzVector.h>

struct hObs {

  std::vector<TH1*> hs;
  
  int nBX;
  int nBY;
  std::vector<float> binsX;
  std::vector<float> binsY;
  
  std::string htype;
  
  std::string titleX;
  std::string titleY;
  std::string name;
  std::string type;
  
  bool IsGlobal() const { return isglb; };
  void SetGlobal(bool glb) { isglb = glb; }; 

  bool isRelevant(std::string iWF) const {
    if(allowedWFs.size()==0) return true;
    std::set<std::string>::const_iterator it=allowedWFs.find(iWF);
    if(it != allowedWFs.end() ) return true;
    return false;
  };
  bool isRelevantUnc(const std::string& type) const {
    if(allowedUncs.size()==0) return true;
    std::set<std::string>::const_iterator it=allowedUncs.find(type);
    if(it != allowedUncs.end() ) return true;
    return false;
  };

  void setRelevantWFs(std::vector<std::string> wfs) {
    for(size_t i=0;i<wfs.size();i++)
      allowedWFs.insert(wfs[i]);
  };
  void setRelevantUncs(std::vector<std::string> uncs) {
    for(size_t i=0;i<uncs.size();i++)
      allowedUncs.insert(uncs[i]);
  };

  void setRelevantWFs(std::set<std::string> wfs) {
    allowedWFs=wfs;
  };
  void setRelevantUncs(std::set<std::string> uncs) {
    allowedUncs=uncs;
  };

  const hObs* clone(const std::string& id) const {
    hObs* newObs=new hObs();
    newObs->nBX=nBX;
    newObs->nBY=nBY;
    newObs->binsX=binsX;
    newObs->binsY=binsY;
    newObs->htype=htype;
    newObs->titleX=titleX;
    newObs->titleY=titleY;
    newObs->name=name;
    newObs->type=type;
    newObs->SetGlobal(isglb);
    newObs->setRelevantWFs(allowedWFs);
    newObs->setRelevantUncs(allowedUncs);

    for(size_t ih=0;ih<hs.size();ih++) {
      newObs->hs.push_back( (TH1*)hs[ih]->Clone( ((std::string)(hs[ih]->GetName())+id).c_str() ) );
    }
    return newObs;
  };

private: 
  bool isglb;
  std::set<std::string> allowedWFs;
  std::set<std::string> allowedUncs;

};

typedef std::map<std::string,TH1*> systM;
typedef std::map<std::string,TH1*>::iterator itSystM;
typedef std::map<std::string,TH1*>::const_iterator citSystM;

typedef std::map<std::string,std::pair<std::string,std::vector<std::vector<float> > > > fitM;
typedef std::map<std::string,std::pair<std::string,std::vector<std::vector<float> > > >::iterator itFitM;
typedef std::map<std::string,std::pair<std::string,std::vector<std::vector<float> > > >::const_iterator citFitM;

//uncNames / dataset / yields
typedef std::map<std::string, std::map<std::string,std::vector<float> > > shapeM; 
typedef std::map<std::string, std::map<std::string,std::vector<float> > >::const_iterator itShapeM;

struct SystST{

   std::string type; //+ * %
   float val; //variation
   std::string db; //database name
   int dir; //direction
   std::vector<std::string> vars; //input dependencies
   std::vector<bool> specVars; //absolute value modifier
   std::vector<std::string> modVar; //variables to be modified

};


struct SampleId{
  
  std::string name;
  std::string cr;
  bool dd;
  bool isData;
  float norm;

};

#endif
