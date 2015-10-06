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

#include "NjetBin.h"

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
    if( i%100000 == 0)cout<<"processing: "<<i<<"th event"<<endl;
    InitVar4Evt();
    evtCnt++;
    fChain->GetEntry(i);
    //=================================================
    // Calculation of Weight============================
    //=================================================

    if(SampleName == "POWHEG" || SampleName == "POWHEG_VBF")
    {
#if SAMPLE == 3
      mWW = MHiggs; 
#endif
#if SAMPLE == 1
      mWW = MHiggs; 
#endif
    }
    if(SampleName == "SHERPA")mWW = CalcmWW();

    //if(mWW <= 130.+13) continue;
    if(mWW <= 130.) continue;

    EvtWeight = CalcWeight();
    
    if(SampleName == "POWHEG") Calc_Pow_Weight();
    if(SampleName == "POWHEG_VBF") Calc_Pow_Vbf_Weight();

    //====================================================
    // number of Jet 
    //====================================================
    //
    //if(njet == 0)if(mWW < 500) continue; // Phantom strange

    if( njet == 3)if(CentJetVetoCut()) njet = 2; //Andrea
    nnjet = njet;

    if(njet>NjetBin-1) nnjet = NjetBin-1;


#if NjetBin == 5
    //if(njet>=3){;}else continue; comment out for 23 jet >= 2 comparison
#endif

#if NjetBin == 4
    //if(njet>=2 && njet<=3){;}else continue;
#endif

    // Test for 23 and >=2
    if( CommonCut_VBFnjet() ==1 && (njet==2 || njet==3) )
    {
      h1_23vsInv->Fill(0.);
      h1_23vsInv_Wevt->Fill(0.,EvtWeight);
      h1_23vsInv_WevtPow2Gen->Fill(0.,WevtPow2Gen);
    }
    if(CommonCut_VBFnjetWoCentJetVeto() ==1 && (njet== 2 || njet ==3))
    {
      h1_23vsInv->Fill(1.);
      h1_23vsInv_Wevt->Fill(1.,EvtWeight);
      h1_23vsInv_WevtPow2Gen->Fill(1.,WevtPow2Gen);
    }

    //if( njet > 3)continue;
    //if(!(njet== 2 || njet ==3))continue;
    //-------------------------------
    if(CommonCut_njet() !=1)continue;

    Fill_BeforeCut();
    //====================================================
    //Cuts 
    //====================================================
    if( Cut == "CommonCut_njet")if(CommonCut_njet() !=1)continue;
    if( Cut == "CommonCut_VBFnjet")if(CommonCut_VBFnjet() !=1)continue;
    if( Cut == "CommonCut_VBf_NoVetoCentralJet")if(CommonCut_VBf_NoVetoCentralJet() !=1)continue;

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

  
