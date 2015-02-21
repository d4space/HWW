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

void metStudy( TString sampleName, TString CutName){

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
  cout<<"File used: "<<fileName<<endl;
  TFile *fname  = new TFile(fileName);

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  TH1D *h1_genMet[4];
  TH1D *h1_pupMet[4];
  TH1D *h1_pfMet[4];
  TH1D *h1_trkMet[4];
  TH2D* h2_pfGenResol[4];
  TH2D* h2_pupGenResol[4];
  TH2D* h2_trkGenResol[4];
  
  TProfile* pr_pfGenResol[4];
  TProfile* pr_pupGenResol[4];
  TProfile* pr_trkGenResol[4];

  //=====================================
  //Looping for each Channel
  //=====================================

  for (int i(0);i<4;i++) {
    TCanvas *myCan = new TCanvas("myCan","Can",800,800);
    
      sprintf(histNameOrg,"h1_genMet_%d",i);
      h1_genMet[i]= (TH1D*)fname->Get(histNameOrg)->Clone(histNameOrg); h1_genMet[i]->Sumw2();
      sprintf(histNameOrg,"h1_pfMet_%d",i);
      h1_pfMet[i]= (TH1D*)fname->Get(histNameOrg)->Clone(histNameOrg); h1_pfMet[i]->Sumw2();
      sprintf(histNameOrg,"h1_pupMet_%d",i);
      h1_pupMet[i]= (TH1D*)fname->Get(histNameOrg)->Clone(histNameOrg); h1_pupMet[i]->Sumw2();
      sprintf(histNameOrg,"h1_trkMet_%d",i);
      h1_trkMet[i]= (TH1D*)fname->Get(histNameOrg)->Clone(histNameOrg); h1_trkMet[i]->Sumw2();
   
      char fileName[30];
      char Ytitle[30];
      sprintf(fileName,sampleName+"_Met_%djet",i);
      sprintf(Ytitle,"Events / %.1f",h1_genMet[i]->GetBinWidth(1));
      CPlot* Plot_MET = new CPlot(fileName,sampleName,"MET[GeV]",Ytitle);
      Plot_MET->setOutDir(OutDir);
      Plot_MET->AddHist1D(h1_genMet[i],"HIST",kBlack);
      Plot_MET->AddHist1D(h1_pfMet[i],"HIST",kRed);
      Plot_MET->AddHist1D(h1_pupMet[i],"HIST",kBlue);
      Plot_MET->AddHist1D(h1_trkMet[i],"HIST",kGreen);
      //Plot_MET->AddTextBox(LgdTitle[i],0.7,0.92,0.9,0.97,0,kBlack,-1);
      Plot_MET->SetLegend(0.65,0.7,0.92,0.85);
      Plot_MET->GetLegend()->AddEntry(h1_genMet[i],"gen","l");
      Plot_MET->GetLegend()->AddEntry(h1_pfMet[i],"pf","l");
      Plot_MET->GetLegend()->AddEntry(h1_pupMet[i],"pup","l");
      Plot_MET->GetLegend()->AddEntry(h1_trkMet[i],"trk","l");
      if(sampleName == "DYJetsToLL")Plot_MET->SetLogy();
      
      Plot_MET->Draw(myCan,kTRUE,"png");


      // 2D plot party===================
      //
      sprintf(histNameOrg,"h2_pup_gen_MetResol_%d",i);
      sprintf(histName,"h2_pupGenResol_%d",i);
      h2_pupGenResol[i] = (TH2D*)fname->Get(histNameOrg)->Clone(histName);
      h2_pupGenResol[i] -> SetMarkerSize(0.4);

      sprintf(histNameOrg,"h2_pf_gen_MetResol_%d",i);
      sprintf(histName,"h2_pfGenResol_%d",i);
      h2_pfGenResol[i] = (TH2D*)fname->Get(histNameOrg)->Clone(histName);
      h2_pfGenResol[i] -> SetMarkerSize(0.4);

      sprintf(histNameOrg,"h2_trk_gen_MetResol_%d",i);
      sprintf(histName,"h2_trkGenResol_%d",i);
      h2_trkGenResol[i] = (TH2D*)fname->Get(histNameOrg)->Clone(histName);
      h2_trkGenResol[i] -> SetMarkerSize(0.4);

      myCan->Clear();
      h2_pupGenResol[i]->GetYaxis()->SetTitle("(met-gen)/gen");
      h2_pupGenResol[i]->Draw();
      sprintf(tmpName,OutDir+"/"+sampleName+"_metGenRes2d_%dj.png",i);
      //myCan->SaveAs(tmpName);
      
      // Making profile ======================
      sprintf(histName,"pr_pupGenResol_%d",i);
      //                                           name , first, last , option
      //pr_pupGenResol[i] = h2_pupGenResol[i]->ProfileX(histName);
      pr_pupGenResol[i] = h2_pupGenResol[i]->ProfileX(histName,1,-1,"s");

      sprintf(histName,"pr_trkGenResol_%d",i);
      pr_trkGenResol[i] = h2_trkGenResol[i]->ProfileX(histName,1,-1,"s");
      sprintf(histName,"pr_pfGenResol_%d",i);
      pr_pfGenResol[i] = h2_pfGenResol[i]->ProfileX(histName,1,-1,"s");

      //pr_trkGenResol[i]->GetXaxis()->SetTitle("genMet");
      //pr_trkGenResol[i]->GetYaxis()->SetTitle("trkmet");
      //pr_trkGenResol[i]->SetTitle("");

      //Leg_met->Draw();
      //sprintf(tmpName,OutDir+"/"+sampleName+"_trkGenResol_%djet.png",i);
      //myCan->SaveAs(tmpName);

      //Each Profiles and 2D

      //pr_pfGenResol[i]->GetXaxis()->SetTitle("genMet");
      //pr_pfGenResol[i]->GetYaxis()->SetTitle("pfmet");
      //pr_pfGenResol[i]->SetTitle("");

      //Leg_met->SetHeader(LgdTitle[i]+" "+sampleName);

      //pr_pfGenResol[i]->Draw();
      //h2_pfGenResol[i]->Draw("same");
      //pr_pfGenResol[i]->Draw("E1same");
      //Leg_met->Draw();
      //sprintf(tmpName,OutDir+"/"+sampleName+"_pfGenResol_%djet.png",i);
      //myCan->SaveAs(tmpName);
      //
      //
      //
      pr_pupGenResol[i]->GetXaxis()->SetTitle("genMet[GeV]");
      pr_pupGenResol[i]->GetYaxis()->SetTitle("(met-gen)/gen");
      pr_pupGenResol[i]->SetTitle("");
      pr_pupGenResol[i]->SetLineColor(kBlue);
      pr_pupGenResol[i]->SetMarkerColor(kBlue);
      pr_trkGenResol[i]->SetLineColor(kGreen);
      pr_trkGenResol[i]->SetMarkerColor(kGreen);
      pr_pfGenResol[i]->SetLineColor(kRed);
      pr_pfGenResol[i]->SetMarkerColor(kRed);

      pr_pupGenResol[i]->Draw("p");
      //pr_pupGenResol[i]->Draw("E1");
      pr_trkGenResol[i]->Draw("psame");
      pr_pfGenResol[i]->Draw("psame");

      TLegend *Leg_met =new TLegend(0.6,0.7,0.9,0.9); Leg_met->SetFillColor(0); Leg_met->SetBorderSize(0);
      Leg_met->SetHeader(sampleName);
      Leg_met->AddEntry(pr_pupGenResol[i],"pupMet","PL");
      Leg_met->AddEntry(pr_trkGenResol[i],"trkMet","PL");
      Leg_met->AddEntry(pr_pfGenResol[i],"pfMet","PL");
      myCan->SetLogy(0);
      Leg_met->Draw();
      TLine myLine(0,0,120,0);
      myLine.Draw();

      sprintf(tmpName,OutDir+"/"+sampleName+"_metGenResol_%djet.png",i);
      myCan->SaveAs(tmpName);

      // RMS Draw
      TH1D pupRMS("pupRMS","RMS",50,0,51);
      TH1D trkRMS("trkRMS","RMS",50,0,51);
      TH1D pfRMS ("pfRMS", "RMS" ,50,0,51);
      for ( int j(0);j<50; j++)
      {
	pupRMS.SetBinContent(j,pr_pupGenResol[i]->GetBinError(j));
	trkRMS.SetBinContent(j,pr_trkGenResol[i]->GetBinError(j));
	pfRMS.SetBinContent(j,pr_pfGenResol[i]->GetBinError(j));
      }
      pupRMS.GetXaxis()->SetTitle("genMet[GeV]");
      pupRMS.GetYaxis()->SetTitle("Resolution");
      pupRMS.SetLineColor(kBlue);
      trkRMS.SetLineColor(kGreen);
      pfRMS.SetLineColor(kRed);
      pupRMS.Draw();
      trkRMS.Draw("same");
      pfRMS.Draw("same");

      TLegend *Leg_RMS =new TLegend(0.6,0.7,0.9,0.9);
      Leg_RMS->SetFillColor(0);
      Leg_RMS->SetBorderSize(0);
      Leg_RMS->SetHeader(sampleName);
      Leg_RMS->AddEntry(&pupRMS,"pupMet","L");
      Leg_RMS->AddEntry(&trkRMS,"trkMet","L");
      Leg_RMS->AddEntry(& pfRMS,"pfMet" ,"L");
      Leg_RMS->Draw();
      sprintf(tmpName,OutDir+"/"+sampleName+"_metGenRMS_%djet.png",i);
      myCan->SaveAs(tmpName);

      //h2_pupGenResol[i]->SetMaximum(10);
      //h2_pupGenResol[i]->SetMinimum(-10);
      //h2_trkGenResol[i]->Draw("same");
      //h2_pfGenResol[i]->Draw("same");
  }
}
