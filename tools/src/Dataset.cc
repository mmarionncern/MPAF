#include "src/Dataset.hh"

using namespace std;

ClassImp(Dataset)


//____________________________________________________________________________
Dataset::Dataset():
_chain(0)
{
  _isData = false;
  _isDataDriven = false;
  _isPoissonPseudo=false;
  config("", 1, kTree );
}


//____________________________________________________________________________
Dataset::Dataset(string name):
  _chain(0)
{
  _isData = false;
  _isDataDriven = false;
  _isPoissonPseudo=false;
  config(name, 1, kTree );
}


//____________________________________________________________________________
Dataset::Dataset(string name, int color):
  _chain(0)
{

  _isData = false;
  _isDataDriven = false;
  _isPoissonPseudo=false;
  config(name, color, kHisto);

}


//____________________________________________________________________________
void Dataset::config(string name, int color, int content) {

  _name = name;
  _color = color;
  _isGhost = false;
  _isDataDriven = false;
  _isPoissonPseudo=false;
  _dsContentType = content;
}


//____________________________________________________________________________
Dataset::~Dataset() {
  delete _chain;
}

//____________________________________________________________________________
void Dataset::freeMemory() {
  delete _chain;
}

void
Dataset::setUsefulVars(vector<string> vars) {
  _usefulVars = vars;
}

//____________________________________________________________________________
void Dataset::addSample(const SampleId sId, string path, string dir, string objName,
			string hname, string hwgtname, float xSect, float kFact, 
			float lumi, float eqLumi, int link, bool loadH, bool isPoissonPseudo) {
  /*
    adds a sample to the dataset; the sample has a name encoded in sfullname,
    lies in the directory path/dir/, has a tree called objName or a histogram
    called hname (hwgtname is a histogram for the sum of processed weights
    corresponding to the sample), has cross section xSect, k-factor kFact, luminosity lumi
    and equivalent luminosity eqLumi (i.e. corrected for the number of events we're
    looping on)
    parameters: sfullname ("data:sname" or just "sname"), path, dir, objName, hname, hwgtname, xSect, kFact, lumi, eqLumi
    return: none
  */

  _isData = false;
  _isPoissonPseudo=isPoissonPseudo;
  
  if(sId.isData)_isData=true;
  if(sId.dd) {
    //norm corresponds to a datadriven like stuff
    _isDataDriven=true;
  }

  //store the control region from which the sampleshould come from, if any
  // _crSamples[ sId.name ] = sId.cr;

  // //store the norm option
  // _crSamples[ sId.name ] = sId.norm!=-1;


  //protection against double loading in the same dataset
  for(size_t is=0;is<_samples.size();is++) {
    if(_samples[is].getName()==sId.name && _samples[is].getCR()==sId.cr) {
      return;
    }
  }
	
  //Tree/chain initialisation =========
  if(isTreeType())
    if(_chain==NULL)
      _chain = new TChain(objName.c_str());

  //======
	
  //Looking for the tree if not data-driven
  //string tmpPath=isTreeType()?("data/"+path):"root"; //CH: why? what about absolute paths?
  string subdir=isTreeType()?"data":"root";
  string tmpFName=isTreeType()?(sId.name):objName;
  int nProcEvt = (hname=="")?-1:getNProcEvents(path, dir, subdir, tmpFName, hname);
  double sumProcWgt = (hwgtname=="")?-1:getSumProcWgts(path, dir, subdir, tmpFName, hwgtname);
  
  if(_treelinks.size()!=0) {
    nProcEvt = getTotNProcEvents();
    sumProcWgt = getTotSumProcWgts();
  }

  Sample s(sId, nProcEvt, sumProcWgt, xSect, kFact, eqLumi);
  _samples.push_back(s);
  if(link!=-1)
    _links[ link ].push_back(_samples.size()-1);
  
  //tree analysis 
  if(isTreeType()) {
    loadTree(path, dir, subdir, sId.name, objName);
	
    cout<<" Adding "<<sId.name<<"  to "<<_name
	<<"   :  nEvt "<<_chain->GetEntries()<<" ("<<nProcEvt
	<<" gen) "<<" ("<<sumProcWgt<<" genwgts)"<<" / w (/pb-1) = "<<s.getLumW()<<endl;
  }
  else {
    if(loadH) { //reading histograms only when needed (disabled for datacards)
      loadHistos(path, dir, subdir, objName, hname, sId.cr);
    }
    if(sId.norm==-1) {
      if(sId.cr=="" && sId.dd==false)
	cout<<" Adding "<<sId.name<<"  to "<<_name
	    <<"   : "<<" ("<<nProcEvt
	    <<" gen) "<<" ("<<sumProcWgt<<" genwgts)"<<" / w (/pb-1) = "<<s.getLumW()<<endl;
      else
	cout<<" Adding "<<sId.name<<" ("<<sId.cr<<")  to "<<_name
	    <<"   : "<<" ("<<nProcEvt
	    <<" gen) "<<" ("<<sumProcWgt<<" genwgts)"<<" / w (/pb-1) = "<<s.getLumW()<<endl;
    
    }
    else {
      cout<<" Adding "<<sId.name<<"  to "<<_name
	  <<"   : "<<" fixed normalization ("<<sId.norm<<")"<<endl;

    }

  }

  //post-processing and update of the weights for linked samples
  if(link!=-1) {
    float sumNProc=getLinkedSumNProc(link);
    float sumWProc=getLinkedSumWeightProc(link);
    for(size_t is=0;is<_links[link].size();is++) {
      _samples[ _links[link][is] ].setNProcEvts(sumNProc+nProcEvt );
      _samples[ _links[link][is] ].setSumProcWgts(sumWProc+sumProcWgt );
      _samples[ _links[link][is] ].linking();
      _samples[ _links[link][is] ].computeWeight();
      cout<<" ===>>> Updated "<<_samples[_links[link][is]].getName()<<" sample weight : w="<<_samples[_links[link][is]].getLumW()<<" ("<<sumNProc<<"/"<<sumWProc<<") "<<endl;
    }
  }

}

void
Dataset::addFriend(vector<string> friendT){
  _friends.push_back(friendT);
}

void
Dataset::addLink(string linkname) {
  _treelinks.push_back(linkname);
}



int
Dataset::getNProcEvents(string path, string dir, string subdir, string fileName, string hname) {

  string NameF = goodFilePath(path, dir, fileName, subdir);

  TFile* file = TFile::Open( NameF.c_str() );
  if(file==nullptr) { cout<<" warning, unable to find the proper number of processed events"<<endl;return 1;}
  TH1* htmp = (TH1*)file->Get( hname.c_str() );
  int nProc=-1;
  if(htmp) {
    nProc = htmp->Integral(0,1001);
    delete htmp;
  }
  else nProc = -1;

  file->Close();
  delete file;

  return nProc;
}

double
Dataset::getSumProcWgts(string path, string dir, string subdir, string fileName, string hwgtname) {

  string NameF = goodFilePath(path, dir, fileName, subdir);
  
  TFile* file = TFile::Open( NameF.c_str() );
  if(file==nullptr) { cout<<" warning, unable to find the proper number of processed events"<<endl;return 1;}
  TH1* htmp = (TH1*)file->Get( hwgtname.c_str() );
  double nProc=-1;
  if(htmp) {
    nProc = htmp->Integral(0,1001);
    delete htmp;
  }
  else nProc = -1;
 
  file->Close();
  delete file;

  return nProc;
}



void
Dataset::setTotNProcEvents(string path, string dir,
			   string subdir, string hwgtname) {
  
  _totNProcEvents=0;
  for(unsigned int is=0;is<_treelinks.size();is++) {
    _totNProcEvents+=getNProcEvents(path, dir, subdir, _treelinks[is], hwgtname);
  }
}

void
Dataset::setTotSumProcWgts(string path, string dir,
			   string subdir, string hwgtname) {
  
  _totSumProxWgts=0;
  for(unsigned int is=0;is<_treelinks.size();is++) {
    _totSumProxWgts+=getSumProcWgts(path, dir, subdir, _treelinks[is], hwgtname);
  }
}


int
Dataset::getTotNProcEvents() const {
  return _totNProcEvents;
}

float
Dataset::getTotSumProcWgts() const {
  return _totSumProxWgts;
}


float 
Dataset::getLinkedSumNProc(int link) {
  // float tot=0;
  // for(size_t is=0;is<_links[link].size();is++)
  //   tot += _samples[ _links[link][is] ].getNProcEvts();

  return _samples[ _links[link][0] ].getNProcEvts();//tot;
}

float 
Dataset::getLinkedSumWeightProc(int link) {
  // float tot=0;
  // for(size_t is=0;is<_links[link].size();is++)
  //   tot += _samples[ _links[link][is] ].getSumProcWgts();

  return _samples[ _links[link][0] ].getSumProcWgts();//tot;
}


vector<string>
Dataset::getSampleNames() {
  vector<string> snames;
  for(size_t is=0;is<_samples.size();is++) {
    snames.push_back( _samples[is].getName() );
  }
  return snames;
}

vector<const Sample*>
Dataset::getSamples() const {
  vector<const Sample*> samples;
  for(size_t is=0;is<_samples.size();is++) {
    const Sample* sample=&(_samples[is]);
    samples.push_back(sample);
  }
  return samples;
}


const Sample*
Dataset::getSample(string sname) const {
  vector<string> snames;
  for(size_t is=0;is<_samples.size();is++) {
    if(sname==_samples[is].getName()) return &(_samples[is]);
  }
  return nullptr;
}


void 
Dataset::loadTree(string path, string dir, string subdir, string sname, string objName) {
  TFile* datafile(nullptr);

  string NameF = goodFilePath(path, dir, sname, subdir);

  datafile = TFile::Open(NameF.c_str());
  if(datafile==nullptr) { 
    cout<<" No such file "<<sname<<endl; return;
  }
    
  TTree* tmptree = (TTree*)datafile->Get( objName.c_str() );

  if(tmptree != nullptr ) {
    _chain->Add( (NameF+"/"+objName).c_str() ); 

    //cleaning friends if needed
    TList* lfriends = _chain->GetListOfFriends();
    TIter next(lfriends);
    TObject* fr = 0;
    while ((fr = next())) {
      _chain->RemoveFriend((TTree*)fr);
    }


    // adding friend-trees
    for (size_t ft=0; ft<_friends.size(); ft++){
      string ext=((_friends[ft].size()==1)?"evVarFriend":_friends[ft][1]);
      string NameFr = goodFilePath(path, dir, _friends[ft][0] + "/"+ext+"_" + sname, subdir);
      if(!gSystem->AccessPathName(NameFr.c_str()) ) //false if file exists...
	NameFr=goodFilePath(path, "", _friends[ft][0] + "/"+ext+"_" + sname, subdir);
      
      //string name = _friends[ft]+" = sf/t"; //MM fixme
      string name = _friends[ft][0]+" = "+((_friends[ft].size()==1)?"t":_friends[ft][2]);// ftNN";
      //cout<<" Connecting friend tree : "<<name<<endl;
      _chain->AddFriend((name).c_str(),(NameFr).c_str());
    } 
    //nEvent = tmptree->GetEntries();
  }
  else {
    cout<<" Error no correct tree in "<<sname<<" file, aborting"<<endl;
    abort();
  }    

  delete tmptree;
  delete datafile;
   
}

void 
Dataset::loadHistos(string path, string dir, string subdir, string filename, string hname, string optCat) {
  TFile* datafile(nullptr);
  
  string NameF = goodFilePath(path, dir, filename, subdir);
  datafile = TFile::Open(NameF.c_str());

  if(datafile==nullptr) {cout<<"Warning, unable to load histograms for sample "<<hname<<endl; return;}

  // for(size_t is=0;is<_samples.size();is++) {
  //   cout<<_name<<" -->> "<<_samples[is].getName()<<endl;
  // }
  
  //scan the file to retrieve the histograms
  TIter nextkey(datafile->GetListOfKeys());
  TKey *key;
  while ((key = ((TKey*)nextkey()))) {
    TObject* obj = key->ReadObj(); 
    if( obj==nullptr ) continue;
      
    //found a TDirectory which can be a variable
    if( (string)obj->IsA()->GetName()!=("TDirectoryFile") ) continue;
      
    string varName(obj->GetName());
    map<string, TH1*> tmp;

    bool find=false;
    for(size_t i=0;i<_usefulVars.size();i++) {
      if(_usefulVars[i]==varName ||
	 _usefulVars[i]+optCat==varName ||
	 varName.find(_usefulVars[i]+"Unc")!=string::npos ||
	 varName.find(_usefulVars[i]+optCat+"Unc")!=string::npos) {
	find=true; break;
      }
    }
    if(_usefulVars.size()!=0 && !find) continue; 
       // find(_usefulVars.begin(), _usefulVars.end(), varName)==_usefulVars.end() &&
       // find(_usefulVars.begin(), _usefulVars.end(), varName+optCat)==_usefulVars.end() &&
       // !findUnc ) continue;
    
    if(optCat!="") {
      //if (optCat.substr(0,1)!="_") optCat="_"+optCat;
      size_t op=varName.find(optCat);
      if(op==string::npos) continue;
      else varName.erase(op,optCat.size());
    }

    TIter nextkeyD( ((TDirectory*)obj)->GetListOfKeys() );
    TKey *keyD;
    while ((keyD = ((TKey*)nextkeyD()))) {
      TObject* objD = keyD->ReadObj(); 
      if( objD==nullptr ) continue;

      if( ((string)(objD->IsA()->GetName())).substr(0,2)!=("TH") &&
	  ((string)(objD->IsA()->GetName())).substr(0,2)!=("TP") ) continue;

      //matching the samples needed for the dataset
      string sName( objD->GetName() );
      for(size_t is=0;is<_samples.size();is++) {
	if( sName!=_samples[is].getName() ) continue;
	if( _samples[is].getCR()!=optCat && sName!=_samples[is].getName() ) continue;
      	if( _histos[ varName ].find(sName+optCat)!=_histos[varName].end() &&
	    _samples[is].getCR()==optCat) continue; //avoid double counting

	//histograms and not normalization file
	if(varName=="nEvtProc") continue;
	if(varName=="sumWgtProc") continue;
	if(_histos[ varName ].size()==0) { //initialization
	  tmp[ sName+optCat ] = (TH1*)((TH1*)objD->Clone());
	  _histos[ varName ]= tmp;
	}
	else {
	  _histos[ varName ][ sName+optCat ]= (TH1*)((TH1*)objD->Clone());
	}
	
	break;
	
      }//sample loop
	
    } //loop keyD in directory
      
  } //loop key in file

  datafile->Close();
  delete datafile;
  
}

vector<string> 
Dataset::getObservables() {
  vector<string> names;
  for(map<string,map<string, TH1*> >::const_iterator it=_histos.begin();
      it!=_histos.end();it++) {
    names.push_back( it->first );
  }

  return names;
}

TH1*
Dataset::getHisto(string varName, string sName) {
  if(_histos.find(varName)==_histos.end()) {
    cout<<" Error, observable "<<varName<<" not found "<<endl;
    return nullptr;
  }
  if(_histos[ varName ].find(sName)==_histos[ varName ].end()) {
    cout<<" Warning, sample "<<sName<<" not found for observable "<<varName<<endl;
    return nullptr;
  }
  return (TH1*)_histos[ varName ][ sName ]->Clone();
}


int
Dataset::hasSample(string sname) const {

  for(size_t is=0;is<_samples.size();is++) {
    if(_samples[is].getName()==sname)
      return is;
  }
  
  return -1;
}

float
Dataset::getWeight(string sname) const {
  int is = hasSample(sname);
  if(is==-1) return 0;
  return getWeight(is);
}

string
Dataset::goodPath(string path){

  if(path.find("psi.ch") != (size_t) -1) return "dcap://t3se01.psi.ch:22125/" + path;
  if(path.find("/eos/")  != (size_t) -1) return "root://eoscms.cern.ch/" + path;

  return path;

}


string
Dataset::goodFilePath(const string& path, const string& dir, const string& fileName, const string& subdir) {

  string opath="";
  //check file first
  opath=goodAbsFilePath(path, dir, fileName, subdir);
  size_t n=opath.find("/./");
  if(n!=string::npos) {
    opath=opath.substr(0,n)+"/"+opath.substr(n+3,opath.size()-n-3);
  }
  
  //check URL after
  //avoiding error handling here
  int errLvl=gErrorIgnoreLevel;
  gErrorIgnoreLevel =1000000;
  TFile* tmp=TFile::Open(opath.c_str(),"read"); //should be better than that...
  gErrorIgnoreLevel = errLvl;
  if(!tmp) { //false if file exists...
    opath=goodURLFilePath(path, dir, fileName, subdir);
    //cout<<" -->>> "<<opath<<endl;
    n=opath.find("/./");
    if(n!=string::npos) {
      opath=opath.substr(0,n)+"/"+opath.substr(n+3,opath.size()-n-3);
    }
    opath=getURL(opath);
  }
  delete tmp;
   

  return opath;
}


string
Dataset::goodAbsFilePath(string path, string dir, string fileName, string subdir){
  // CH: path is the "dir" variable given in the config file
  //     dir  is the "dir" attribute given to the dataset (if so), whose name is fileName

  // remove the last slash because it's added in the logic below
  if(dir .length() > 0 && dir .substr(dir .length()-1,1) == "/") dir .erase(dir .length()-1);
  if(path.length() > 0 && path.substr(path.length()-1,1) == "/") path.erase(path.length()-1);

  // absolute dir
  if(dir.substr(0,1) == "/") 
    return goodPath(dir + "/"  + fileName + ".root"); 

  // dir on EOS with root://
  if(dir.find(":") != (size_t) -1 && dir.find("psi.ch") == (size_t) -1) 
    return dir + "/"  + fileName + ".root";

  // dir on EOS with eos tag
  if(dir.find("eos") != (size_t) -1 && dir.find("psi.ch") == (size_t) -1) 
    return dir + "/"  + fileName + ".root";
  
  // relative dir -> relative to path!
  if(dir != "") 
    path += "/" + dir;

  // path on EOS with root://
  if(path.find(":") != (size_t) -1 && path.find("psi.ch") == (size_t) -1) 
    return path + "/"  + fileName + ".root";

 // path on EOS with root://
  if(path.find("eos") != (size_t) -1 && path.find("psi.ch") == (size_t) -1) 
    return path + "/"  + fileName + ".root";

  // absolute path
  if(path.substr(0,1) == "/") 
    return goodPath(path + "/" + fileName + ".root");

  // ignore empty subdirs (in case data or root is already appended to path)
  if(subdir.length() > 0) 
    path = subdir + "/" + path;

  // relative path -> relative to MPAF/workdir! data or root given in subdir
  return string(getenv("MPAF")) + "/workdir/" + path + "/" + fileName + ".root";

}


string
Dataset::goodURLFilePath(string path, string dir, string fileName, string subdir) {
  // CH: path is the "dir" variable given in the config file
  //     dir  is the "dir" attribute given to the dataset (if so), whose name is fileName

  // remove the last slash because it's added in the logic below
  if(dir .length() > 0 && dir .substr(dir .length()-1,1) == "/") dir .erase(dir .length()-1);
  if(path.length() > 0 && path.substr(path.length()-1,1) == "/") path.erase(path.length()-1);

  // absolute dir
  if(dir.substr(0,1) == "/") 
    return goodPath(dir + "/"  + fileName + ".root.url"); 

  // dir on EOS with root://
  if(dir.find(":") != (size_t) -1 && dir.find("psi.ch") == (size_t) -1) 
    return dir + "/"  + fileName + ".root.url";

  // dir on EOS with eos tag
  if(dir.find("eos") != (size_t) -1 && dir.find("psi.ch") == (size_t) -1) 
    return dir + "/"  + fileName + ".root.url";
  
  // relative dir -> relative to path!
  if(dir != "") 
    path += "/" + dir;

  // path on EOS with root://
  if(path.find(":") != (size_t) -1 && path.find("psi.ch") == (size_t) -1) 
    return path + "/"  + fileName + ".root.url";

 // path on EOS with root://
  if(path.find("eos") != (size_t) -1 && path.find("psi.ch") == (size_t) -1) 
    return path + "/"  + fileName + ".root.url";

  // absolute path
  if(path.substr(0,1) == "/") 
    return goodPath(path + "/" + fileName + ".root.url");

  // ignore empty subdirs (in case data or root is already appended to path)
  if(subdir.length() > 0) 
    path = subdir + "/" + path;

  // relative path -> relative to MPAF/workdir! data or root given in subdir
  return string(getenv("MPAF")) + "/workdir/" + path + "/" + fileName + ".root.url";

}

string
Dataset::getURL(const string& urlFile) {

  ifstream in(urlFile.c_str(), ios::in);
  string url;
  in >> url;
  in.close();
  return url;
}
