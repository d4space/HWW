#define HWwNjetStudy_cxx
#include "HWwNjetStudy.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include <algorithm>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

void HWwNjetStudy::Loop()
{
  gBenchmark->Start("HWwNjetStudy");
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
    //=================================================
    // Calculation of Weight============================
    //=================================================

    if(SampleName == "POWHEG" || SampleName == "POWHEG_VBF")
    {
      //mWW = MHiggs; // Activate mWW at HWwBase.h
    }
    if(SampleName == "SHERPA")mWW = CalcmWW();

    if(mWW <= 130.) continue;

    EvtWeight = CalcWeight();
    
    if(SampleName == "POWHEG") Calc_Pow_Weight();
    if(SampleName == "POWHEG_VBF") Calc_Pow_Vbf_Weight();
    //====================================================
    // number of Jet 
    //====================================================
    nnjet = njet;
    if(njet>=NjetBin-1) nnjet = NjetBin-1;

    if(njet>=2 && njet<=3){;}else continue;
    if(CommonCut_njet() !=1)continue;
    Fill_BeforeCut();
    //====================================================
    //Cuts 
    //====================================================

    if( Cut == "CommonCut_njet")if(CommonCut_njet() !=1)continue;
    if( Cut == "CommonCut_VBFnjet")if(CommonCut_VBFnjet() !=1)continue;
    if( Cut == "CommonCut_VBf_NoVetoCentralJet")if(CommonCut_VBf_NoVetoCentralJet() !=1)continue;
    if(mWW<130) continue;

    // Fill Histogram ===========
    Fill_Histo();
  }
  // Usie one of the Write_Histo ro myFile->Write
  // Write_Histo: to write specific ones
  // myFile->Write ==> All
    
  //Write_Histo();
  myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("HWwNjetStudy");
}

