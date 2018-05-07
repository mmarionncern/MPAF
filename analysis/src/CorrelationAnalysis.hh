#ifndef CorrelationAnalysis_HH
#define CorrelationAnalysis_HH

#include "analysis/core/MPAF.hh"

struct CorVar{

  vector<float> x;
  vector<float> y;
  vector<float> w;
  //int n;

  CorVar(){
    // x=0;
    // y=0;
    // //n=0;
  };

  void addEntry(float valx, float valy, float valw=1) {
    x.push_back(valx);
    y.push_back(valy);
    w.push_back(valw);
    //n+=1;
  }

  float getCorCoef() {

    if(x.size()==0) return -100;
    float sdevx=StatUtils::standardDeviation(x);
    float sdevy=StatUtils::standardDeviation(y);
    float covxy=StatUtils::covariance(x,y);
    if(sdevx==0 || sdevy==0) return -100; //dirac case, unphysical
    return covxy/(sdevx*sdevy);
    
  }
  
};


class CorrelationAnalysis: public MPAF {

public:

  // Member Functions
  
  CorrelationAnalysis(std::string);
  virtual ~CorrelationAnalysis();


private:

  void initialize();

  void defineOutput() ;
  void modifyWeight() {};
  void writeOutput();
  
  void modifySkimming() {};

  void run();

private:

  vector<pair<string, string> > _correlations;
  map<string,CorVar> _corVars;
  set<string> _allVars;
  vector<string> _vars;

  vector<int> getIds(string name);
  int getSize(string name);
  float get(string name, int idx);
  vector<string> getFullCompo(const string& str);
  
};

#endif
