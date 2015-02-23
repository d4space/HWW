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

void njet_mWW_Scale()
{
  //TString OutDir = "mWW_sf_reweighted";
  TString OutDir = "mWW_sf_unweighted";
  gSystem->mkdir(OutDir);
  
  TFile *fname_phantom;
  TFile *fname_powheg;

  fname_phantom  = new TFile("phantom/phantom_CommonCut_VBFnjet.root");
  fname_powheg   = new TFile("POWHEG_VBF_unweighted/POWHEG_VBF_CommonCut_VBFnjet.root");
  //fname_powheg   = new TFile("POWHEG_VBF_reweighted/POWHEG_VBF_CommonCut_VBFnjet.root");

  //Histograms
  TH1D* h1_njet_phantom[12];
  TH1D* h1_njet_powheg[12];
  TH1D* h1_njet_noW_phantom[12];
  TH1D* h1_njet_noW_powheg[12];
  TH1D* h1_reWeightFac[12];
  TH1D* h1_powheg_phantom[4];

  //Inclusive jet bin mWW histograms
  TH1D* h1_mWW_phantom;
  TH1D* h1_mWW_powheg;
  TH1D* h1_mWW_noW_phantom;
  TH1D* h1_mWW_noW_powheg;
  
  //Inclusive Total number
  double nTotalPha;
  double nTotalPow;
  
  double ymax;
  double err_phantom;
  double err_powheg;

  char tmpName[50];
  char histName[50];
  char mWWrange[50];

  double Bins[12] = {130.,200.,300.,400.,500.,600.,700.,800.,900.,1000.,1250.,1500.};
  TH1D *h1_tmp = new TH1D("h1_tmp","",11,Bins); h1_tmp->Sumw2();

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);

  //Read Histograms from root file
  for(int i(0);i<12;i++)
  {
    sprintf(tmpName,"h1_njet_OffSh_%d",i);

    sprintf(histName,"h1_njet_phantom_%d",i);
    h1_njet_phantom[i] = (TH1D*)fname_phantom->Get(tmpName)->Clone(histName); h1_njet_phantom[i]->Sumw2();
    
    sprintf(histName,"h1_njet_powheg_%d",i);
    h1_njet_powheg[i] = (TH1D*)fname_powheg->Get(tmpName)->Clone(histName); h1_njet_powheg[i]->Sumw2();
    
    sprintf(tmpName,"h1_njet_OffSh_noWeight_%d",i);

    sprintf(histName,"h1_njet_noW_phantom_%d",i);
    h1_njet_noW_phantom[i] = (TH1D*)fname_phantom->Get(tmpName)->Clone(histName); h1_njet_noW_phantom[i]->Sumw2();
    
    sprintf(histName,"h1_njet_noW_powheg_%d",i);
    h1_njet_noW_powheg[i] = (TH1D*)fname_powheg->Get(tmpName)->Clone(histName); h1_njet_noW_powheg[i]->Sumw2();

    for (int j(1);j<=h1_njet_phantom[i]->GetNbinsX();j++)
    {
      err_phantom = 0.;
      err_powheg  = 0.;
      if(h1_njet_noW_phantom[i]->GetBinContent(j)>0.)
        err_phantom = h1_njet_phantom[i]->GetBinContent(j) * sqrt(h1_njet_noW_phantom[i]->GetBinContent(j))/h1_njet_noW_phantom[i]->GetBinContent(j);
      if(h1_njet_noW_powheg[i]->GetBinContent(j)>0.)
        err_powheg = h1_njet_powheg[i]->GetBinContent(j) * sqrt(h1_njet_noW_powheg[i]->GetBinContent(j))/h1_njet_noW_powheg[i]->GetBinContent(j);
      h1_njet_phantom[i] -> SetBinError(j,err_phantom);
      h1_njet_powheg[i]  -> SetBinError(j,err_powheg);
    }
  }

  //Read inclusive jet bin mWW histograms
  h1_mWW_phantom = (TH1D*)fname_phantom->Get("h1_mww_off_CalcPowRew_4")->Clone("h1_mWW_phantom"); //h1_mWW_phantom->Sumw2();
  h1_mWW_powheg  = (TH1D*)fname_powheg ->Get("h1_mww_off_CalcPowRew_4")->Clone("h1_mWW_powheg"); //h1_mWW_powheg->Sumw2();
  h1_mWW_noW_phantom = (TH1D*)fname_phantom->Get("h1_mww_off_CalcPowRew_noWeight_4")->Clone("h1_mWW_noW_phantom"); //h1_mWW_noW_phantom->Sumw2();
  h1_mWW_noW_powheg  = (TH1D*)fname_powheg ->Get("h1_mww_off_CalcPowRew_noWeight_4")->Clone("h1_mWW_noW_powheg"); //h1_mWW_noW_powheg->Sumw2();
  
  for (int j(1);j<=h1_mWW_phantom->GetNbinsX();j++)
  {
    err_phantom = 0.;
    err_powheg  = 0.;
    if(h1_mWW_noW_phantom->GetBinContent(j)>0.)
      err_phantom = h1_mWW_phantom->GetBinContent(j) * sqrt(h1_mWW_noW_phantom->GetBinContent(j))/h1_mWW_noW_phantom->GetBinContent(j);
    if(h1_mWW_noW_powheg->GetBinContent(j)>0.)
      err_powheg = h1_mWW_powheg->GetBinContent(j) * sqrt(h1_mWW_noW_powheg->GetBinContent(j))/h1_mWW_noW_powheg->GetBinContent(j);
    h1_mWW_phantom -> SetBinError(j,err_phantom);
    h1_mWW_powheg  -> SetBinError(j,err_powheg);
  }
  
  //Inclusive Total number
  nTotalPha = h1_mWW_phantom -> Integral();
  nTotalPow = h1_mWW_powheg  -> Integral();

  //Inclusive Total number
  for(int i(0);i<12;i++)
  {
    h1_njet_phantom[i] -> Scale(1./nTotalPha);
    h1_njet_powheg[i]  -> Scale(1./nTotalPow);
    
    //Scale factors calculation for each jet bin
    sprintf(histName,"h1_reWeightFac_%d",i);
    h1_reWeightFac[i] = (TH1D*)h1_njet_powheg[i] -> Clone(histName); h1_reWeightFac[i]->Sumw2();
    h1_reWeightFac[i] -> Divide(h1_njet_phantom[i]);
    
    //Printout powheg/phantom scale factor for each mWW windows
    if(i==11)
      sprintf(mWWrange,"mWW > 130");
    else
      sprintf(mWWrange,"%.1f < mWW #leq %.1f",Bins[i],Bins[i+1]);
    for (int j(1);j<=h1_reWeightFac[i]->GetNbinsX();j++)
    {
      cout<<mWWrange<<"-bin, "<<j-1<<"=njet: "<<h1_reWeightFac[i]->GetBinContent(j)<<" +/- "<<h1_reWeightFac[i]->GetBinError(j)<<endl;
    }
    
    ymax = 1.15*(h1_njet_phantom[i]->GetMaximum()); 
    if(i==0 || i==11)
      ymax = 1.15*(h1_njet_powheg[i]->GetMaximum()); 
    
    //Save Histograms to file
    sprintf(histName,"Bin_%d",i);
    if(i==11)
      sprintf(histName,"incl_Bin");
    CPlot* plotNjet=new CPlot(histName,"","number of jets","");
    plotNjet->setOutDir(OutDir);
    if(i==11)
    {
      plotNjet->AddHist1D(h1_njet_powheg[i],"E1",kRed);
      plotNjet->AddHist1D(h1_njet_phantom[i],"E1",kBlue);
    }else{
      plotNjet->AddHist1D(h1_njet_powheg[i],"HIST",kRed);
      plotNjet->AddHist1D(h1_njet_phantom[i],"HIST",kBlue);
    }
    plotNjet->SetLegend(0.63,0.84,0.88,0.92);
    plotNjet->GetLegend()->AddEntry(h1_njet_powheg[i],"POWHEG","l");
    plotNjet->GetLegend()->AddEntry(h1_njet_phantom[i],"Phantom Sig.","l");
    plotNjet->AddTextBox(mWWrange,0.6,0.92,0.92,0.95,0);
    plotNjet->SetYRange(-0.001,ymax);
    plotNjet->Draw(myCan,kTRUE,"png");

    h1_njet_powheg[i]->Divide(h1_njet_phantom[i]);
    
    sprintf(histName,"Bin_%d_Ratio",i);
    if(i==11)
    {
      sprintf(histName,"incl_Bin_Ratio");
      cout<<h1_njet_powheg[i]->GetBinContent(3)<<"\t"<<h1_njet_powheg[i]->GetBinContent(4)<<endl;
    }
    CPlot* plotRatio=new CPlot(histName,"","number of jets","POWHEG/Phantom");
    plotRatio->setOutDir(OutDir);
    plotRatio->AddHist1D(h1_njet_powheg[i],"HIST",kRed);
    plotRatio->SetLegend(0.63,0.84,0.88,0.92);
    //plotRatio->GetLegend()->AddEntry(h1_njet_powheg[i],"POWHEG","l");
    plotRatio->AddTextBox(mWWrange,0.6,0.92,0.92,0.95,0);
    plotRatio->SetYRange(-0.001,1.15*(h1_njet_powheg[i]->GetMaximum()));
    plotRatio->Draw(myCan,kTRUE,"png");
  }

  //Write Scale Factors to root file
  TFile f_out(OutDir+"/scaleFactors.root","recreate");
  h1_mWW_phantom -> Scale(1./nTotalPha);
  h1_mWW_powheg  -> Scale(1./nTotalPow);
  h1_mWW_powheg  -> Divide(h1_mWW_phantom);
  for (int i(0);i<5;i++)
  {
    if(i==4)
    {
      h1_powheg_phantom[i] = (TH1D*)h1_mWW_powheg -> Clone("h1_powheg_phantom_4"); h1_powheg_phantom[i]->Sumw2();
    }else{
      sprintf(histName,"h1_powheg_phantom_%d",i);
      h1_powheg_phantom[i] = (TH1D*)h1_tmp -> Clone(histName); h1_powheg_phantom[i]->Sumw2();
      for (int j(1);j<=h1_powheg_phantom[i]->GetNbinsX();j++)
      {
	h1_powheg_phantom[i] -> SetBinContent(j,h1_reWeightFac[j-1]->GetBinContent(i+1));
	h1_powheg_phantom[i] -> SetBinError(j,h1_reWeightFac[j-1]->GetBinError(i+1));
      }
    }
    h1_powheg_phantom[i] -> Write();
  }
}
