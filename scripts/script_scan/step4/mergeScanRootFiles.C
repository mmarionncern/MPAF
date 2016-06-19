#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>

#include "TError.h"
#include "TFile.h"
#include "TF1.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TKey.h"


void mergeScanRootFiles(/*vector<string> tks/*string files,*/ string ofileName="/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/merged_2fb.root"){

//past string here
//compile: .L step4/mergeScanRootFile.C+

vector<string> tks; tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/merged_2fb.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_DoubleEG_Run2016B_PromptReco_v2_runs_271036_274421.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_DoubleMuon_Run2016B_PromptReco_v2_runs_271036_274421.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_DYJetsToLL_M10to50.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_DYJetsToLL_M50.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_GGHZZ4L.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_MuonEG_Run2016B_PromptReco_v2_runs_271036_274421.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_TGJets.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_TTGJets.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_TTHnobb_pow.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_TTJets.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_TTLLJets_m1to10.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_TTTT.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_TTWToLNu.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_TTZToLLNuNu.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_tZq_ll.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_VHToNonbb.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_WGToLNuG.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_WJetsToLNu.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_WWZ.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_WZTo3LNu.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_ZGTo2LG.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_ZZTo4L.root"); tks.push_back("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/root/SUSY3L/3l_scanBkg_ZZZ.root");


  // istringstream iss(files);
  // vector<string> tks;
  // copy(istream_iterator<string>(iss),
  //      istream_iterator<string>(),
  //      back_inserter<vector<string> >(tks));

  TFile* ofile=new TFile(ofileName.c_str(),"recreate");
  ofile->mkdir("nEvtProc");
  ofile->mkdir("sumWgtProc");

  for(int it=0;it<tks.size();it++) {
    cout<<tks[it]<<"   "<<it<<"/"<<tks.size()<<endl;
    TFile* f=new TFile(tks[it].c_str(), "read");
  
    TIter nextkey(f->GetListOfKeys());
    TKey *key;
    while ((key = ((TKey*)nextkey()))) {
      TObject* obj = key->ReadObj(); 
      //found a TDirectory which can be a variable
      if( (string)obj->IsA()->GetName()!=("TDirectoryFile") ) continue;
      
      string varName(obj->GetName());
      if(varName!="nEvtProc" && varName!="sumWgtProc") continue;

      TIter nextkeyD( ((TDirectory*)obj)->GetListOfKeys() );
      TKey *keyD;
      while ((keyD = ((TKey*)nextkeyD()))) {
	TObject* objD = keyD->ReadObj(); 
	if( objD==nullptr ) continue;
	
	TH1* htmp=(TH1*)((TH1*)objD->Clone());
	
	ofile->cd(varName.c_str());
	htmp->Write();

      }//samples

      // break;//no nee to run over everything if the nevtproc is found
    }//tdirectory
  }//files

  ofile->Close();
 gROOT->ProcessLine(".qqqqqqqqqqqqqqqqqqqqq");
}
