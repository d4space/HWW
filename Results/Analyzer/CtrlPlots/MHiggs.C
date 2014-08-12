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

TH1D* makeRatioHist(TH1D* hData, TH1D* hMC, const TString name);

void MHiggs(TString CutName, TString VarName, TString DirName){

  TString ChannelName[4];
  ChannelName[0] = "sf0j";
  ChannelName[1] = "of0j";
  ChannelName[2] = "sf1j";
  ChannelName[3] = "of1j";

  TFile *fh125  = new TFile("H125/H125_"+CutName+".root");
  TFile *fhw1  = new TFile("gg2vvHw1/gg2vvHw1_"+CutName+".root");

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  TH1D *h125[4];
  TH1D *hw1[4];
  TH1D *hdiff[4];
  TH1D *hRatio[4];

  //=====================================
  //Looping for each Channel
  //=====================================
  // 0 = "sf0j"
  // 1 = "of0j"
  // 2 = "sf1j"
  // 3 = "of1j"
  for (int i(0);i<4;i++) {
    TCanvas *myCan = new TCanvas("myCan","Can",800,800);
    myCan->cd();
    myCan->SetLogy();
    myCan->Divide(1,2,0,0);
    myCan->cd(1)->SetPad(0,0.35,0.95,1.0);
    myCan->cd(1)->SetTopMargin(0.1);
    myCan->cd(1)->SetBottomMargin(0.01);
    myCan->cd(1)->SetLeftMargin(0.15);
    myCan->cd(1)->SetRightMargin(0.07);
    myCan->cd(1)->SetTickx(1);
    myCan->cd(1)->SetTicky(1);
    myCan->cd(2)->SetPad(0,0,0.95,0.34);
    myCan->cd(2)->SetTopMargin(0.025);
    myCan->cd(2)->SetBottomMargin(0.3);
    myCan->cd(2)->SetLeftMargin(0.15);
    myCan->cd(2)->SetRightMargin(0.07);
    myCan->cd(2)->SetTickx(1);
    myCan->cd(2)->SetTicky(1);
    gStyle->SetLineWidth(2.);
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0.5);
    //gPad->SetLogx(1);
    //gPad->SetLogy(1);
 
    if(VarName == "MHiggs"){
      sprintf(histNameOrg,"h1_mH_%d",i);
    }else if(VarName == "OnShell"){
      sprintf(histNameOrg,"h1_mH_OnShell_%d",i);
    }else if(VarName == "OffShell"){
      sprintf(histNameOrg,"h1_mH_OffShell_%d",i);
    }
    
    cout<<"Loop: "<<i<<endl;
    sprintf(histName,"h125_%d",i);
    h125[i]= (TH1D*)fh125->Get(histNameOrg)->Clone(histName); h125[i]->Sumw2();
    sprintf(histName,"hw1_%d",i);
    hw1[i]= (TH1D*)fhw1->Get(histNameOrg)->Clone(histName); hw1[i]->Sumw2();

    h125[i]->SetLineColor(kRed);
    h125[i]->SetLineWidth(2);
    
    hw1[i]->SetLineColor(kBlue);
    hw1[i]->SetLineWidth(2);
    
    myCan->cd(1);
    sprintf(tmpName,"Events / %d",h125[i]->GetBinWidth(1));
    h125[i]->GetYaxis()->SetTitle(tmpName);
    h125[i]->GetYaxis()->SetTitleOffset(1.2);
    h125[i]->GetYaxis()->SetTitleSize(0.04);
    h125[i]->GetYaxis()->SetLabelSize(0.04);
    h125[i]->GetYaxis()->SetNdivisions(505);
    h125[i]->GetXaxis()->SetTitle("");
    h125[i]->GetXaxis()->SetLabelSize(0);
    hw1[i]->GetYaxis()->SetTitle(tmpName);
    hw1[i]->GetYaxis()->SetTitleOffset(1.2);
    hw1[i]->GetYaxis()->SetTitleSize(0.04);
    hw1[i]->GetYaxis()->SetLabelSize(0.04);
    hw1[i]->GetYaxis()->SetNdivisions(505);
    hw1[i]->GetXaxis()->SetTitle("");
    hw1[i]->GetXaxis()->SetLabelSize(0);
    //if(VarName == "OffShell")
    //  h125[i]->SetMaximum(1.15*(hw1[i]->GetMaximum()));
    
    //if(VarName == "OffShell")
    if(hw1[i]->GetMaximum() > h125[i]->GetMaximum())
    {
      hw1[i]->Draw("HIST");
      h125[i]->Draw("HIST SAME");
    }else{
      h125[i]->Draw("HIST");
      hw1[i]->Draw("HIST SAME");
    }
    
    //TLegend* Lgd = new TLegend(.7,.65,.95,.85);
    TLegend* Lgd = new TLegend(.6,.65,.95,.85);
    if (i==1)
      Lgd->SetHeader("0-jet e#mu");
    if (i==3)
      Lgd->SetHeader("1-jet e#mu");
    Lgd->AddEntry(h125[i],"m_{H}=125 GeV","l");
    Lgd->AddEntry(hw1[i],"Hw1gg2vvSig","l");
    Lgd->SetBorderSize(0);
    Lgd->SetFillStyle(0);
    Lgd->SetTextSize(0.05);
    Lgd->Draw();

    myCan->cd(2);
    sprintf(histName,"hRatio_%d",i);
    hRatio[i] = makeRatioHist(h125[i],hw1[i],histName);
    hRatio[i]->SetMarkerStyle(kFullCircle);
    hRatio[i]->SetMarkerSize(0.9);
    hRatio[i]->GetYaxis()->SetTitle("H125 / gg2VV");
    hRatio[i]->GetXaxis()->SetTitle("m_{H} [GeV/c^{2}]");
    
    hRatio[i]->Draw("E");
    myCan->Modified();
    myCan->Update();
    TString outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + ".png";
    myCan->SaveAs(outFile);

    myCan->cd(1);
    gPad->SetLogy(1);
    //myCan_1->SetLogy();
    myCan->Update();
    outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + "_Log.png";
    myCan->SaveAs(outFile);
    //myCan->SaveAs(VarName+CutName+tmpName);
    delete myCan;
  }
}

//--------------------------------------------------------------------------------------------------
TH1D *makeRatioHist(TH1D* hData, TH1D* hMC, const TString name)
{
  TH1D *h_ratio;
  
  h_ratio = (TH1D*)hData->Clone("");
  h_ratio->Divide(hMC);
  
  h_ratio->GetYaxis()->SetRangeUser(0,2.5);
  h_ratio->GetYaxis()->SetTitleOffset(0.6);
  h_ratio->GetYaxis()->SetTitleSize(0.08);
  h_ratio->GetYaxis()->SetLabelSize(0.07);
  h_ratio->GetYaxis()->CenterTitle();
  h_ratio->GetXaxis()->SetTitleOffset(1.2);
  h_ratio->GetXaxis()->SetTitleSize(0.08);
  h_ratio->GetXaxis()->SetLabelSize(0.07);
  h_ratio->SetTitle("");
  
  return h_ratio;
}

