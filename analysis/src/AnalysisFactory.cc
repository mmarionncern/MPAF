
#include "analysis/src/AnalysisFactory.hh"

using namespace std;

//list of analyzers and modules in alphabetical order
#include "analysis/src/csa14exerc.hh"
#include "analysis/src/SSDLBoosted.hh"
#include "analysis/src/FRClosure.hh"
#include "analysis/src/FRSimple.hh"
#include "analysis/src/ComputeFR.hh"
#include "analysis/src/synchECO.hh"
#include "analysis/src/synchRA5.hh"
#include "analysis/src/phys14limits.hh"
#include "analysis/src/FakeRatio.hh"
#include "analysis/src/FakeEstim.hh"
#include "analysis/src/UncertaintyTest.hh"

MPAF*
AnalysisFactory::get(const string& analysis, const string& cfg) {

  // list of analyzers and modules in alphabetical order
  if(analysis=="csa14exerc") {
    return new csa14exerc(cfg);
  }
  if(analysis=="SSDLBoosted") {
    return new SSDLBoosted(cfg);
  }
  if(analysis=="synchECO") {
    return new synchECO(cfg);
  }
  if(analysis=="synchRA5") {
    return new synchRA5(cfg);
  }
  if(analysis=="phys14limits") {
    return new phys14limits(cfg);
  }
  if(analysis=="FakeRatio") {
    return new FakeRatio(cfg);
  }
  if(analysis=="FakeEstim") {
    return new FakeEstim(cfg);
  }
  if(analysis=="ComputeFR") {
    return new ComputeFR(cfg);
  }
  if(analysis=="FRClosure") {
    return new FRClosure(cfg);
  }
  if(analysis=="FRSimple") {
    return new FRSimple(cfg);
  }
 if(analysis=="UncertaintyTest") {
    return new UncertaintyTest(cfg);
  }
  return 0;
}
