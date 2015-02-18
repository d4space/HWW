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

#include "../../../Utils/const.h"
#include "../../../Utils/CPlot.hh"
#include "../../../Utils/MitStyleRemix.hh"

void metStudy(TString CutName, TString VarName, TString sampleName){

  TString OutDir = "CtrPlots_metStudy";
  gSystem->mkdir(OutDir);

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
  
  TString fileName  = sampleName+"/"+sampleName+"_"+CutName+".root";
  TFile *fname  = new TFile(fileName);

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  TH1D *h1_met[4];
  TH2D* h2_met[4];
  
  TProfile* hp_met[4];

  //=====================================
  //Looping for each Channel
  //=====================================

  for (int i(0);i<4;i++) {
    TCanvas *myCan = new TCanvas("myCan","Can",800,800);
    
    if(VarName=="pupMet" || VarName=="pfMet" || VarName=="genMet")
    {
      sprintf(histNameOrg,"h1_"+VarName+"_%d",i);
      sprintf(histName,"h1_met_%d",i);
      h1_met[i]= (TH1D*)fname->Get(histNameOrg)->Clone(histName); h1_met[i]->Sumw2();
    
      sprintf(tmpName,"Events / %.1f",h1_met[i]->GetBinWidth(1));
      sprintf(histName,sampleName+"_"+VarName+"_%djet",i);
      CPlot* Plot_MET = new CPlot(histName,"",VarName,tmpName);
      Plot_MET->setOutDir(OutDir);
      Plot_MET->AddHist1D(h1_met[i],"HIST",kBlack);
      Plot_MET->AddTextBox(LgdTitle[i],0.7,0.92,0.9,0.97,0,kBlack,-1);
      Plot_MET->SetLegend(0.65,0.8,0.92,0.85);
      Plot_MET->GetLegend()->AddEntry(h1_met[i],sampleName,"l");
      Plot_MET->Draw(myCan,kTRUE,"png");
    }else if(VarName=="genMet_pupMet" || VarName=="genMet_pfMet"){
      sprintf(histNameOrg,"h2_"+VarName+"_%d",i);
      sprintf(histName,"h2_met_%d",i);
      h2_met[i] = (TH2D*)fname->Get(histNameOrg)->Clone(histName);
      
      //Profiles
      h2_met[i] -> SetMarkerSize(0.4);
      sprintf(histName,"hp_met_%d",i);
      hp_met[i] = new TProfile(histName,"met ProfileX",8,0,80,0,120);
      hp_met[i] = h2_met[i]->ProfileX("met_pfx",0,120,"s");

      hp_met[i]->GetXaxis()->SetTitle("genMet");
      if(VarName=="genMet_pupMet")
	hp_met[i]->GetYaxis()->SetTitle("pupmet");
      if(VarName=="genMet_pfMet")
	hp_met[i]->GetYaxis()->SetTitle("pfmet");
      hp_met[i]->SetTitle("");
      hp_met[i]->SetLineColor(kRed);
      hp_met[i]->SetMarkerColor(kRed);

      TLegend *Leg_met =new TLegend(0.2,0.8,0.5,0.9); Leg_met->SetFillColor(0); Leg_met->SetBorderSize(0);
      Leg_met->SetHeader(LgdTitle[i]+" "+sampleName);
      Leg_met->AddEntry(hp_met[i],"ProfileX()","PL");

      hp_met[i]->Draw();
      h2_met[i]->Draw("same");
      hp_met[i]->Draw("E1same");
      Leg_met->Draw();
      sprintf(tmpName,OutDir+"/"+sampleName+"_"+VarName+"_%djet.png",i);
      myCan->SaveAs(tmpName);
    }
  }
}
