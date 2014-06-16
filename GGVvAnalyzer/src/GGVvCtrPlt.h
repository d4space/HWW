//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 25 16:28:28 2014 by ROOT version 5.32/00
// from TChain LHEF/
//////////////////////////////////////////////////////////

#ifndef GGVvCtrPlt_h
#define GGVvCtrPlt_h

#include <TH1D.h>
#include <TH2D.h>
#include "GGVvBase.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class GGVvCtrPlt: public GGVvBase {
public :

   GGVvCtrPlt(TTree *tree=0,TString DirName = "OutPut", TString Mode="Test");
   virtual ~GGVvCtrPlt();
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

   int Hig_N_LowReso;
   int Hig_N_Reso;
   int Hig_N_HighReso;
   int Hig_N_Sig; //Signal region
   int Hig_N_Total;
   int Hig_N_OnPeak;
   int Hig_N_OffPeak;

   int Hig_N_LowReso8;
   int Hig_N_Reso8;
   int Hig_N_HighReso8;
   int Hig_N_Sig8; //Signal region
   int Hig_N_Total8;
   int Hig_N_OnPeak8;
   int Hig_N_OffPeak8;

   int Hig_N_LowReso20;
   int Hig_N_Reso20;
   int Hig_N_HighReso20;
   int Hig_N_Sig20; //Signal region
   int Hig_N_Total20;
   int Hig_N_OnPeak20;
   int Hig_N_OffPeak20;

   TFile *OutTFile;
   TH1D *hHig_Mass;
   TH1D *hEle_Mass;
   TH1D *hMu_Mass;
   TH1D *hEleMu_Mass;
   TH1D *hHigT_Mass;
   TH1D *h_leadingPt;
//   TH1D *h_trailingPt;
   TH1D *h_leadingM;
   TH1D *hHig_Et;
   TH1D *hHigEM_Mass;
   ofstream Fout;
};

#endif

#ifdef GGVvCtrPlt_cxx
GGVvCtrPlt::GGVvCtrPlt(TTree *tree, TString DirName, TString Mode) :
  GGVvBase::GGVvBase(tree, DirName, Mode)
{
  InitVar();
  InitHistogram();
}

GGVvCtrPlt::~GGVvCtrPlt()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GGVvCtrPlt::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GGVvCtrPlt::LoadTree(Long64_t entry)
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

Bool_t GGVvCtrPlt::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GGVvCtrPlt::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GGVvCtrPlt::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GGVvCtrPlt_cxx
