#define HWwMET_cxx
#include "HWwMET.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include <algorithm>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

void HWwMET::Loop()
{
  gBenchmark->Start("HWwMET");
  if (fChain == 0) return;

  int Ntries = fChain->GetEntries();
  cout<<"Total: "<<Ntries<<endl;
  Fout<<"Total: "<<Ntries<<endl;
  cout<<"LumiW: "<<LumiW<<endl;
  Fout<<"LumiW: "<<LumiW<<endl;
  
  for (int i(0); i<Ntries;i++)
  {
    InitVar4Evt();
    evtCnt++;
    fChain->GetEntry(i);

    mWW = CalcmWW();
    //if(mWW <= 130.) continue;

    EvtWeight = CalcWeight();

    if( Cut == "LooseCut") if(LooseCut()  !=1)continue;
    if( Cut == "CommonCut")if(CommonCut() !=1)continue;
    if( Cut == "CommonCut_njet")if(CommonCut_njet() !=1)continue;
    if( Cut == "CommonCut_OnShell")if(CommonCut_OnShell() !=1)continue;
    if( Cut == "CommonCut_OffShell")if(CommonCut_OffShell() !=1)continue;
    if( Cut == "SignalCutV1")if(SignalCutV1() !=1)continue;
    if( Cut == "SignalCutV2")if(SignalCutV2() !=1)continue;
    if( Cut == "SignalCutV3")if(SignalCutV3() !=1)continue;
    Nselect[0] += EvtWeight;

    Fill_Histo();
  }
  Fout<<"Nselected: "<<Nselect[0]<<endl;

  // Usie one of the Write_Histo ro myFile->Write
  // Write_Histo: to write specific ones
  // myFile->Write ==> All
    
  //Write_Histo();
  myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("HWwMET");
}

int HWwMET::Fill_Histo()
{
  if ((ch1*ch2 ==-1.) && !sameflav)
  {
    h1_pupmet[3]   -> Fill(pupmet, EvtWeight);
    if(njet==0)
      h1_pupmet[0] -> Fill(pupmet, EvtWeight);
    if(njet==1)
      h1_pupmet[1] -> Fill(pupmet, EvtWeight);
    if(njet>=2)
      h1_pupmet[2] -> Fill(pupmet, EvtWeight);
  }

  return 0;
}

int HWwMET::InitVar()
{
  TString FoutName = mResultDir+"/"+SampleName+"_"+Cut+".txt";
  Fout.open(FoutName);
  evtCnt = 0;

  return 0;
}
int HWwMET::InitVar4Evt()
{
  return 0;
}
int HWwMET::InitHistogram()
{
  myFile = new TFile(mResultDir+"/"+SampleName+"_"+Cut+".root","RECREATE");
  char histName[30];

  for(int i(0); i<4; i++)
  {
    sprintf(histName, "h1_pupmet_%d",i);
    h1_pupmet[i] = new TH1D(histName,"PupMET", 15, 0, 150);
  }

  return 0;
}

int Write_Histo()
{
  return 0;
}
