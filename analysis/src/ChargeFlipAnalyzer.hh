#ifndef ChargeFlipAnalyzer_HH
#define ChargeFlipAnalyzer_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

class ChargeFlipAnalyzer: public MPAF {

public:

  // Member Functions

  ChargeFlipAnalyzer(std::string);
  virtual ~ChargeFlipAnalyzer();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();

  void modifySkimming();

  void makeCandList(const string& coll, CandList& list, vector<int>& idxs, 
		    CandList& listFake, vector<int>& idxsFake, const string& type);
  float getFR(Candidate* cand, int idx, const string& type);

  bool isPrompt();
  bool passHLLine(string line);

  void skimming(const string& type, vector<Candidate*> leps,
		vector<int> idLeps, vector<Candidate*> fakables,
		vector<int> idFakables, int& aux, int& IS, float& mZ, float& weight );
  void fillChargeFlipPlots(const string& type, vector<Candidate*> leps, vector<int> idLeps);

  float electronFakeRate(float pt, float eta);
  float muonFakeRate(float pt, float eta);

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0};
  
  CandList _leps;
  CandList _fakables;
  vector<int> _idFakables;
  vector<int> _idLeps;
  
  CandList _lepsMVAM;
  CandList _fakablesMVAM;
  vector<int> _idFakablesMVAM;
  vector<int> _idLepsMVAM;

  CandList _lepsMVAVT;
  CandList _fakablesMVAVT;
  vector<int> _idFakablesMVAVT;
  vector<int> _idLepsMVAVT;

  std::map<int, std::map<std::pair<int, unsigned long>, bool > > _eventsskip;
  std::map<int, std::map<std::pair<int, unsigned long>, bool > >::const_iterator _it;
  std::map<std::pair<int, unsigned long>, bool >::const_iterator _itM;

  float _mZ;
  float _weight;
  int _aux;
  int _IS;

  float _mZMVAM;
  float _weightMVAM;
  int _auxMVAM;
  int _ISMVAM;

  float _mZMVAVT;
  float _weightMVAVT;
  int _auxMVAVT;
  int _ISMVAVT;


  SusyModule* _susyMod;

  bool _valid;

  vector<float> _binsPt;
  vector<float> _binsEta;

};


#endif
