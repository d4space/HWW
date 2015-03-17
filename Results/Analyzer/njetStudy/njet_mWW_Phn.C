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

int njet_mWW_Phn()
{
  TString OutDir = "mWW_Pow_weighted_2_Phn";
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

  //Histograms
  TH1D* h1_mWW_Phn_Sg[NjetBin+1];

  TH1D* h1_mWW_Phn_1_noW[NjetBin+1];
  TH1D* h1_mWW_Phn_9_noW[NjetBin+1];
  TH1D* h1_mWW_Phn_25_noW[NjetBin+1];

  TH1D* h1_mWW_Phn_1_Wevt[NjetBin+1];
  TH1D* h1_mWW_Phn_9_Wevt[NjetBin+1];
  TH1D* h1_mWW_Phn_25_Wevt[NjetBin+1];
  TH1D* h1_mWW_Phn_Sg_Wevt[NjetBin+1];

  TH1D* h1_mWW_Pow[NjetBin+1];
  TH1D* h1_mWW_Pow_noW[NjetBin+1];
  TH1D* h1_mWW_Pow_WevtPow2Gen[NjetBin+1];

  double tmpK, tmpV1, tmpV2, tmpE;

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  
  for(int i(0);i<NjetBin+1;i++)
  {
    // Take noWeighted
    sprintf(tmpName, "h1_mWW_Off_noWeight_%d",i);
    sprintf(histName,"h1_mWW_Phn_1_noW_%d",i);
    h1_mWW_Phn_1_noW[i] = (TH1D*)f_phn_1->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_1_noW[i]->Sumw2();
    sprintf(histName,"h1_mWW_Phn_9_noW_%d",i);
    h1_mWW_Phn_9_noW[i] = (TH1D*)f_phn_9->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_9_noW[i]->Sumw2();
    sprintf(histName,"h1_mWW_Phn_25_noW_%d",i);
    h1_mWW_Phn_25_noW[i] = (TH1D*)f_phn_25->Get(tmpName)->Clone(histName);
    h1_mWW_Phn_25_noW[i]->Sumw2();

    sprintf(histName,"h1_mWW_Pow_noW_%d",i);
    h1_mWW_Pow_noW[i] = (TH1D*)f_pow->Get(tmpName)->Clone(histName);
    h1_mWW_Pow_noW[i]->Sumw2();

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

    sprintf(tmpName, "h1_mWW_Off_WevtPow2Gen_%d",i);
    sprintf(histName,"h1_mWW_Pow_WevtPow2Gen_%d",i);
    h1_mWW_Pow_WevtPow2Gen[i] = (TH1D*)f_pow->Get(tmpName)->Clone(histName);
    h1_mWW_Pow_WevtPow2Gen[i]->Sumw2();


    // Total number before signal extraction
    //NttPhan_1_noW[i] = h1_mWW_Phn_1_noW[i]->Integral();
    //NttPhan_9_noW[i] = h1_mWW_Phn_9_noW[i]->Integral();
    //NttPhan_25_noW[i]= h1_mWW_Phn_25_noW[i]->Integral();
    //
    // Rebin ===============================
    h1_mWW_Phn_1_noW[i]->Rebin(3);
    h1_mWW_Phn_9_noW[i]->Rebin(3);
    h1_mWW_Phn_25_noW[i]->Rebin(3);

    h1_mWW_Pow_noW[i]->Rebin(3);

    // Take Weighted
    h1_mWW_Phn_1_Wevt[i] ->Rebin(3);
    h1_mWW_Phn_9_Wevt[i] ->Rebin(3);
    h1_mWW_Phn_25_Wevt[i]->Rebin(3);

    h1_mWW_Pow_WevtPow2Gen[i]->Rebin(3);
    //========================


    // Phantom Signal Extraction without Event Weight histogram
    sprintf(histName,"h1_mWW_Phn_Sg_%d",i);
    h1_mWW_Phn_Sg[i] = (TH1D*) h1_mWW_Phn_1_noW[i]->Clone(histName);
    h1_mWW_Phn_Sg[i]->Sumw2();
    h1_mWW_Phn_Sg[i]->Scale(0.125);
    h1_mWW_Phn_Sg[i]->Add(h1_mWW_Phn_9_noW[i],-0.250);
    h1_mWW_Phn_Sg[i]->Add(h1_mWW_Phn_25_noW[i],0.125);

    sprintf(histName,"h1_mWW_Pow_%d",i);
    h1_mWW_Pow[i] = (TH1D*) h1_mWW_Pow_noW[i]->Clone(histName);

    sprintf(histName,"h1_mWW_Phn_Sg_Wevt_%d",i);
    h1_mWW_Phn_Sg_Wevt[i] = (TH1D*)h1_mWW_Phn_1_Wevt[i]->Clone(histName);
    h1_mWW_Phn_Sg_Wevt[i]->Add(h1_mWW_Phn_9_Wevt[i]);
    h1_mWW_Phn_Sg_Wevt[i]->Add(h1_mWW_Phn_25_Wevt[i]);

    // Calculation of factor which make the non-Weighted phantom signal to event weighted one for value and error both
    for(int bdx(1);bdx <= h1_mWW_Phn_Sg[i]->GetNbinsX();bdx++)
    {
      tmpV1 = h1_mWW_Phn_Sg_Wevt[i]->GetBinContent(bdx);
      tmpV2 = h1_mWW_Phn_Sg[i]->GetBinContent(bdx);
      tmpE  = h1_mWW_Phn_Sg[i]->GetBinError(bdx);
      tmpK  = tmpV1/tmpV2;
      h1_mWW_Phn_Sg[i]->SetBinContent(bdx, tmpV1);
      h1_mWW_Phn_Sg[i]->SetBinError(bdx, tmpE*tmpK);

      tmpV1 = h1_mWW_Pow_WevtPow2Gen[i]->GetBinContent(bdx);
      tmpV2 = h1_mWW_Pow_noW[i]->GetBinContent(bdx);
      tmpE  = h1_mWW_Pow_noW[i]->GetBinError(bdx);
      tmpK   = tmpV1/tmpV2;

      h1_mWW_Pow[i]->SetBinContent(bdx,tmpV1);
      h1_mWW_Pow[i]->SetBinError(bdx,tmpE*tmpK);
    }
  }
  double Ntt_Phn = h1_mWW_Phn_Sg[NjetBin]->Integral();
  double Ntt_Pow = h1_mWW_Pow[NjetBin]->Integral();
  TH1D* h1_mWW_PowOvPhn[NjetBin+1];
  for(int i(0);i<NjetBin+1;i++)
  {
 
    //Normalize Histograms
    h1_mWW_Pow[i]->Scale(1./Ntt_Pow);
    h1_mWW_Phn_Sg[i]->Scale(1./Ntt_Phn);

    
    //h1_sherpa_mWW[i]  -> Rebin(2);
  

    sprintf(jetName,"(njet = %d)",i);
    if(i==NjetBin-1)
      sprintf(jetName,"(njet #geq %d)",i);
    if(i==NjetBin)
      sprintf(jetName,"(Inclusive jet bins)");

    h1_mWW_Phn_Sg[i]->SetMinimum(-0.007);
    h1_mWW_Pow[i]->SetMinimum(-0.007);

    // Plots
    //Powheg Phantom comparison after step 1
    sprintf(histName,"Phantom_Powheg_mWW_comp_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
    CPlot* plotmWW_comp=new CPlot(histName,"","mWW","");
    plotmWW_comp->setOutDir(OutDir);
    plotmWW_comp->setOutDir(OutDir);
    plotmWW_comp->AddHist1D(h1_mWW_Phn_Sg[i],"e",kBlue);
    //plotmWW_comp->AddHist1D(h1_mWW_Phn_Sg[i],"HIST",kBlue);
    plotmWW_comp->AddHist1D(h1_mWW_Pow[i],"e",kRed);
    plotmWW_comp->SetLegend(0.63,0.76,0.88,0.92);
    plotmWW_comp->GetLegend()->AddEntry(h1_mWW_Pow[i],"POWHEG","pl");
    plotmWW_comp->GetLegend()->AddEntry(h1_mWW_Phn_Sg[i],"Phn Sig.","pl");
    plotmWW_comp->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_comp->Draw(myCan,kTRUE,"png");


    sprintf(histName,"h1_mWW_PowOvPhn_%d",i);
    h1_mWW_PowOvPhn[i] = (TH1D*) h1_mWW_Pow[i]->Clone(histName);
    h1_mWW_PowOvPhn[i]->Sumw2();
    if(i == 2 || i== 3 || i==4){
      h1_mWW_PowOvPhn[i]->SetBinContent(1,0);
      h1_mWW_PowOvPhn[i]->SetBinError(1,0);
      h1_mWW_Phn_Sg[i]->SetBinContent(1,0);
      h1_mWW_Phn_Sg[i]->SetBinError(1,0);
      //h1_mWW_PowOvPhn[i]->SetBinContent(10,0);
      //h1_mWW_PowOvPhn[i]->SetBinError(10,0);
      //h1_mWW_Phn_Sg[i]->SetBinContent(10,0);
      //h1_mWW_Phn_Sg[i]->SetBinError(10,0);
    }
    if(i == 4)
    for(int k(1);k<=h1_mWW_PowOvPhn[i]->GetNbinsX();k++)
    {
      cout<<"bin"<<k<<"\t"<<h1_mWW_PowOvPhn[i]->GetBinContent(k)<<"+"<<h1_mWW_PowOvPhn[i]->GetBinError(k)<<endl;
      cout<<"bin"<<k<<"\t"<<h1_mWW_Phn_Sg[i]->GetBinContent(k)<<"+"<<h1_mWW_Phn_Sg[i]->GetBinError(k)<<endl;
    }
    h1_mWW_PowOvPhn[i]->Divide(h1_mWW_Phn_Sg[i]);

    sprintf(histName,"Powheg_Ov_Phantom_%d",i);
    CPlot* plt_PowOvPhn=new CPlot(histName,"","mWW","");
    plt_PowOvPhn->setOutDir(OutDir);
    plt_PowOvPhn->AddHist1D(h1_mWW_PowOvPhn[i],"e",kBlue);
    plt_PowOvPhn->SetLegend(0.63,0.76,0.88,0.92);
    plt_PowOvPhn->GetLegend()->AddEntry(h1_mWW_PowOvPhn[i],"POWovPhn","p");
    plt_PowOvPhn->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plt_PowOvPhn->Draw(myCan,kTRUE,"png");

  }

  return 0;
}
