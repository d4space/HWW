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

void OnShOffSh(TString CutName, TString VarName, TString vSigBkgInt){

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
  TH2D *h2_OnSh[4]; // Basically SCI
  TH2D *h2_OffSh[4]; // Basically SCI
  TH2D *h2_SigOnSh[4];
  TH2D *h2_SigOffSh[4];
  TH2D *h2_CotOnSh[4];
  TH2D *h2_CotOffSh[4];

  //Continuum
  TH1D *h1_CotOnSh1[4];
  TH1D *h1_CotOnSh2[4];
  TH1D *h1_CotOffSh1[4];
  TH1D *h1_CotOffSh2[4];

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
      sprintf(histNameOrg,"h2_mthmll_OnSh_%d",i);// OnShell-----------

      sprintf(histName,"h2_OnSh_%d",i);
      h2_OnSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName);  h2_OnSh[i]->Sumw2();

      sprintf(histName,"h2_SigOnSh_%d",i);
      h2_SigOnSh[i]= (TH2D*)fSig->Get(histNameOrg)->Clone(histName);  h2_SigOnSh[i]->Sumw2();
      
      sprintf(histName,"h2_CotOnSh_%d",i);
      h2_CotOnSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName);  h2_CotOnSh[i]->Sumw2();
      
      sprintf(histNameOrg,"h2_mthmll_OffSh_%d",i); // OffShell----------

      sprintf(histName,"h2_OffSh_%d",i);
      h2_OffSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName); h2_OffSh[i]->Sumw2();

      sprintf(histName,"h2_SigOffSh_%d",i);
      h2_SigOffSh[i]= (TH2D*)fSig->Get(histNameOrg)->Clone(histName); h2_SigOffSh[i]->Sumw2();
      
      sprintf(histName,"h2_CotOffSh_%d",i);
      h2_CotOffSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName); h2_CotOffSh[i]->Sumw2();
    }else if(VarName == "mthptll"){//HERE
      sprintf(histNameOrg,"h2_mthptll_OnSh_%d",i);

      sprintf(histName,"h2_OnSh_%d",i);
      h2_OnSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName);  h2_OnSh[i]->Sumw2();
      sprintf(histName,"h2_SigOnSh_%d",i);
      h2_SigOnSh[i]= (TH2D*)fSig->Get(histNameOrg)->Clone(histName);  h2_SigOnSh[i]->Sumw2();
      sprintf(histName,"h2_CotOnSh_%d",i);
      h2_CotOnSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName);  h2_CotOnSh[i]->Sumw2();
      sprintf(histNameOrg,"h2_mthptll_OffSh_%d",i);
      sprintf(histName,"h2_OffSh_%d",i);
      h2_OffSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName); h2_OffSh[i]->Sumw2();
      sprintf(histName,"h2_SigOffSh_%d",i);
      h2_SigOffSh[i]= (TH2D*)fSig->Get(histNameOrg)->Clone(histName); h2_SigOffSh[i]->Sumw2();
      sprintf(histName,"h2_CotOffSh_%d",i);
      h2_CotOffSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName); h2_CotOffSh[i]->Sumw2();
    }else if(VarName == "mllptll"){//HERE
      sprintf(histNameOrg,"h2_mllptll_OnSh_%d",i);
      sprintf(histName,"h2_OnSh_%d",i);
      h2_OnSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName);  h2_OnSh[i]->Sumw2();
      sprintf(histName,"h2_SigOnSh_%d",i);
      h2_SigOnSh[i]= (TH2D*)fSig->Get(histNameOrg)->Clone(histName);  h2_SigOnSh[i]->Sumw2();
      sprintf(histName,"h2_CotOnSh_%d",i);
      h2_CotOnSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName);  h2_CotOnSh[i]->Sumw2();
      sprintf(histNameOrg,"h2_mllptll_OffSh_%d",i);
      sprintf(histName,"h2_OffSh_%d",i);
      h2_OffSh[i]= (TH2D*)fSCI->Get(histNameOrg)->Clone(histName); h2_OffSh[i]->Sumw2();
      sprintf(histName,"h2_SigOffSh_%d",i);
      h2_SigOffSh[i]= (TH2D*)fSig->Get(histNameOrg)->Clone(histName); h2_SigOffSh[i]->Sumw2();
      sprintf(histName,"h2_CotOffSh_%d",i);
      h2_CotOffSh[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName); h2_CotOffSh[i]->Sumw2();
    }else if(VarName == "mll"){
      //sprintf(histNameOrg,"h1_mll_OnSh_mth_l130_%d",i);
      sprintf(histNameOrg,"h1_mll_OnSh_mth_l120_%d",i);
      sprintf(histName,"h1_OnSh1_%d",i);
      h1_OnSh1[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OnSh1[i]->Sumw2();
      
      sprintf(histName,"h1_CotOnSh1_%d",i);
      h1_CotOnSh1[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_CotOnSh1[i]->Sumw2();
      
      //sprintf(histNameOrg,"h1_mll_OnSh_mth_g130_%d",i);
      sprintf(histNameOrg,"h1_mll_OnSh_mth_g120_%d",i);
      sprintf(histName,"h1_OnSh2_%d",i);
      h1_OnSh2[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OnSh2[i]->Sumw2();
      
      sprintf(histName,"h1_CotOnSh2_%d",i);
      h1_CotOnSh2[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_CotOnSh2[i]->Sumw2();
      
      //sprintf(histNameOrg,"h1_mll_OffSh_mth_l130_%d",i);
      sprintf(histNameOrg,"h1_mll_OffSh_mth_l120_%d",i);
      sprintf(histName,"h1_OffSh1_%d",i);
      h1_OffSh1[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OffSh1[i]->Sumw2();
      
      sprintf(histName,"h1_CotOffSh1_%d",i);
      h1_CotOffSh1[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_CotOffSh1[i]->Sumw2();
      
      //sprintf(histNameOrg,"h1_mll_OffSh_mth_g130_%d",i);
      sprintf(histNameOrg,"h1_mll_OffSh_mth_g120_%d",i);
      sprintf(histName,"h1_OffSh2_%d",i);
      h1_OffSh2[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OffSh2[i]->Sumw2();
      
      sprintf(histName,"h1_CotOffSh2_%d",i);
      h1_CotOffSh2[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_CotOffSh2[i]->Sumw2();
    }else if(VarName == "mth"){
      sprintf(histNameOrg,"h1_mth_OnSh_mll_l83_%d",i);
      sprintf(histName,"h1_OnSh1_%d",i);
      h1_OnSh1[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OnSh1[i]->Sumw2();
      
      sprintf(histName,"h1_CotOnSh1_%d",i);
      h1_CotOnSh1[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_CotOnSh1[i]->Sumw2();
      
      sprintf(histNameOrg,"h1_mth_OnSh_mll_g83_%d",i);
      sprintf(histName,"h1_OnSh2_%d",i);
      h1_OnSh2[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OnSh2[i]->Sumw2();
      
      sprintf(histName,"h1_CotOnSh2_%d",i);
      h1_CotOnSh2[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_CotOnSh2[i]->Sumw2();
      
      sprintf(histNameOrg,"h1_mth_OffSh_mll_l83_%d",i);
      sprintf(histName,"h1_OffSh1_%d",i);
      h1_OffSh1[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OffSh1[i]->Sumw2();
      
      sprintf(histName,"h1_CotOffSh1_%d",i);
      h1_CotOffSh1[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_CotOffSh1[i]->Sumw2();
      
      sprintf(histNameOrg,"h1_mth_OffSh_mll_l83_%d",i);
      sprintf(histName,"h1_OffSh2_%d",i);
      h1_OffSh2[i]= (TH1D*)fSCI->Get(histNameOrg)->Clone(histName); h1_OffSh2[i]->Sumw2();
      
      sprintf(histName,"h1_CotOffSh2_%d",i);
      h1_CotOffSh2[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h1_CotOffSh2[i]->Sumw2();
    }
    
    if(vSigBkgInt == "SigInt"){
      if(VarName == "mll" || VarName == "mth"){
	h1_OnSh1[i] ->Add(h1_CotOnSh1[i],-1);
	h1_OnSh2[i] ->Add(h1_CotOnSh2[i],-1);
	h1_OffSh1[i]->Add(h1_CotOffSh1[i],-1);
	h1_OffSh2[i]->Add(h1_CotOffSh2[i],-1);
      }else if(VarName == "mthmll" || VarName == "mthptll" || VarName == "mllptll"){
	h2_OnSh[i]  ->Add(h2_CotOnSh[i],-1);
	h2_OffSh[i] ->Add(h2_CotOffSh[i],-1);
      }
    }
    else if(vSigBkgInt == "Int"){
      if(VarName == "mll" || VarName == "mth"){
	h1_OnSh1[i] ->Add(h1_CotOnSh1[i],-1);
	h1_OnSh2[i] ->Add(h1_CotOnSh2[i],-1);
	h1_OffSh1[i]->Add(h1_CotOffSh1[i],-1);
	h1_OffSh2[i]->Add(h1_CotOffSh2[i],-1);
      }else if(VarName == "mthmll" || VarName == "mthptll" || VarName == "mllptll"){
	h2_OnSh[i]  ->Add(h2_CotOnSh[i],-1);
	h2_OffSh[i] ->Add(h2_CotOffSh[i],-1);
	h2_OnSh[i]  ->Add(h2_SigOnSh[i],-1);
	h2_OffSh[i] ->Add(h2_SigOffSh[i],-1);
      }
    }

    TCanvas *myCan = new TCanvas("myCan", "myCan", 900, 800);
    
    gStyle->SetOptStat(0);
    TString dataName = "Hw1 S+C+I 8TeV";
    if(vSigBkgInt == "SigInt")
      dataName = "Hw1 S+I 8TeV";
    if(vSigBkgInt == "Int")
      dataName = "Hw1 Int 8TeV";
    
    TPaveText *tb0 = new TPaveText(.63,.7,.9,.87,"NDC");
    tb0->SetBorderSize(0);
    tb0->SetFillStyle(0);
    tb0->SetTextSize(0.04);
    tb0->AddText(dataName);
    tb0->AddText("CommonCut");
    tb0->AddText(ChannelName[i]+",   mWW < 150");
    
    TPaveText *tb1 = new TPaveText(.55,.7,.9,.87,"NDC");
    tb1->SetBorderSize(0);
    tb1->SetFillStyle(0);
    tb1->SetTextSize(0.04);
    tb1->AddText(dataName);
    tb1->AddText("CommonCut");
    tb1->AddText(ChannelName[i]+",   mWW > 150");
    
    TPaveText *tb2 = new TPaveText(.65,.7,.9,.87,"NDC");
    //tb2->SetBorderSize(0);
    tb2->SetFillColor(kWhite);
    tb2->SetFillStyle(1001);
    tb2->SetTextSize(0.03);
    tb2->AddText(dataName);
    tb2->AddText(ChannelName[i]);
    tb2->AddText("CONT  mWW < 150");
    tb2->AddText("COL   mWW > 150");
    
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
      h2_OnSh[i] ->SetTitle("");
      h2_OffSh[i]->SetTitle("");

      h2_OnSh[i]->GetXaxis()->SetTitle(xlabel);
      h2_OnSh[i]->GetYaxis()->SetTitle(ylabel);
      h2_OnSh[i]->GetYaxis()->SetTitleOffset(1.4);
      h2_OnSh[i]->GetXaxis()->SetTitleOffset(1.2);
      
      //h2_OnSh[i]->Draw("CONTZ");
      h2_OnSh[i]->Draw("COLZ");
      tb0->Draw();
      TString outName = "OnOffShell/"+vSigBkgInt + "_OnShell_" + VarName + "_" + ChannelName[i] + ".png";
      myCan->SaveAs(outName);
    
      h2_OffSh[i]->GetXaxis()->SetTitle(xlabel);
      h2_OffSh[i]->GetYaxis()->SetTitle(ylabel);
      h2_OffSh[i]->GetYaxis()->SetTitleOffset(1.4);
      h2_OffSh[i]->GetXaxis()->SetTitleOffset(1.2);
      
      //h2_OffSh[i]->Draw("CONTZ");
      h2_OffSh[i]->Draw("COLZ");
      tb1->Draw();
      outName = "OnOffShell/"+vSigBkgInt + "_OffShell_" + VarName + "_" + ChannelName[i] + ".png";
      myCan->SaveAs(outName);
      
      //Overlap 2D histo
      h2_OffSh[i]->Draw("COLZ");
      h2_OnSh[i]->Draw("CONT1SAME");
      tb2->Draw();
      outName = "OnOffShell/"+vSigBkgInt + "_OnOffShell_" + VarName + "_" + ChannelName[i] + ".png";
      myCan->SaveAs(outName);

      // Signal
      h2_SigOnSh[i] ->SetTitle("");
      h2_SigOffSh[i]->SetTitle("");

      h2_SigOnSh[i]->GetXaxis()->SetTitle(xlabel);
      h2_SigOnSh[i]->GetYaxis()->SetTitle(ylabel);
      h2_SigOnSh[i]->GetYaxis()->SetTitleOffset(1.4);
      h2_SigOnSh[i]->GetXaxis()->SetTitleOffset(1.2);
      
      //h2_OnSh[i]->Draw("CONTZ");
      h2_SigOnSh[i]->Draw("COLZ");
      tb0->Draw();
      outName = "OnOffShell/Sig_OnShell_" + VarName + "_" + ChannelName[i] + ".png";
      myCan->SaveAs(outName);
    
      h2_SigOffSh[i]->GetXaxis()->SetTitle(xlabel);
      h2_SigOffSh[i]->GetYaxis()->SetTitle(ylabel);
      h2_SigOffSh[i]->GetYaxis()->SetTitleOffset(1.4);
      h2_SigOffSh[i]->GetXaxis()->SetTitleOffset(1.2);
      
      //h2_OffSh[i]->Draw("CONTZ");
      h2_SigOffSh[i]->Draw("COLZ");
      tb1->Draw();
      outName = "OnOffShell/Sig_OffShell_" + VarName + "_" + ChannelName[i] + ".png";
      myCan->SaveAs(outName);
      
      //Overlap 2D histo
      h2_SigOffSh[i]->Draw("COLZ");
      h2_SigOnSh[i]->Draw("CONT1SAME");
      tb2->Draw();
      outName = "OnOffShell/Sig_OnOffShell_" + VarName + "_" + ChannelName[i] + ".png";
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
      if(vSigBkgInt == "SigInt")
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

      Lgd0->AddEntry(h1_OnSh1[i],"mWW < 150","l");
      Lgd0->AddEntry(h1_OffSh1[i],"mWW > 150","l");
      
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
      //TString outName = "OnOffShell/"+vSigBkgInt + "_" + VarName + "_" + ChannelName[i] + "_mthLt130.png";
      TString outName = "OnOffShell/"+vSigBkgInt + "_" + VarName + "_" + ChannelName[i] + "_mthLt120.png";
      if(VarName == "mth")
	outName = "OnOffShell/"+vSigBkgInt + "_" + VarName + "_" + ChannelName[i] + "_mllLt83.png";
      myCan->SaveAs(outName);

      sprintf(tmpName,"Events / %.1f GeV/c^{2}",h1_OnSh1[i]->GetBinWidth(1));
      h1_OnSh2[i]->GetXaxis()->SetTitle(xlabel);
      h1_OnSh2[i]->GetYaxis()->SetTitle(tmpName);
      h1_OnSh2[i]->GetYaxis()->SetTitleOffset(1.4);
      h1_OnSh2[i]->GetXaxis()->SetTitleOffset(1.2);
      h1_OnSh2[i]->SetLineColor(kRed);
      h1_OnSh2[i]->SetLineWidth(2);
      if(vSigBkgInt == "SigInt")
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

      Lgd1->AddEntry(h1_OnSh2[i],"mWW < 150","l");
      Lgd1->AddEntry(h1_OffSh2[i],"mWW > 150","l");
      
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
      //outName = "OnOffShell/"+vSigBkgInt + "_" + VarName + "_" + ChannelName[i] + "_mthGt130.png";
      outName = "OnOffShell/"+vSigBkgInt + "_" + VarName + "_" + ChannelName[i] + "_mthGt120.png";
      if(VarName == "mth")
	outName = "OnOffShell/"+vSigBkgInt + "_" + VarName + "_" + ChannelName[i] + "_mllGt83.png";
      myCan->SaveAs(outName);
    }
    delete myCan;
  }
}
