//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 25 16:28:28 2014 by ROOT version 5.32/00
// from TChain LHEF/
//////////////////////////////////////////////////////////

#ifndef GGVvMkNtuple_h
#define GGVvMkNtuple_h

#include <TH1D.h>
#include <TH2D.h>
#include "GGVvBase.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class GGVvMkNtuple: public GGVvBase {
public :

   GGVvMkNtuple(TTree *tree=0,TString DirName = "OutPut", TString Mode="Test",double weight=1);
   virtual ~GGVvMkNtuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
protected:
   int InitHistogram();
   int InitVar();
   int Ntries;
   int FillHist();

   double nPass;

   TFile *OutTFile;
   TTree *ggTree;
   
   //Common Cut
   TH1D *h_Hig_Mass;
   TH2D *h_Hig_MassMll;
   TH2D *h_Hig_MassPtll;

   ofstream Fout;
};

#endif

#ifdef GGVvMkNtuple_cxx
GGVvMkNtuple::GGVvMkNtuple(TTree *tree, TString DirName, TString Mode,double lumiweight) :
  GGVvBase::GGVvBase(tree, DirName, Mode, lumiweight)
{
  InitVar();
  InitHistogram();
}

GGVvMkNtuple::~GGVvMkNtuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GGVvMkNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GGVvMkNtuple::LoadTree(Long64_t entry)
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

Bool_t GGVvMkNtuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GGVvMkNtuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GGVvMkNtuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GGVvMkNtuple_cxx
