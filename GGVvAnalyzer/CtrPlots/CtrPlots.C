#include "../../Utils/const.h"
#include "../../Utils/CPlot.hh"
#include "../../Utils/MitStyleRemix.hh"

// Hw1
#define SigXsec 17.99776700786161 //fb
//#define CotXsec 16.6*15 //fb
//#define IntXsec 32.3*15 //fb
// Hw25
//#define SigXsec 29.5*15 //fb
//#define CotXsec 16.6*15 //fb
//#define IntXsec 38.3*15 //fb

#define Nevt 25000*160

int CtrPlots()
{
  //TString OutDir = "CtrPlotsHw1";
  TString OutDir = "CtrPlotsHw1Sig";
  //TString OutDir = "CtrPlotsOffPeak";
  gSystem->mkdir(OutDir);

  TFile *f_Sig, *f_Cot, *f_Int;
  TH1D* Cot_Hig_Mass;
  TH1D* Int_Hig_Mass;
  //Signal histograms
  TH1D* Sig_Hig_Mass;
  TH1D* Sig_HigT_Mass;
  TH1D* Sig_Lept_pt1;
  TH1D* Sig_Lept_pt2;
  //TH1D* Sig_Hig_CutMass;
  TH1D* Sig_Hig_CutEt;
  TH1D* Sig_ElMu_Mass;
  TH1D* hMET;
  TH1D* hmpMET;
  TH1D* hdphill;
  double SigLumi = Nevt/SigXsec;
  //double CotLumi = Nevt/CotXsec;
  //double IntLumi = Nevt/IntXsec;

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  CPlot* HigMass    = new CPlot("HiggsMass","","m_{H} [GeV/c^{2}]","events/bin");
  CPlot* HigTMass   = new CPlot("HigTMass","","m_{T}^{ll-#slash{E}_{T}} [Gev/c^{2}]","events/bin");
  CPlot* Leptpt1    = new CPlot("Leptpt1","","p_{T}^{l, max} [GeV/c]","events/bin");
  CPlot* Leptpt2    = new CPlot("Leptpt2","","p_{T}^{l, min} [GeV/c]","events/bin");
  //CPlot* HigCutMass = new CPlot("HigCutMass","","Higgs Mass (Cut pt1>20, pt2>10)","events/bin");
  CPlot* HigCutEt   = new CPlot("HigCutEt","","Higgs Et (Cut Et>0)","events/bin");
  CPlot* DiLeptMass = new CPlot("DiLeptMass","","m_{ll} [Gev/c^{2}]","events/bin");
  CPlot* MET = new CPlot("MET","","PF #slash{E}_{T} [GeV]","events/bin");
  CPlot* mpMET = new CPlot("mpMET","","min(proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]","events/bin");
  CPlot* Dphill = new CPlot("Dphill","","#Delta#phi_{ll} [^{0}]","events/bin");
  //CPlot* HigMass= new CPlot("HiggsMass","","mass (emu2nu)","xsec [fb]");
  //f_Sig = new TFile("SigHw25RoScMiCut/CtrPlt.root");
  //f_Sig = new TFile("SigHw25RoScMiCutOffPeak/CtrPlt.root");
  //f_Cot = new TFile("CotHw25RoScMiCut/CtrPlt.root");
  //Cot_Hig_Mass	=(TH1D*)f_Cot->Get("hHig_Mass")->Clone();
  //f_Int = new TFile("IntHw25RoScMiCut/CtrPlt.root");
  //f_Int = new TFile("IntHw25RoScMiCutOffPeak/CtrPlt.root");
  //Int_Hig_Mass	=(TH1D*)f_Int->Get("hHig_Mass")->Clone();
  
  f_Sig = new TFile("SigHw1Full8TeV/CtrPlt.root");
  
  Sig_Hig_Mass	  = (TH1D*)f_Sig->Get("hHig_Mass")->Clone("Sig_Hig_Mass");
  Sig_HigT_Mass   = (TH1D*)f_Sig->Get("hHigT_Mass")->Clone("Sig_HigT_Mass");
  Sig_Lept_pt1    = (TH1D*)f_Sig->Get("h_leadingPt")->Clone("Sig_Lept_pt1");
  Sig_Lept_pt2    = (TH1D*)f_Sig->Get("h_trailingPt")->Clone("Sig_Lept_pt2");
  //Sig_Hig_CutMass = (TH1D*)f_Sig->Get("h_leadingM")->Clone("Sig_Hig_CutMass");
  Sig_Hig_CutEt   = (TH1D*)f_Sig->Get("hHig_Et")->Clone("Sig_Hig_CutEt");
  Sig_ElMu_Mass   = (TH1D*)f_Sig->Get("h_DiLept_Mass")->Clone("Sig_ElMu_Mass");
  hMET = (TH1D*)f_Sig->Get("h_MET")->Clone("hMET");
  hmpMET = (TH1D*)f_Sig->Get("h_mpMET")->Clone("hmpMET");
  hdphill = (TH1D*)f_Sig->Get("h_dphill")->Clone("hdphill");
  
  Sig_Hig_Mass    -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  Sig_HigT_Mass   -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  Sig_Lept_pt1    -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  Sig_Lept_pt2    -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  //Sig_Hig_CutMass -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  Sig_Hig_CutEt   -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  Sig_ElMu_Mass   -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  hMET -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  hmpMET -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  hdphill -> Scale(LumiTotal8TeV/SigLumi); // Normalize to 8 TeV total Data
  //Cot_Hig_Mass->Scale(LumiTotal8TeV/CotLumi);
  //Int_Hig_Mass->Scale(LumiTotal8TeV/IntLumi);

  int binMin = Sig_Hig_Mass->GetMinimumBin();
  double x = Sig_Hig_Mass->GetXaxis()->GetBinCenter(binMin);

  //HigMass->setOutDir(OutDir);
  //HigMass->AddHist1D(Sig_Hig_Mass,"l",kBlack);
  ////HigMass->AddHist1D(Cot_Hig_Mass,"l",kRed);
  ////HigMass->AddHist1D(Int_Hig_Mass,"l",kGreen);
  //HigMass->AddLine(140, 0.0, 140, 1.2*Sig_Hig_Mass->GetMaximum(),kRed,2);
  //HigMass->AddLine(300, 0.0, 300, 1.2*Sig_Hig_Mass->GetMaximum(),kBlue,2);
  //HigMass->SetLegend(0.6,0.7,0.9,0.8);
  //HigMass->GetLegend()->AddEntry(Sig_Hig_Mass,"H #rightarrow WW","l");
  ////HigMass->GetLegend()->AddEntry(Cot_Hig_Mass,"gg #rightarrow WW","l");
  ////HigMass->GetLegend()->AddEntry(Int_Hig_Mass,"H(WW) + gg(WW)","l");
  //HigMass->SetLogy();
  ////HigMass->SetLogx();
  //HigMass->Draw(myCan,kTRUE,"png");

  //Save Histograms to file
  HigMass->setOutDir(OutDir);
  HigMass->AddHist1D(Sig_Hig_Mass,"l",kBlack);
  HigMass->AddLine(140, 0.0, 140, 1.2*Sig_Hig_Mass->GetMaximum(),kRed,2);
  HigMass->AddLine(300, 0.0, 300, 1.2*Sig_Hig_Mass->GetMaximum(),kBlue,2);
  HigMass->SetLegend(0.6,0.7,0.9,0.8);
  HigMass->GetLegend()->AddEntry(Sig_Hig_Mass,"H #rightarrow WW","l");
  HigMass->SetLogy();
  HigMass->Draw(myCan,kTRUE,"png");
  
  HigTMass->setOutDir(OutDir);
  HigTMass->AddHist1D(Sig_HigT_Mass,"l",kBlack);
  //HigTMass->AddLine(140, 0.0, 140, 1.2*Sig_HigT_Mass->GetMaximum(),kRed,2);
  //HigTMass->AddLine(300, 0.0, 300, 1.2*Sig_HigT_Mass->GetMaximum(),kBlue,2);
  HigTMass->SetLegend(0.6,0.7,0.9,0.8);
  HigTMass->GetLegend()->AddEntry(Sig_HigT_Mass,"H #rightarrow WW","l");
  HigTMass->SetLogy();
  HigTMass->Draw(myCan,kTRUE,"png");
  
  Leptpt1->setOutDir(OutDir);
  Leptpt1->AddHist1D(Sig_Lept_pt1,"l",kBlack);
  Leptpt1->SetLegend(0.6,0.7,0.9,0.8);
  Leptpt1->GetLegend()->AddEntry(Sig_Lept_pt1,"H #rightarrow WW","l");
  Leptpt1->SetLogy();
  Leptpt1->Draw(myCan,kTRUE,"png");
  
  Leptpt2->setOutDir(OutDir);
  Leptpt2->AddHist1D(Sig_Lept_pt2,"l",kBlack);
  Leptpt2->SetLegend(0.6,0.7,0.9,0.8);
  Leptpt2->GetLegend()->AddEntry(Sig_Lept_pt2,"H #rightarrow WW","l");
  Leptpt2->SetLogy();
  Leptpt2->Draw(myCan,kTRUE,"png");
  
  //HigCutMass->setOutDir(OutDir);
  //HigCutMass->AddHist1D(Sig_Hig_CutMass,"l",kBlack);
  ////HigCutMass->AddLine(140, 0.0, 140, 1.2*Sig_Hig_CutMass->GetMaximum(),kRed,2);
  ////HigCutMass->AddLine(300, 0.0, 300, 1.2*Sig_Hig_CutMass->GetMaximum(),kBlue,2);
  //HigCutMass->SetLegend(0.6,0.7,0.9,0.8);
  //HigCutMass->GetLegend()->AddEntry(Sig_Hig_CutMass,"H #rightarrow WW","l");
  //HigCutMass->SetLogy();
  //HigCutMass->Draw(myCan,kTRUE,"png");
  
  HigCutEt->setOutDir(OutDir);
  HigCutEt->AddHist1D(Sig_Hig_CutEt,"l",kBlack);
  HigCutEt->SetLegend(0.6,0.7,0.9,0.8);
  HigCutEt->GetLegend()->AddEntry(Sig_Hig_CutEt,"H #rightarrow WW","l");
  HigCutEt->SetLogy();
  HigCutEt->Draw(myCan,kTRUE,"png");
  
  DiLeptMass->setOutDir(OutDir);
  DiLeptMass->AddHist1D(Sig_ElMu_Mass,"l",kBlack);
  //DiLeptMass->AddLine(140, 0.0, 140, 1.2*Sig_ElMu_Mass->GetMaximum(),kRed,2);
  //DiLeptMass->AddLine(300, 0.0, 300, 1.2*Sig_ElMu_Mass->GetMaximum(),kBlue,2);
  DiLeptMass->SetLegend(0.6,0.7,0.9,0.8);
  DiLeptMass->GetLegend()->AddEntry(Sig_ElMu_Mass,"H #rightarrow WW","l");
  DiLeptMass->SetLogy();
  DiLeptMass->Draw(myCan,kTRUE,"png");

  MET->setOutDir(OutDir);
  MET->AddHist1D(hMET,"l",kBlack);
  MET->SetLegend(0.6,0.7,0.9,0.8);
  MET->GetLegend()->AddEntry(hMET,"H #rightarrow WW","l");
  MET->SetLogy();
  MET->Draw(myCan,kTRUE,"png");

  mpMET->setOutDir(OutDir);
  mpMET->AddHist1D(hmpMET,"l",kBlack);
  mpMET->SetLegend(0.6,0.7,0.9,0.8);
  mpMET->GetLegend()->AddEntry(hmpMET,"H #rightarrow WW","l");
  mpMET->SetLogy();
  mpMET->Draw(myCan,kTRUE,"png");

  Dphill->setOutDir(OutDir);
  Dphill->AddHist1D(hdphill,"l",kBlack);
  Dphill->SetLegend(0.6,0.7,0.9,0.8);
  Dphill->GetLegend()->AddEntry(hdphill,"H #rightarrow WW","l");
  Dphill->SetLogy();
  Dphill->Draw(myCan,kTRUE,"png");

  return 0;
}
