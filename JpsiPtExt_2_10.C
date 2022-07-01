//percentiles 2_10, 10_20, 20_40, 40_60, 60_80, 80_90%
// Input Jpsi Pt distribution is from HEPData JpsiToMuMu for pPb 8.16 TeV
// Jpsi Pt spectra 0-20 GeV/c and extrapolate upto 40 GeV/c.
// Fit with Levy-Tsallis distribution.
// No chi2/NDF cut applied.
Double_t Tsallis(Double_t *var, Double_t *par);
Double_t JpsiPt(Double_t *var, Double_t *par);
void JpsiPtExt_2_10(Bool_t IsOutput=0)
{
gStyle->SetOptStat(0);
    
Int_t nTrails = 3*pow(10,3);
Float_t dFitI = 0.5, dFitF = 16.;
Float_t dExtI = 16., dExtF = 40.;
        
//const Double_t Xbins[] = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 7., 9., 11., 13., };
const Double_t Xbins[] = {0,1,2,3,4,5,6,8,10,16., 22., 28., 34.,40.};
Int_t Nbinsx     = sizeof(Xbins)/sizeof(Double_t)-1;
cout << "Nbinsx = " << Nbinsx << endl;    
const Double_t xbins[] = {0,1, 2,3,4,5,6,8,10,16};
Int_t nbinsx     = sizeof(xbins)/sizeof(Double_t)-1;
cout << "nbinsx = " << nbinsx << endl;
    
const Double_t Ext_xbins[] = {16., 22., 28., 34.,40.};
Int_t Ext_nbinsx     = sizeof(Ext_xbins)/sizeof(Double_t)-1;
cout << "Ext_nbinsx = " << Ext_nbinsx << endl;
    
TCanvas *c1 = new TCanvas("c1","");
c1->Range(0., 0., 1., 1.);
c1->SetLogy();

TH1D *hTemp = new TH1D("hTemp", "hTemp", Nbinsx, Xbins);
hTemp->SetTitle("");
//hTemp->SetAxisRange(0, 30+0.1,"X");
hTemp->SetAxisRange(1e-5, 1e+05,"Y");
hTemp->SetXTitle("#it{p}_{T} (GeV/c)");
hTemp->SetYTitle("d^{2}#sigma/(dp_{T}dy) (#mub/(GeV/#it{c}))");
hTemp->GetYaxis()->SetTitleOffset(1.2);
/*
hTemp->GetXaxis()->SetTickLength(0.04);
hTemp->GetYaxis()->SetTickLength(0.02);
hTemp->GetXaxis()->SetLabelFont(42);
hTemp->GetYaxis()->SetLabelFont(42);
hTemp->GetXaxis()->SetLabelSize(0.05);
hTemp->GetYaxis()->SetLabelSize(0.03);
hTemp->GetXaxis()->SetLabelOffset(0.01);
hTemp->GetYaxis()->SetLabelOffset(0.01);
hTemp->GetXaxis()->SetTitleFont(42);
hTemp->GetYaxis()->SetTitleFont(42);
hTemp->GetYaxis()->SetTitleOffset(1.30);
hTemp->GetXaxis()->SetTitleSize(0.05);
hTemp->GetYaxis()->SetTitleSize(0.03);
hTemp->GetYaxis()->SetNdivisions(508);
*/
hTemp->DrawCopy("");

TFile* infile = new TFile("~/Desktop/MuonVsMultiplicity/files/JPsi2022/multbins/final.root", "READ");
//infile->ls(); 
TDirectoryFile *Table1 = (TDirectoryFile*)infile->FindObjectAny("Table 2"); 
//Table1->ls(); 
TH1F *Hist1D_y1 = (TH1F*)Table1->FindObjectAny("Hist1D_y1");
TH1F *Hist1D_y1_e1 = (TH1F*)Table1->FindObjectAny("Hist1D_y1_e1"); // stat
TH1F *Hist1D_y1_e2 = (TH1F*)Table1->FindObjectAny("Hist1D_y1_e2");
TH1F *Hist1D_y1_e3 = (TH1F*)Table1->FindObjectAny("Hist1D_y1_e3");
//TH1F *Hist1D_y1_e4 = (TH1F*)Table1->FindObjectAny("Hist1D_y1_e4");
//Hist1D_y1->Draw();
    
TH1D *hData = new TH1D("fWeightPt","fWeightPt",Nbinsx,Xbins); hData->Sumw2();
//define x,y, ex,ey to get the TGraph with errors
Float_t xR[nbinsx], yR[nbinsx], exR[nbinsx], eyR[nbinsx];

for (Int_t j=0; j<nbinsx; j++) {
    xR[j]   = Hist1D_y1->GetBinCenter(j+1);
    yR[j]   = Hist1D_y1->GetBinContent(j+1);
    exR[j]  = Hist1D_y1->GetBinWidth(j+1)/2.;
    eyR[j]  =sqrt(pow(Hist1D_y1_e1->GetBinContent(j+1),2)+pow(Hist1D_y1_e2->GetBinContent(j+1),2)+pow(Hist1D_y1_e3->GetBinContent(j+1),2));
    hData->SetBinContent(j+1,yR[j]);
    hData->SetBinError(j+1,eyR[j]);
    cout << xR[j] << "; " << yR[j] << "; " << exR[j] << "; " << eyR[j] <<  endl;
}
// return;
//hData->Draw("SAME");
    
TGraphAsymmErrors *g1 = new TGraphAsymmErrors(nbinsx, xR, yR, exR, exR, eyR, eyR);
TH1D *hTrial[nTrails];
    
for (Int_t i=0; i<nTrails; i++) {
    hTrial[i] = new TH1D(Form("hTrial_%d",i+1),Form("hTrial_%d",i+1),nbinsx,xbins);
    hTrial[i]->Sumw2();
    }

Float_t dVal[nbinsx][nTrails], dE[nbinsx][nTrails], gRandTrial[nbinsx][nTrails];

for (Int_t i=0; i<nTrails; i++) {
     for (Int_t j=0; j<nbinsx; j++) {
         dVal[j][i] = hData->GetBinContent(j+1);
         dE[j][i] = hData->GetBinError(j+1);
         gRandTrial[j][i]=gRandom->Gaus(dVal[j][i],dE[j][i]);
         hTrial[i]->SetBinContent(j+1,gRandTrial[j][i]);
         hTrial[i]->SetBinError(j+1, dE[j][i]);
         //cout << dVal[j][i] << setw(20) << dE[j][i] << endl;
         }
        //if(i==0)hTrial[i]->Draw();
        //else hTrial[i]->Draw("SAME");
     }

TF1 *fFit[nTrails],  *fExt[nTrails];
TH1D *hExt[nTrails];

Float_t p0,p1,p2;
p0=4.79978e+02, p1=9.10523e+00, p2=7.43153e-01; //p-Pb
// p0=2.21862e+02, p1=9.50128e+00, p2=8.34651e-01; // Pb-p

for (Int_t i=0; i<nTrails; i++) {
    fFit[i] = new TF1(Form("fFit_%d",i+1), Tsallis, dFitI, dFitF, 3);
    fFit[i]->SetParameters(p0,p1,p2);
    
    fExt[i] = new TF1(Form("fExt_%d",i+1), Tsallis, dExtI, dExtF, 3);
    
    hExt[i] = new TH1D(Form("hExt_%d",i+1),Form("hExt_%d",i+1),Ext_nbinsx, Ext_xbins);
    hExt[i]->Sumw2();
    }

Float_t chi2[nTrails], ndf[nTrails];
int chi2True=0;
    
for (Int_t i=0; i<nTrails; i++) {
    cout << "****** " << i+1 << "'th trial ******" << endl;

    hTrial[i]->Fit(fFit[i], "NR+", "");
    fExt[i]->SetParameter(0, fFit[i]->GetParameter(0));
    fExt[i]->SetParameter(1, fFit[i]->GetParameter(1));
    fExt[i]->SetParameter(2, fFit[i]->GetParameter(2));
    chi2[i] = fFit[i]->GetChisquare(); ndf[i] = fFit[i]->GetNDF();
    hExt[i]->Add(fExt[i]);
    cout << "chi2[" << i << "] = " << chi2[i] << "  ndf[" << i<< "] = " << ndf[i] << endl;
    if(chi2[i]/ndf[i]<=1.5) chi2True++;
   }
    cout << "chi2True = " << chi2True << endl;
    
 
 Double_t xVal[Ext_nbinsx][nTrails], yVal[Ext_nbinsx][nTrails];
     
 for(int i=0;i<nTrails;i++){
     for(int j=0;j<Ext_nbinsx;j++){
        yVal[j][i] = hExt[i]->GetBinContent(j+1);
        xVal[j][i] = hExt[i]->GetBinCenter(j+1);
     }
   }
    
 Double_t xValpT[Ext_nbinsx], exValpTErr[Ext_nbinsx];
 Double_t xMVal[Ext_nbinsx], xMErr[Ext_nbinsx];
 Double_t yMVal[Ext_nbinsx], yMErr[Ext_nbinsx];
 Double_t yValpT[nTrails];
    
    
 for(int j=0;j<Ext_nbinsx;j++){
     for(int i=0;i<nTrails;i++){
         yValpT[i] = yVal[j][i];
     }
     
     yMVal[j]=TMath::Mean(nTrails,yValpT);
     yMErr[j]=TMath::RMS(nTrails,yValpT);
     xMVal[j]= hExt[0]->GetBinCenter(j+1);
     xMErr[j] = hExt[0]->GetBinWidth(j+1)/2.;

     hData->SetBinContent(nbinsx+j+1, yMVal[j]);
     hData->SetBinError(nbinsx+j+1, yMErr[j]);
    }
    
  hData->SetLineWidth(3);
  hData->SetLineWidth(2);
  hData->SetLineColor(1);
  hData->SetMarkerStyle(1);
  hData->SetMarkerColor(1);
  hData->Draw("same");
    
  for (Int_t i=0; i<nTrails; i++) {
      fExt[i]->SetLineColor(2); fExt[i]->SetLineWidth(4); fExt[i]->Draw("SAME");
    }
    
  g1->SetMarkerStyle(20);
  g1->SetMarkerColor(3);
  g1->SetFillStyle(0);
  g1->SetFillColor(3);
  g1->SetLineWidth(2);
  g1->SetLineColor(3);
  g1->Draw("2");
    
  TGraphErrors *gExt =  new TGraphErrors(Ext_nbinsx,xMVal,yMVal,xMErr,yMErr);
  gExt->SetLineWidth(2);
  gExt->SetLineStyle(1);
  gExt->SetLineColor(4);
  gExt->SetMarkerStyle(24);
  gExt->SetMarkerColor(4);
  gExt->SetFillStyle(0);
  gExt->SetFillColor(4);
  gExt->Draw("2");
    
  TLegend *leg = new TLegend(0.5, 0.6, 0.85, 0.85);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(hData,Form("J/#psi #rightarrow #mu^{+}#mu^{-}"),"LP");
  leg->AddEntry(g1, "#sqrt{stat^{2}+sys^{2}}","F");
  leg->AddEntry(fExt[0], "extrapolated results","L");
  leg->AddEntry(gExt, "one sigma uncertainty","F");
  leg->SetNColumns(1);
  leg->Draw();
//     
  TLatex la;
  la.SetNDC();
  la.SetTextSize(0.04);
  la.SetTextAlign(18);//12
  la.DrawLatex(0.18,0.85,Form("p-Pb at #sqrt{s_{NN}} = 8.16 TeV"));
  la.DrawLatex(0.18,0.78,Form("2.03 < y_{cms} < 3.53"));
  la.DrawLatex(0.21,0.71,"2-10 %");
    
  if(IsOutput){
      TFile *outfile = new TFile(Form("output/Pbp/tsallis/WeightPtJpsiTsallis_2_10.root"),"RECREATE");
//       hData->Scale(1/(Double_t)hData->GetBinContent(1));
      hData->Write();
      //huncertaintyPi->Write();
      outfile->Write();
      outfile->Close();
  }
    
}

Double_t JpsiPt(Double_t *var, Double_t *par) {
  Double_t pt   = var[0];
  Double_t c    = par[0];
  Double_t p0   = par[1];
  Double_t n    = par[2];
    
  return (c*pt)/pow((1+pow((pt/p0),2)),n);
  //return C*(pt/(pow((1+TMath::Power((pt/p0),2)),n)));

}

Double_t Tsallis(Double_t *var, Double_t *par) {
  Double_t pt   = var[0];
  Double_t norm = par[0];
  //Double_t m0    = par[1];
  Double_t n    = par[1];
  Double_t T    = par[2];
 
  const Double_t m0    = 3.096;
  Double_t mt = TMath::Sqrt(pt*pt+m0*m0);

  return norm * pt * TMath::Power((1 + (mt-m0)/(n*T)),-1.*n);

}



