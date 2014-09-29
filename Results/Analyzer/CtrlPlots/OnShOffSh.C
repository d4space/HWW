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

void OnShOffSh(TString CutName, TString VarName, TString DirName){

  TString ChannelName[4];
  ChannelName[0] = "sf0j";
  ChannelName[1] = "of0j";
  ChannelName[2] = "sf1j";
  ChannelName[3] = "of1j";

  TFile *fSCI = new TFile("gg2vvHw1Int8TeV/gg2vvHw1Int8TeV_"+CutName+".root");
  TFile *fSig = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_"+CutName+".root");
  TFile *fCot = new TFile("gg2vvHw25Cot8TeV/gg2vvHw25Cot8TeV_"+CutName+".root");

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  TH1D *h1_OnSh1[4];
  TH1D *h1_OnSh2[4];
  TH1D *h1_OffSh1[4];
  TH1D *h1_OffSh2[4];

  //2D histograms
  TH2D *h2_SCIOnSh[4];
  TH2D *h2_SCIOffSh[4];
  TH2D *h2_cotOnSh[4];
  TH2D *h2_cotOffSh[4];

  //Continuum
  TH1D *h1_cotOnSh1[4];
  TH1D *h1_cotOnSh2[4];
  TH1D *h1_cotOffSh1[4];
  TH1D *h1_cotOffSh2[4];

  //2D histograms

  //=====================================
  //Looping for each Channel
  //=====================================
  // 0 = "sf0j"
  // 1 = "of0j"
  // 2 = "sf1j"
  // 3 = "of1j"
  for (int i(0);i<4;i++) {
    if(i == 0 || i == 2) continue;
    if(VarName == "mthmll"){
      sprintf(histNameOrg,"h2_mthmll_OnSh_%d",i);
      sprintf(histName,"h2_SCIOnSh_%d",i);
      h2_SCIOnSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName);  h2_SCIOnSh[i]->Sumw2();
      
      sprintf(histName,"h2_cotOnSh_%d",i);
      h2_cotOnSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName);  h2_cotOnSh[i]->Sumw2();
      
      sprintf(histNameOrg,"h2_mthmll_OffSh_%d",i);
      sprintf(histName,"h2_SCIOffSh_%d",i);
      h2_SCIOffSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName); h2_SCIOffSh[i]->Sumw2();
      
      sprintf(histName,"h2_cotOffSh_%d",i);
      h2_cotOffSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName); h2_cotOffSh[i]->Sumw2();
    }else if(VarName == "mthptll"){//HERE
      sprintf(histNameOrg,"h2_mthptll_OnSh_%d",i);
      sprintf(histName,"h2_SCIOnSh_%d",i);
      h2_SCIOnSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName);  h2_SCIOnSh[i]->Sumw2();
      
      sprintf(histName,"h2_cotOnSh_%d",i);
      h2_cotOnSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName);  h2_cotOnSh[i]->Sumw2();
      
      sprintf(histNameOrg,"h2_mthptll_OffSh_%d",i);
      sprintf(histName,"h2_SCIOffSh_%d",i);
      h2_SCIOffSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName); h2_SCIOffSh[i]->Sumw2();
      
      sprintf(histName,"h2_cotOffSh_%d",i);
      h2_cotOffSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName); h2_cotOffSh[i]->Sumw2();
    }else if(VarName == "mllptll"){//HERE
      sprintf(histNameOrg,"h2_mllptll_OnSh_%d",i);
      sprintf(histName,"h2_SCIOnSh_%d",i);
      h2_SCIOnSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName);  h2_SCIOnSh[i]->Sumw2();
      
      sprintf(histName,"h2_cotOnSh_%d",i);
      h2_cotOnSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName);  h2_cotOnSh[i]->Sumw2();
      
      sprintf(histNameOrg,"h2_mllptll_OffSh_%d",i);
      sprintf(histName,"h2_SCIOffSh_%d",i);
      h2_SCIOffSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName); h2_SCIOffSh[i]->Sumw2();
      
      sprintf(histName,"h2_cotOffSh_%d",i);
      h2_cotOffSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName); h2_cotOffSh[i]->Sumw2();
    }else if(VarName == "mll"){
      //sprintf(histNameOrg,"h1_mll_OnSh_mth_l130_%d",i);
      sprintf(histNameOrg,"h1_mll_OnSh_mth_l120_%d",i);
      sprintf(histName,"h1_OnSh1_%d",i);
      h1_OnSh1[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OnSh1[i]->Sumw2();
      
      sprintf(histName,"h1_cotOnSh1_%d",i);
      h1_cotOnSh1[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_cotOnSh1[i]->Sumw2();
      
      //sprintf(histNameOrg,"h1_mll_OnSh_mth_g130_%d",i);
      sprintf(histNameOrg,"h1_mll_OnSh_mth_g120_%d",i);
      sprintf(histName,"h1_OnSh2_%d",i);
      h1_OnSh2[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OnSh2[i]->Sumw2();
      
      sprintf(histName,"h1_cotOnSh2_%d",i);
      h1_cotOnSh2[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_cotOnSh2[i]->Sumw2();
      
      //sprintf(histNameOrg,"h1_mll_OffSh_mth_l130_%d",i);
      sprintf(histNameOrg,"h1_mll_OffSh_mth_l120_%d",i);
      sprintf(histName,"h1_OffSh1_%d",i);
      h1_OffSh1[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OffSh1[i]->Sumw2();
      
      sprintf(histName,"h1_cotOffSh1_%d",i);
      h1_cotOffSh1[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_cotOffSh1[i]->Sumw2();
      
      //sprintf(histNameOrg,"h1_mll_OffSh_mth_g130_%d",i);
      sprintf(histNameOrg,"h1_mll_OffSh_mth_g120_%d",i);
      sprintf(histName,"h1_OffSh2_%d",i);
      h1_OffSh2[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OffSh2[i]->Sumw2();
      
      sprintf(histName,"h1_cotOffSh2_%d",i);
      h1_cotOffSh2[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_cotOffSh2[i]->Sumw2();
    }else if(VarName == "mth"){
      sprintf(histNameOrg,"h1_mth_OnSh_mll_l83_%d",i);
      sprintf(histName,"h1_OnSh1_%d",i);
      h1_OnSh1[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OnSh1[i]->Sumw2();
      
      sprintf(histName,"h1_cotOnSh1_%d",i);
      h1_cotOnSh1[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_cotOnSh1[i]->Sumw2();
      
      sprintf(histNameOrg,"h1_mth_OnSh_mll_g83_%d",i);
      sprintf(histName,"h1_OnSh2_%d",i);
      h1_OnSh2[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OnSh2[i]->Sumw2();
      
      sprintf(histName,"h1_cotOnSh2_%d",i);
      h1_cotOnSh2[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_cotOnSh2[i]->Sumw2();
      
      sprintf(histNameOrg,"h1_mth_OffSh_mll_l83_%d",i);
      sprintf(histName,"h1_OffSh1_%d",i);
      h1_OffSh1[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OffSh1[i]->Sumw2();
      
      sprintf(histName,"h1_cotOffSh1_%d",i);
      h1_cotOffSh1[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_cotOffSh1[i]->Sumw2();
      
      sprintf(histNameOrg,"h1_mth_OffSh_mll_l83_%d",i);
      sprintf(histName,"h1_OffSh2_%d",i);
      h1_OffSh2[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OffSh2[i]->Sumw2();
      
      sprintf(histName,"h1_cotOffSh2_%d",i);
      h1_cotOffSh2[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_cotOffSh2[i]->Sumw2();
    }
    
    if(DirName == "SigInt"){
      if(VarName == "mll" || VarName == "mth"){
	h1_OnSh1[i] ->Add(h1_cotOnSh1[i],-1);
	h1_OnSh2[i] ->Add(h1_cotOnSh2[i],-1);
	h1_OffSh1[i]->Add(h1_cotOffSh1[i],-1);
	h1_OffSh2[i]->Add(h1_cotOffSh2[i],-1);
      }else if(VarName == "mthmll" || VarName == "mthptll" || VarName == "mllptll"){
	h2_SCIOnSh[i]  ->Add(h2_cotOnSh[i],-1);
	h2_SCIOffSh[i] ->Add(h2_cotOffSh[i],-1);
      }
    }

    TCanvas *myCan = new TCanvas("myCan", "myCan", 900, 800);
    
    gStyle->SetOptStat(0);
    TString dataName = "Hw1 S+B+I 8TeV";
    if(DirName == "SigInt")
      dataName = "Hw1 S+I 8TeV";
    
    TPaveText *tb0 = new TPaveText(.63,.7,.9,.87,"NDC");
    tb0->SetBorderSize(0);
    tb0->SetFillStyle(0);
    tb0->SetTextSize(0.04);
    tb0->AddText(dataName);
    tb0->AddText("CommonCut");
    tb0->AddText(ChannelName[i]+",   mWW < 160");
    
    TPaveText *tb1 = new TPaveText(.55,.7,.9,.87,"NDC");
    tb1->SetBorderSize(0);
    tb1->SetFillStyle(0);
    tb1->SetTextSize(0.04);
    tb1->AddText(dataName);
    tb1->AddText("CommonCut w/o ptll cut");
    tb1->AddText(ChannelName[i]+",   mWW > 160");
    
    TPaveText *tb2 = new TPaveText(.65,.7,.9,.87,"NDC");
    //tb2->SetBorderSize(0);
    tb2->SetFillColor(kWhite);
    tb2->SetFillStyle(1001);
    tb2->SetTextSize(0.03);
    tb2->AddText(dataName);
    tb2->AddText(ChannelName[i]);
    tb2->AddText("CONT  mWW < 160");
    tb2->AddText("COL   mWW > 160");
    
    TPaveText *txtbox1 = new TPaveText(.63,.6,.9,.75,"NDC");
    txtbox1->SetBorderSize(0);
    txtbox1->SetFillStyle(0);
    txtbox1->SetTextSize(0.03);
    txtbox1->AddText(dataName);
    //txtbox1->AddText(ChannelName[i]+",   mth < 130");
    //txtbox1->AddText(ChannelName[i]+",   mth < 120");
    txtbox1->AddText(ChannelName[i]+",   mth<120 && mll<50");
    
    TPaveText *txtbox2 = new TPaveText(.63,.6,.9,.75,"NDC");
    txtbox2->SetBorderSize(0);
    txtbox2->SetFillStyle(0);
    txtbox2->SetTextSize(0.03);
    txtbox2->AddText(dataName);
    //txtbox2->AddText(ChannelName[i]+",   mth > 130");
    //txtbox2->AddText(ChannelName[i]+",   mth > 120");
    txtbox2->AddText(ChannelName[i]+",   mth>120 || mll>50");
    
    TPaveText *txtbox3 = new TPaveText(.63,.6,.9,.75,"NDC");
    txtbox3->SetBorderSize(0);
    txtbox3->SetFillStyle(0);
    txtbox3->SetTextSize(0.04);
    txtbox3->AddText(dataName);
    txtbox3->AddText(ChannelName[i]+",   mll < 83");
    
    TPaveText *txtbox4 = new TPaveText(.63,.6,.9,.75,"NDC");
    txtbox4->SetBorderSize(0);
    txtbox4->SetFillStyle(0);
    txtbox4->SetTextSize(0.04);
    txtbox4->AddText(dataName);
    txtbox4->AddText(ChannelName[i]+",   mll > 83");
    
    TString xlabel = "m_{H}^{T} [GeV/c^{2}]";
    TString ylabel = "m_{ll} [GeV/c^{2}]";
    if(VarName == "mthptll")
      ylabel = "p_{T}^{ll} [GeV/c]";
    if(VarName == "mllptll"){
      xlabel = "m_{ll} [GeV/c^{2}]";
      ylabel = "p_{T}^{ll} [GeV/c]";
    }
    
    if(VarName == "mthmll" || VarName == "mthptll" || VarName == "mllptll"){
      h2_SCIOnSh[i] ->SetTitle("");
      h2_SCIOffSh[i]->SetTitle("");

      h2_SCIOnSh[i]->GetXaxis()->SetTitle(xlabel);
      h2_SCIOnSh[i]->GetYaxis()->SetTitle(ylabel);
      h2_SCIOnSh[i]->GetYaxis()->SetTitleOffset(1.4);
      h2_SCIOnSh[i]->GetXaxis()->SetTitleOffset(1.2);
      
      //h2_OnSh[i]->Draw("CONTZ");
      h2_SCIOnSh[i]->Draw("COLZ");
      tb0->Draw();
      TString outName = "OnOffShell/"+DirName + "_OnShell_" + VarName + "_" + ChannelName[i] + ".png";
      myCan->SaveAs(outName);
    
      h2_SCIOffSh[i]->GetXaxis()->SetTitle(xlabel);
      h2_SCIOffSh[i]->GetYaxis()->SetTitle(ylabel);
      h2_SCIOffSh[i]->GetYaxis()->SetTitleOffset(1.4);
      h2_SCIOffSh[i]->GetXaxis()->SetTitleOffset(1.2);
      
      //h2_SCIOffSh[i]->Draw("CONTZ");
      h2_SCIOffSh[i]->Draw("COLZ");
      tb1->Draw();
      outName = "OnOffShell/"+DirName + "_OffShell_" + VarName + "_" + ChannelName[i] + ".png";
      myCan->SaveAs(outName);
      
      //Overlap 2D histo
      h2_SCIOffSh[i]->Draw("COLZ");
      h2_SCIOnSh[i]->Draw("CONT1SAME");
      tb2->Draw();
      outName = "OnOffShell/"+DirName + "_OnOffShell_" + VarName + "_" + ChannelName[i] + ".png";
      myCan->SaveAs(outName);
    }else if(VarName == "mll" || VarName == "mth"){
      h1_OnSh1[i] ->SetTitle("");
      h1_OnSh2[i] ->SetTitle("");
      h1_OffSh1[i]->SetTitle("");
      h1_OffSh2[i]->SetTitle("");

      if(VarName == "mll")
	xlabel = "m_{ll} [GeV/c^{2}]";
      if(VarName == "mth")
	xlabel = "m_{H}^{T} [GeV/c^{2}]";

      sprintf(tmpName,"Events / %.1f GeV/c^{2}",h1_OnSh1[i]->GetBinWidth(1));
      h1_OnSh1[i]->GetXaxis()->SetTitle(xlabel);
      h1_OnSh1[i]->GetYaxis()->SetTitle(tmpName);
      h1_OnSh1[i]->GetYaxis()->SetTitleOffset(1.4);
      h1_OnSh1[i]->GetXaxis()->SetTitleOffset(1.2);
      h1_OnSh1[i]->SetLineColor(kRed);
      h1_OnSh1[i]->SetLineWidth(2);
      if(DirName == "SigInt")
	h1_OnSh1[i]->SetMinimum(1.2*h1_OffSh1[i]->GetMinimum());
    
      h1_OffSh1[i]->GetXaxis()->SetTitle(xlabel);
      h1_OffSh1[i]->GetYaxis()->SetTitle(tmpName);
      h1_OffSh1[i]->GetYaxis()->SetTitleOffset(1.4);
      h1_OffSh1[i]->GetXaxis()->SetTitleOffset(1.2);
      h1_OffSh1[i]->SetLineColor(kBlue);
      h1_OffSh1[i]->SetLineWidth(2);
    
      TLegend* Lgd0 = new TLegend(.63,.75,.9,.9);
      Lgd0->SetBorderSize(0);
      Lgd0->SetFillStyle(0);
      Lgd0->SetTextSize(0.03);

      Lgd0->AddEntry(h1_OnSh1[i],"mWW < 160","l");
      Lgd0->AddEntry(h1_OffSh1[i],"mWW > 160","l");
      
      if(h1_OnSh1[i]->GetMaximum() > h1_OffSh1[i]->GetMaximum())
      {
      h1_OnSh1[i] ->Draw("HIST");
      h1_OffSh1[i]->Draw("HISTSAME");
      }else{
      h1_OffSh1[i]->Draw("HIST");
      h1_OnSh1[i] ->Draw("HISTSAME");
      }
      if(VarName == "mll")
	txtbox1->Draw();
      if(VarName == "mth")
	txtbox3->Draw();
      
      Lgd0->Draw();
      //TString outName = "OnOffShell/"+DirName + "_" + VarName + "_" + ChannelName[i] + "_mthLt130.png";
      TString outName = "OnOffShell/"+DirName + "_" + VarName + "_" + ChannelName[i] + "_mthLt120.png";
      if(VarName == "mth")
	outName = "OnOffShell/"+DirName + "_" + VarName + "_" + ChannelName[i] + "_mllLt83.png";
      myCan->SaveAs(outName);

      sprintf(tmpName,"Events / %.1f GeV/c^{2}",h1_OnSh1[i]->GetBinWidth(1));
      h1_OnSh2[i]->GetXaxis()->SetTitle(xlabel);
      h1_OnSh2[i]->GetYaxis()->SetTitle(tmpName);
      h1_OnSh2[i]->GetYaxis()->SetTitleOffset(1.4);
      h1_OnSh2[i]->GetXaxis()->SetTitleOffset(1.2);
      h1_OnSh2[i]->SetLineColor(kRed);
      h1_OnSh2[i]->SetLineWidth(2);
      if(DirName == "SigInt")
	h1_OnSh2[i]->SetMinimum(1.2*h1_OffSh2[i]->GetMinimum());
    
      h1_OffSh2[i]->GetXaxis()->SetTitle(xlabel);
      h1_OffSh2[i]->GetYaxis()->SetTitle(tmpName);
      h1_OffSh2[i]->GetYaxis()->SetTitleOffset(1.4);
      h1_OffSh2[i]->GetXaxis()->SetTitleOffset(1.2);
      h1_OffSh2[i]->SetLineColor(kBlue);
      h1_OffSh2[i]->SetLineWidth(2);
    
      TLegend* Lgd1 = new TLegend(.63,.75,.9,.9);
      Lgd1->SetBorderSize(0);
      Lgd1->SetFillStyle(0);
      Lgd1->SetTextSize(0.03);

      Lgd1->AddEntry(h1_OnSh2[i],"mWW < 160","l");
      Lgd1->AddEntry(h1_OffSh2[i],"mWW > 160","l");
      
      if(h1_OnSh2[i]->GetMaximum() > h1_OffSh2[i]->GetMaximum())
      {
      h1_OnSh2[i] ->Draw("HIST");
      h1_OffSh2[i]->Draw("HISTSAME");
      }else{
      h1_OffSh2[i]->Draw("HIST");
      h1_OnSh2[i] ->Draw("HISTSAME");
      }
      if(VarName == "mll")
	txtbox2->Draw();
      if(VarName == "mth")
	txtbox4->Draw();
      
      Lgd1->Draw();
      //outName = "OnOffShell/"+DirName + "_" + VarName + "_" + ChannelName[i] + "_mthGt130.png";
      outName = "OnOffShell/"+DirName + "_" + VarName + "_" + ChannelName[i] + "_mthGt120.png";
      if(VarName == "mth")
	outName = "OnOffShell/"+DirName + "_" + VarName + "_" + ChannelName[i] + "_mllGt83.png";
      myCan->SaveAs(outName);
    }
    delete myCan;
  }
}
