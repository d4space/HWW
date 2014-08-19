#include <TProfile.h>
#include "../../Utils/const.h"
#include "../../Utils/CPlot.hh"
#include "../../Utils/MitStyleRemix.hh"

// Hw1
#define Hw1SigXsec 17.9978 //fb
#define Hw1IntXsec 32.2422 //fb
#define Hw1CotXsec 16.5574 //fb

// Hw25
#define Hw25SigXsec 28.3501 //fb
#define Hw25IntXsec 37.2656 //fb
#define Hw25CotXsec 16.5574 //fb

int CtrPlotsIntOnly(TString BaseName, TString CutName)
{
  TString OutDir = "CtrPlots_mH_mtH_Interference";
  gSystem->mkdir(OutDir);

  TString fSig;
  TString fInt;
  TString fCot;
  
  if(BaseName=="Hw1gg2vv8TeV")
  {
    fSig = "Hw1Sig8TeV/CtrPlt.root";
    fInt = "Hw1Int8TeV/CtrPlt.root";
    fCot = "Hw1Cot8TeV/CtrPlt.root";
  }

  if(BaseName=="Hw25gg2vv8TeV")
  {
    fSig = "Hw25Sig8TeV/CtrPlt.root";
    fInt = "Hw25Int8TeV/CtrPlt.root";
    fCot = "Hw25Cot8TeV/CtrPlt.root";
  }

  TFile *fname[3];
  fname[0] = new TFile(fSig);
  fname[1] = new TFile(fInt);
  fname[2] = new TFile(fCot);

  char tmpName[50];
  char histName[50];

  //Histograms
  TH1D* h_mH[3];
  TH1D* h_mtH[3];
  TH1D* h_mH_mllCut[3];
  TH1D* h_mtH_mllCut[3];

  TH1D* h_mH_IntOnly;
  TH1D* h_mtH_IntOnly;
  TH1D* h_mH_mllCut_IntOnly;
  TH1D* h_mtH_mllCut_IntOnly;

  double LumiWeight[3];
  
  if(BaseName=="Hw1gg2vv8TeV")
  {
    LumiWeight[0] = 3998353./Hw1SigXsec;
    LumiWeight[1] = 3999076./Hw1IntXsec;
    LumiWeight[2] = 4000000./Hw1CotXsec;
  }

  if(BaseName=="Hw25gg2vv8TeV")
  {
    LumiWeight[0] = 3998986./Hw25SigXsec;
    LumiWeight[1] = 3999219./Hw25IntXsec;
    LumiWeight[2] = 4000000./Hw25CotXsec;
  }
  
  TCanvas *myCan = MakeCanvas("myCan", "myCan", 900, 800);
  
  for(int i(0);i<3;i++)
  {
    if(CutName=="NoCut")
    {
      sprintf(tmpName,"h_mH_%d",i);         h_mH[i]         = (TH1D*)fname[i]->Get("hNoCut_Hig_mass")->Clone(tmpName);
      sprintf(tmpName,"h_mtH_%d",i);        h_mtH[i]        = (TH1D*)fname[i]->Get("hNoCut_HigT_mass")->Clone(tmpName);
      sprintf(tmpName,"h_mH_mllCut_%d",i);  h_mH_mllCut[i]  = (TH1D*)fname[i]->Get("hNoCut_Hig_mass_mllCut")->Clone(tmpName);
      sprintf(tmpName,"h_mtH_mllCut_%d",i); h_mtH_mllCut[i] = (TH1D*)fname[i]->Get("hNoCut_HigT_mass_mllCut")->Clone(tmpName);
    }
  
    if(CutName=="CommonCut")
    {
      sprintf(tmpName,"h_mH_%d",i);         h_mH[i]         = (TH1D*)fname[i]->Get("h_Hig_mass")->Clone(tmpName);
      sprintf(tmpName,"h_mtH_%d",i);        h_mtH[i]        = (TH1D*)fname[i]->Get("h_HigT_mass")->Clone(tmpName);
      sprintf(tmpName,"h_mH_mllCut_%d",i);  h_mH_mllCut[i]  = (TH1D*)fname[i]->Get("h_Hig_mass_mllCut")->Clone(tmpName);
      sprintf(tmpName,"h_mtH_mllCut_%d",i); h_mtH_mllCut[i] = (TH1D*)fname[i]->Get("h_HigT_mass_mllCut")->Clone(tmpName);
    }
  
    // Normalize to 8 TeV total Data
    h_mH[i]         -> Sumw2();
    h_mtH[i]        -> Sumw2();
    h_mH_mllCut[i]  -> Sumw2();
    h_mtH_mllCut[i] -> Sumw2();
    h_mH[i]         -> Scale(LumiTotal8TeV/LumiWeight[i]);
    h_mtH[i]        -> Scale(LumiTotal8TeV/LumiWeight[i]);
    h_mH_mllCut[i]  -> Scale(LumiTotal8TeV/LumiWeight[i]);
    h_mtH_mllCut[i] -> Scale(LumiTotal8TeV/LumiWeight[i]);
  }

  //Save Histograms to file
  if(CutName=="CommonCut" || CutName=="NoCut")
  {
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mH[0]->GetBinWidth(1));
    sprintf(histName,"mH_"+CutName);
    CPlot* Plot_mH    = new CPlot(histName,"","m_{H} [GeV/c^{2}]",tmpName);
    Plot_mH->setOutDir(OutDir);
    Plot_mH->AddHist1D(h_mH[0],"H",kRed);
    Plot_mH->AddHist1D(h_mH[1],"H",kBlue);
    Plot_mH->AddHist1D(h_mH[2],"H",kGreen);
    //Plot_mH->AddLine(140,0,140,1.2*h_mH[0]->GetMaximum(),kBlack,2);
    //Plot_mH->AddLine(300,0,300,1.2*h_mH[0]->GetMaximum(),kBlack,2);
    Plot_mH->SetLegend(0.55,0.8,0.85,0.9);
    if(BaseName=="Hw1gg2vv8TeV")
    {
      Plot_mH->GetLegend()->AddEntry(h_mH[0],"Hw1Sig8TeV","l");
      //Plot_mH->GetLegend()->AddEntry(h_mH[1],"Hw1Int8TeV","l");
      Plot_mH->GetLegend()->AddEntry(h_mH[1],"Hw1SigBckgr8TeV","l");
      Plot_mH->GetLegend()->AddEntry(h_mH[2],"Hw1Cot8TeV","l");
    }
    if(BaseName=="Hw25gg2vv8TeV")
    {
      Plot_mH->GetLegend()->AddEntry(h_mH[0],"Hw25Sig8TeV","l");
      //Plot_mH->GetLegend()->AddEntry(h_mH[1],"Hw25Int8TeV","l");
      Plot_mH->GetLegend()->AddEntry(h_mH[1],"Hw25SigBckgr8TeV","l");
      Plot_mH->GetLegend()->AddEntry(h_mH[2],"Hw25Cot8TeV","l");
    }
    Plot_mH->SetLogy();
    Plot_mH->Draw(myCan,kTRUE,"png");
    
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mtH[0]->GetBinWidth(1));
    sprintf(histName,"mtH_"+CutName);
    CPlot* Plot_mtH   = new CPlot(histName,"","m_{T}^{H} [Gev/c^{2}]",tmpName);
    Plot_mtH->setOutDir(OutDir);
    Plot_mtH->AddHist1D(h_mtH[0],"H",kRed);
    Plot_mtH->AddHist1D(h_mtH[1],"H",kBlue);
    Plot_mtH->AddHist1D(h_mtH[2],"H",kGreen);
    Plot_mtH->SetLegend(0.55,0.8,0.85,0.9);
    if(BaseName=="Hw1gg2vv8TeV")
    {
      Plot_mtH->GetLegend()->AddEntry(h_mtH[0],"Hw1Sig8TeV","l");
      //Plot_mtH->GetLegend()->AddEntry(h_mtH[1],"Hw1Int8TeV","l");
      Plot_mtH->GetLegend()->AddEntry(h_mtH[1],"Hw1SigBckgr8TeV","l");
      Plot_mtH->GetLegend()->AddEntry(h_mtH[2],"Hw1Cot8TeV","l");
    }
    if(BaseName=="Hw25gg2vv8TeV")
    {
      Plot_mtH->GetLegend()->AddEntry(h_mtH[0],"Hw25Sig8TeV","l");
      //Plot_mtH->GetLegend()->AddEntry(h_mtH[1],"Hw25Int8TeV","l");
      Plot_mtH->GetLegend()->AddEntry(h_mtH[1],"Hw25SigBckgr8TeV","l");
      Plot_mtH->GetLegend()->AddEntry(h_mtH[2],"Hw25Cot8TeV","l");
    }
    Plot_mtH->SetLogy();
    Plot_mtH->Draw(myCan,kTRUE,"png");
    
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mH_mllCut[0]->GetBinWidth(1));
    sprintf(histName,"mH_mllCut_"+CutName);
    if(CutName=="NoCut")
      sprintf(histName,"mH_mllCut");
    CPlot* Plot_mH_mllCut    = new CPlot(histName,"","m_{H} [GeV/c^{2}]",tmpName);
    Plot_mH_mllCut->setOutDir(OutDir);
    Plot_mH_mllCut->AddHist1D(h_mH_mllCut[0],"H",kRed);
    Plot_mH_mllCut->AddHist1D(h_mH_mllCut[1],"H",kBlue);
    Plot_mH_mllCut->AddHist1D(h_mH_mllCut[2],"H",kGreen);
    //Plot_mH_mllCut->AddLine(140,0,140,1.2*h_mH_mllCut[0]->GetMaximum(),kBlack,2);
    //Plot_mH_mllCut->AddLine(300,0,300,1.2*h_mH_mllCut[0]->GetMaximum(),kBlack,2);
    Plot_mH_mllCut->SetLegend(0.55,0.8,0.85,0.9);
    if(BaseName=="Hw1gg2vv8TeV")
    {
      Plot_mH_mllCut->GetLegend()->AddEntry(h_mH_mllCut[0],"Hw1Sig8TeV","l");
      //Plot_mH_mllCut->GetLegend()->AddEntry(h_mH_mllCut[1],"Hw1Int8TeV","l");
      Plot_mH_mllCut->GetLegend()->AddEntry(h_mH_mllCut[1],"Hw1SigBckgr8TeV","l");
      Plot_mH_mllCut->GetLegend()->AddEntry(h_mH_mllCut[2],"Hw1Cot8TeV","l");
    }
    if(BaseName=="Hw25gg2vv8TeV")
    {
      Plot_mH_mllCut->GetLegend()->AddEntry(h_mH_mllCut[0],"Hw25Sig8TeV","l");
      //Plot_mH_mllCut->GetLegend()->AddEntry(h_mH_mllCut[1],"Hw25Int8TeV","l");
      Plot_mH_mllCut->GetLegend()->AddEntry(h_mH_mllCut[1],"Hw25SigBckgr8TeV","l");
      Plot_mH_mllCut->GetLegend()->AddEntry(h_mH_mllCut[2],"Hw25Cot8TeV","l");
    }
    Plot_mH_mllCut->SetLogy();
    Plot_mH_mllCut->Draw(myCan,kTRUE,"png");
    
    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mtH_mllCut[0]->GetBinWidth(1));
    sprintf(histName,"mtH_mllCut_"+CutName);
    if(CutName=="NoCut")
      sprintf(histName,"mtH_mllCut");
    CPlot* Plot_mtH_mllCut   = new CPlot(histName,"","m_{T}^{H} [Gev/c^{2}]",tmpName);
    Plot_mtH_mllCut->setOutDir(OutDir);
    Plot_mtH_mllCut->AddHist1D(h_mtH_mllCut[0],"H",kRed);
    Plot_mtH_mllCut->AddHist1D(h_mtH_mllCut[1],"H",kBlue);
    Plot_mtH_mllCut->AddHist1D(h_mtH_mllCut[2],"H",kGreen);
    Plot_mtH_mllCut->SetLegend(0.55,0.8,0.85,0.9);
    if(BaseName=="Hw1gg2vv8TeV")
    {
      Plot_mtH_mllCut->GetLegend()->AddEntry(h_mtH_mllCut[0],"Hw1Sig8TeV","l");
      //Plot_mtH_mllCut->GetLegend()->AddEntry(h_mtH_mllCut[1],"Hw1Int8TeV","l");
      Plot_mtH_mllCut->GetLegend()->AddEntry(h_mtH_mllCut[1],"Hw1SigBckgr8TeV","l");
      Plot_mtH_mllCut->GetLegend()->AddEntry(h_mtH_mllCut[2],"Hw1Cot8TeV","l");
    }
    if(BaseName=="Hw25gg2vv8TeV")
    {
      Plot_mtH_mllCut->GetLegend()->AddEntry(h_mtH_mllCut[0],"Hw25Sig8TeV","l");
      //Plot_mtH_mllCut->GetLegend()->AddEntry(h_mtH_mllCut[1],"Hw25Int8TeV","l");
      Plot_mtH_mllCut->GetLegend()->AddEntry(h_mtH_mllCut[1],"Hw25SigBckgr8TeV","l");
      Plot_mtH_mllCut->GetLegend()->AddEntry(h_mtH_mllCut[2],"Hw25Cot8TeV","l");
    }
    Plot_mtH_mllCut->SetLogy();
    Plot_mtH_mllCut->Draw(myCan,kTRUE,"png");

    //Interference = Int(SigBckgr)-(Sig+Bckgr)
    h_mH_IntOnly = (TH1D*)h_mH[1]->Clone("h_mH_IntOnly");
    h_mH_IntOnly->Add(h_mH[0],-1.);
    h_mH_IntOnly->Add(h_mH[2],-1.);

    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mH_IntOnly->GetBinWidth(1));
    sprintf(histName,"mH_Interference_"+CutName);
    CPlot* Plot_mH_Int  = new CPlot(histName,"","m_{H} [GeV/c^{2}]",tmpName);
    Plot_mH_Int->setOutDir(OutDir);
    Plot_mH_Int->AddHist1D(h_mH_IntOnly,"E1",kBlack);
    Plot_mH_Int->SetLegend(0.6,0.2,0.9,0.3);
    if(BaseName=="Hw1gg2vv8TeV")
      Plot_mH_Int->GetLegend()->AddEntry(h_mH_IntOnly,"Hw1Int8TeV","PL");
    if(BaseName=="Hw25gg2vv8TeV")
      Plot_mH_Int->GetLegend()->AddEntry(h_mH_IntOnly,"Hw25Int8TeV","PL");
    //Plot_mH_Int->SetLogy();
    Plot_mH_Int->Draw(myCan,kTRUE,"png");

    h_mtH_IntOnly = (TH1D*)h_mtH[1]->Clone("h_mtH_IntOnly");
    h_mtH_IntOnly->Add(h_mtH[0],-1.);
    h_mtH_IntOnly->Add(h_mtH[2],-1.);

    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mtH_IntOnly->GetBinWidth(1));
    sprintf(histName,"mtH_Interference_"+CutName);
    CPlot* Plot_mtH_Int  = new CPlot(histName,"","m_{H} [GeV/c^{2}]",tmpName);
    Plot_mtH_Int->setOutDir(OutDir);
    Plot_mtH_Int->AddHist1D(h_mtH_IntOnly,"E1",kBlack);
    Plot_mtH_Int->SetLegend(0.6,0.2,0.9,0.3);
    if(BaseName=="Hw1gg2vv8TeV")
      Plot_mtH_Int->GetLegend()->AddEntry(h_mtH_IntOnly,"Hw1Int8TeV","PL");
    if(BaseName=="Hw25gg2vv8TeV")
      Plot_mtH_Int->GetLegend()->AddEntry(h_mtH_IntOnly,"Hw25Int8TeV","PL");
    //Plot_mtH_Int->SetLogy();
    Plot_mtH_Int->Draw(myCan,kTRUE,"png");

    h_mH_mllCut_IntOnly = (TH1D*)h_mH_mllCut[1]->Clone("h_mH_mllCut_IntOnly");
    h_mH_mllCut_IntOnly->Add(h_mH_mllCut[0],-1.);
    h_mH_mllCut_IntOnly->Add(h_mH_mllCut[2],-1.);

    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mH_mllCut_IntOnly->GetBinWidth(1));
    sprintf(histName,"mH_Interference_mllCut_"+CutName);
    if(CutName=="NoCut")
      sprintf(histName,"mH_Interference_mllCut");
    CPlot* Plot_mH_mllCut_Int  = new CPlot(histName,"","m_{H} [GeV/c^{2}]",tmpName);
    Plot_mH_mllCut_Int->setOutDir(OutDir);
    Plot_mH_mllCut_Int->AddHist1D(h_mH_mllCut_IntOnly,"E1",kBlack);
    Plot_mH_mllCut_Int->SetLegend(0.6,0.2,0.9,0.3);
    if(BaseName=="Hw1gg2vv8TeV")
      Plot_mH_mllCut_Int->GetLegend()->AddEntry(h_mH_mllCut_IntOnly,"Hw1Int8TeV","PL");
    if(BaseName=="Hw25gg2vv8TeV")
      Plot_mH_mllCut_Int->GetLegend()->AddEntry(h_mH_mllCut_IntOnly,"Hw25Int8TeV","PL");
    //Plot_mH_mllCut_Int->SetLogy();
    Plot_mH_mllCut_Int->Draw(myCan,kTRUE,"png");

    h_mtH_mllCut_IntOnly = (TH1D*)h_mtH_mllCut[1]->Clone("h_mtH_mllCut_IntOnly");
    h_mtH_mllCut_IntOnly->Add(h_mtH_mllCut[0],-1.);
    h_mtH_mllCut_IntOnly->Add(h_mtH_mllCut[2],-1.);

    sprintf(tmpName,"Events / %.1f GeV/c^{2}",h_mtH_mllCut_IntOnly->GetBinWidth(1));
    sprintf(histName,"mtH_Interference_mllCut_"+CutName);
    if(CutName=="NoCut")
      sprintf(histName,"mtH_Interference_mllCut");
    CPlot* Plot_mtH_mllCut_Int  = new CPlot(histName,"","m_{H} [GeV/c^{2}]",tmpName);
    Plot_mtH_mllCut_Int->setOutDir(OutDir);
    Plot_mtH_mllCut_Int->AddHist1D(h_mtH_mllCut_IntOnly,"E1",kBlack);
    Plot_mtH_mllCut_Int->SetLegend(0.6,0.2,0.9,0.3);
    if(BaseName=="Hw1gg2vv8TeV")
      Plot_mtH_mllCut_Int->GetLegend()->AddEntry(h_mtH_mllCut_IntOnly,"Hw1Int8TeV","PL");
    if(BaseName=="Hw25gg2vv8TeV")
      Plot_mtH_mllCut_Int->GetLegend()->AddEntry(h_mtH_mllCut_IntOnly,"Hw25Int8TeV","PL");
    //Plot_mtH_mllCut_Int->SetLogy();
    Plot_mtH_mllCut_Int->Draw(myCan,kTRUE,"png");
  }
  
  return 0;
}
