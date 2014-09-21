//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 12 01:53:46 2014 by ROOT version 5.32/00
// from TChain latino/
//////////////////////////////////////////////////////////

#ifndef HWwNEvents_h
#define HWwNEvents_h

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

class HWwNEvents: public HWwBase {
public :

   HWwNEvents(TTree *tree=0,double lumiweight =1, TString SampleName = "Data",TString Cut ="Tight", bool RunOnMC= true);
   virtual ~HWwNEvents();
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
   
   //Efficiency
   double ntruth_OF0j[6]; //0,1,2 - RecoLvl OF events (elmu and muel, muel, elmu), index 3,4,5 - genLvl OF events
   double ntruth_OF1j[6];
   double nfake_OF0j[8]; //0-genLvl total fake events, 1-mumu, 2-mutau, 3-elel, 4-eltau, 5-taumu, 6-tauel, 7-tautau
   double nfake_OF1j[8];
   
   double ntruth_SF0j[2]; //0,1,2 - RecoLvl SF events (elmu and muel, muel, elmu), index 3,4,5 - genLvl SF events
   double ntruth_SF1j[2];
   double nfake_SF0j[8]; //0-genLvl total fake events, 1-mumu, 2-mutau, 3-elel, 4-eltau, 5-taumu, 6-tauel, 7-tautau
   double nfake_SF1j[8];
};

#endif

#ifdef HWwNEvents_cxx

HWwNEvents::HWwNEvents(TTree *tree,double lumiweight, TString SampleName_,TString Cut_, bool RunOnMC) :
  HWwBase::HWwBase( tree, lumiweight, SampleName_, Cut_, RunOnMC)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  cout<<"HWwNEvents constructor"<<endl;
  if (tree == 0) {
    cout<<"Usage: HWwNEvents(TTree*... ) "<<endl;
    exit(-1);
  }
  cout<<"HWwNEvents.h: initializing =================="<<endl;
  InitVar();
  InitHistogram();
}

HWwNEvents::~HWwNEvents()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HWwNEvents::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HWwNEvents::LoadTree(Long64_t entry)
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


Bool_t HWwNEvents::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HWwNEvents::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
#endif // #ifdef HWwNEvents_cxx
