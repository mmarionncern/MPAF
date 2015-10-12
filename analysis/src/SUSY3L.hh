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

#ifndef SUSY3L_HH
#define SUSY3L_HH

#include "analysis/core/MPAF.hh"
#include "analysis/modules/SusyModule.hh"

class SUSY3L: public MPAF {

public:
    // Member Functions
    SUSY3L(std::string);
    virtual ~SUSY3L();

private:
    void initialize();

    void run();
    void defineOutput();
    void loadInput();
    void modifyWeight();
    void writeOutput();

    void modifySkimming();

    void setMultiIsoWP();
    void collectKinematicObjects();
    bool electronSelection(int);
    bool muonSelection(int);
    bool tauSelection(int);
    bool bJetSelection(int);
    bool goodJetSelection(int);

    bool baseSelection();
    bool wzCRSelection();
    void setBaselineRegion();
    void setWZControlRegion();
    void setSignalRegion();
    void setCut(std::string, float, std::string, float = 0);
    bool hardLegSelection();
    bool checkMultiIso();
    bool ZEventSelection();
    bool ZEventSelectionLoop();
    bool srSelection();
    bool electronMvaCut(int, int);
    bool multiIsolation(int, float, float, float);
    void fillEventPlots();
    float getMT2();
    void sortSelectedLeps();
    float lowestOssfMll(bool ossf = true);
    bool passMultiLine(bool doubleOnly);
    bool passHLTLine(string line);

    float HT();
    float M_T(float, float, float, float);
    float DeltaPhi(float, float);
    float MT2(Candidate*, Candidate*, Candidate*, double);

    string _selectMuons;
    string _selectElectrons;
    string _selectTaus;
    string _pairmass;
    string _BR;
    string _SR;
    


private:

    //counter categories, 0 is ALWAYS global (even if not specified later)
    enum {
        kGlobal=0,                                      //global counter
        kElId, kMuId, kTauId, kJetId, kBJetId,          //objects counter
        kBase,kWZ,
        conZEvents,                                     //Z cand. counter
        kWZCR                                     //WZ control region counter
        };
    
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
    float _valCutHTSR;
    float _valCutMETSR;
    float _valCutNJetsSR;
    float _valCutNBJetsSR;
    float _valCutMllBR;
    float _valCutMT2BR;

    float _valCutLepMultiplicityWZ;
    float _valCutNJetsWZ;
    float _valCutNBJetsWZ;
    float _valCutHTWZ;
    float _valCutMETWZ;
    
    std::vector<std::string> _hltLines;
    
    std::string _cTypeLepMultiplicityBR;
    std::string _cTypeNJetsBR;
    std::string _cTypeNBJetsBR;
    std::string _cTypeHTBR;
    std::string _cTypeMETBR;
    std::string _cTypeNJetsSR;
    std::string _cTypeNBJetsSR;
    std::string _cTypeHTSR;
    std::string _cTypeMETSR;
    std::string _cTypeMllBR;
    std::string _cTypeMT2BR;
    
    std::string _cTypeLepMultiplicityWZ;
    std::string _cTypeNJetsWZ;
    std::string _cTypeNBJetsWZ;
    std::string _cTypeHTWZ;
    std::string _cTypeMETWZ;

    float _upValCutLepMultiplicityBR;
    float _upValCutNJetsBR;
    float _upValCutNBJetsBR;
    float _upValCutHTBR;
    float _upValCutMETBR;
    float _upValCutNJetsSR;
    float _upValCutNBJetsSR;
    float _upValCutHTSR;
    float _upValCutMETSR;
    float _upValCutMllBR;
    float _upValCutMT2BR;
    
    float _upValCutLepMultiplicityWZ;
    float _upValCutNJetsWZ;
    float _upValCutNBJetsWZ;
    float _upValCutHTWZ;
    float _upValCutMETWZ;
 
    //vectors for electron, muon, and tau candidates
    std::vector<int> _elIdx;
    std::vector<int> _muIdx;
    std::vector<int> _tauIdx;

    //length of candiate vectors
    int _nEls;
    int _nVEls;
    int _nMus;
    int _nVMus;
    int _nTaus;
    int _nVTaus;
    int _nJets;
    int _nBJets;
    int _nleps;

    //list of object candidates
    CandList _els;
    CandList _vEls;
    CandList _mus;
    CandList _vMus;
    CandList _taus;
    CandList _vTaus;
    CandList _jets;
    CandList _bJets;
    CandList _leps;
    Candidate* _met;
    Candidate* _Z;
    Candidate* _lep1;
    Candidate* _lep2;

    float _HT;
    float _MT2;
    float _deltaR;
    float _mll;
  
    
};

#endif
