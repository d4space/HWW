//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 12 01:53:46 2014 by ROOT version 5.32/00
// from TChain latino/
//////////////////////////////////////////////////////////

#ifndef HWwMET_h
#define HWwMET_h

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

class HWwMET: public HWwBase {
public :

   HWwMET(TTree *tree=0,double lumiweight =1, TString SampleName = "Data",TString Cut ="Tight", bool RunOnMC= true);
   virtual ~HWwMET();
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
   int Write_Histo();

   ofstream Fout;
   TFile *myFile;
   
   TH1D *h1_pupmet[4];
};

#endif

#ifdef HWwMET_cxx

HWwMET::HWwMET(TTree *tree,double lumiweight, TString SampleName_,TString Cut_, bool RunOnMC) :
  HWwBase::HWwBase( tree, lumiweight, SampleName_, Cut_, RunOnMC)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  cout<<"HWwMET constructor"<<endl;
  if (tree == 0) {
    cout<<"Usage: HWwMET(TTree*... ) "<<endl;
    exit(-1);
  }
  cout<<"HWwMET.h: initializing =================="<<endl;
  InitVar();
  InitHistogram();
}

HWwMET::~HWwMET()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HWwMET::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HWwMET::LoadTree(Long64_t entry)
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


Bool_t HWwMET::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HWwMET::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
#endif // #ifdef HWwMET_cxx
