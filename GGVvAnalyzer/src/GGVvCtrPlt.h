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
   int sfFillHist();
   int Nselected4Bin();

   double nPass;
   double nOffShell_NoCut; //Off-Shell events No Cut
   double nOffShMll_NoCut[nMllBin]; //Off-Shell events different mll Cut
   double nOffShPTll_NoCut[nMllBin]; //Off-Shell events different ptll Cut
   double nOffShell_ComCut; //Off-Shell events Common Cut
   double nOffShMll_ComCut[nMllBin]; //Off-Shell events different mll Cut and Common Cut
   double nOffShPTll_ComCut[nMllBin]; //Off-Shell events different ptll Cut and Common Cut

   double nOnShell_NoCut; //On-Shell events No Cut
   double nOnShMll_NoCut[nMllBin]; //On-Shell events different mll Cut
   double nOnShPTll_NoCut[nMllBin]; //On-Shell events different ptll Cut
   double nOnShell_ComCut; //On-Shell events Common Cut
   double nOnShMll_ComCut[nMllBin]; //On-Shell events different mll Cut and Common Cut
   double nOnShPTll_ComCut[nMllBin]; //On-Shell events different ptll Cut and Common Cut

   double nOnSh_MllCut[nMllBin];
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
   //mll>100 histograms
   TH1D *hNoCut_Hig_mass_mllCut;
   TH1D *hNoCut_HigT_mass_mllCut;
   TH1D *hNoCut_mll_mllCut;
   TH1D *hNoCut_ptll_mllCut;
   TH1D *hNoCut_pt1_mllCut;
   TH1D *hNoCut_pt2_mllCut;
   TH1D *hNoCut_MET_mllCut;
   TH1D *hNoCut_mpMET_mllCut;
   TH1D *hNoCut_ppfMET_mllCut;
   TH1D *hNoCut_dphill_mllCut;
   TH1D *hNoCut_dphillmet_mllCut;
   
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
   TH2D *h2_mH_mtH;

   //Common Cut at mll>100
   TH1D *h_Hig_mass_mllCut;
   TH1D *h_HigT_mass_mllCut;
   TH1D *h_mll_mllCut;
   TH1D *h_ptll_mllCut;
   TH1D *h_pt1_mllCut;
   TH1D *h_pt2_mllCut;
   TH1D *h_MET_mllCut;
   TH1D *h_mpMET_mllCut;
   TH1D *h_ppfMET_mllCut;
   TH1D *h_dphill_mllCut;
   TH1D *h_dphillmet_mllCut;
   TH2D *h2_mH_mtH_mllCut;
  
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

   TH1D *h_OffSh_NoCut;
   TH1D *h_mllOffSh_NoCut;
   TH1D *h_ptllOffSh_NoCut;
   TH1D *h_OffSh_ComCut;
   TH1D *h_mllOffSh_ComCut;
   TH1D *h_ptllOffSh_ComCut;
   TH1D *h_OnSh_NoCut;
   TH1D *h_mllOnSh_NoCut;
   TH1D *h_ptllOnSh_NoCut;
   TH1D *h_OnSh_ComCut;
   TH1D *h_mllOnSh_ComCut;
   TH1D *h_ptllOnSh_ComCut;

   //SameFlavor
   TH1D *h1_mH_mumu;
   TH1D *h1_mH_elel;
   TH1D *h1_mH_tautau;
   TH2D *h2_mH_mll_mumu;
   TH2D *h2_mH_mll_elel;
   TH2D *h2_mH_mll_tautau;

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
