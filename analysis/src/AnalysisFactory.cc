#include "analysis/src/AnalysisFactory.hh"

using namespace std;

//list of analyzers and modules in alphabetical order
#include "analysis/src/FakeRatio.hh"
#include "analysis/src/FakeRatioV3.hh"
#include "analysis/src/UncertaintyTest.hh"
#include "analysis/src/DoubleCounterChecker.hh"
#include "analysis/src/Skimmer.hh"
#include "analysis/src/TTVAnalysis.hh"
#include "analysis/src/ChargeFlipAnalyzer.hh"
#include "analysis/src/TreeConverter.hh"
#include "analysis/src/CorrelationAnalysis.hh"
//#include "analysis/src/Comissioning.hh"

MPAF*
AnalysisFactory::get(const string& analysis, const string& cfg) {
 
// list of analyzers and modules in alphabetical order 
  
  if(analysis=="FakeRatio") {
    return new FakeRatio(cfg);
  }
 
 if(analysis=="FakeRatioV3") {
   return new FakeRatioV3(cfg);
 }
 
  if(analysis=="DoubleCounterChecker") {
    return new DoubleCounterChecker(cfg);
  }
  if(analysis=="Skimmer") {
    return new Skimmer(cfg);
  }
  if(analysis=="ChargeFlipAnalyzer") {
    return new ChargeFlipAnalyzer(cfg);
  }
  if(analysis=="TTVAnalysis") {
    return new TTVAnalysis(cfg);
  }
  if(analysis=="TreeConverter") {
    return new TreeConverter(cfg);
  }
  if(analysis=="CorrelationAnalysis") {
    return new CorrelationAnalysis(cfg);
  }
  
  // if(analysis=="UncertaintyTest") {
  //   return new UncertaintyTest(cfg);
  // }
  // if(analysis=="Comissioning") {
  //  return new Comissioning(cfg);
  // }
  return 0;
}
