#include <TFile.h>
#include <TMath.h>
using namespace::TMath;
#include <TRandom3.h>
#include <TParticle.h>
#include <TParticlePDG.h>
#include <TDatabasePDG.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <iostream>
using namespace::std;

#include "AliDecayerPythia.h"
#include "AliKPiDecayMuon.h"

ClassImp(AliKPiDecayMuon)


AliKPiDecayMuon::AliKPiDecayMuon() :
fOutputName("")
{
  if(gRandom)
  {
    delete gRandom;
    gRandom = 0;
  }
  
  gRandom = new TRandom3();
  gRandom->SetSeed();
}


AliKPiDecayMuon::~AliKPiDecayMuon()
{
  if(fOutputFile)
    delete fOutputFile;
  
  if(fTree)
    delete fTree;
  
  if(fDecayer)
    delete fDecayer;
  
  TClonesArray *fPartArray = new TClonesArray("TParticle",1000);
}


void AliKPiDecayMuon::RunClass(Int_t nEvents)
{
  TString partName;
  if (fPdgH==443) partName="Jpsi";
  else if (fPdgH==211) partName="Pion";
  else if (fPdgH==321) partName="Kaon";
   
//fileNmin, fileNmax
  for(Int_t j=fileNmin;j<2;j++){ 
     fOutputName = Form("%sDecayMuonNtuple_0%0d.root", partName.Data(), j+1);
     fOutputFile =  new TFile(fOutputName.Data(), "RECREATE");
     Init();
     for(Int_t iEv=0; iEv<nEvents; iEv++)
  	{
   	 if(iEv==0 || iEv%1000==0)
           cout << j+1 << "'th OutFile=> iEvent generation: " << iEv << "/" << nEvents << "\r" << flush;
         else if(iEv == nEvents-1)
           cout << j+1 << "'th OutFile=> iEvent generation: " << nEvents << "/" << nEvents << "\r" << flush;
         if(iEv == nEvents-1)
         cout << endl;
         Make();
        }
       
      fOutputFile->cd();
      fTree->Write();
     }
      fOutputFile->Close();
}


void AliKPiDecayMuon::Init()
{
  //fOutputFile = new TFile(fOutputName.Data(), "RECREATE");
  fTree = new TTree("bkgJpsiMuonTuple","bkgJpsiMuonTuple");
  fTree->Branch("fPtH",&fPtH,"fPtH/F");
  fTree->Branch("fEtaH",&fEtaH,"fEtaH/F");
  fTree->Branch("fRapH",&fRapH,"fRapH/F");
  fTree->Branch("fPdgH",&fPdgH,"fPdgH/F"); 
  
  //Mu-
 // fTree->Branch("NMuons",&fNMuons,"NMuons/I");
  fTree->Branch("fRhoHMu1",&fRhoH1,"fRhoH1/F");
  fTree->Branch("fPdgLMu1",&fPdgL1,"fPdgL1/F");
  fTree->Branch("fPtLMu1",&fPtL1,"fPtL1/F");
  fTree->Branch("fEtaLMu1",&fEtaL1,"fEtaL1/F");
  fTree->Branch("fRapLMu1",&fRapL1,"fRapL1/F");
  
//Mu+
  fTree->Branch("fRhoHMu2",&fRhoH2,"fRhoH2/F");
  fTree->Branch("fPdgLMu2",&fPdgL2,"fPdgL2/F");
  fTree->Branch("fPtLMu2",&fPtL2,"fPtL2/F");
  fTree->Branch("fEtaLMu2",&fEtaL2,"fEtaL2/F");
  fTree->Branch("fRapLMu2",&fRapL2,"fRapL2");
 
  fPartArray = new TClonesArray("TParticle",1000);
}


void AliKPiDecayMuon::Make()
{
  
  Int_t signHad;
  if (fPdgH==443) signHad =  1;   
  else signHad = (gRandom->Rndm()>0.5) ? 1 : -1;
  fPdgH*=signHad;
  fDecayer = new AliDecayerPythia();
  //fDecayer->SwitchOffHeavyFlavour(); //HeavyFlavourOff(kTRUE)
  //fDecayer->ForceParticleDecay(443,13,2);
  if(TMath::Abs(fPdgH)==443) fDecayer->SetForceDecay(kJpsiDiMuon);
  else if(TMath::Abs(fPdgH)==211) fDecayer->SetForceDecay(kPiToMu);
  else if(TMath::Abs(fPdgH)==321) fDecayer->SetForceDecay(kKaToMu);
  else return;
  fDecayer->Init();
  
  const Double_t massHadron = TDatabasePDG::Instance()->GetParticle(TMath::Abs(fPdgH))->Mass();
  //cout << "massHadron =  " << massHadron << endl;
  
  fPtH = gRandom->Uniform(fPtMin,fPtMax);
  fRapH = gRandom->Uniform(fYMin,fYMax);
  fEtaH = YtoEta(fPtH,massHadron,fRapH);
  
  TLorentzVector *lorentzP = new TLorentzVector();
  lorentzP->SetPtEtaPhiM(fPtH,fEtaH,0.,massHadron);
  
  fDecayer->Decay(fPdgH,lorentzP);
 
  Float_t pdg, Vz, Pt, Y, Eta; 
  for(Int_t p=0; p<fDecayer->ImportParticles(fPartArray); p++)
  {  
    fParticle = (TParticle*)fPartArray->At(p);
    
    // mu-(13), mu+(-13)
    if(TMath::Abs(fParticle->GetPdgCode())!=13) continue;
    //if(fParticle->Eta()<-4.3 || fParticle->Eta()>-2.2) continue;
    //if(fParticle->Vz()>20 || fParticle->Vz()<-510) continue;
    
    fNMuons++;
    if(fParticle->GetPdgCode()>0) {
       fRhoH1  = fParticle->Vz();
       fPdgL1 =  fParticle->GetPdgCode(); 
       fPtL1   = fParticle->Pt();
       fRapL1  = fParticle->Y();
       fEtaL1  = fParticle->Eta();
    }

    if(fParticle->GetPdgCode()<0) {
      fRhoH2  = fParticle->Vz();
      fPdgL2 =  fParticle->GetPdgCode();  
      fPtL2   = fParticle->Pt();
      fRapL2  = fParticle->Y();
      fEtaL2  = fParticle->Eta();
    }
 
  }

  fTree->Fill();
  fPartArray->Clear("C");
}


Float_t AliKPiDecayMuon::YtoEta(Float_t pt, Float_t mm, Float_t rap)
{
  return ASinH(TMath::SinH(rap)*Sqrt(pt*pt+mm*mm)/pt);
}


void AliKPiDecayMuon::Term()
{
  fOutputFile->cd();
  fTree->Write();
  fOutputFile->Close();
}

