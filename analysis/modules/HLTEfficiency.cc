#include "analysis/modules/HLTEfficiency.hh"

HLTEfficiency::HLTEfficiency(std::string filename) {
  _initHistos=false;
  _fileName=filename;
  loadFile();
}
  
HLTEfficiency::~HLTEfficiency() {
  delete _hist_HLT_DiEle_Leg1;
  delete _hist_HLT_DiEle_Leg2;
  delete _hist_HLT_EleMu_Leg1;
  delete _hist_HLT_MuEle_Leg2;
  delete _hist_HLT_DiEleHT_Leg;
  delete _hist_HLT_EleMuHT_Leg1;
  delete _hist_HLT_DiMu_Leg1;
  delete _hist_HLT_DiMu_Leg2;
  delete _hist_HLT_MuEle_Leg1;
  delete _hist_HLT_EleMu_Leg2;
  delete _hist_HLT_DiMuHT_Leg;
  delete _hist_HLT_EleMuHT_Leg2;

  delete _file;
}


float 
HLTEfficiency::getEfficiency(float pt1, float eta1, int pdgId1,
			     float pt2, float eta2, int pdgId2, 
			     float ht, int var) {
    
  int flav=std::abs(pdgId1)+std::abs(pdgId2);
  bool isHTHLT=(ht>300);
  bool l1Lead=(pt1>pt2);

  int hltleg1=-1; 
  int hltleg2=-1;

  float totEff=1;

  switch(flav) {
  case 22: {
    hltleg1 = (isHTHLT)?( kElHTLeg ):( l1Lead?kElLeg1:kElLeg2 );
    hltleg2 = (isHTHLT)?( kElHTLeg ):( l1Lead?kElLeg2:kElLeg1 );
    //DZ efficiency correction
    totEff *= 0.995 + var*0.005;
    break;
  }
  case 24: {
    if(std::abs(pdgId1)==11) {
      hltleg1 = (isHTHLT)?( kElHTXTLeg ):( l1Lead?kElXTLeg1:kElXTLeg2 );
      hltleg2 = (isHTHLT)?( kMuHTXTLeg ):( l1Lead?kMuXTLeg2:kMuXTLeg1 );
    } else {
      hltleg1 = (isHTHLT)?( kMuHTXTLeg ):( l1Lead?kMuXTLeg1:kMuXTLeg2 );
      hltleg2 = (isHTHLT)?( kElHTXTLeg ):( l1Lead?kElXTLeg2:kElXTLeg1 );
    }
    break;
  }
  case 26: { 
    hltleg1 = (isHTHLT)?( kMuHTLeg ):( l1Lead?kMuLeg1:kMuLeg2 );
    hltleg2 = (isHTHLT)?( kMuHTLeg ):( l1Lead?kMuLeg2:kMuLeg1 );
    break;
  }
  }
    
  totEff *= getSingleEfficiency(pt1, eta1, hltleg1, var) * getSingleEfficiency(pt2, eta2, hltleg2, var );

  //L1 HT plateau efficiency
  //https://lathomas.web.cern.ch/lathomas/SUSYMultiLepton/TriggerEff/Results_7p65fb/l1htturnon.pdf
  if(isHTHLT) totEff *= 0.962 + var*0.01;
    
  //HLT HT efficiency correction for low pt leptons
  if(ht>300 && ht<325 && pt1<30 && pt2<30) {
    totEff *= 0.85 + var*0.05;
  }

  return std::min( (float)1.0,totEff);
}




float 
HLTEfficiency::getEfficiencyRA7(float pt1, float eta1, int pdgId1,
				float pt2, float eta2, int pdgId2, 
				float pt3, float eta3, int pdgId3, 
				float ht, int var) {
  
  //leptons are ordered before!
  
  int flav=std::abs(pdgId1)+std::abs(pdgId2);
  int flav3l=std::abs(pdgId1)+std::abs(pdgId2)+std::abs(pdgId3);
  
  int hltleg1=-1; 
  int hltleg2=-1;
  
  float totEff=1;

  if( ht>=400) return totEff*std::min(1., 1+ var*0.03);
  
  //bypass for specific cases
  switch(flav3l) {
  case 33: {
    if(pt1>25 && pt2>25 && pt3>15) return totEff*std::min(1., 1+ var*0.03); //diele
    else if(pt1>25 && pt2>15 && pt3>15) return totEff*getSingleEfficiency(pt1, eta1, kElLeg1, var); //diele, 1leg cor
    break;
  }
  case 35: {
    int isMu=(std::abs(pdgId1)==11?1:(std::abs(pdgId2)==11?2:3));
    if(isMu==1 && (pt1>25 && pt2>25 && pt3>15) ) return totEff*std::min(1., 1+ var*0.03); //muele +elemu trigger
    else if(isMu==1 && (pt1>25 && pt2>15 && pt3>15) ) return totEff*getSingleEfficiency(pt1, eta1, kMuXTLeg1, var); //muele only trigger, 1leg cor

    if(isMu==2 && (pt1>25 && pt2>25 && pt3>15) ) return totEff*std::min(1., 1+ var*0.03); //elemu + muele trigger
    else if(isMu==2 && (pt1>25 && pt2>10 && pt3>15) ) return totEff*getSingleEfficiency(pt1, eta1, kElXTLeg1, var); //elemu only trigger, 1leg cor -> should never happen

    if(isMu==3 && (pt1>25 && pt2>25 && pt3>10) ) return totEff*std::min(1., 1+ var*0.03); //case diele + eleMu trigger, 
    else if(isMu==3 && (pt1>25 && pt2>15 && pt3>10) ) return totEff*getSingleEfficiency(pt1, eta1, kElLeg1, var); //case diele + eleMu trigger,  1leg cor

    break;
  }
  case 37: {
    int isEl=(std::abs(pdgId1)==11?1:(std::abs(pdgId2)==11?2:3));
    if(isEl==1 && (pt1>25 && pt2>25 && pt3>10) ) return totEff*std::min(1., 1+ var*0.03); //elemu +muele trigger
    else if(isEl==1 && (pt1>25 && pt2>10 && pt3>10) ) return totEff*getSingleEfficiency(pt1, eta1, kElXTLeg1, var); //elemu only trigger, 1leg cor

    if(isEl==2 && (pt1>25 && pt2>25 && pt3>10) ) return totEff*std::min(1., 1+ var*0.03); //case MuEle + elemu trigger 
    else if(isEl==2 && (pt1>25 && pt2>15 && pt3>10) ) return totEff*getSingleEfficiency(pt1, eta1, kMuXTLeg1, var); //muele only trigger, 1leg cor

    if(isEl==3 && (pt1>25 && pt2>20 && pt3>15) ) return totEff*std::min(1., 1+ var*0.03); //case dimu + eleMu trigger
    else if(isEl==3 && (pt1>25 && pt2>10 && pt3>15) ) return totEff*getSingleEfficiency(pt1, eta1, kMuLeg1, var); //case dimu + muele trigger,  1leg cor -> should never happen
    break;

  }
  case 39: {
    if(pt1>20 && pt2>20 && pt3>10) return totEff*std::min(1., 1+ var*0.03);  //dimu
    else if(pt1>20 && pt2>10 && pt3>10) return totEff*getSingleEfficiency(pt1, eta1, kMuLeg1, var); //dimu, 1leg cor
    break;
  }
    
  }
  
  //other cases, looking at the 2 first legs
  switch(flav) {
  case 22: {
    hltleg1 = kElLeg1;
    hltleg2 = kElLeg2;
    //DZ efficiency correction
    totEff *= 0.995 + var*0.005;
    break;
  }
  case 24: {
    if(std::abs(pdgId1)==11) {
      hltleg1 = kElXTLeg1;
      hltleg2 = kMuXTLeg2;
    } else {
      hltleg1 = kMuXTLeg1;
      hltleg2 = kElXTLeg2;
    }
    break;
  }
  case 26: { 
    hltleg1 = kMuLeg1;
    hltleg2 = kMuLeg2;
    break;
  }
  }
    
  totEff *= getSingleEfficiency(pt1, eta1, hltleg1, var) * getSingleEfficiency(pt2, eta2, hltleg2, var );

  // //L1 HT plateau efficiency
  // //https://lathomas.web.cern.ch/lathomas/SUSYMultiLepton/TriggerEff/Results_7p65fb/l1htturnon.pdf
  // if(isHTHLT) totEff *= 0.962 + var*0.01;
    
  // //HLT HT efficiency correction for low pt leptons
  // if(ht>300 && ht<325 && pt1<30 && pt2<30) {
  //   totEff *= 0.85 + var*0.05;
  // }

  return std::min( (float)1.0,totEff);
}











void 
HLTEfficiency::loadFile() { 
  _file = TFile::Open(_fileName.c_str(), "read");
  
  _hist_HLT_DiEle_Leg1   =(TH2F*)_file->Get("hist2dnum_Ele23_CaloIdL_TrackIdL_IsoVL__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
  _hist_HLT_DiEle_Leg2   =(TH2F*)_file->Get("hist2dnum_Ele12_CaloIdL_TrackIdL_IsoVL__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
  _hist_HLT_EleMu_Leg1   =(TH2F*)_file->Get("hist2dnum_Ele23_CaloIdL_TrackIdL_IsoVL__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
  _hist_HLT_MuEle_Leg2   =(TH2F*)_file->Get("hist2dnum_Ele12_CaloIdL_TrackIdL_IsoVL__HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
  _hist_HLT_DiEleHT_Leg  =(TH2F*)_file->Get("hist2dnum_Ele8_CaloIdM_TrackIdM__DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250or300");
  _hist_HLT_EleMuHT_Leg1 =(TH2F*)_file->Get("hist2dnum_Ele8_CaloIdM_TrackIdM__DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250or300");
  _hist_HLT_DiMu_Leg1    =(TH2F*)_file->Get("hist2dnum_Mu17__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
  _hist_HLT_DiMu_Leg2    =(TH2F*)_file->Get("hist2dnum_Mu8__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
  _hist_HLT_MuEle_Leg1   =(TH2F*)_file->Get("hist2dnum_Mu17__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
  _hist_HLT_EleMu_Leg2   =(TH2F*)_file->Get("hist2dnum_Mu8__HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
  _hist_HLT_DiMuHT_Leg   =(TH2F*)_file->Get("hist2dnum_Mu8__HLT_DoubleMu8_Mass8_PFHT250or300");
  _hist_HLT_EleMuHT_Leg2 =(TH2F*)_file->Get("hist2dnum_Mu8__HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250or300");
    
};

float 
HLTEfficiency::getSingleEfficiency(float pt, float eta, int hlttag, int var) {

  switch(hlttag) {
  case kElLeg1:    { return getBinContent(pt, std::abs(eta), _hist_HLT_DiEle_Leg1)   + var*0.01;}
  case kElLeg2:    { return getBinContent(pt, std::abs(eta), _hist_HLT_DiEle_Leg2)   + var*0.01;}
  case kElXTLeg1:  { return getBinContent(pt, std::abs(eta), _hist_HLT_EleMu_Leg1)   + var*0.01;}
  case kElXTLeg2:  { return getBinContent(pt, std::abs(eta), _hist_HLT_MuEle_Leg2)   + var*0.01;}
  case kElHTLeg:   { return getBinContent(pt, std::abs(eta), _hist_HLT_DiEleHT_Leg)  + var*0.01;}
  case kElHTXTLeg: { return getBinContent(pt, std::abs(eta), _hist_HLT_EleMuHT_Leg1) + var*0.01;}
  case kMuLeg1:    { return getBinContent(pt, std::abs(eta), _hist_HLT_DiMu_Leg1)    + var*0.01;}
  case kMuLeg2:    { return getBinContent(pt, std::abs(eta), _hist_HLT_DiMu_Leg2)    + var*0.01;}
  case kMuXTLeg1:  { return getBinContent(pt, std::abs(eta), _hist_HLT_MuEle_Leg1)   + var*0.01;}
  case kMuXTLeg2:  { return getBinContent(pt, std::abs(eta), _hist_HLT_EleMu_Leg2)   + var*0.01;}
  case kMuHTLeg:   { return getBinContent(pt, std::abs(eta), _hist_HLT_DiMuHT_Leg)   + var*0.01;}
  case kMuHTXTLeg: { return getBinContent(pt, std::abs(eta), _hist_HLT_EleMuHT_Leg2) + var*0.01;}
  }
  return 1;
}

float 
HLTEfficiency::getBinContent(float x, float y, TH2F* h) {
  int xb=h->GetXaxis()->FindBin( x );
  int yb=h->GetYaxis()->FindBin( y );
  return h->GetBinContent(xb,yb);
}

