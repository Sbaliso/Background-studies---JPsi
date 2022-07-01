#include "TGraphErrors.h"

double function(double* xx,double* pp);

void Jpsirapextrap(){

Double_t pp0, pp1, pp2, pp3, pp4, pp5;    
ifstream infpPb("pPbrap.txt");
ifstream infPbp("Pbprap.txt");

 Double_t xpPb[200], expPb[200], ypPb[200], eypPb[200];   
 Double_t xPbp[200], exPbp[200], yPbp[200], eyPbp[200];
 
 Double_t vxpPb , vexpPb , vypPb , veypPb;
 Double_t vxPbp , vexPbp , vyPbp , veyPbp;
 
 TH1D *hpPb = new TH1D("hpPb","hpPb",6,-4.335,-3.085);
 TH1D *hPbp = new TH1D("hPbp","hPbp",6,-4.335,-3.085);
 
 TH1D *hpPbnew = new TH1D("hpPbnew","hpPbnew",48,-6,6);
 TH1D *hPbpnew = new TH1D("hPbpnew","hPbpnew",48,-6,6);
 Int_t n =6;
   
 for(int i=0; i<6; i++){
     
  infpPb >> vxpPb >> vexpPb >> vypPb >> veypPb;  
  infPbp >> vxPbp >> vexPbp >> vyPbp >> veyPbp;  
  
     hpPb->SetBinContent(i+1,vypPb);
     hPbp->SetBinContent(i+1,vyPbp);
     
      hpPb->SetBinError(i+1,veypPb);
      hPbp->SetBinError(i+1,veyPbp);
      
      
}
 TCanvas * c1 = new TCanvas();
  hpPb->Draw();
  hpPbnew->Draw("same");
  hpPbnew->GetXaxis()->SetLimits(-4,-2.5);

TF1* func = new TF1("fun",gaus,-6,6.,6);  
//   pp0 = -1.62221e+07;  
//   pp1 = -8.41689e+07;  
//   pp2 = -3.04475e+07;  
//   pp3 = 1.27233e+06;  
//   pp4 = -44574.9;  
//   pp5 = 711.382;  
//     
//    
//   func->SetParameter(0,pp0  );  
//   func->SetParameter(1,pp1  );  
//   func->SetParameter(2,pp2  );  
//   func->SetParameter(3,pp3  );  
//   func->SetParameter(4,pp4  );  
//   func->SetParameter(5,pp5  );  
  
hpPb->Fit("fun","","",-6,6);

     
//   TCanvas * c1 = new TCanvas();
//   TGraphErrors *g1 = new TGraphErrors(n,vxpPb, vexpPb , vypPb , veypPb);
//   TGraphErrors *g2 = new TGraphErrors(n,vxPbp, vexPbp , vyPbp , veyPbp);
//   g1->Draw();
//   g2->Draw("same");
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
