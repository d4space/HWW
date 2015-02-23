//=======================================
// Scale factors at different mWW ranges for each jet bin
//======================================= 

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

void njet_mjj_detajj_Scale()
{
  //TString OutDir = "mjj_detajj_unweighted";
  TString OutDir = "mjj_detajj_reweighted";
  gSystem->mkdir(OutDir);
  
  TFile *fname_phantom;
  TFile *fname_powheg;

  fname_phantom  = new TFile("phantom/phantom_CommonCut_VBFnjet.root");
  //fname_powheg   = new TFile("POWHEG_VBF_unweighted/POWHEG_VBF_CommonCut_VBFnjet.root");
  fname_powheg   = new TFile("POWHEG_VBF_reweighted/POWHEG_VBF_CommonCut_VBFnjet.root");

  //Histograms
  TH1D* h1_mjj_phantom[5];
  TH1D* h1_mjj_powheg[5];
  TH1D* h1_detajj_phantom[5];
  TH1D* h1_detajj_powheg[5];

  //Inclusive Total number
  double nTotalPha_mjj;
  double nTotalPow_mjj;
  double nTotalPha_detajj;
  double nTotalPow_detajj;
  
  double ymax;

  char tmpName[50];
  char histName[50];

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);

  //Read Histograms from root file
  for(int i(0);i<5;i++)
  {
    sprintf(tmpName,"h1_mjj_%d",i);

    sprintf(histName,"h1_mjj_phantom_%d",i);
    h1_mjj_phantom[i] = (TH1D*)fname_phantom->Get(tmpName)->Clone(histName); h1_mjj_phantom[i]->Sumw2();
    
    sprintf(histName,"h1_mjj_powheg_%d",i);
    h1_mjj_powheg[i] = (TH1D*)fname_powheg->Get(tmpName)->Clone(histName); h1_mjj_powheg[i]->Sumw2();
    
    sprintf(tmpName,"h1_detajj_%d",i);

    sprintf(histName,"h1_detajj_phantom_%d",i);
    h1_detajj_phantom[i] = (TH1D*)fname_phantom->Get(tmpName)->Clone(histName); h1_detajj_phantom[i]->Sumw2();
    
    sprintf(histName,"h1_detajj_powheg_%d",i);
    h1_detajj_powheg[i] = (TH1D*)fname_powheg->Get(tmpName)->Clone(histName); h1_detajj_powheg[i]->Sumw2();

  }

  //Inclusive Total number
  nTotalPha_mjj = h1_mjj_phantom[4] -> Integral();
  nTotalPow_mjj = h1_mjj_powheg[4]  -> Integral();
  nTotalPha_detajj = h1_detajj_phantom[4] -> Integral();
  nTotalPow_detajj = h1_detajj_powheg[4]  -> Integral();

  cout<<nTotalPha_mjj<<"\t"<<nTotalPow_mjj<<"\t"<<nTotalPha_detajj<<"\t"<<nTotalPow_detajj<<endl;
  //Inclusive Total number
  for(int i(0);i<5;i++)
  {
    h1_mjj_phantom[i] -> Scale(1./nTotalPha_mjj);
    h1_mjj_powheg[i]  -> Scale(1./nTotalPow_mjj);
    h1_detajj_phantom[i] -> Scale(1./nTotalPha_detajj);
    h1_detajj_powheg[i]  -> Scale(1./nTotalPow_detajj);
    
    //Save Histograms to file
    ymax = 1.15*TMath::Max(h1_mjj_phantom[i]->GetMaximum(),h1_mjj_powheg[i]->GetMaximum()); 
    
    sprintf(tmpName,"(njet = %d)",i);
    sprintf(histName,"mjj_%d",i);
    if(i==4)
    {
      sprintf(histName,"mjj_incl");
      sprintf(tmpName,"(Inclusive jet bins)");
    }
    CPlot* plotmjj=new CPlot(histName,"","M(jj)","");
    plotmjj->setOutDir(OutDir);
    plotmjj->AddHist1D(h1_mjj_powheg[i],"HIST",kRed);
    plotmjj->AddHist1D(h1_mjj_phantom[i],"HIST",kBlue);
    plotmjj->SetLegend(0.63,0.84,0.88,0.92);
    plotmjj->GetLegend()->AddEntry(h1_mjj_powheg[i],"POWHEG","l");
    plotmjj->GetLegend()->AddEntry(h1_mjj_phantom[i],"Phantom Sig.","l");
    plotmjj->AddTextBox(tmpName,0.6,0.92,0.92,0.95,0);
    plotmjj->SetYRange(-0.001,ymax);
    plotmjj->Draw(myCan,kTRUE,"png");

    ymax = 1.15*TMath::Max(h1_detajj_phantom[i]->GetMaximum(),h1_detajj_powheg[i]->GetMaximum()); 
    
    sprintf(histName,"detajj_%d",i);
    if(i==4)
      sprintf(histName,"detajj_incl");
    CPlot* plotdetajj=new CPlot(histName,"","#Delta#eta(jj)","");
    plotdetajj->setOutDir(OutDir);
    plotdetajj->AddHist1D(h1_detajj_powheg[i],"HIST",kRed);
    plotdetajj->AddHist1D(h1_detajj_phantom[i],"HIST",kBlue);
    plotdetajj->SetLegend(0.63,0.84,0.88,0.92);
    plotdetajj->GetLegend()->AddEntry(h1_detajj_powheg[i],"POWHEG","l");
    plotdetajj->GetLegend()->AddEntry(h1_detajj_phantom[i],"Phantom Sig.","l");
    plotdetajj->AddTextBox(tmpName,0.6,0.92,0.92,0.95,0);
    plotdetajj->SetYRange(-0.001,ymax);
    plotdetajj->Draw(myCan,kTRUE,"png");
  }
}
