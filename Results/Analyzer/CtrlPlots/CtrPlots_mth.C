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

  //TFile *f_H125    = new TFile("H125/H125_"+CutName+".root");
  TFile *f_Hw1Sig  = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_"+CutName+".root");
  TFile *f_Hw1SCI  = new TFile("gg2vvHw1Int8TeV/gg2vvHw1Int8TeV_"+CutName+".root");
  TFile *f_Hw25SCI = new TFile("gg2vvHw25Int8TeV/gg2vvHw25Int8TeV_"+CutName+".root");
  TFile *f_Hw25Cot = new TFile("gg2vvHw25Cot8TeV/gg2vvHw25Cot8TeV_"+CutName+".root");

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  //TH1D *h_H125[4];
  TH1D *h_Hw1Sig[4];
  TH1D *h_Hw1Int[4];
  TH1D *h_Hw1SCI[4];
  TH1D *h_Hw25Cot[4];
  TH1D *h_Hw25SCI[4];
  TH1D *h_Hw1SI[4];
  TH1D *h_Hw25SI[4];

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
    //gStyle->SetErrorX(0.5);
 
    sprintf(histNameOrg,"h1_mth_%d",i);
    //sprintf(histNameOrg,"h1_mllCut_mth_%d",i);
    //sprintf(histName,"h_H125_%d",i);
    //h_H125[i]= (TH1D*)f_H125->Get(histNameOrg)->Clone(histName); h_H125[i]->Sumw2();

    sprintf(histName,"h_Hw1Sig_%d",i);
    h_Hw1Sig[i]= (TH1D*)f_Hw1Sig->Get(histNameOrg)->Clone(histName); h_Hw1Sig[i]->Sumw2();

    sprintf(histName,"h_Hw1SCI_%d",i);
    h_Hw1SCI[i]= (TH1D*)f_Hw1SCI->Get(histNameOrg)->Clone(histName); h_Hw1SCI[i]->Sumw2();

    sprintf(histName,"h_Hw25Cot_%d",i);
    h_Hw25Cot[i]= (TH1D*)f_Hw25Cot->Get(histNameOrg)->Clone(histName); h_Hw25Cot[i]->Sumw2();
    
    sprintf(histName,"h_Hw1Int_%d",i);
    h_Hw1Int[i] = (TH1D*)h_Hw1SCI[i]->Clone(histName); //Interference
    
    sprintf(histName,"h_Hw25SCI_%d",i);
    h_Hw25SCI[i]= (TH1D*)f_Hw25SCI->Get(histNameOrg)->Clone(histName); h_Hw25SCI[i]->Sumw2();

    h_Hw1Int[i]->Add(h_Hw1Sig[i],-1.);
    h_Hw1Int[i]->Add(h_Hw25Cot[i],-1.);
    
    //===========================
    //Signal+Interference
    sprintf(histName,"h_Hw1SI_%d",i);
    h_Hw1SI[i] = (TH1D*)h_Hw1SCI[i]->Clone(histName); //Hw1 Signal+Interference
    h_Hw1SI[i]->Add(h_Hw25Cot[i],-1.);
    h_Hw1SI[i]->SetLineColor(kRed);
    h_Hw1SI[i]->SetLineWidth(2);
    h_Hw1SI[i]->GetYaxis()->SetTitleOffset(1.4);
    h_Hw1SI[i]->GetXaxis()->SetTitleOffset(1.4);
    h_Hw1SI[i]->SetTitle("");
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_Hw1SI[i]->GetBinWidth(1));
    h_Hw1SI[i]->GetYaxis()->SetTitle(tmpName);
    h_Hw1SI[i]->GetXaxis()->SetTitle("m_{T}^{H} [GeV/c^{2}]");
    
    sprintf(histName,"h_Hw25SI_%d",i);
    h_Hw25SI[i] = (TH1D*)h_Hw25SCI[i]->Clone(histName); //Hw25 Signal+Interference
    h_Hw25SI[i]->Add(h_Hw25Cot[i],-1.);
    h_Hw25SI[i]->SetLineColor(kRed);
    h_Hw25SI[i]->SetLineWidth(2);
    h_Hw25SI[i]->GetYaxis()->SetTitleOffset(1.4);
    h_Hw25SI[i]->GetXaxis()->SetTitleOffset(1.4);
    h_Hw25SI[i]->SetTitle("");
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_Hw25SI[i]->GetBinWidth(1));
    h_Hw25SI[i]->GetYaxis()->SetTitle(tmpName);
    h_Hw25SI[i]->GetXaxis()->SetTitle("m_{T}^{H} [GeV/c^{2}]");
    
    TLegend* Lgd1 = new TLegend(.6,.7,.85,.9);
    if (i==1)
      Lgd1->SetHeader("0-jet e#mu");
    if (i==3)
      Lgd1->SetHeader("1-jet e#mu");
    Lgd1->AddEntry(h_Hw1SI[i],"Hw1 S+I 8TeV","l");
    Lgd1->SetBorderSize(0);
    Lgd1->SetFillStyle(0);
    Lgd1->SetTextSize(0.03);
    h_Hw1SI[i] ->Draw("HIST");
    Lgd1->Draw();

    TString outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + "_Hw1SI.png";
    myCan->SaveAs(outFile);
    
    TLegend* Lgd2 = new TLegend(.6,.7,.85,.9);
    if (i==1)
      Lgd2->SetHeader("0-jet e#mu");
    if (i==3)
      Lgd2->SetHeader("1-jet e#mu");
    Lgd2->AddEntry(h_Hw25SI[i],"Hw25 S+I 8TeV","l");
    Lgd2->SetBorderSize(0);
    Lgd2->SetFillStyle(0);
    Lgd2->SetTextSize(0.03);
    h_Hw25SI[i]->Draw("HIST");
    Lgd2->Draw();

    TString outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + "_Hw25SI.png";
    myCan->SaveAs(outFile);
    //===========================
    
    h_Hw1Int[i]->Rebin(2);
    h_Hw1Int[i]->SetMarkerStyle(20);
    h_Hw1Int[i]->SetLineColor(kBlack);

    //h_H125[i]->SetLineColor(kBlack);
    //h_H125[i]->SetLineWidth(2);
    //h_H125[i]->Rebin(2);
    
    h_Hw1Sig[i]->SetLineColor(kRed);
    h_Hw1Sig[i]->SetLineWidth(2);
    h_Hw1Sig[i]->Rebin(2);
    
    h_Hw1SCI[i]->SetLineColor(kBlue);
    h_Hw1SCI[i]->SetLineWidth(2);
    h_Hw1SCI[i]->Rebin(2);
    
    h_Hw25Cot[i]->SetLineColor(kGreen);
    h_Hw25Cot[i]->SetLineWidth(2);
    h_Hw25Cot[i]->Rebin(2);
    
    h_Hw1Sig[i]->GetYaxis()->SetTitleOffset(1.4);
    h_Hw1Sig[i]->GetXaxis()->SetTitleOffset(1.4);
    h_Hw1Sig[i]->SetTitle("");
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_Hw1Sig[i]->GetBinWidth(1));
    h_Hw1Sig[i]->GetYaxis()->SetTitle(tmpName);
    h_Hw1Sig[i]->GetXaxis()->SetTitle("m_{T}^{H} [GeV/c^{2}]");
    if((h_Hw1Sig[i]->GetMaximum()) < h_Hw1SCI[i]->GetMaximum())
      h_Hw1Sig[i]->SetMaximum(1.2.*(h_Hw1SCI[i]->GetMaximum()));
    if((h_Hw1Sig[i]->GetMaximum()) < h_Hw25Cot[i]->GetMaximum())
      h_Hw1Sig[i]->SetMaximum(1.2.*(h_Hw25Cot[i]->GetMaximum()));

    h_Hw1Sig[i]->Draw("HIST");
    h_Hw1SCI[i]->Draw("HISTSAME");
    h_Hw25Cot[i]->Draw("HISTSAME");
    //h_H125[i]->Draw("HISTSAME");
    
    TLegend* Lgd = new TLegend(.6,.7,.85,.9);
    if (i==1)
      Lgd->SetHeader("0-jet e#mu");
    if (i==3)
      Lgd->SetHeader("1-jet e#mu");
    Lgd->AddEntry(h_Hw1Sig[i],"Hw1Sig8TeV","l");
    Lgd->AddEntry(h_Hw1SCI[i],"Hw1SCI8TeV","l");
    Lgd->AddEntry(h_Hw25Cot[i],"Hw25Cot8TeV","l");
    //Lgd->AddEntry(h_H125[i],"m_{H}=125 GeV","l");
    Lgd->SetBorderSize(0);
    Lgd->SetFillStyle(0);
    Lgd->SetTextSize(0.03);
    Lgd->Draw();

    gPad->SetLogy(1);
    outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + ".png";
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
    outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + "_Hw1Int8TeV.png";
    myCan->SaveAs(outFile);

    delete myCan;
  }
}
