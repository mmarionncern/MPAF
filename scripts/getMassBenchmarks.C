{

  TFile* file=new TFile("/home/mmarionn/Documents/CMS/MPAF/workdir/data/test/test.root");
  TTree* tree=(TTree*)file->Get("tree");
  
  int M1,M2;

  tree->SetBranchStatus("*",0);
  
  tree->SetBranchStatus("GenSusyMScan1",1);
  tree->SetBranchStatus("GenSusyMScan2",1);

  tree->SetBranchAddress("GenSusyMScan1",&M1);
  tree->SetBranchAddress("GenSusyMScan2",&M2);

  set<string> vals;
  string s;
  for(int ie=0;ie<tree->GetEntries();ie++) {
    tree->GetEntry(ie);
    
    ostringstream os,os1;
    os<<M1;
    os1<<M2;
    s="-"+os.str()+"-"+os1.str()+"-";

    if(vals.find(s)==vals.end() )
      vals.insert(s);
  }
  
  ofstream ofile("massT1ttt.txt", ios::out | ios::trunc);

  for(set<string>::const_iterator it=vals.begin(); it!=vals.end(); it++) {
    cout<<(*it)<<endl;
    ofile<<(*it)<<endl;
  }
  ofile.close();
  
}
