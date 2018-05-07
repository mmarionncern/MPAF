/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, Matthieu Marionneau                                **
** CERN, Fall 2014                                                          **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "analysis/src/AnalysisFactory.hh"

using namespace std;

//_____________________________________________________________________________________
void printUsageAndExit(){


  std::cout << "printing usage" << std::endl;
  exit(1);

}


//_____________________________________________________________________________________
int main(int argc, char* argv[]) {
  /*
    main function, which does the whole job
    parameters: argument list given to the executable
    return: none
  */

  // Starting MPAF

  std::cout << ">> STARTING MPAF" << std::endl;



  // Getting Configuration File Path

  std::string cfg = "";
  char ch;
  unsigned long int nMax=-1;
  unsigned long int nSkip=0;
  std::string dsName = "";

  while ((ch = getopt(argc, argv, "c:n:k:d:h:?")) != -1 ) {
    switch (ch) {
    case 'c': cfg = optarg; break;
    case 'n': nMax = strtoul(optarg,nullptr,0); break;
    case 'k': nSkip = strtoul(optarg,nullptr,0); break;
    case 'd': dsName = optarg; break;
    case '?':
    case 'h': printUsageAndExit(); break;
    default : printUsageAndExit();
    }
  }

  // Checking Number of Arguments
  if(argc < 2) printUsageAndExit();
  
  
  // Reading cfg file and get classes to run on
  vector<string> ans;

  MIPar inputVars = Parser::parseFile(cfg);
  for(MIPar::const_iterator it=inputVars.begin(); 
      it!=inputVars.end();it++) {


    if(it->second.type==Parser::kNMax && nMax==(unsigned int)-1) {
      nMax = atoi(it->second.val.c_str());
    }
    if(it->second.type==Parser::kSkip && nSkip==(unsigned int)-1) {
      nSkip = atoi(it->second.val.c_str());
    }
    if(it->second.type!=Parser::kAN) continue;
    //cout<<it->second.val<<endl;
    ans.push_back(it->second.val);
    vector<string> opts= it->second.opts;
    for(size_t i=0;i<opts.size();i++)
      ans.push_back( opts[i] );
  }


  // Running the Classes
  for(unsigned int i = 0; i < ans.size(); ++i) {
   
    MPAF* ac = AnalysisFactory::get(ans[i], cfg);
    if(ac==nullptr) {
      cout<<"Error, no analysis "<<ans[i]<<" available, please check your config file and the declaration of the analysis"<<endl;
      abort();
    }
    ac->setNMax(nMax);
    ac->setNSkip(nSkip);
    ac->setDS(dsName);
    ac->analyze();

    delete ac;
  
  }
  
  // Closing MPAF
  std::cout << std::endl << ">> CLOSING MPAF" << std::endl;

  
  // Return
  return 0;
}

