#define HWwCtrPlt_cxx
#include "HWwCtrPlt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include <algorithm>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

void HWwCtrPlt::Loop()
{
  gBenchmark->Start("HWwCtrPlt");
  if (fChain == 0) return;

  int Ntries = fChain->GetEntries();
  cout<<"Total: "<<Ntries<<endl;
  cout<<"LumiW: "<<LumiW<<endl;
  
  for (int i(0); i<Ntries;i++)
  {
    InitVar4Evt();
    evtCnt++;
    fChain->GetEntry(i);
    //cout<<"channel: "<<channel<<endl;
    // NT already applied loose cuts
    // select channel
    if (SF0jCut() == 1)     myChannel = An_sf0j;
    else if (DF0jCut() == 1)myChannel = An_of0j;
    else if (SF1jCut() == 1)myChannel = An_sf1j;
    else if (DF1jCut() == 1)myChannel = An_of1j;
    else continue;

    if( Cut == "Tight")if(CommonCut() !=1)continue;
    CalcWeight();
    Fill_Histo();

  }
  // Usie one of the Write_Histo ro myFile->Write
  // Write_Histo: to write specific ones
  // myFile->Write ==> All
    
  //Write_Histo();
  myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("HWwCtrPlt");
}
int HWwCtrPlt::Fill_Histo()
{

  h1_channel[myChannel]->Fill(channel, EvtWeight);
  h1_mll[myChannel]->Fill(mll, EvtWeight);
  h1_dphill[myChannel]->Fill(180./PI*fabs(dphill), EvtWeight);
  h1_mth[myChannel]->Fill(mth, EvtWeight);

  return 0;
}
int HWwCtrPlt::InitVar()
{
  TString FoutName = mResultDir+"/"+SampleName+"_"+Cut+".txt";
  Fout.open(FoutName);
  evtCnt = 0;
  return 0;
}
int HWwCtrPlt::InitVar4Evt()
{
  return 0;
}
int HWwCtrPlt::InitHistogram()
{
  myFile = new TFile(mResultDir+"/"+SampleName+"_"+Cut+".root","RECREATE");
  char histName[30];
  for(int i(0); i<4; i++)
  {
    sprintf(histName, "h1_channel_%d",i);
    h1_channel[i] = new TH1D(histName,"channel", 4, 0, 4);
    sprintf(histName, "h1_mll_%d",i);
    h1_mll[i] = new TH1D(histName,"Dilepton mass", 30, 0, 300);
    sprintf(histName,"h1_dphill_%d",i);
    h1_dphill[i] = new TH1D(histName,"Dileptom dphi",18,0,180);
    sprintf(histName,"h1_mth_%d",i);
    h1_mth[i] = new TH1D(histName,"Transverse higs mass",25,0,300);
  }
  
  return 0;
}
int Write_Histo()
{
  return 0;
}
