#ifndef DoubleCounterChecker_HH
#define DoubleCounterChecker_HH

#include "analysis/core/MPAF.hh"

class DoubleCounterChecker: public MPAF {

public:

  // Member Functions

  DoubleCounterChecker(std::string);
  virtual ~DoubleCounterChecker();


private:

  void initialize();

  void run();
  void defineOutput();
  void modifyWeight();
  void writeOutput();

  void modifySkimming();


private: 

  //counter categories, 0 is ALWAYS global (even if not specified later
  enum {kGlobal=0};
  
  std::map<int, std::map<std::pair<int,unsigned long>, bool > > _runs;
  std::map<int, std::map<std::pair<int,unsigned long>, bool > >::iterator _it;
  std::map<std::pair<int,unsigned long>, bool >::iterator _itM;


};


#endif
