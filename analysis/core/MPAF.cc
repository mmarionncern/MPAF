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

#include "analysis/core/MPAF.hh"


#include <TObjArray.h>

/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
MPAF::MPAF(){
  /* 
     constructs the MPAF Class 
     parameters: none
     return: none
  */
	
  initialize();
}


//____________________________________________________________________________
MPAF::~MPAF(){
  /* 
     destructs the MPAF class
     parameters: none
     return: none
  */

  delete _vc;
  delete _hm;
  delete _dbm;
  delete _au;

}


//____________________________________________________________________________
void MPAF::initialize(){
  /*
    initializes the MPAF class, defining standard values of certain variables
    parameters: none
    return: none
  */
 
  _vc  = new VarClass();
  _hm  = new HistoManager();
  _dbm = new DataBaseManager();
  _au  = new AnaUtils();
  
  _vc->_su->init(_dbm);

  _fullSkim=false;
  _skim=false;
  _friendSkim=false;
  
  _nEvtMax=-1;
  _nSkip=0;
  _byPassDsName="";

  _wfNames[AUtils::kGlobal] = "";
  _offsetWF=0;
  
  _hname="";
  _hwgtname="";
  _summary=false;

  _systVarOnly=false;
  _systSource="";

  _postfix="";

  _verb=0;
 
}


void
MPAF::setNMax(unsigned long int nMax) {
  _nEvtMax=nMax;

}
void
MPAF::setNSkip(unsigned long int nSkip) {
  _nSkip=nSkip;

}
void
MPAF::setDS(string dsName) {
  _byPassDsName=dsName;
}

//____________________________________________________________________________
//void MPAF::modifyWeight() {
  /*
    modifies the event weight for every entry in the tree
    parameters: none
    return: none
  */  

//}


//____________________________________________________________________________
void MPAF::analyze(){
  /*
    does the loop over the data samples, reads the tree and calls run() at every
    iteration
    parameters: none
    return: none
  */
  TStopwatch stw;
  float timeCPU=0;
  float timeWall=0;
  int nE=0;

  //CH: this line has to be BEFORE the call of defineOutput!
  //FakeRatio and FRinSitu class needs to know the number of datasets before defining Output
  _numDS = _datasets.size();
  if(_numDS==0) {
    cout<<"ERROR: dataset list is empty"<<endl;
    return;
  }

  //fixme MM //for correlation analysis
  if(_className=="CorrelationAnalysis") {
    _vc->reset();
    _vc->buildTree( _datasets[0]->getTree(), false );
    _vc->buildFriendTree( _datasets[0]->getTree(), false );
  }  

  // define and book all outputs
  defineOutput();
  //copy the histograms for the different workflows
  addWorkflowHistos();

  // loop over given samples
  for(unsigned int i=0; i<_numDS; ++i){

    // open file
    _sampleName = _datasets[i]->getName();
    if(_byPassDsName!="" && _byPassDsName!=_sampleName) {
      cout<<" skipping the dataset : "<<_sampleName<<endl;
      continue;
    }
      
    _inds = i;
    _isData = _datasets[i]->isPPcolDataset();
  
    _vc->reset();
    _vc->buildTree( _datasets[i]->getTree() , _skim&&_fullSkim );
    _vc->buildFriendTree( _datasets[i]->getTree() , _skim&&_fullSkim );
    //prepare skimmed file and tree
    if(_skim) {
      initSkimming();
    }
	
    // loop over entries
    _nEvts[i] = _datasets[i]->getNEvents();
    _nEvtsDs[i] = _nEvts[i];
    if(_nEvtMax != (unsigned long int)-1) _nEvts[i] =  min(_nEvtMax+_nSkip,_nEvts[i]);
    _maxEvts = _nEvts[i];   
    cout<<" Processing dataset : "<<_sampleName<<"  (running on "<<_nEvts[i]<<" events)"<<endl;

    //FIXME MM
    // if(_sampleName=="DYJetsToLL_M50") {
    //   _corruptedSample=true;
    //   _corrSample.push_back( make_pair() );
    //   _corrSample.push_back( make_pair() );
    //   _corrSample.push_back( make_pair() );
    // }


    if(_nSkip!=0)
      cout<<" Skipping "<<_nSkip<<" first events "<<endl;
    boost::progress_display show_progress( _nEvts[i]-_nSkip );
    //bool validEvent=true;
    for(_ie = _nSkip; _ie < _nEvts[i]; ++_ie) {
      ++show_progress;
      stw.Start();
     
      if(_ie>=0) {//negative event for converter
	// if(_corruptedSample) {
	//   validEvent=true;
	  // for(unsigned_int ic=0;ic<_corrSample.size();ic++) {
	  //   if(_ie>=_corrSample[ic].first && _ie<=_corrSample[ic].second)
	  //     {validEvent=false; break;}
	  // }
	//   if(!validEvent) continue;
	// }


	//reinitialization
	_weight = 1.;
	_wBack = _weight;
	_uncId = false;
	_unc = "";//reinitialization
	_uDir=SystUtils::kNone;
	_au->setUncSrc("", SystUtils::kNone );
	_curWF = -100;//default workflow, all counters triggered 
	_au->setCurrentWorkflow(_curWF);

	// get tree entry, i.e. load branches
	_vc->setEvent(_ie);
	if(_skim||_fullSkim) {
	  _datasets[i]->getTree()->GetEntry(_ie);
	}
      } //negative event for converter
      
      if(!_systVarOnly || _systSource=="") {
	// get event weight, PU reweight it if needed 
	modifyWeight();
	
	// do something at every entry	
	run();
      }

      //alternate workflows for uncertainty sources
      for(size_t iu=0;iu<_uncSrcs.size();iu++) {
	//update the workflow
	_curWF = -100;
	_weight = _wBack;
	_uncId = true;
	_unc = _uncSrcs[iu];
	_uDir = _uncDirs[iu];
	_au->setCurrentWorkflow(_curWF);
	_au->setUncSrc(_unc, _uDir );
	  
	modifyWeight();
	if(iu==0) _vc->nextEvent();
	else _vc->sameEvent();
	applySystVar( _vc->_su->getSystInfos(_unc, _uDir) );
	run();
	_vc->backPortAllVars();
      }

      //destroy old Candidate pointers ======
      Candidate::reset();
      ObjectStore::clear();
      //===========================

      timeWall+=stw.RealTime();
      timeCPU+=stw.CpuTime();
      nE++;   
    }

    //write skimmed file
    if(_skim) {
      finalizeSkimming();
    }
		
    //cleaning memory
    _datasets[i]->freeMemory();
 
  } //datasets


  cout<<" +++ Execution frequency +++ "<<endl;
  cout<<"   Real time = "<<timeWall/nE<<" s/evt "<<"->"<<nE/timeWall<<" Hz"<<endl;
  cout<<"   CPU time = "<<timeCPU/nE<<" s/evt "<<"->"<<nE/timeCPU<<" Hz"<<endl<<endl;

  // write all outputs to disk
  internalWriteOutput();

  if(_summary)
    _au->printNumbers(std::cout);
  
  //summary backup
  writeSummary();
  
}

void
MPAF::writeSummary() {
  string dirname_ =  (string)(getenv("MPAF")) + "/workdir/summary/" + _className;
  FILE* test = fopen( dirname_.c_str(), "r" );
  if( test == 0 ) {
    string command_ = "mkdir -p " + dirname_; 
    assert( system( command_.c_str() ) == 0 );
  }
  else
    fclose( test );

  string ofilename_ = dirname_ + "/" + _cfgName + _postfix + ".txt";
  test = fopen( ofilename_.c_str(), "r" );
  if( test != 0 )	{
    fclose( test );
    TDatime datime_;
    cout << "File " << ofilename_ << " already exists, save it." << endl;
    string command_ = "mv " + ofilename_ + " " + ofilename_ + "_"; 
    ostringstream os;
    os << datime_.Get();
    command_ += os.str();
    assert( system( command_.c_str() ) == 0 );
  }
  ofstream ofile( ofilename_.c_str(), ios::out | ios::trunc );
  if(!ofile) {
    cout << "Error writing stat file " << endl; 
    return;
  }
  _au->printNumbers(ofile);
}

//____________________________________________________________________________
void MPAF::loadConfigurationFile(std::string cfg){
  /*
    loads the configuration file and reads the configuration variables
    parameters: configuratoin_file (path to the configuration file)
    return: none
  */

  _inputVars = Parser::parseFile(cfg);
  //_nEvtMax = -1;
  string tName;
  vector<vector<string> > _friends;
  
  for(MIPar::const_iterator it=_inputVars.begin(); 
      it!=_inputVars.end();it++) {

    if(it->second.type==Parser::kAN) {
      _className = it->second.val;
    }
    if(it->second.type==Parser::kDir) {
      _inputPath=it->second.val;
    }
    if(it->second.type==Parser::kVbs) {
      _verb=atoi(it->second.val.c_str());
    }
    if(it->second.type==Parser::kSkim) {
      _skim    = true;
      _fullSkim= true;
      if(it->second.val=="Limited") _fullSkim=false;
      if(it->second.val=="Friend") _friendSkim=true;
    }
    if(it->second.type==Parser::kNMax) {
      _nEvtMax = atoi(it->second.val.c_str());
    }
    if(it->second.type==Parser::kSkip) {
      _nSkip = atoi(it->second.val.c_str());
    }
    if(it->second.type==Parser::kTree) {
      tName = it->second.val;
    }
    if(it->second.type==Parser::kHisto) {
      _hname = it->second.val;
    }
    if(it->second.type==Parser::kWgtHisto) {
      _hwgtname = it->second.val;
    }
    if(it->second.type==Parser::kFT){
      vector<string> friendT=Tools::split(it->second.val, ':');
      _friends.push_back(friendT);
    }
    if(it->second.type==Parser::kSummary){
      _summary = atoi(it->second.val.c_str());
    }
    if(it->second.type==Parser::kSyst){
      _systVarOnly=true;
      size_t p=it->second.val.find(":");
      if(p==string::npos) {
	_systSource = it->second.val;
	continue;
      }
      
      _systSource = it->second.val.substr(0,p);
      _systDir = SystUtils::kNone;
      if(it->second.val.substr(p+1)!="")
	_systDir=((it->second.val.substr(p+1)=="Up")?SystUtils::kUp:SystUtils::kDown);
    }
    if(it->second.type==Parser::kCounter){
      
      bool cnt=false;
      string singlecnt="";

      if(it->second.val=="0" || it->second.val=="1") {
	cnt= 1-atoi(it->second.val.c_str());
      } else {
	singlecnt=it->second.val;
      }
   
      _au->setCounterOption(cnt, singlecnt);
    }
    if(it->second.type==Parser::kPfx) {
      _postfix="_"+it->second.val;
    }
    
  }

  //datasets
  for(MIPar::const_iterator it=_inputVars.begin(); 
      it!=_inputVars.end();it++) {

    string dsName="";
    string dirName="";
    // if(_byPassDsName!="") {
    //   if(_datasets.size()!=0) continue;
    //   vector<string> vals=Tools::split(_byPassDsName,':');
    //   if(vals.size()==2)
    // 	dirName=vals[0];
    //   dsName=vals.back();    
    // }
    // else {
    if(it->second.type!=Parser::kDS) continue;
    dsName=it->second.val;
    //}
   
    string pfx="";
    bool absdir=false;
    vector<vector<string> > friends;
    vector<string> opts=(_byPassDsName!="")?(vector<string>(0,"")):it->second.opts;
    vector<string> links;
    if(opts.size()!=0) {
      for(size_t i=0;i<opts.size();i++) {
	if(opts[i].substr(0,4)=="pfx:") {
	  pfx=opts[i].substr(4, opts[i].size()-4 );
	}
        if(opts[i].substr(0,4)=="dir:") {
          dirName=opts[i].substr(4, opts[i].size()-4 );
        }
        if(opts[i].substr(0,7)=="absdir:") {
          dirName=opts[i].substr(7, opts[i].size()-7 );
          absdir=true;
        }
	if(opts[i].substr(0,3)=="ft:"){
	  vector<string> friendT=Tools::split(opts[i].substr(3, opts[i].size()-3), ':');
	  friends.push_back(friendT);
	} 
	if(opts[i].substr(0,5)=="link:") {
	  links=Tools::split(opts[i].substr(5, opts[i].size()-5), '|');
        }
      }
    }
    //adding postfix
    dsName+=pfx;

    _datasets.push_back(new Dataset(dsName));
    _nEvtsDs.push_back(0);
    _nEvts.push_back(0);
    
    SampleId sId;
    sId.name =(_byPassDsName!="")?dsName:it->second.val; //was val
    sId.cr = "";
    sId.dd =false;
    sId.norm = -1; 
    
    for (size_t ft=0; ft<_friends.size();ft++) {
      _datasets.back()->addFriend(_friends[ft]); 
    }

    for (size_t ft=0; ft<friends.size();ft++) {
      _datasets.back()->addFriend(friends[ft]);
    }

    //links
    linking(_datasets.back(), links, dirName);
    _datasets.back()->setTotNProcEvents(_inputPath, dirName, "data", _hname);
    _datasets.back()->setTotSumProcWgts(_inputPath, dirName, "data", _hwgtname);

    if(!absdir)
      _datasets.back()->addSample(sId, _inputPath, dirName, tName, _hname, _hwgtname, 1.0, 1.0, 1.0, 1.0);
    else
      _datasets.back()->addSample(sId, "://"+dirName, "", tName, _hname, _hwgtname, 1.0, 1.0, 1.0, 1.0);
    
    _au->addDataset( dsName );
  }


  _au->init();


  // _postfix = getCfgVarS("postfix","");
  // if(_postfix!="") _postfix="_"+_postfix;
}


string
MPAF::getCfgVarS(string n, string def) {
  MIPar::const_iterator it;
  it=_inputVars.find(n);
  if(it==_inputVars.end()) return def;
  return _inputVars[n].opts[0];
}

int
MPAF::getCfgVarI(string n, int def) {
  MIPar::const_iterator it;
  it=_inputVars.find(n);
  if(it==_inputVars.end()) return def;
  return atoi(getCfgVarS(n, "").c_str() );
}

float
MPAF::getCfgVarF(string n, float def) {
  MIPar::const_iterator it;
  it=_inputVars.find(n);
  if(it==_inputVars.end()) return def;
  return atof(getCfgVarS(n, "").c_str() );
}

void
MPAF::linking(Dataset* ds, const vector<string>& links, const string& dirName) {

  for(size_t il=0;il<links.size();il++) {
    string path=string(getenv("MPAF"))+"/workdir/data/"+_inputPath;
    if(dirName.size()>0) path=string(getenv("MPAF"))+"/workdir/"+dirName+"/"+_inputPath;
    if(_inputPath.substr(0,5)=="/pnfs") path=_inputPath;

    string out="";
    string outURL="";
    string prefix="";
    if(_inputPath.find("eos")!=string::npos) {
      out=Tools::getCmdOutput("eos ls "+_inputPath+"/"+links[il]+".root");
      //prefix=_inputPath+"/";
      path="";
    } else {
      out=Tools::getCmdOutput("ls "+path+"/"+links[il]+".root 2>&1");
      outURL=Tools::getCmdOutput("ls "+path+"/"+links[il]+".root.url 2>&1");
    }

    bool validLS=out.find("No such file")==string::npos;
    bool validURLLS=outURL.find("No such file")==string::npos;

    if(validLS) {
      validLS=out.find("impossible d")==string::npos;
    }
    if(validURLLS) {
      validURLLS=outURL.find("impossible d")==string::npos;
    }

    vector<string> intLinks=Tools::explodeString(out,".root");
    vector<string> intLinksURL=Tools::explodeString(outURL,".root.url");
    for(unsigned int is=0;is<intLinks.size();is++) {
      if(!validLS) continue;
      if(intLinks[is]=="") continue;
      //cout<<prefix+intLinks[is]<<"  <>  "<<path<<endl;
      ds->addLink( (prefix+intLinks[is]).substr(path.size()) );
    }
    
    for(unsigned int isu=0;isu<intLinksURL.size();isu++) {
      if(!validURLLS) continue;
      if(intLinksURL[isu]=="") continue;
      for(unsigned int is=0;is<intLinks.size();is++) {
	if(!validLS) continue;
	if(intLinks[is]=="") continue;
	if(intLinksURL[isu]==intLinks[is]) continue; //giving priority to non url files
      }
      ds->addLink( (prefix+intLinksURL[isu]).substr(path.size()) );
    }

  }

}


//____________________________________________________________________________
void MPAF::setConfigName(std::string cfg){
  /*
    saves the name of the configuration
    parameters: configuration_file
    return: none
  */

  size_t p = cfg.find_last_of("/");
  size_t q = cfg.find(".cfg");

  _cfgName = cfg.substr(p+1, q-p-1);

}


//____________________________________________________________________________
void MPAF::configure(std::string cfg){
  /*
    starts MPAF, i.e. loads the configuration file, checks the configuration,
    loads and sets some variables and prepares the output structure
    parameters: configuration_file (path to the configuration file)
    return: none
  */
  
  setConfigName(cfg);
  loadConfigurationFile(cfg);
  
  std::vector<std::string> dsNames;
  for(unsigned int i=0; i<_datasets.size(); ++i) {
    dsNames.push_back(_datasets[i]->getName());
  }

  _hm->configAnalysis( dsNames );

}





/*****************************************************************************
******************************************************************************
** PLACEHOLDERS AND FUNCTIONS TO BE USED BY SUB CLASSES                     **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
void MPAF::run(){
  /*
    placeholder for running the analysis, performing the event selection and
    filling histograms per tree entry
    parameters: none
    return: none
  */

}

void MPAF::internalWriteOutput() {

  writeOutput();

  map<string, int> cnts;
  map<string, double> wgtcnts;
  for(unsigned int ids=0;ids<_datasets.size(); ++ids) {
    if(_byPassDsName!="" && _datasets[ids]->getName()!=_byPassDsName)
      continue;
    float fact=1;
    if(_nEvts[ids]!=0 && _nEvtsDs[ids]!=0)
      fact=(float)_nEvts[ids]/_nEvtsDs[ids];
    if(_nSkip!=0)
      fact*=(_nEvts[ids]-_nSkip)/(float)_nEvts[ids];
    //cout<<ids<<"  "<<_datasets[ids]->getName()<<"  "<< _datasets[ids]<<" -->> "<<fact<<"  "<<_datasets[ids]->getNProcEvents()<<"  "<<_datasets[ids]->getSumProcWgts()<<" -->>  "<<_nEvts[ids]<<"  "<<_nEvtsDs[ids]<<endl;
    cnts[ _datasets[ids]->getName() ] = _datasets[ids]->getNProcEvents() * fact;
    wgtcnts[ _datasets[ids]->getName() ] = _datasets[ids]->getSumProcWgts() * fact;
  }

  cout << "writing output to disk" << endl;
  if(_byPassDsName!="") _postfix+="_"+_byPassDsName;
  _hm->saveHistos (_className, _cfgName+_postfix, cnts, wgtcnts, _byPassDsName);
  _au->saveNumbers(_className, _cfgName+_postfix, cnts, wgtcnts, _byPassDsName);


}


/*****************************************************************************
******************************************************************************
** INTERFACE TO HISTOGRAM MANAGER                                           **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
void MPAF::fill(string var, float valx, float weight) {
  /*
    fills a histogram (var) with a value (valx) that has a weight (weight)
    parameters: var, valx, weight
    return: none
  */
  const hObs* obs = _hm->getHObs(var);
  
  if(obs->IsGlobal()) {  
    
    // IF HISTOGRAM IS GLOBAL DO AS USUAL:
    if(!_uncId) { //central value
      if(_curWF!=-100) { //single workflow
	if(!obs->isRelevant(_wfNames[_curWF])) return;
	_hm->fill( var+_wfNames[_curWF], _inds, valx, weight );
      }
      else { //multiple workflows
	for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
	  if(!obs->isRelevant(_itWF->second)) continue;
	  _hm->fill( var+_itWF->second, _inds, valx, weight );
	}
      }
      
    }
    else { //uncertainties
      string uvar=(_uDir==SystUtils::kUp)?("Up"):("Do");
      if(_curWF!=-100) { //single workflow
	if(!obs->isRelevant(_wfNames[_curWF])) return;
	_hm->fill( var+_wfNames[_curWF], _inds, _unc, valx, weight,uvar);
      } else {
	for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
	  if(!obs->isRelevant(_itWF->second)) continue;
	  _hm->fill( var+_itWF->second, _inds, _unc, valx, weight,uvar);
	}
      }
    }
  }
  else {  //for local HISTOS
    if(!_uncId) { //central value
      _hm->fill( var, _inds, valx, weight );
    }
    else {
      if(_uDir==SystUtils::kUp)
	_hm->fill( var, _inds, _unc, valx, weight,"Up");
      //fillUnc(var,_unc,valx,weight,"Up");
      if(_uDir==SystUtils::kDown)
	_hm->fill( var, _inds, _unc, valx, weight,"Do");
    }
  }

}


//____________________________________________________________________________
void MPAF::fill(string var, float valx, float valy, float weight) {
  /*
    fills a histogram (var) with values (valx, valy) that have a weight (weight)
    parameters: var, valx, valy, weight
    return: none
  */
  const hObs* obs = _hm->getHObs(var);
  
  if(obs->IsGlobal()) {  
    // IF HISTOGRAM IS GLOBAL DO AS USUAL:
    if(_curWF!=-100) { //single workflow
      if(!obs->isRelevant(_wfNames[_curWF])) return;
    _hm->fill( var+_wfNames[_curWF], _inds, valx, valy, weight );
    }
    else { //multiple workflows
      for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
	if(!obs->isRelevant(_itWF->second)) continue;
	_hm->fill( var+_itWF->second, _inds, valx, valy, weight );
      }
    }
  }
  else {
    // IF HISTOGRAM IS GLOBAL DO AS USUAL:
    _hm->fill( var, _inds, valx, valy, weight );
  }
}


//____________________________________________________________________________
void MPAF::fillUnc(string var, string unc, float val, float weight, string dir) {
  /*
    ??
    parameters: 
    return: 
  */

  if(_isData) return;

  if(_curWF!=-100) { //single workflow
    _hm->fill( var+_wfNames[_curWF], _inds, unc, val, weight,dir);
  }
  else { //multiple workflows
    for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
      _hm->fill( var+_itWF->second, _inds, unc, val, weight,dir);
    }
  }
}


//____________________________________________________________________________
void MPAF::fillUnc(string var, string unc, float val, float weight, float wup, float wdo) {
  /*
    ??
    parameters: 
    return: 
  */

  fill(var, _inds, val, weight);

    //_hm->fill(var, _inds, val, weight );

  if(!_isData ) {
    fillUnc( var, unc, val, wup, "Up");
    fillUnc( var, unc, val, wup, "Do");
    // _hm->fill( var, unc, val, wup, "Up");
    // _hm->fill( var, unc, val, wdo, "Do");
  }
}





/*****************************************************************************
******************************************************************************
** INTERFACE TO DATABASE MANAGER                                            **
******************************************************************************
*****************************************************************************/

//____________________________________________________________________________
float MPAF::getDBVal(string db, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10) {
  /*
    ??
    parameters: 
    return: 
  */
  
  if(!_uncId)
    return _dbm->getDBValue( db, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 );
  //MM fixme
  // else
  //   return applySystDBVar( _vc->_su->getSystInfos(_unc, _uDir), db, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
  else
    return 0;
}


//____________________________________________________________________________
float MPAF::getDBErrL(string db, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10) {
  /*
    ??
    parameters: 
    return: 
  */

  return _dbm->getDBErrL( db, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 );

}


//____________________________________________________________________________
float MPAF::getDBErrH(string db, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10) {
  /*
    ??
    parameters: 
    return: 
  */

  return _dbm->getDBErrH(db, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 );

}


//____________________________________________________________________________
void MPAF::loadDb(string key, string dbfile, string hname) {
  /*
    ??
    parameters: 
    return: 
  */

  // ASCII database per definition
  if(hname == "") 
    _dbm->loadDb(key, dbfile);
  else
    _dbm->loadDb(key, dbfile, hname);

}


//____________________________________________________________________________
bool MPAF::makeCut(bool decision, string cName, string type, int eCateg) {
  /*
    ??
    parameters: 
    return: 
  */
  return _au->makeCut(decision, _inds , cName, _weight, type, eCateg+_offsetWF, false);

}


//____________________________________________________________________________
void MPAF::counter(string cName, int eCateg) {
  /*
    ??
    parameters: 
    return: 
  */
  _au->makeCut(true, _inds , cName, _weight, "=", eCateg+_offsetWF, false);

}

void 
MPAF::setWorkflow(int wf) {
  _curWF=wf;
  _au->setCurrentWorkflow(wf);
}

void 
MPAF::setMultiWorkflow(vector<int> wf) {
  //_curWF ?? would need a full loop everywhere...
  _au->setMultiWorkflow(wf);
}

// skimming functions ======================================
// void
// MPAF::regBranchForSkimming(const string& brName) {
//   (TTree*)_datasets[_inds]->getTree()->SetBranchStatus(brName.c_str(),1);
//   if(_skimTree)
//     _skimTree->SetBranchStatus(brName.c_str(),1);
// }


void MPAF::initSkimming() {
  
  //string opath =string(getenv ("MPAF"))+"/workdir/skims"; //"/scratch/mmarionn/MPAFSkims";
  string machine=SystemUtils::exec("hostname -d");
  bool isPsi=(machine.find("psi")!=string::npos);
  string user=SystemUtils::exec("whoami");
  string opath = ((isPsi)?("/scratch/"+user):((string)(getenv ("MPAF"))+"/workdir/skims"));
  FILE* test = fopen( opath.c_str(), "r" ); 
  if( test == 0 ) {
    string command_ = "mkdir -p " + opath; 
    assert( system( command_.c_str() ) == 0 );
  }
  else
    fclose( test );

  _oFile = new TFile( (opath+"/"+_sampleName+".root").c_str(),"RECREATE");

  
  if(!_friendSkim) {
    _skimTree = (TTree*)_datasets[_inds]->getTree()->CloneTree(0);
    _vc->linkFriendBranches(_skimTree);
  }
  else {
    //_datasets[_inds]->getTree()->LoadTree(0);
    _oFile->mkdir("sf/");
    _skimTree = new TTree("t","friend tree");
  }

  _hnSkim =new TH1I( _hname.c_str(), _hname.c_str(), 1, 0, 1);
  _hnSkim->SetBinContent(1,_datasets[_inds]->getNProcEvents() );
  
  _hnwSkim =new TH1D( _hwgtname.c_str(), _hwgtname.c_str(), 1, 0, 1);
  _hnwSkim->SetBinContent(1,_datasets[_inds]->getSumProcWgts() );

  modifySkimming();

}

void MPAF::finalizeSkimming() {


  cout<<" skim done : "<<_skimTree->GetEntries()
      <<" events selected over "<<_nEvts[_inds]<<" events"<<endl;

  _oFile->cd();
  if(_skimTree->GetListOfFriends()) {
    TObjLink *lnk = _skimTree->GetListOfFriends()->FirstLink();
    vector<string> fts;
    while(lnk) {
      fts.push_back( (string)lnk->GetObject()->GetName() );
      lnk = lnk->Next(); 
    }
    
    for(size_t i=0;i<fts.size();i++) {
      _skimTree->RemoveFriend((TTree*)_skimTree->GetTree()->GetFriend(fts[i].c_str()));
    }
  }

  if(_hnSkim!=nullptr)
    _hnSkim->Write();
  if(_hnwSkim!=nullptr)
    _hnwSkim->Write();
  _oFile->Write();
  _oFile->Close();

  //copy file to T3
  string machine=SystemUtils::exec("hostname -d");
  if(machine.find("psi")==string::npos) return;

  string user=SystemUtils::exec("whoami");
  string ofName=" srm://t3se01.psi.ch:8443/srm/managerv2?SFN=/pnfs/psi.ch/cms/trivcat/store/user/"+user+"/MPAFskims/"+_className+"/"+_sampleName+".root";
 
  //string rmCommand=""

  string cpCommand="lcg-cp -b -D srmv2 "+(string)(_oFile->GetName())+ofName;
  system( cpCommand.c_str() );

  //removal of file
  //system( ("rm "+(string)(_oFile->GetName())).c_str() );
  
}


// void
// MPAF::cloneSkimBranch(const string& name) {

  
  
//   _skimTree->Branch( name.c_str(), val );
  
// }

// Workflow functions =======================================

void
MPAF::addWorkflow(int wfid, string wfName) {

  _wfNames[wfid] = wfName;
  _au->addWorkflow(wfid, wfName);
} 

void
MPAF::addWorkflowHistos() {

  if(_wfNames.size()==1) return;

  vector<string> obss = _hm->getObservables(true);
  
  for(unsigned int io=0;io<obss.size();io++) {
    const hObs* obs = _hm->getHObs(obss[io]);
    bool prof = obs->htype.find("P")!=string::npos;
    bool is2D = obs->htype.find("2D")!=string::npos;

    if(!obs->IsGlobal()) continue;  // don't declare histo if it's not declared as global
    
    for(_itWF=_wfNames.begin(); _itWF!=_wfNames.end(); ++_itWF) {
      if(_itWF->second=="") continue; //protection for global histo
      if(!obs->isRelevant(_itWF->second) ) continue; //no need to store all histograms!
      // cout<<obs->name+_itWF->second<<"  "<<obs<<endl;
      // cout<<obs->hs[0]<<endl;
      //"  "<<obs->hs[0]<<"  "<<obs->type<<endl;
      _hm->addVariableFromTemplate( obs->name+_itWF->second, obs->hs[0], prof, is2D, obs->type );
    }
  }  
}


// systematic uncertainties functions =======================

void
MPAF::addManualSystSource(string name, int dir) {

  if(_systVarOnly && _systSource!=name) return;
  if(_systVarOnly && _systDir==SystUtils::kUp && dir==SystUtils::kDown) return;
  if(_systVarOnly && _systDir==SystUtils::kDown && dir==SystUtils::kUp) return;
  if(_systVarOnly && dir==SystUtils::kNone) dir=_systDir;

  //everything has to be done by hand
  addWSystSource(name, dir, "+", 0); 
}

void
MPAF::addWSystSource(string name, int dir, string type, float val) {
  vector<string> t;
  addSystSource(name, dir, type, t, val, true);
}

void
MPAF::addWSystSource(string name, int dir, string type, string db, string hname) {
  vector<string> t;
  addSystSource(name, dir, type, t, db, hname, true);
}

void
MPAF::addSystSource(string name, int dir, string type, vector<string> modVar,
			     float val, bool wUnc) {

  _au->addAutoWorkflow( "Unc"+name+"Up");
  _au->addAutoWorkflow( "Unc"+name+"Do");
  _uType[ name ] = wUnc;

  if(_systVarOnly && _systSource!=name) return;
  if(_systVarOnly && _systDir==SystUtils::kUp && dir==SystUtils::kDown) return;
  if(_systVarOnly && _systDir==SystUtils::kDown && dir==SystUtils::kUp) return;

  //check the direction
  if(dir!=SystUtils::kNone) {
    _uncSrcs.push_back(name);
    _uncDirs.push_back(dir);
    _vc->_su->addSystSource(name, dir, type, modVar, val);
  }
  else {
    //up variation
    _uncSrcs.push_back(name);
    _uncDirs.push_back(SystUtils::kUp);
    _vc->_su->addSystSource(name, SystUtils::kUp, type, modVar, val);

    //down variation
    _uncSrcs.push_back(name);
    _uncDirs.push_back(SystUtils::kDown);
    _vc->_su->addSystSource(name, SystUtils::kDown, type, modVar, val);
  }

}

void
MPAF::addSystSource(string name, int dir, string type, vector<string> modVar,
		    string db, string hname, bool wUnc) {
  
  _au->addAutoWorkflow( "Unc"+name+"Up");
  _au->addAutoWorkflow( "Unc"+name+"Do");
  _uType[ name ] = wUnc;

  if(_systVarOnly && _systSource!=name) return;
  if(_systVarOnly && _systDir==SystUtils::kUp && dir==SystUtils::kDown) return;
  if(_systVarOnly && _systDir==SystUtils::kDown && dir==SystUtils::kUp) return;

  //check the direction
  if(dir!=SystUtils::kNone) {
    _uncSrcs.push_back(name);
    _uncDirs.push_back(dir);
    _vc->_su->addSystSource(name, dir, type, modVar, db, hname);
  }
  else {
    //up variation
    _uncSrcs.push_back(name);
    _uncDirs.push_back(SystUtils::kUp);
    _vc->_su->addSystSource(name, SystUtils::kUp, type, modVar, db, hname);
    
    //down variation
    _uncSrcs.push_back(name);
    _uncDirs.push_back(SystUtils::kDown);
    _vc->_su->addSystSource(name, SystUtils::kDown, type, modVar, db, hname);
  }

}



void
MPAF::applySystVar(SystST s) {

  //weight variation, MM: incomplete ===========================
  // if(_uType[ _unc ]) {
  //   if(s.val!=-100) {
  //     //fixed variation
  //     SystUtils::systOp<float>(_unc, _uDir, s.type, _weight,  s.val );
  //   }  
  //   else {
  //     //db variation
  //     SystUtils::systOp<float>(_unc, _uDir, s.type, _weight, s.db, s.vars);
  //   }
  //   return;
  // }
  
  // variable variation =======================================
  if(s.val!=-100) {
    //fixed variation
    for(size_t iv=0;iv<s.modVar.size();iv++) //loop over variables
      _vc->applySystVar(_unc, _uDir, s.modVar[iv], s.val, s.type);
  }
  else {
    //db variation
    for(size_t iv=0;iv<s.modVar.size();iv++) //loop over variables
      _vc->applySystVar(_unc, _uDir, s.modVar[iv], s.vars, s.specVars, s.db, s.type);
  }

}


void
MPAF::print(const string& message, int verbose) {
  if(_verb>=verbose)
    cout<<message<<endl;
}
