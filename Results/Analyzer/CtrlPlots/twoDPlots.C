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

void twoDPlots(TString CutName, TString VarName, TString DirName){

  TString ChannelName[4];
  ChannelName[0] = "sf0j";
  ChannelName[1] = "of0j";
  ChannelName[2] = "sf1j";
  ChannelName[3] = "of1j";

  TFile *fww      = new TFile("WW/WW_"+CutName+".root");
  TFile *fSig     = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_"+CutName+".root");
  TFile *fSig_Hw25= new TFile("gg2vvHw25Sig8TeV/gg2vvHw25Sig8TeV_"+CutName+".root");
  TFile *fSigBkgr = new TFile("gg2vvHw1Int8TeV/gg2vvHw1Int8TeV_"+CutName+".root");
  TFile *fCot     = new TFile("gg2vvHw25Cot8TeV/gg2vvHw25Cot8TeV_"+CutName+".root");

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  //2D histograms
  TH2D *h2_wjets[4];
  TH2D *h2_ww[4];
  TH2D *h2_top[4];
  TH2D *h2_dyll[4]; 
  TH2D *h2_dytt[4];
  TH2D *h2_vv[4];
  TH2D *h2_vvv[4];
  TH2D *h2_sig[4];
  TH2D *h2_sig_bkgr[4];
  TH2D *h2_cot[4];
  TH2D *h2_bkgr[4];
  TH2D *h2_sig_Hw25[4];

  //=====================================
  //Looping for each Channel
  //=====================================
  // 0 = "sf0j"
  // 1 = "of0j"
  // 2 = "sf1j"
  // 3 = "of1j"
  for (int i(0);i<4;i++) {
    if(i == 0 || i == 2) continue;
    sprintf(histNameOrg,"h2_mthmll_%d",i);
    if(VarName == "mthdphill")
      sprintf(histNameOrg,"h2_mthdphill_%d",i);
    if(VarName == "mlldphill")
      sprintf(histNameOrg,"h2_mlldphill_%d",i);
    sprintf(histName,"h2_ww_%d",i);
    h2_ww[i]= (TH2D*)fww->Get(histNameOrg)->Clone(histName); h2_ww[i]->Sumw2();
    sprintf(histName,"h2_sig_%d",i);
    h2_sig[i]= (TH2D*)fSig->Get(histNameOrg)->Clone(histName); h2_sig[i]->Sumw2();
    sprintf(histName,"h2_sig_bkgr_%d",i);
    h2_sig_bkgr[i]= (TH2D*)fSigBkgr->Get(histNameOrg)->Clone(histName); h2_sig_bkgr[i]->Sumw2();
    sprintf(histName,"h2_cot_%d",i);
    h2_cot[i]= (TH2D*)fCot->Get(histNameOrg)->Clone(histName); h2_cot[i]->Sumw2();
    sprintf(histName,"h2_sig_Hw25_%d",i);
    h2_sig_Hw25[i]= (TH2D*)fSig_Hw25->Get(histNameOrg)->Clone(histName); h2_sig_Hw25[i]->Sumw2();
    
    TCanvas *myCan = new TCanvas("myCan", "myCan", 900, 800);
    TLegend* Lgd1 = new TLegend(.7,.75,.9,.9);
    TLegend* Lgd2 = new TLegend(.7,.75,.9,.9);
    
    h2_sig[i]->SetTitle("Hw1Sig8TeV");
    h2_sig_Hw25[i]->SetTitle("Hw25Sig8TeV");
    h2_sig_bkgr[i]->SetTitle("Hw1SigBkgr8TeV");
    h2_cot[i]->SetTitle("Hw1Cot8TeV");
    h2_ww[i]->SetTitle("WW");

    gStyle->SetOptStat(0);

    TPaveText *tb = new TPaveText(.8,.83,.9,.87,"NDC");
    tb->SetBorderSize(0);
    tb->SetFillStyle(0);
    tb->AddText(ChannelName[i]);

    TString xlabel = "m_{H}^{T} [GeV/c^{2}]";
    TString ylabel = "m_{ll} [GeV/c^{2}]";
    if(VarName == "mthdphill" || VarName == "mlldphill")
      ylabel = "#Delta#phi_{ll} [^{0}]";
    if(VarName == "mlldphill")
      xlabel = "m_{ll} [GeV/c^{2}]";
    h2_sig[i]->GetXaxis()->SetTitle(xlabel);
    h2_sig[i]->GetYaxis()->SetTitle(ylabel);
    h2_sig[i]->GetYaxis()->SetTitleOffset(1.4);
    h2_sig[i]->GetXaxis()->SetTitleOffset(1.2);

    h2_sig[i]->Draw("CONT");
    tb->Draw();
    TString outName = DirName + "/sig_" + VarName + "_" + ChannelName[i] + "_" + CutName + ".png";
    myCan->SaveAs(outName);
    
    h2_sig_Hw25[i]->GetXaxis()->SetTitle(xlabel);
    h2_sig_Hw25[i]->GetYaxis()->SetTitle(ylabel);
    h2_sig_Hw25[i]->GetYaxis()->SetTitleOffset(1.4);
    h2_sig_Hw25[i]->GetXaxis()->SetTitleOffset(1.2);

    h2_sig_Hw25[i]->Draw("CONT");
    tb->Draw();
    TString outName = DirName + "/sig_Hw25_" + VarName + "_" + ChannelName[i] + "_" + CutName + ".png";
    myCan->SaveAs(outName);
    
    h2_sig_bkgr[i]->GetXaxis()->SetTitle(xlabel);
    h2_sig_bkgr[i]->GetYaxis()->SetTitle(ylabel);
    h2_sig_bkgr[i]->GetYaxis()->SetTitleOffset(1.4);
    h2_sig_bkgr[i]->GetXaxis()->SetTitleOffset(1.2);

    h2_sig_bkgr[i]->Draw("CONT");
    tb->Draw();
    TString outName = DirName + "/sig_bkgr_" + VarName + "_" + ChannelName[i] + "_" + CutName + ".png";
    myCan->SaveAs(outName);
    
    h2_cot[i]->GetXaxis()->SetTitle(xlabel);
    h2_cot[i]->GetYaxis()->SetTitle(ylabel);
    h2_cot[i]->GetYaxis()->SetTitleOffset(1.4);
    h2_cot[i]->GetXaxis()->SetTitleOffset(1.2);

    h2_cot[i]->Draw("CONT");
    tb->Draw();
    TString outName = DirName + "/cot_" + VarName + "_" + ChannelName[i] + "_" + CutName + ".png";
    myCan->SaveAs(outName);
    
    h2_ww[i]->GetXaxis()->SetTitle(xlabel);
    h2_ww[i]->GetYaxis()->SetTitle(ylabel);
    h2_ww[i]->GetYaxis()->SetTitleOffset(1.4);
    h2_ww[i]->GetXaxis()->SetTitleOffset(1.2);

    h2_ww[i]->Draw("CONT");
    tb->Draw();
    TString outName = DirName + "/WW_" + VarName + "_" + ChannelName[i] + "_" + CutName + ".png";
    myCan->SaveAs(outName);
    
    delete myCan;
  }
}
