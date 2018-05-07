#include "analysis/src/CorrelationAnalysis.hh"

#include <algorithm>

CorrelationAnalysis::CorrelationAnalysis(std::string cfg) {

  //startExecution(cfg);
  
  initialize();

}


CorrelationAnalysis::~CorrelationAnalysis(){
 
}

void
CorrelationAnalysis::initialize() {
  string cors=getCfgVarS("correlations","");
  vector<string> correlations=Parser::split(cors,'!');
  
  for(unsigned int i=0;i<correlations.size();i++) {
    vector<string> tmp=Parser::split(correlations[i],':');
    for(unsigned j=0;j<tmp.size();j++) {
      //cout<<tmp[j]<<" <--->>> "<<(_allVars.find(tmp[j])!=_allVars.end())<<endl;
      if(_allVars.find(tmp[j])==_allVars.end())
	_allVars.insert(tmp[j]);
      
      vector<string> tmp2=getFullCompo(tmp[j]);
      for(unsigned k=0;k<tmp2.size();k++) {
	//	cout<<j<<" -> "<<tmp2[k]<<"  "<<tmp[j]<<endl;
	if(!_vc->isUsefulVar(tmp2[k]) ) { //variable not registered yet
	  //cout<<" registering ->  "<<tmp2[k]<<endl;
	  _vc->registerVar(tmp2[k]);
	}
      }
    }
    _correlations.push_back( make_pair(tmp[0], tmp[1]) );

  }


  _vc->registerVar("lepWIdx");
  _vc->registerVar("lepZIdx");
  _vc->registerVar("jetIdx");
}

void
CorrelationAnalysis::defineOutput() {

  //  cout<<"<<< ============================================ "<<endl;
  for(unsigned int ic=0;ic<_correlations.size();ic++) {

    vector<int> id0=getIds(_correlations[ic].first);
    vector<int> id1=getIds(_correlations[ic].second);
    int size0 = getSize(_correlations[ic].first);
    int size1 = getSize(_correlations[ic].second);
    if(id0[0]==VarClass::kScalar) size0=1;
    if(id1[0]==VarClass::kScalar) size1=1;

    for(int ii=0;ii<size0;ii++) {
      ostringstream os;
      if(size0!=1) os<<ii;

      for(int jj=0;jj<size1;jj++) {
	ostringstream os2;
	if(size1!=1) os2<<jj;
	
	_hm->addVariable(_correlations[ic].first+os.str()+"Vs"+_correlations[ic].second+os2.str(),
			 101,-1.,1.02,101,-1.,1.02,_correlations[ic].first+os.str()
			 ,_correlations[ic].second+os2.str());

	_hm->addVariable(_correlations[ic].first+os.str(),101,-1.,1.02,_correlations[ic].first+os.str());
	_hm->addVariable(_correlations[ic].second+os2.str(),101,-1.,1.02,_correlations[ic].second+os2.str());
	  
	CorVar cv;
	_corVars[_correlations[ic].first+os.str()+"Vs"+_correlations[ic].second+os2.str()] = cv;
      }

      // if(size0!=1) //checking the neural net profile shapes
      // 	_hm->addVariable(_correlations[ic].first+os.str()+"Vs"+_correlations[ic].second,
      // 			 100,0,1.,100,0,1.,_correlations[ic].first+os.str(),
      // 			 _correlations[ic].second, true, true);
    }

  }//correlation

  // cout<<">>> ============================================ "<<endl;
  for(set<string>::const_iterator it=_allVars.begin();it!=_allVars.end();it++) {
    string name= (*it);
    vector<int> id=getIds(name);
    int size = getSize(name);
    //cout<<name<<" <> "<<id[0]<<" <> "<<size<<endl;
    if(id[0]==VarClass::kScalar) _vars.push_back(name);
    else {
      for(int ii=0;ii<size;ii++) {
	ostringstream os;
	os<<ii;

	_vars.push_back(name+os.str());
      }
    }//vector/array
  }//_allVars
  //cout<<" -->><><> "<<_vars.size()<<endl;
  _hm->addVariable("correlationTable",_vars.size(),0,_vars.size(),
		   _vars.size(),0,_vars.size(), "", "", true, false,
		   _vars, _vars );
  
}


void
CorrelationAnalysis::writeOutput() {
  
  float x=0;
  float y=0;
  float w=1;
  
  //compute correlation coefficients
  for(unsigned int ic=0;ic<_correlations.size();ic++) {
    vector<int> id0=getIds(_correlations[ic].first);
    vector<int> id1=getIds(_correlations[ic].second);
    int size0 = getSize(_correlations[ic].first);
    int size1 = getSize(_correlations[ic].second);
    if(id0[0]==VarClass::kScalar) size0=1;
    if(id1[0]==VarClass::kScalar) size1=1;
    
    for(int ii=0;ii<size0;ii++) {
      for(int jj=0;jj<size1;jj++) {
	ostringstream os, os2;
	if(size0!=1) os<<ii;
	if(size1!=1) os2<<jj;
	string name=_correlations[ic].first+os.str()+"Vs"+_correlations[ic].second+os2.str();

	
	float maxX = *std::max_element(_corVars[name].x.begin(), _corVars[name].x.end());
	float minX = *std::min_element(_corVars[name].x.begin(), _corVars[name].x.end());
	float maxY = *std::max_element(_corVars[name].y.begin(), _corVars[name].y.end());
	float minY = *std::min_element(_corVars[name].y.begin(), _corVars[name].y.end());

	for(unsigned int iv=0;iv<_corVars[name].x.size();iv++) {
	  x=StatUtils::normalizeVariable(_corVars[name].x[iv], minX, maxX, -1, 1);
	  y=StatUtils::normalizeVariable(_corVars[name].y[iv], minY, maxY, -1, 1);
	  w=_corVars[name].w[iv];
	  if(_correlations[ic].second.find("lstm_btag_lstm2_NNLayerTest")!=string::npos && jj==0 && y<-0.99 && ii==0 && ic<2)
	    cout<<minY<<"  "<<maxY<<"  "<<_corVars[name].y[iv]<<"  "<<y<<" / "<<_corVars[name].x[iv]<<"  ====== "<<StatUtils::min(_corVars[name].y)<<"  "<<StatUtils::max(_corVars[name].y)<<endl;

	  
	  ((TH2*)(_hm->getHisto(name,0)))->Fill(x,y,w);
	  _hm->getHisto(_correlations[ic].first+os.str(),0)->Fill(x,w);
	  _hm->getHisto(_correlations[ic].second+os2.str(),0)->Fill(y,w);
	  
	}//each event

	
	float cor=_corVars[name].getCorCoef();
	if(cor==-100) continue;
	
	int binx=-1;
	int biny=-1;
	for(unsigned int i=0;i<_vars.size();i++) {
	  if(_vars[i]==_correlations[ic].first+os.str() && binx==-1) binx=1+i;
	  if(_vars[i]==_correlations[ic].second+os2.str() && biny==-1) biny=1+i;
	  if(binx!=-1 && biny!=-1) break;
	}
	
	_hm->getHisto("correlationTable",0)->SetBinContent(binx,biny, cor);
	  //_hm->fill();

	
      }
    }
  
  } //correlation

}

void
CorrelationAnalysis::run() {

  //fixme
  if(_vc->get("lepZIdx",0)==-1 || _vc->get("lepZIdx",1)==-1 ||
     _vc->get("lepWIdx")==-1 || _vc->get("jetIdx",0)==-1 || _vc->get("jetIdx",1)==-1) return;

  //if(_vc->get("jetIdx",2)==-1) return;
  //if(_vc->get("jetIdx",2)!=-1 && _vc->get("jetIdx",3)==-1) return;
  
  string name="";
  for(unsigned int ic=0;ic<_correlations.size();ic++) {

    vector<int> id0=getIds(_correlations[ic].first);
    vector<int> id1=getIds(_correlations[ic].second);
    int size0 = getSize(_correlations[ic].first);
    int size1 = getSize(_correlations[ic].second);
    if(id0[0]==VarClass::kScalar) size0=1;
    if(id1[0]==VarClass::kScalar) size1=1;

    for(int ii=0;ii<size0;ii++) {
      for(int jj=0;jj<size1;jj++) {
	ostringstream os, os2;
	if(size0!=1) os<<ii;
	if(size1!=1) os2<<jj;
	
	name=_correlations[ic].first+os.str()+"Vs"+_correlations[ic].second+os2.str();

	float val1=get(_correlations[ic].first, ii);
	float val2=get(_correlations[ic].second, jj);
	
	if(_correlations[ic].first.find("Jet_btagCSV")!=string::npos && val1<0) val1=0;
	if(_correlations[ic].second.find("Jet_btagCSV")!=string::npos && val2<0) val2=0;

	// if(_correlations[ic].second.find("lstm_btag_lstm2_NNLayerTest")!=string::npos && jj==0)
	//   cout<<_ie<<" ==>> "<<ii<<"  "<<jj<<" -->> "<<val2<<"  "<<val1<<" / "
	//       <<_vc->get("lepZIdx",0)<<"  "<<_vc->get("lepZIdx",1)<<"  "<<_vc->get("lepWIdx")<<"  "
	//       <<_vc->get("jetIdx",0)<<"  "<<_vc->get("jetIdx",1)<<"  "<<_vc->get("jetIdx",2)<<endl;
	
	//cout<<
	   
	// _hm->fill(name,
	// 	  _vc->get(_correlation[ic][0], size0),
	// 	  _vc->get(_correlation[ic][1], size1) );

	_corVars[name].addEntry( val1 , val2 );

      }
    }
	
  } //correlation
  
}


vector<int>
CorrelationAnalysis::getIds(string name) {
  size_t p=name.find("[");
  if(p!=string::npos) {
    string idname=name.substr(p+1, name.size()-p-2 );
    return _vc->getIds(idname);
  } else {
    return _vc->getIds(name);
  }
}

int
CorrelationAnalysis::getSize(string name) {
  size_t p=name.find("[");
  if(p!=string::npos) {
    string idname=name.substr(p+1, name.size()-p-2 );
    return _vc->getSize(idname);
  } else {
    return _vc->getSize(name);
  }
}

float
CorrelationAnalysis::get(string name, int idx) {

  size_t p=name.find("[");
  if(p!=string::npos) {
    string idname=name.substr(p+1, name.size()-p-2 );
    name=name.substr(0,p);
    //cout<<idname<<"   "<<name<<endl;
    //cout<<idname<<"  "<<name<<" / "<<idx<<" -> "<<_vc->get(idname, idx)<<endl;
    int id=_vc->get(idname, idx);
    return _vc->get(name, id);
  } else {
    //cout<<_ie<<"  "<<name<<" / "<<idx<<" -> "<<_vc->get(name, idx)<<endl;
    return _vc->get(name, idx);
  }


}

vector<string>
CorrelationAnalysis::getFullCompo(const string& str) {

  size_t p=str.find("[");
  if(p!=string::npos) {
    string idname=str.substr(p+1, str.size()-p-2 );
    string name2=str.substr(0,p);
    //cout<<idname<<" <+++++++>>>  "<<name2<<endl;
    vector<string> vs({idname, name2});
    return vs;
  } else {
    vector<string> vs({str});
    return vs;
  }
  
}
