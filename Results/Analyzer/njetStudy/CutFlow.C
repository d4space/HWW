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

int CutFlow()
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
  // Powheg------------------------
  TH1D* h1_mWW_Pow_Wevt[NjetBin+1];
  TH1D* h1_mWW_Pow_Wevt_NoCut[NjetBin+1];
  TH1D* h1_mWW_Pow_WevtPow2Gen[NjetBin+1];
  TH1D* h1_mWW_Pow_WevtPow2Gen_NoCut[NjetBin+1];

  TH1D* h1_23vsInv_Pow_Wevt;
  TH1D* h1_23vsInv_Pow_WevtPow2Gen;



  sprintf(tmpName, "h1_23vs34_Wevt");
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

  double integralX;
  integralX=h1_23vsInv_Phn_Sg_Wevt->Integral();
  h1_23vsInv_Phn_Sg_Wevt->Scale(1./integralX);
  h1_23vsInv_Phn_Sg_Wevt->SetMinimum(0);
  integralX=h1_23vsInv_Pow_WevtPow2Gen->Integral();
  h1_23vsInv_Pow_WevtPow2Gen->Scale(1./integralX);
  h1_23vsInv_Pow_WevtPow2Gen->SetMinimum(0);

  double powBin1 = h1_23vsInv_Pow_WevtPow2Gen->GetBinContent(1);
  double powBin2 = h1_23vsInv_Pow_WevtPow2Gen->GetBinContent(2);
  double phnBin1 = h1_23vsInv_Phn_Sg_Wevt->GetBinContent(1);
  double phnBin2 = h1_23vsInv_Phn_Sg_Wevt->GetBinContent(2);

  char texBoxContentPow[50];
  sprintf(texBoxContentPow,"Pow: %5.4f,  %5.4f",powBin1, powBin2);
  char texBoxContentPhn[50];
  sprintf(texBoxContentPhn,"Phn: %5.4f,  %5.4f",phnBin1, phnBin2);

  sprintf(histName,"Njet=23vsInverse");
  //sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
  CPlot* plt_23vsInv=new CPlot(histName,"","njet23/GtEq2!centVeto","");
  plt_23vsInv->setOutDir(OutDir);
  plt_23vsInv->AddHist1D(h1_23vsInv_Pow_WevtPow2Gen,"HIST",kBlue);
  plt_23vsInv->AddHist1D(h1_23vsInv_Phn_Sg_Wevt,"HIST",kRed);
  plt_23vsInv->SetLegend(0.63,0.26,0.88,0.42);
  plt_23vsInv->GetLegend()->AddEntry(h1_23vsInv_Pow_WevtPow2Gen,"POWHEG","l");
  plt_23vsInv->GetLegend()->AddEntry(h1_23vsInv_Phn_Sg_Wevt,"Phantom","l");
  plt_23vsInv->AddTextBox(texBoxContentPow,0.2,0.52,0.42,0.65,0);
  plt_23vsInv->AddTextBox(texBoxContentPhn,0.5,0.52,0.82,0.65,0);
  plt_23vsInv->Draw(myCan,kTRUE,"png");
  
  for(int i(0);i<NjetBin+1;i++)
  {
    // Take Weighted
    sprintf(tmpName, "h1_mWW_Off_Wevt_%d",i);
    sprintf(histName,"h1_mWW_Phn_1_Wevt_%d",i);
    h1_mWW_Phn_1_Wevt[i] = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_1_Wevt[i]->Sumw2();
    sprintf(histName,"h1_mWW_Phn_9_Wevt_%d",i);
    h1_mWW_Phn_9_Wevt[i] = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_9_Wevt[i]->Sumw2();
    sprintf(histName,"h1_mWW_Phn_25_Wevt_%d",i);
    h1_mWW_Phn_25_Wevt[i] = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_25_Wevt[i]->Sumw2();
    h1_mWW_Pow_Wevt[i] = (TH1D*)f_pow->Get(tmpName)->Clone(histName);
    h1_mWW_Pow_Wevt[i]->Sumw2();

    sprintf(tmpName, "h1_mWW_Off_Wevt_NoCut_%d",i);
    sprintf(histName,"h1_mWW_Phn_1_Wevt_NoCut_%d",i);
    h1_mWW_Phn_1_Wevt_NoCut[i] = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_1_Wevt_NoCut[i]->Sumw2();
    sprintf(histName,"h1_mWW_Phn_9_Wevt_NoCut_%d",i);
    h1_mWW_Phn_9_Wevt_NoCut[i] = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_9_Wevt_NoCut[i]->Sumw2();
    sprintf(histName,"h1_mWW_Phn_25_Wevt_NoCut_%d",i);
    h1_mWW_Phn_25_Wevt_NoCut[i] = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_25_Wevt_NoCut[i]->Sumw2();
    sprintf(histName,"h1_mWW_Pow_Wevt_NoCut_%d",i);
    h1_mWW_Pow_Wevt_NoCut[i] = (TH1D*)f_pow->Get(tmpName)->Clone(histName);
    h1_mWW_Pow_Wevt_NoCut[i]->Sumw2();

    sprintf(tmpName, "h1_mWW_Off_WevtPow2Gen_%d",i);
    sprintf(histName,"h1_mWW_Pow_WevtPow2Gen_%d",i);
    h1_mWW_Pow_WevtPow2Gen[i] = (TH1D*)f_pow->Get(tmpName)->Clone(histName);
    h1_mWW_Pow_WevtPow2Gen[i]->Sumw2();
    sprintf(tmpName, "h1_mWW_Off_WevtPow2Gen_NoCut_%d",i);
    sprintf(histName,"h1_mWW_Pow_WevtPow2Gen_NoCut_%d",i);
    h1_mWW_Pow_WevtPow2Gen_NoCut[i] = (TH1D*)f_pow->Get(tmpName)->Clone(histName);
    h1_mWW_Pow_WevtPow2Gen_NoCut[i]->Sumw2();



    // Phantom Signal Extraction without Event Weight histogram

    sprintf(histName,"h1_mWW_Phn_Sg_Wevt_%d",i);
    h1_mWW_Phn_Sg_Wevt[i] = (TH1D*)h1_mWW_Phn_1_Wevt[i]->Clone(histName);
    h1_mWW_Phn_Sg_Wevt[i]->Add(h1_mWW_Phn_9_Wevt[i]);
    h1_mWW_Phn_Sg_Wevt[i]->Add(h1_mWW_Phn_25_Wevt[i]);
    sprintf(histName,"h1_mWW_Phn_Sg_Wevt_NoCut_%d",i);
    h1_mWW_Phn_Sg_Wevt_NoCut[i] = (TH1D*)h1_mWW_Phn_1_Wevt_NoCut[i]->Clone(histName);
    h1_mWW_Phn_Sg_Wevt_NoCut[i]->Add(h1_mWW_Phn_9_Wevt_NoCut[i]);
    h1_mWW_Phn_Sg_Wevt_NoCut[i]->Add(h1_mWW_Phn_25_Wevt_NoCut[i]);

    // Calculation of factor which make the non-Weighted phantom signal to event weighted one for value and error both
  }
  TH1D* h1_CutFlow_Pow_WevtPow2Gen[NjetBin+1];
  TH1D* h1_CutFlow_Phn_Wevt[NjetBin+1];
  double Pow_WevtPow2Gen_pass;
  double Pow_WevtPow2Gen_all;
  double Phn_Wevt_pass;
  double Phn_Wevt_all;

  TH1D* h1_mWW_Pow_Wevt_CutOvNoCut[NjetBin+1];
  TH1D* h1_mWW_Phn_Wevt_CutOvNoCut[NjetBin+1];
  for(int i(0);i<NjetBin+1;i++)
  {
 
    sprintf(jetName,"(njet = %d)",i);
    //if(i==NjetBin-1)
    //  sprintf(jetName,"(njet #geq %d)",i);
    if(i==NjetBin)
      sprintf(jetName,"(Inclusive jet bins)");

    //=================================
    // Cut Flow
    //=================================
    sprintf(histName,"h1_CutFlow_Pow_WevtPow2Gen_%d",i);
    h1_CutFlow_Pow_WevtPow2Gen[i]= new TH1D(histName,"CutFlow",2,0,2);
    Pow_WevtPow2Gen_pass = h1_mWW_Pow_WevtPow2Gen[i]->Integral();
    Pow_WevtPow2Gen_all  = h1_mWW_Pow_WevtPow2Gen_NoCut[i]->Integral();
    h1_CutFlow_Pow_WevtPow2Gen[i]->SetBinContent(1, Pow_WevtPow2Gen_all);
    h1_CutFlow_Pow_WevtPow2Gen[i]->SetBinContent(2, Pow_WevtPow2Gen_pass);
    h1_CutFlow_Pow_WevtPow2Gen[i]->SetMinimum(0);

    sprintf(histName,"CutFlow_Pow_%d",i);
    //sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
    CPlot* plt_Cutfl_Pow=new CPlot(histName,"","All/Pass","");
    plt_Cutfl_Pow->setOutDir(OutDir);
    plt_Cutfl_Pow->AddHist1D(h1_CutFlow_Pow_WevtPow2Gen[i],"HIST",kBlue);
    //plt_Cutfl_Pow->SetLegend(0.63,0.76,0.88,0.92);
    //plt_Cutfl_Pow->GetLegend()->AddEntry(h1_mWW_Pow_Wevt_NoCut[i],"Nocut","l");
    //plt_Cutfl_Pow->GetLegend()->AddEntry(h1_mWW_Pow_Wevt[i],"VBFcut","l");
    plt_Cutfl_Pow->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plt_Cutfl_Pow->Draw(myCan,kTRUE,"png");
    // Phantom==================================
    sprintf(histName,"h1_CutFlow_Phn_Wevt_%d",i);
    h1_CutFlow_Phn_Wevt[i]= new TH1D(histName,"CutFlow",2,0,2);
    Phn_Wevt_pass = h1_mWW_Phn_Sg_Wevt[i]->Integral();
    Phn_Wevt_all  = h1_mWW_Phn_Sg_Wevt_NoCut[i]->Integral();
    h1_CutFlow_Phn_Wevt[i]->SetBinContent(1, Phn_Wevt_all);
    h1_CutFlow_Phn_Wevt[i]->SetBinContent(2, Phn_Wevt_pass);
    h1_CutFlow_Phn_Wevt[i]->SetMinimum(0);

    sprintf(histName,"CutFlow_Phn_%d",i);
    //sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
    CPlot* plt_Cutfl_Phn=new CPlot(histName,"","All/Pass","");
    plt_Cutfl_Phn->setOutDir(OutDir);
    plt_Cutfl_Phn->AddHist1D(h1_CutFlow_Phn_Wevt[i],"HIST",kBlue);
    //plt_Cutfl_Pow->SetLegend(0.63,0.76,0.88,0.92);
    //plt_Cutfl_Pow->GetLegend()->AddEntry(h1_mWW_Pow_Wevt_NoCut[i],"Nocut","l");
    //plt_Cutfl_Pow->GetLegend()->AddEntry(h1_mWW_Pow_Wevt[i],"VBFcut","l");
    plt_Cutfl_Phn->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plt_Cutfl_Phn->Draw(myCan,kTRUE,"png");
    //
    //
    //======================================

    sprintf(histName,"h1_mWW_Pow_Wevt_CutOvNoCut_%d",i);
    h1_mWW_Pow_Wevt_CutOvNoCut[i] = (TH1D*)h1_mWW_Pow_Wevt[i]->Clone(histName);
    h1_mWW_Pow_Wevt_CutOvNoCut[i]->Sumw2();
    h1_mWW_Pow_Wevt_CutOvNoCut[i]->Divide(h1_mWW_Pow_Wevt_NoCut[i]);

    double PowYieldNoCut = h1_mWW_Pow_Wevt_NoCut[i]->Integral();
    double PowYieldCut   = h1_mWW_Pow_Wevt[i]->Integral();
    cout<<"nocut: "<<PowYieldNoCut<<" cut:"<<PowYieldCut<<endl;
    sprintf(Yield,"Cut/NoCut = %f",PowYieldCut/PowYieldNoCut);

    // Plots
    //Powheg Phantom comparison after step 1
    sprintf(histName,"Powh_mWW_Cut_NoCut_%d",i);
    //sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
    CPlot* plt_Pow=new CPlot(histName,"","mWW","");
    plt_Pow->setOutDir(OutDir);
    plt_Pow->AddHist1D(h1_mWW_Pow_Wevt_NoCut[i],"HIST",kBlue);
    plt_Pow->AddHist1D(h1_mWW_Pow_Wevt[i],"HIST",kRed);
    plt_Pow->SetLegend(0.63,0.76,0.88,0.92);
    plt_Pow->GetLegend()->AddEntry(h1_mWW_Pow_Wevt_NoCut[i],"Nocut","l");
    plt_Pow->GetLegend()->AddEntry(h1_mWW_Pow_Wevt[i],"VBFcut","l");
    plt_Pow->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plt_Pow->Draw(myCan,kTRUE,"png");

    //Powheg Phantom comparison after step 1
    sprintf(histName,"Powh_mWW_CutOvNoCut_%d",i);
    //sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
    CPlot* plt_Pow_ratio=new CPlot(histName,"","mWW","");
    plt_Pow_ratio->setOutDir(OutDir);
    plt_Pow_ratio->AddHist1D(h1_mWW_Pow_Wevt_CutOvNoCut[i],"HIST",kBlue);
    plt_Pow_ratio->SetLegend(0.63,0.76,0.88,0.92);
    plt_Pow_ratio->GetLegend()->AddEntry(h1_mWW_Pow_Wevt_CutOvNoCut[i],"POWHEG_Cut/Nocut","l");
    plt_Pow_ratio->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plt_Pow_ratio->AddTextBox(Yield,0.1,0.7,0.5,0.8,0);
    plt_Pow_ratio->Draw(myCan,kTRUE,"png");

  }
  for(int i(0);i<NjetBin+1;i++)
  {
 
    sprintf(jetName,"(njet = %d)",i);
    //if(i==NjetBin-1)
    //  sprintf(jetName,"(njet #geq %d)",i);
    if(i==NjetBin)
      sprintf(jetName,"(Inclusive jet bins)");

    sprintf(histName,"h1_mWW_Phn_Wevt_CutOvNoCut_%d",i);
    h1_mWW_Phn_Wevt_CutOvNoCut[i] = (TH1D*)h1_mWW_Phn_Sg_Wevt[i]->Clone(histName);
    h1_mWW_Phn_Wevt_CutOvNoCut[i]->Sumw2();
    h1_mWW_Phn_Wevt_CutOvNoCut[i]->Divide(h1_mWW_Phn_Sg_Wevt_NoCut[i]);

    double PhnYieldNoCut = h1_mWW_Phn_Sg_Wevt_NoCut[i]->Integral();
    double PhnYieldCut   = h1_mWW_Phn_Sg_Wevt[i]->Integral();
    cout<<"nocut: "<<PhnYieldNoCut<<" cut:"<<PhnYieldCut<<endl;
    sprintf(Yield,"Cut/NoCut = %f",PhnYieldCut/PhnYieldNoCut);

    // Plots
    //Powheg Phantom comparison after step 1
    sprintf(histName,"Phn_mWW_CutOvNoCut_%d",i);
    //sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
    CPlot* plt_Phn_rate=new CPlot(histName,"","mWW","");
    plt_Phn_rate->setOutDir(OutDir);
    plt_Phn_rate->AddHist1D(h1_mWW_Phn_Wevt_CutOvNoCut[i],"HIST",kBlue);
    plt_Phn_rate->SetLegend(0.63,0.76,0.88,0.92);
    plt_Phn_rate->GetLegend()->AddEntry(h1_mWW_Phn_Wevt_CutOvNoCut[i],"Phn_Cut/Nocut","l");
    plt_Phn_rate->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plt_Phn_rate->AddTextBox(Yield,0.1,0.7,0.5,0.8,0);
    plt_Phn_rate->Draw(myCan,kTRUE,"png");

    sprintf(histName,"Phn_mWW_Cut_NoCut_%d",i);
    //sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
    CPlot* plt_Phn=new CPlot(histName,"","mWW","");
    plt_Phn->setOutDir(OutDir);
    plt_Phn->AddHist1D(h1_mWW_Phn_Sg_Wevt_NoCut[i],"HIST",kBlue);
    plt_Phn->AddHist1D(h1_mWW_Phn_Sg_Wevt[i],"HIST",kRed);
    plt_Phn->SetLegend(0.63,0.76,0.88,0.92);
    plt_Phn->GetLegend()->AddEntry(h1_mWW_Phn_Sg_Wevt_NoCut[i],"Nocut","l");
    plt_Phn->GetLegend()->AddEntry(h1_mWW_Phn_Sg_Wevt[i],"VBFcut","l");
    plt_Phn->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plt_Phn->Draw(myCan,kTRUE,"png");

  }

  return 0;
}
