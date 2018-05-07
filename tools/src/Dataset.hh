#ifndef _Dataset_
#define _Dataset_

#include <vector>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "TError.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TChain.h"
#include "TObject.h"
#include "TKey.h"
#include "TSystem.h"

#include "tools/src/Sample.hh"
#include "tools/src/Format.cc"
#include "tools/src/HistoUtils.hh"

class Dataset {

private:

  std::string _name;
  bool _isData;
 
  std::vector<Sample> _samples;
  vector<pair<int,int> > _events;
  std::vector<float> _weights;
  std::vector<int> _nprocs;
  std::map<int, std::vector<unsigned int> > _links;
  vector<string> _treelinks;

  int _color;
	
  //for tChain part
  TChain* _chain;
	
  //for histogram part
  std::map<std::string, std::map<std::string, TH1*> > _histos;
	
  int _isFromCS;
  bool _isGhost;
	
  int _dsContentType;
  std::vector<std::vector<std::string> > _friends;

  std::vector<string> _usefulVars;

  bool _isDataDriven;
  bool _isPoissonPseudo;

  int _totNProcEvents;
  float _totSumProxWgts;

public:

  enum {
    kTree = 0,
    kHisto
  };

  Dataset();
  Dataset(std::string name);
  Dataset(std::string name, int color);
	
  virtual ~Dataset();
	
  void freeMemory();

  void config(std::string name, int color, int content);
	
  void setName(std::string name){ _name=name;};
  void setColor(int ncol){ _color=ncol;};
	
  void addSample(SampleId sId, std::string path, std::string dir, std::string objName,
		 std::string hname, std::string hwgtname, float xSect,
		 float kFact, float lumi, float eqLumi, int link=-1, bool loadH=true,
		 bool isPoissonPseudo=false);

  void addFriend(std::vector<std::string> friendT);

  void setUsefulVars(std::vector<std::string> vars);

  //access functions 
  std::string getName() const { return _name;};
  int getColor() const { return _color;};
	
  bool isDataset(std::string name) const {return _name==name;};
  bool isPPcolDataset() const { return _isData;};

  int hasSample(string sname) const;
	
  bool isTreeType() const { return _dsContentType==kTree;};
  bool isHistoType() const { return _dsContentType==kHisto;};

  bool isPoissonPseudo() const {return _isPoissonPseudo;};
  bool isDataDriven() const {return _isDataDriven;};
  bool isFromCS() const {return _isFromCS!=0;};
  int csCode() const {return _isFromCS;};
	
  bool isGhost() const {return _isGhost;};
	
  float getWeight(int is) const {return _samples[is].getLumW(); };
  float getWeight(string sname) const;
	
  TTree* getTree() const {return _chain;};
  unsigned long int getNEvents() const { return _chain->GetEntries(); };
	
  void addLink(string linkname);
  int getTotNProcEvents() const;
  float getTotSumProcWgts() const;
  void setTotNProcEvents(string path, string dir, string subdir, string hwgtname);
  void setTotSumProcWgts(string path, string dir, string subdir, string hgwtname);
  int getNProcEvents() const {return _samples[0].getNProcEvts();};
  float getSumProcWgts() const {return _samples[0].getSumProcWgts();};

  std::vector<std::string> getSampleNames();
  std::vector<const Sample*> getSamples() const;
  std::vector<std::string> getObservables();
  TH1* getHisto( std::string varName, std::string sName);

  const Sample* getSample(string sname) const;
  

private:

  void loadTree(std::string path, std::string dir, string subdir, std::string sname, std::string objName);
  void loadHistos(std::string path, std::string dir, string subdir, std::string sname, std::string hname, std::string optCat);

  int getNProcEvents(string path, string dir, string subdir, string sname, string hname);
  double getSumProcWgts(string path, string dir, string subdir, string sname, string hwgtname);

  float getLinkedSumNProc(int link);
  float getLinkedSumWeightProc(int link);

  string getURL(const string& urlFile);

  public:
  static string goodPath(string path);
  static string goodAbsFilePath(string path, string dir, string fileName, string subdir = "data");
  static string goodURLFilePath(string path, string dir, string fileName, string subdir = "data");
  string goodFilePath(const string& path, const string& dir, const string& fileName, const string& subdir = "data");
  
  ClassDef(Dataset,0)
  
};

#endif
