#ifndef Comissioning_HH
#define Comissioning_HH

#include "analysis/core/MPAF.hh"

#include "analysis/modules/SusyModule.hh"

class Comissioning: public MPAF {

public:

  // Member Functions

  Comissioning(std::string);
  virtual ~Comissioning();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();

  void modifySkimming();


  void selectObjects();

  bool passHLLine(string line);
  bool passMultiLine(bool doubleOnly);

  void computeL1NC();
  void buildCategs();
  string getCateg(bool OS, float pt1, float pt2, float eta1, float eta2, float mass);
  
  int isGenChMisId(const Candidate* c);

  bool tightLepton(const Candidate*c, int idx, int pdgId);

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0, kElSel};
 

  CandList _leptons;
  CandList _jets;

  vector<int> _leptonsIdx;
  vector<int> _jetsIdxs;
  
  Candidate* _met;
  Candidate* _metNoHF;

  vector<float> _elMvaIdWP;

  vector<std::string> _hltLines;


  float _mass, _channel, _charge, _fidu, _puW;
  vector<float> _L1NC;
  bool _isData;
  vector<int> _jetMatch;
  vector<bool> _lepMatch;


  vector<float> _binsPt;
  vector<float> _binsEta;
  //vector<std::string> _categs;
  map<string,float> _categs;
  int _categ;

  SusyModule* _susyMod;

};


#endif
