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

void pupmet(TString CutName, TString VarName, TString DirName){

  TString ChannelName[4];
  ChannelName[0] = "of0j";
  ChannelName[1] = "of1j";
  ChannelName[2] = "of2j";
  ChannelName[3] = "Incl";

  TString LgdTitle[4];
  LgdTitle[0] = "njet = 0, e#mu";
  LgdTitle[1] = "njet = 1, e#mu";
  LgdTitle[2] = "njet #geq 2, e#mu";
  LgdTitle[3] = "Incl.jet, e#mu";
  
  TFile *fname  = new TFile("WJetsToLNuMad/WJetsToLNuMad_"+CutName+".root");

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  TH1D *h1_pupmet[4];

  //=====================================
  //Looping for each Channel
  //=====================================
  for (int i(0);i<4;i++) {
    TCanvas *myCan = new TCanvas("myCan","Can",800,800);
    
    sprintf(histNameOrg,"h1_pupmet_%d",i);
    h1_pupmet[i]= (TH1D*)fname->Get(histNameOrg)->Clone(histName); h1_pupmet[i]->Sumw2();
    
    h1_pupmet[i]->SetLineColor(kBlack);
    h1_pupmet[i]->SetLineWidth(2);
    
    sprintf(tmpName,"Events / %d",h1_pupmet[i]->GetBinWidth(1));
    h1_pupmet[i]->GetYaxis()->SetTitle(tmpName);
    h1_pupmet[i]->GetYaxis()->SetTitleOffset(1.2);
    h1_pupmet[i]->GetYaxis()->SetTitleSize(0.04);
    h1_pupmet[i]->GetYaxis()->SetLabelSize(0.04);
    h1_pupmet[i]->GetYaxis()->SetNdivisions(505);
    h1_pupmet[i]->GetXaxis()->SetTitle("pupmet");
    h1_pupmet[i]->GetXaxis()->SetTitleSize(0.04);
    
    h1_pupmet[i]->Draw("HIST");
    
    TLegend* Lgd = new TLegend(.7,.8,.9,.9);
    Lgd->SetHeader(LgdTitle[i]);
    Lgd->AddEntry(h1_pupmet[i],"WJetsToLNuMad","l");
    Lgd->SetBorderSize(0);
    Lgd->SetFillStyle(0);
    //Lgd->SetTextSize(0.05);
    Lgd->Draw();
    TString outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + ".png";
    myCan->SaveAs(outFile);

    delete myCan;
  }
}
