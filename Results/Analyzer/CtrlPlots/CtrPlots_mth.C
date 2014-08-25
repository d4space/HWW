#include <stdio.h>
#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TPaveStats.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TProfile.h>
#include <TLine.h>
#include <THStack.h>

void CtrPlots_mth(TString CutName, TString VarName, TString DirName){

  TString ChannelName[4];
  ChannelName[0] = "sf0j";
  ChannelName[1] = "of0j";
  ChannelName[2] = "sf1j";
  ChannelName[3] = "of1j";

  TFile *f_Hw1Sig  = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_"+CutName+".root");
  TFile *f_Hw25Cot = new TFile("gg2vvHw25Cot8TeV/gg2vvHw25Cot8TeV_"+CutName+".root");
  TFile *f_Hw1SigBckgr  = new TFile("gg2vvHw1Int8TeV/gg2vvHw1Int8TeV_"+CutName+".root");

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  TH1D *h_Hw1Sig[4];
  TH1D *h_Hw1SigBckgr[4];
  TH1D *h_Hw25Cot[4];
  TH1D *h_Hw1Int[4];

  //=====================================
  //Looping for each Channel
  //=====================================
  // 0 = "sf0j"
  // 1 = "of0j"
  // 2 = "sf1j"
  // 3 = "of1j"
  
  for (int i(0);i<4;i++) {
    if(i==0 || i==2)continue;
    TCanvas *myCan = new TCanvas("myCan","Can",800,800);
    gStyle->SetLineWidth(2.);
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0.5);
 
    sprintf(histNameOrg,"h1_mth_%d",i);
    sprintf(histName,"h_Hw1Sig_%d",i);
    h_Hw1Sig[i]= (TH1D*)f_Hw1Sig->Get(histNameOrg)->Clone(histName); h_Hw1Sig[i]->Sumw2();

    sprintf(histName,"h_Hw1SigBckgr_%d",i);
    h_Hw1SigBckgr[i]= (TH1D*)f_Hw1SigBckgr->Get(histNameOrg)->Clone(histName); h_Hw1SigBckgr[i]->Sumw2();

    sprintf(histName,"h_Hw25Cot_%d",i);
    h_Hw25Cot[i]= (TH1D*)f_Hw25Cot->Get(histNameOrg)->Clone(histName); h_Hw25Cot[i]->Sumw2();
    
    sprintf(histName,"h_Hw1Int_%d",i);
    h_Hw1Int[i] = (TH1D*)h_Hw1SigBckgr[i]->Clone(histName); //Interference
    
    h_Hw1Int[i]->Add(h_Hw1Sig[i],-1.);
    h_Hw1Int[i]->Add(h_Hw25Cot[i],-1.);
    
    h_Hw1Int[i]->Rebin(2);
    h_Hw1Int[i]->SetMarkerStyle(20);
    h_Hw1Int[i]->SetLineColor(kBlack);

    h_Hw1Sig[i]->SetLineColor(kRed);
    h_Hw1Sig[i]->SetLineWidth(2);
    
    h_Hw1SigBckgr[i]->SetLineColor(kBlue);
    h_Hw1SigBckgr[i]->SetLineWidth(2);
    
    h_Hw25Cot[i]->SetLineColor(kGreen);
    h_Hw25Cot[i]->SetLineWidth(2);
    
    h_Hw1Sig[i]->GetYaxis()->SetTitleOffset(1.4);
    h_Hw1Sig[i]->GetXaxis()->SetTitleOffset(1.4);
    h_Hw1Sig[i]->SetTitle("");
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_Hw1Sig[i]->GetBinWidth(1));
    h_Hw1Sig[i]->GetYaxis()->SetTitle(tmpName);
    h_Hw1Sig[i]->GetXaxis()->SetTitle("m_{T}^{H} [GeV/c^{2}]");
    h_Hw1Sig[i]->SetMaximum(1.2.*(h_Hw1SigBckgr[i]->GetMaximum()));

    h_Hw1Sig[i]->Draw("HIST");
    h_Hw1SigBckgr[i]->Draw("HISTSAME");
    h_Hw25Cot[i]->Draw("HISTSAME");
    
    TLegend* Lgd = new TLegend(.6,.7,.85,.9);
    if (i==1)
      Lgd->SetHeader("0-jet e#mu");
    if (i==3)
      Lgd->SetHeader("1-jet e#mu");
    Lgd->AddEntry(h_Hw1Sig[i],"Hw1Sig8TeV","l");
    Lgd->AddEntry(h_Hw1SigBckgr[i],"Hw1SigBckgr8TeV","l");
    Lgd->AddEntry(h_Hw25Cot[i],"Hw25Cot8TeV","l");
    Lgd->SetBorderSize(0);
    Lgd->SetFillStyle(0);
    Lgd->SetTextSize(0.03);
    Lgd->Draw();

    gPad->SetLogy(1);
    TString outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + ".png";
    myCan->SaveAs(outFile);

    h_Hw1Int[i]->GetYaxis()->SetTitleOffset(1.4);
    h_Hw1Int[i]->GetXaxis()->SetTitleOffset(1.4);
    h_Hw1Int[i]->SetTitle("");
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_Hw1Int[i]->GetBinWidth(1));
    h_Hw1Int[i]->GetYaxis()->SetTitle(tmpName);
    h_Hw1Int[i]->GetXaxis()->SetTitle("m_{T}^{H} [GeV/c^{2}]");

    h_Hw1Int[i]->Draw("E1");
    
    TLegend* LgdInt = new TLegend(.6,.8,.85,.9);
    if (i==1)
      LgdInt->SetHeader("0-jet e#mu");
    if (i==3)
      LgdInt->SetHeader("1-jet e#mu");
    LgdInt->AddEntry(h_Hw1Int[i],"Hw1Int8TeV","PL");
    LgdInt->SetBorderSize(0);
    LgdInt->SetFillStyle(0);
    LgdInt->SetTextSize(0.03);
    LgdInt->Draw();

    gPad->SetLogy(0);
    TString outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + "_Hw1Int8TeV.png";
    myCan->SaveAs(outFile);

    delete myCan;
  }
}
