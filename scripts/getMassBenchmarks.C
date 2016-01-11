#include <set>
#include <TFile.h>
#include <TTree.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void getMassBenchmarks() {
  
  vector<string> fileNames;
  ifstream ifile("/afs/cern.ch/user/m/mmarionn/workspace/private/SUSY/filesScan", ios::in );
  string line;
  while(getline(ifile, line)) {
    fileNames.push_back(line);
  }

  ofstream ofile("massT1ttt.txt", ios::out | ios::trunc);
  set<string> vals;

  for(int i=0;i<fileNames.size();i++) {

    cout<<i<<"/"<<fileNames.size()<<endl;

    TFile* file=TFile::Open(fileNames[i].c_str() );
    TTree* tree=(TTree*)file->Get("tree");
    
    int M1,M2;
    
    tree->SetBranchStatus("*",0);
    
    tree->SetBranchStatus("GenSusyMScan1",1);
    tree->SetBranchStatus("GenSusyMScan2",1);
    
    tree->SetBranchAddress("GenSusyMScan1",&M1);
    tree->SetBranchAddress("GenSusyMScan2",&M2);
  
  
    string s;
    for(int ie=0;ie<tree->GetEntries();ie++) {
      tree->GetEntry(ie);
    
      ostringstream os,os1;
      os<<M1;
      os1<<M2;
      s="-"+os.str()+"-"+os1.str()+"-";

      if(vals.find(s)==vals.end() ) {
	vals.insert(s);
	cout<<s<<endl;
	ofile<<s<<endl;
      }
    }

    //delete tree;
    file->Close();
  }
  


  // for(set<string>::const_iterator it=vals.begin(); it!=vals.end(); it++) {
  //   cout<<(*it)<<endl;
  //   ofile<<(*it)<<endl;
  // }
  ofile.close();
  
}
