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

int njet_mWW_Scale()
{
  TString OutDir = "mWW_sf_reweighted_step1";
  //TString OutDir = "mWW_sf_unweighted";
  gSystem->mkdir(OutDir);
  
  TFile *fname_gg2vv;
  TFile *fname_POWHEG;
  TFile *fname_SHERPA;

  fname_gg2vv  = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_CommonCut_njet.root");
  //fname_POWHEG = new TFile("POWHEG_unweighted/POWHEG_CommonCut_njet.root");
  fname_POWHEG = new TFile("POWHEG_reweighted_step1/POWHEG_CommonCut_njet.root");
  fname_SHERPA = new TFile("SHERPA/SHERPA_CommonCut_njet.root");

  char tmpName[50];
  char a0Name[50];
  char a1Name[50];
  char histName[50];
  char mWWrange[50];

  //Histograms
  TH1D* h1_gg2vv_mWW[4];
  TH1D* h1_powheg_mWW[4];
  TH1D* h1_sherpa_mWW[4];

  TH1D* h1_gg2vv_mWW_noW[4];
  TH1D* h1_powheg_mWW_noW[4];
  TH1D* h1_sherpa_mWW_noW[4];
  
  TH1D* h1_gg2vv_njet[12];
  TH1D* h1_powheg_njet[12];
  TH1D* h1_sherpa_njet[12];
  
  TH1D* h1_gg2vv_njet_noW[12];
  TH1D* h1_powheg_njet_noW[12];
  TH1D* h1_sherpa_njet_noW[12];
  
  TH1D* h1_powheg_gg2vv_njet[12];
  TH1D* h1_powheg_sherpa_njet[12];
  
  TH1D* h1_gg2vv_mjj;
  TH1D* h1_powheg_mjj;
  TH1D* h1_sherpa_mjj;
  TH1D* h1_gg2vv_detajj;
  TH1D* h1_powheg_detajj;
  TH1D* h1_sherpa_detajj;
  
  double Bins[12] = {130.,200.,300.,400.,500.,600.,700.,800.,900.,1000.,1250.,1500.};
  double ymax;
  double err_gg2vv;
  double err_powheg;
  double err_sherpa;

  TH1D *h1_powheg_gg2vv_0 = new TH1D("h1_powheg_gg2vv_0","h1_powheg_gg2vv_0",11,Bins); h1_powheg_gg2vv_0->Sumw2();
  TH1D *h1_powheg_gg2vv_1 = new TH1D("h1_powheg_gg2vv_1","h1_powheg_gg2vv_1",11,Bins); h1_powheg_gg2vv_1->Sumw2();
  TH1D *h1_powheg_gg2vv_2 = new TH1D("h1_powheg_gg2vv_2","h1_powheg_gg2vv_2",11,Bins); h1_powheg_gg2vv_2->Sumw2();
  TH1D *h1_powheg_gg2vv_3 = new TH1D("h1_powheg_gg2vv_3","h1_powheg_gg2vv_3",11,Bins); h1_powheg_gg2vv_3->Sumw2();
  TH1D *h1_powheg_gg2vv_4 = new TH1D("h1_powheg_gg2vv_4","h1_powheg_gg2vv_4",11,Bins); h1_powheg_gg2vv_4->Sumw2();

  TH1D *h1_powheg_sherpa_0 = new TH1D("h1_powheg_sherpa_0","h1_powheg_sherpa_0",11,Bins); h1_powheg_sherpa_0->Sumw2();
  TH1D *h1_powheg_sherpa_1 = new TH1D("h1_powheg_sherpa_1","h1_powheg_sherpa_1",11,Bins); h1_powheg_sherpa_1->Sumw2();
  TH1D *h1_powheg_sherpa_2 = new TH1D("h1_powheg_sherpa_2","h1_powheg_sherpa_2",11,Bins); h1_powheg_sherpa_2->Sumw2();
  TH1D *h1_powheg_sherpa_3 = new TH1D("h1_powheg_sherpa_3","h1_powheg_sherpa_3",11,Bins); h1_powheg_sherpa_3->Sumw2();
  TH1D *h1_powheg_sherpa_4 = new TH1D("h1_powheg_sherpa_4","h1_powheg_sherpa_4",11,Bins); h1_powheg_sherpa_4->Sumw2();

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  
  for(int i(0);i<12;i++)
  {
    sprintf(tmpName,"h1_njet_OffSh_%d",i);
    sprintf(histName,"h1_gg2vv_njet_%d",i);
    h1_gg2vv_njet[i] = (TH1D*)fname_gg2vv->Get(tmpName)->Clone(histName); h1_gg2vv_njet[i]->Sumw2();
    
    sprintf(histName,"h1_sherpa_njet_%d",i);
    h1_sherpa_njet[i] = (TH1D*)fname_SHERPA->Get(tmpName)->Clone(histName); h1_sherpa_njet[i]->Sumw2();
  
    sprintf(histName,"h1_powheg_njet_%d",i);
    h1_powheg_njet[i] = (TH1D*)fname_POWHEG->Get(tmpName)->Clone(histName); h1_powheg_njet[i]->Sumw2();
  
    sprintf(tmpName,"h1_njet_OffSh_noWeight_%d",i);
    sprintf(histName,"h1_gg2vv_njet_noW_%d",i);
    h1_gg2vv_njet_noW[i] = (TH1D*)fname_gg2vv->Get(tmpName)->Clone(histName); h1_gg2vv_njet_noW[i]->Sumw2();
    
    sprintf(histName,"h1_sherpa_njet_noW_%d",i);
    h1_sherpa_njet_noW[i] = (TH1D*)fname_SHERPA->Get(tmpName)->Clone(histName); h1_sherpa_njet_noW[i]->Sumw2();
  
    sprintf(histName,"h1_powheg_njet_noW_%d",i);
    h1_powheg_njet_noW[i] = (TH1D*)fname_POWHEG->Get(tmpName)->Clone(histName); h1_powheg_njet_noW[i]->Sumw2();
    
    for (int j(1);j<=h1_gg2vv_njet[i]->GetNbinsX();j++)
    {
      err_gg2vv  = 0.;
      err_powheg = 0.;
      err_sherpa = 0.;
      if(h1_gg2vv_njet[i]->GetBinContent(j)>0.)
	err_gg2vv  = sqrt(h1_gg2vv_njet[i]->GetBinContent(j))*(h1_gg2vv_njet[i]->GetBinContent(j)/h1_gg2vv_njet_noW[i]->GetBinContent(j));
      if(h1_powheg_njet[i]->GetBinContent(j)>0.)
	err_powheg = sqrt(h1_powheg_njet[i]->GetBinContent(j))*(h1_powheg_njet[i]->GetBinContent(j)/h1_powheg_njet_noW[i]->GetBinContent(j));
      if(h1_sherpa_njet[i]->GetBinContent(j)>0.)
	err_sherpa = sqrt(h1_sherpa_njet[i]->GetBinContent(j))*(h1_sherpa_njet[i]->GetBinContent(j)/h1_sherpa_njet_noW[i]->GetBinContent(j));
      h1_gg2vv_njet[i]  -> SetBinError(j,err_gg2vv);
      h1_powheg_njet[i] -> SetBinError(j,err_powheg);
      h1_sherpa_njet[i] -> SetBinError(j,err_sherpa);
    }

    //Normalize Histograms
    h1_gg2vv_njet[i]  -> Scale(1./h1_gg2vv_njet[i]->Integral());
    h1_powheg_njet[i] -> Scale(1./h1_powheg_njet[i]->Integral());
    
    if(h1_sherpa_njet[i]->Integral()==0)
      h1_sherpa_njet[i] -> Scale(1.);
    else
      h1_sherpa_njet[i] -> Scale(1./h1_sherpa_njet[i]->Integral());
    
    sprintf(histName,"h1_powheg_gg2vv_njet_%d",i);
    h1_powheg_gg2vv_njet[i] = (TH1D*)h1_powheg_njet[i]->Clone(histName); //h1_powheg_gg2vv_njet[i]->Sumw2();
    sprintf(histName,"h1_powheg_sherpa_njet_%d",i);
    h1_powheg_sherpa_njet[i] = (TH1D*)h1_powheg_njet[i]->Clone(histName); //h1_powheg_sherpa_njet[i]->Sumw2();

   
    sprintf(mWWrange,"%.1f < mWW #leq %.1f",Bins[i],Bins[i+1]);
    if(i==11)
      sprintf(mWWrange,"mWW > 130");
    
    ymax = 1.15*(h1_sherpa_njet[i]->GetMaximum()); 
    if(i<=2 || i==4)
      ymax = 1.15*(h1_gg2vv_njet[i]->GetMaximum()); 
    if(i==9 || i==10 || i==11)
      ymax = 1.15*(h1_powheg_njet[i]->GetMaximum()); 

    //Save Histograms to file
    sprintf(histName,"Bin_%d",i);
    if(i==11)
      sprintf(histName,"incl_Bin");
    CPlot* plotNjet=new CPlot(histName,"","number of jets","");
    plotNjet->setOutDir(OutDir);
    plotNjet->AddHist1D(h1_powheg_njet[i],"HIST",kRed);
    plotNjet->AddHist1D(h1_sherpa_njet[i],"HIST",kGreen);
    plotNjet->AddHist1D(h1_gg2vv_njet[i],"HIST",kBlue);
    plotNjet->SetLegend(0.63,0.84,0.88,0.92);
    plotNjet->GetLegend()->AddEntry(h1_powheg_njet[i],"POWHEG","l");
    plotNjet->GetLegend()->AddEntry(h1_gg2vv_njet[i],"gg2VV Sig.","l");
    plotNjet->GetLegend()->AddEntry(h1_sherpa_njet[i],"SHERPA Sig.","l");
    plotNjet->AddTextBox(mWWrange,0.6,0.92,0.92,0.95,0);
    plotNjet->SetYRange(-0.01,ymax);
    plotNjet->Draw(myCan,kTRUE,"png");
 
    h1_powheg_gg2vv_njet[i]  -> Divide(h1_gg2vv_njet[i]);
    h1_powheg_sherpa_njet[i] -> Divide(h1_sherpa_njet[i]);
  
    ymax = 1.15*(h1_powheg_sherpa_njet[i]->GetMaximum()); 
    if((i==0 || i==5) || i==7 || (i>8 && i<=10))
      ymax = 1.15*(h1_powheg_gg2vv_njet[i]->GetMaximum()); 

    sprintf(histName,"Bin_%d_Ratio",i);
    if(i==11)
      sprintf(histName,"incl_Bin_Ratio");
    CPlot* plotRatio=new CPlot(histName,"","number of jets","Scale Factor");
    plotRatio->setOutDir(OutDir);
    plotRatio->AddHist1D(h1_powheg_gg2vv_njet[i],"HIST",kBlue);
    plotRatio->AddHist1D(h1_powheg_sherpa_njet[i],"HIST",kRed);
    plotRatio->SetLegend(0.2,0.85,0.5,0.92);
    plotRatio->GetLegend()->AddEntry(h1_powheg_gg2vv_njet[i],"POWHEG / gg2VV Sig.","l");
    plotRatio->GetLegend()->AddEntry(h1_powheg_sherpa_njet[i],"POWHEG / SHERPA Sig.","l");
    plotRatio->AddTextBox(mWWrange,0.6,0.92,0.92,0.95,0);
    plotRatio->SetYRange(-0.01,ymax);
    plotRatio->Draw(myCan,kTRUE,"png");
    //cout<<mWWrange<<"POWHEG/gg2VV:\t"<<h1_powheg_gg2vv_njet[i]->GetBinContent(1)<<"\t"<<h1_powheg_gg2vv_njet[i]->GetBinContent(2)<<"\t"<<h1_powheg_gg2vv_njet[i]->GetBinContent(3)<<endl;
  }
  
  h1_gg2vv_mjj  = (TH1D*)fname_gg2vv ->Get("h1_mjj_3")->Clone("h1_gg2vv_mjj");  h1_gg2vv_mjj ->Sumw2();
  h1_powheg_mjj = (TH1D*)fname_POWHEG->Get("h1_mjj_3")->Clone("h1_powheg_mjj"); h1_powheg_mjj->Sumw2();
  h1_sherpa_mjj = (TH1D*)fname_SHERPA->Get("h1_mjj_3")->Clone("h1_sherpa_mjj"); h1_sherpa_mjj->Sumw2();

  h1_gg2vv_detajj  = (TH1D*)fname_gg2vv ->Get("h1_detajj_3")->Clone("h1_gg2vv_detajj");  h1_gg2vv_detajj ->Sumw2();
  h1_powheg_detajj = (TH1D*)fname_POWHEG->Get("h1_detajj_3")->Clone("h1_powheg_detajj"); h1_powheg_detajj->Sumw2();
  h1_sherpa_detajj = (TH1D*)fname_SHERPA->Get("h1_detajj_3")->Clone("h1_sherpa_detajj"); h1_sherpa_detajj->Sumw2();
  
  h1_gg2vv_mjj  -> Scale(1./h1_gg2vv_mjj ->Integral());
  h1_powheg_mjj -> Scale(1./h1_powheg_mjj->Integral());
  h1_sherpa_mjj -> Scale(1./h1_sherpa_mjj->Integral());

  sprintf(histName,"mjj");
  CPlot* plotmjj = new CPlot(histName,"","M(jj)","");
  plotmjj->setOutDir(OutDir);
  plotmjj->AddHist1D(h1_powheg_mjj,"HIST",kRed);
  plotmjj->AddHist1D(h1_sherpa_mjj,"HIST",kGreen);
  plotmjj->AddHist1D(h1_gg2vv_mjj, "HIST",kBlue);
  plotmjj->SetLegend(0.63,0.84,0.88,0.92);
  plotmjj->GetLegend()->AddEntry(h1_powheg_mjj,"POWHEG","l");
  plotmjj->GetLegend()->AddEntry(h1_gg2vv_mjj, "gg2VV Sig.","l");
  plotmjj->GetLegend()->AddEntry(h1_sherpa_mjj,"SHERPA Sig.","l");
  plotmjj->AddTextBox("Inclusive jet bins",0.6,0.92,0.92,0.95,0);
  plotmjj->SetYRange(-0.01,1.15*h1_powheg_mjj->GetMaximum());
  plotmjj->Draw(myCan,kTRUE,"png");

  h1_gg2vv_detajj  -> Scale(1./h1_gg2vv_detajj ->Integral());
  h1_powheg_detajj -> Scale(1./h1_powheg_detajj->Integral());
  h1_sherpa_detajj -> Scale(1./h1_sherpa_detajj->Integral());

  sprintf(histName,"detajj");
  CPlot* plotdetajj = new CPlot(histName,"","#Delta#eta(jj)","");
  plotdetajj->setOutDir(OutDir);
  plotdetajj->AddHist1D(h1_powheg_detajj,"HIST",kRed);
  plotdetajj->AddHist1D(h1_sherpa_detajj,"HIST",kGreen);
  plotdetajj->AddHist1D(h1_gg2vv_detajj, "HIST",kBlue);
  plotdetajj->SetLegend(0.63,0.84,0.88,0.92);
  plotdetajj->GetLegend()->AddEntry(h1_powheg_detajj,"POWHEG","l");
  plotdetajj->GetLegend()->AddEntry(h1_gg2vv_detajj, "gg2VV Sig.","l");
  plotdetajj->GetLegend()->AddEntry(h1_sherpa_detajj,"SHERPA Sig.","l");
  plotdetajj->AddTextBox("Inclusive jet bins",0.6,0.92,0.92,0.95,0);
  plotdetajj->SetYRange(-0.01,1.15*h1_powheg_detajj->GetMaximum());
  plotdetajj->Draw(myCan,kTRUE,"png");

  return 0;
}
