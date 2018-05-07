/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, Matthieu Marionneau                                **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef __VC_
#define __VC_

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <TROOT.h>
#include <TLorentzVector.h>
#include <TBranch.h>
#include <TBranchSTL.h>
#include <TClass.h>
#include <TObjArray.h>
#include <TTree.h>
#include <TBits.h>
#include <TChain.h>
#include <TLeaf.h>
#include <TBranch.h>

#include "tools/src/SystUtils.hh"


using namespace std;

typedef map<int, vector<int>* > mapVI;
typedef map<int, vector<unsigned int>* > mapVUI;
typedef map<int, vector<unsigned long>* > mapVUL;
typedef map<int, vector<double>* > mapVD;
typedef map<int, vector<float>* > mapVF;
typedef map<int, vector<string>* > mapVS;
typedef map<int, vector<bool>* > mapVB;

typedef map<int, vector<int>* >::iterator itMapVI;
typedef map<int, vector<unsigned int>* >::iterator itMapVUI;
typedef map<int, vector<unsigned long>* >::iterator itMapVUL;
typedef map<int, vector<double>* >::iterator itMapVD;
typedef map<int, vector<float>* >::iterator itMapVF;
typedef map<int, vector<string>* >::iterator itMapVS;
typedef map<int, vector<bool>* >::iterator itMapVB;

typedef map<int, int* > mapAI; 
typedef map<int, unsigned int* > mapAUI; 
typedef map<int, unsigned long* > mapAUL; 
typedef map<int, double* > mapAD; 
typedef map<int, float* > mapAF; 
typedef map<int, string* > mapAS; 
typedef map<int, bool* > mapAB; 
 
typedef map<int, int* >::iterator itMapAI; 
typedef map<int, unsigned int* >::iterator itMapAUI; 
typedef map<int, unsigned long* >::iterator itMapAUL; 
typedef map<int, double* >::iterator itMapAD; 
typedef map<int, float* >::iterator itMapAF; 
typedef map<int, string* >::iterator itMapAS; 
typedef map<int, bool* >::iterator itMapAB;

typedef map<int, int > mapI;
typedef map<int, unsigned int > mapUI;
typedef map<int, unsigned long > mapUL;
typedef map<int, unsigned long long > mapUL64;
typedef map<int, double > mapD;
typedef map<int, float > mapF;
typedef map<int, bool > mapB;
typedef map<int, string > mapS;

typedef map<string, TBits* > mapTB;

typedef map<int, int >::iterator itMapI;
typedef map<int, unsigned int >::iterator itMapUI;
typedef map<int, unsigned long >::iterator itMapUL;
typedef map<int, unsigned long long >::iterator itMapUL64;
typedef map<int, double >::iterator itMapD;
typedef map<int, float >::iterator itMapF;
typedef map<int, bool >::iterator itMapB;
typedef map<int, string >::iterator itMapS;

typedef map<int, TBits* >::iterator itMapTB;




class VarClass {


  // Private Template Members

private:

  //____________________________________________________________________________
  template<typename T> inline vector<float> convertVal(T val) {
    /*
      converts a scalar of arbitrary type to a vetor of one float
      parameters: val (the scalar)
      return: the vector
    */

    vector<float> vf;
    vf.push_back((float) val);

    return vf;
  };


  //____________________________________________________________________________
  template<typename T> inline vector<float> convertVal(vector<T> vals) {
    /*
      converts a vector of arbitrary type to a vector of floats
      parameters: vals (the vector)
      return: vector of floats
    */

    vector<float> vf;

    for(size_t iv = 0; iv < vals.size(); ++iv)
      vf.push_back( (float) vals[iv] );

    return vf;
  };

  template<typename T> inline vector<float> convertVal(T* vals) {
    
    //vector<float> vf(vals, vals + sizeof(vals) / sizeof(vals[0]));
    vector<float> vf;
    int sa=sizeof(vals)/sizeof(vals[0]);
    for(int iv=0; iv<sa; ++iv) {
      vf.push_back( (float)vals[iv] );
    }

    return vf;
  };

 
  //____________________________________________________________________________
  template<typename T> inline void storeAccess(int mvar, map<int, T>& imap, map<int, T>& cmap) {
    /*
      adds a scalar variable mvar to the map cmap taking the values from imap, if it is 
      not already registered; if it is, it reinitializes the map cmap for new events,
      otherwise loads the value from cmap into imap
      parameters: mvar, imap, cmap
      return: none
    */
	
    typename map<int, T>::const_iterator it = cmap.find(mvar);
    if( it == cmap.end() ) { // variable not yet registered in the backup map	
      cmap[ mvar ] = imap[ mvar ];
    }
    else {   // variable already registered, reinitialization
      if(_nextEvent)
  	cmap[ mvar ] = imap[ mvar ];
      else
  	imap[ mvar ] = cmap[ mvar ];
    }
  };


  //____________________________________________________________________________
  template<typename T> inline void storeAccessV(int mvar, map<int, vector<T>* >& imap, map<int, vector<T>* >& cmap) {
    /*
      adds a vector variable mvar to a map cmap with values taken from imap if it is 
      not already registered; if it is, it reinitializes the vector in the map cmap 
      for new events, otherwise it reinitializes the map imap with values from cmap
      parameters: mvar (the variable), imap, cmap
      return: none
    */
	
    typename map<int, vector<T>* >::const_iterator it = cmap.find(mvar);
	
    if( it == cmap.end() ) {   // variable not yet registered in the backup map
      cmap[ mvar ] = new vector<T>;
      for(size_t ie = 0; ie < imap[mvar]->size(); ++ie) {
  	cmap[ mvar ]->push_back( imap[ mvar ]->at(ie) );
      }
    }
    else { // variable already registered, reinitialization 
      // vector reinitialization (for new events)
      if( _nextEvent ) {
	cmap[ mvar ]->resize( imap[mvar]->size() );
  	for(size_t ie = 0; ie < imap[mvar]->size(); ++ie)
  	  cmap[ mvar ]->at(ie) = imap[ mvar ]->at(ie);
      }
      else {
  	for(size_t ie = 0; ie < imap[mvar]->size(); ++ie) {
  	  imap[ mvar ]->at(ie) = cmap[ mvar ]->at(ie);
  	}
      }
    }
  };


  template<typename T> inline void storeAccessA(int mvar, map<int, T* >& imap, map<int, vector<T>* >& cmap) {
    
    typename map<int, vector<T>* >::const_iterator it = cmap.find(mvar);
	
    unsigned int as = sizeof(imap[mvar])/sizeof(imap[mvar][0]);

    if( it == cmap.end() ) {   // variable not yet registered in the backup map
      cmap[mvar] = new vector<T>;
      for(size_t ie=0;ie<as;++ie) {
  	cmap[mvar]->push_back( imap[mvar][ie] );
      }
    }
    else { // variable already registered, reinitialization 
      // vector reinitialization (for new events)
      if( _nextEvent ) {
	cmap[ mvar ]->resize( as );
  	for(size_t ie=0;ie<as;++ie)
  	  cmap[mvar]->at(ie) = imap[mvar][ie];
      }
      else {
  	for(size_t ie=0;ie<as;++ie) {
  	  imap[mvar][ie] = cmap[ mvar]->at(ie);
	}
      }
    }

  };


  //____________________________________________________________________________
  template<typename T> inline void multiReinit(map<int, T>& imap, map<int, T> cmap) {
    /*
      reinitializes a map (imap) of scalars with values from another map (cmap)
      parameters: imap, cmap
      return: none
    */

    typename map<int, T>::const_iterator it;
		
    for(it = cmap.begin(); it != cmap.end(); ++it)
      imap[ it->first ] = it->second;
		
  };


  // //____________________________________________________________________________
  template<typename T> inline void multiReinitV(map<int, vector<T>* >& imap, map<int, vector<T>* > cmap) {
    /*
      reinitializes a map (imap) of vectors with values from another map (cmap)
      parameters: imap, cmap
      return: none
    */
	
    typename map<int, vector<T>* >::const_iterator it;
	
    for(it = cmap.begin(); it != cmap.end(); ++it)
      for(size_t ie = 0; ie < imap[ it->first ]->size(); ++ie)
  	imap[ it->first ]->at(ie) = it->second->at(ie);
	
  };

  template<typename T> inline void multiReinitA(map<int, T* >& imap, map<int, vector<T>* > cmap) {
    /*
      reinitializes a map (imap) of arrays with values from another map (cmap)
      parameters: imap, cmap
      return: none
    */
	
    typename map<int, vector<T>* >::const_iterator it;
    for(it = cmap.begin(); it != cmap.end(); ++it) {
      for(size_t ie = 0; ie <it->second->size(); ++ie) {
  	imap[ it->first ][ie]=it->second->at(ie);
      }
    }
	
  };


  template<typename T> inline void reinitArray(map<int, T*>& imap, int cat) {
    typename map<int, T* >::const_iterator it;
    for(it=imap.begin(); it!=imap.end(); it++) {
      for(int ie=0;ie<_leafSizeI[it->first+cat];ie++) {
	it->second[ie]=0;
      }
    }
  }


  // Public Non-Template Methods


public:

  VarClass();
  ~VarClass();
	
  void reset();

  void setEvent(int ie) {
    _ie=ie;
    for(map<int,bool>::iterator it=_loaded.begin();it!=_loaded.end();it++)
      it->second = false;
  };
	
  void registerVar(string name);
  void registerVarPfx(string name, string prefix);
  void registerVar(string name, string type);
  bool isUsefulVar(string name);

  double get(string name, int idx=0);
  
  string getS(string name, int idx=0);

  // const vector<int>& getVI(string name);
  // const vector<unsigned int>& getVUI(string name);
  // const vector<size_t>& getVUL(string name);
  // const vector<bool>& getVB(string name);
  // const vector<double>& getVD(string name);
  // const vector<float>& getVF(string name);
  // const vector<string>& getVS(string name);
	
  // bool tryType(string name, string type);
  string getType(const string& name);
	
  unsigned int getSize(string name);

  //reinitalization of arrays (avoid weird stuff?)
  vector<int> getIds(const string& name);
  
  void buildTree(TTree* tree, bool bypass);
  void buildFriendTree(TTree* tree, bool bypass);
  void registerBranch(TTree* tree, string name, string type, EDataType t, int len);

  //clonage functions
  void* getBranchAddress(const string& name);
  string getEncodedFormat(const string& name);
  void cloneBranch(TTree* skT, const string& name);
  void reinitArrays();
  
  //systematic ucnertainty propagation     ============
  void applySystVar(string name, int dir, string mvar, float mag, string type);
  void applySystVar(string name, int dir, string mvar, 
		    vector<string> vars, vector<bool> specVars,
		    string db, string type);
  void backPortVar(int mvar);
  void backPortAllVars();
  // void applyWSystVar(string name, int dir, float& w, vector<string> vars, 
  // 		     string db, string type);
	
  void linkFriendBranches(TTree*& tree);

  void nextEvent(){ _nextEvent=true;};
  void sameEvent(){ _nextEvent=false;};
	
  SystUtils* _su;
  //===================================================

  // void
  // printVarNames() {
  //   for(int i=0;i< _varnames.size();i++)
  //     std::cout<<_varNames[i]<<std::endl;
  // }
  void
  printUsedVarNames() {
    for(map<string,bool>::const_iterator it=_usedVars.begin();
	it!=_usedVars.end();it++)
      std::cout<<it->first<<std::endl;
  }

  //   void
  // printAllVarNames() {
  //   for(map<string,bool>::const_iterator it=_usedVars.begin();
  // 	it!=_usedVars.end();it++)
  //     std::cout<<it->first<<std::endl;
  // }

  // Private Non-Template Methods

private:

  //vector<float> getUnivF(string name);

  double findValue(int id, int idx);
  void initIds();

  void setIds(string name, int cont, int type, int& id, TTree* tree);
 

  double findSVal(int tType, int key);
  double findVVal(int tType, int key, int idx);
  double findAVal(int tType, int key, int idx);

  unsigned int findASize(int tType, int key);

  vector<float> getUnivF(int id);


  void linkBranch(string name);
  void linkScalarVal(string name, int tType, int key);
  void linkVectorVal(string name, int tType, int key);
  void linkArrayVal(string name, int tType, int key);

  // Public Members

public: 

  enum {
    kNoneType=0,
    kInt=1,
    kUInt=2,
    kULong=3,
    kULong64=4,
    kDouble=5,
    kFloat=6,
    kString=7,
    kBool=8,
    kNTypes=9
  };
  //static string objectType[VarClass::kNTypes];
	
   enum {
     kNoneCont=0,
     kScalar=1,
     kVector=2,
     kArray=3,
     kNConts=4
   };
  //static string objectType[VarClass::kNTypes];

  // Private Members

private:


  //event number
  int _ie;
  map<int,TBranch*> _branches;
  map<int,bool> _loaded;


  //mapping names-ids
  static int oC_;
  static int oT_;
  map<int,int> cnt_;
  map<string, int> varIds_;
  map<string, int>::const_iterator itVId_;

  map<string, int> varTypes;
  map<string, int>::const_iterator itVt;

  map<string,int> _leafSize;
  map<int,int> _leafSizeI;
  
  //All variables
  mapVI varmVI;
  mapVUI varmVUI;
  mapVUL varmVUL;
  mapVD varmVD;
  mapVF varmVF;
  mapVB varmVB;
  mapVS varmVS;

  mapAI varmAI;
  mapAUI varmAUI;
  mapAUL varmAUL;
  mapAD varmAD;
  mapAF varmAF;
  mapAB varmAB;
  mapAS varmAS;	
	
  mapI varmI;
  mapUI varmUI;
  mapUL varmUL;
  mapUL64 varmUL64;
  mapS varmS;
  mapB varmB;
  mapD varmD;
  mapF varmF;
	
  mapTB varmTB;
	
  itMapVI itVI;
  itMapVUI itVUI;
  itMapVUL itVUL;
  itMapVD itVD;
  itMapVF itVF;
  itMapVB itVB;
  itMapVS itVS;

  itMapAI itAI;
  itMapAUI itAUI;
  itMapAUL itAUL;
  itMapAD itAD;
  itMapAF itAF;
  itMapAB itAB;
  itMapAS itAS;

  itMapI itI;
  itMapUI itUI;
  itMapUL itUL;
  itMapUL64 itUL64;
  itMapS itS;
  itMapB itB;
  itMapD itD;
  itMapF itF;
  itMapTB itTB;
	
  //list of variables
  map<string,bool> _usedVars;
  vector<string> _varnames;
  map<string, std::pair<string,int> > _varTypes;
  map<pair<string,string>,string> _prefix;

private:
  
  //backup maps for systeamtic uncertainty variations
  mapVI uncmVI;
  mapVUI uncmVUI;
  mapVUL uncmVUL;
  mapVD uncmVD;
  mapVF uncmVF;

  mapVI uncmAI;
  mapVUI uncmAUI;
  mapVUL uncmAUL;
  mapVD uncmAD;
  mapVF uncmAF;
	
  mapI uncmI;
  mapUI uncmUI;
  mapUL uncmUL;
  mapD uncmD;
  mapF uncmF;
	
  TTree* _mTree;
  vector<string> _friendBranches;

  bool _nextEvent;
	
  std::set<std::string> _regTwice;

};

#endif
