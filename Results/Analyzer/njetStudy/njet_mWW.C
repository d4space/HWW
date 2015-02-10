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

int njet_mWW()
{
  TString OutDir = "mWW_unweighted";
  //TString OutDir = "mWW_reweighted_step1";
  gSystem->mkdir(OutDir);
  
  TFile *fname_gg2vv;
  TFile *fname_POWHEG;
  TFile *fname_SHERPA;

  fname_gg2vv  = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_CommonCut_njet.root");
  fname_POWHEG = new TFile("POWHEG_unweighted/POWHEG_CommonCut_njet.root");
  //fname_POWHEG = new TFile("POWHEG_reweighted_step1/POWHEG_CommonCut_njet.root");
  fname_SHERPA = new TFile("SHERPA/SHERPA_CommonCut_njet.root");

  char tmpName[50];
  char histName[50];
  char jetName[50];

  //Histograms
  TH1D* h1_gg2vv_mWW[4];
  TH1D* h1_powheg_mWW[4];
  TH1D* h1_sherpa_mWW[4];
  
  TH1D* h1_gg2vv_mWW_noW[4];
  TH1D* h1_powheg_mWW_noW[4];
  TH1D* h1_sherpa_mWW_noW[4];

  double err_gg2vv;
  double err_powheg;
  double err_sherpa;

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  
  for(int i(0);i<4;i++)
  {
    sprintf(tmpName,"h1_mWW_OffSh_%d",i);
    sprintf(histName,"h1_gg2vv_mWW_%d",i);
    h1_gg2vv_mWW[i] = (TH1D*)fname_gg2vv->Get(tmpName)->Clone(histName); h1_gg2vv_mWW[i]->Sumw2();
    
    sprintf(histName,"h1_powheg_mWW_%d",i);
    h1_powheg_mWW[i] = (TH1D*)fname_POWHEG->Get(tmpName)->Clone(histName); h1_powheg_mWW[i]->Sumw2();
  
    sprintf(histName,"h1_sherpa_mWW_%d",i);
    h1_sherpa_mWW[i] = (TH1D*)fname_SHERPA->Get(tmpName)->Clone(histName); h1_sherpa_mWW[i]->Sumw2();
  
    sprintf(tmpName,"h1_mWW_OffSh_noWeight_%d",i);
    sprintf(histName,"h1_gg2vv_mWW_noW_%d",i);
    h1_gg2vv_mWW_noW[i] = (TH1D*)fname_gg2vv->Get(tmpName)->Clone(histName); h1_gg2vv_mWW_noW[i]->Sumw2();
    
    sprintf(histName,"h1_powheg_mWW_noW_%d",i);
    h1_powheg_mWW_noW[i] = (TH1D*)fname_POWHEG->Get(tmpName)->Clone(histName); h1_powheg_mWW_noW[i]->Sumw2();
  
    sprintf(histName,"h1_sherpa_mWW_noW_%d",i);
    h1_sherpa_mWW_noW[i] = (TH1D*)fname_SHERPA->Get(tmpName)->Clone(histName); h1_sherpa_mWW_noW[i]->Sumw2();
  
    for (int j(1);j<=h1_gg2vv_mWW[i]->GetNbinsX();j++)
    {
      err_gg2vv  = 0.;
      err_powheg = 0.;
      err_sherpa = 0.;
      if(h1_gg2vv_mWW[i]->GetBinContent(j)>0.)
	err_gg2vv  = sqrt(h1_gg2vv_mWW_noW[i]->GetBinContent(j))*(h1_gg2vv_mWW[i]->GetBinContent(j)/h1_gg2vv_mWW_noW[i]->GetBinContent(j));
      if(h1_powheg_mWW[i]->GetBinContent(j)>0.)
	err_powheg = sqrt(h1_powheg_mWW_noW[i]->GetBinContent(j))*(h1_powheg_mWW[i]->GetBinContent(j)/h1_powheg_mWW_noW[i]->GetBinContent(j));
      if(h1_sherpa_mWW[i]->GetBinContent(j)>0.)
	err_sherpa = sqrt(h1_sherpa_mWW_noW[i]->GetBinContent(j))*(h1_sherpa_mWW[i]->GetBinContent(j)/h1_sherpa_mWW_noW[i]->GetBinContent(j));
      h1_gg2vv_mWW[i]  -> SetBinError(j,err_gg2vv);
      h1_powheg_mWW[i] -> SetBinError(j,err_powheg);
      h1_sherpa_mWW[i] -> SetBinError(j,err_sherpa);
    }
    //Normalize Histograms
    h1_gg2vv_mWW[i]   -> Scale(1./h1_gg2vv_mWW[i]->Integral());
    h1_powheg_mWW[i]  -> Scale(1./h1_powheg_mWW[i]->Integral());
    h1_sherpa_mWW[i]  -> Scale(1./h1_sherpa_mWW[i]->Integral());
    
    h1_sherpa_mWW[i]  -> Rebin(2);
  
//Print weights (Powheg to gg2VV)
    if(i==3)
      for (int j(1);j<=h1_powheg_mWW[i]->GetNbinsX();j++)
    {
      cout<<"if(mWW > "<<(j-1)*10.<<" && mWW <= "<<10.*j<<") EvtWeight *="<<h1_gg2vv_mWW[i]->GetBinContent(j)/h1_powheg_mWW[i]->GetBinContent(j)<<";"<<endl;
    }

    sprintf(jetName,"(njet = %d)",i);
    if(i==2)
      sprintf(jetName,"(njet #geq 2)");
    if(i==3)
      sprintf(jetName,"(Inclusive jet bins)");

    //Save Histograms to file
    sprintf(histName,"gg2vv_mWW_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_gg2vv_mWW[i]->GetBinWidth(1));
    CPlot* plotmWW_gg2vv=new CPlot(histName,"","mWW","");
    plotmWW_gg2vv->setOutDir(OutDir);
    plotmWW_gg2vv->AddHist1D(h1_gg2vv_mWW[i],"HIST",kBlack);
    plotmWW_gg2vv->SetLegend(0.63,0.84,0.88,0.92);
    plotmWW_gg2vv->GetLegend()->AddEntry(h1_gg2vv_mWW[i],"gg2VV Sig.","l");
    plotmWW_gg2vv->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_gg2vv->Draw(myCan,kTRUE,"png");

    //Powheg gg2VV comparison after step 1
    sprintf(histName,"gg2vv_powheg_mWW_comp_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_gg2vv_mWW[i]->GetBinWidth(1));
    CPlot* plotmWW_comp=new CPlot(histName,"","mWW","");
    plotmWW_comp->setOutDir(OutDir);
    plotmWW_comp->AddHist1D(h1_gg2vv_mWW[i],"HIST",kBlue);
    plotmWW_comp->AddHist1D(h1_powheg_mWW[i],"HIST",kRed);
    plotmWW_comp->SetLegend(0.63,0.76,0.88,0.92);
    plotmWW_comp->GetLegend()->AddEntry(h1_powheg_mWW[i],"POWHEG","l");
    plotmWW_comp->GetLegend()->AddEntry(h1_gg2vv_mWW[i],"gg2VV Sig.","l");
    plotmWW_comp->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_comp->Draw(myCan,kTRUE,"png");

    sprintf(histName,"powheg_mWW_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_powheg_mWW[i]->GetBinWidth(1));
    CPlot* plotmWW_powheg=new CPlot(histName,"","mWW","");
    plotmWW_powheg->setOutDir(OutDir);
    plotmWW_powheg->AddHist1D(h1_powheg_mWW[i],"HIST",kBlack);
    plotmWW_powheg->SetLegend(0.63,0.84,0.88,0.92);
    plotmWW_powheg->GetLegend()->AddEntry(h1_powheg_mWW[i],"POWHEG","l");
    plotmWW_powheg->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_powheg->Draw(myCan,kTRUE,"png");

    sprintf(histName,"sherpa_mWW_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_sherpa_mWW[i]->GetBinWidth(1));
    CPlot* plotmWW_sherpa=new CPlot(histName,"","mWW","");
    plotmWW_sherpa->setOutDir(OutDir);
    plotmWW_sherpa->AddHist1D(h1_sherpa_mWW[i],"HIST",kBlack);
    plotmWW_sherpa->SetLegend(0.63,0.84,0.88,0.92);
    plotmWW_sherpa->GetLegend()->AddEntry(h1_sherpa_mWW[i],"Sherpa Sig.","l");
    plotmWW_sherpa->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_sherpa->Draw(myCan,kTRUE,"png");
  }

  return 0;
}
