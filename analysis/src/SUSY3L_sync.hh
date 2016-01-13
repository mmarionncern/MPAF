/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Jan Hoss, ETHZ, 12/2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef SUSY3L_sync_HH
#define SUSY3L_sync_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

class SUSY3L_sync: public MPAF {

public:
    // Member Functions
    SUSY3L_sync(std::string);
    virtual ~SUSY3L_sync();

private:
    void initialize();

    void run();
    void defineOutput();
    void loadInput();
    void modifyWeight();
    void writeOutput();
    void modifySkimming();
    void collectKinematicObjects();
    
    bool tauSelection(int);
    bool looseLepton(const Candidate* c, int idx, int pdgId);
    bool fakableLepton(const Candidate* c, int idx, int pdgId, bool bypass);
    bool tightLepton(const Candidate* c, int idx, int pdgId);
    
    bool multiLepSelection(bool onZ);
    void advancedSelection(int WF);
    float getTF_SingleFake(int ic);
    float getTF_DoubleFake(int ic);
    float getTF_TripleFake(int ic);
    bool wzCRSelection();
    void categorize();
    bool testRegion();
    vector<CandList> build3LCombFake(const CandList tightLeps, vector<unsigned int> idxsT,
		const CandList fakableLeps, vector<unsigned int> idxsL, const CandList fakableLepsPtCorr,
		vector<unsigned int> idxsLPtCorr, int nHardestLepton, float pt_cut_hardest_legs, 
        int nHardLeptons, float pt_cut_hard_legs, bool onZ,
        vector< vector<int> >& combIdxs, vector<int>& combType ); 
    void setBaselineRegion();
    void setSignalRegion();
    void setSelLine(string str);
    float getFR(Candidate* cand, int idx);
    void setCut(std::string, float, std::string, float = 0);
    bool hardLeg(CandList leptons, int n_hardestLeg, float cut_hardestLeg, int n_hardLeg, float cut_hardLeg);
    void fillHistos();
    void fillControlPlots();
    float getMT2();
    void sortSelectedLeps(CandList leps, std::vector<unsigned int> lepsIdx);
    float lowestOssfMll(CandList leps);
    bool passMultiLine(bool doubleOnly, bool isolatedOnly);
    bool passHLTLine(string line);

    float HT();
    float M_T(float, float, float, float);
    float DeltaPhi(float, float);
    float MT2(Candidate*, Candidate*, Candidate*, double);

    bool _selectMuons;
    bool _selectElectrons;
    bool _selectTaus;
    bool _onZ;
    string _BR;
    string _SR;
    string _FR;




private:

    //counter categories, 0 is ALWAYS global (even if not specified later)
    enum {kGlobal=0,
    
    kSR001, kSR002, kSR003, kSR004, kSR005, kSR006, kSR007, kSR008,
    kSR009, kSR010, kSR011, kSR012, kSR013, kSR014, kSR015,
    
    kSR001_Fake, kSR002_Fake, kSR003_Fake, kSR004_Fake, kSR005_Fake, kSR006_Fake, kSR007_Fake, kSR008_Fake,
    kSR009_Fake, kSR010_Fake, kSR011_Fake, kSR012_Fake, kSR013_Fake, kSR014_Fake, kSR015_Fake,

    kGlobalFake,
    
    kWZCR
    };

    enum {kIsSingleFake=0,kIsDoubleFake,kIsTripleFake };
    
    SusyModule* _susyMod;

    //cut variables
    float _valCutLepMultiplicityBR;
    float _pt_cut_hard_legs;
    int   _nHardLeptons;
    float _pt_cut_hardest_legs;
    int   _nHardestLeptons;
    float _M_T_3rdLep_MET_cut;
    float _multiIsoWP[5][3];
    float _valCutNJetsBR;
    float _valCutNBJetsBR;
    float _ZMassWindow;
    float _lowMllCut;
    float _valCutHTBR;
    float _valCutMETBR;
    float _valCutMllBR;
    float _valCutMT2BR;

    std::vector<std::string> _hltLines;
    
    std::string _cTypeLepMultiplicityBR;
    std::string _cTypeNJetsBR;
    std::string _cTypeNBJetsBR;
    std::string _cTypeHTBR;
    std::string _cTypeMETBR;
    std::string _cTypeMllBR;
    std::string _cTypeMT2BR;
    
    float _upValCutLepMultiplicityBR;
    float _upValCutNJetsBR;
    float _upValCutNBJetsBR;
    float _upValCutHTBR;
    float _upValCutMETBR;
    float _upValCutMllBR;
    float _upValCutMT2BR;
    
    //vectors for electron, muon, and tau candidates
    std::vector<int> _tauIdx;
    std::vector<unsigned int> _lepsIdx;
    std::vector<unsigned int> _looseLepsIdx;
    std::vector<unsigned int> _looseLepsPtCutIdx;
    std::vector<unsigned int> _looseLepsPtCorrCutIdx;
    std::vector<unsigned int> _fakableLepsIdx;
    std::vector<unsigned int> _fakableLepsPtCutIdx;
    std::vector<unsigned int> _fakableNotTightLepsPtCutIdx;
    std::vector<unsigned int> _fakableNotTightLepsPtCorrCutIdx;
    std::vector<unsigned int> _tightLepsPtCutIdx;
    std::vector<unsigned int> _tightLepsPtCutMllCutIdx;
    std::vector<std::pair<std::string, unsigned int> >  _jetsIdx;
    std::vector<std::pair<std::string, unsigned int> >  _bJetsIdx;
    std::vector<std::pair<std::string, unsigned int> >  _lepJetsIdx;

    //length of candiate vectors
    float _nTaus;
    float _nJets;
    float _nBJets;
    float _nleps;
    std::map<std::string,float*> _val;

    //list of object candidates
    CandList _els;
    CandList _mus;
    CandList _taus;
    CandList _jets;
    CandList _bJets;
    CandList _leps;
    CandList _looseLeps;
    CandList _looseLepsPtCut;
    CandList _looseLepsPtCorrCut;
    CandList _fakableLeps;
    CandList _fakableLepsPtCut;
    CandList _fakableNotTightLepsPtCut;
    CandList _fakableNotTightLepsPtCorrCut;
    CandList _tightLepsPtCut;
    CandList _tightLepsPtCutMllCut;
    CandList _lepJets;

    Candidate* _met;
    Candidate* _Z;
    CandList _zPair;
    
    float _HT;
    float _MT2;
    float _deltaR;
    float _lowOSSFMll;
    float _metPt;
    float _MT;
    float _zMass;
    float _zPt;
    int _nEls;
    int _nMus;
  
    std::map<std::string, std::vector<std::vector<std::vector<std::string> > > > _sels;
   
    float _jetThreshold;
    float _bjetThreshold;
    
    vector<string> _categs;
    bool _categorization;
    bool _isMultiLep = false;
    bool _isFake = false;

    //for fake background
    vector<CandList> _combList;
    vector< vector<int> > _combIdxs;
    vector<int> _combType;
};

#endif
