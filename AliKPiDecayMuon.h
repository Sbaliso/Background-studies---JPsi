#ifndef ALIKPIDECAYMUON_H
#define ALIKPIDECAYMUON_H

class AliKPiDecayMuon
{
 public:
  AliKPiDecayMuon();
  AliKPiDecayMuon(const AliKPiDecayMuon &);
  AliKPiDecayMuon& operator=(const AliKPiDecayMuon &);
  virtual ~AliKPiDecayMuon();
  
  void RunClass(Int_t nEvents);// {nEvents = fEvents;}
  void SetOutputFile(TString name) {fOutputName = name;}
  void SetPDG(Float_t pdg) {fPdgH = pdg;}
  void SetPtRange(Float_t pTmin, Float_t pTmax) {fPtMin = pTmin; fPtMax = pTmax;}
  void SetYRange(Float_t yMin, Float_t yMax) {fYMin = yMin; fYMax = yMax;}
  void SetFileRange(Int_t fNmin, Int_t fNmax) {fileNmin=fNmin; fileNmax=fNmax;}
  
 private:
  void Init();
  void Make();
  void Term();
  Float_t YtoEta(Float_t pt, Float_t mm, Float_t rap);
  //Int_t nEvents;
  Int_t fileNmin;
  Int_t fileNmax;
  Float_t fPtMin;
  Float_t fPtMax;
  Float_t fYMin;
  Float_t fYMax;
  
  Float_t fPdgH;
  Float_t fPtH;
  Float_t fRapH;
  Float_t fEtaH;

  Int_t fNMuons;

  Float_t fRhoH1;
  Float_t fPdgL1;
  Float_t fPtL1;
  Float_t fRapL1;
  Float_t fEtaL1;

  Float_t fRhoH2;
  Float_t fPdgL2;
  Float_t fPtL2;
  Float_t fRapL2;
  Float_t fEtaL2;

  TFile *fOutputFile;
  TTree *fTree;
  AliDecayerPythia *fDecayer;
  TClonesArray *fPartArray;
  TParticle *fParticle;
  TString fOutputName;
  
  ClassDef(AliKPiDecayMuon,1)
};

#endif
