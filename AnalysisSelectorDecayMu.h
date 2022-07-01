//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May  7 15:14:49 2017 by ROOT version 5.34/36
// from TTree bkgKPiMuonTuple/
// found on file: AliKPiDecayMuonNtuple.root
//////////////////////////////////////////////////////////

#ifndef AnalysisSelectorDecayMu_h
#define AnalysisSelectorDecayMu_h

#include <TChain.h>
#include <TSelector.h>

class TF1;
class TH1D;
class TH2D;
class TChain;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class AnalysisSelectorDecayMu : public TSelector {

 public :

  AnalysisSelectorDecayMu(TTree * /*tree*/ =0) :
    fChain(0),
    fHistoWeightPt(0x0),
    fHistoWeightRap(0x0),
    fFxnWeightRap(0x0),
    fFxnWeightAbsExp1(0x0),
    fFxnWeightAbsExp2(0x0),
    fHist2HadronPtRap(0x0),
    fHist2MuonPtEta(0x0),
    fHist2MuonHadronPt(0x0){ }
  virtual ~AnalysisSelectorDecayMu() { }

  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);

  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();

  virtual Bool_t  Process(Long64_t entry);

  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }

  virtual void    SlaveTerminate();
  virtual void    Terminate();

  virtual Int_t   Version() const { return 2; }
//=============================================================================

  void SetHadronPtRange(Double_t dMin, Double_t dMax) { fCutMinPtH = dMin; fCutMaxPtH = dMax; }
//=============================================================================

 private :

  virtual Int_t GetEntry(Long64_t entry, Int_t getall=0) {
    return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
  }

  void Loop1stBegin();
  void Loop2ndBegin();

  void Loop1stProcess();
  void Loop2ndProcess();
//=============================================================================

  TH1D *fHistoWeightPt;     //!
  TH1D *fHistoWeightRap;      //!
  TF1  *fFxnWeightRap;      //!
  TF1  *fFxnWeightAbsExp1;  //!
  TF1  *fFxnWeightAbsExp2;  //!

  TH2D *fHist2HadronPtRap;    //!
  TH2D *fHist2MuonPtEta;     //!
  TH2D *fHist2MuonHadronPt;  //!
    
  Double_t fCutMinPtH;
  Double_t fCutMaxPtH;

  const static Int_t nRapBin;
  const static Double_t dRapBin[7];
//=============================================================================

  TTree *fChain;  //!

  Float_t fPtH;
  Float_t fEtaH;
  Float_t fRapH;
  Float_t fPdgH;
  Float_t fRhoHMu1;
  Float_t fRhoHMu2;
    
  Float_t fPtLMu1;
  Float_t fEtaLMu1;
  Float_t fRapLMu1;
  Float_t fPdgLMu1;
    
  Float_t fPtLMu2;
  Float_t fEtaLMu2;
  Float_t fRapLMu2;
  Float_t fPdgLMu2;

  TBranch *b_fPtH;   //!
  TBranch *b_fEtaH;  //!
  TBranch *b_fRapH;  //!
  TBranch *b_fPdgH;  //!
  TBranch *b_fRhoHMu1;  //!
  TBranch *b_fRhoHMu2;  //!
  TBranch *b_fPtLMu1;   //!
  TBranch *b_fEtaLMu1;  //!
  TBranch *b_fRapLMu1;  //!
  TBranch *b_fPdgLMu1;  //!
  TBranch *b_fPtLMu2;   //!
  TBranch *b_fEtaLMu2;  //!
  TBranch *b_fRapLMu2;  //!
  TBranch *b_fPdgLMu2;  //!


   ClassDef(AnalysisSelectorDecayMu,0);
};

#endif

#ifdef AnalysisSelectorDecayMu_cxx
void AnalysisSelectorDecayMu::Init(TTree *tree)
{
// The Init() function is called when the selector needs to initialize
// a new tree or chain. Typically here the branch addresses and branch
// pointers of the tree will be set.
// It is normally not necessary to make changes to the generated
// code, but the routine can be extended by the user if needed.
// Init() will be called many times when running on PROOF
// (once per file to be processed).

// Set branch addresses and branch pointers

  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("fPtH",  &fPtH,  &b_fPtH);
  fChain->SetBranchAddress("fEtaH", &fEtaH, &b_fEtaH);
  fChain->SetBranchAddress("fRapH", &fRapH, &b_fRapH);
  fChain->SetBranchAddress("fPdgH", &fPdgH, &b_fPdgH);
  fChain->SetBranchAddress("fRhoHMu1", &fRhoHMu1, &b_fRhoHMu1);
  fChain->SetBranchAddress("fRhoHMu2", &fRhoHMu2, &b_fRhoHMu2);
  fChain->SetBranchAddress("fPtLMu1",  &fPtLMu1,  &b_fPtLMu1);
  fChain->SetBranchAddress("fEtaLMu1", &fEtaLMu1, &b_fEtaLMu1);
  fChain->SetBranchAddress("fRapLMu1", &fRapLMu1, &b_fRapLMu1);
  fChain->SetBranchAddress("fPdgLMu1", &fPdgLMu1, &b_fPdgLMu1);
  fChain->SetBranchAddress("fPtLMu2",  &fPtLMu2,  &b_fPtLMu2);
  fChain->SetBranchAddress("fEtaLMu2", &fEtaLMu2, &b_fEtaLMu2);
  fChain->SetBranchAddress("fRapLMu2", &fRapLMu2, &b_fRapLMu2);
  fChain->SetBranchAddress("fPdgLMu2", &fPdgLMu2, &b_fPdgLMu2);

  return;
}

Bool_t AnalysisSelectorDecayMu::Notify()
{
// The Notify() function is called when a new file is opened. This
// can be either for a new TTree in a TChain or when when a new TTree
// is started when using PROOF. It is normally not necessary to make changes
// to the generated code, but the routine can be extended by the
// user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef AnalysisSelectorDecayMu_cxx
