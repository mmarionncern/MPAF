#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include <TFile.h>
#include <TH2F.h>



class HLTEfficiency{
  
public:

  HLTEfficiency(std::string filename="HLT_Efficiencies_4fb_2016.root");
  
  ~HLTEfficiency();


  float getEfficiency(float pt1, float eta1, int pdgId1,
		      float pt2, float eta2, int pdgId2, 
		      float ht, int var=0);
  float getEfficiencyRA7(float pt1, float eta1, int pdgId1,
			 float pt2, float eta2, int pdgId2, 
			 float pt3, float eta3, int pdgId3, 
			 float ht, int var);

private:

  void loadFile();

  float getSingleEfficiency(float pt, float eta, int hlttag, int var);

  float getBinContent(float x, float y, TH2F* h);


private:

  enum {kElLeg1, kElLeg2, kElXTLeg1, kElXTLeg2, kElHTLeg, kElHTXTLeg,
	kMuLeg1, kMuLeg2, kMuXTLeg1, kMuXTLeg2, kMuHTLeg, kMuHTXTLeg };
  
  bool _initHistos;


  //TH2F* _hist_HLT_DiEle_DZ;
  TH2F* _hist_HLT_DiEle_Leg1;
  TH2F* _hist_HLT_DiEle_Leg2;
  TH2F* _hist_HLT_EleMu_Leg1;
  TH2F* _hist_HLT_MuEle_Leg2;
  TH2F* _hist_HLT_DiEleHT_Leg;
  TH2F* _hist_HLT_EleMuHT_Leg1;
  TH2F* _hist_HLT_DiMu_Leg1;
  TH2F* _hist_HLT_DiMu_Leg2;
  TH2F* _hist_HLT_MuEle_Leg1;
  TH2F* _hist_HLT_EleMu_Leg2;
  TH2F* _hist_HLT_DiMuHT_Leg;
  TH2F* _hist_HLT_EleMuHT_Leg2;

  TFile* _file;
  std::string _fileName;

};
