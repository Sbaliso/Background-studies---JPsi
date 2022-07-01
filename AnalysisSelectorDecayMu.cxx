#define AnalysisSelectorDecayMu_cxx
// The class definition in AnalysisSelectorDecayMu.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("AnalysisSelectorDecayMu.C")
// Root > T->Process("AnalysisSelectorDecayMu.C","some options")
// Root > T->Process("AnalysisSelectorDecayMu.C+")
//

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TFile.h>
#include <TString.h>
#include "TError.h"
#include "Math/GSLIntegrator.h"

#include "AnalysisSelectorDecayMu.h"
//ROOT::Math::IntegratorOneDimOptions::SetDefaultRelTolerance(1.E-6);
const Int_t AnalysisSelectorDecayMu::nRapBin = 7;
const Double_t AnalysisSelectorDecayMu::dRapBin[7] = { 0., 1., 2., 2.5, 3., 3.5, 4. };

void AnalysisSelectorDecayMu::Begin(TTree * /*tree*/)
{
// The Begin() function is called at the start of the query.
// When running with PROOF Begin() is only called on the client.
// The tree argument is deprecated (on PROOF 0 is passed).
  //gSystem->Load("libMathMore");
  TString sOpt = GetOption();
  Info(__func__, "%s", sOpt.Data());

  if (sOpt.Contains("Loop1st")) Loop1stBegin();
  if (sOpt.Contains("Loop2nd")) Loop2ndBegin();

  return;
}

void AnalysisSelectorDecayMu::SlaveBegin(TTree * /*tree*/)
{
// The SlaveBegin() function is called after the Begin() function.
// When running with PROOF SlaveBegin() is called on each slave server.
// The tree argument is deprecated (on PROOF 0 is passed).

//TString sOpt = GetOption();

  return;
}

Bool_t AnalysisSelectorDecayMu::Process(Long64_t entry)
{
// The Process() function is called for each entry in the tree (or possibly
// keyed object in the case of PROOF) to be processed. The entry argument
// specifies which entry in the currently loaded tree is to be processed.
// It can be passed to either AnalysisSelectorDecayMu::GetEntry() or TBranch::GetEntry()
// to read either all or the required parts of the data. When processing
// keyed objects with PROOF, the object is already loaded and is available
// via the fObject pointer.
//
// This function should contain the "body" of the analysis. It can contain
// simple or elaborate selection criteria, run algorithms on the data
// of the event and typically fill histograms.
//
// The processing can be stopped by calling Abort().
//
// Use fStatus to set the return value of TTree::Process().
//
// The return value is currently not used.

  GetEntry(entry);
  TString sOpt = GetOption();
  if (sOpt.Contains("Loop1st")) Loop1stProcess();
  if (sOpt.Contains("Loop2nd")) Loop2ndProcess();

  return kTRUE;
}

void AnalysisSelectorDecayMu::SlaveTerminate()
{
// The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.

  return;
}

void AnalysisSelectorDecayMu::Terminate()
{
// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.

  TString sOpt = GetOption();

  if (sOpt.Contains("Loop2nd")) {
    fOutput->Print();
    TFile *file = new TFile("AnalysisOutputs2_10.root","RECREATE");
    file->cd(); fOutput->Write(); file->Close();
  }

  Info(__func__, "%s DONE", sOpt.Data());

  return;
}

//_____________________________________________________________________________
void AnalysisSelectorDecayMu::Loop1stBegin()
{
//
//  AnalysisSelectorDecayMu::Loop1stBegin()
//
  if (fHistoWeightPt) { delete fHistoWeightPt;  fHistoWeightPt  = 0x0; }
  if (fHistoWeightRap)  { delete fHistoWeightRap;   fHistoWeightRap   = 0x0; }
  if (fFxnWeightRap)  { delete fFxnWeightRap;   fFxnWeightRap   = 0x0; }

  fHistoWeightPt = dynamic_cast<TH1D*>(fInput->FindObject("hWeightPt"));
  if (!fHistoWeightPt) { Error(__func__, "Problem to read pT weight"); exit(-1); }

  fHistoWeightRap = dynamic_cast<TH1D*>(fInput->FindObject("hWeightRap"));
  if (!fHistoWeightRap) { Error(__func__, "Problem to read HistoRap weight"); exit(-1); }
    
//   fFxnWeightRap = dynamic_cast<TF1*>(fInput->FindObject("fWeightRap"));
//   if (!fFxnWeightRap) { Error(__func__, "Problem to read FxnRap weight"); exit(-1); }
//     
/*
  for (Int_t k=1; k<nRapBin; ++k) {
    TH1D *hExtrapRap = dynamic_cast<TH1D*>(fInput->FindObject(Form("hExtrapRap%d",k)));
    if (!hExtrapRap) { Error(__func__, "Problem to read rap extrap fact"); exit(-1); }
  }
*/
    
  const TArrayD *aBin(fHistoWeightPt->GetXaxis()->GetXbins());
  const Int_t nBin(aBin->GetSize() - 1);

  Double_t dBin[nBin+1];
  for (Int_t i=0; i<=nBin; ++i) {
        dBin[i] = (*aBin)[i];
        //cout << "dBin["<<i<<"] = " << dBin[i] << endl << "   JpsiPt = " << ;
  }
    
  for (Int_t i=0; i<nBin; ++i) {
      //cout << i+1 << "'th bin = " <<  fHistoWeightPt->GetBinCenter(i+1) << "   JpsiPt = " << fHistoWeightPt->GetBinContent(i+1) << endl;
    }

  if (fHist2HadronPtRap) { delete fHist2HadronPtRap; fHist2HadronPtRap = 0x0; }
  fHist2HadronPtRap = new TH2D("hHadronPtRap", "", nBin, dBin, 200, -10., 10.);
 
  return;
}

//_________________________________________________________________________
void AnalysisSelectorDecayMu::Loop1stProcess()
{
//
//  AnalysisSelectorDecayMu::Loop1stProcess()
//

  //fHist2HadronPtRap->Fill(fPtH, TMath::Abs(fRapH));
  fHist2HadronPtRap->Fill(fPtH, fRapH);
  return;
}

//________________________________________________________________________
void AnalysisSelectorDecayMu::Loop2ndBegin()
{
//
//  AnalysisSelectorDecayMu::Loop2ndBegin
//
  //fHist2HadronPtRap->Draw();
  const TArrayD *aBin(fHistoWeightPt->GetXaxis()->GetXbins());
  const Int_t nBin(aBin->GetSize() - 1);
  Double_t dBin[nBin+1];
  for (Int_t i=0; i<=nBin; ++i) dBin[i] = (*aBin)[i];

  if (fHist2MuonHadronPt) { delete fHist2MuonHadronPt; fHist2MuonHadronPt = 0; }
  fHist2MuonHadronPt = new TH2D("hMuonHadronPt", "", 80, 0., 80., nBin, dBin);
  fHist2MuonHadronPt->Sumw2(); fOutput->Add(fHist2MuonHadronPt);

  if (fHist2MuonPtEta) { delete fHist2MuonPtEta; fHist2MuonPtEta = 0; }
  fHist2MuonPtEta = new TH2D("hMuonPtEta", "", 80, 0., 80., 200, -10, 10.);
  fHist2MuonPtEta->Sumw2(); fOutput->Add(fHist2MuonPtEta);
    
  return;
}

//_____________________________________________________________________________
void AnalysisSelectorDecayMu::Loop2ndProcess()
{
//
//  AnalysisSelectorDecayMu::Loop2ndProcess
//
  if ((fPtH<fCutMinPtH) || (fPtH>=fCutMaxPtH)) return;
  //if((fEtaH>-2.5) || (fEtaH<=-4.)) return;
  if (((fEtaLMu1> -2.5) || (fEtaLMu1<= -4.)) && ((fEtaLMu2> -2.5) || (fEtaLMu2<= -4.))) return;
 // cout << "fPtH = " << fPtH << "  fRapH = " << fRapH << "  fEtaLMu1 = " << fEtaLMu1 << "  fEtaLMu2 = "  << fEtaLMu2 << endl;//"  fPtLMu1 = " << fPtLMu1 << "  fPtLMu2 = "  << fPtLMu2 << endl;
  
    //Float_t dRapH(TMath::Abs(fRapH));
    //Float_t dEtaL1(TMath::Abs(fEtaLMu1));
    //Float_t dEtaL2(TMath::Abs(fEtaLMu2));
    
    Float_t dRapH(fRapH);
    Float_t dEtaL1(fEtaLMu1);
    Float_t dEtaL2(fEtaLMu2);
//=============================================================================
// Weight in Pt distribution
// ------------------------------------------------------------------
  Double_t dWeightPt = fHistoWeightPt->GetBinWidth(fHistoWeightPt->FindBin(fPtH)) * fHistoWeightPt->GetBinContent(fHistoWeightPt->FindBin(fPtH));
  //cout << "fPtH bin = " << fHistoWeightPt->FindBin(fPtH) << "   fPtH = " << fHistoWeightPt->GetBinContent(fHistoWeightPt->FindBin(fPtH)) << endl;

//=============================================================================
// Weight Rapidity distribution.
// ------------------------------------------------------------------
 Double_t dWeightRap = fHistoWeightRap->GetBinWidth(fHistoWeightRap->FindBin(fRapH)) * fHistoWeightRap->GetBinContent(fHistoWeightRap->FindBin(fRapH));
/*
  Int_t    kBinRap = fHist2HadronPtRap->GetYaxis()->FindBin(dRapH);
  Double_t dBinRap = fHist2HadronPtRap->GetYaxis()->GetBinWidth(kBinRap);
  Double_t dWeightRap = (fFxnWeightRap->Eval(dRapH)) * dBinRap;
  //Double_t dWeightRap = ((fFxnWeightRap->Eval(dRapH))/(fFxnWeightRap->Integral(-2.8,-2.5,1e-06))) * dBinRap;
 */
//=============================================================================
  Double_t dNorm = fHist2HadronPtRap->GetBinContent(fHist2HadronPtRap->FindBin(fPtH,dRapH));
  Double_t dWeight = (dWeightPt * dWeightRap)/dNorm;
  dWeight=dWeight/2.;
  
  fHist2MuonPtEta->Fill(fPtLMu1, dEtaL1, dWeight);
  fHist2MuonHadronPt->Fill(fPtLMu1, fPtH, dWeight);
  fHist2MuonPtEta->Fill(fPtLMu2, dEtaL2, dWeight);
  fHist2MuonHadronPt->Fill(fPtLMu2, fPtH, dWeight);
  return;
}
