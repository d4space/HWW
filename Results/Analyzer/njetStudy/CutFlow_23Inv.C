// Run as root -l CutFlow_23Inv.C

#include "TStyle.h"
#include "../../../Utils/const.h"
#include "../../../Utils/CPlot.hh"
#include "../../../Utils/MitStyleRemix.hh"
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

#include "RooRealVar.h"
#include "RooPoisson.h"
#include "RooPolynomial.h"
#include "RooLandau.h"
#include "RooPlot.h"
#include "RooBinning.h"
#include "RooExponential.h"
#include "RooBreitWigner.h"
#include "RooCBShape.h"
#include "RooDataHist.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooNLLVar.h"
#include "RooMinuit.h"
#include "RooChi2Var.h"
#include "RooGenericPdf.h"
#include "RooFFTConvPdf.h"

#include "../AnaSrc/NjetBin.h"

int CutFlow_23Inv()
{
  TString OutDir = "CutFlow23Inv";
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

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  TH1F *hr = myCan->DrawFrame(0.,0,2,1);
  
  hr->SetXTitle("Njet 2||3 w/o centJet     Njet#geq2 w/ centJet");
  hr->SetYTitle("Efficiency");
  //++++++++++++++++++++++++++++
  //Histograms
  //++++++++++++++++++++++++++++
  // Phantom---------------
  TH1D* h1_mWW_Phn_1_Wevt[NjetBin+1];
  TH1D* h1_mWW_Phn_9_Wevt[NjetBin+1];
  TH1D* h1_mWW_Phn_25_Wevt[NjetBin+1];
  TH1D* h1_mWW_Phn_Sg_Wevt[NjetBin+1];
  TH1D* h1_mWW_Phn_1_Wevt_NoCut[NjetBin+1];
  TH1D* h1_mWW_Phn_9_Wevt_NoCut[NjetBin+1];
  TH1D* h1_mWW_Phn_25_Wevt_NoCut[NjetBin+1];
  TH1D* h1_mWW_Phn_Sg_Wevt_NoCut[NjetBin+1];

  TH1D* h1_23vsInv_Phn_1_Wevt;
  TH1D* h1_23vsInv_Phn_9_Wevt;
  TH1D* h1_23vsInv_Phn_25_Wevt;
  TH1D* h1_23vsInv_Phn_Sg_Wevt;
  TH1D* h1_23vsInv_Phn_1;
  TH1D* h1_23vsInv_Phn_9;
  TH1D* h1_23vsInv_Phn_25;
  TH1D* h1_23vsInv_Phn_Sg;
  TH1D* h1_23vsInv_Phn_Sg_Err;
  // Powheg------------------------
  TH1D* h1_mWW_Pow_Wevt[NjetBin+1];
  TH1D* h1_mWW_Pow_Wevt_NoCut[NjetBin+1];
  TH1D* h1_mWW_Pow_WevtPow2Gen[NjetBin+1];
  TH1D* h1_mWW_Pow_WevtPow2Gen_NoCut[NjetBin+1];

  TH1D* h1_23vsInv_Pow;
  TH1D* h1_23vsInv_Pow_Err;
  TH1D* h1_23vsInv_Pow_Wevt;
  TH1D* h1_23vsInv_Pow_WevtPow2Gen;


  sprintf(tmpName, "h1_23vsInv_Wevt");
  sprintf(histName,"h1_23vsInv_Phn1_Wevt");
  h1_23vsInv_Phn_1_Wevt = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
  h1_23vsInv_Phn_1_Wevt->Sumw2();
  sprintf(histName,"h1_23vsInv_Phn9_Wevt");
  h1_23vsInv_Phn_9_Wevt = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
  h1_23vsInv_Phn_9_Wevt->Sumw2();
  sprintf(histName,"h1_23vsInv_Phn25_Wevt");
  h1_23vsInv_Phn_25_Wevt = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
  h1_23vsInv_Phn_25_Wevt->Sumw2();
  h1_23vsInv_Phn_Sg_Wevt=(TH1D*)h1_23vsInv_Phn_1_Wevt->Clone("h1_23vsInv_Phn_Sg_Wevt");
  h1_23vsInv_Phn_Sg_Wevt->Add(h1_23vsInv_Phn_9_Wevt);
  h1_23vsInv_Phn_Sg_Wevt->Add(h1_23vsInv_Phn_25_Wevt);
  sprintf(histName,"h1_23vsInv_Pow_WevtPow2Gen");
  h1_23vsInv_Pow_WevtPow2Gen=(TH1D*)f_pow->Get(tmpName)->Clone(histName);

  sprintf(tmpName, "h1_23vsInv");
  sprintf(histName,"h1_23vsInv_Phn1");
  h1_23vsInv_Phn_1 = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
  h1_23vsInv_Phn_1->Sumw2();
  sprintf(histName,"h1_23vsInv_Phn9");
  h1_23vsInv_Phn_9 = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
  h1_23vsInv_Phn_9->Sumw2();
  sprintf(histName,"h1_23vsInv_Phn25");
  h1_23vsInv_Phn_25 = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
  h1_23vsInv_Phn_25->Sumw2();
  h1_23vsInv_Phn_Sg=(TH1D*)h1_23vsInv_Phn_1->Clone("h1_23vsInv_Phn_Sg");
  h1_23vsInv_Phn_Sg->Scale(0.125);
  h1_23vsInv_Phn_Sg->Add(h1_23vsInv_Phn_9, -0.250);
  h1_23vsInv_Phn_Sg->Add(h1_23vsInv_Phn_25, 0.125);
  sprintf(histName,"h1_23vsInv_Pow");
  h1_23vsInv_Pow=(TH1D*)f_pow->Get(tmpName)->Clone(histName);

  //Error calculation
  h1_23vsInv_Pow_Err=(TH1D*)h1_23vsInv_Pow_WevtPow2Gen->Clone("h1_23vsInv_Pow_Err");
  h1_23vsInv_Phn_Sg_Err=(TH1D*)h1_23vsInv_Phn_Sg->Clone("h1_23vsInv_Phn_Sg_Err");

  double X_Phn_Wevt[2], X_Phn[2], X_Pow_WevtPow2Gen[2], X_Pow[2], tmpK;
  for(int bdx(1);bdx <=2;bdx++)
  {
    X_Phn_Wevt[bdx-1] = h1_23vsInv_Phn_Sg_Wevt->GetBinContent(bdx);
    X_Phn[bdx-1]      = h1_23vsInv_Phn_Sg->GetBinContent(bdx);
    tmpK  = X_Phn_Wevt[bdx-1]/X_Phn[bdx-1];
    h1_23vsInv_Phn_Sg_Err->SetBinContent(bdx, X_Phn_Wevt[bdx-1]);
    h1_23vsInv_Phn_Sg_Err->SetBinError(bdx, tmpK* TMath::Sqrt(X_Phn[bdx-1]));

    X_Pow_WevtPow2Gen[bdx-1] = h1_23vsInv_Pow_WevtPow2Gen->GetBinContent(bdx);
    X_Pow[bdx-1]             = h1_23vsInv_Pow->GetBinContent(bdx);
    tmpK   = X_Pow_WevtPow2Gen[bdx-1]/X_Pow[bdx-1];

    h1_23vsInv_Pow_Err->SetBinContent(bdx,X_Pow_WevtPow2Gen[bdx-1]);
    h1_23vsInv_Pow_Err->SetBinError(bdx,tmpK*TMath::Sqrt(X_Pow[bdx-1]));
  }



  // bin2 - bin1
  double powBin1     = h1_23vsInv_Pow_Err->GetBinContent(1);
  double powBin1_Err = h1_23vsInv_Pow_Err->GetBinError(1);
  double powBin2     = h1_23vsInv_Pow_Err->GetBinContent(2);
  double powBin2_Err = h1_23vsInv_Pow_Err->GetBinError(2);
  double phnBin1     = h1_23vsInv_Phn_Sg_Err->GetBinContent(1);
  double phnBin1_Err = h1_23vsInv_Phn_Sg_Err->GetBinError(1);
  double phnBin2     = h1_23vsInv_Phn_Sg_Err->GetBinContent(2);
  double phnBin2_Err = h1_23vsInv_Phn_Sg_Err->GetBinError(2);
  h1_23vsInv_Pow_Err->SetBinContent(2,powBin2-powBin1);
  tmpK = (X_Pow_WevtPow2Gen[1]-X_Pow_WevtPow2Gen[0])/(X_Pow[1]-X_Pow[0]);
  h1_23vsInv_Pow_Err->SetBinError(2,tmpK*TMath::Sqrt(X_Pow[1]-X_Pow[0]));
  h1_23vsInv_Phn_Sg_Err    ->SetBinContent(2,phnBin2-phnBin1);
  tmpK = (X_Phn_Wevt[1]-X_Phn_Wevt[0])/(X_Phn[1]-X_Phn[0]);
  h1_23vsInv_Phn_Sg_Err    ->SetBinError(2,tmpK* TMath::Sqrt(X_Phn[1]-X_Phn[0]));

  // Normalize
  double integralX;
  integralX=h1_23vsInv_Phn_Sg_Err->Integral();
  h1_23vsInv_Phn_Sg_Err->Scale(1./integralX);
  h1_23vsInv_Phn_Sg_Err->SetMinimum(0);
  integralX=h1_23vsInv_Pow_Err->Integral();
  h1_23vsInv_Pow_Err->Scale(1./integralX);
  h1_23vsInv_Pow_Err->SetMinimum(0);

  double x[2] ={0.5, 1.5};
  double x_E[2] = {0.5, 0.5};
  double pow_y[2], pow_ye[2];
  double phn_y[2], phn_ye[2];
  for(int k(0);k<2;k++)
  {
    phn_y[k]  = h1_23vsInv_Phn_Sg_Err->GetBinContent(k+1);
    phn_ye[k] = h1_23vsInv_Phn_Sg_Err->GetBinError(k+1);
    pow_y[k]  = h1_23vsInv_Pow_Err->GetBinContent(k+1);
    pow_ye[k] = h1_23vsInv_Pow_Err->GetBinError(k+1);
  }
  TGraphErrors *gr_powErr = new TGraphErrors(2, x, pow_y, x_E, pow_ye);
  TGraphErrors *gr_phnErr = new TGraphErrors(2, x, phn_y, x_E, phn_ye);

  TColor *colBlue = gROOT->GetColor(kBlue);
  TColor *colRed = gROOT->GetColor(kRed);
  colBlue->SetAlpha(0.5);
  colRed->SetAlpha(0.5);


  gr_powErr->SetFillColor(kBlue);
  gr_powErr->SetLineColor(kBlue);
  gr_phnErr->SetFillColor(kRed);
  gr_phnErr->SetLineColor(kRed);
  gr_powErr->Draw("5"); //5
  gr_phnErr->Draw("5");
  TLegend *myLeg = new TLegend(0.65,0.64,0.85,0.75);
  myLeg->AddEntry(gr_powErr,"Powheg","f");
  myLeg->AddEntry(gr_phnErr,"Phntom","f");
  myLeg->Draw();
  myCan->SaveAs(OutDir+"/hahaha.pdf");

  return 0;
}
