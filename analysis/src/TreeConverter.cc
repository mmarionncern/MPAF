#include "analysis/src/TreeConverter.hh"

#include <algorithm>

TreeConverter::TreeConverter(std::string cfg) {

  configure(cfg);
  initialize();

}


TreeConverter::~TreeConverter(){
 
}

void
TreeConverter::initialize() {
  _vectorToArray=(bool)getCfgVarI("vectorToArray", 0);
  string branches=getCfgVarS("branches","");
  //string branchesWithPfx=getCfgVarS("branchesWithPfx","");
  if(branches=="All") {

  } else {
    _branchesToKeep=Parser::split(branches,':');
    for(unsigned int i=0;i<_branchesToKeep.size();i++) {
      _vc->registerVar(_branchesToKeep[i]);
    }
    // _branchesToKeepPfx=Parser::split(branches,':');
    // for(unsigned int i=0;i<_branchesToKeep.size();i+=2) {
    //   _vc->registerVar(_branchesToKeepPfx[i],_branchesToKeepPfx[i+1]);
    // }
  }
  _nSkip=-1;
  _maxFound=false;
  _init=false;
  _skim=false;
  
}

void
TreeConverter::modifySkimming() {
  for(unsigned int i=0;i<_stdBranches.size();i++) {
    cloneSkimBranch(_stdBranches[i]);
  }
  initVectorToArray();
}

void
TreeConverter::run() {
  //cout<<" -->> "<<_vc->get("nJet")<<endl;
  _vc->reinitArrays();
  if(!_vectorToArray) { //array -> vector
  
 
    if(!_maxFound) { //finding the maximums
      for(unsigned int i=0;i<_branchesToKeep.size();i++) {
	int val=(_sizeBranches.find(_branchesToKeep[i])==_sizeBranches.end())?0:_sizeBranches[ _branchesToKeep[i] ];
	_sizeBranches[ _branchesToKeep[i] ] = max(val, (int)_vc->getSize(_branchesToKeep[i]));
      }
      _maxFound=(_ie+1>=_maxEvts);
      if(!_maxFound) return;
    }
    
    if(_maxFound) {
      //found the maximum, converting
      
      if(!_init) {
	_skim=true;
	_init=true;
	_ie=-1;
	vector<int> id(2,0);
	for(unsigned int i=0;i<_branchesToKeep.size();i++) {
	  
	  id=_vc->getIds(_branchesToKeep[i]);
	  if(id[0]==VarClass::kScalar) _stdBranches.push_back( _branchesToKeep[i] );
	  else { //all, vectors and arrays
	    //cout<<" -->> "<<id[1]<<endl;
	    if(id[1]==VarClass::kInt) _aBranchesI[ _branchesToKeep[i] ]=new int[_sizeBranches[_branchesToKeep[i]]];
	    if(id[1]==VarClass::kFloat) _aBranchesF[ _branchesToKeep[i] ]=new float[_sizeBranches[_branchesToKeep[i]]];
	    if(id[1]==VarClass::kDouble) _aBranchesD[ _branchesToKeep[i] ]=new double[_sizeBranches[_branchesToKeep[i]]];
	    if(id[1]==VarClass::kBool) _aBranchesB[ _branchesToKeep[i] ]=new bool[_sizeBranches[_branchesToKeep[i]]];
	  }
	  
	}//for loop

	// for(unsigned int i=0;i<_branchesToKeepPfx.size();i+=2) {
	  
	//   id=_vc->getIds(_branchesToKeepPfx[i]);
	//   if(id[0]==VarClass::kScalar) _stdBranches.push_back( _branchesToKeepPfx[i] );
	//   else { //all, vectors and arrays
	//     //cout<<" -->> "<<id[1]<<endl;
	//     if(id[1]==VarClass::kInt) _aBranchesI[ _branchesToKeepPfx[i] ]=new int[_sizeBranches[_branchesToKeepPfx[i]]];
	//     if(id[1]==VarClass::kFloat) _aBranchesF[ _branchesToKeepPfx[i] ]=new float[_sizeBranches[_branchesToKeepPfx[i]]];
	//     if(id[1]==VarClass::kDouble) _aBranchesD[ _branchesToKeepPfx[i] ]=new double[_sizeBranches[_branchesToKeepPfx[i]]];
	//     if(id[1]==VarClass::kBool) _aBranchesB[ _branchesToKeepPfx[i] ]=new bool[_sizeBranches[_branchesToKeepPfx[i]]];
	//   }
	  
	// }//for loop

	
	protInitSkimming();
	return;
      }


      convertVectorToArray();
      
    }

  }//  else { //vector -> array

  fillSkimTree();


}


void
TreeConverter::convertVectorToArray() {
  
  for(_itI=_aBranchesI.begin();_itI!=_aBranchesI.end();_itI++) {
    //cout<<_itI->first<<" <<-->> "<<_vc->getSize(_itI->first)<<endl;
    for(unsigned int i=0;i<_vc->getSize(_itI->first);i++) {
      _itI->second[i]=_vc->get(_itI->first,i);
      //cout<<i<<" : "<<_itI->second[i]<<" <<-->> "<<_vc->get(_itI->first,i)<<endl;
    }
  }
  
  for(_itF=_aBranchesF.begin();_itF!=_aBranchesF.end();_itF++) {
    for(unsigned int i=0;i<_vc->getSize(_itF->first);i++) {
      _itF->second[i]=_vc->get(_itF->first,i);
    }
  }

  for(_itD=_aBranchesD.begin();_itD!=_aBranchesD.end();_itD++) {
    for(unsigned int i=0;i<_vc->getSize(_itD->first);i++) {
      _itD->second[i]=_vc->get(_itD->first,i);
    }
  }
  
  for(_itB=_aBranchesB.begin();_itB!=_aBranchesB.end();_itB++) {
    for(unsigned int i=0;i<_vc->getSize(_itB->first);i++) {
      _itB->second[i]=_vc->get(_itB->first,i);
    }
  }
    
}


void
TreeConverter::convertArrayToVector() {


}


void
TreeConverter::initVectorToArray() {

  for(_itI=_aBranchesI.begin();_itI!=_aBranchesI.end();_itI++) {
    removeSkimBranch(_itI->first);
    ostringstream os;
    os<<_sizeBranches[_itI->first];
    addSkimBranch<int>(_itI->first, _itI->second, _itI->first+"["+os.str()+"]"+"/I");
  }

  for(_itF=_aBranchesF.begin();_itF!=_aBranchesF.end();_itF++) {
    removeSkimBranch(_itF->first);
    ostringstream os;
    os<<_sizeBranches[_itF->first];
    addSkimBranch<float>(_itF->first, _itF->second, _itF->first+"["+os.str()+"]"+"/F");
  }

  for(_itD=_aBranchesD.begin();_itD!=_aBranchesD.end();_itD++) {
    removeSkimBranch(_itD->first);
    ostringstream os;
    os<<_sizeBranches[_itD->first];
    addSkimBranch<double>(_itD->first, _itD->second, _itD->first+"["+os.str()+"]"+"/D");
  }

  for(_itB=_aBranchesB.begin();_itB!=_aBranchesB.end();_itB++) {
    removeSkimBranch(_itB->first);
    ostringstream os;
    os<<_sizeBranches[_itB->first];
    addSkimBranch<bool>(_itB->first, _itB->second, _itB->first+"["+os.str()+"]"+"/B");
  }

}

void
TreeConverter::initArrayToVector() {


}
