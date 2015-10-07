//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 12 01:53:46 2014 by ROOT version 5.32/00
// from TChain latino/
//////////////////////////////////////////////////////////

#ifndef HWwNjetStudy_h
#define HWwNjetStudy_h

#include <TSystem.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>

#include <iostream>
#include <fstream>
#include <iomanip>

#include "HWwBase.h"
#include "NjetBin.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class HWwNjetStudy: public HWwBase {
public :

   HWwNjetStudy(TTree *tree=0,double lumiweight =1, TString SampleName = "Data",TString Cut ="Tight", bool RunOnMC= true);
   virtual ~HWwNjetStudy();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   //virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
protected:
   int InitVar();
   int InitVar4Evt();
   int InitHistogram();
   int Fill_Histo();
   int Fill_BeforeCut();
   int Write_Histo();
   void Calc_Pow_Vbf_Weight();
   void Calc_Pow_Weight();
   double WevtPow2Gen;
   int nnjet;

   ofstream Fout;
   TFile *myFile;
   
   TH1D *h1_23vsInv;
   TH1D *h1_23vsInv_Wevt;
   TH1D *h1_23vsInv_WevtPow2Gen;

   TH1D *h1_njet_Off_Wevt[NmWWBin+1]; //idx NmWWBin for inclusive//11 for mWW>130 GeV
   TH1D *h1_njet_Off_WevtPow2Gen[NmWWBin+1];
   TH1D *h1_njet_Off_noWeight[NmWWBin+1];
   
   TH1D *h1_mWW_Off_Wevt[NjetBin+1];        // NjetBin for jet inclusive
   TH1D *h1_mWW_Off_WevtPow2Gen[NjetBin+1]; // NjetBin for jet inclusive
   TH1D *h1_mWW_Off_noWeight[NjetBin+1];    // NjetBin for jet inclusive
   TH1D *h1_mjj_NoW[NjetBin+1];                 // NjetBin for jet inclusive
   TH1D *h1_mjj_Wevt[NjetBin+1];                 // NjetBin for jet inclusive
   TH1D *h1_mjj_WevtPow2Gen[NjetBin+1];                 // NjetBin for jet inclusive
   TH1D *h1_detajj_NoW[NjetBin+1];              // NjetBin for jet inclusive
   TH1D *h1_detajj_Wevt[NjetBin+1];              // NjetBin for jet inclusive
   TH1D *h1_detajj_WevtPow2Gen[NjetBin+1];              // NjetBin for jet inclusive

   
   TH1D *h1_mWW_Off_Wevt_NoCut[NjetBin+1];        // 5 for jet inclusive
   TH1D *h1_mWW_Off_WevtPow2Gen_NoCut[NjetBin+1]; // 5 for jet inclusive
   TH1D *h1_mWW_Off_noWeight_NoCut[NjetBin+1];    // 5 for jet inclusive
   TH1D *h1_mjj_NoCut[NjetBin+1];                 // 5 for jet inclusive
   TH1D *h1_detajj_NoCut[NjetBin+1];              // 5 for jet inclusive

   TH1D *h1_Njet_NoW;
   TH1D *h1_Njet_Wevt;
   TH1D *h1_Njet_WevtPow2Gen;

   TH1D *h1_Njet_NoW_NoCut;
   TH1D *h1_Njet_Wevt_NoCut;
   TH1D *h1_Njet_WevtPow2Gen_NoCut;

};
#endif

#ifdef HWwNjetStudy_cxx

HWwNjetStudy::HWwNjetStudy(TTree *tree,double lumiweight, TString SampleName_,TString Cut_, bool RunOnMC) :
  HWwBase::HWwBase( tree, lumiweight, SampleName_, Cut_, RunOnMC)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  cout<<"HWwNjetStudy constructor"<<endl;
  if (tree == 0) {
    cout<<"Usage: HWwNjetStudy(TTree*... ) "<<endl;
    exit(-1);
  }
  cout<<"HWwNjetStudy.h: initializing =================="<<endl;
  InitVar();
  InitHistogram();
}

HWwNjetStudy::~HWwNjetStudy()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HWwNjetStudy::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HWwNjetStudy::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}


Bool_t HWwNjetStudy::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HWwNjetStudy::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

int HWwNjetStudy::Fill_Histo()
{
  h1_njet_Off_Wevt[NmWWBin]		-> Fill(nnjet,EvtWeight); // Inclusive
  h1_njet_Off_WevtPow2Gen[NmWWBin]	-> Fill(nnjet,WevtPow2Gen);
  h1_njet_Off_noWeight[NmWWBin]		-> Fill(nnjet);
  for(int iBin(0);iBin<NmWWBin;iBin++){
    if(mWW > mWWBins[iBin] && mWW <= mWWBins[iBin+1])
    {
      h1_njet_Off_Wevt[iBin] 		-> Fill(nnjet,EvtWeight);
      h1_njet_Off_WevtPow2Gen[iBin] 	-> Fill(nnjet,WevtPow2Gen);
      h1_njet_Off_noWeight[iBin]	-> Fill(nnjet);
    }
  }

  // Fill inclusive
//  if( nnjet < NjetBin){
  h1_mWW_Off_Wevt[NjetBin] 		-> Fill(mWW, EvtWeight);
  h1_mWW_Off_WevtPow2Gen[NjetBin] 	-> Fill(mWW, WevtPow2Gen);
  h1_mWW_Off_noWeight[NjetBin]		-> Fill(mWW);
  h1_mjj_NoW[NjetBin]			-> Fill(mjj);
  h1_mjj_Wevt[NjetBin]			-> Fill(mjj, EvtWeight);
  h1_mjj_WevtPow2Gen[NjetBin]		-> Fill(mjj, WevtPow2Gen);
  h1_detajj_NoW[NjetBin]		-> Fill(detajj);
  h1_detajj_Wevt[NjetBin]		-> Fill(detajj, EvtWeight);
  h1_detajj_WevtPow2Gen[NjetBin]	-> Fill(detajj, WevtPow2Gen);
//  }
  
 // Fill bin dependent 
  h1_mWW_Off_Wevt[nnjet]		-> Fill(mWW, EvtWeight);
  h1_mWW_Off_WevtPow2Gen[nnjet]		-> Fill(mWW, WevtPow2Gen);
  h1_mWW_Off_noWeight[nnjet]		-> Fill(mWW);
  h1_mjj_NoW[nnjet]			-> Fill(mjj);
  h1_mjj_Wevt[nnjet] 			-> Fill(mjj,    EvtWeight);
  h1_mjj_WevtPow2Gen[nnjet]		-> Fill(mjj,    WevtPow2Gen);
  h1_detajj_NoW[nnjet]			-> Fill(detajj);
  h1_detajj_Wevt[nnjet]			-> Fill(detajj, EvtWeight);
  h1_detajj_WevtPow2Gen[nnjet]		-> Fill(detajj, WevtPow2Gen);

  h1_Njet_NoW->Fill(nnjet);
  h1_Njet_Wevt->Fill(nnjet, EvtWeight);
  h1_Njet_WevtPow2Gen->Fill(nnjet, WevtPow2Gen);
  
  return 0;
}
int HWwNjetStudy::Fill_BeforeCut()
{
  h1_Njet_NoW_NoCut->Fill(nnjet);
  h1_Njet_Wevt_NoCut->Fill(nnjet, EvtWeight);
  h1_Njet_WevtPow2Gen_NoCut->Fill(nnjet, WevtPow2Gen);

  // Fill inclusive
  //if( nnjet < NjetBin){
  h1_mWW_Off_Wevt_NoCut[NjetBin] 		-> Fill(mWW, EvtWeight);
  h1_mWW_Off_WevtPow2Gen_NoCut[NjetBin] 	-> Fill(mWW, WevtPow2Gen);
  h1_mWW_Off_noWeight_NoCut[NjetBin]		-> Fill(mWW);
  h1_mjj_NoCut[NjetBin]			-> Fill(mjj,    WevtPow2Gen);
  h1_detajj_NoCut[NjetBin]			-> Fill(detajj, WevtPow2Gen);
  //}
 // Fill bin dependent 
  h1_mWW_Off_Wevt_NoCut[nnjet]		-> Fill(mWW, EvtWeight);
  h1_mWW_Off_WevtPow2Gen_NoCut[nnjet]		-> Fill(mWW, WevtPow2Gen);
  h1_mWW_Off_noWeight_NoCut[nnjet]		-> Fill(mWW);
  h1_mjj_NoCut[nnjet]				-> Fill(mjj,    WevtPow2Gen);
  h1_detajj_NoCut[nnjet]			-> Fill(detajj, WevtPow2Gen);
  
  return 0;
}
int HWwNjetStudy::InitVar()
{
  TString FoutName = mResultDir+"/"+SampleName+"_"+Cut+".txt";
  Fout.open(FoutName);
  evtCnt = 0;
  return 0;
}
int HWwNjetStudy::InitVar4Evt()
{
  return 0;
}
int HWwNjetStudy::InitHistogram()
{
  myFile = new TFile(mResultDir+"/"+SampleName+"_"+Cut+".root","RECREATE");
  char histName[30];

  sprintf(histName, "h1_23vsInv");
  h1_23vsInv = new TH1D(histName,"h1_23vsInv", 2, 0, 2);
  sprintf(histName, "h1_23vsInv_Wevt");
  h1_23vsInv_Wevt = new TH1D(histName,"h1_23vsInv_Wevt", 2, 0, 2);
  sprintf(histName, "h1_23vsInv_WevtPow2Gen");
  h1_23vsInv_WevtPow2Gen = new TH1D(histName,"h1_23vsInv_WevtPow2Gen", 2, 0, 2);

  sprintf(histName, "h1_Njet_NoW");
  h1_Njet_NoW = new TH1D(histName,"h1_Njet_NoW", NjetBin, 0, NjetBin);
  sprintf(histName, "h1_Njet_Wevt");
  h1_Njet_Wevt = new TH1D(histName,"h1_Njet_Wevt", NjetBin, 0, NjetBin);
  sprintf(histName, "h1_Njet_WevtPow2Gen");
  h1_Njet_WevtPow2Gen = new TH1D(histName,"h1_Njet_WevtPow2Gen", NjetBin, 0, NjetBin);
  sprintf(histName, "h1_Njet_NoW_NoCut");
  h1_Njet_NoW_NoCut = new TH1D(histName,"h1_Njet_NoW_NoCut", NjetBin, 0, NjetBin);
  sprintf(histName, "h1_Njet_Wevt_NoCut");
  h1_Njet_Wevt_NoCut = new TH1D(histName,"h1_Njet_Wevt_NoCut", NjetBin, 0, NjetBin);
  sprintf(histName, "h1_Njet_WevtPow2Gen_NoCut");
  h1_Njet_WevtPow2Gen_NoCut = new TH1D(histName,"h1_Njet_WevtPow2Gen_NoCut", NjetBin, 0, NjetBin);

  for(int i(0); i<NmWWBin+1; i++)
  {
    sprintf(histName, "h1_njet_Off_Wevt_%d",i);
    h1_njet_Off_Wevt[i] = new TH1D(histName,"Jet numbers in off-shell", 5, 0, 5);

    sprintf(histName, "h1_njet_Off_WevtPow2Gen_%d",i);
    h1_njet_Off_WevtPow2Gen[i] = new TH1D(histName,"Jet numbers in off-shell", 5, 0, 5);

    sprintf(histName, "h1_njet_Off_noWeight_%d",i);
    h1_njet_Off_noWeight[i] = new TH1D(histName,"Jet numbers in off-shell", 5, 0, 5);
  }

  for(int i(0); i<NjetBin+1; i++)
  {
    sprintf(histName, "h1_mWW_Off_Wevt_%d",i);
#if VBF_MODE == 1
    h1_mWW_Off_Wevt[i] = new TH1D(histName,"mWW", 100, 130, 1430);//phn
#else
    h1_mWW_Off_Wevt[i]  = new TH1D(histName,"mWW", 150, 0, 1500); // gg2Vv
#endif

    sprintf(histName, "h1_mWW_Off_WevtPow2Gen_%d",i);
#if VBF_MODE == 1
    h1_mWW_Off_WevtPow2Gen[i] = new TH1D(histName,"mWW", 100, 130, 1430);
#else
    h1_mWW_Off_WevtPow2Gen[i] = new TH1D(histName,"mWW", 150, 0, 1500);
#endif

    sprintf(histName, "h1_mWW_Off_noWeight_%d",i);
#if VBF_MODE == 1
    h1_mWW_Off_noWeight[i] = new TH1D(histName,"mWW", 100, 130, 1430);
#else
    h1_mWW_Off_noWeight[i] = new TH1D(histName,"mWW", 150, 0, 1500); //gg2VV
#endif

    sprintf(histName, "h1_mjj_NoW_%d",i);
    h1_mjj_NoW[i] = new TH1D(histName,"mjj_NoW", 20, 0, 2000);
    sprintf(histName, "h1_mjj_Wevt_%d",i);
    h1_mjj_Wevt[i] = new TH1D(histName,"mjj_Wevt", 20, 0, 2000);
    sprintf(histName, "h1_mjj_WevtPow2Gen_%d",i);
    h1_mjj_WevtPow2Gen[i] = new TH1D(histName,"mjj_WevtPow2Gen", 20, 0, 2000);
    sprintf(histName, "h1_detajj_NoW_%d",i);
    h1_detajj_NoW[i] = new TH1D(histName,"detajj_NoW", 16, 0, 8);
    sprintf(histName, "h1_detajj_Wevt_%d",i);
    h1_detajj_Wevt[i] = new TH1D(histName,"detajj_Wevt", 16, 0, 8);
    sprintf(histName, "h1_detajj_WevtPow2Gen_%d",i);
    h1_detajj_WevtPow2Gen[i] = new TH1D(histName,"detajj_WevtPow2Gen", 16, 0, 8);
    
    sprintf(histName, "h1_mWW_Off_Wevt_NoCut_%d",i);
#if VBF_MODE == 1
    h1_mWW_Off_Wevt_NoCut[i] = new TH1D(histName,"mWW", 100, 130, 1430);
#else
    h1_mWW_Off_Wevt_NoCut[i] = new TH1D(histName,"mWW", 150, 0, 1500);
#endif

    sprintf(histName, "h1_mWW_Off_WevtPow2Gen_NoCut_%d",i);
#if VBF_MODE == 1
    h1_mWW_Off_WevtPow2Gen_NoCut[i] = new TH1D(histName,"mWW", 100, 130, 1430);
#else
    h1_mWW_Off_WevtPow2Gen_NoCut[i] = new TH1D(histName,"mWW", 150, 0, 1500);
#endif

    sprintf(histName, "h1_mWW_Off_noWeight_NoCut_%d",i);
#if VBF_MODE == 1
    h1_mWW_Off_noWeight_NoCut[i] = new TH1D(histName,"mWW", 100, 130, 1430);
#else
    h1_mWW_Off_noWeight_NoCut[i] = new TH1D(histName,"mWW", 150, 0, 1500);
#endif

    sprintf(histName, "h1_mjj_NoCut_%d",i);
    h1_mjj_NoCut[i] = new TH1D(histName,"mjj", 20, 0, 2000);
    sprintf(histName, "h1_detajj_NoCut_%d",i);
    h1_detajj_NoCut[i] = new TH1D(histName,"detajj", 16, 0, 8);
    
  }
  return 0;
}
void HWwNjetStudy::Calc_Pow_Vbf_Weight()
{
      //if(mWW <= 130)               WevtPow2Gen= EvtWeight *0;
      //if(mWW > 130 && mWW <= 200)  WevtPow2Gen= EvtWeight *0.153388;
      //if(mWW > 200 && mWW <= 300)  WevtPow2Gen= EvtWeight *1.78492;
      //if(mWW > 300 && mWW <= 400)  WevtPow2Gen= EvtWeight *2.15192;
      //if(mWW > 400 && mWW <= 500)  WevtPow2Gen= EvtWeight *3.29945;
      //if(mWW > 500 && mWW <= 600)  WevtPow2Gen= EvtWeight *5.25967;
      //if(mWW > 600 && mWW <= 700)  WevtPow2Gen= EvtWeight *10.6058;
      //if(mWW > 700 && mWW <= 800)  WevtPow2Gen= EvtWeight *18.1124;
      //if(mWW > 800 && mWW <= 900)  WevtPow2Gen= EvtWeight *22.0678;
      //if(mWW > 900 && mWW <= 1000) WevtPow2Gen= EvtWeight *36.0357;
      //if(mWW > 1000 && mWW <= 1250)WevtPow2Gen= EvtWeight *77.5059;
      //if(mWW > 1250 && mWW <= 1500)WevtPow2Gen= EvtWeight *234.308;
      //
      //
      //
#if REWEIGHT == 1
      //VBF ctVeto mjj500 nj2,3 NjetBin 3
	 if(mWW <= 130)	 WevtPow2Gen= 0;
	 if(mWW > 130 && mWW <= 143)	 WevtPow2Gen= EvtWeight *0.0658186;
	 if(mWW > 143 && mWW <= 156)	 WevtPow2Gen= EvtWeight *0.0290923;
	 if(mWW > 156 && mWW <= 169)	 WevtPow2Gen= EvtWeight *0.303703;
	 if(mWW > 169 && mWW <= 182)	 WevtPow2Gen= EvtWeight *0.207194;
	 if(mWW > 182 && mWW <= 195)	 WevtPow2Gen= EvtWeight *0.489053;
	 if(mWW > 195 && mWW <= 208)	 WevtPow2Gen= EvtWeight *0.587594;
	 if(mWW > 208 && mWW <= 221)	 WevtPow2Gen= EvtWeight *15.7996;
	 if(mWW > 221 && mWW <= 234)	 WevtPow2Gen= EvtWeight *13.5723;
	 if(mWW > 234 && mWW <= 247)	 WevtPow2Gen= EvtWeight *2.44848;
	 if(mWW > 247 && mWW <= 260)	 WevtPow2Gen= EvtWeight *0.740945;
	 if(mWW > 260 && mWW <= 273)	 WevtPow2Gen= EvtWeight *8.9384;
	 if(mWW > 273 && mWW <= 286)	 WevtPow2Gen= EvtWeight *6.29525;
	 if(mWW > 286 && mWW <= 299)	 WevtPow2Gen= EvtWeight *1.86619;
	 if(mWW > 299 && mWW <= 312)	 WevtPow2Gen= EvtWeight *1.28063;
	 if(mWW > 312 && mWW <= 325)	 WevtPow2Gen= EvtWeight *3.89935;
	 if(mWW > 325 && mWW <= 338)	 WevtPow2Gen= EvtWeight *4.18579;
	 if(mWW > 338 && mWW <= 351)	 WevtPow2Gen= EvtWeight *1.80522;
	 if(mWW > 351 && mWW <= 364)	 WevtPow2Gen= EvtWeight *1.79279;
	 if(mWW > 364 && mWW <= 377)	 WevtPow2Gen= EvtWeight *3.85722;
	 if(mWW > 377 && mWW <= 390)	 WevtPow2Gen= EvtWeight *3.13312;
	 if(mWW > 390 && mWW <= 403)	 WevtPow2Gen= EvtWeight *2.60684;
	 if(mWW > 403 && mWW <= 416)	 WevtPow2Gen= EvtWeight *2.74232;
	 if(mWW > 416 && mWW <= 429)	 WevtPow2Gen= EvtWeight *3.65012;
	 if(mWW > 429 && mWW <= 442)	 WevtPow2Gen= EvtWeight *3.08333;
	 if(mWW > 442 && mWW <= 455)	 WevtPow2Gen= EvtWeight *3.45557;
	 if(mWW > 455 && mWW <= 468)	 WevtPow2Gen= EvtWeight *3.95537;
	 if(mWW > 468 && mWW <= 481)	 WevtPow2Gen= EvtWeight *4.28514;
	 if(mWW > 481 && mWW <= 494)	 WevtPow2Gen= EvtWeight *4.46231;
	 if(mWW > 494 && mWW <= 507)	 WevtPow2Gen= EvtWeight *4.0617;
	 if(mWW > 507 && mWW <= 520)	 WevtPow2Gen= EvtWeight *4.04718;
	 if(mWW > 520 && mWW <= 533)	 WevtPow2Gen= EvtWeight *4.18022;
	 if(mWW > 533 && mWW <= 546)	 WevtPow2Gen= EvtWeight *5.22116;
	 if(mWW > 546 && mWW <= 559)	 WevtPow2Gen= EvtWeight *4.73004;
	 if(mWW > 559 && mWW <= 572)	 WevtPow2Gen= EvtWeight *4.77969;
	 if(mWW > 572 && mWW <= 585)	 WevtPow2Gen= EvtWeight *7.3399;
	 if(mWW > 585 && mWW <= 598)	 WevtPow2Gen= EvtWeight *6.31513;
	 if(mWW > 598 && mWW <= 611)	 WevtPow2Gen= EvtWeight *5.40842;
	 if(mWW > 611 && mWW <= 624)	 WevtPow2Gen= EvtWeight *7.79547;
	 if(mWW > 624 && mWW <= 637)	 WevtPow2Gen= EvtWeight *10.265;
	 if(mWW > 637 && mWW <= 650)	 WevtPow2Gen= EvtWeight *9.99022;
	 if(mWW > 650 && mWW <= 663)	 WevtPow2Gen= EvtWeight *13.5158;
	 if(mWW > 663 && mWW <= 676)	 WevtPow2Gen= EvtWeight *10.3985;
	 if(mWW > 676 && mWW <= 689)	 WevtPow2Gen= EvtWeight *14.3856;
	 if(mWW > 689 && mWW <= 702)	 WevtPow2Gen= EvtWeight *11.9662;
	 if(mWW > 702 && mWW <= 715)	 WevtPow2Gen= EvtWeight *9.17898;
	 if(mWW > 715 && mWW <= 728)	 WevtPow2Gen= EvtWeight *16.3996;
	 if(mWW > 728 && mWW <= 741)	 WevtPow2Gen= EvtWeight *17.6741;
	 if(mWW > 741 && mWW <= 754)	 WevtPow2Gen= EvtWeight *15.9045;
	 if(mWW > 754 && mWW <= 767)	 WevtPow2Gen= EvtWeight *14.5923;
	 if(mWW > 767 && mWW <= 780)	 WevtPow2Gen= EvtWeight *21.6395;
	 if(mWW > 780 && mWW <= 793)	 WevtPow2Gen= EvtWeight *16.3228;
	 if(mWW > 793 && mWW <= 806)	 WevtPow2Gen= EvtWeight *20.698;
	 if(mWW > 806 && mWW <= 819)	 WevtPow2Gen= EvtWeight *18.0486;
	 if(mWW > 819 && mWW <= 832)	 WevtPow2Gen= EvtWeight *20.0777;
	 if(mWW > 832 && mWW <= 845)	 WevtPow2Gen= EvtWeight *16.927;
	 if(mWW > 845 && mWW <= 858)	 WevtPow2Gen= EvtWeight *16.3798;
	 if(mWW > 858 && mWW <= 871)	 WevtPow2Gen= EvtWeight *22.6743;
	 if(mWW > 871 && mWW <= 884)	 WevtPow2Gen= EvtWeight *29.815;
	 if(mWW > 884 && mWW <= 897)	 WevtPow2Gen= EvtWeight *24.1585;
	 if(mWW > 897 && mWW <= 910)	 WevtPow2Gen= EvtWeight *29.3371;
	 if(mWW > 910 && mWW <= 923)	 WevtPow2Gen= EvtWeight *29.4276;
	 if(mWW > 923 && mWW <= 936)	 WevtPow2Gen= EvtWeight *32.1237;
	 if(mWW > 936 && mWW <= 949)	 WevtPow2Gen= EvtWeight *34.995;
	 if(mWW > 949 && mWW <= 962)	 WevtPow2Gen= EvtWeight *42.5459;
	 if(mWW > 962 && mWW <= 975)	 WevtPow2Gen= EvtWeight *40.1096;
	 if(mWW > 975 && mWW <= 988)	 WevtPow2Gen= EvtWeight *44.4366;
	 if(mWW > 988 && mWW <= 1001)	 WevtPow2Gen= EvtWeight *35.6793;
	 if(mWW > 1001 && mWW <= 1014)	 WevtPow2Gen= EvtWeight *52.5044;
	 if(mWW > 1014 && mWW <= 1027)	 WevtPow2Gen= EvtWeight *43.1178;
	 if(mWW > 1027 && mWW <= 1040)	 WevtPow2Gen= EvtWeight *47.6499;
	 if(mWW > 1040 && mWW <= 1053)	 WevtPow2Gen= EvtWeight *51.2047;
	 if(mWW > 1053 && mWW <= 1066)	 WevtPow2Gen= EvtWeight *48.4705;
	 if(mWW > 1066 && mWW <= 1079)	 WevtPow2Gen= EvtWeight *54.7015;
	 if(mWW > 1079 && mWW <= 1092)	 WevtPow2Gen= EvtWeight *60.334;
	 if(mWW > 1092 && mWW <= 1105)	 WevtPow2Gen= EvtWeight *69.3787;
	 if(mWW > 1105 && mWW <= 1118)	 WevtPow2Gen= EvtWeight *77.6331;
	 if(mWW > 1118 && mWW <= 1131)	 WevtPow2Gen= EvtWeight *95.8485;
	 if(mWW > 1131 && mWW <= 1144)	 WevtPow2Gen= EvtWeight *65.9313;
	 if(mWW > 1144 && mWW <= 1157)	 WevtPow2Gen= EvtWeight *101.152;
	 if(mWW > 1157 && mWW <= 1170)	 WevtPow2Gen= EvtWeight *105.822;
	 if(mWW > 1170 && mWW <= 1183)	 WevtPow2Gen= EvtWeight *92.8826;
	 if(mWW > 1183 && mWW <= 1196)	 WevtPow2Gen= EvtWeight *124.658;
	 if(mWW > 1196 && mWW <= 1209)	 WevtPow2Gen= EvtWeight *96.8311;
	 if(mWW > 1209 && mWW <= 1222)	 WevtPow2Gen= EvtWeight *131.674;
	 if(mWW > 1222 && mWW <= 1235)	 WevtPow2Gen= EvtWeight *157.814;
	 if(mWW > 1235 && mWW <= 1248)	 WevtPow2Gen= EvtWeight *134.172;
	 if(mWW > 1248 && mWW <= 1261)	 WevtPow2Gen= EvtWeight *109.921;
	 if(mWW > 1261 && mWW <= 1274)	 WevtPow2Gen= EvtWeight *127.499;
	 if(mWW > 1274 && mWW <= 1287)	 WevtPow2Gen= EvtWeight *207.544;
	 if(mWW > 1287 && mWW <= 1300)	 WevtPow2Gen= EvtWeight *131.427;
	 if(mWW > 1300 && mWW <= 1313)	 WevtPow2Gen= EvtWeight *101.145;
	 if(mWW > 1313 && mWW <= 1326)	 WevtPow2Gen= EvtWeight *148.65;
	 if(mWW > 1326 && mWW <= 1339)	 WevtPow2Gen= EvtWeight *167.744;
	 if(mWW > 1339 && mWW <= 1352)	 WevtPow2Gen= EvtWeight *207.841;
	 if(mWW > 1352 && mWW <= 1365)	 WevtPow2Gen= EvtWeight *207.255;
	 if(mWW > 1365 && mWW <= 1378)	 WevtPow2Gen= EvtWeight *277.471;
	 if(mWW > 1378 && mWW <= 1391)	 WevtPow2Gen= EvtWeight *198.477;
	 if(mWW > 1391 && mWW <= 1404)	 WevtPow2Gen= EvtWeight *201.074;
	 if(mWW > 1404 && mWW <= 1417)	 WevtPow2Gen= EvtWeight *184.864;
	 if(mWW > 1417 && mWW <= 1430)	 WevtPow2Gen= EvtWeight *228.852;


	 if(mWW > 1430 && mWW <= 1434)	 WevtPow2Gen= EvtWeight *418.315;
	 if(mWW > 1434 && mWW <= 1445)	 WevtPow2Gen= EvtWeight *398.415;
	 if(mWW > 1445 && mWW <= 1456)	 WevtPow2Gen= EvtWeight *319.643;
	 if(mWW > 1456 && mWW <= 1467)	 WevtPow2Gen= EvtWeight *461.978;
	 if(mWW > 1467 && mWW <= 1478)	 WevtPow2Gen= EvtWeight *460.139;
	 if(mWW > 1478 && mWW <= 1489)	 WevtPow2Gen= EvtWeight *585.044;
	 if(mWW > 1489 )	 WevtPow2Gen= EvtWeight *617.698;
#endif

#if REWEIGHT == 4
      //VBF ctVeto mjj500 NjetBin 4
	 if(mWW <= 130 )		 WevtPow2Gen= 0.0;
	 if(mWW > 130 && mWW <= 143)	 WevtPow2Gen= EvtWeight *0.066139;
	 if(mWW > 143 && mWW <= 156)	 WevtPow2Gen= EvtWeight *0.028814;
	 if(mWW > 156 && mWW <= 169)	 WevtPow2Gen= EvtWeight *0.302127;
	 if(mWW > 169 && mWW <= 182)	 WevtPow2Gen= EvtWeight *0.206397;
	 if(mWW > 182 && mWW <= 195)	 WevtPow2Gen= EvtWeight *0.490389;
	 if(mWW > 195 && mWW <= 208)	 WevtPow2Gen= EvtWeight *0.596631;
	 if(mWW > 208 && mWW <= 221)	 WevtPow2Gen= EvtWeight *15.4524;
	 if(mWW > 221 && mWW <= 234)	 WevtPow2Gen= EvtWeight *13.5485;
	 if(mWW > 234 && mWW <= 247)	 WevtPow2Gen= EvtWeight *2.47577;
	 if(mWW > 247 && mWW <= 260)	 WevtPow2Gen= EvtWeight *0.753245;
	 if(mWW > 260 && mWW <= 273)	 WevtPow2Gen= EvtWeight *8.79294;
	 if(mWW > 273 && mWW <= 286)	 WevtPow2Gen= EvtWeight *6.32957;
	 if(mWW > 286 && mWW <= 299)	 WevtPow2Gen= EvtWeight *1.91056;
	 if(mWW > 299 && mWW <= 312)	 WevtPow2Gen= EvtWeight *1.25629;
	 if(mWW > 312 && mWW <= 325)	 WevtPow2Gen= EvtWeight *3.85582;
	 if(mWW > 325 && mWW <= 338)	 WevtPow2Gen= EvtWeight *4.24473;
	 if(mWW > 338 && mWW <= 351)	 WevtPow2Gen= EvtWeight *1.79908;
	 if(mWW > 351 && mWW <= 364)	 WevtPow2Gen= EvtWeight *1.75651;
	 if(mWW > 364 && mWW <= 377)	 WevtPow2Gen= EvtWeight *3.83495;
	 if(mWW > 377 && mWW <= 390)	 WevtPow2Gen= EvtWeight *3.03398;
	 if(mWW > 390 && mWW <= 403)	 WevtPow2Gen= EvtWeight *2.61669;
	 if(mWW > 403 && mWW <= 416)	 WevtPow2Gen= EvtWeight *2.71911;
	 if(mWW > 416 && mWW <= 429)	 WevtPow2Gen= EvtWeight *3.65617;
	 if(mWW > 429 && mWW <= 442)	 WevtPow2Gen= EvtWeight *3.1571;
	 if(mWW > 442 && mWW <= 455)	 WevtPow2Gen= EvtWeight *3.48881;
	 if(mWW > 455 && mWW <= 468)	 WevtPow2Gen= EvtWeight *3.96089;
	 if(mWW > 468 && mWW <= 481)	 WevtPow2Gen= EvtWeight *4.32345;
	 if(mWW > 481 && mWW <= 494)	 WevtPow2Gen= EvtWeight *4.39497;
	 if(mWW > 494 && mWW <= 507)	 WevtPow2Gen= EvtWeight *4.0643;
	 if(mWW > 507 && mWW <= 520)	 WevtPow2Gen= EvtWeight *3.96316;
	 if(mWW > 520 && mWW <= 533)	 WevtPow2Gen= EvtWeight *4.09743;
	 if(mWW > 533 && mWW <= 546)	 WevtPow2Gen= EvtWeight *5.11887;
	 if(mWW > 546 && mWW <= 559)	 WevtPow2Gen= EvtWeight *4.86429;
	 if(mWW > 559 && mWW <= 572)	 WevtPow2Gen= EvtWeight *4.80659;
	 if(mWW > 572 && mWW <= 585)	 WevtPow2Gen= EvtWeight *7.3496;
	 if(mWW > 585 && mWW <= 598)	 WevtPow2Gen= EvtWeight *6.4184;
	 if(mWW > 598 && mWW <= 611)	 WevtPow2Gen= EvtWeight *5.45169;
	 if(mWW > 611 && mWW <= 624)	 WevtPow2Gen= EvtWeight *7.85496;
	 if(mWW > 624 && mWW <= 637)	 WevtPow2Gen= EvtWeight *10.2942;
	 if(mWW > 637 && mWW <= 650)	 WevtPow2Gen= EvtWeight *10.135;
	 if(mWW > 650 && mWW <= 663)	 WevtPow2Gen= EvtWeight *13.7855;
	 if(mWW > 663 && mWW <= 676)	 WevtPow2Gen= EvtWeight *10.4688;
	 if(mWW > 676 && mWW <= 689)	 WevtPow2Gen= EvtWeight *14.1903;
	 if(mWW > 689 && mWW <= 702)	 WevtPow2Gen= EvtWeight *12.3467;
	 if(mWW > 702 && mWW <= 715)	 WevtPow2Gen= EvtWeight *9.03818;
	 if(mWW > 715 && mWW <= 728)	 WevtPow2Gen= EvtWeight *16.8833;
	 if(mWW > 728 && mWW <= 741)	 WevtPow2Gen= EvtWeight *17.4962;
	 if(mWW > 741 && mWW <= 754)	 WevtPow2Gen= EvtWeight *16.03;
	 if(mWW > 754 && mWW <= 767)	 WevtPow2Gen= EvtWeight *14.3014;
	 if(mWW > 767 && mWW <= 780)	 WevtPow2Gen= EvtWeight *20.8461;
	 if(mWW > 780 && mWW <= 793)	 WevtPow2Gen= EvtWeight *16.2599;
	 if(mWW > 793 && mWW <= 806)	 WevtPow2Gen= EvtWeight *21.0158;
	 if(mWW > 806 && mWW <= 819)	 WevtPow2Gen= EvtWeight *17.7591;
	 if(mWW > 819 && mWW <= 832)	 WevtPow2Gen= EvtWeight *20.3268;
	 if(mWW > 832 && mWW <= 845)	 WevtPow2Gen= EvtWeight *16.8561;
	 if(mWW > 845 && mWW <= 858)	 WevtPow2Gen= EvtWeight *16.8983;
	 if(mWW > 858 && mWW <= 871)	 WevtPow2Gen= EvtWeight *22.8881;
	 if(mWW > 871 && mWW <= 884)	 WevtPow2Gen= EvtWeight *30.59;
	 if(mWW > 884 && mWW <= 897)	 WevtPow2Gen= EvtWeight *24.2134;
	 if(mWW > 897 && mWW <= 910)	 WevtPow2Gen= EvtWeight *30.338;
	 if(mWW > 910 && mWW <= 923)	 WevtPow2Gen= EvtWeight *29.2583;
	 if(mWW > 923 && mWW <= 936)	 WevtPow2Gen= EvtWeight *32.6099;
	 if(mWW > 936 && mWW <= 949)	 WevtPow2Gen= EvtWeight *35.6324;
	 if(mWW > 949 && mWW <= 962)	 WevtPow2Gen= EvtWeight *43.2515;
	 if(mWW > 962 && mWW <= 975)	 WevtPow2Gen= EvtWeight *40.0791;
	 if(mWW > 975 && mWW <= 988)	 WevtPow2Gen= EvtWeight *44.9608;
	 if(mWW > 988 && mWW <= 1001)	 WevtPow2Gen= EvtWeight *36.3621;
	 if(mWW > 1001 && mWW <= 1014)	 WevtPow2Gen= EvtWeight *51.2949;
	 if(mWW > 1014 && mWW <= 1027)	 WevtPow2Gen= EvtWeight *43.7972;
	 if(mWW > 1027 && mWW <= 1040)	 WevtPow2Gen= EvtWeight *47.422;
	 if(mWW > 1040 && mWW <= 1053)	 WevtPow2Gen= EvtWeight *52.8197;
	 if(mWW > 1053 && mWW <= 1066)	 WevtPow2Gen= EvtWeight *48.4755;
	 if(mWW > 1066 && mWW <= 1079)	 WevtPow2Gen= EvtWeight *54.9183;
	 if(mWW > 1079 && mWW <= 1092)	 WevtPow2Gen= EvtWeight *60.1821;
	 if(mWW > 1092 && mWW <= 1105)	 WevtPow2Gen= EvtWeight *69.9583;
	 if(mWW > 1105 && mWW <= 1118)	 WevtPow2Gen= EvtWeight *75.1814;
	 if(mWW > 1118 && mWW <= 1131)	 WevtPow2Gen= EvtWeight *95.4731;
	 if(mWW > 1131 && mWW <= 1144)	 WevtPow2Gen= EvtWeight *62.8458;
	 if(mWW > 1144 && mWW <= 1157)	 WevtPow2Gen= EvtWeight *102.605;
	 if(mWW > 1157 && mWW <= 1170)	 WevtPow2Gen= EvtWeight *98.3806;
	 if(mWW > 1170 && mWW <= 1183)	 WevtPow2Gen= EvtWeight *92.7965;
	 if(mWW > 1183 && mWW <= 1196)	 WevtPow2Gen= EvtWeight *122.676;
	 if(mWW > 1196 && mWW <= 1209)	 WevtPow2Gen= EvtWeight *95.9892;
	 if(mWW > 1209 && mWW <= 1222)	 WevtPow2Gen= EvtWeight *137.01;
	 if(mWW > 1222 && mWW <= 1235)	 WevtPow2Gen= EvtWeight *156.783;
	 if(mWW > 1235 && mWW <= 1248)	 WevtPow2Gen= EvtWeight *132.058;
	 if(mWW > 1248 && mWW <= 1261)	 WevtPow2Gen= EvtWeight *112.181;
	 if(mWW > 1261 && mWW <= 1274)	 WevtPow2Gen= EvtWeight *128.731;
	 if(mWW > 1274 && mWW <= 1287)	 WevtPow2Gen= EvtWeight *209.208;
	 if(mWW > 1287 && mWW <= 1300)	 WevtPow2Gen= EvtWeight *141.719;
	 if(mWW > 1300 && mWW <= 1313)	 WevtPow2Gen= EvtWeight *98.3268;
	 if(mWW > 1313 && mWW <= 1326)	 WevtPow2Gen= EvtWeight *152.087;
	 if(mWW > 1326 && mWW <= 1339)	 WevtPow2Gen= EvtWeight *156.461;
	 if(mWW > 1339 && mWW <= 1352)	 WevtPow2Gen= EvtWeight *212.418;
	 if(mWW > 1352 && mWW <= 1365)	 WevtPow2Gen= EvtWeight *199.621;
	 if(mWW > 1365 && mWW <= 1378)	 WevtPow2Gen= EvtWeight *279.715;
	 if(mWW > 1378 && mWW <= 1391)	 WevtPow2Gen= EvtWeight *198.023;
	 if(mWW > 1391 && mWW <= 1404)	 WevtPow2Gen= EvtWeight *198.323;
	 if(mWW > 1404 && mWW <= 1417)	 WevtPow2Gen= EvtWeight *197.068;
	 if(mWW > 1417 && mWW <= 1430)	 WevtPow2Gen= EvtWeight *233.393;


	 if(mWW > 1430 && mWW <= 1434)	 WevtPow2Gen= EvtWeight *418.315;
	 if(mWW > 1434 && mWW <= 1445)	 WevtPow2Gen= EvtWeight *398.415;
	 if(mWW > 1445 && mWW <= 1456)	 WevtPow2Gen= EvtWeight *319.643;
	 if(mWW > 1456 && mWW <= 1467)	 WevtPow2Gen= EvtWeight *461.978;
	 if(mWW > 1467 && mWW <= 1478)	 WevtPow2Gen= EvtWeight *460.139;
	 if(mWW > 1478 && mWW <= 1489)	 WevtPow2Gen= EvtWeight *585.044;
	 if(mWW > 1489 )	 WevtPow2Gen= EvtWeight *617.698;
#endif
#if REWEIGHT == 5
      //VBF ctVeto mjj500 NjetBin 4 ME phn
	 if(mWW <= 130 )		 WevtPow2Gen= 0.0;
	 if(mWW > 130 && mWW <= 143)	 WevtPow2Gen= EvtWeight *0.0698067;
	 if(mWW > 143 && mWW <= 156)	 WevtPow2Gen= EvtWeight *0.0277956;
	 if(mWW > 156 && mWW <= 169)	 WevtPow2Gen= EvtWeight *0.320166;
	 if(mWW > 169 && mWW <= 182)	 WevtPow2Gen= EvtWeight *0.218402;
	 if(mWW > 182 && mWW <= 195)	 WevtPow2Gen= EvtWeight *0.553578;
	 if(mWW > 195 && mWW <= 208)	 WevtPow2Gen= EvtWeight *0.641179;
	 if(mWW > 208 && mWW <= 221)	 WevtPow2Gen= EvtWeight *17.9223;
	 if(mWW > 221 && mWW <= 234)	 WevtPow2Gen= EvtWeight *15.5159;
	 if(mWW > 234 && mWW <= 247)	 WevtPow2Gen= EvtWeight *3.08465;
	 if(mWW > 247 && mWW <= 260)	 WevtPow2Gen= EvtWeight *0.94297;
	 if(mWW > 260 && mWW <= 273)	 WevtPow2Gen= EvtWeight *9.58093;
	 if(mWW > 273 && mWW <= 286)	 WevtPow2Gen= EvtWeight *7.17339;
	 if(mWW > 286 && mWW <= 299)	 WevtPow2Gen= EvtWeight *1.93324;
	 if(mWW > 299 && mWW <= 312)	 WevtPow2Gen= EvtWeight *1.36201;
	 if(mWW > 312 && mWW <= 325)	 WevtPow2Gen= EvtWeight *4.98149;
	 if(mWW > 325 && mWW <= 338)	 WevtPow2Gen= EvtWeight *4.59586;
	 if(mWW > 338 && mWW <= 351)	 WevtPow2Gen= EvtWeight *1.97795;
	 if(mWW > 351 && mWW <= 364)	 WevtPow2Gen= EvtWeight *1.9501;
	 if(mWW > 364 && mWW <= 377)	 WevtPow2Gen= EvtWeight *4.50574;
	 if(mWW > 377 && mWW <= 390)	 WevtPow2Gen= EvtWeight *2.85619;
	 if(mWW > 390 && mWW <= 403)	 WevtPow2Gen= EvtWeight *2.37329;
	 if(mWW > 403 && mWW <= 416)	 WevtPow2Gen= EvtWeight *2.65845;
	 if(mWW > 416 && mWW <= 429)	 WevtPow2Gen= EvtWeight *3.30726;
	 if(mWW > 429 && mWW <= 442)	 WevtPow2Gen= EvtWeight *3.40163;
	 if(mWW > 442 && mWW <= 455)	 WevtPow2Gen= EvtWeight *3.38622;
	 if(mWW > 455 && mWW <= 468)	 WevtPow2Gen= EvtWeight *3.62798;
	 if(mWW > 468 && mWW <= 481)	 WevtPow2Gen= EvtWeight *3.79056;
	 if(mWW > 481 && mWW <= 494)	 WevtPow2Gen= EvtWeight *3.85759;
	 if(mWW > 494 && mWW <= 507)	 WevtPow2Gen= EvtWeight *3.87919;
	 if(mWW > 507 && mWW <= 520)	 WevtPow2Gen= EvtWeight *4.03642;
	 if(mWW > 520 && mWW <= 533)	 WevtPow2Gen= EvtWeight *3.66191;
	 if(mWW > 533 && mWW <= 546)	 WevtPow2Gen= EvtWeight *4.7778;
	 if(mWW > 546 && mWW <= 559)	 WevtPow2Gen= EvtWeight *4.32701;
	 if(mWW > 559 && mWW <= 572)	 WevtPow2Gen= EvtWeight *3.84084;
	 if(mWW > 572 && mWW <= 585)	 WevtPow2Gen= EvtWeight *6.39623;
	 if(mWW > 585 && mWW <= 598)	 WevtPow2Gen= EvtWeight *5.91922;
	 if(mWW > 598 && mWW <= 611)	 WevtPow2Gen= EvtWeight *5.63125;
	 if(mWW > 611 && mWW <= 624)	 WevtPow2Gen= EvtWeight *7.62216;
	 if(mWW > 624 && mWW <= 637)	 WevtPow2Gen= EvtWeight *10.2343;
	 if(mWW > 637 && mWW <= 650)	 WevtPow2Gen= EvtWeight *7.7546;
	 if(mWW > 650 && mWW <= 663)	 WevtPow2Gen= EvtWeight *11.0072;
	 if(mWW > 663 && mWW <= 676)	 WevtPow2Gen= EvtWeight *8.43003;
	 if(mWW > 676 && mWW <= 689)	 WevtPow2Gen= EvtWeight *10.9584;
	 if(mWW > 689 && mWW <= 702)	 WevtPow2Gen= EvtWeight *10.7027;
	 if(mWW > 702 && mWW <= 715)	 WevtPow2Gen= EvtWeight *8.01947;
	 if(mWW > 715 && mWW <= 728)	 WevtPow2Gen= EvtWeight *14.2686;
	 if(mWW > 728 && mWW <= 741)	 WevtPow2Gen= EvtWeight *16.3065;
	 if(mWW > 741 && mWW <= 754)	 WevtPow2Gen= EvtWeight *14.5156;
	 if(mWW > 754 && mWW <= 767)	 WevtPow2Gen= EvtWeight *14.1114;
	 if(mWW > 767 && mWW <= 780)	 WevtPow2Gen= EvtWeight *15.5457;
	 if(mWW > 780 && mWW <= 793)	 WevtPow2Gen= EvtWeight *14.4109;
	 if(mWW > 793 && mWW <= 806)	 WevtPow2Gen= EvtWeight *18.6849;
	 if(mWW > 806 && mWW <= 819)	 WevtPow2Gen= EvtWeight *16.5027;
	 if(mWW > 819 && mWW <= 832)	 WevtPow2Gen= EvtWeight *17.004;
	 if(mWW > 832 && mWW <= 845)	 WevtPow2Gen= EvtWeight *12.7309;
	 if(mWW > 845 && mWW <= 858)	 WevtPow2Gen= EvtWeight *14.8329;
	 if(mWW > 858 && mWW <= 871)	 WevtPow2Gen= EvtWeight *19.4091;
	 if(mWW > 871 && mWW <= 884)	 WevtPow2Gen= EvtWeight *23.1815;
	 if(mWW > 884 && mWW <= 897)	 WevtPow2Gen= EvtWeight *24.7223;
	 if(mWW > 897 && mWW <= 910)	 WevtPow2Gen= EvtWeight *24.9616;
	 if(mWW > 910 && mWW <= 923)	 WevtPow2Gen= EvtWeight *24.7178;
	 if(mWW > 923 && mWW <= 936)	 WevtPow2Gen= EvtWeight *24.8399;
	 if(mWW > 936 && mWW <= 949)	 WevtPow2Gen= EvtWeight *28.7422;
	 if(mWW > 949 && mWW <= 962)	 WevtPow2Gen= EvtWeight *32.3175;
	 if(mWW > 962 && mWW <= 975)	 WevtPow2Gen= EvtWeight *36.281;
	 if(mWW > 975 && mWW <= 988)	 WevtPow2Gen= EvtWeight *34.1759;
	 if(mWW > 988 && mWW <= 1001)	 WevtPow2Gen= EvtWeight *29.4394;
	 if(mWW > 1001 && mWW <= 1014)	 WevtPow2Gen= EvtWeight *42.403;
	 if(mWW > 1014 && mWW <= 1027)	 WevtPow2Gen= EvtWeight *33.1899;
	 if(mWW > 1027 && mWW <= 1040)	 WevtPow2Gen= EvtWeight *35.5377;
	 if(mWW > 1040 && mWW <= 1053)	 WevtPow2Gen= EvtWeight *42.735;
	 if(mWW > 1053 && mWW <= 1066)	 WevtPow2Gen= EvtWeight *38.2991;
	 if(mWW > 1066 && mWW <= 1079)	 WevtPow2Gen= EvtWeight *44.0984;
	 if(mWW > 1079 && mWW <= 1092)	 WevtPow2Gen= EvtWeight *46.5477;
	 if(mWW > 1092 && mWW <= 1105)	 WevtPow2Gen= EvtWeight *53.7592;
	 if(mWW > 1105 && mWW <= 1118)	 WevtPow2Gen= EvtWeight *60.2134;
	 if(mWW > 1118 && mWW <= 1131)	 WevtPow2Gen= EvtWeight *74.9374;
	 if(mWW > 1131 && mWW <= 1144)	 WevtPow2Gen= EvtWeight *57.1887;
	 if(mWW > 1144 && mWW <= 1157)	 WevtPow2Gen= EvtWeight *87.8388;
	 if(mWW > 1157 && mWW <= 1170)	 WevtPow2Gen= EvtWeight *80.3069;
	 if(mWW > 1170 && mWW <= 1183)	 WevtPow2Gen= EvtWeight *64.2696;
	 if(mWW > 1183 && mWW <= 1196)	 WevtPow2Gen= EvtWeight *96.8577;
	 if(mWW > 1196 && mWW <= 1209)	 WevtPow2Gen= EvtWeight *57.4114;
	 if(mWW > 1209 && mWW <= 1222)	 WevtPow2Gen= EvtWeight *110.997;
	 if(mWW > 1222 && mWW <= 1235)	 WevtPow2Gen= EvtWeight *115.181;
	 if(mWW > 1235 && mWW <= 1248)	 WevtPow2Gen= EvtWeight *98.2295;
	 if(mWW > 1248 && mWW <= 1261)	 WevtPow2Gen= EvtWeight *67.0863;
	 if(mWW > 1261 && mWW <= 1274)	 WevtPow2Gen= EvtWeight *82.0832;
	 if(mWW > 1274 && mWW <= 1287)	 WevtPow2Gen= EvtWeight *173.726;
	 if(mWW > 1287 && mWW <= 1300)	 WevtPow2Gen= EvtWeight *120.707;
	 if(mWW > 1300 && mWW <= 1313)	 WevtPow2Gen= EvtWeight *69.0137;
	 if(mWW > 1313 && mWW <= 1326)	 WevtPow2Gen= EvtWeight *101.92;
	 if(mWW > 1326 && mWW <= 1339)	 WevtPow2Gen= EvtWeight *115.803;
	 if(mWW > 1339 && mWW <= 1352)	 WevtPow2Gen= EvtWeight *142.994;
	 if(mWW > 1352 && mWW <= 1365)	 WevtPow2Gen= EvtWeight *165.299;
	 if(mWW > 1365 && mWW <= 1378)	 WevtPow2Gen= EvtWeight *215.119;
	 if(mWW > 1378 && mWW <= 1391)	 WevtPow2Gen= EvtWeight *119.604;
	 if(mWW > 1391 && mWW <= 1404)	 WevtPow2Gen= EvtWeight *197.778;
	 if(mWW > 1404 && mWW <= 1417)	 WevtPow2Gen= EvtWeight *173.457;
	 if(mWW > 1417 && mWW <= 1430)	 WevtPow2Gen= EvtWeight *174.478;


	 if(mWW > 1430 && mWW <= 1434)	 WevtPow2Gen= EvtWeight *418.315;
	 if(mWW > 1434 && mWW <= 1445)	 WevtPow2Gen= EvtWeight *398.415;
	 if(mWW > 1445 && mWW <= 1456)	 WevtPow2Gen= EvtWeight *319.643;
	 if(mWW > 1456 && mWW <= 1467)	 WevtPow2Gen= EvtWeight *461.978;
	 if(mWW > 1467 && mWW <= 1478)	 WevtPow2Gen= EvtWeight *460.139;
	 if(mWW > 1478 && mWW <= 1489)	 WevtPow2Gen= EvtWeight *585.044;
	 if(mWW > 1489 )	 WevtPow2Gen= EvtWeight *617.698;
#endif
#if REWEIGHT == 6
      //VBF ctVeto mjj500 NjetBin 4 no ptll cut
	 if(mWW <= 130 )		 WevtPow2Gen= 0.0;

	 if(mWW > 130 && mWW <= 143)	 WevtPow2Gen= EvtWeight *0.0666314;
	 if(mWW > 143 && mWW <= 156)	 WevtPow2Gen= EvtWeight *0.0287354;
	 if(mWW > 156 && mWW <= 169)	 WevtPow2Gen= EvtWeight *0.264803;
	 if(mWW > 169 && mWW <= 182)	 WevtPow2Gen= EvtWeight *0.188945;
	 if(mWW > 182 && mWW <= 195)	 WevtPow2Gen= EvtWeight *0.46514;
	 if(mWW > 195 && mWW <= 208)	 WevtPow2Gen= EvtWeight *0.57968;
	 if(mWW > 208 && mWW <= 221)	 WevtPow2Gen= EvtWeight *13.6668;
	 if(mWW > 221 && mWW <= 234)	 WevtPow2Gen= EvtWeight *12.659;
	 if(mWW > 234 && mWW <= 247)	 WevtPow2Gen= EvtWeight *2.40156;
	 if(mWW > 247 && mWW <= 260)	 WevtPow2Gen= EvtWeight *0.692351;
	 if(mWW > 260 && mWW <= 273)	 WevtPow2Gen= EvtWeight *7.93954;
	 if(mWW > 273 && mWW <= 286)	 WevtPow2Gen= EvtWeight *6.81224;
	 if(mWW > 286 && mWW <= 299)	 WevtPow2Gen= EvtWeight *1.62464;
	 if(mWW > 299 && mWW <= 312)	 WevtPow2Gen= EvtWeight *1.10564;
	 if(mWW > 312 && mWW <= 325)	 WevtPow2Gen= EvtWeight *3.80174;
	 if(mWW > 325 && mWW <= 338)	 WevtPow2Gen= EvtWeight *4.28692;
	 if(mWW > 338 && mWW <= 351)	 WevtPow2Gen= EvtWeight *1.75124;
	 if(mWW > 351 && mWW <= 364)	 WevtPow2Gen= EvtWeight *1.84265;
	 if(mWW > 364 && mWW <= 377)	 WevtPow2Gen= EvtWeight *4.03778;
	 if(mWW > 377 && mWW <= 390)	 WevtPow2Gen= EvtWeight *3.17174;
	 if(mWW > 390 && mWW <= 403)	 WevtPow2Gen= EvtWeight *2.31893;
	 if(mWW > 403 && mWW <= 416)	 WevtPow2Gen= EvtWeight *2.6283;
	 if(mWW > 416 && mWW <= 429)	 WevtPow2Gen= EvtWeight *3.5248;
	 if(mWW > 429 && mWW <= 442)	 WevtPow2Gen= EvtWeight *3.27349;
	 if(mWW > 442 && mWW <= 455)	 WevtPow2Gen= EvtWeight *3.1872;
	 if(mWW > 455 && mWW <= 468)	 WevtPow2Gen= EvtWeight *3.74006;
	 if(mWW > 468 && mWW <= 481)	 WevtPow2Gen= EvtWeight *3.86135;
	 if(mWW > 481 && mWW <= 494)	 WevtPow2Gen= EvtWeight *4.19688;
	 if(mWW > 494 && mWW <= 507)	 WevtPow2Gen= EvtWeight *3.97097;
	 if(mWW > 507 && mWW <= 520)	 WevtPow2Gen= EvtWeight *3.92828;
	 if(mWW > 520 && mWW <= 533)	 WevtPow2Gen= EvtWeight *4.33001;
	 if(mWW > 533 && mWW <= 546)	 WevtPow2Gen= EvtWeight *4.81427;
	 if(mWW > 546 && mWW <= 559)	 WevtPow2Gen= EvtWeight *4.68825;
	 if(mWW > 559 && mWW <= 572)	 WevtPow2Gen= EvtWeight *4.73319;
	 if(mWW > 572 && mWW <= 585)	 WevtPow2Gen= EvtWeight *7.16026;
	 if(mWW > 585 && mWW <= 598)	 WevtPow2Gen= EvtWeight *6.02728;
	 if(mWW > 598 && mWW <= 611)	 WevtPow2Gen= EvtWeight *6.05842;
	 if(mWW > 611 && mWW <= 624)	 WevtPow2Gen= EvtWeight *7.89105;
	 if(mWW > 624 && mWW <= 637)	 WevtPow2Gen= EvtWeight *9.86079;
	 if(mWW > 637 && mWW <= 650)	 WevtPow2Gen= EvtWeight *9.54183;
	 if(mWW > 650 && mWW <= 663)	 WevtPow2Gen= EvtWeight *13.7482;
	 if(mWW > 663 && mWW <= 676)	 WevtPow2Gen= EvtWeight *10.1112;
	 if(mWW > 676 && mWW <= 689)	 WevtPow2Gen= EvtWeight *13.2272;
	 if(mWW > 689 && mWW <= 702)	 WevtPow2Gen= EvtWeight *11.3759;
	 if(mWW > 702 && mWW <= 715)	 WevtPow2Gen= EvtWeight *10.0086;
	 if(mWW > 715 && mWW <= 728)	 WevtPow2Gen= EvtWeight *16.4725;
	 if(mWW > 728 && mWW <= 741)	 WevtPow2Gen= EvtWeight *16.8634;
	 if(mWW > 741 && mWW <= 754)	 WevtPow2Gen= EvtWeight *14.991;
	 if(mWW > 754 && mWW <= 767)	 WevtPow2Gen= EvtWeight *15.2637;
	 if(mWW > 767 && mWW <= 780)	 WevtPow2Gen= EvtWeight *20.0403;
	 if(mWW > 780 && mWW <= 793)	 WevtPow2Gen= EvtWeight *17.5664;
	 if(mWW > 793 && mWW <= 806)	 WevtPow2Gen= EvtWeight *19.5776;
	 if(mWW > 806 && mWW <= 819)	 WevtPow2Gen= EvtWeight *18.7711;
	 if(mWW > 819 && mWW <= 832)	 WevtPow2Gen= EvtWeight *21.3503;
	 if(mWW > 832 && mWW <= 845)	 WevtPow2Gen= EvtWeight *19.1523;
	 if(mWW > 845 && mWW <= 858)	 WevtPow2Gen= EvtWeight *18.4445;
	 if(mWW > 858 && mWW <= 871)	 WevtPow2Gen= EvtWeight *24.2383;
	 if(mWW > 871 && mWW <= 884)	 WevtPow2Gen= EvtWeight *27.6952;
	 if(mWW > 884 && mWW <= 897)	 WevtPow2Gen= EvtWeight *24.6543;
	 if(mWW > 897 && mWW <= 910)	 WevtPow2Gen= EvtWeight *27.4673;
	 if(mWW > 910 && mWW <= 923)	 WevtPow2Gen= EvtWeight *29.985;
	 if(mWW > 923 && mWW <= 936)	 WevtPow2Gen= EvtWeight *30.7625;
	 if(mWW > 936 && mWW <= 949)	 WevtPow2Gen= EvtWeight *34.7191;
	 if(mWW > 949 && mWW <= 962)	 WevtPow2Gen= EvtWeight *46.4543;
	 if(mWW > 962 && mWW <= 975)	 WevtPow2Gen= EvtWeight *36.1743;
	 if(mWW > 975 && mWW <= 988)	 WevtPow2Gen= EvtWeight *42.5985;
	 if(mWW > 988 && mWW <= 1001)	 WevtPow2Gen= EvtWeight *36.0012;
	 if(mWW > 1001 && mWW <= 1014)	 WevtPow2Gen= EvtWeight *55.3427;
	 if(mWW > 1014 && mWW <= 1027)	 WevtPow2Gen= EvtWeight *41.6807;
	 if(mWW > 1027 && mWW <= 1040)	 WevtPow2Gen= EvtWeight *48.3046;
	 if(mWW > 1040 && mWW <= 1053)	 WevtPow2Gen= EvtWeight *52.0242;
	 if(mWW > 1053 && mWW <= 1066)	 WevtPow2Gen= EvtWeight *49.733;
	 if(mWW > 1066 && mWW <= 1079)	 WevtPow2Gen= EvtWeight *63.781;
	 if(mWW > 1079 && mWW <= 1092)	 WevtPow2Gen= EvtWeight *65.3324;
	 if(mWW > 1092 && mWW <= 1105)	 WevtPow2Gen= EvtWeight *66.9966;
	 if(mWW > 1105 && mWW <= 1118)	 WevtPow2Gen= EvtWeight *65.9971;
	 if(mWW > 1118 && mWW <= 1131)	 WevtPow2Gen= EvtWeight *91.2544;
	 if(mWW > 1131 && mWW <= 1144)	 WevtPow2Gen= EvtWeight *65.9611;
	 if(mWW > 1144 && mWW <= 1157)	 WevtPow2Gen= EvtWeight *100.192;
	 if(mWW > 1157 && mWW <= 1170)	 WevtPow2Gen= EvtWeight *97.1083;
	 if(mWW > 1170 && mWW <= 1183)	 WevtPow2Gen= EvtWeight *85.1929;
	 if(mWW > 1183 && mWW <= 1196)	 WevtPow2Gen= EvtWeight *119.801;
	 if(mWW > 1196 && mWW <= 1209)	 WevtPow2Gen= EvtWeight *108.326;
	 if(mWW > 1209 && mWW <= 1222)	 WevtPow2Gen= EvtWeight *137.84;
	 if(mWW > 1222 && mWW <= 1235)	 WevtPow2Gen= EvtWeight *148.795;
	 if(mWW > 1235 && mWW <= 1248)	 WevtPow2Gen= EvtWeight *134.42;
	 if(mWW > 1248 && mWW <= 1261)	 WevtPow2Gen= EvtWeight *125.041;
	 if(mWW > 1261 && mWW <= 1274)	 WevtPow2Gen= EvtWeight *126.937;
	 if(mWW > 1274 && mWW <= 1287)	 WevtPow2Gen= EvtWeight *210.181;
	 if(mWW > 1287 && mWW <= 1300)	 WevtPow2Gen= EvtWeight *143;
	 if(mWW > 1300 && mWW <= 1313)	 WevtPow2Gen= EvtWeight *123.988;
	 if(mWW > 1313 && mWW <= 1326)	 WevtPow2Gen= EvtWeight *161.646;
	 if(mWW > 1326 && mWW <= 1339)	 WevtPow2Gen= EvtWeight *151.111;
	 if(mWW > 1339 && mWW <= 1352)	 WevtPow2Gen= EvtWeight *218.396;
	 if(mWW > 1352 && mWW <= 1365)	 WevtPow2Gen= EvtWeight *231.691;
	 if(mWW > 1365 && mWW <= 1378)	 WevtPow2Gen= EvtWeight *254.19;
	 if(mWW > 1378 && mWW <= 1391)	 WevtPow2Gen= EvtWeight *210.999;
	 if(mWW > 1391 && mWW <= 1404)	 WevtPow2Gen= EvtWeight *234.494;
	 if(mWW > 1404 && mWW <= 1417)	 WevtPow2Gen= EvtWeight *172.471;
	 if(mWW > 1417 && mWW <= 1430)	 WevtPow2Gen= EvtWeight *216.623;


	 if(mWW > 1430 && mWW <= 1434)	 WevtPow2Gen= EvtWeight *418.315;
	 if(mWW > 1434 && mWW <= 1445)	 WevtPow2Gen= EvtWeight *398.415;
	 if(mWW > 1445 && mWW <= 1456)	 WevtPow2Gen= EvtWeight *319.643;
	 if(mWW > 1456 && mWW <= 1467)	 WevtPow2Gen= EvtWeight *461.978;
	 if(mWW > 1467 && mWW <= 1478)	 WevtPow2Gen= EvtWeight *460.139;
	 if(mWW > 1478 && mWW <= 1489)	 WevtPow2Gen= EvtWeight *585.044;
	 if(mWW > 1489 )	 WevtPow2Gen= EvtWeight *617.698;
#endif


      //
      // VBF Cut without center jet veto
	// if( mWW <= 100)	 WevtPow2Gen= EvtWeight *0;
	// if(mWW > 100 && mWW <= 150)	 WevtPow2Gen= EvtWeight *0.0372618;
	// if(mWW > 150 && mWW <= 200)	 WevtPow2Gen= EvtWeight *0.193659;
	// if(mWW > 200 && mWW <= 250)	 WevtPow2Gen= EvtWeight *1.85815;
	// if(mWW > 250 && mWW <= 300)	 WevtPow2Gen= EvtWeight *1.73352;
	// if(mWW > 300 && mWW <= 350)	 WevtPow2Gen= EvtWeight *1.92232;
	// if(mWW > 350 && mWW <= 400)	 WevtPow2Gen= EvtWeight *2.25595;
	// if(mWW > 400 && mWW <= 450)	 WevtPow2Gen= EvtWeight *3.13837;
	// if(mWW > 450 && mWW <= 500)	 WevtPow2Gen= EvtWeight *3.66799;
	// if(mWW > 500 && mWW <= 550)	 WevtPow2Gen= EvtWeight *4.86068;
	// if(mWW > 550 && mWW <= 600)	 WevtPow2Gen= EvtWeight *6.26024;
	// if(mWW > 600 && mWW <= 650)	 WevtPow2Gen= EvtWeight *9.07783;
	// if(mWW > 650 && mWW <= 700)	 WevtPow2Gen= EvtWeight *12.8086;
	// if(mWW > 700 && mWW <= 750)	 WevtPow2Gen= EvtWeight *16.7139;
	// if(mWW > 750 && mWW <= 800)	 WevtPow2Gen= EvtWeight *18.8401;
	// if(mWW > 800 && mWW <= 850)	 WevtPow2Gen= EvtWeight *22.0173;
	// if(mWW > 850 && mWW <= 900)	 WevtPow2Gen= EvtWeight *24.3131;
	// if(mWW > 900 && mWW <= 950)	 WevtPow2Gen= EvtWeight *34.1954;
	// if(mWW > 950 && mWW <= 1000)	 WevtPow2Gen= EvtWeight *47.3046;
	// if(mWW > 1000 && mWW <= 1050)	 WevtPow2Gen= EvtWeight *58.556;
	// if(mWW > 1050 && mWW <= 1100)	 WevtPow2Gen= EvtWeight *69.2101;
	// if(mWW > 1100 && mWW <= 1150)	 WevtPow2Gen= EvtWeight *80.5022;
	// if(mWW > 1150 && mWW <= 1200)	 WevtPow2Gen= EvtWeight *103.767;
	// if(mWW > 1200 && mWW <= 1250)	 WevtPow2Gen= EvtWeight *133.35;
	// if(mWW > 1250 && mWW <= 1300)	 WevtPow2Gen= EvtWeight *188.21;
	// if(mWW > 1300 && mWW <= 1350)	 WevtPow2Gen= EvtWeight *166.798;
	// if(mWW > 1350 && mWW <= 1400)	 WevtPow2Gen= EvtWeight *281.304;
	// if(mWW > 1400 && mWW <= 1450)	 WevtPow2Gen= EvtWeight *418.985;
	// if(mWW > 1450 && mWW <= 1500)	 WevtPow2Gen= EvtWeight *337.312;
      //
      //
      //
      //
      // Without VBF Cut
      //if(             mWW <= 100)  WevtPow2Gen= EvtWeight *0;
      //if(mWW > 100 && mWW <= 150)  WevtPow2Gen= EvtWeight *0.0550216;
      //if(mWW > 150 && mWW <= 200)  WevtPow2Gen= EvtWeight *0.203043;
      //if(mWW > 200 && mWW <= 250)  WevtPow2Gen= EvtWeight *1.6185;
      //if(mWW > 250 && mWW <= 300)  WevtPow2Gen= EvtWeight *1.46889;
      //if(mWW > 300 && mWW <= 350)  WevtPow2Gen= EvtWeight *1.94218;
      //if(mWW > 350 && mWW <= 400)  WevtPow2Gen= EvtWeight *2.45464;
      //if(mWW > 400 && mWW <= 450)  WevtPow2Gen= EvtWeight *3.44705;
      //if(mWW > 450 && mWW <= 500)  WevtPow2Gen= EvtWeight *4.29206;
      //if(mWW > 500 && mWW <= 550)  WevtPow2Gen= EvtWeight *5.18598;
      //if(mWW > 550 && mWW <= 600)  WevtPow2Gen= EvtWeight *6.89927;
      //if(mWW > 600 && mWW <= 650)  WevtPow2Gen= EvtWeight *10.6168;
      //if(mWW > 650 && mWW <= 700)  WevtPow2Gen= EvtWeight *14.8114;
      //if(mWW > 700 && mWW <= 750)  WevtPow2Gen= EvtWeight *20.8833;
      //if(mWW > 750 && mWW <= 800)  WevtPow2Gen= EvtWeight *20.4456;
      //if(mWW > 800 && mWW <= 850)  WevtPow2Gen= EvtWeight *27.4497;
      //if(mWW > 850 && mWW <= 900)  WevtPow2Gen= EvtWeight *32.24;
      //if(mWW > 900 && mWW <= 950)  WevtPow2Gen= EvtWeight *38.6845;
      //if(mWW > 950 && mWW <= 1000) WevtPow2Gen= EvtWeight *56.1421;
      //if(mWW > 1000 && mWW <= 1050)WevtPow2Gen= EvtWeight *52.0246;
      //if(mWW > 1050 && mWW <= 1100)WevtPow2Gen= EvtWeight *90.8438;
      //if(mWW > 1100 && mWW <= 1150)WevtPow2Gen= EvtWeight *102.309;
      //if(mWW > 1150 && mWW <= 1200)WevtPow2Gen= EvtWeight *124.899;
      //if(mWW > 1200 && mWW <= 1250)WevtPow2Gen= EvtWeight *160.725;
      //if(mWW > 1250 && mWW <= 1300)WevtPow2Gen= EvtWeight *243.644;
      //if(mWW > 1300 && mWW <= 1350)WevtPow2Gen= EvtWeight *230.913;
      //if(mWW > 1350 && mWW <= 1400)WevtPow2Gen= EvtWeight *327.961;
      //if(mWW > 1400 && mWW <= 1450)WevtPow2Gen= EvtWeight *475.712;
      //if(mWW > 1450 && mWW <= 1500)WevtPow2Gen= EvtWeight *454.708;
      //VBF ctVeto mjj500 nj3
#if REWEIGHT == 2
	if(             mWW <= 100)	 WevtPow2Gen= EvtWeight *0;
	if(mWW > 100 && mWW <= 150)	 WevtPow2Gen= EvtWeight *0.0102222;
	if(mWW > 150 && mWW <= 200)	 WevtPow2Gen= EvtWeight *0.214728;
	if(mWW > 200 && mWW <= 250)	 WevtPow2Gen= EvtWeight *1.07133;
	if(mWW > 250 && mWW <= 300)	 WevtPow2Gen= EvtWeight *1.34311;
	if(mWW > 300 && mWW <= 350)	 WevtPow2Gen= EvtWeight *1.34613;
	if(mWW > 350 && mWW <= 400)	 WevtPow2Gen= EvtWeight *0.628382;
	if(mWW > 400 && mWW <= 450)	 WevtPow2Gen= EvtWeight *4.84683;
	if(mWW > 450 && mWW <= 500)	 WevtPow2Gen= EvtWeight *6.829;
	if(mWW > 500 && mWW <= 550)	 WevtPow2Gen= EvtWeight *4.66017;
	if(mWW > 550 && mWW <= 600)	 WevtPow2Gen= EvtWeight *5.17772;
	if(mWW > 600 && mWW <= 650)	 WevtPow2Gen= EvtWeight *15.0567;
	if(mWW > 650 && mWW <= 700)	 WevtPow2Gen= EvtWeight *14.1738;
	if(mWW > 700 && mWW <= 750)	 WevtPow2Gen= EvtWeight *27.8694;
	if(mWW > 750 && mWW <= 800)	 WevtPow2Gen= EvtWeight *32.8749;
	if(mWW > 800 && mWW <= 850)	 WevtPow2Gen= EvtWeight *23.6391;
	if(mWW > 850 && mWW <= 900)	 WevtPow2Gen= EvtWeight *46.1452;
	if(mWW > 900 && mWW <= 950)	 WevtPow2Gen= EvtWeight *53.4986;
	if(mWW > 950 && mWW <= 1000)	 WevtPow2Gen= EvtWeight *82.0739;
	if(mWW > 1000 && mWW <= 1050)	 WevtPow2Gen= EvtWeight *68.3463;
	if(mWW > 1050 && mWW <= 1100)	 WevtPow2Gen= EvtWeight *133.917;
	if(mWW > 1100 && mWW <= 1150)	 WevtPow2Gen= EvtWeight *153.06;
	if(mWW > 1150 && mWW <= 1200)	 WevtPow2Gen= EvtWeight *111.759;
	if(mWW > 1200 && mWW <= 1250)	 WevtPow2Gen= EvtWeight *223.613;
	if(mWW > 1250 && mWW <= 1300)	 WevtPow2Gen= EvtWeight *358.234;
	if(mWW > 1300 && mWW <= 1350)	 WevtPow2Gen= EvtWeight *227.722;
	if(mWW > 1350 && mWW <= 1400)	 WevtPow2Gen= EvtWeight *598.68;
	if(mWW > 1400 && mWW <= 1450)	 WevtPow2Gen= EvtWeight *95.808;
	if(mWW > 1450 && mWW <= 1500)	 WevtPow2Gen= EvtWeight *0;
#endif

#if REWEIGHT == 3
      //
      //mjj 300 njet 2.3
	 if(             mWW <= 100)	 WevtPow2Gen= EvtWeight *0;
	 if(mWW > 100 && mWW <= 150)	 WevtPow2Gen= EvtWeight *0.0447568;
	 if(mWW > 150 && mWW <= 200)	 WevtPow2Gen= EvtWeight *0.21264;
	 if(mWW > 200 && mWW <= 250)	 WevtPow2Gen= EvtWeight *2.06641;
	 if(mWW > 250 && mWW <= 300)	 WevtPow2Gen= EvtWeight *1.70796;
	 if(mWW > 300 && mWW <= 350)	 WevtPow2Gen= EvtWeight *2.14422;
	 if(mWW > 350 && mWW <= 400)	 WevtPow2Gen= EvtWeight *2.54918;
	 if(mWW > 400 && mWW <= 450)	 WevtPow2Gen= EvtWeight *3.55034;
	 if(mWW > 450 && mWW <= 500)	 WevtPow2Gen= EvtWeight *4.07274;
	 if(mWW > 500 && mWW <= 550)	 WevtPow2Gen= EvtWeight *5.06353;
	 if(mWW > 550 && mWW <= 600)	 WevtPow2Gen= EvtWeight *5.83332;
	 if(mWW > 600 && mWW <= 650)	 WevtPow2Gen= EvtWeight *10.2089;
	 if(mWW > 650 && mWW <= 700)	 WevtPow2Gen= EvtWeight *14.0521;
	 if(mWW > 700 && mWW <= 750)	 WevtPow2Gen= EvtWeight *18.4153;
	 if(mWW > 750 && mWW <= 800)	 WevtPow2Gen= EvtWeight *21.496;
	 if(mWW > 800 && mWW <= 850)	 WevtPow2Gen= EvtWeight *25.2915;
	 if(mWW > 850 && mWW <= 900)	 WevtPow2Gen= EvtWeight *26.266;
	 if(mWW > 900 && mWW <= 950)	 WevtPow2Gen= EvtWeight *31.7399;
	 if(mWW > 950 && mWW <= 1000)	 WevtPow2Gen= EvtWeight *50.2364;
	 if(mWW > 1000 && mWW <= 1050)	 WevtPow2Gen= EvtWeight *61.6709;
	 if(mWW > 1050 && mWW <= 1100)	 WevtPow2Gen= EvtWeight *72.9291;
	 if(mWW > 1100 && mWW <= 1150)	 WevtPow2Gen= EvtWeight *86.5085;
	 if(mWW > 1150 && mWW <= 1200)	 WevtPow2Gen= EvtWeight *141.137;
	 if(mWW > 1200 && mWW <= 1250)	 WevtPow2Gen= EvtWeight *146.798;
	 if(mWW > 1250 && mWW <= 1300)	 WevtPow2Gen= EvtWeight *171.091;
	 if(mWW > 1300 && mWW <= 1350)	 WevtPow2Gen= EvtWeight *154.853;
	 if(mWW > 1350 && mWW <= 1400)	 WevtPow2Gen= EvtWeight *314.15;
	 if(mWW > 1400 && mWW <= 1450)	 WevtPow2Gen= EvtWeight *418.172;
	 if(mWW > 1450 && mWW <= 1500)	 WevtPow2Gen= EvtWeight *456.45;
#endif
	//
	// mjj 300 njet >=3
      
	// if(             mWW <= 100)	 WevtPow2Gen= EvtWeight *0;
	// if(mWW > 100 && mWW <= 150)	 WevtPow2Gen= EvtWeight *0.0336382;
	// if(mWW > 150 && mWW <= 200)	 WevtPow2Gen= EvtWeight *0.235092;
	// if(mWW > 200 && mWW <= 250)	 WevtPow2Gen= EvtWeight *1.63826;
	// if(mWW > 250 && mWW <= 300)	 WevtPow2Gen= EvtWeight *1.45798;
	// if(mWW > 300 && mWW <= 350)	 WevtPow2Gen= EvtWeight *2.2227;
	// if(mWW > 350 && mWW <= 400)	 WevtPow2Gen= EvtWeight *0.927127;
	// if(mWW > 400 && mWW <= 450)	 WevtPow2Gen= EvtWeight *4.12511;
	// if(mWW > 450 && mWW <= 500)	 WevtPow2Gen= EvtWeight *6.19297;
	// if(mWW > 500 && mWW <= 550)	 WevtPow2Gen= EvtWeight *4.45781;
	// if(mWW > 550 && mWW <= 600)	 WevtPow2Gen= EvtWeight *4.9977;
	// if(mWW > 600 && mWW <= 650)	 WevtPow2Gen= EvtWeight *15.2351;
	// if(mWW > 650 && mWW <= 700)	 WevtPow2Gen= EvtWeight *15.5674;
	// if(mWW > 700 && mWW <= 750)	 WevtPow2Gen= EvtWeight *26.4302;
	// if(mWW > 750 && mWW <= 800)	 WevtPow2Gen= EvtWeight *33.8956;
	// if(mWW > 800 && mWW <= 850)	 WevtPow2Gen= EvtWeight *31.1315;
	// if(mWW > 850 && mWW <= 900)	 WevtPow2Gen= EvtWeight *47.3308;
	// if(mWW > 900 && mWW <= 950)	 WevtPow2Gen= EvtWeight *47.2902;
	// if(mWW > 950 && mWW <= 1000)	 WevtPow2Gen= EvtWeight *82.0697;
	// if(mWW > 1000 && mWW <= 1050)	 WevtPow2Gen= EvtWeight *77.9094;
	// if(mWW > 1050 && mWW <= 1100)	 WevtPow2Gen= EvtWeight *136.003;
	// if(mWW > 1100 && mWW <= 1150)	 WevtPow2Gen= EvtWeight *152.698;
	// if(mWW > 1150 && mWW <= 1200)	 WevtPow2Gen= EvtWeight *145.185;
	// if(mWW > 1200 && mWW <= 1250)	 WevtPow2Gen= EvtWeight *207.587;
	// if(mWW > 1250 && mWW <= 1300)	 WevtPow2Gen= EvtWeight *343.54;
	// if(mWW > 1300 && mWW <= 1350)	 WevtPow2Gen= EvtWeight *214.527;
	// if(mWW > 1350 && mWW <= 1400)	 WevtPow2Gen= EvtWeight *612.928;
	// if(mWW > 1400 && mWW <= 1450)	 WevtPow2Gen= EvtWeight *124.388;
	// if(mWW > 1450 && mWW <= 1500)	 WevtPow2Gen= EvtWeight *0;
      
      //
}
void HWwNjetStudy::Calc_Pow_Weight()
{
      //Step1 reweighting Powheg to gg2VV
      //if(mWW > 130 && mWW <= 140)WevtPow2Gen= EvtWeight *0;
      //if(mWW > 140 && mWW <= 150)WevtPow2Gen= EvtWeight *51.1303;
      //if(mWW > 150 && mWW <= 160)WevtPow2Gen= EvtWeight *0.0478779;
      //if(mWW > 160 && mWW <= 170)WevtPow2Gen= EvtWeight *0.122384;
      //if(mWW > 170 && mWW <= 180)WevtPow2Gen= EvtWeight *0.148526;
      //if(mWW > 180 && mWW <= 190)WevtPow2Gen= EvtWeight *0.189493;
      //if(mWW > 190 && mWW <= 200)WevtPow2Gen= EvtWeight *0.23596;
      //if(mWW > 200 && mWW <= 210)WevtPow2Gen= EvtWeight *0.48091;
      //if(mWW > 210 && mWW <= 220)WevtPow2Gen= EvtWeight *19.4147;
      //if(mWW > 220 && mWW <= 230)WevtPow2Gen= EvtWeight *22.3205;
      //if(mWW > 230 && mWW <= 240)WevtPow2Gen= EvtWeight *7.22016;
      //if(mWW > 240 && mWW <= 250)WevtPow2Gen= EvtWeight *0.62342;
      //if(mWW > 250 && mWW <= 260)WevtPow2Gen= EvtWeight *0.613474;
      //if(mWW > 260 && mWW <= 270)WevtPow2Gen= EvtWeight *5.97016;
      //if(mWW > 270 && mWW <= 280)WevtPow2Gen= EvtWeight *7.93497;
      //if(mWW > 280 && mWW <= 290)WevtPow2Gen= EvtWeight *4.19944;
      //if(mWW > 290 && mWW <= 300)WevtPow2Gen= EvtWeight *0.769442;
      //if(mWW > 300 && mWW <= 310)WevtPow2Gen= EvtWeight *0.757447;
      //if(mWW > 310 && mWW <= 320)WevtPow2Gen= EvtWeight *5.3415;
      //if(mWW > 320 && mWW <= 330)WevtPow2Gen= EvtWeight *10.2543;
      //if(mWW > 330 && mWW <= 340)WevtPow2Gen= EvtWeight *15.1817;
      //if(mWW > 340 && mWW <= 350)WevtPow2Gen= EvtWeight *15.8538;
      //if(mWW > 350 && mWW <= 360)WevtPow2Gen= EvtWeight *16.8142;
      //if(mWW > 360 && mWW <= 370)WevtPow2Gen= EvtWeight *12.5228;
      //if(mWW > 370 && mWW <= 380)WevtPow2Gen= EvtWeight *7.53283;
      //if(mWW > 380 && mWW <= 390)WevtPow2Gen= EvtWeight *4.15059;
      //if(mWW > 390 && mWW <= 400)WevtPow2Gen= EvtWeight *2.46605;
      //if(mWW > 400 && mWW <= 410)WevtPow2Gen= EvtWeight *2.79782;
      //if(mWW > 410 && mWW <= 420)WevtPow2Gen= EvtWeight *4.55461;
      //if(mWW > 420 && mWW <= 430)WevtPow2Gen= EvtWeight *6.92859;
      //if(mWW > 430 && mWW <= 440)WevtPow2Gen= EvtWeight *10.0075;
      //if(mWW > 440 && mWW <= 450)WevtPow2Gen= EvtWeight *10.9316;
      //if(mWW > 450 && mWW <= 460)WevtPow2Gen= EvtWeight *10.983;
      //if(mWW > 460 && mWW <= 470)WevtPow2Gen= EvtWeight *10.5683;
      //if(mWW > 470 && mWW <= 480)WevtPow2Gen= EvtWeight *7.84492;
      //if(mWW > 480 && mWW <= 490)WevtPow2Gen= EvtWeight *6.04171;
      //if(mWW > 490 && mWW <= 500)WevtPow2Gen= EvtWeight *6.34104;
      //if(mWW > 500 && mWW <= 510)WevtPow2Gen= EvtWeight *5.87117;
      //if(mWW > 510 && mWW <= 520)WevtPow2Gen= EvtWeight *7.04725;
      //if(mWW > 520 && mWW <= 530)WevtPow2Gen= EvtWeight *8.05815;
      //if(mWW > 530 && mWW <= 540)WevtPow2Gen= EvtWeight *9.74238;
      //if(mWW > 540 && mWW <= 550)WevtPow2Gen= EvtWeight *10.8453;
      //if(mWW > 550 && mWW <= 560)WevtPow2Gen= EvtWeight *9.67099;
      //if(mWW > 560 && mWW <= 570)WevtPow2Gen= EvtWeight *10.8926;
      //if(mWW > 570 && mWW <= 580)WevtPow2Gen= EvtWeight *10.4321;
      //if(mWW > 580 && mWW <= 590)WevtPow2Gen= EvtWeight *10.7205;
      //if(mWW > 590 && mWW <= 600)WevtPow2Gen= EvtWeight *10.8797;
      //if(mWW > 600 && mWW <= 610)WevtPow2Gen= EvtWeight *11.4627;
      //if(mWW > 610 && mWW <= 620)WevtPow2Gen= EvtWeight *10.0712;
      //if(mWW > 620 && mWW <= 630)WevtPow2Gen= EvtWeight *10.759;
      //if(mWW > 630 && mWW <= 640)WevtPow2Gen= EvtWeight *12.9894;
      //if(mWW > 640 && mWW <= 650)WevtPow2Gen= EvtWeight *15.5317;
      //if(mWW > 650 && mWW <= 660)WevtPow2Gen= EvtWeight *20.0885;
      //if(mWW > 660 && mWW <= 670)WevtPow2Gen= EvtWeight *18.7505;
      //if(mWW > 670 && mWW <= 680)WevtPow2Gen= EvtWeight *19.5823;
      //if(mWW > 680 && mWW <= 690)WevtPow2Gen= EvtWeight *18.7507;
      //if(mWW > 690 && mWW <= 700)WevtPow2Gen= EvtWeight *24.2711;
      //if(mWW > 700 && mWW <= 710)WevtPow2Gen= EvtWeight *27.1249;
      //if(mWW > 710 && mWW <= 720)WevtPow2Gen= EvtWeight *26.0178;
      //if(mWW > 720 && mWW <= 730)WevtPow2Gen= EvtWeight *30.3208;
      //if(mWW > 730 && mWW <= 740)WevtPow2Gen= EvtWeight *42.7271;
      //if(mWW > 740 && mWW <= 750)WevtPow2Gen= EvtWeight *28.9253;
      //if(mWW > 750 && mWW <= 760)WevtPow2Gen= EvtWeight *31.6985;
      //if(mWW > 760 && mWW <= 770)WevtPow2Gen= EvtWeight *43.9006;
      //if(mWW > 770 && mWW <= 780)WevtPow2Gen= EvtWeight *43.8016;
      //if(mWW > 780 && mWW <= 790)WevtPow2Gen= EvtWeight *32.9426;
      //if(mWW > 790 && mWW <= 800)WevtPow2Gen= EvtWeight *60.615;
      //if(mWW > 800 && mWW <= 810)WevtPow2Gen= EvtWeight *32.0942;
      //if(mWW > 810 && mWW <= 820)WevtPow2Gen= EvtWeight *28.3471;
      //if(mWW > 820 && mWW <= 830)WevtPow2Gen= EvtWeight *44.8383;
      //if(mWW > 830 && mWW <= 840)WevtPow2Gen= EvtWeight *31.2978;
      //if(mWW > 840 && mWW <= 850)WevtPow2Gen= EvtWeight *41.6292;
      //if(mWW > 850 && mWW <= 860)WevtPow2Gen= EvtWeight *55.7313;
      //if(mWW > 860 && mWW <= 870)WevtPow2Gen= EvtWeight *37.3944;
      //if(mWW > 870 && mWW <= 880)WevtPow2Gen= EvtWeight *45.1447;
      //if(mWW > 880 && mWW <= 890)WevtPow2Gen= EvtWeight *45.2296;
      //if(mWW > 890 && mWW <= 900)WevtPow2Gen= EvtWeight *55.7684;
      //if(mWW > 900 && mWW <= 910)WevtPow2Gen= EvtWeight *62.7376;
      //if(mWW > 910 && mWW <= 920)WevtPow2Gen= EvtWeight *55.7921;
      //if(mWW > 920 && mWW <= 930)WevtPow2Gen= EvtWeight *54.3934;
      //if(mWW > 930 && mWW <= 940)WevtPow2Gen= EvtWeight *102.145;
      //if(mWW > 940 && mWW <= 950)WevtPow2Gen= EvtWeight *37.2144;
      //if(mWW > 950 && mWW <= 960)WevtPow2Gen= EvtWeight *50.58;
      //if(mWW > 960 && mWW <= 970)WevtPow2Gen= EvtWeight *44.3337;
      //if(mWW > 970 && mWW <= 980)WevtPow2Gen= EvtWeight *60.3516;
      //if(mWW > 980 && mWW <= 990)WevtPow2Gen= EvtWeight *74.0306;
      //if(mWW > 990 && mWW <= 1000)WevtPow2Gen= EvtWeight *67.2666;
      //if(mWW > 1000 && mWW <= 1010)WevtPow2Gen= EvtWeight *19.5773;
      //if(mWW > 1010 && mWW <= 1020)WevtPow2Gen= EvtWeight *66.0482;
      //if(mWW > 1020 && mWW <= 1030)WevtPow2Gen= EvtWeight *73.4724;
      //if(mWW > 1030 && mWW <= 1040)WevtPow2Gen= EvtWeight *44.6105;
      //if(mWW > 1040 && mWW <= 1050)WevtPow2Gen= EvtWeight *95.411;
      //if(mWW > 1050 && mWW <= 1060)WevtPow2Gen= EvtWeight *81.114;
      //if(mWW > 1060 && mWW <= 1070)WevtPow2Gen= EvtWeight *42.0407;
      //if(mWW > 1070 && mWW <= 1080)WevtPow2Gen= EvtWeight *116.167;
      //if(mWW > 1080 && mWW <= 1090)WevtPow2Gen= EvtWeight *118.585;
      //if(mWW > 1090 && mWW <= 1100)WevtPow2Gen= EvtWeight *50.1939;
      //if(mWW > 1100 && mWW <= 1110)WevtPow2Gen= EvtWeight *81.9378;
      //if(mWW > 1110 && mWW <= 1120)WevtPow2Gen= EvtWeight *50.4567;
      //if(mWW > 1120 && mWW <= 1130)WevtPow2Gen= EvtWeight *70.9683;
      //if(mWW > 1130 && mWW <= 1140)WevtPow2Gen= EvtWeight *18.4721;
      //if(mWW > 1140 && mWW <= 1150)WevtPow2Gen= EvtWeight *53.0915;
      //if(mWW > 1150 && mWW <= 1160)WevtPow2Gen= EvtWeight *47.0092;
      //if(mWW > 1160 && mWW <= 1170)WevtPow2Gen= EvtWeight *42.3676;
      //if(mWW > 1170 && mWW <= 1180)WevtPow2Gen= EvtWeight *53.8578;
      //if(mWW > 1180 && mWW <= 1190)WevtPow2Gen= EvtWeight *142.918;
      //if(mWW > 1190 && mWW <= 1200)WevtPow2Gen= EvtWeight *43.5121;
      //if(mWW > 1200 && mWW <= 1210)WevtPow2Gen= EvtWeight *64.1233;
      //if(mWW > 1210 && mWW <= 1220)WevtPow2Gen= EvtWeight *18.6497;
      //if(mWW > 1220 && mWW <= 1230)WevtPow2Gen= EvtWeight *148.524;
      //if(mWW > 1230 && mWW <= 1240)WevtPow2Gen= EvtWeight *53.3047;
      //if(mWW > 1240 && mWW <= 1250)WevtPow2Gen= EvtWeight *174.73;
      //if(mWW > 1250 && mWW <= 1260)WevtPow2Gen= EvtWeight *82.8151;
      //if(mWW > 1260 && mWW <= 1270)WevtPow2Gen= EvtWeight *76.0686;
      //if(mWW > 1270 && mWW <= 1280)WevtPow2Gen= EvtWeight *224.172;
      //if(mWW > 1280 && mWW <= 1290)WevtPow2Gen= EvtWeight *95.0422;
      //if(mWW > 1290 && mWW <= 1300)WevtPow2Gen= EvtWeight *140.862;
      //if(mWW > 1300 && mWW <= 1310)WevtPow2Gen= EvtWeight *332.692;
      //if(mWW > 1310 && mWW <= 1320)WevtPow2Gen= EvtWeight *122.033;
      //if(mWW > 1320 && mWW <= 1330)WevtPow2Gen= EvtWeight *300.629;
      //if(mWW > 1330 && mWW <= 1340)WevtPow2Gen= EvtWeight *84.3002;
      //if(mWW > 1340 && mWW <= 1350)WevtPow2Gen= EvtWeight *0;
      //if(mWW > 1350 && mWW <= 1360)WevtPow2Gen= EvtWeight *0;
      //if(mWW > 1360 && mWW <= 1370)WevtPow2Gen= EvtWeight *303.616;
      //if(mWW > 1370 && mWW <= 1380)WevtPow2Gen= EvtWeight *88.6832;
      //if(mWW > 1380 && mWW <= 1390)WevtPow2Gen= EvtWeight *47.9035;
      //if(mWW > 1390 && mWW <= 1400)WevtPow2Gen= EvtWeight *3160.08;
      //if(mWW > 1400 && mWW <= 1410)WevtPow2Gen= EvtWeight *0;
      //if(mWW > 1410 && mWW <= 1420)WevtPow2Gen= EvtWeight *0;
      //if(mWW > 1420 && mWW <= 1430)WevtPow2Gen= EvtWeight *259.887;
      //if(mWW > 1430 && mWW <= 1440)WevtPow2Gen= EvtWeight *147.746;
      //if(mWW > 1440 && mWW <= 1450)WevtPow2Gen= EvtWeight *0;
      //if(mWW > 1450 && mWW <= 1460)WevtPow2Gen= EvtWeight *0;
      //if(mWW > 1460 && mWW <= 1470)WevtPow2Gen= EvtWeight *0;
      //if(mWW > 1470 && mWW <= 1480)WevtPow2Gen= EvtWeight *134.284;
      //if(mWW > 1480 && mWW <= 1490)WevtPow2Gen= EvtWeight *0;
      //if(mWW >= 1490)              WevtPow2Gen= EvtWeight *0;
      //
      if(mWW > 0 && mWW <= 10) WevtPow2Gen = EvtWeight *0;
      if(mWW > 10 && mWW <= 20) WevtPow2Gen = EvtWeight *0;
      if(mWW > 20 && mWW <= 30) WevtPow2Gen = EvtWeight *0;
      if(mWW > 30 && mWW <= 40) WevtPow2Gen = EvtWeight *0;
      if(mWW > 40 && mWW <= 50) WevtPow2Gen = EvtWeight *0;
      if(mWW > 50 && mWW <= 60) WevtPow2Gen = EvtWeight *0;
      if(mWW > 60 && mWW <= 70) WevtPow2Gen = EvtWeight *0;
      if(mWW > 70 && mWW <= 80) WevtPow2Gen = EvtWeight *0;
      if(mWW > 80 && mWW <= 90) WevtPow2Gen = EvtWeight *0;
      if(mWW > 90 && mWW <= 100) WevtPow2Gen = EvtWeight *0;
      if(mWW > 100 && mWW <= 110) WevtPow2Gen = EvtWeight *0;
      if(mWW > 110 && mWW <= 120) WevtPow2Gen = EvtWeight *0;
      if(mWW > 120 && mWW <= 130) WevtPow2Gen = EvtWeight *29.7118;
      if(mWW > 130 && mWW <= 140) WevtPow2Gen = EvtWeight *0.00279086;
      if(mWW > 140 && mWW <= 150) WevtPow2Gen = EvtWeight *0.00134997;
      if(mWW > 150 && mWW <= 160) WevtPow2Gen = EvtWeight *0.00226138;
      if(mWW > 160 && mWW <= 170) WevtPow2Gen = EvtWeight *0.0198519;
      if(mWW > 170 && mWW <= 180) WevtPow2Gen = EvtWeight *0.0241099;
      if(mWW > 180 && mWW <= 190) WevtPow2Gen = EvtWeight *0.0306862;
      if(mWW > 190 && mWW <= 200) WevtPow2Gen = EvtWeight *0.0382137;
      if(mWW > 200 && mWW <= 210) WevtPow2Gen = EvtWeight *0.0776168;
      if(mWW > 210 && mWW <= 220) WevtPow2Gen = EvtWeight *2.82594;
      if(mWW > 220 && mWW <= 230) WevtPow2Gen = EvtWeight *3.1255;
      if(mWW > 230 && mWW <= 240) WevtPow2Gen = EvtWeight *1.08824;
      if(mWW > 240 && mWW <= 250) WevtPow2Gen = EvtWeight *0.100536;
      if(mWW > 250 && mWW <= 260) WevtPow2Gen = EvtWeight *0.0986332;
      if(mWW > 260 && mWW <= 270) WevtPow2Gen = EvtWeight *0.890345;
      if(mWW > 270 && mWW <= 280) WevtPow2Gen = EvtWeight *1.11697;
      if(mWW > 280 && mWW <= 290) WevtPow2Gen = EvtWeight *0.612297;
      if(mWW > 290 && mWW <= 300) WevtPow2Gen = EvtWeight *0.122205;
      if(mWW > 300 && mWW <= 310) WevtPow2Gen = EvtWeight *0.118729;
      if(mWW > 310 && mWW <= 320) WevtPow2Gen = EvtWeight *0.627305;
      if(mWW > 320 && mWW <= 330) WevtPow2Gen = EvtWeight *0.698478;
      if(mWW > 330 && mWW <= 340) WevtPow2Gen = EvtWeight *0.455363;
      if(mWW > 340 && mWW <= 350) WevtPow2Gen = EvtWeight *0.172007;
      if(mWW > 350 && mWW <= 360) WevtPow2Gen = EvtWeight *0.216106;
      if(mWW > 360 && mWW <= 370) WevtPow2Gen = EvtWeight *0.550866;
      if(mWW > 370 && mWW <= 380) WevtPow2Gen = EvtWeight *0.68561;
      if(mWW > 380 && mWW <= 390) WevtPow2Gen = EvtWeight *0.517929;
      if(mWW > 390 && mWW <= 400) WevtPow2Gen = EvtWeight *0.34963;
      if(mWW > 400 && mWW <= 410) WevtPow2Gen = EvtWeight *0.38036;
      if(mWW > 410 && mWW <= 420) WevtPow2Gen = EvtWeight *0.533375;
      if(mWW > 420 && mWW <= 430) WevtPow2Gen = EvtWeight *0.583199;
      if(mWW > 430 && mWW <= 440) WevtPow2Gen = EvtWeight *0.577958;
      if(mWW > 440 && mWW <= 450) WevtPow2Gen = EvtWeight *0.481313;
      if(mWW > 450 && mWW <= 460) WevtPow2Gen = EvtWeight *0.503448;
      if(mWW > 460 && mWW <= 470) WevtPow2Gen = EvtWeight *0.580928;
      if(mWW > 470 && mWW <= 480) WevtPow2Gen = EvtWeight *0.603506;
      if(mWW > 480 && mWW <= 490) WevtPow2Gen = EvtWeight *0.56764;
      if(mWW > 490 && mWW <= 500) WevtPow2Gen = EvtWeight *0.635131;
      if(mWW > 500 && mWW <= 510) WevtPow2Gen = EvtWeight *0.595673;
      if(mWW > 510 && mWW <= 520) WevtPow2Gen = EvtWeight *0.688364;
      if(mWW > 520 && mWW <= 530) WevtPow2Gen = EvtWeight *0.691017;
      if(mWW > 530 && mWW <= 540) WevtPow2Gen = EvtWeight *0.774553;
      if(mWW > 540 && mWW <= 550) WevtPow2Gen = EvtWeight *0.766557;
      if(mWW > 550 && mWW <= 560) WevtPow2Gen = EvtWeight *0.709171;
      if(mWW > 560 && mWW <= 570) WevtPow2Gen = EvtWeight *0.789538;
      if(mWW > 570 && mWW <= 580) WevtPow2Gen = EvtWeight *0.828584;
      if(mWW > 580 && mWW <= 590) WevtPow2Gen = EvtWeight *0.868391;
      if(mWW > 590 && mWW <= 600) WevtPow2Gen = EvtWeight *0.950148;
      if(mWW > 600 && mWW <= 610) WevtPow2Gen = EvtWeight *0.981945;
      if(mWW > 610 && mWW <= 620) WevtPow2Gen = EvtWeight *0.897412;
      if(mWW > 620 && mWW <= 630) WevtPow2Gen = EvtWeight *0.930661;
      if(mWW > 630 && mWW <= 640) WevtPow2Gen = EvtWeight *1.02751;
      if(mWW > 640 && mWW <= 650) WevtPow2Gen = EvtWeight *1.19138;
      if(mWW > 650 && mWW <= 660) WevtPow2Gen = EvtWeight *1.28862;
      if(mWW > 660 && mWW <= 670) WevtPow2Gen = EvtWeight *1.30348;
      if(mWW > 670 && mWW <= 680) WevtPow2Gen = EvtWeight *1.23069;
      if(mWW > 680 && mWW <= 690) WevtPow2Gen = EvtWeight *1.14769;
      if(mWW > 690 && mWW <= 700) WevtPow2Gen = EvtWeight *1.34062;
      if(mWW > 700 && mWW <= 710) WevtPow2Gen = EvtWeight *1.38738;
      if(mWW > 710 && mWW <= 720) WevtPow2Gen = EvtWeight *1.19113;
      if(mWW > 720 && mWW <= 730) WevtPow2Gen = EvtWeight *1.37518;
      if(mWW > 730 && mWW <= 740) WevtPow2Gen = EvtWeight *1.75121;
      if(mWW > 740 && mWW <= 750) WevtPow2Gen = EvtWeight *1.15044;
      if(mWW > 750 && mWW <= 760) WevtPow2Gen = EvtWeight *1.21337;
      if(mWW > 760 && mWW <= 770) WevtPow2Gen = EvtWeight *1.56737;
      if(mWW > 770 && mWW <= 780) WevtPow2Gen = EvtWeight *1.50851;
      if(mWW > 780 && mWW <= 790) WevtPow2Gen = EvtWeight *1.14128;
      if(mWW > 790 && mWW <= 800) WevtPow2Gen = EvtWeight *1.99833;
      if(mWW > 800 && mWW <= 810) WevtPow2Gen = EvtWeight *1.11318;
      if(mWW > 810 && mWW <= 820) WevtPow2Gen = EvtWeight *1.19217;
      if(mWW > 820 && mWW <= 830) WevtPow2Gen = EvtWeight *1.51537;
      if(mWW > 830 && mWW <= 840) WevtPow2Gen = EvtWeight *0.762487;
      if(mWW > 840 && mWW <= 850) WevtPow2Gen = EvtWeight *1.35799;
      if(mWW > 850 && mWW <= 860) WevtPow2Gen = EvtWeight *1.48034;
      if(mWW > 860 && mWW <= 870) WevtPow2Gen = EvtWeight *1.19687;
      if(mWW > 870 && mWW <= 880) WevtPow2Gen = EvtWeight *1.48977;
      if(mWW > 880 && mWW <= 890) WevtPow2Gen = EvtWeight *1.45757;
      if(mWW > 890 && mWW <= 900) WevtPow2Gen = EvtWeight *1.6408;
      if(mWW > 900 && mWW <= 910) WevtPow2Gen = EvtWeight *1.96676;
      if(mWW > 910 && mWW <= 920) WevtPow2Gen = EvtWeight *1.759;
      if(mWW > 920 && mWW <= 930) WevtPow2Gen = EvtWeight *1.86401;
      if(mWW > 930 && mWW <= 940) WevtPow2Gen = EvtWeight *3.15964;
      if(mWW > 940 && mWW <= 950) WevtPow2Gen = EvtWeight *1.64016;
      if(mWW > 950 && mWW <= 960) WevtPow2Gen = EvtWeight *1.53691;
      if(mWW > 960 && mWW <= 970) WevtPow2Gen = EvtWeight *1.49601;
      if(mWW > 970 && mWW <= 980) WevtPow2Gen = EvtWeight *1.383;
      if(mWW > 980 && mWW <= 990) WevtPow2Gen = EvtWeight *2.01563;
      if(mWW > 990 && mWW <= 1000) WevtPow2Gen = EvtWeight *1.77149;
      if(mWW > 1000 && mWW <= 1010) WevtPow2Gen = EvtWeight *0.618595;
      if(mWW > 1010 && mWW <= 1020) WevtPow2Gen = EvtWeight *2.43869;
      if(mWW > 1020 && mWW <= 1030) WevtPow2Gen = EvtWeight *1.86481;
      if(mWW > 1030 && mWW <= 1040) WevtPow2Gen = EvtWeight *1.42522;
      if(mWW > 1040 && mWW <= 1050) WevtPow2Gen = EvtWeight *2.37188;
      if(mWW > 1050 && mWW <= 1060) WevtPow2Gen = EvtWeight *2.49977;
      if(mWW > 1060 && mWW <= 1070) WevtPow2Gen = EvtWeight *1.61175;
      if(mWW > 1070 && mWW <= 1080) WevtPow2Gen = EvtWeight *3.10188;
      if(mWW > 1080 && mWW <= 1090) WevtPow2Gen = EvtWeight *4.04621;
      if(mWW > 1090 && mWW <= 1100) WevtPow2Gen = EvtWeight *1.50288;
      if(mWW > 1100 && mWW <= 1110) WevtPow2Gen = EvtWeight *2.58528;
      if(mWW > 1110 && mWW <= 1120) WevtPow2Gen = EvtWeight *2.17278;
      if(mWW > 1120 && mWW <= 1130) WevtPow2Gen = EvtWeight *3.08231;
      if(mWW > 1130 && mWW <= 1140) WevtPow2Gen = EvtWeight *1.41535;
      if(mWW > 1140 && mWW <= 1150) WevtPow2Gen = EvtWeight *2.02723;
      if(mWW > 1150 && mWW <= 1160) WevtPow2Gen = EvtWeight *1.73087;
      if(mWW > 1160 && mWW <= 1170) WevtPow2Gen = EvtWeight *2.10286;
      if(mWW > 1170 && mWW <= 1180) WevtPow2Gen = EvtWeight *1.04876;
      if(mWW > 1180 && mWW <= 1190) WevtPow2Gen = EvtWeight *2.26694;
      if(mWW > 1190 && mWW <= 1200) WevtPow2Gen = EvtWeight *0.77937;
      if(mWW > 1200 && mWW <= 1210) WevtPow2Gen = EvtWeight *1.57147;
      if(mWW > 1210 && mWW <= 1220) WevtPow2Gen = EvtWeight *0.467873;
      if(mWW > 1220 && mWW <= 1230) WevtPow2Gen = EvtWeight *1.72792;
      if(mWW > 1230 && mWW <= 1240) WevtPow2Gen = EvtWeight *1.09347;
      if(mWW > 1240 && mWW <= 1250) WevtPow2Gen = EvtWeight *3.01786;
      if(mWW > 1250 && mWW <= 1260) WevtPow2Gen = EvtWeight *1.56647;
      if(mWW > 1260 && mWW <= 1270) WevtPow2Gen = EvtWeight *1.57424;
      if(mWW > 1270 && mWW <= 1280) WevtPow2Gen = EvtWeight *3.6806;
      if(mWW > 1280 && mWW <= 1290) WevtPow2Gen = EvtWeight *1.69596;
      if(mWW > 1290 && mWW <= 1300) WevtPow2Gen = EvtWeight *2.22172;
      if(mWW > 1300 && mWW <= 1310) WevtPow2Gen = EvtWeight *4.64277;
      if(mWW > 1310 && mWW <= 1320) WevtPow2Gen = EvtWeight *2.1824;
      if(mWW > 1320 && mWW <= 1330) WevtPow2Gen = EvtWeight *5.81765;
      if(mWW > 1330 && mWW <= 1340) WevtPow2Gen = EvtWeight *2.53258;
      if(mWW > 1340 && mWW <= 1350) WevtPow2Gen = EvtWeight *0;
      if(mWW > 1350 && mWW <= 1360) WevtPow2Gen = EvtWeight *0;
      if(mWW > 1360 && mWW <= 1370) WevtPow2Gen = EvtWeight *2.95061;
      if(mWW > 1370 && mWW <= 1380) WevtPow2Gen = EvtWeight *2.4571;
      if(mWW > 1380 && mWW <= 1390) WevtPow2Gen = EvtWeight *1.15239;
      if(mWW > 1390 && mWW <= 1400) WevtPow2Gen = EvtWeight *6.44579;
      if(mWW > 1400 && mWW <= 1410) WevtPow2Gen = EvtWeight *4.29784;
      if(mWW > 1410 && mWW <= 1420) WevtPow2Gen = EvtWeight *0.0282039;
      if(mWW > 1420 && mWW <= 1430) WevtPow2Gen = EvtWeight *6.74571;
      if(mWW > 1430 && mWW <= 1440) WevtPow2Gen = EvtWeight *3.57463;
      if(mWW > 1440 && mWW <= 1450) WevtPow2Gen = EvtWeight *1.40198;
      if(mWW > 1450 && mWW <= 1460) WevtPow2Gen = EvtWeight *0;
      if(mWW > 1460 && mWW <= 1470) WevtPow2Gen = EvtWeight *0;
      if(mWW > 1470 && mWW <= 1480) WevtPow2Gen = EvtWeight *4.07527;
      if(mWW > 1480 && mWW <= 1490) WevtPow2Gen = EvtWeight *0;
      if(mWW > 1490               ) WevtPow2Gen = EvtWeight *0;


}

int Write_Histo()
{
  return 0;
}


#endif // #ifdef HWwNjetStudy_cxx
