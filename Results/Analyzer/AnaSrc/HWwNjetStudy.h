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
   int Fill_vbfHisto();
   int Write_Histo();
   double mWW;
   double WevtPow2Gen;

   ofstream Fout;
   TFile *myFile;
   
   TH1D *h1_njet_Off_Wevt[12]; //11 for mWW>130 GeV
   TH1D *h1_njet_Off_WevtPow2Gen[12];
   TH1D *h1_njet_Off_noWeight[12];
   
   TH1D *h1_mWW_Off_Wevt[4]; // 3 for all
   TH1D *h1_mWW_Off_WevtPow2Gen[4]; // 3 for all
   TH1D *h1_mWW_Off_noWeight[4];
   
   TH1D *h1_mWWbin_Off_Wevt[4];
   TH1D *h1_mWWbin_Off_WevtPow2Gen[4];
   TH1D *h1_mWWbin_Off_noWeight[4];
   
   TH1D *h1_mww_off_CalcPowRew[5];
   TH1D *h1_mww_off_CalcPowRew_noWeight[5];
   
   TH1D *h1_mjj[5];
   TH1D *h1_detajj[5];
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
#endif // #ifdef HWwNjetStudy_cxx
