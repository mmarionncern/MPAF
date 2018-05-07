#ifndef Skimmer_HH
#define Skimmer_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

class Skimmer: public MPAF {

public:

  // Member Functions

  Skimmer(std::string);
  virtual ~Skimmer();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();

  void modifySkimming();

  void makeCandList(const string& coll, CandList& list);

private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0};
  
  CandList _leps;
  CandList _tausG;
  CandList _tausO;
  CandList _jets;
  CandList _djets;

  std::map<int, std::map<std::pair<int, unsigned long>, bool > > _eventsskip;
  std::map<int, std::map<std::pair<int, unsigned long>, bool > >::const_iterator _it;
  std::map<std::pair<int, unsigned long>, bool >::const_iterator _itM;

  float _mZ;
  bool _anSkim;

  SusyModule* _susyMod;

};


#endif
