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

    double mWW = CalcmWW();
    //if(mWW <= 130.) continue;

    EvtWeight = CalcWeight();
    //cout<<"EvtWeight: "<<EvtWeight<<endl;

    if( Cut == "LooseCut") if(LooseCut()  !=1)continue;
    if( Cut == "CommonCut")if(CommonCut() !=1)continue;
    if( Cut == "CommonCut_njet")if(CommonCut_njet() !=1)continue;
    //if( Cut == "CommonCut_OnShell")if(CommonCut_OnShell() !=1)continue;
    //if( Cut == "CommonCut_OffShell")if(CommonCut_OffShell() !=1)continue;
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
  if ((ch1*ch2 ==-1.) )
  //if ((ch1*ch2 ==-1.) && !sameflav)
  {
    h1_pupMet[3] -> Fill(pupmet, EvtWeight);
    h1_genMet[3] -> Fill(metGenpt, EvtWeight);
    h1_pfMet[3]  -> Fill(pfmet, EvtWeight);
    h1_trkMet[3] -> Fill(trkmet, EvtWeight);
    h2_pup_gen_MetResol[3]->Fill(metGenpt,(pupmet-metGenpt)/metGenpt,EvtWeight);
    h2_pf_gen_MetResol[3] ->Fill(metGenpt,(pfmet-metGenpt)/metGenpt, EvtWeight);
    h2_trk_gen_MetResol[3]->Fill(metGenpt,(trkmet-metGenpt)/metGenpt, EvtWeight);
    if(njet==0)
    {
      h1_pupMet[0] -> Fill(pupmet, EvtWeight);
      h1_genMet[0] -> Fill(metGenpt, EvtWeight);
      h1_pfMet[0]  -> Fill(pfmet, EvtWeight);
      h1_trkMet[0] -> Fill(trkmet, EvtWeight);
      h2_pup_gen_MetResol[0]->Fill(metGenpt,(pupmet-metGenpt)/metGenpt,EvtWeight);
      h2_pf_gen_MetResol[0] ->Fill(metGenpt,(pfmet-metGenpt)/metGenpt, EvtWeight);
      h2_trk_gen_MetResol[0]->Fill(metGenpt,(trkmet-metGenpt)/metGenpt, EvtWeight);
    }
    if(njet==1)
    {
      h1_pupMet[1] -> Fill(pupmet, EvtWeight);
      h1_genMet[1] -> Fill(metGenpt, EvtWeight);
      h1_pfMet[1]  -> Fill(pfmet, EvtWeight);
      h1_trkMet[1] -> Fill(trkmet, EvtWeight);
      h2_pup_gen_MetResol[1]->Fill(metGenpt,(pupmet-metGenpt)/metGenpt,EvtWeight);
      h2_pf_gen_MetResol[1] ->Fill(metGenpt,(pfmet-metGenpt)/metGenpt, EvtWeight);
      h2_trk_gen_MetResol[1]->Fill(metGenpt,(trkmet-metGenpt)/metGenpt,EvtWeight);
    }
    if(njet>=2)
    {
      h1_pupMet[2] -> Fill(pupmet, EvtWeight);
      h1_genMet[2] -> Fill(metGenpt,EvtWeight);
      h1_pfMet[2]  -> Fill(pfmet, EvtWeight);
      h1_trkMet[2] -> Fill(trkmet, EvtWeight);
      h2_pup_gen_MetResol[2]->Fill(metGenpt,(pupmet-metGenpt)/metGenpt,EvtWeight);
      h2_pf_gen_MetResol[2] ->Fill(metGenpt,(pfmet-metGenpt)/metGenpt, EvtWeight);
      h2_trk_gen_MetResol[2]->Fill(metGenpt,(trkmet-metGenpt)/metGenpt, EvtWeight);
    }
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
    sprintf(histName, "h1_genMet_%d",i);
    h1_genMet[i] = new TH1D(histName,"genMET", 50, 0, 120);
    
    sprintf(histName, "h1_pupMet_%d",i);
    h1_pupMet[i] = new TH1D(histName,"pupMET", 50, 0, 120);
    
    sprintf(histName, "h1_pfMet_%d",i);
    h1_pfMet[i] = new TH1D(histName,"pfMET", 50, 0, 120);

    sprintf(histName, "h1_trkMet_%d",i);
    h1_trkMet[i] = new TH1D(histName,"trkMet", 50, 0, 120);
    
    sprintf(histName, "h2_pup_gen_MetResol_%d",i);
    h2_pup_gen_MetResol[i] = new TH2D(histName,"(pup-gen)/gen", 50,0,120,50,-10,20);
    
    sprintf(histName, "h2_pf_gen_MetResol_%d",i);
    h2_pf_gen_MetResol[i] = new TH2D(histName,"(pf-gen)/gen", 50,0,120,50,-10,20);
     
    sprintf(histName, "h2_trk_gen_MetResol_%d",i);
    h2_trk_gen_MetResol[i] = new TH2D(histName,"(trk-gen)/gen", 50,0,120,50,-10,20);
  }

  return 0;
}

int Write_Histo()
{
  return 0;
}
