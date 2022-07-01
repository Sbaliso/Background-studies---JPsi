#include "Riostream.h"  
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TStyle.h"

double function(double* xx,double* pp);
void SetStyle(Bool_t graypalette=kFALSE);
void fit_rapidityextrap() 
{
Double_t pp0, pp1, pp2, pp3, pp4, pp5;  
    
    
 TH1D* histogram();
//  SetStyle();
 c = new TCanvas;
 c->SetLogy();
//  TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
// //   pad1->SetLogy();
//   pad1->SetBottomMargin(0);
//   pad1->Draw();

//   TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.4);
//   pad2->SetTopMargin(0);
//   pad2->SetBottomMargin(0.25);
//   pad2->Draw();
//   SetStyle();
//   gStyle->SetOptFit(1);
//  gStyle->SetOptFit(1);  
 TH1D* hsum = 0;
 hsum = histogram();
 hsum->SetLineWidth(3);
  
 TF1* func = new TF1("fun",function,-6,6.,6);
  pp0 = -1.62221e+07;
  pp1 = -8.41689e+07;
  pp2 = -3.04475e+07;
  pp3 = 1.27233e+06;
  pp4 = -44574.9;
  pp5 = 711.382;
  
 
  func->SetParameter(0,pp0  );
  func->SetParameter(1,pp1  );
  func->SetParameter(2,pp2  );
  func->SetParameter(3,pp3  );
  func->SetParameter(4,pp4  );
  func->SetParameter(5,pp5  );
//   func->SetParameter(6,pp6  );
//   func->SetParameter(7,pp7  ); 
 
 
 
 
    hsum->Fit("fun","/*ER0*/","",-6,6);
//  hsum->Fit("fun","/*ER0*/","",-4,-2.5);
//  hsum->Fit("fun","/*ER0*/","",-4,-2.5);
//  pad1->cd();
 hsum->GetYaxis()->SetTitle("d#sigma/dy");
 hsum->GetYaxis()->SetLabelSize(0.05);
 hsum->Draw("hist");
 func->Draw("same");
//  hsum->GetXaxis()->SetLimits(-4.335,-3.085);
 
 double pPbY[200]; 
 double PbpY[200];
 double pPb;
 double Pbp;
 double epPbY[200];
 double ePbpY[200];
 double xpPb;
 double xPbp;
 
 const nbinspPb = 6;
 const nbinsPbp = 6;
 
 double xbinspPb[nbinspPb+1] = {2.1,2.4,2.6,2.9,3.1,3.4};
 double xbinsPbp[nbinsPbp+1] = {-4.335,-4.085,-3.835,-3.585,-3.335,-3.085};
 
 TH1D *hpPb = new TH1D("pPb","pPb",nbinspPb,xbinspPb);
 TH1D *hPbp = new TH1D("Pbp","Pbp",nbinsPbp,xbinsPbp);
 
 ifstream infpPb("pPbrapY.txt");
 ifstream infPbp("PbprapY.txt");
 
 for(int i=0; i<5; i++){
      infpPb >> xpPb >> pPb >> epPbY[200] ;
      infPbp >> xPbp >> Pbp >> ePbpY[200] ;
     
     
  pPbY[i] = pPb;   
  PbpY[i] = Pbp;
  
  hpPb->SetBinContent(i+1,pPbY[i]);
  hPbp->SetBinContent(i+1,PbpY[i]);
  
  hpPb->SetBinError(i+1,epPbY[i]);
  hPbp->SetBinError(i+1,ePbpY[i]); 
  
     
}
 
 TCanvas *cpPb = new TCanvas();
//  hsum->Draw();
//  hsum->Fit("fun","/*ER0*/","",-6,6);
 hpPb->Draw();
 hpPb->SaveAs("rapiditypPb.root");
 
 TCanvas *cPbp = new TCanvas();
//  hsum->Draw();
//  hsum->Fit("fun","/*ER0*/","",-6,6);
 hPbp->Draw("same");
 hPbp->SaveAs("rapidityPbp.root");
 
 
 
 
 
 
 Double_t avg = hsum->Integral()/24;
 
 cout << "avg= " << avg << endl; 
 cout << "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn" << endl;
 TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
 leg->AddEntry(hsum, "Sum", "flp");
 leg->AddEntry(func, "Fit", "flp");
 // leg->AddEntry(hbtocR, "#mu #leftarrow D #leftarrow b", "flp");
 // leg->AddEntry(hsumR, "Total", "flp");
 leg->Draw();
 
  cout << "  pp0 = " << func->GetParameter(0)<<";"  <<endl;
  cout << "  pp1 = " << func->GetParameter(1)<<";"  <<endl;
  cout << "  pp2 = " << func->GetParameter(2)<<";"  <<endl;
  cout << "  pp3 = " << func->GetParameter(3)<<";"  <<endl;
  cout << "  pp4 = " << func->GetParameter(4)<<";"  <<endl;
  cout << "  pp5 = " << func->GetParameter(5)<<";"  <<endl;
 
// gStyle->SetOptTitle(0);
//   pad2->cd();
// //   cc = new TCanvas;
//  TH1D *hratio = (TH1D*)hsum->Clone("ratio");
//  hratio->Sumw2();
// //  hfunc->Draw();
// //  hsum->Draw("same");
//   hratio->Divide(func);
//   hratio->GetYaxis()->SetRangeUser(0.95,1.05);
//   hratio->GetXaxis()->SetLabelSize(0.05);
//   hratio->GetYaxis()->SetLabelSize(0.07);
//   hratio->GetXaxis()->SetTitle("#eta");
//   hratio->GetYaxis()->SetTitle("FONLL/Fit");
//   hratio->GetXaxis()->SetTitleSize(0.065);
//   hratio->SetLineWidth(1.2);
//   
//   hratio->Fit("pol1","R0","",-4,-2.5);
//   hratio->Draw("hist");
//   hratio->GetFunction("pol1")->Draw("same");
//   hratio->SetLineWidth(3);
  
}

TH1D* histogram(){
 TFile* file = TFile::Open("/home/sibaliso/16ktest/fit//htotalRap.root","read"); 
  hsum = (TH1D*)file->Get("tot");
  hsum=hsum->Scale(1e-5);
  return hsum;
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
