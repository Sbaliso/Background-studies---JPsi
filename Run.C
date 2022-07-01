#include "AnalysisSelectorDecayMu.h"
#include <typeinfo>
#include "TChain.h"
#include "TSelector.h"
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TFile.h>
#include <TString.h>
#include <TSelector.h>

TChain *CreateChain(const TString sDataset="", const TString sChain="");
void Run(const TString sFn = "Tsallis")
{
  gSystem->Load("libMathMore");
  const TString sPathIn="/home/sibaliso/Desktop/MuonVsMultiplicity/files/JPsi2022/JpsiDecayMu/JpsiDecayMu/input";
  const TString sDataset=  "Jpsi.txt";
  const TString sPar = "Jpsi";
  //const TString sGen = (sType.Contains("PYTHIA") ? "PYTHIA" : "PHOJET");
  //const int sCR = (sType.Contains("CR0") ? 0 : 1);
//=============================================================================

  TList *listIn = new TList();

  TFile *file = new TFile(Form("%s/Pbp/output/Pbp/tsallis/WeightPt%s%s_2_10.root",sPathIn.Data(),sPar.Data(),sFn.Data()));
  TH1D *hWeightPt = (TH1D*)file->Get(Form("fWeightPt"));
  hWeightPt->SetName("hWeightPt");
  hWeightPt->SetDirectory(0);
  file->Close();

  listIn->Add(hWeightPt);
    
  //=============================================================================
  file = TFile::Open(Form("%s/newPbpWeightRap%s.root",sPathIn.Data(),sPar.Data()), "READ");
  TFile *file1 = new TFile(Form("%s/newpPbWeightRap%s_1.root",sPathIn.Data(),sPar.Data()), "READ");

  TH1D *hWeightRap = (TH1D*)file->Get("hWeightRap");
  hWeightRap->SetName("hWeightRap");
  hWeightRap->SetDirectory(0);
  listIn->Add(hWeightRap);
 
  TF1 *fWeightRap = (TF1*)file1->Get("fWeightRap_1");
  fWeightRap->SetName("fWeightRap");
  file->Close();
  listIn->Add(fWeightRap);

  listIn->ls();
//=============================================================================

TSelector *psel = TSelector::GetSelector("AnalysisSelectorDecayMu.cxx++");
//AnalysisSelectorDecayMu *pMuSel=dynamic_cast<AnalysisSelectorDecayMu*>(psel); // error is coming from here in defining the dynamic_cast
AnalysisSelectorDecayMu *pMuSel= (AnalysisSelectorDecayMu*)psel->Clone();

pMuSel->SetInputList(listIn);

const Double_t dCutMinPtH = ((sPar=="Jpsi") ?  0. :  2.);
const Double_t dCutMaxPtH = ((sPar=="Jpsi") ? 50. : 40.);
pMuSel->SetHadronPtRange(dCutMinPtH, dCutMaxPtH);


TChain *chain = CreateChain(sDataset,"bkgJpsiMuonTuple");
chain->Process((TSelector*)pMuSel, "Loop1st");
chain->Process((TSelector*)pMuSel, "Loop2nd");
return;

}

//_____________________________________________________________________________
TChain *CreateChain(const TString sDataset, const TString sChain)
{
 
  if (gSystem->AccessPathName(sDataset.Data())) {
    ::Error("Run.C::CreateChain","Dataset %s does not exist!",sDataset.Data());
    return NULL;
  }
 
  TString sFile;
  TChain *fchain = new TChain(sChain.Data(),sChain.Data());
  ifstream fList(sDataset.Data(), ios::in);
  while (!fList.eof()) {
    sFile.ReadLine(fList,kFALSE);
    if (!sFile.EndsWith(".root")) continue;
    if (!gSystem->AccessPathName(sFile.Data())) fchain->Add(sFile.Data());
  }
  
 fList.close();

 return fchain;
 
}

