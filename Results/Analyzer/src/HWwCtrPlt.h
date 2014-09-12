//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 12 01:53:46 2014 by ROOT version 5.32/00
// from TChain latino/
//////////////////////////////////////////////////////////

#ifndef HWwCtrPlt_h
#define HWwCtrPlt_h

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

class HWwCtrPlt: public HWwBase {
public :

   HWwCtrPlt(TTree *tree=0,double lumiweight =1, TString SampleName = "Data",TString Cut ="Tight", bool RunOnMC= true);
   virtual ~HWwCtrPlt();
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
   
   TH1D *h1_channel[4];
   TH1D *h1_chmet[4];//charged smurf met
   TH1D *h1_chmetphi[4]; //charged smurf met phi
   TH1D *h1_chmetx[4]; //charged smurf met x
   TH1D *h1_chmety[4]; //charged smurf met x
   TH1D *h1_dphill[4];
   TH1D *h1_dphilljet[4];
   TH1D *h1_dphillmet[4];
   TH1D *h1_dphilmet1[4];
   TH1D *h1_dphilmet2[4];
   TH1D *h1_dphilmet[4];
   TH1D *h1_drll[4];
   TH1D *h1_dymva1[4];
   TH1D *h1_eta1[4];
   TH1D *h1_eta2[4];
   TH1D *h1_hardtche[4];
   TH1D *h1_jeteta1[4];
   TH1D *h1_jetmva1[4];
   TH1D *h1_jetpt1[4];
   TH1D *h1_mll[4];
   TH1D *h1_mpmet[4];
   TH1D *h1_mpmet_FOM[4];
   TH1D *h1_ppfmet[4];
   TH1D *h1_mth[4];
   TH1D *h1_mtw1[4];
   TH1D *h1_mtw2[4];
   TH1D *h1_njet[4];
   TH1D *h1_nvtx[4];
   TH1D *h1_pchmet[4];
   TH1D *h1_pfmet[4];
   TH1D *h1_pfmetphi[4];
   TH1D *h1_pfmetx[4];
   TH1D *h1_pfmety[4];
   TH1D *h1_phi1[4];
   TH1D *h1_phi2[4];
   TH1D *h1_pt1[4];
   TH1D *h1_pt2[4];
   TH1D *h1_ptll[4];
   TH1D *h1_softtche[4];
   TH1D *h1_mH[4];
   TH1D *h1_mH_OffShell[4];
   TH1D *h1_mH_OnShell[4];

   TH1D *h1_charge1[4];
   TH1D *h1_charge2[4];
   TH1D *h1_trigger[4];
   TH1D *h1_nextra[4];
   TH1D *h1_zveto[4];
   TH1D *h1_flavor[4];
   TH1D *h1_dphilljetjet[4];
   TH1D *h1_bveto_mu[4];
   TH1D *h1_bveto_ip[4];
   TH1D *h1_nbjettche[4];

   TH2D *h2_mllptll[4];
   TH2D *h2_mthmll[4];
   TH2D *h2_mthdphill[4];
   TH2D *h2_mlldphill[4];
};

#endif

#ifdef HWwCtrPlt_cxx

HWwCtrPlt::HWwCtrPlt(TTree *tree,double lumiweight, TString SampleName_,TString Cut_, bool RunOnMC) :
  HWwBase::HWwBase( tree, lumiweight, SampleName_, Cut_, RunOnMC)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  cout<<"HWwCtrPlt constructor"<<endl;
  if (tree == 0) {
    cout<<"Usage: HWwCtrPlt(TTree*... ) "<<endl;
    exit(-1);
  }
  cout<<"HWwCtrPlt.h: initializing =================="<<endl;
  InitVar();
  InitHistogram();
}

HWwCtrPlt::~HWwCtrPlt()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HWwCtrPlt::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HWwCtrPlt::LoadTree(Long64_t entry)
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


Bool_t HWwCtrPlt::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HWwCtrPlt::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
#endif // #ifdef HWwCtrPlt_cxx
