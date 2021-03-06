//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 25 16:28:28 2014 by ROOT version 5.32/00
// from TChain LHEF/
//////////////////////////////////////////////////////////

#ifndef GGVvTemplate_h
#define GGVvTemplate_h

#include "GGVvBase.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class GGVvTemplate: public GGVvBase {
public :

   GGVvTemplate(TTree *tree=0,TString DirName = "OutPut", TString Mode="Test");
   virtual ~GGVvTemplate();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
protected:
   int InitHistogram();
   int InitVar();
   TFile *OutTFile;
   int Ntries;
};

#endif

#ifdef GGVvTemplate_cxx
GGVvTemplate::GGVvTemplate(TTree *tree, TString DirName, TString Mode) :
  GGVvBase::GGVvBase(tree, DirName, Mode)
{
  InitVar();
  InitHistogram();
}

GGVvTemplate::~GGVvTemplate()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GGVvTemplate::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GGVvTemplate::LoadTree(Long64_t entry)
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

Bool_t GGVvTemplate::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GGVvTemplate::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GGVvTemplate::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GGVvTemplate_cxx
