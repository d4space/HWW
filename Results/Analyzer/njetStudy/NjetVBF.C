// Run as root -l NjetVBF.C

#include "TStyle.h"
#include "../../../Utils/const.h"
//#include "../../../Utils/CPlot.hh"
//#include "../../../Utils/MitStyleRemix.hh"
#include <fstream>
#include <iostream>
#include <iomanip>

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TString.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLine.h"
#include "TGraphErrors.h"

//#include "RooRealVar.h"
//#include "RooPoisson.h"
//#include "RooPolynomial.h"
//#include "RooLandau.h"
//#include "RooPlot.h"
//#include "RooBinning.h"
//#include "RooExponential.h"
//#include "RooBreitWigner.h"
//#include "RooCBShape.h"
//#include "RooDataHist.h"
//#include "RooAddPdf.h"
//#include "RooFitResult.h"
//#include "RooNLLVar.h"
//#include "RooMinuit.h"
//#include "RooChi2Var.h"
//#include "RooGenericPdf.h"
//#include "RooFFTConvPdf.h"

#include "../AnaSrc/NjetBin.h"

int NjetVBF()
{
  TString OutDir = "CtlPot";
  //TString OutDir = "mWW_reweighted_step1";
  gSystem->mkdir(OutDir);
  
  TFile *f_phn_1;
  TFile *f_phn_9;
  TFile *f_phn_25;
  TFile *f_pow;

  f_phn_1  = new TFile("phantom_1SM/phantom_1SM_CommonCut_VBFnjet.root");
  f_phn_9  = new TFile("phantom_9SM/phantom_9SM_CommonCut_VBFnjet.root");
  f_phn_25 = new TFile("phantom_25SM/phantom_25SM_CommonCut_VBFnjet.root");
  f_pow    = new TFile("POWHEG_VBF/POWHEG_VBF_CommonCut_VBFnjet.root");

  char tmpName[50];
  char histName[50];
  char jetName[50];
  char Yield[50];

  //++++++++++++++++++++++++++++
  //Histograms
  //++++++++++++++++++++++++++++
  // Phantom---------------

  TH1D* h1_Njet_Phn_1_Wevt;
  TH1D* h1_Njet_Phn_9_Wevt;
  TH1D* h1_Njet_Phn_25_Wevt;
  TH1D* h1_Njet_Phn_Sg_Wevt;
  TH1D* h1_Njet_Phn_1_NoW;
  TH1D* h1_Njet_Phn_9_NoW;
  TH1D* h1_Njet_Phn_25_NoW;
  TH1D* h1_Njet_Phn_Sg_NoW;

  TH1D* h1_Njet_Phn_1_Wevt_NoCut;
  TH1D* h1_Njet_Phn_9_Wevt_NoCut;
  TH1D* h1_Njet_Phn_25_Wevt_NoCut;
  TH1D* h1_Njet_Phn_Sg_Wevt_NoCut;
  TH1D* h1_Njet_Phn_1_NoW_NoCut;
  TH1D* h1_Njet_Phn_9_NoW_NoCut;
  TH1D* h1_Njet_Phn_25_NoW_NoCut;
  TH1D* h1_Njet_Phn_Sg_NoW_NoCut;

  // Powheg------------------------

  TH1D* h1_Njet_Pow_NoW;
  TH1D* h1_Njet_Pow_WevtPow2Gen;
  TH1D* h1_Njet_Pow_NoW_NoCut;
  TH1D* h1_Njet_Pow_WevtPow2Gen_NoCut;


  double NjetX[NjetBin],NjetX_err[NjetBin], ttMjj_Phn, ttMjj_Pow, ttDetajj_Phn, ttDetajj_Pow;
  for(int i(0);i<NjetBin;i++)
  {
    NjetX[i]=NjetBin/NjetBin*i + 1./2;
    NjetX_err[i]=1./2;
  }
  double Njet_Phn_Wevt[NjetBin], Njet_Phn[NjetBin],Njet_Phn_Wevt_Err[NjetBin], Njet_Pow_WevtPow2Gen[NjetBin], Njet_Pow[NjetBin], Njet_Pow_WevtPow2Gen_Err[NjetBin];
  double Njet_Phn_Wevt_NoCut[NjetBin], Njet_Phn_NoCut[NjetBin],Njet_Phn_Wevt_Err_NoCut[NjetBin], Njet_Pow_WevtPow2Gen_NoCut[NjetBin], Njet_Pow_NoCut[NjetBin], Njet_Pow_WevtPow2Gen_Err_NoCut[NjetBin];

  sprintf(tmpName, "h1_Njet_Wevt");
  sprintf(histName,"h1_Njet_Phn1_Wevt");
  h1_Njet_Phn_1_Wevt = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_1_Wevt->Sumw2();
  double bin1 = h1_Njet_Phn_1_Wevt->GetBinContent(1);
  sprintf(histName,"h1_Njet_Phn9_Wevt");
  h1_Njet_Phn_9_Wevt = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_9_Wevt->Sumw2();
  bin1 += h1_Njet_Phn_9_Wevt->GetBinContent(1);
  sprintf(histName,"h1_Njet_Phn25_Wevt");
  h1_Njet_Phn_25_Wevt = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_25_Wevt->Sumw2();
  bin1 += h1_Njet_Phn_25_Wevt->GetBinContent(1);
  cout<<"bin1: "<<bin1<<endl;
  sprintf(histName,"h1_Njet_Phn_Sg_Wevt");
  h1_Njet_Phn_Sg_Wevt=(TH1D*)h1_Njet_Phn_1_Wevt->Clone(histName);
  h1_Njet_Phn_Sg_Wevt->Add(h1_Njet_Phn_9_Wevt);
  h1_Njet_Phn_Sg_Wevt->Add(h1_Njet_Phn_25_Wevt);
  //h1_Njet_Phn_Sg_Wevt->Draw("hist");

  sprintf(tmpName, "h1_Njet_Wevt_NoCut");
  sprintf(histName,"h1_Njet_Phn1_Wevt_NoCut");
  h1_Njet_Phn_1_Wevt_NoCut = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_1_Wevt_NoCut->Sumw2();
  sprintf(histName,"h1_Njet_Phn9_Wevt_NoCut");
  h1_Njet_Phn_9_Wevt_NoCut = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_9_Wevt_NoCut->Sumw2();
  sprintf(histName,"h1_Njet_Phn25_Wevt_NoCut");
  h1_Njet_Phn_25_Wevt_NoCut = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_25_Wevt_NoCut->Sumw2();
  sprintf(histName,"h1_Njet_Phn_Sg_Wevt_NoCut");
  h1_Njet_Phn_Sg_Wevt_NoCut=(TH1D*)h1_Njet_Phn_1_Wevt_NoCut->Clone(histName);
  h1_Njet_Phn_Sg_Wevt_NoCut->Add(h1_Njet_Phn_9_Wevt_NoCut);
  h1_Njet_Phn_Sg_Wevt_NoCut->Add(h1_Njet_Phn_25_Wevt_NoCut);
  //h1_Njet_Phn_Sg_Wevt_NoCut->Draw();


  sprintf(tmpName, "h1_Njet_WevtPow2Gen");
  sprintf(histName,"h1_Njet_Pow_WevtPow2Gen");
  h1_Njet_Pow_WevtPow2Gen=(TH1D*)f_pow->Get(tmpName)->Clone(histName);
  sprintf(tmpName, "h1_Njet_WevtPow2Gen_NoCut");
  sprintf(histName,"h1_Njet_Pow_WevtPow2Gen_NoCut");
  h1_Njet_Pow_WevtPow2Gen_NoCut=(TH1D*)f_pow->Get(tmpName)->Clone(histName);

  sprintf(tmpName, "h1_Njet_NoW");
  sprintf(histName,"h1_Njet_Phn1_NoW");
  h1_Njet_Phn_1_NoW = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_1_NoW->Sumw2();
  sprintf(histName,"h1_Njet_Phn9_NoW");
  h1_Njet_Phn_9_NoW = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_9_NoW->Sumw2();
  sprintf(histName,"h1_Njet_Phn25_NoW");
  h1_Njet_Phn_25_NoW = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_25_NoW->Sumw2();
  sprintf(histName,"h1_Njet_Phn_Sg_NoW");
  h1_Njet_Phn_Sg_NoW=(TH1D*)h1_Njet_Phn_1_NoW->Clone(histName);
  h1_Njet_Phn_Sg_NoW->Scale(0.125);
  h1_Njet_Phn_Sg_NoW->Add(h1_Njet_Phn_9_NoW, -0.250);
  h1_Njet_Phn_Sg_NoW->Add(h1_Njet_Phn_25_NoW, 0.125);

  //h1_Njet_Phn_Sg_NoW->Draw();
  sprintf(histName,"h1_Njet_Pow_NoW");
  h1_Njet_Pow_NoW=(TH1D*)f_pow->Get(tmpName)->Clone(histName);

  sprintf(tmpName, "h1_Njet_NoW_NoCut");
  sprintf(histName,"h1_Njet_Phn1_NoW_NoCut");
  h1_Njet_Phn_1_NoW_NoCut = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_1_NoW_NoCut->Sumw2();
  sprintf(histName,"h1_Njet_Phn9_NoW_NoCut");
  h1_Njet_Phn_9_NoW_NoCut = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_9_NoW_NoCut->Sumw2();
  sprintf(histName,"h1_Njet_Phn25_NoW_NoCut");
  h1_Njet_Phn_25_NoW_NoCut = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
  h1_Njet_Phn_25_NoW_NoCut->Sumw2();
  sprintf(histName,"h1_Njet_Phn_Sg_NoW_NoCut");
  h1_Njet_Phn_Sg_NoW_NoCut=(TH1D*)h1_Njet_Phn_1_NoW_NoCut->Clone(histName);
  h1_Njet_Phn_Sg_NoW_NoCut->Scale(0.125);
  h1_Njet_Phn_Sg_NoW_NoCut->Add(h1_Njet_Phn_9_NoW_NoCut, -0.250);
  h1_Njet_Phn_Sg_NoW_NoCut->Add(h1_Njet_Phn_25_NoW_NoCut, 0.125);

  //h1_Njet_Phn_Sg_NoW_NoCut->Draw();
  //
  sprintf(histName,"h1_Njet_Pow_NoW_NoCut");
  h1_Njet_Pow_NoW_NoCut=(TH1D*)f_pow->Get(tmpName)->Clone(histName);
  for(int i(0); i<NjetBin;i++)
  {
    cout<<"hahah: "<<i<<endl;
    cout<<"phn1_NoW: "<<h1_Njet_Phn_1_NoW->GetBinContent(i+1)<<endl;
    cout<<"phn9_NoW: "<<h1_Njet_Phn_9_NoW->GetBinContent(i+1)<<endl;
    cout<<"phn25_NoW: "<<h1_Njet_Phn_25_NoW->GetBinContent(i+1)<<endl;
  }

  //Error calculation

  double tmpK;
  ttMjj_Phn=0;
  ttMjj_Pow=0;
  for(int bdx(1);bdx <=NjetBin;bdx++)
  {
    Njet_Phn_Wevt[bdx-1] = h1_Njet_Phn_Sg_Wevt->GetBinContent(bdx);
    ttMjj_Phn+= Njet_Phn_Wevt[bdx-1];
    Njet_Phn[bdx-1]      = h1_Njet_Phn_Sg_NoW->GetBinContent(bdx);
    tmpK  = Njet_Phn_Wevt[bdx-1]/Njet_Phn[bdx-1];
    Njet_Phn_Wevt_Err[bdx-1]= tmpK* TMath::Sqrt(Njet_Phn[bdx-1]);

    Njet_Pow_WevtPow2Gen[bdx-1] = h1_Njet_Pow_WevtPow2Gen->GetBinContent(bdx);
    ttMjj_Pow += Njet_Pow_WevtPow2Gen[bdx-1];
    Njet_Pow[bdx-1]             = h1_Njet_Pow_NoW->GetBinContent(bdx);
    tmpK   = Njet_Pow_WevtPow2Gen[bdx-1]/Njet_Pow[bdx-1];

    Njet_Pow_WevtPow2Gen_Err[bdx-1]=tmpK*TMath::Sqrt(Njet_Pow[bdx-1]);
    //cout<<"bin: "<<bdx<<"Phn Evet: "<<Njet_Phn[bdx-1]<<" Pow: Evt: "<<Njet_Pow[bdx-1]<<endl;
  }
  // Normalization
  for(int j(0);j<NjetBin;j++)
  {
    Njet_Phn_Wevt[j] /= ttMjj_Phn;
    Njet_Phn_Wevt_Err[j] /= ttMjj_Phn;
    Njet_Pow_WevtPow2Gen[j] /= ttMjj_Pow;
    Njet_Pow_WevtPow2Gen_Err[j] /= ttMjj_Pow;
    cout<<"after norm phn wevt cut: "<<Njet_Phn_Wevt[j]<<endl;
  }
  ttMjj_Phn=0;
  ttMjj_Pow=0;
  //h1_Njet_Phn_Sg_Wevt_NoCut->Draw();
  for(int bdx(1);bdx <=NjetBin;bdx++)
  {
    Njet_Phn_Wevt_NoCut[bdx-1] = h1_Njet_Phn_Sg_Wevt_NoCut->GetBinContent(bdx);
    ttMjj_Phn+= Njet_Phn_Wevt_NoCut[bdx-1];
    Njet_Phn_NoCut[bdx-1]      = h1_Njet_Phn_Sg_NoW_NoCut->GetBinContent(bdx);
    tmpK  = Njet_Phn_Wevt_NoCut[bdx-1]/Njet_Phn_NoCut[bdx-1];
    cout<<"Njet_Phn_NoCut:"<<Njet_Phn_NoCut[bdx-1]<<endl;
    Njet_Phn_Wevt_Err_NoCut[bdx-1]= tmpK* TMath::Sqrt(Njet_Phn_NoCut[bdx-1]);

    Njet_Pow_WevtPow2Gen_NoCut[bdx-1] = h1_Njet_Pow_WevtPow2Gen_NoCut->GetBinContent(bdx);
    ttMjj_Pow += Njet_Pow_WevtPow2Gen_NoCut[bdx-1];
    Njet_Pow_NoCut[bdx-1]             = h1_Njet_Pow_NoW_NoCut->GetBinContent(bdx);
    tmpK   = Njet_Pow_WevtPow2Gen_NoCut[bdx-1]/Njet_Pow_NoCut[bdx-1];

    Njet_Pow_WevtPow2Gen_Err_NoCut[bdx-1]=tmpK*TMath::Sqrt(Njet_Pow_NoCut[bdx-1]);
    //cout<<"bin: "<<bdx<<"Phn Evet: "<<Njet_Phn[bdx-1]<<" Pow: Evt: "<<Njet_Pow[bdx-1]<<endl;
  }
  // Normalization
  for(int j(0);j<NjetBin;j++)
  {
    cout<<"before norm phn wevt Nocut: "<<Njet_Phn_Wevt_NoCut[j]<<endl;
    Njet_Phn_Wevt_NoCut[j] /= ttMjj_Phn;
    cout<<"after norm phn wevt Nocut: "<<Njet_Phn_Wevt_NoCut[j]<<endl;
    Njet_Phn_Wevt_Err_NoCut[j] /= ttMjj_Phn;
    Njet_Pow_WevtPow2Gen_NoCut[j] /= ttMjj_Pow;
    Njet_Pow_WevtPow2Gen_Err_NoCut[j] /= ttMjj_Pow;
  }
  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  TH1F *hr = myCan->DrawFrame(0.,0,NjetBin,1.0); //make TGraph can do "same"
  hr->SetXTitle("Njet");
  hr->SetYTitle("Normalized");

  TGraphErrors *gr_powErr = new TGraphErrors(NjetBin, NjetX, Njet_Pow_WevtPow2Gen, NjetX_err, Njet_Pow_WevtPow2Gen_Err);
  TGraphErrors *gr_phnErr = new TGraphErrors(NjetBin, NjetX, Njet_Phn_Wevt       , NjetX_err, Njet_Phn_Wevt_Err);
  TGraphErrors *gr_powErr_NoCut = new TGraphErrors(NjetBin, NjetX, Njet_Pow_WevtPow2Gen_NoCut, NjetX_err, Njet_Pow_WevtPow2Gen_Err_NoCut);
  TGraphErrors *gr_phnErr_NoCut = new TGraphErrors(NjetBin, NjetX, Njet_Phn_Wevt_NoCut       , NjetX_err, Njet_Phn_Wevt_Err_NoCut);
  ofstream Fout;
  TString FoutName = OutDir+"/"+"NjetBin4.txt";
  Fout.open(FoutName);
  Fout<<"Before Cut ================================"<<endl;
  Fout<<"<<<<< Phantom >>>>>"<<endl;
  for(int i(0);i<NjetBin;i++)
  {
    cout<<i<<" jet: "<<Njet_Phn_Wevt_NoCut[i]<<"+"<<Njet_Phn_Wevt_Err_NoCut[i]<<endl;
    Fout<<i<<" jet: "<<Njet_Phn_Wevt_NoCut[i]<<"+"<<Njet_Phn_Wevt_Err_NoCut[i]<<endl;
  }
  Fout<<"<<<<< Powheg_VBF >>>>>"<<endl;
  for(int i(0);i<NjetBin;i++)
  {
    cout<<i<<" jet: "<<Njet_Pow_WevtPow2Gen_NoCut[i]<<"+"<<Njet_Pow_WevtPow2Gen_Err_NoCut[i]<<endl;
    Fout<<i<<" jet: "<<Njet_Pow_WevtPow2Gen_NoCut[i]<<"+"<<Njet_Pow_WevtPow2Gen_Err_NoCut[i]<<endl;
  }
  Fout<<"After Cut ================================"<<endl;
  Fout<<"<<<<< Phantom >>>>>"<<endl;
  for(int i(0);i<NjetBin;i++)
  {
    cout<<i<<" jet: "<<Njet_Phn_Wevt[i]<<"+"<<Njet_Phn_Wevt_Err[i]<<endl;
    Fout<<i<<" jet: "<<Njet_Phn_Wevt[i]<<"+"<<Njet_Phn_Wevt_Err[i]<<endl;
  }
  Fout<<"<<<<< Powheg_VBF >>>>>"<<endl;
  for(int i(0);i<NjetBin;i++)
  {
    cout<<i<<" jet: "<<Njet_Pow_WevtPow2Gen[i]<<"+"<<Njet_Pow_WevtPow2Gen_Err[i]<<endl;
    Fout<<i<<" jet: "<<Njet_Pow_WevtPow2Gen[i]<<"+"<<Njet_Pow_WevtPow2Gen_Err[i]<<endl;
  }
  Fout<<"<<<<< (Phntom -Powheg_VBF)/PowHeg >>>>>"<<endl;
  for(int i(0);i<NjetBin;i++)
  {
    cout<<i<<" jet: "<<(Njet_Phn_Wevt[i]-Njet_Pow_WevtPow2Gen[i])/Njet_Pow_WevtPow2Gen[i]<<endl;
    Fout<<i<<" jet: "<<(Njet_Phn_Wevt[i]-Njet_Pow_WevtPow2Gen[i])/Njet_Pow_WevtPow2Gen[i]<<endl;
  }

  Fout.close();

  TColor *colBlue = gROOT->GetColor(kBlue);
  TColor *colRed = gROOT->GetColor(kRed);
  colBlue->SetAlpha(0.5);
  colRed->SetAlpha(0.5);
  TColor *colGreen = gROOT->GetColor(kGreen);
  TColor *colPink = gROOT->GetColor(kPink);
  colGreen->SetAlpha(0.5);
  colPink->SetAlpha(0.5);


  gr_powErr->SetFillColor(kBlue);
  gr_powErr->SetLineColor(kBlue);
  gr_phnErr->SetFillColor(kRed);
  gr_phnErr->SetLineColor(kRed);
  
  gr_powErr->Draw("5"); //5
  gr_phnErr->Draw("5");
  //
  TLegend *myLeg = new TLegend(0.25,0.64,0.45,0.75);
  myLeg->AddEntry(gr_powErr,"PowhegVBfCut","f");
  myLeg->AddEntry(gr_phnErr,"PhntomVBfCut","f");
  myLeg->Draw();
  sprintf(tmpName, "/NjetVBF4Bins.pdf");
  myCan->SaveAs(OutDir+tmpName);
  myCan->Clear();

  TH1F *hr2 = myCan->DrawFrame(0.,0,NjetBin,1.0); //make TGraph can do "same"
  hr2->SetXTitle("Njet");
  hr2->SetYTitle("Normalized");
  gr_powErr_NoCut->SetFillColor(kGreen);
  gr_powErr_NoCut->SetLineColor(kGreen);
  gr_phnErr_NoCut->SetFillColor(kMagenta);
  gr_phnErr_NoCut->SetLineColor(kMagenta);
  
  gr_powErr_NoCut->Draw("5"); //5
  gr_phnErr_NoCut->Draw("5");
  //
  TLegend *myLeg2 = new TLegend(0.25,0.64,0.45,0.75);
  myLeg2->AddEntry(gr_powErr_NoCut,"PowhegNoCut","f");
  myLeg2->AddEntry(gr_phnErr_NoCut,"PhntomNoCut","f");
  myLeg2->Draw();
  sprintf(tmpName, "/NjetVBF4BinsNoCut.pdf");
  myCan->SaveAs(OutDir+tmpName);
  return 0;
}
