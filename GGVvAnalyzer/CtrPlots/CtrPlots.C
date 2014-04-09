#include "../Utils/const.h"
#include "../Utils/CPlot.hh"
#include "../Utils/MitStyleRemix.hh"

#define SigXsec 29.5*16 //fb
#define CotXsec 16.6*16 //fb
#define IntXsec 38.3*16 //fb

#define Nevt 25000*16

int CtrPlots()
{
  TString OutDir = "CtrPlots";
  //TString OutDir = "CtrPlotsOffPeak";
  gSystem->mkdir(OutDir);

  TFile *f_Sig, *f_Cot, *f_Int;
  TH1D* Sig_Hig_Mass;
  TH1D* Cot_Hig_Mass;
  TH1D* Int_Hig_Mass;
  double SigLumi = Nevt/SigXsec;
  double CotLumi = Nevt/CotXsec;
  double IntLumi = Nevt/IntXsec;

  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  CPlot* HigMass= new CPlot("HiggsMass","","mass (emu2nu)","xsec [fb]");
  f_Sig = new TFile("SigHw25RoScMiCut/CtrPlt.root");
  //f_Sig = new TFile("SigHw25RoScMiCutOffPeak/CtrPlt.root");
  Sig_Hig_Mass	=(TH1D*)f_Sig->Get("hHig_Mass")->Clone();
  f_Cot = new TFile("CotHw25RoScMiCut/CtrPlt.root");
  Cot_Hig_Mass	=(TH1D*)f_Cot->Get("hHig_Mass")->Clone();
  f_Int = new TFile("IntHw25RoScMiCut/CtrPlt.root");
  //f_Int = new TFile("IntHw25RoScMiCutOffPeak/CtrPlt.root");
  Int_Hig_Mass	=(TH1D*)f_Int->Get("hHig_Mass")->Clone();
  Sig_Hig_Mass->Scale(1/SigLumi); // Xsec
  Cot_Hig_Mass->Scale(1/CotLumi);
  Int_Hig_Mass->Scale(1/IntLumi);

  int binMin = Sig_Hig_Mass->GetMinimumBin();
  double x = Sig_Hig_Mass->GetXaxis()->GetBinCenter(binMin);

  HigMass->setOutDir(OutDir);
  HigMass->AddHist1D(Sig_Hig_Mass,"l",kBlue);
  HigMass->AddHist1D(Cot_Hig_Mass,"l",kRed);
  HigMass->AddHist1D(Int_Hig_Mass,"l",kGreen);
  HigMass->AddLine(140, 0.0, 140, 0.6);
  HigMass->AddLine(300, 0.0, 300, 0.6);
  HigMass->SetLegend(0.6,0.7,0.9,0.8);
  HigMass->GetLegend()->AddEntry(Sig_Hig_Mass,"H #rightarrow WW","l");
  HigMass->GetLegend()->AddEntry(Cot_Hig_Mass,"gg #rightarrow WW","l");
  HigMass->GetLegend()->AddEntry(Int_Hig_Mass,"H(WW) + gg(WW)","l");
  HigMass->SetLogy();
  //HigMass->SetLogx();
  HigMass->Draw(myCan,kTRUE,"png");

  return 0;
}
