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

//#include "../../../Utils/CPlot.hh"
//#include "../../../Utils/MitStyleRemix.hh"

TH1D* makeRatioHist(TH1D* hData, TH1D* hMC, const TString name);

void CutStudy(TString CutName, TString VarName, TString DirName){

  TString OutDir = "CutStudy";
  gSystem->mkdir(OutDir);

  TString ChannelName[4];
  ChannelName[0] = "sf0j";
  ChannelName[1] = "of0j";
  ChannelName[2] = "sf1j";
  ChannelName[3] = "of1j";

  TFile *fwjets = new TFile("WJet/WJet_"+CutName+".root");
  TFile *fww    = new TFile("WW/WW_"+CutName+".root");
  TFile *ftop   = new TFile("Top/Top_"+CutName+".root");
  TFile *fdyll  = new TFile("DYll/DYll_"+CutName+".root");// we're using DYtt(data driven) in OF channel instead for DYll
  TFile *fdytt  = new TFile("DYtt/DYtt_"+CutName+".root");
  TFile *fvv    = new TFile("VV/VV_"+CutName+".root");
  TFile *fvvv   = new TFile("VVV/VVV_"+CutName+".root");
  TFile *fh125  = new TFile("H125/H125_"+CutName+".root");
  TFile *fhw1  = new TFile("gg2vvHw1/gg2vvHw1_"+CutName+".root");

  char histName[30];
  char histNameOrg[30];

  TH1D *h_eff[4];
  TH1D *h_total[4];
  TH1D *h_tmp[4];
  TH1D *h_wjets[4];
  TH1D *h_ww[4];
  TH1D *h_top[4];
  TH1D *h_dyll[4]; 
  TH1D *h_dytt[4];
  TH1D *hdy[4];
  TH1D *h_vv[4];
  TH1D *h_vvv[4];
  TH1D *h_h125[4];
  TH1D *h_hw1[4];
  TH2D *h2_mllptll[4];

  //=====================================
  //Looping for each Channel
  //=====================================
  // 0 = "sf0j"
  // 1 = "of0j"
  // 2 = "sf1j"
  // 3 = "of1j"
  for (int i(0);i<4;i++) {
    if(i==0 || i==2) continue;
    TCanvas *myCan = new TCanvas("myCan", "myCan", 900, 800);
    //TCanvas *myCan = new TCanvas("myCan","Can",800,800);
    //myCan->cd();
    //myCan->SetLogy();
    //myCan->Divide(1,2,0,0);
    //myCan->cd(1)->SetPad(0,0.35,0.95,1.0);
    //myCan->cd(1)->SetTopMargin(0.1);
    //myCan->cd(1)->SetBottomMargin(0.01);
    //myCan->cd(1)->SetLeftMargin(0.15);
    //myCan->cd(1)->SetRightMargin(0.07);
    //myCan->cd(1)->SetTickx(1);
    //myCan->cd(1)->SetTicky(1);
    //myCan->cd(2)->SetPad(0,0,0.95,0.34);
    //myCan->cd(2)->SetTopMargin(0.025);
    //myCan->cd(2)->SetBottomMargin(0.3);
    //myCan->cd(2)->SetLeftMargin(0.15);
    //myCan->cd(2)->SetRightMargin(0.07);
    //myCan->cd(2)->SetTickx(1);
    //myCan->cd(2)->SetTicky(1);
    //gStyle->SetLineWidth(2.);
    //gStyle->SetOptStat(0);
    //gStyle->SetErrorX(0.5);
    
    //TLegend* Lgd = new TLegend(.62,.65,.9,.85);

    sprintf(histNameOrg,"h1_mpmet_FOM_%d",i);
    
    sprintf(histName,"h_wjets_%d",i);
    h_wjets[i]= (TH1D*)fwjets->Get(histNameOrg)->Clone(histName); h_wjets[i]->Sumw2();
    sprintf(histName,"h_ww_%d",i);
    h_ww[i]= (TH1D*)fww->Get(histNameOrg)->Clone(histName); h_ww[i]->Sumw2();
    sprintf(histName,"h_top_%d",i);
    h_top[i]= (TH1D*)ftop->Get(histNameOrg)->Clone(histName); h_top[i]->Sumw2();
    sprintf(histName,"h_dyll_%d",i);
    h_dyll[i]= (TH1D*)fdyll->Get(histNameOrg)->Clone(histName); h_dyll[i]->Sumw2();
    sprintf(histName,"h_dytt_%d",i);
    h_dytt[i]= (TH1D*)fdytt->Get(histNameOrg)->Clone(histName); h_dytt[i]->Sumw2();
    sprintf(histName,"h_vv_%d",i);
    h_vv[i]= (TH1D*)fvv->Get(histNameOrg)->Clone(histName); h_vv[i]->Sumw2();
    sprintf(histName,"h_vvv_%d",i);
    h_vvv[i]= (TH1D*)fvvv->Get(histNameOrg)->Clone(histName); h_vvv[i]->Sumw2();
    sprintf(histName,"h_h125_%d",i);
    h_h125[i]= (TH1D*)fh125->Get(histNameOrg)->Clone(histName); h_h125[i]->Sumw2();
    sprintf(histName,"h_hw1_%d",i);
    h_hw1[i]= (TH1D*)fhw1->Get(histNameOrg)->Clone(histName); h_hw1[i]->Sumw2();

    sprintf(histNameOrg,"h2_mllptll_%d",i);
    sprintf(histName,"h2_mllptll_%d",i);
    h2_mllptll[i]= (TH2D*)fhw1->Get(histNameOrg)->Clone(histName); h2_mllptll[i]->Sumw2();
    
    sprintf(histName,"hdy_%d",i);
    hdy[i] = (TH1D*)h_dytt[i]->Clone(histName); //DYtt is data driven background amount to DYll
    if(i == 0 || i == 2)//sf0j, sf1j
    {
      hdy[i]->Add(h_dyll[i]);
    }
    
    //sprintf(histName,"h_tmp_%d",i);
    //h_tmp[i] = (TH1D*)h_wjets[i]->Clone(histName);

    //Add all histograms (Signal + Background)
    sprintf(histName,"h_tmp_%d",i);
    h_tmp[i] = (TH1D*)h_wjets[i]->Clone(histName);
    h_tmp[i]->Add(h_ww[i]);
    h_tmp[i]->Add(h_top[i]);
    h_tmp[i]->Add(hdy[i]);
    h_tmp[i]->Add(h_vv[i]);
    h_tmp[i]->Add(h_vvv[i]);
    h_tmp[i]->Add(h_h125[i]);
    h_tmp[i]->Add(h_hw1[i]);

    sprintf(histName,"h_total_%d",i);
    h_total[i] = (TH1D*)h_tmp[i]->Clone(histName);
    
    for (int j(1);j<=h_wjets[i]->GetNbinsX();j++)
    {
      cout<<j<<" "<<h_wjets[i]->GetBinContent(j)<<" "<<h_ww[i]->GetBinContent(j)<<" "<<h_top[i]->GetBinContent(j)<<" "<<hdy[i]->GetBinContent(j)<<" "<<h_vv[i]->GetBinContent(j)<<" "<<h_vvv[i]->GetBinContent(j)<<" "<<h_h125[i]->GetBinContent(j)<<" "<<h_hw1[i]->GetBinContent(j)<<": "<<h_tmp[i]->GetBinContent(j)<<endl;
    }

    for (int j(1);j<=h_tmp[i]->GetNbinsX();j++)
    {
      if(h_tmp[i]->GetBinContent(j)<0){
	h_total[i]->SetBinContent(j,0);
	h_total[i]->SetBinError(j,0);
      }else{
	h_total[i]->SetBinContent(j,sqrt(h_tmp[i]->GetBinContent(j)));
	h_total[i]->SetBinError(j,sqrt(h_tmp[i]->GetBinError(j)));
      }
    }

    sprintf(histName,"h_eff_%d",i);
    h_eff[i] = (TH1D*)h_hw1[i]->Clone(histName);
    h_eff[i]->Divide(h_total[i]);

    //h_total[i] ->Sumw2();
    for (int j(1);j<=h_tmp[i]->GetNbinsX();j++)
    {
      cout<<j<<setprecision(4)<<"\t"<<h_hw1[i]->GetBinContent(j)<<"\t +/- "<<h_hw1[i]->GetBinError(j)<<"\t"<<h_total[i]->GetBinContent(j)<<"\t +/- "<<h_total[i]->GetBinError(j)<<"\t"<<h_eff[i]->GetBinContent(j)<<"\t +/- "<<h_eff[i]->GetBinError(j)<<endl;
    }
    gStyle->SetPaintTextFormat("1.2f");
    gStyle->SetOptStat(0);
    gPad->SetLogz(0);
    h2_mllptll[i]->SetTitle("");
    h2_mllptll[i]->GetXaxis()->SetTitle("m_{ll} [GeV/c^{2}]");
    h2_mllptll[i]->GetYaxis()->SetTitle("p_{T}^{ll} [GeV/c]");
    h2_mllptll[i]->SetMarkerSize(0.3);
    h2_mllptll[i]->Draw("COLTEXTZ");
    sprintf(histName,"CutStudy/mllptll_OF%dj.png",int((i-1)/2));
    myCan->SaveAs(histName);
  }
  
  TLegend *Leg_eff1 =new TLegend(0.6,0.75,0.85,0.85); Leg_eff1->SetFillColor(0); Leg_eff1->SetBorderSize(0);
  Leg_eff1->SetTextSize(0.04);
  Leg_eff1->AddEntry(h_eff[1],"#frac{gg2vv}{#sqrt{gg2vv+Bckgr}}","PL");
  h_eff[1]->GetXaxis()->SetTitle("Minimum proj. #slash{E}_{T} [GeV]");
  h_eff[1]->GetYaxis()->SetTitle("F.O.M.");
  h_eff[1]->SetTitle("");
  h_eff[1]->SetLineColor(kRed);
  h_eff[1]->SetMarkerStyle(kFullCircle);
  h_eff[1]->SetMarkerColor(kRed);
  h_eff[1]->Draw("E1");
  Leg_eff1->Draw();
  //sprintf(tmpName,OutDir+"/mpmet_FOM_OF0j.png");
  //cout<<tmpName<<endl;
  myCan->SaveAs(OutDir+"/mpmet_FOM_OF0j.png");

  TLegend *Leg_eff3 =new TLegend(0.6,0.75,0.85,0.85); Leg_eff3->SetFillColor(0); Leg_eff3->SetBorderSize(0);
  Leg_eff3->SetTextSize(0.04);
  Leg_eff3->AddEntry(h_eff[3],"#frac{gg2vv}{#sqrt{gg2vv+Bckgr}}","PL");
  h_eff[3]->GetXaxis()->SetTitle("Minimum proj. #slash{E}_{T} [GeV]");
  h_eff[3]->GetYaxis()->SetTitle("F.O.M.");
  h_eff[3]->SetTitle("");
  h_eff[3]->SetLineColor(kRed);
  h_eff[3]->SetMarkerStyle(kFullCircle);
  h_eff[3]->SetMarkerColor(kRed);
  h_eff[3]->Draw("E1");
  Leg_eff3->Draw();
  //sprintf(tmpName,OutDir+"/mpmet_FOM_OF1j.png");
  //myCan->SaveAs(tmpName);
  myCan->SaveAs(OutDir+"/mpmet_FOM_OF1j.png");
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

