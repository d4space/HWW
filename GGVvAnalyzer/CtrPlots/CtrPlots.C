#include <TProfile.h>
#include "../../Utils/const.h"
#include "../../Utils/CPlot.hh"
#include "../../Utils/MitStyleRemix.hh"

// Hw1
#define SigXsec 17.9978 //fb
#define CotXsec 16.5574 //fb
#define IntXsec 32.2422 //fb

#define Nevt 25000*160

int CtrPlots(TString BaseName, TString CutName)
{
  TString OutDir = "CtrPlots_"+BaseName+"_"+CutName;
  gSystem->mkdir(OutDir);

  TFile *fname;
  //char tmpName[30];
  char tmpName[50];

  //Histograms
  TH1D* h_mH;
  TH1D* h_mtH;
  TH1D* h_pt1;
  TH1D* h_pt2;
  TH1D* h_pfMET;
  TH1D* h_mll;
  TH1D* h_ptll;
  TH1D* h_mpMET;
  TH1D* h_ppfMET;
  TH1D* h_dphill;
  //TH1D* h_dphillmet;

  //N-1 Cut Histograms
  TH2D* h2_mH_pt1;
  TH2D* h2_mH_pt2;
  TH2D* h2_mH_pfMET;
  TH2D* h2_mH_mpMET;
  TH2D* h2_mH_mll;
  TH2D* h2_mH_ptll;
  TH2D* h2_mH_mtH;

  TProfile* hp_pt1;
  TProfile* hp_pt2;
  TProfile* hp_pfMET;
  TProfile* hp_mpMET;
  TProfile* hp_mll;
  TProfile* hp_ptll;

  double LumiWeight;
  if(BaseName=="Hw1Sig8TeV")
    LumiWeight = Nevt/SigXsec;
  if(BaseName=="Hw1Cot8TeV")
    LumiWeight = Nevt/CotXsec;
  if(BaseName=="Hw1Int8TeV")
    LumiWeight = Nevt/IntXsec;

  sprintf(tmpName,BaseName+"/CtrPlt.root");
  fname = new TFile(tmpName);

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  
  if(CutName=="NoCut")
  {
    LumiWeight = Nevt/SigXsec;
    h_mH       = (TH1D*)fname->Get("hNoCut_Hig_mass")->Clone("h_mH");
    h_mtH      = (TH1D*)fname->Get("hNoCut_HigT_mass")->Clone("h_mtH");
    h_mll      = (TH1D*)fname->Get("hNoCut_mll")->Clone("h_mll");
    h_ptll     = (TH1D*)fname->Get("hNoCut_ptll")->Clone("h_ptll");
    h_pt1      = (TH1D*)fname->Get("hNoCut_pt1")->Clone("h_pt1");
    h_pt2      = (TH1D*)fname->Get("hNoCut_pt2")->Clone("h_pt2");
    h_pfMET    = (TH1D*)fname->Get("hNoCut_MET")->Clone("h_pfMET");
    h_mpMET    = (TH1D*)fname->Get("hNoCut_mpMET") ->Clone("h_mpMET");
    h_ppfMET   = (TH1D*)fname->Get("hNoCut_ppfMET")->Clone("h_ppfMET");
    h_dphill   = (TH1D*)fname->Get("hNoCut_dphill")->Clone("h_dphill");
    //h_dphillmet= (TH1D*)fname->Get("hNoCut_dphillmet")->Clone("h_dphillmet");
  }
  
  if(CutName=="CommonCut")
  {
    h_mH       = (TH1D*)fname->Get("h_Hig_mass")->Clone("h_mH");
    h_mtH      = (TH1D*)fname->Get("h_HigT_mass")->Clone("h_mtH");
    h_mll      = (TH1D*)fname->Get("h_mll")->Clone("h_mll");
    h_ptll     = (TH1D*)fname->Get("h_ptll")->Clone("h_ptll");
    h_pt1      = (TH1D*)fname->Get("h_pt1")->Clone("h_pt1");
    h_pt2      = (TH1D*)fname->Get("h_pt2")->Clone("h_pt2");
    h_pfMET    = (TH1D*)fname->Get("h_MET")->Clone("h_pfMET");
    h_mpMET    = (TH1D*)fname->Get("h_mpMET") ->Clone("h_mpMET");
    h_ppfMET   = (TH1D*)fname->Get("h_ppfMET")->Clone("h_ppfMET");
    h_dphill   = (TH1D*)fname->Get("h_dphill")->Clone("h_dphill");
    //h_dphillmet= (TH1D*)fname->Get("h_dphillmet")->Clone("h_dphillmet");
  }
  
  if(CutName=="N1Cut")
  {
    h2_mH_pt1  = (TH2D*)fname->Get("h2_mH_pt1")->Clone("h2_mH_pt1");
    h2_mH_pt2  = (TH2D*)fname->Get("h2_mH_pt2")->Clone("h2_mH_pt2");
    h2_mH_pfMET= (TH2D*)fname->Get("h2_mH_MET")->Clone("h2_mH_pfMET");
    h2_mH_mpMET= (TH2D*)fname->Get("h2_mH_mpMET")->Clone("h2_mH_mpMET");
    h2_mH_mll  = (TH2D*)fname->Get("h2_mH_mll")->Clone("h2_mH_mll");
    h2_mH_ptll = (TH2D*)fname->Get("h2_mH_ptll")->Clone("h2_mH_ptll");
    h2_mH_mtH  = (TH2D*)fname->Get("h2_mH_mtH")->Clone("h2_mH_mtH");
    h_mll      = (TH1D*)fname->Get("hN1Cut_mll")->Clone("h_mll");
    h_ptll     = (TH1D*)fname->Get("hN1Cut_ptll")->Clone("h_ptll");
    h_pt1      = (TH1D*)fname->Get("hN1Cut_pt1")->Clone("h_pt1");
    h_pt2      = (TH1D*)fname->Get("hN1Cut_pt2")->Clone("h_pt2");
    h_pfMET    = (TH1D*)fname->Get("hN1Cut_MET")->Clone("h_pfMET");
    h_mpMET    = (TH1D*)fname->Get("hN1Cut_mpMET") ->Clone("h_mpMET");
  }

  // Normalize to 8 TeV total Data  
  if(CutName=="CommonCut" || CutName=="NoCut")
  {
    h_mH     -> Scale(LumiTotal8TeV/LumiWeight);
    h_mtH    -> Scale(LumiTotal8TeV/LumiWeight);
    h_ppfMET -> Scale(LumiTotal8TeV/LumiWeight);
    h_dphill -> Scale(LumiTotal8TeV/LumiWeight);
    //h_dphillmet-> Scale(LumiTotal8TeV/LumiWeight);
  }
  h_mll   -> Scale(LumiTotal8TeV/LumiWeight);
  h_ptll  -> Scale(LumiTotal8TeV/LumiWeight);
  h_pt1   -> Scale(LumiTotal8TeV/LumiWeight);
  h_pt2   -> Scale(LumiTotal8TeV/LumiWeight);
  h_pfMET -> Scale(LumiTotal8TeV/LumiWeight);
  h_mpMET -> Scale(LumiTotal8TeV/LumiWeight);

  //Save Histograms to file
  if(CutName=="CommonCut" || CutName=="NoCut")
  {
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mH->GetBinWidth(1));
    CPlot* Plot_mH    = new CPlot("HiggsMass","","m_{H} [GeV/c^{2}]",tmpName);
    Plot_mH->setOutDir(OutDir);
    Plot_mH->AddHist1D(h_mH,"H",kBlack);
    Plot_mH->AddLine(140,0,140,1.2*h_mH->GetMaximum(),kRed,2);
    Plot_mH->AddLine(300,0,300,1.2*h_mH->GetMaximum(),kBlue,2);
    Plot_mH->SetLegend(0.55,0.8,0.85,0.9);
    Plot_mH->GetLegend()->AddEntry(h_mH,BaseName,"l");
    Plot_mH->SetLogy();
    Plot_mH->Draw(myCan,kTRUE,"png");
    
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mtH->GetBinWidth(1));
    CPlot* Plot_mtH   = new CPlot("HiggsTMass","","m_{T}^{H} [Gev/c^{2}]",tmpName);
    Plot_mtH->setOutDir(OutDir);
    Plot_mtH->AddHist1D(h_mtH,"H",kBlack);
    Plot_mtH->SetLegend(0.55,0.8,0.85,0.9);
    Plot_mtH->GetLegend()->AddEntry(h_mtH,BaseName,"l");
    Plot_mtH->SetLogy();
    Plot_mtH->Draw(myCan,kTRUE,"png");
  
    sprintf(tmpName,"Events / %.1f GeV",h_ppfMET->GetBinWidth(1));
    CPlot* Plot_ppfMET= new CPlot("ppfMET","","proj. pf #slash{E}_{T} [GeV]",tmpName);
    Plot_ppfMET->setOutDir(OutDir);
    Plot_ppfMET->AddHist1D(h_ppfMET,"H",kBlack);
    Plot_ppfMET->SetLegend(0.55,0.8,0.85,0.9);
    Plot_ppfMET->GetLegend()->AddEntry(h_ppfMET,BaseName,"l");
    Plot_ppfMET->SetLogy();
    Plot_ppfMET->Draw(myCan,kTRUE,"png");
    
    sprintf(tmpName,"Events / %.1f^{0}",h_dphill->GetBinWidth(1));
    CPlot* Plot_dphill= new CPlot("dphill","","#Delta#phi_{ll} [^{0}]",tmpName);
    Plot_dphill->setOutDir(OutDir);
    Plot_dphill->AddHist1D(h_dphill,"H",kBlack);
    Plot_dphill->SetLegend(0.55,0.8,0.85,0.9);
    Plot_dphill->GetLegend()->AddEntry(h_dphill,BaseName,"l");
    Plot_dphill->SetLogy();
    Plot_dphill->Draw(myCan,kTRUE,"png");
    
    //sprintf(tmpName,"Events / %.1f^{0}",h_dphillmet->GetBinWidth(1));
    //CPlot* Plot_dphillmet= new CPlot("dphillmet","","#Delta#phi_{ll-#slash{E}_{T}} [^{0}]",tmpName);
    //Plot_dphillmet->setOutDir(OutDir);
    //Plot_dphillmet->AddHist1D(h_dphillmet,"H",kBlack);
    //Plot_dphillmet->SetLegend(0.55,0.8,0.85,0.9);
    //Plot_dphillmet->GetLegend()->AddEntry(h_dphillmet,BaseName,"l");
    //Plot_dphillmet->SetLogy();
    //Plot_dphillmet->Draw(myCan,kTRUE,"png");
  }
  
  if(CutName=="N1Cut")
  {
    h2_mH_pt1   -> SetMarkerSize(0.4);
    h2_mH_pt2   -> SetMarkerSize(0.4);
    h2_mH_pfMET -> SetMarkerSize(0.4);
    h2_mH_mpMET -> SetMarkerSize(0.4);
    h2_mH_mll   -> SetMarkerSize(0.4);
    h2_mH_mtH   -> SetMarkerSize(0.4);
    h2_mH_ptll  -> SetMarkerSize(0.4);
    
    //2Dplot Higgs Mass vs Higgs Transverse Mass
    CPlot* Plot_mH_mtH = new CPlot("H2D_HmassVsHTmass","","m_{H} [GeV/c^{2}]","m_{T}^{H} [GeV/c^{2}]");
    Plot_mH_mtH->setOutDir(OutDir);
    Plot_mH_mtH->AddHist2D(h2_mH_mtH);
    Plot_mH_mtH->Draw(myCan,kTRUE,"png");

    //pt1 TProfileX()
    hp_pt1 = new TProfile("hp_pt1","pt1 ProfileX",20,0,1000,0,150);
    hp_pt1 = h2_mH_pt1->ProfileX("pt1_pfx",0,150,"s");

    hp_pt1->GetXaxis()->SetTitle("m_{H} [GeV/c^{2}]");
    hp_pt1->GetYaxis()->SetTitle("p_{T}^{l, max} [GeV/c]");
    hp_pt1->SetTitle("");
    hp_pt1->SetLineColor(kRed);
    hp_pt1->SetMarkerColor(kRed);
    
    TLine *rL_pt1 = new TLine(0,20,1000,20);
    rL_pt1->SetLineWidth(2);
    rL_pt1->SetLineStyle(2);
    rL_pt1->SetLineColor(kRed);

    TLegend *Leg_pt1 =new TLegend(0.2,0.83,0.35,0.9); Leg_pt1->SetFillColor(0); Leg_pt1->SetBorderSize(0);
    Leg_pt1->AddEntry(hp_pt1,"ProfileX()","PL");

    hp_pt1->Draw();
    h2_mH_pt1->Draw("same");
    hp_pt1->Draw("E1same");
    rL_pt1->Draw("same");
    Leg_pt1->Draw();
    sprintf(tmpName,OutDir+"/pt1_ProfileX.png");
    myCan->SaveAs(tmpName);

    //pt2 TProfileX()
    hp_pt2 = new TProfile("hp_pt2","pt2 ProfileX",20,0,1000,0,150);
    hp_pt2 = h2_mH_pt2->ProfileX("pt2_pfx",0,150,"s");

    hp_pt2->GetXaxis()->SetTitle("m_{H} [GeV/c^{2}]");
    hp_pt2->GetYaxis()->SetTitle("p_{T}^{l, min} [GeV/c]");
    hp_pt2->SetTitle("");
    hp_pt2->SetLineColor(kRed);
    hp_pt2->SetMarkerColor(kRed);
    
    TLine *rL_pt2 = new TLine(0,10,1000,10);
    rL_pt2->SetLineWidth(2);
    rL_pt2->SetLineStyle(2);
    rL_pt2->SetLineColor(kRed);

    TLegend *Leg_pt2 =new TLegend(0.2,0.83,0.35,0.9); Leg_pt2->SetFillColor(0); Leg_pt2->SetBorderSize(0);
    Leg_pt2->AddEntry(hp_pt2,"ProfileX()","PL");

    hp_pt2->Draw();
    h2_mH_pt2->Draw("same");
    hp_pt2->Draw("E1same");
    rL_pt2->Draw("same");
    Leg_pt2->Draw();
    sprintf(tmpName,OutDir+"/pt2_ProfileX.png");
    myCan->SaveAs(tmpName);

    //pfMET TProfileX()
    hp_pfMET = new TProfile("hp_pfMET","pfMET ProfileX",20,0,1000,0,200);
    hp_pfMET = h2_mH_pfMET->ProfileX("pfMET_pfx",0,200,"s");

    hp_pfMET->GetXaxis()->SetTitle("m_{H} [GeV/c^{2}]");
    hp_pfMET->GetYaxis()->SetTitle("pf #slash{E}_{T} [GeV]");
    hp_pfMET->SetTitle("");
    hp_pfMET->SetLineColor(kRed);
    hp_pfMET->SetMarkerColor(kRed);
    
    TLine *rL_pfMET = new TLine(0,20,1000,20);
    rL_pfMET->SetLineWidth(2);
    rL_pfMET->SetLineStyle(2);
    rL_pfMET->SetLineColor(kRed);

    TLegend *Leg_pfMET =new TLegend(0.2,0.83,0.35,0.9); Leg_pfMET->SetFillColor(0); Leg_pfMET->SetBorderSize(0);
    Leg_pfMET->AddEntry(hp_pfMET,"ProfileX()","PL");

    hp_pfMET->Draw();
    h2_mH_pfMET->Draw("same");
    hp_pfMET->Draw("E1same");
    rL_pfMET->Draw("same");
    Leg_pfMET->Draw();
    sprintf(tmpName,OutDir+"/pfMET_ProfileX.png");
    myCan->SaveAs(tmpName);

    //mpMET TProfileX()
    hp_mpMET = new TProfile("hp_mpMET","mpMET ProfileX",20,0,1000,0,200);
    hp_mpMET = h2_mH_mpMET->ProfileX("mpMET_pfx",0,200,"s");

    hp_mpMET->GetXaxis()->SetTitle("m_{H} [GeV/c^{2}]");
    hp_mpMET->GetYaxis()->SetTitle("min(proj. #slash{E}_{T}) [GeV]");
    hp_mpMET->SetTitle("");
    hp_mpMET->SetLineColor(kRed);
    hp_mpMET->SetMarkerColor(kRed);
    
    TLine *rL_mpMET = new TLine(0,20,1000,20);
    rL_mpMET->SetLineWidth(2);
    rL_mpMET->SetLineStyle(2);
    rL_mpMET->SetLineColor(kRed);

    TLegend *Leg_mpMET =new TLegend(0.2,0.83,0.35,0.9); Leg_mpMET->SetFillColor(0); Leg_mpMET->SetBorderSize(0);
    Leg_mpMET->AddEntry(hp_mpMET,"ProfileX()","PL");

    hp_mpMET->Draw();
    h2_mH_mpMET->Draw("same");
    hp_mpMET->Draw("E1same");
    rL_mpMET->Draw("same");
    Leg_mpMET->Draw();
    sprintf(tmpName,OutDir+"/mpMET_ProfileX.png");
    myCan->SaveAs(tmpName);

    //mll TProfileX()
    hp_mll = new TProfile("hp_mll","mll ProfileX",20,0,1000,0,600);
    hp_mll = h2_mH_mll->ProfileX("mll_pfx",0,600,"s");

    hp_mll->GetXaxis()->SetTitle("m_{H} [GeV/c^{2}]");
    hp_mll->GetYaxis()->SetTitle("m_{ll} [GeV/c^{2}]");
    hp_mll->SetTitle("");
    hp_mll->SetLineColor(kRed);
    hp_mll->SetMarkerColor(kRed);
    
    TLine *rL_mll = new TLine(0,12,1000,12);
    rL_mll->SetLineWidth(2);
    rL_mll->SetLineStyle(2);
    rL_mll->SetLineColor(kRed);

    TLegend *Leg_mll =new TLegend(0.2,0.83,0.35,0.9); Leg_mll->SetFillColor(0); Leg_mll->SetBorderSize(0);
    Leg_mll->AddEntry(hp_mll,"ProfileX()","PL");

    hp_mll->Draw();
    h2_mH_mll->Draw("same");
    hp_mll->Draw("E1same");
    rL_mll->Draw("same");
    Leg_mll->Draw();
    sprintf(tmpName,OutDir+"/DiLept_mass_ProfileX.png");
    myCan->SaveAs(tmpName);

    //ptll TProfileX()
    hp_ptll = new TProfile("hp_ptll","ptll ProfileX",20,0,1000,0,150);
    hp_ptll = h2_mH_ptll->ProfileX("ptll_pfx",0,150,"s");

    hp_ptll->GetXaxis()->SetTitle("m_{H} [GeV/c^{2}]");
    hp_ptll->GetYaxis()->SetTitle("p_{T}^{ll} [GeV/c]");
    hp_ptll->SetTitle("");
    hp_ptll->SetLineColor(kRed);
    hp_ptll->SetMarkerColor(kRed);
    
    TLine *rL_ptll = new TLine(0,30,1000,30);
    rL_ptll->SetLineWidth(2);
    rL_ptll->SetLineStyle(2);
    rL_ptll->SetLineColor(kRed);

    TLegend *Leg_ptll =new TLegend(0.2,0.83,0.35,0.9); Leg_ptll->SetFillColor(0); Leg_ptll->SetBorderSize(0);
    Leg_ptll->AddEntry(hp_ptll,"ProfileX()","PL");

    hp_ptll->Draw();
    h2_mH_ptll->Draw("same");
    hp_ptll->Draw("E1same");
    rL_ptll->Draw("same");
    Leg_ptll->Draw();
    sprintf(tmpName,OutDir+"/DiLept_pt_ProfileX.png");
    myCan->SaveAs(tmpName);
  }

  sprintf(tmpName,"Events / %.1f GeV/c",h_pt1->GetBinWidth(1));
  CPlot* Plot_pt1   = new CPlot("pt1","","p_{T}^{l, max} [GeV/c]",tmpName);
  Plot_pt1->setOutDir(OutDir);
  Plot_pt1->AddHist1D(h_pt1,"H",kBlack);
  if(CutName=="NoCut" || CutName=="N1Cut")
    Plot_pt1->AddLine(20,0,20,1.2*h_pt1->GetMaximum(),kRed,2);
  Plot_pt1->SetLegend(0.55,0.8,0.85,0.9);
  Plot_pt1->GetLegend()->AddEntry(h_pt1,BaseName,"l");
  Plot_pt1->SetLogy();
  Plot_pt1->Draw(myCan,kTRUE,"png");
  
  sprintf(tmpName,"Events / %.1f GeV/c",h_pt2->GetBinWidth(1));
  CPlot* Plot_pt2   = new CPlot("pt2","","p_{T}^{l, min} [GeV/c]",tmpName);
  Plot_pt2->setOutDir(OutDir);
  Plot_pt2->AddHist1D(h_pt2,"H",kBlack);
  if(CutName=="NoCut" || CutName=="N1Cut")
    Plot_pt2->AddLine(10,0,10,1.2*h_pt2->GetMaximum(),kRed,2);
  Plot_pt2->SetLegend(0.55,0.8,0.85,0.9);
  Plot_pt2->GetLegend()->AddEntry(h_pt2,BaseName,"l");
  Plot_pt2->SetLogy();
  Plot_pt2->Draw(myCan,kTRUE,"png");
  
  sprintf(tmpName,"Events / %.1f GeV",h_pfMET->GetBinWidth(1));
  CPlot* Plot_pfMET = new CPlot("pfMET","","pf #slash{E}_{T} [GeV]",tmpName);
  Plot_pfMET->setOutDir(OutDir);
  Plot_pfMET->AddHist1D(h_pfMET,"H",kBlack);
  if(CutName=="NoCut" || CutName=="N1Cut")
    Plot_pfMET->AddLine(20,0,20,1.2*h_pfMET->GetMaximum(),kRed,2);
  Plot_pfMET->SetLegend(0.55,0.8,0.85,0.9);
  Plot_pfMET->GetLegend()->AddEntry(h_pfMET,BaseName,"l");
  Plot_pfMET->SetLogy();
  Plot_pfMET->Draw(myCan,kTRUE,"png");
  
  sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mll->GetBinWidth(1));
  CPlot* Plot_mll   = new CPlot("DiLeptMass","","m_{ll} [GeV/c^{2}]",tmpName);
  Plot_mll->setOutDir(OutDir);
  Plot_mll->AddHist1D(h_mll,"H",kBlack);
  if(CutName=="NoCut" || CutName=="N1Cut")
    Plot_mll->AddLine(12,0,12,1.2*h_mll->GetMaximum(),kRed,2);
  Plot_mll->SetLegend(0.55,0.8,0.85,0.9);
  Plot_mll->GetLegend()->AddEntry(h_mll,BaseName,"l");
  Plot_mll->SetLogy();
  Plot_mll->Draw(myCan,kTRUE,"png");
  
  sprintf(tmpName,"Events / %.1f GeV/c",h_ptll->GetBinWidth(1));
  CPlot* Plot_ptll  = new CPlot("DiLeptPt","","p_{T}^{ll} [GeV/c]",tmpName);
  Plot_ptll->setOutDir(OutDir);
  Plot_ptll->AddHist1D(h_ptll,"H",kBlack);
  if(CutName=="NoCut" || CutName=="N1Cut")
    Plot_ptll->AddLine(30,0,30,1.2*h_ptll->GetMaximum(),kRed,2);
  Plot_ptll->SetLegend(0.55,0.8,0.85,0.9);
  Plot_ptll->GetLegend()->AddEntry(h_ptll,BaseName,"l");
  Plot_ptll->SetLogy();
  Plot_ptll->Draw(myCan,kTRUE,"png");
  
  sprintf(tmpName,"Events / %.1f GeV",h_mpMET->GetBinWidth(1));
  CPlot* Plot_mpMET = new CPlot("mpMET","","min(proj. #slash{E}_{T}) [GeV]",tmpName);
  Plot_mpMET->setOutDir(OutDir);
  Plot_mpMET->AddHist1D(h_mpMET,"H",kBlack);
  if(CutName=="NoCut" || CutName=="N1Cut")
    Plot_mpMET->AddLine(20,0,20,1.2*h_mpMET->GetMaximum(),kRed,2);
  Plot_mpMET->SetLegend(0.55,0.8,0.85,0.9);
  Plot_mpMET->GetLegend()->AddEntry(h_mpMET,BaseName,"l");
  Plot_mpMET->SetLogy();
  Plot_mpMET->Draw(myCan,kTRUE,"png");
  
  return 0;
}
