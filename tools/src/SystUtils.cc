#include "tools/src/SystUtils.hh"

using namespace std;

//ClassImp(SystUtils)

SystUtils::SystUtils() {
}

SystUtils::~SystUtils() {
}

string SystUtils::uDir[SystUtils::kNDirs]={
  "Up",
  "Do",
  ""
};


vector<string>
SystUtils::parseDb(string db, vector<bool>& specVars) {

  vector<string> vars;

  size_t ib=0;
  size_t ie=0;
  while(ie!=db.size()) {
    ie = db.find(":",ib);
    if(ie==string::npos) ie=db.size();
    vars.push_back( db.substr(ib,ie-ib) );
    specVars.push_back(false);

    if(vars.back().find("abs(")!=string::npos) {
      vars.back() = vars.back().substr(4, vars.back().size()-5 );
      specVars.back() = true;
    }

    ib = ie+1;
  }

  return vars;
}

void
SystUtils::addSystSource(string name, int dir, string type, vector<string> modVar, 
			 float val) {

  vector<string> pvars;// = parseDb(vars);
  vector<bool> specVars;
  
  SystST tmp;
  tmp.type = type;
  tmp.val = val;
  tmp.db = name;
  tmp.dir = dir;
  tmp.vars = pvars;
  tmp.modVar = modVar;

  string sName=name;
  if(dir==kUp) sName+="Up";
  if(dir==kDown) sName+="Do";
  
  _uncSrcs[ sName ] = tmp;
}

void
SystUtils::addSystSource(string name, int dir, string type, vector<string> modVar,
			 string db, string hname) {
  
  vector<bool> specVars;
  vector<string> dbVars = parseDb(db,specVars);
  
  string file = dbVars[0];
 
  SystST tmp;
  tmp.type = type;
  tmp.val = -100;
  tmp.db = name;  
  tmp.dir = dir;
  dbVars.erase( dbVars.begin() );
  tmp.vars = dbVars;
  tmp.specVars=specVars; 
  tmp.modVar = modVar;

 
  string sName=name;
  if(dir==kUp) sName+="Up";
  if(dir==kDown) sName+="Do";

  
  if(hname!="" && hname!="e" && hname!="E")
    _dbm->loadDb(name, file , hname);
  else {
    _dbm->loadDb(name, file);
  }


  _uncSrcs[ sName ] = tmp;
}


SystST
SystUtils::getSystInfos(string name, int dir) {
  
  map<string,SystST>::const_iterator it;
  
  if(dir==kUp) name+="Up";
  if(dir==kDown) name+="Do";

  it = _uncSrcs.find(name);
  if(it==_uncSrcs.end()) {
    cout<<" Error, no "<<name<<" systematic uncertainty detected, emergency abort "<<endl;
    abort();
  }

  return it->second;
}

void
SystUtils::systOpW(string name, int dir, string type, float& w,
		   string db, vector<float> vals) {

  float dw=0;
  if(dir==kUp) dw = _dbm->getDBErrH(db,vals[0],vals[1],vals[2],vals[3],vals[4], 
				    vals[5], vals[6], vals[7], vals[8], vals[9]);
  if(dir==kDown) dw = _dbm->getDBErrL(db,vals[0],vals[1],vals[2],vals[3],vals[4], 
				      vals[5], vals[6], vals[7], vals[8], vals[9]);
  
  systOp<float>(name, dir, type, w, dw);
 
}

void
SystUtils::systOpW(string name, int dir, string type, float& w, float x) {
  systOp<float>(name, dir, type, w, x);
}
