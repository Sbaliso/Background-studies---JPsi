/// To generate muon decaying from Jpsi/Pion/Kaon
// Set partName as per the hadron to be decayed into muon
// Jpsi=>0, Pion=>1, Kaon=>2;
// select file number range into the loop in AliKPiDecayMuon.cxx
void RunHadronGeneration(Int_t nEvents=1e4, Int_t partName=0)
{
  if(!LoadLibraries()) return;
    
  Float_t pdg;
  if(partName==0) pdg=443;
  else if(partName==1) pdg=211;
  else if(partName==2) pdg=321;
  
  TStopwatch timer;
  timer.Start();

  AliKPiDecayMuon *maker = new AliKPiDecayMuon();
  maker->SetPDG(pdg);
  maker->SetFileRange(0,2); // number of files, put ranges
  maker->SetPtRange(0,50);
  maker->SetYRange(-6.,6.);
  maker->RunClass(nEvents);
  
  //timer.Stop();
  //timer.Print();
}


Bool_t LoadLibraries()
{
  if (gSystem->Load("libCore")          <0) return kFALSE;
  if (gSystem->Load("libTree")          <0) return kFALSE;
  if (gSystem->Load("libGeom")          <0) return kFALSE;
  if (gSystem->Load("libVMC")           <0) return kFALSE;
  if (gSystem->Load("libXMLIO")         <0) return kFALSE;
  if (gSystem->Load("libPhysics")       <0) return kFALSE;
  if (gSystem->Load("libXMLParser")     <0) return kFALSE;
  if (gSystem->Load("libProof")         <0) return kFALSE;
  if (gSystem->Load("libProofPlayer")   <0) return kFALSE;
  if (gSystem->Load("libMinuit")        <0) return kFALSE;
  if (gSystem->Load("libGui")           <0) return kFALSE;

  gSystem->AddIncludePath("-I$ALICE_ROOT/include");
  if (gSystem->Load("libSTEERBase")     <0) return kFALSE;
  if (gSystem->Load("libESD")           <0) return kFALSE;
  if (gSystem->Load("libAOD")           <0) return kFALSE;
  if (gSystem->Load("libANALYSIS")      <0) return kFALSE;
  if (gSystem->Load("libANALYSISalice") <0) return kFALSE;
  if (gSystem->Load("libCORRFW")        <0) return kFALSE;

  TString includePath = "-I${ALICE_ROOT}/EVGEN ";
  includePath        += "-I${ALICE_ROOT}/PYTHIA8 ";
  includePath        += "-I${ALICE_ROOT}/PWG/FLOW/Base";
  gSystem->AddIncludePath(includePath.Data());
  if (gSystem->Load("libEVGEN")         <0) return kFALSE;
  if (gSystem->Load("libFASTSIM")       <0) return kFALSE;
  if (gSystem->Load("liblhapdf")        <0) return kFALSE;
  if (gSystem->Load("libEGPythia6")     <0) return kFALSE;
  if (gSystem->Load("libpythia6")       <0) return kFALSE;
  if (gSystem->Load("libAliPythia6")    <0) return kFALSE;

  gROOT->LoadMacro("AliKPiDecayMuon.cxx+");
  return kTRUE;
}
