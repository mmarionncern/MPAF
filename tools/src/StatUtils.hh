#ifndef _StatUtils_
#define _StatUtils_


#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>

#include "TH1.h"
#include "TMath.h"
#include "TRandom3.h"

extern TRandom3 _rnd;

using namespace std;


class StatUtils {

public :

  static float standardDeviation(const vector<float>& x);
  static float covariance(const vector<float>& x, const vector<float>& y);

  static float normalizeVariable(float x, float min, float max, float minT=0, float maxT=1);
  
  static float BinomError(float Nt, double eff);
  
  static void ComputeStatFromHisto(TH1* histo, double& Em, double& EM, double& M);

  static void Get90PCInterval(TH1* histo, double& range0, double& range1);
  static TH1* Get90HistoInterval(TH1* histo);

  static float Kurt(vector<double>,double mean , double sigma);
  static void KolmogorovTest(TH1* MC, TH1* data, string observable);
  static float Poisson(float mc, int data);
  static void Chi2Test(TH1* MC, TH1* data);
  
  static float ErrorPL(int N, int sigma=1);
  static float ErrorPH(int N, int sigma=1);

  // static float LnL(float si, float bi, int ni, int NData, float a);
  // static float Chi2(float si, float bi, int ni, int NData, float a);
  static float Fact(int x);

  static void Integral(TH1* mc, TH1* data, double xmin, double xmax);

  static float retrieveNumEvents(float y, float ye);

  static float PoissonYield(float y);
  
  template < typename T > static inline
  unsigned int findBin(T v, vector<T> vals) {
    bool find=false;
    
    size_t bm=0;
    size_t bM=vals.size()-1;
    //cout<<v<<"   "<<bm<<"    "<<bM<<"     "<<vals[bm]<<"    "<<vals[bM]<<endl;
    if(v< vals[ bm ]) return -1;
    if(v>= vals[ bM ]) return vals.size();
    size_t n=0;
    while(!find) {
      if(v < vals[ bm+(bM-bm)/2 ] ) {
	bM = bm+(bM-bm)/2;
      }
      else {
	bm = bm+(bM-bm)/2;
      }
      
	if( std::abs((int)(bM-bm))==1 )  {
	return bm;
      }
   
      if(n>(size_t)vals.size()) return -1;
      n++;
    }
    return -1;
  };

  
  template <typename T> static inline
  int findInVector(T v, vector<T> vals) {
    for(size_t i=0;i<vals.size();i++){
      if( v==vals[i] ) return i;
    }
    return -1;
  };

  template <typename T> static inline
  T max(vector<T> vals) {
    if(vals.size()==0) return 0;
    T max=-10000000;
    for(size_t i=0;i<vals.size();i++){
      if(vals[i]>max) max=vals[i];
    }
    return max;
  };

  template <typename T> static inline
  T min(vector<T> vals) {
    if(vals.size()==0) return 0;
    T min=100000000;
    for(size_t i=0;i<vals.size();i++){
      if(vals[i]<min) min=vals[i];
    }
    return min;
  };

  
  ClassDef(StatUtils,0)

}; 


#endif
