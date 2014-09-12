#include <TProfile.h>
#include "../../Utils/const.h"
#include "../../Utils/CPlot.hh"
#include "../../Utils/MitStyleRemix.hh"

// Hw1
#define Hw1IntXsec 33.4764 //fb

int CtrPlots_SF(TString BaseName, TString CutName)
{
  TString OutDir = "CtrPlots_SF_mH_mll";
  gSystem->mkdir(OutDir);

  TString fSig;
  TString fInt;
  TString fCot;
  
  fInt = "SF_Hw1g2vvInt8TeV/CtrPlt.root";

  TFile *fname[3];
  fname[1] = new TFile(fInt);

  char tmpName[50];
  char histName[50];

  //Histograms
  TH1D* h1_mH[3];
  TH2D* h2_mH_mll[3];

  double LumiWeight[3];
  LumiWeight[1] = 24998./Hw1IntXsec;
  
  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  
  for(int i(0);i<3;i++)
  {
    sprintf(tmpName,"h1_mH_%d",i);
    sprintf(histName,"h2_mH_mll_%d",i);
    if(i==0)
    {
      h1_mH[i]     = (TH1D*)fname[1]->Get("h1_mH_mumu")->Clone(tmpName);
      h2_mH_mll[i] = (TH2D*)fname[1]->Get("h2_mH_mll_mumu")->Clone(histName);
    }else if(i==1){
      h1_mH[i] = (TH1D*)fname[1]->Get("h1_mH_elel")->Clone(tmpName);
      h2_mH_mll[i] = (TH2D*)fname[1]->Get("h2_mH_mll_elel")->Clone(histName);
    }else if(i==2){
      h1_mH[i] = (TH1D*)fname[1]->Get("h1_mH_tautau")->Clone(tmpName);
      h2_mH_mll[i] = (TH2D*)fname[1]->Get("h2_mH_mll_tautau")->Clone(histName);
    }
  
    // Normalize to 8 TeV total Data
    h1_mH[i]      -> Sumw2();
    h2_mH_mll[i]  -> Sumw2();
    h1_mH[i]      -> Scale(LumiTotal8TeV/LumiWeight[1]);
    //h2_mH_mll[i]  -> Scale(LumiTotal8TeV/LumiWeight[1]);
    h2_mH_mll[i]  -> SetMarkerSize(0.4);
  }

  //Save Histograms to file
  //MuMu
  sprintf(tmpName,"Events / %.1f GeV/c^{2}",h1_mH[0]->GetBinWidth(1));
  CPlot* muPlot_mH = new CPlot("mH_mumu","","m_{H} [GeV/c^{2}]",tmpName);
  muPlot_mH->setOutDir(OutDir);
  muPlot_mH->AddHist1D(h1_mH[0],"HIST",kRed);
  muPlot_mH->SetLegend(0.55,0.8,0.85,0.9);
  muPlot_mH->GetLegend()->AddEntry(h1_mH[0],"Hw1Int8TeV #mu#mu","l");
  muPlot_mH->SetLogy();
  muPlot_mH->Draw(myCan,kTRUE,"png");
    
  CPlot* muPlot_mH_mll = new CPlot("mH_mll_mumu","","m_{H} [GeV/c^{2}]","m_{#mu#mu} [GeV/c^{2}]");
  muPlot_mH_mll->setOutDir(OutDir);
  muPlot_mH_mll->AddHist2D(h2_mH_mll[0]);
  muPlot_mH_mll->Draw(myCan,kTRUE,"png");

  //EleEle
  sprintf(tmpName,"Events / %.1f GeV/c^{2}",h1_mH[1]->GetBinWidth(1));
  CPlot* elPlot_mH = new CPlot("mH_elel","","m_{H} [GeV/c^{2}]",tmpName);
  elPlot_mH->setOutDir(OutDir);
  elPlot_mH->AddHist1D(h1_mH[1],"HIST",kRed);
  elPlot_mH->SetLegend(0.55,0.8,0.85,0.9);
  elPlot_mH->GetLegend()->AddEntry(h1_mH[1],"Hw1Int8TeV ee","l");
  elPlot_mH->SetLogy();
  elPlot_mH->Draw(myCan,kTRUE,"png");
    
  CPlot* elPlot_mH_mll = new CPlot("mH_mll_elel","","m_{H} [GeV/c^{2}]","m_{ee} [GeV/c^{2}]");
  elPlot_mH_mll->setOutDir(OutDir);
  elPlot_mH_mll->AddHist2D(h2_mH_mll[1]);
  elPlot_mH_mll->Draw(myCan,kTRUE,"png");

  //TauTau
  sprintf(tmpName,"Events / %.1f GeV/c^{2}",h1_mH[2]->GetBinWidth(1));
  CPlot* tauPlot_mH = new CPlot("mH_tautau","","m_{H} [GeV/c^{2}]",tmpName);
  tauPlot_mH->setOutDir(OutDir);
  tauPlot_mH->AddHist1D(h1_mH[3],"HIST",kRed);
  tauPlot_mH->SetLegend(0.55,0.8,0.85,0.9);
  tauPlot_mH->GetLegend()->AddEntry(h1_mH[2],"Hw1Int8TeV #tau#tau","l");
  tauPlot_mH->SetLogy();
  tauPlot_mH->Draw(myCan,kTRUE,"png");
    
  CPlot* tauPlot_mH_mll = new CPlot("mH_mll_tautau","","m_{H} [GeV/c^{2}]","m_{#tau#tau} [GeV/c^{2}]");
  tauPlot_mH_mll->setOutDir(OutDir);
  tauPlot_mH_mll->AddHist2D(h2_mH_mll[2]);
  tauPlot_mH_mll->Draw(myCan,kTRUE,"png");

  return 0;
}
