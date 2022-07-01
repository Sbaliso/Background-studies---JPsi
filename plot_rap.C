#include "Riostream.h"  
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TStyle.h"

double powerlaw(double* xx,double* pp);
double function(double* xx,double* pp);

void plot_rap() 
{
 
 float pPb;
 float Pbp;
 float pPbY[200];
 float epPbY[200];
 float pPbX[13];
 float epPbX[200];
 float xpPb;
 float expPb;
 float ypPb;
 float eypPb;
 
 float Pbp;
 float Pbp;
 float PbpY[200];
 float ePbpY[200];
 float PbpX[13];
 float ePbpX[200];
 float xPbp;
 float exPbp;
 float yPbp;
 float eyPbp;
 
 
 
 
 
 int nbinspPb = 6;
 Double_t pp0, pp1, pp2; 
 
 TF1* funcpowerlaw = new TF1("fJpsi_Y",powlaw,-6,6.,3);
  pp0 = 2.39585e+03;
  pp1 = 2.83585e+00;
  pp2 = 3.44820e-01;
  
  fJpsi_Y->SetParameter(0,pp0  );
  fJpsi_Y->SetParameter(1,pp1  );
  fJpsi_Y->SetParameter(2,pp2  );
 
//   double xbinspPb[nbinspPb+1] = {-4.335, -4.085, -3.835,-3.585,-3.335,-3.085, 2.155, 2.405, 2.655, 2.905, 3.155, 3.405};
//   double xbinspPb[nbinspPb+1] = {-4.335, -4.085, -3.835,-3.585,-3.335,-3.085, 2.155, 2.405, 2.655, 2.905, 3.155, 3.405};
 
//  TH1D *hpPb = new TH1D("pPb","pPb",nbinspPb,xbinspPb);
 
 ifstream infpPb("pPbrap.txt");
 ifstream infPbp("Pbprap.txt");
 
 for(int i=0; i<6; i++){
      infpPb >> xpPb >> expPb >> ypPb >> eypPb[200] ;
      infPbp >> xPbp >> exPbp >> yPbp >> eyPbp[200] ;
     
     
   pPbY[i]  = ypPb;   
   epPbY[i] = eypPb;
  
    pPbX[i] = xpPb; 
    epPbX[i] = expPb;
    
    PbpY[i]  = yPbp;  
    ePbpY[i] = eyPbp;
    
     PbpX[i] = xPbp; 
     ePbpX[i] = exPbp;
    
    
}



TCanvas *cpPb = new TCanvas();
 TGraphErrors *grpPb = new TGraphErrors(nbinspPb,pPbX,pPbY,epPbX,epPbY); 
  grpPb->Draw("");
//   grpPb->Fit("fJpsi_Y","","",-6,6);
  
//   TCanvas *cPbp = new TCanvas();
   TGraphErrors *grPbp = new TGraphErrors(nbinspPb,PbpX,PbpY,ePbpX,ePbpY); 
    grPbp->Draw("same");
//     grPbp->Fit("fJpsi_Y","","",-6,6);
  
TH1F *hpPb = new TH1F("pPb","pPb",5,pPbX);
TH1F *hPbp = new TH1F("Pbp","Pbp",5,PbpX); // the histogram (you should set the number of bins, the title etc)
int nPoints = grpPb->GetN(); // number of points in your TGraph
for(int i=0; i < nPoints; i++) {  
   double xbinpPb,ybinpPb;  
   double xbinPbp,ybinPbp; 
   grpPb->GetPoint(i, xbinpPb, ybinpPb);
   grPbp->GetPoint(i, xbinPbp, ybinPbp);
   
   
//    cout << xpPb << " " << ypPb << endl;
   hpPb->Fill(xbinpPb,ybinpPb);
   hPbp->Fill(xbinPbp,ybinPbp);
   
}  
TCanvas *c1pPb = new TCanvas();
// TH1D *hist = new TH1D("","",24,-6,6);
// hist->Draw();
hpPb->Draw("e");
// hpPb->Fit("fJpsi_Y","","",-6,6);
hpPb->GetXaxis()->SetRangeUser(-6,6);

TCanvas *c1Pbp = new TCanvas();  
hPbp->Draw("e");
// hPbp->Fit("gaus","","",-6,6);

// TCanvas *c2Pbp = new TCanvas();
// TH1D *hPbpnew = (TH1D*)hPbp->Clone("JPsi_Y");
// hPbpnew->Add(hpPb);
// hPbpnew->Draw();
// hPbpnew->GetXaxis()->SetLimits(-6,6);

}

double function(double* xx,double* pp){

  double x = xx[0];
  double a = pp[5];
  double b = pp[4];
  double c = pp[3];
  double d = pp[2];
  double e = pp[1];
  double f = pp[0];
  
//   double function =  e*TMath::Power(x,4) +  d*TMath::Power(x,3) +  c*TMath::Power(x,2) + b*TMath::Power(x,1) + a;
  double function = a*TMath::Power(x,8) + b*TMath::Power(x,6) +  c*TMath::Power(x,4) +  d*TMath::Power(x,2) + e*TMath::Power(x,1) + f;
  
  return function;
  
}

double powlaw(double* xx,double* pp){

  double x = xx[0];
  double a = pp[0];
  double b = pp[1];
  double c = pp[2];
    
  double powlaw = a/TMath::Power((TMath::Power(b,2) + TMath::Power(x,2)),c);
  
  return powlaw;
  
}


void SetStyle(Bool_t graypalette) {
  cout << "Setting style!" << endl;
  
  gStyle->Reset("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  if(graypalette) gStyle->SetPalette(8,0);
  else gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  gStyle->SetFuncColor(kRed);
  gStyle->SetLineWidth(2);
  gStyle->SetLabelSize(0.045,"xyz");
  gStyle->SetLabelOffset(0.01,"y");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelColor(kBlack,"xyz");
  gStyle->SetTitleSize(0.065,"xyz");
  gStyle->SetTitleOffset(0.5,"y");
  gStyle->SetTitleOffset(0.5,"x");
  gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);
  //  gStyle->SetTickLength(0.04,"X");  gStyle->SetTickLength(0.04,"Y"); 

  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  //  gStyle->SetFillColor(kWhite);
  gStyle->SetLegendFont(42);


}
