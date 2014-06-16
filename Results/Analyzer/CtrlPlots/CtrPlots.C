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

void CtrPlots(TString CutName, TString VarName, TString DirName){
  double LumiW = 19.468;

  TString ChannelName[4];
  ChannelName[0] = "sf0j";
  ChannelName[1] = "of0j";
  ChannelName[2] = "sf1j";
  ChannelName[3] = "of1j";

  TFile *fdata  = new TFile("Data/Data_"+CutName+".root");
  TFile *fwjets = new TFile("WJet/WJet_"+CutName+".root");
  TFile *fww    = new TFile("WW/WW_"+CutName+".root");
  TFile *ftop   = new TFile("Top/Top_"+CutName+".root");
  TFile *fdyll  = new TFile("DYll/DYll_"+CutName+".root");
  TFile *fdytt  = new TFile("DYtt/DYtt_"+CutName+".root");
  TFile *fvv    = new TFile("VV/VV_"+CutName+".root");
  TFile *fvvv   = new TFile("VVV/VVV_"+CutName+".root");
  TFile *fh125  = new TFile("H125/H125_"+CutName+".root");

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  TH1D *h_data[4];
  TH1D *h_wjets[4];
  TH1D *h_ww[4];
  TH1D *h_top[4];
  TH1D *h_dyll[4];
  TH1D *h_dytt[4];
  TH1D *h_vv[4];
  TH1D *h_vvv[4];
  TH1D *h_h125[4];
  TH1D *hdy[4];
  TH1D *h125[4];
  TH1D *hdiff[4];
  TH1D* hRatio[4];
  THStack *hs[4];

  //=====================================
  //Looping for each Channel
  //=====================================
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
 
    if(VarName == "channel"){
      TLegend* Lgd = new TLegend(.22,.65,.5,.85);
      sprintf(histNameOrg,"h1_channel_%d",i);
    }else if(VarName == "dphill"){
      TLegend* Lgd = new TLegend(.22,.65,.5,.85);
      sprintf(histNameOrg,"h1_dphill_%d",i);
    }else if(VarName == "mll"){
      TLegend* Lgd = new TLegend(.62,.65,.9,.85);
      sprintf(histNameOrg,"h1_mll_%d",i);
    }else if(VarName == "mth"){
      TLegend* Lgd = new TLegend(.62,.65,.9,.85);
      sprintf(histNameOrg,"h1_mth_%d",i);
    }
    
    sprintf(histName,"h_data_%d",i);
    h_data[i] = (TH1D*)fdata->Get(histNameOrg)->Clone(histName); h_data[i]->Sumw2();
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

    if(VarName == "dphill")
      h_wjets[i]->Scale(1./LumiW);
    h_data[i]->SetMarkerStyle(20);
    
    sprintf(histName,"hdy_%d",i);
    hdy[i] = (TH1D*)h_dyll[i]->Clone(histName);
    hdy[i]->Add(h_dytt[i]);
    
    sprintf(histName,"h125_%d",i);
    h125[i] = (TH1D*)h_h125[i]->Clone(histName);
    
    h_wjets[i]->SetFillColor(kGray+1);
    h_ww[i]->SetFillColor(kCyan-8);
    h_top[i]->SetFillColor(kYellow);
    hdy[i]->SetFillColor(kGreen+2);
    h_vv[i]->SetFillColor(kAzure-2);
    h_vvv[i]->SetFillColor(36);
    h_h125[i]->SetFillColor(kRed);
    h_h125[i]->SetLineColor(kRed);
    h125[i]->SetLineColor(kRed);
    h125[i]->SetLineWidth(2);
  
    h_data[i]->GetYaxis()->SetTitleOffset(0.6);
    h_data[i]->GetYaxis()->SetTitleSize(0.08);
    h_data[i]->GetYaxis()->SetLabelSize(0.08);
    h_data[i]->GetYaxis()->SetNdivisions(505);
    h_data[i]->GetYaxis()->SetTitle(histName);
    
    sprintf(histName,"hs_%d",i);
    hs[i] = new THStack(histName,histName);
    hs[i]->Add(h_ww[i]);
    hs[i]->Add(hdy[i]);
    hs[i]->Add(h_top[i]);
    hs[i]->Add(h_vvv[i]);
    hs[i]->Add(h_vv[i]);
    hs[i]->Add(h_wjets[i]);
    //hs[i]->Add(h_h125[i]);
    hs[i]->SetMaximum(1.5*(h_data[i]->GetMaximum()));
    hs[i]->SetTitle("");

    myCan->cd(1);
    hs[i]->Draw("HIST");
    
   if(VarName == "dphill")
      sprintf(tmpName,"Events / %d^{0}",h_data[i]->GetBinWidth(1));
    if(VarName == "mll" || VarName == "mth")
      sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_data[i]->GetBinWidth(1));
    hs[i]->GetYaxis()->SetTitle(tmpName);
    hs[i]->GetXaxis()->SetTitle("");

    hs[i]->Draw("HIST");
    h_data[i]->Draw("E same");
    h125[i]->Draw("HIST SAME");
    
    if (i==1)
      Lgd->SetHeader("0-jet e#mu");
    if (i==3)
      Lgd->SetHeader("1-jet e#mu");
    Lgd->AddEntry(h_data[i],"data","pl");
    Lgd->AddEntry(h125[i],"m_{H}=125 GeV","l");
    //Lgd->AddEntry(h_h125[i],"H125","F");
    Lgd->AddEntry(h_wjets[i],"W+jets","F");
    Lgd->AddEntry(h_vv[i],"VV","F");
    Lgd->AddEntry(h_vvv[i],"VVV","F");
    Lgd->AddEntry(h_top[i],"Top","F");
    Lgd->AddEntry(hdy[i],"Z/#gamma*","F");
    Lgd->AddEntry(h_ww[i],"WW","F");
    Lgd->SetBorderSize(0);
    Lgd->SetFillStyle(0);
    Lgd->SetTextSize(0.03);
    Lgd->SetNColumns(2);
    Lgd->Draw();

    sprintf(histName,"hdiff_%d",i);
    hdiff[i] = (TH1D*)h_wjets[i]->Clone(histName);
    hdiff[i]->Add(h_ww[i]);
    hdiff[i]->Add(h_top[i]);
    hdiff[i]->Add(h_dyll[i]);
    hdiff[i]->Add(h_dytt[i]);
    hdiff[i]->Add(h_vv[i]);
    hdiff[i]->Add(h_vvv[i]);
    hdiff[i]->Add(h_h125[i]);
    sprintf(histName,"hRatio_%d",i);
    hRatio[i] = makeRatioHist(h_data[i],hdiff[i],histName);
    hRatio[i]->SetMarkerStyle(kFullCircle);
    hRatio[i]->SetMarkerSize(0.9);
    hRatio[i]->GetYaxis()->SetTitle("data / MC");
    if(VarName == "channel")
      hRatio[i]->GetXaxis()->SetTitle("channel");
    if(VarName == "dphill")
      hRatio[i]->GetXaxis()->SetTitle("#Delta#phi_{ll} [^{0}]");
    if(VarName == "mll")
      hRatio[i]->GetXaxis()->SetTitle("m_{ll} [GeV/c^{2}]");
    if(VarName == "mth")
      hRatio[i]->GetXaxis()->SetTitle("m_{T}^{ll-#slash{E}_{T}} [GeV/c^{2}]");
    
    TLine *rLine = new TLine(0,1,h_data[i]->GetXaxis()->GetXmax(),1);
    rLine->SetLineWidth(2);
    rLine->SetLineStyle(2);
    rLine->SetLineColor(kRed);

    myCan->cd(2);
    hRatio[i]->Draw("E");
    rLine->Draw("same");
    myCan->Modified();
    myCan->Update();
    //sprintf(tmpName,"_%s.png",ChannelName);
    TString outFile = DirName + "/" + VarName + "_" + CutName + "_" + ChannelName[i] + ".png";
    myCan->SaveAs(outFile);

    myCan->cd(1);
    myCan_1->SetLogy();
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
  
  return h_ratio;
}
