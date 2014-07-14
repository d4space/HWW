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

   GGVvCtrPlt(TTree *tree=0,TString DirName = "OutPut", TString Mode="Test",double weight=1);
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
   int FillHist();
   int FillHistNoCut();
   int Nselected4Bin();

   double nPass;
   double nPass_mll;
   double Higgs_EM_N_Total;
   double Npt0_140;
   double Npt8_140;
   double Npt20_140;
   double Npt0_140_300;
   double Npt8_140_300;
   double Npt20_140_300;
   double Npt0_300;
   double Npt8_300;
   double Npt20_300;

   double Hig_N_LowReso;
   double Hig_N_Reso;
   double Hig_N_HighReso;
   double Hig_N_Sig; //Signal region
   double Hig_N_Total;
   double Hig_N_OnPeak;
   double Hig_N_OffPeak;

   double Hig_N_LowReso8;
   double Hig_N_Reso8;
   double Hig_N_HighReso8;
   double Hig_N_Sig8; //Signal region
   double Hig_N_Total8;
   double Hig_N_OnPeak8;
   double Hig_N_OffPeak8;

   double Hig_N_LowReso20;
   double Hig_N_Reso20;
   double Hig_N_HighReso20;
   double Hig_N_Sig20; //Signal region
   double Hig_N_Total20;
   double Hig_N_OnPeak20;
   double Hig_N_OffPeak20;

   double nEvents_OnPeak_AllCh;
   double nEvents_Shoulder_AllCh;
   double nEvents_Tail_AllCh;

   TFile *OutTFile;
   //No Cut
   TH1D *hNoCut_Hig_mass;
   TH1D *hNoCut_HigT_mass;
   TH1D *hNoCut_mll;
   TH1D *hNoCut_ptll;
   TH1D *hNoCut_pt1;
   TH1D *hNoCut_pt2;
   TH1D *hNoCut_MET;
   TH1D *hNoCut_mpMET;
   TH1D *hNoCut_ppfMET;
   TH1D *hNoCut_dphill;
   TH1D *hNoCut_dphillmet;
   
   //Common Cut
   TH1D *h_Hig_mass;
   TH1D *h_HigT_mass;
   TH1D *h_mll;
   TH1D *h_ptll;
   TH1D *h_pt1;
   TH1D *h_pt2;
   TH1D *h_MET;
   TH1D *h_mpMET;
   TH1D *h_ppfMET;
   TH1D *h_dphill;
   TH1D *h_dphillmet;
  
   //N-1 cut study histograms
   TH1D *hN1Cut_pt1;
   TH1D *hN1Cut_pt2;
   TH1D *hN1Cut_MET;
   TH1D *hN1Cut_mll;
   TH1D *hN1Cut_ptll;
   TH1D *hN1Cut_mpMET;
   TH2D *h2_mH_pt1;
   TH2D *h2_mH_pt2;
   TH2D *h2_mH_MET;
   TH2D *h2_mH_mll;
   TH2D *h2_mH_ptll;
   TH2D *h2_mH_mpMET;
   TH2D *h2_mH_mtH;
   ofstream Fout;
};

#endif

#ifdef GGVvCtrPlt_cxx
GGVvCtrPlt::GGVvCtrPlt(TTree *tree, TString DirName, TString Mode,double lumiweight) :
  GGVvBase::GGVvBase(tree, DirName, Mode, lumiweight)
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
