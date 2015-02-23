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

void CalcPowRew()
{
  //TString OutDir = "mWW_unweighted";
  TString OutDir = "mWW_reweighted";
  gSystem->mkdir(OutDir);
  
  TFile *fname_phantom;
  TFile *fname_powheg;

  fname_phantom  = new TFile("phantom/phantom_CommonCut_VBFnjet.root");
  //fname_powheg   = new TFile("POWHEG_VBF_unweighted/POWHEG_VBF_CommonCut_VBFnjet.root");
  fname_powheg   = new TFile("POWHEG_VBF_reweighted/POWHEG_VBF_CommonCut_VBFnjet.root");

  char tmpName[50];
  char histName[50];
  char jetName[50];

  //Histograms
  TH1D* h1_mWW_phantom[5];
  TH1D* h1_mWW_powheg[5];
  TH1D* h1_reWeightFac;

  //Calculation of Normalization factor
  double nTotalPha;
  double nTotalPow;

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);

  //Read Histograms from root file
  for(int i(0);i<5;i++)
  {
    sprintf(tmpName,"h1_mww_off_CalcPowRew_%d",i);
    
    sprintf(histName,"h1_mWW_phantom_%d",i);
    h1_mWW_phantom[i] = (TH1D*)fname_phantom->Get(tmpName)->Clone(histName); h1_mWW_phantom[i]->Sumw2();
    
    sprintf(histName,"h1_mWW_powheg_%d",i);
    h1_mWW_powheg[i] = (TH1D*)fname_powheg->Get(tmpName)->Clone(histName); h1_mWW_powheg[i]->Sumw2();
  }

  nTotalPha = h1_mWW_phantom[4] -> Integral();
  nTotalPow = h1_mWW_powheg[4]  -> Integral();

  //Normalization to Inclusive Total number
  for(int i(0);i<=4;i++)
  {
    h1_mWW_phantom[i] -> Scale(1./nTotalPha);
    h1_mWW_powheg[i]  -> Scale(1./nTotalPow);
  }
  
  //Calculating reWeight Factor
  h1_reWeightFac = (TH1D*)h1_mWW_phantom[4] -> Clone("h1_reWeightFac"); h1_reWeightFac->Sumw2();
  h1_reWeightFac -> Divide(h1_mWW_powheg[4]);

  //Printout reWeight Factor
  for (int j(1);j<=h1_reWeightFac->GetNbinsX();j++)
  {
    cout<<"if(mWW > "<<j*100.<<" && mWW <= "<<100.*(j+1)<<") EvtWeight *="<<h1_reWeightFac->GetBinContent(j)<<";"<<endl;
  }

  //
  //Plot reWeighted Histograms
  //
  for(int i(0);i<5;i++)
  {
    // Powheg reWeight
    //h1_mWW_powheg[i] -> Multiply(h1_reWeightFac);
    cout<<i<<"-jet bin: "<<h1_mWW_powheg[i]->Integral()<<"\t"<<h1_mWW_phantom[i]->Integral()<<endl;

    sprintf(jetName,"(njet = %d)",i);
    if(i==3)
      sprintf(jetName,"(njet #geq 3)");
    if(i==4)
      sprintf(jetName,"(Inclusive jet bins)");

    //Phantom mWW distribution
    sprintf(histName,"mWW_phantom_njet_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_phantom[i]->GetBinWidth(1));
    CPlot* plotmWW_phantom=new CPlot(histName,"","mWW","");
    plotmWW_phantom->setOutDir(OutDir);
    plotmWW_phantom->AddHist1D(h1_mWW_phantom[i],"HIST",kBlack);
    plotmWW_phantom->SetLegend(0.63,0.84,0.88,0.92);
    plotmWW_phantom->GetLegend()->AddEntry(h1_mWW_phantom[i],"Phantom Sig.","l");
    plotmWW_phantom->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_phantom->SetXRange(0,1500);
    plotmWW_phantom->Draw(myCan,kTRUE,"png");

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

    //Powheg vs phantom comparison after reweight
    sprintf(histName,"mWW_powheg_phantom_njet_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_powheg[i]->GetBinWidth(1));
    CPlot* plotmWW_comp=new CPlot(histName,"","mWW","");
    plotmWW_comp->setOutDir(OutDir);
    plotmWW_comp->AddHist1D(h1_mWW_phantom[i],"HIST",kBlue);
    plotmWW_comp->AddHist1D(h1_mWW_powheg[i],"HIST",kRed);
    plotmWW_comp->SetLegend(0.63,0.76,0.88,0.92);
    plotmWW_comp->GetLegend()->AddEntry(h1_mWW_powheg[i],"POWHEG","l");
    plotmWW_comp->GetLegend()->AddEntry(h1_mWW_phantom[i],"Phantom Sig.","l");
    plotmWW_comp->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_comp->SetXRange(0,1500);
    plotmWW_comp->Draw(myCan,kTRUE,"png");
  }
}

