//===========================================================
// Calculating reweighing factor to POWHEG to be same to gg2VV
//===========================================================

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

#define NjBin 3 // Nbin is inclusive bin
void CalcPowReW2gg2vv()
{
  //TString OutDir = "mWW_unweighted";
  TString OutDir = "CalcPowReW2gg2vv";
  gSystem->mkdir(OutDir);
  
  TFile *F_gg2vv;
  TFile *F_powheg;

  F_gg2vv   = new TFile("POWHEG/POWHEG_CommonCut_njet.root");
  F_pow     = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_CommonCut_njet.root");

  char tmpName[50];
  char histName[50];
  char jetName[50];

  //Histograms
  TH1D* h1_mWW_gg2vv[NjBin+ 1];
  TH1D* h1_mWW_powheg [NjBin+ 1];
  TH1D* h1_reWeightFac;

  //Calculation of Normalization factor
  double nTotalGG2VV;
  double nTotalPOW;

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);

  //Read Histograms from root file
  for(int i(0);i<NjBin+1;i++)
  {
    
    // Take noWeighted
    sprintf(tmpName, "h1_mWW_Off_noWeight_%d",i);
    sprintf(histName,"h1_mWW_gg2vv_%d",i);
    h1_mWW_gg2vv[i] = (TH1D*)F_gg2vv->Get(tmpName)->Clone(histName);
    h1_mWW_gg2vv[i]->Sumw2();
    
    sprintf(histName,"h1_mWW_powheg_%d",i);
    h1_mWW_powheg[i] = (TH1D*)F_pow->Get(tmpName)->Clone(histName);
    h1_mWW_powheg[i]->Sumw2();
  }

  nTotalGG2VV = h1_mWW_gg2vv[NjBin] -> Integral();
  nTotalPOW   = h1_mWW_powheg[NjBin]-> Integral();

  //Normalization to Inclusive Total number
  for(int i(0);i<=NjBin;i++)
  {
    h1_mWW_gg2vv[i] -> Scale(1./nTotalGG2VV);
    h1_mWW_powheg[i]-> Scale(1./nTotalPOW);
  }
  
  //Calculating reWeight Factor
  h1_reWeightFac = (TH1D*)h1_mWW_gg2vv[4] -> Clone("h1_reWeightFac"); h1_reWeightFac->Sumw2();
  h1_reWeightFac -> Divide(h1_mWW_powheg[4]);

  //Printout reWeight Factor
  for (int j(1);j<=h1_reWeightFac->GetNbinsX();j++)
  {
    cout<<"if(mWW > "<<j*100.<<" && mWW <= "<<100.*(j+1)<<") EvtWeight *="<<h1_reWeightFac->GetBinContent(j)<<";"<<endl;
  }

  //
  //Plot reWeighted Histograms
  //
  for(int i(0);i<NjBin+1;i++)
  {
    // Powheg reWeight
    //h1_mWW_powheg[i] -> Multiply(h1_reWeightFac);
    cout<<i<<"-jet bin: "<<h1_mWW_powheg[i]->Integral()<<"\t"<<h1_mWW_gg2vv[i]->Integral()<<endl;

    sprintf(jetName,"(njet = %d)",i);
    if(i==NjBin-1)
      sprintf(jetName,"(njet #geq %d)",i);
    if(i==NjBin)
      sprintf(jetName,"(Inclusive jet bins)");

    //GG2VV mWW distribution
    sprintf(histName,"mWW_gg2vv_njet_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_gg2vv[i]->GetBinWidth(1));
    CPlot* plotmWW_gg2vv=new CPlot(histName,"","mWW","");
    plotmWW_gg2vv->setOutDir(OutDir);
    plotmWW_gg2vv->AddHist1D(h1_mWW_gg2vv[i],"HIST",kBlack);
    plotmWW_gg2vv->SetLegend(0.63,0.84,0.88,0.92);
    plotmWW_gg2vv->GetLegend()->AddEntry(h1_mWW_gg2vv[i],"Phantom Sig.","l");
    plotmWW_gg2vv->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_gg2vv->SetXRange(0,1500);
    plotmWW_gg2vv->Draw(myCan,kTRUE,"png");

    //Powheg mWW distribution
    sprintf(histName,"mWW_powheg_njet_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_powheg[i]->GetBinWidth(1));
    CPlot* plotmWW_powheg=new CPlot(histName,"","mWW","");
    plotmWW_powheg->setOutDir(OutDir);
    plotmWW_powheg->AddHist1D(h1_mWW_powheg[i],"HIST",kBlack);
    plotmWW_powheg->SetLegend(0.63,0.84,0.88,0.92);
    plotmWW_powheg->GetLegend()->AddEntry(h1_mWW_powheg[i],"POWHEG","l");
    plotmWW_powheg->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_powheg->SetXRange(0,1500);
    plotmWW_powheg->Draw(myCan,kTRUE,"png");

    //Powheg vs gg2vv comparison after reweight
    sprintf(histName,"mWW_powheg_gg2vv_njet_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_powheg[i]->GetBinWidth(1));
    CPlot* plotmWW_comp=new CPlot(histName,"","mWW","");
    plotmWW_comp->setOutDir(OutDir);
    plotmWW_comp->AddHist1D(h1_mWW_gg2vv[i],"HIST",kBlue);
    plotmWW_comp->AddHist1D(h1_mWW_powheg[i],"HIST",kRed);
    plotmWW_comp->SetLegend(0.63,0.76,0.88,0.92);
    plotmWW_comp->GetLegend()->AddEntry(h1_mWW_powheg[i],"POWHEG","l");
    plotmWW_comp->GetLegend()->AddEntry(h1_mWW_gg2vv[i],"Phantom Sig.","l");
    plotmWW_comp->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_comp->SetXRange(0,1500);
    plotmWW_comp->Draw(myCan,kTRUE,"png");
  }
}

