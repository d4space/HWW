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

  TString ChannelName[4];
  ChannelName[0] = "sf0j";
  ChannelName[1] = "of0j";
  ChannelName[2] = "sf1j";
  ChannelName[3] = "of1j";

  TFile *fdata    = new TFile("Data/Data_"+CutName+".root");
  TFile *fwjets   = new TFile("WJet/WJet_"+CutName+".root");
  TFile *fww      = new TFile("WW/WW_"+CutName+".root");
  TFile *ftop     = new TFile("Top/Top_"+CutName+".root");
  TFile *fdyll    = new TFile("DYll/DYll_"+CutName+".root");// we're using DYtt(data driven) in OF channel instead for DYll
  TFile *fdytt    = new TFile("DYtt/DYtt_"+CutName+".root");
  TFile *fvv      = new TFile("VV/VV_"+CutName+".root");
  TFile *fvvv     = new TFile("VVV/VVV_"+CutName+".root");
  TFile *fh125    = new TFile("H125/H125_"+CutName+".root");
  TFile *fSig     = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_"+CutName+".root");
  TFile *fSigBkgr = new TFile("gg2vvHw1Int8TeV/gg2vvHw1Int8TeV_"+CutName+".root");
  TFile *fCot     = new TFile("gg2vvHw25Cot8TeV/gg2vvHw25Cot8TeV_"+CutName+".root");

  char tmpName[30];
  char histName[30];
  char histNameOrg[30];

  TH1D *h_data[4];
  TH1D *h_wjets[4];
  TH1D *h_ww[4];
  TH1D *h_top[4];
  TH1D *h_dyll[4]; 
  TH1D *hdy[4];
  TH1D *h_dytt[4];
  TH1D *h_vv[4];
  TH1D *h_vvv[4];
  TH1D *h_h125[4];
  TH1D *h125[4];
  TH1D *h_sig[4];
  TH1D *h_sig_bkgr[4];
  TH1D *h_cot[4];
  //TH1D *h_hw25[4];
  //TH1D *hw25[4];
  TH1D *hdiff[4];
  TH1D *hRatio[4];
  THStack *hs[4];

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
 
    if(VarName == "channel"){
      TLegend* Lgd = new TLegend(.2,.6,.5,.85);
      if(i == 0 || i == 2)
	TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_channel_%d",i);
    }else if(VarName == "dphill"){
      TLegend* Lgd = new TLegend(.2,.6,.5,.85);
      sprintf(histNameOrg,"h1_dphill_%d",i);
    }else if(VarName == "mll"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_mll_%d",i);
    }else if(VarName == "mth"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_mth_%d",i);
    }else if(VarName == "high_mth"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_high_mth_%d",i);
    }else if(VarName == "charge1"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_charge1_%d",i);
    }else if(VarName == "charge2"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_charge2_%d",i);
    }else if(VarName == "trigger"){
      TLegend* Lgd = new TLegend(.2,.6,.5,.85);
      sprintf(histNameOrg,"h1_trigger_%d",i);
    }else if(VarName == "nextra"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_nextra_%d",i);
    }else if(VarName == "zveto"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_zveto_%d",i);
    }else if(VarName == "flavor"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_flavor_%d",i);
    }else if(VarName == "njet"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_njet_%d",i);
    }else if(VarName == "bveto_mu"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_bveto_mu_%d",i);
    }else if(VarName == "bveto_ip"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_bveto_ip_%d",i);
    }else if(VarName == "nbjettche"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_nbjettche_%d",i);
    }else if(VarName == "ptll"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_ptll_%d",i);
    }else if(VarName == "pt1"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_pt1_%d",i);
    }else if(VarName == "pt2"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_pt2_%d",i);
    }else if(VarName == "pfmet"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_pfmet_%d",i);
    }else if(VarName == "mpmet"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_mpmet_%d",i);
    }else if(VarName == "ppfmet"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_ppfmet_%d",i);
    }else if(VarName == "dymva1"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_dymva1_%d",i);
    }else if(VarName == "dphilljetjet"){
      TLegend* Lgd = new TLegend(.6,.6,.9,.85);
      sprintf(histNameOrg,"h1_dphilljetjet_%d",i);
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
    sprintf(histName,"h_sig_%d",i);
    h_sig[i]= (TH1D*)fSig->Get(histNameOrg)->Clone(histName); h_sig[i]->Sumw2();
    sprintf(histName,"h_sig_bkgr_%d",i);
    h_sig_bkgr[i]= (TH1D*)fSigBkgr->Get(histNameOrg)->Clone(histName); h_sig_bkgr[i]->Sumw2();
    sprintf(histName,"h_cot_%d",i);
    h_cot[i]= (TH1D*)fCot->Get(histNameOrg)->Clone(histName); h_cot[i]->Sumw2();
    //sprintf(histName,"h_hw25_%d",i);
    //h_hw25[i]= (TH1D*)fhw25->Get(histNameOrg)->Clone(histName); h_hw25[i]->Sumw2();

    h_data[i]->SetMarkerStyle(20);
    
    sprintf(histName,"hdy_%d",i);
    hdy[i] = (TH1D*)h_dytt[i]->Clone(histName); //DYtt is data driven background amount to DYll
    if(i == 0 || i == 2)//sf0j, sf1j
    {
      hdy[i]->Add(h_dyll[i]);
    }
    
    sprintf(histName,"h125_%d",i);
    h125[i] = (TH1D*)h_h125[i]->Clone(histName);
    
    //sprintf(histName,"hw25_%d",i);
    //hw25[i] = (TH1D*)h_hw25[i]->Clone(histName);
    
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
    
    h_sig[i]->SetLineColor(kViolet);
    //h_sig[i]->SetLineColor(kOrange-3);
    h_sig[i]->SetLineWidth(2);
    h_sig_bkgr[i]->SetLineColor(kBlue-3);
    h_sig_bkgr[i]->SetLineWidth(2);
    h_cot[i]->SetLineColor(kGreen+3);
    h_cot[i]->SetLineWidth(2);
    
    //h_hw25[i]->SetFillColor(kViolet);
    //h_hw25[i]->SetLineColor(kViolet);
    //hw25[i]->SetLineColor(kViolet);
    //hw25[i]->SetLineWidth(2);
    
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
    //hs[i]->SetMaximum(1.5*(h_data[i]->GetMaximum()));
    hs[i]->SetMaximum(2.*(hs[i]->GetMaximum()));
    hs[i]->SetTitle("");

    myCan->cd(1);
    hs[i]->Draw("HIST");
    
    sprintf(tmpName,"Events / %d",h_data[i]->GetBinWidth(1));
   if(VarName == "dphill" || VarName == "dphilljetjet")
      sprintf(tmpName,"Events / %d^{0}",h_data[i]->GetBinWidth(1));
    if((VarName == "mll" || VarName == "mth") || VarName == "high_mth")
      sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_data[i]->GetBinWidth(1));
    hs[i]->GetYaxis()->SetTitle(tmpName);
    hs[i]->GetYaxis()->SetTitleOffset(1.2);
    hs[i]->GetYaxis()->SetTitleSize(0.04);
    hs[i]->GetYaxis()->SetLabelSize(0.04);
    hs[i]->GetYaxis()->SetNdivisions(505);
    hs[i]->GetXaxis()->SetTitle("");
    hs[i]->GetXaxis()->SetLabelSize(0);
    
    hs[i]->Draw("HIST");
    h_data[i]->Draw("E same");
    h125[i]->Draw("HIST SAME");
    h_sig[i]->Draw("HIST SAME");
    h_sig_bkgr[i]->Draw("HIST SAME");
    h_cot[i]->Draw("HIST SAME");
    //hw25[i]->Draw("HIST SAME");
    
    //sprintf(histName,ChannelName[i]+" "+CutName);
    Lgd->SetHeader(ChannelName[i]+" "+CutName);
    //if (i==1)
    //  Lgd->SetHeader("0-jet e#mu");
    //if (i==3)
    //  Lgd->SetHeader("1-jet e#mu");
    Lgd->AddEntry(h_data[i],"data","pl");
    Lgd->AddEntry(h125[i],"m_{H}=125 GeV","l");
    //Lgd->AddEntry(h_h125[i],"H125","F");
    Lgd->AddEntry(h_wjets[i],"W+jets","F");
    Lgd->AddEntry(h_vv[i],"VV","F");
    Lgd->AddEntry(h_vvv[i],"VVV","F");
    Lgd->AddEntry(h_top[i],"Top","F");
    Lgd->AddEntry(hdy[i],"Z/#gamma*","F");
    Lgd->AddEntry(h_ww[i],"WW","F");
    //Lgd->AddEntry(hw25[i],"Hw25SigOnPeak","l");
    //Lgd->AddEntry(h_sig[i],"Hw1gg2vvSig","l");
    Lgd->AddEntry(h_sig[i],"Hw1 Sig","l");
    Lgd->AddEntry("","","");
    Lgd->AddEntry(h_sig_bkgr[i],"Hw1 Sig+Bkgr","l");
    Lgd->AddEntry("","","");
    Lgd->AddEntry(h_cot[i],"Hw1 Cot","l");
    Lgd->SetBorderSize(0);
    Lgd->SetFillStyle(0);
    Lgd->SetTextSize(0.03);
    Lgd->SetNColumns(2);
    Lgd->Draw();

    sprintf(histName,"hdiff_%d",i);
    hdiff[i] = (TH1D*)h_wjets[i]->Clone(histName);
    hdiff[i]->Add(h_ww[i]);
    hdiff[i]->Add(h_top[i]);
//    hdiff[i]->Add(h_dyll[i]);
//    hdiff[i]->Add(h_dytt[i]);
    hdiff[i]->Add(hdy[i]);
    hdiff[i]->Add(h_vv[i]);
    hdiff[i]->Add(h_vvv[i]);
    hdiff[i]->Add(h_h125[i]);
    sprintf(histName,"hRatio_%d",i);
    hRatio[i] = makeRatioHist(h_data[i],hdiff[i],histName);
    hRatio[i]->SetMarkerStyle(kFullCircle);
    hRatio[i]->SetMarkerSize(0.9);
    hRatio[i]->GetYaxis()->SetTitle("data / MC");
    hRatio[i]->GetXaxis()->SetTitle(VarName);
    if(VarName == "dphill")
      hRatio[i]->GetXaxis()->SetTitle("#Delta#phi_{ll} [^{0}]");
    if(VarName == "mll")
      hRatio[i]->GetXaxis()->SetTitle("m_{ll} [GeV/c^{2}]");
    if(VarName == "mth" || VarName == "high_mth")
      hRatio[i]->GetXaxis()->SetTitle("m_{T}^{ll-#slash{E}_{T}} [GeV/c^{2}]");
    if(VarName == "ptll")
      hRatio[i]->GetXaxis()->SetTitle("p_{T}^{ll} [GeV/c]");
    if(VarName == "pt1")
      hRatio[i]->GetXaxis()->SetTitle("p_{T}^{l,max} [GeV/c]");
    if(VarName == "pt2")
      hRatio[i]->GetXaxis()->SetTitle("p_{T}^{l,min} [GeV/c]");
    if(VarName == "pfmet")
      hRatio[i]->GetXaxis()->SetTitle("PF #slash{E}_{T} [GeV]");
    if(VarName == "mpmet")
      hRatio[i]->GetXaxis()->SetTitle("Minimum proj. PF #slash{E}_{T} [GeV]");
    if(VarName == "ppfmet")
      hRatio[i]->GetXaxis()->SetTitle("proj. PF #slash{E}_{T} [GeV]");
    if(VarName == "dymva1")
      hRatio[i]->GetXaxis()->SetTitle("DY MVA");
    if(VarName == "dphilljetjet")
      hRatio[i]->GetXaxis()->SetTitle("#Delta#phi_{ll-jetjet} [^{0}]");
    
    TLine *rLine = new TLine(h_data[i]->GetXaxis()->GetXmin(),1,h_data[i]->GetXaxis()->GetXmax(),1);
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
  h_ratio->SetTitle("");
  
  return h_ratio;
}

