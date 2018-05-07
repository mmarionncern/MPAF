#ifndef TreeConverter_HH
#define TreeConverter_HH

#include "analysis/core/MPAF.hh"

class TreeConverter: public MPAF {

public:

  // Member Functions
  
  TreeConverter(std::string);
  virtual ~TreeConverter();


private:

  void initialize();

  void defineOutput() {};
  void modifyWeight() {};
  void writeOutput() {};
  
  void modifySkimming();

  void run();
  
  void convertVectorToArray();
  void convertArrayToVector();

  void initVectorToArray();
  void initArrayToVector();
  
  

private:

  bool _vectorToArray;
  
  vector<string> _branchesToKeep;
  vector<string> _stdBranches;
  map<string, unsigned int> _sizeBranches;
  map<string, unsigned int>::const_iterator _it;

  bool _maxFound;
  bool _init;

  //==============================================
  map<string, int*> _aBranchesI;
  map<string, float*> _aBranchesF;
  map<string, double*> _aBranchesD;
  map<string, bool*> _aBranchesB;

  map<string, int*>::const_iterator _itI;
  map<string, float*>::const_iterator _itF;
  map<string, double*>::const_iterator _itD;
  map<string, bool*>::const_iterator _itB;

  //==============================================
  map<string, vector<int> > _vBranchesI;
  map<string, vector<float> > _vBranchesF;
  map<string, vector<double> > _vBranchesD;
  map<string, vector<bool> > _vBranchesB;
  
  map<string, vector<int> >::const_iterator _itVI;
  map<string, vector<float> >::const_iterator _itVF;
  map<string, vector<double> >::const_iterator _itVD;
  map<string, vector<bool> >::const_iterator _itVB;
  
};

#endif
