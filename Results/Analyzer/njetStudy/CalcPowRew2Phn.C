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

void CalcPowRew2Phn()
{
  //TString OutDir = "mWW_unweighted";
  TString OutDir = "mWW_2Phn";
  gSystem->mkdir(OutDir);
  
  TFile *f_phn_1;
  TFile *f_phn_9;
  TFile *f_phn_25;
  TFile *f_pow;

  f_phn_1  = new TFile("phantom_1SM/phantom_1SM_CommonCut_VBf_NoVetoCentralJet.root");
  f_phn_9  = new TFile("phantom_9SM/phantom_9SM_CommonCut_VBf_NoVetoCentralJet.root");
  f_phn_25 = new TFile("phantom_25SM/phantom_25SM_CommonCut_VBf_NoVetoCentralJet.root");
  f_pow    = new TFile("POWHEG_VBF/POWHEG_VBF_CommonCut_VBf_NoVetoCentralJet.root");
  //f_phn_1  = new TFile("phantom_1SM/phantom_1SM_CommonCut_VBFnjet.root");
  //f_phn_9  = new TFile("phantom_9SM/phantom_9SM_CommonCut_VBFnjet.root");
  //f_phn_25 = new TFile("phantom_25SM/phantom_25SM_CommonCut_VBFnjet.root");
  //f_pow    = new TFile("POWHEG_VBF/POWHEG_VBF_CommonCut_VBFnjet.root");

  char tmpName[50];
  char histName[50];
  char jetName[50];

  //Histograms
  TH1D* h1_mWW_Phn_Sg[5];

  TH1D* h1_mWW_Phn_1_noW[5];
  TH1D* h1_mWW_Phn_9_noW[5];
  TH1D* h1_mWW_Phn_25_noW[5];

  TH1D* h1_mWW_Phn_1_Wevt[5];
  TH1D* h1_mWW_Phn_9_Wevt[5];
  TH1D* h1_mWW_Phn_25_Wevt[5];
  TH1D* h1_mWW_Phn_Sg_Wevt[5];

  TH1D* h1_mWW_Pow[5];
  TH1D* h1_mWW_Pow_noW[5];
  TH1D* h1_mWW_Pow_Wevt[5];
  TH1D* h1_mWW_Pow_Wevt_norm[5];

  TH1D* h1_reWeightFac;

  double tmpK, tmpV1, tmpV2, tmpE;

  //Calculation of Normalization factor
  //double NttPhan_1_noW[5];
  double nTotalPow;

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);

  //Read Histograms from root file
  for(int i(0);i<5;i++) // Index for jet-multiplicity 4 for all
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

    sprintf(histName,"h1_mWW_Pow_Wevt_%d",i);
    h1_mWW_Pow_Wevt[i] = (TH1D*)f_pow->Get(tmpName)->Clone(histName);
    h1_mWW_Pow_Wevt[i]->Sumw2();
    sprintf(histName,"h1_mWW_Pow_Wevt_norm_%d",i);
    h1_mWW_Pow_Wevt_norm[i] = (TH1D*)h1_mWW_Pow_Wevt[i]->Clone(histName);

    sprintf(histName,"h1_mWW_Phn_Sg_Wevt_%d",i);
    h1_mWW_Phn_Sg_Wevt[i] = (TH1D*)h1_mWW_Phn_1_Wevt[i]->Clone(histName);
    h1_mWW_Phn_Sg_Wevt[i]->Add(h1_mWW_Phn_9_Wevt[i]);
    h1_mWW_Phn_Sg_Wevt[i]->Add(h1_mWW_Phn_25_Wevt[i]);

    // Total number before signal extraction
    //NttPhan_1_noW[i] = h1_mWW_Phn_1_noW[i]->Integral();
    //NttPhan_9_noW[i] = h1_mWW_Phn_9_noW[i]->Integral();
    //NttPhan_25_noW[i]= h1_mWW_Phn_25_noW[i]->Integral();

    // Phantom Signal Extraction without Event Weight histogram
    sprintf(histName,"h1_mWW_Phn_Sg_%d",i);
    h1_mWW_Phn_Sg[i] = (TH1D*) h1_mWW_Phn_1_noW[i]->Clone(histName);
    h1_mWW_Phn_Sg[i]->Sumw2();
    h1_mWW_Phn_Sg[i]->Scale(0.125);
    h1_mWW_Phn_Sg[i]->Add(h1_mWW_Phn_9_noW[i],-0.250);
    h1_mWW_Phn_Sg[i]->Add(h1_mWW_Phn_25_noW[i],0.125);

    sprintf(histName,"h1_mWW_Pow_%d",i);
    h1_mWW_Pow[i] = (TH1D*) h1_mWW_Pow_noW[i]->Clone(histName);

    // Calculation of factor which make the non-Weighted phantom signal to event weighted one for value and error both
    for(int bdx(1);bdx <= h1_mWW_Phn_Sg[i]->GetNbinsX();bdx++)
    {
      tmpV1 = h1_mWW_Phn_Sg_Wevt[i]->GetBinContent(bdx);
      tmpV2 = h1_mWW_Phn_Sg[i]->GetBinContent(bdx);
      tmpE  = h1_mWW_Phn_Sg[i]->GetBinError(bdx);
      tmpK  = tmpV1/tmpV2;
      h1_mWW_Phn_Sg[i]->SetBinContent(bdx, tmpV1);
      h1_mWW_Phn_Sg[i]->SetBinError(bdx, tmpE*tmpK);

      tmpV1 = h1_mWW_Pow_Wevt[i]->GetBinContent(bdx);
      tmpV2 = h1_mWW_Pow_noW[i]->GetBinContent(bdx);
      tmpE  = h1_mWW_Pow_noW[i]->GetBinError(bdx);
      tmpK   = tmpV1/tmpV2;

      h1_mWW_Pow[i]->SetBinContent(bdx,tmpV1);
      h1_mWW_Pow[i]->SetBinError(bdx,tmpE*tmpK);
    }
  }

  double NttPhn = h1_mWW_Phn_Sg[4]->Integral();
  double NttPow = h1_mWW_Pow[4]   ->Integral();

  //Normalization to Inclusive Total number
  TH1D* h1_mWW_Phn_Sg_Wevt_norm[5];
  for(int i(0);i<5;i++)
  {
    h1_mWW_Phn_Sg[i]->Scale(1./NttPhn);
    h1_mWW_Pow[i]   ->Scale(1./NttPow);
    h1_mWW_Pow_Wevt_norm[i]   ->Scale(1./NttPow*0.9);
    sprintf(histName,"h1_mWW_Phn_Sg_Wevt_norm_%d",i);
    h1_mWW_Phn_Sg_Wevt_norm[i] = (TH1D*)h1_mWW_Phn_Sg_Wevt[i]->Clone(histName);
    h1_mWW_Phn_Sg_Wevt_norm[i]->Scale(1./NttPhn*0.5);

  }
  CPlot *plt_Pow_All = new CPlot("Pow_All","","mWW","");
  plt_Pow_All->setOutDir(OutDir);
  plt_Pow_All->AddHist1D(h1_mWW_Pow[0],"HIST",kBlack);
  plt_Pow_All->AddHist1D(h1_mWW_Pow[1],"HIST",kBlack);
  plt_Pow_All->AddHist1D(h1_mWW_Pow[2],"HIST",kBlack);
  plt_Pow_All->AddHist1D(h1_mWW_Pow[3],"HIST",kBlack);
  plt_Pow_All->AddHist1D(h1_mWW_Pow[4],"HIST",kBlack);
  plt_Pow_All->AddHist1D(h1_mWW_Pow_Wevt_norm[0],"HIST",kRed);
  plt_Pow_All->AddHist1D(h1_mWW_Pow_Wevt_norm[1],"HIST",kRed);
  plt_Pow_All->AddHist1D(h1_mWW_Pow_Wevt_norm[2],"HIST",kRed);
  plt_Pow_All->AddHist1D(h1_mWW_Pow_Wevt_norm[3],"HIST",kRed);
  plt_Pow_All->AddHist1D(h1_mWW_Pow_Wevt_norm[4],"HIST",kRed);
  plt_Pow_All->Draw(myCan,kTRUE,"png");



  CPlot *plt_Phn_All = new CPlot("Phn_All","","mWW","");
  plt_Phn_All->setOutDir(OutDir);
  //plt_Phn_All->AddHist1D(h1_mWW_Phn_1_Wevt[1],"HIST",kBlack);
  //plt_Phn_All->AddHist1D(h1_mWW_Phn_1_Wevt[2],"HIST",kBlack);
  //plt_Phn_All->AddHist1D(h1_mWW_Phn_1_Wevt[3],"HIST",kBlack);
  //plt_Phn_All->AddHist1D(h1_mWW_Phn_1_Wevt[4],"HIST",kBlack);
  plt_Phn_All->AddHist1D(h1_mWW_Phn_9_Wevt[1],"HIST",kRed);
  plt_Phn_All->AddHist1D(h1_mWW_Phn_9_Wevt[2],"HIST",kRed);
  plt_Phn_All->AddHist1D(h1_mWW_Phn_9_Wevt[3],"HIST",kRed);
  plt_Phn_All->AddHist1D(h1_mWW_Phn_9_Wevt[4],"HIST",kRed);
  //plt_Phn_All->AddHist1D(h1_mWW_Phn_25_Wevt[1],"HIST",kBlue);
  //plt_Phn_All->AddHist1D(h1_mWW_Phn_25_Wevt[2],"HIST",kBlue);
  //plt_Phn_All->AddHist1D(h1_mWW_Phn_25_Wevt[3],"HIST",kBlue);
  //plt_Phn_All->AddHist1D(h1_mWW_Phn_25_Wevt[4],"HIST",kBlue);
  plt_Phn_All->Draw(myCan,kTRUE,"png");
  
  //Calculating reWeight Factor
  h1_reWeightFac = (TH1D*) h1_mWW_Phn_Sg[4]-> Clone("h1_reWeightFac");h1_reWeightFac->Sumw2();
  h1_reWeightFac -> Divide(h1_mWW_Pow[4]);

  //Printout reWeight Factor
  // bin index start from 1 !!!
  for (int j(1);j<=h1_reWeightFac->GetNbinsX();j++) 
  {
    cout<<"\t if(mWW > "<<(j-1)*50.<<" && mWW <= "<<50.*j<<")\t WevtPow2Gen= EvtWeight *"<<h1_reWeightFac->GetBinContent(j)<<";"<<endl;
  }

  //
  //Plot reWeighted Histograms
  //
  for(int i(0);i<5;i++)
  {
    // Powheg reWeight
    //h1_mWW_powheg[i] -> Multiply(h1_reWeightFac);
    //cout<<i<<"-jet bin: "<<h1_mWW_powheg[i]->Integral()<<"\t"<<h1_mWW_phn[i]->Integral()<<endl;

    sprintf(jetName,"(njet = %d)",i);
    if(i==3)
      sprintf(jetName,"(njet #geq 3)");
    if(i==4)
      sprintf(jetName,"(Inclusive jet bins)");

    //Phantom mWW distribution
    sprintf(histName,"mWW_phantom_njet_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_Phn_Sg[i]->GetBinWidth(1));
    CPlot* plotmWW_phantom=new CPlot(histName,"","mWW","");
    plotmWW_phantom->setOutDir(OutDir);
    plotmWW_phantom->AddHist1D(h1_mWW_Phn_Sg[i],"HIST",kBlack);
    plotmWW_phantom->AddHist1D(h1_mWW_Phn_Sg_Wevt_norm[i],"HIST",kRed);
    plotmWW_phantom->SetLegend(0.63,0.84,0.88,0.92);
    plotmWW_phantom->GetLegend()->AddEntry(h1_mWW_Phn_Sg[i],"Phantom Sig.","l");
    plotmWW_phantom->GetLegend()->AddEntry(h1_mWW_Phn_Sg_Wevt_norm[i],"Phantom Sig_Wevt","l");
    plotmWW_phantom->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_phantom->SetXRange(0,1500);
    plotmWW_phantom->Draw(myCan,kTRUE,"png");

    //Powheg mWW distribution
    sprintf(histName,"mWW_powheg_njet_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_Pow[i]->GetBinWidth(1));
    CPlot* plotmWW_powheg=new CPlot(histName,"","mWW","");
    plotmWW_powheg->setOutDir(OutDir);
    plotmWW_powheg->AddHist1D(h1_mWW_Pow[i],"HIST",kBlack);
    plotmWW_powheg->SetLegend(0.63,0.84,0.88,0.92);
    plotmWW_powheg->GetLegend()->AddEntry(h1_mWW_Pow[i],"POWHEG","l");
    plotmWW_powheg->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_powheg->SetXRange(0,1500);
    plotmWW_powheg->Draw(myCan,kTRUE,"png");

    //Powheg vs phantom comparison after reweight
    /***********
    sprintf(histName,"mWW_powheg_phantom_njet_%d",i);
    sprintf(tmpName,"Events / %.1f ",h1_mWW_powheg[i]->GetBinWidth(1));
    CPlot* plotmWW_comp=new CPlot(histName,"","mWW","");
    plotmWW_comp->setOutDir(OutDir);
    plotmWW_comp->AddHist1D(h1_mWW_phn[i],"HIST",kBlue);
    plotmWW_comp->AddHist1D(h1_mWW_powheg[i],"HIST",kRed);
    plotmWW_comp->SetLegend(0.63,0.76,0.88,0.92);
    plotmWW_comp->GetLegend()->AddEntry(h1_mWW_powheg[i],"POWHEG","l");
    plotmWW_comp->GetLegend()->AddEntry(h1_mWW_phn[i],"Phantom Sig.","l");
    plotmWW_comp->AddTextBox(jetName,0.6,0.92,0.92,0.95,0);
    plotmWW_comp->SetXRange(0,1500);
    plotmWW_comp->Draw(myCan,kTRUE,"png");
    *****************/
  }
  CPlot* plotmWW_ReW=new CPlot("ReweightingFactor","","mWW","");
  plotmWW_ReW->setOutDir(OutDir);
  plotmWW_ReW->AddHist1D(h1_reWeightFac,"e",kBlack);
  plotmWW_ReW->Draw(myCan,kTRUE,"png");
}

