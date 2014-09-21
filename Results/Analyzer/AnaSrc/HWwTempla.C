#define HWwTempla_cxx
#include "HWwTempla.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include <algorithm>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

void HWwTempla::Loop()
{
  gBenchmark->Start("HWwTempla");
  if (fChain == 0) return;

  int Ntries = fChain->GetEntries();
  cout<<"Total: "<<Ntries<<endl;
  cout<<"LumiW: "<<LumiW<<endl;
 
  cout<<"Arg Channel: "<<argChannel<<endl;
  for (int i(0); i<Ntries;i++)
  {
    InitVar4Evt();
    evtCnt++;
    fChain->GetEntry(i);

  
    // For all channel option, check channel and save to myChannel
    if(argChannel == 100){// all
      if (SF0jCut() == 1)     myChannel = AC_sf0j;
      else if (OF0jCut() == 1)myChannel = AC_of0j;
      else if (SF1jCut() == 1)myChannel = AC_sf1j;
      else if (OF1jCut() == 1)myChannel = AC_of1j;
      else continue;
    }else{ myChannel = argChannel;}

    // For single channel option, check Channel
    if(argChannel == AC_sf0j)if(SF0jCut() != 1) continue;
    if(argChannel == AC_of0j)if(OF0jCut() != 1) continue;
    if(argChannel == AC_sf1j)if(SF1jCut() != 1) continue;
    if(argChannel == AC_of1j)if(OF1jCut() != 1) continue;

    if( Cut == "Tight")if(CommonCut() !=1)continue;

    EvtWeight = CalcWeight();
    ScaleF = ScaleFactor();
    Fill_Histo();

  }

  // Usie one of the Write_Histo ro myFile->Write
  // Write_Histo: to write specific ones
  // myFile->Write ==> All
    
  //Write_Histo();
  myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("HWwTempla");
}

int HWwTempla::InitVar()
{
  TString FoutName = mResultDir+"/"+SampleName+"_"+Cut+".txt";
  Fout.open(FoutName);
  evtCnt = 0;
  return 0;
}
int HWwTempla::InitVar4Evt()
{
  return 0;
}
int HWwTempla::Fill_Histo()
{
  h1_mll[myChannel]->Fill(mll, EvtWeight*ScaleF);
  return 0;
}
int HWwTempla::InitHistogram()
{
  myFile = new TFile(mResultDir+"/"+SampleName+"_"+Cut+".root","RECREATE");
  char histName[30];
  for(int i(0); i<4; i++)
  {
    sprintf(histName, "h1_mll_%d",i);
    h1_mll[i] = new TH1D(histName,"Dilepton mass", 30, 0, 300);
  }
  
  return 0;
}
int Write_Histo()
{
  return 0;
}
