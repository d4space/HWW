//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 12 01:53:46 2014 by ROOT version 5.32/00
// from TChain latino/
//////////////////////////////////////////////////////////

#ifndef HWwBase_h
#define HWwBase_h

#include <TSystem.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>

#include <iostream>
#include <fstream>
#include <iomanip>

#include "HWwNT.h"
#include "../../../Utils/const.h"
#include <TLorentzVector.h>
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class HWwBase: public HWwNT {
public :

   HWwBase(TTree *tree=0,double lumiweight =1, TString SampleName = "Data",TString Cut ="Test", bool RunOnMC=true);
   virtual ~HWwBase();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
protected:
   int evtCnt;
   double MT;
   double LumiW;
   double EvtWeight;
   bool RunOnMC;

   double Nselect[6];
   double NselectSF0j[6];
   double NselectSF1j[6];
   double NselectOF0j[6];
   double NselectOF1j[6];
   double ncut1;
   double ncut2;
   double ncut3;
   double ncut4;
   double ncut5;
   double ncut6;
   double ncut7;
   double ncut8;
   double ncut9;
   double ncut10;
   double ncutLoose;

   int evtChannel;
   enum AnaChan{
     Chan_sf0j,
     Chan_of0j,
     Chan_sf1j,
     Chan_of1j
   };

   TString       mResultDir;
   TString       SampleName;
   TString       Cut;

   virtual Int_t    SF0jCut();
   virtual Int_t    OF0jCut();
   virtual Int_t    SF1jCut();
   virtual Int_t    OF1jCut();
   virtual Int_t    CommonCut();
   virtual Int_t    CommonCut_Without_mll_ptll_Cut();
   virtual Int_t    CommonCut_Without_mllCut();
   virtual Int_t    CommonCut_Without_ptllCut();
   virtual Int_t    CommonCut_Without_mpmetCut();
   virtual Int_t    LooseCut();
   virtual Int_t    SignalCutV1();
   virtual Int_t    SignalCutV2();

   double 	CalcWeight();
   double 	CalcmWW();
   double mH;
   double mllBins[61];
   double ptllBins[31];
   double Nmllptll_OF0j[61][31];
   double Nmllptll_OF1j[61][31];
};
#endif

#ifdef HWwBase_cxx

void HWwBase::Init(TTree *tree)
{
   if (!tree){
     cout<<"No Tree ?????????????????: Exiting==========="<<endl;
     exit(-1);
   }

   HWwNT::Init(tree);
   EvtWeight = 1;
   mH = 0;

   cout<<"RunOnMC:  "<<RunOnMC<<endl;
   if(!RunOnMC)
   {
     fChain->SetBranchStatus("pdfid1",0);
     fChain->SetBranchStatus("pdfid2",0);
     fChain->SetBranchStatus("pdfscalePDF",0);
     fChain->SetBranchStatus("pdfx1",0);
     fChain->SetBranchStatus("pdfx1PDF",0);
     fChain->SetBranchStatus("pdfx2",0);
     fChain->SetBranchStatus("pdfx2PDF",0);
     fChain->SetBranchStatus("effCW",0);
     fChain->SetBranchStatus("effDW",0);
     fChain->SetBranchStatus("puWD",0);
     fChain->SetBranchStatus("puWA",0);
     fChain->SetBranchStatus("puWB",0);
     fChain->SetBranchStatus("puWC",0);
     fChain->SetBranchStatus("puWABC",0);
     fChain->SetBranchStatus("effABCW",0);
     fChain->SetBranchStatus("effWMuUp",0);
     fChain->SetBranchStatus("effWElUp",0);
     fChain->SetBranchStatus("effWMuDown",0);
     fChain->SetBranchStatus("effWElDown",0);
     fChain->SetBranchStatus("effWUp",0);
     fChain->SetBranchStatus("effWDown",0);
     fChain->SetBranchStatus("pdfid1",0);
   }
   gSystem->mkdir(mResultDir);
   Notify();
}

HWwBase::HWwBase(TTree *HWwBaseTree,double lumiweight, TString SampleName_,TString Cut_, bool runOnMC)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  cout<<"HWwBase constructor"<<endl;
  if (HWwBaseTree == 0) {
    cout<<"Usage: HWwBase(TTree*... ) "<<endl;
    exit(-1);
  }
  cout<<"HWwBase.h: initializing =================="<<endl;
  LumiW = lumiweight;
  SampleName = SampleName_;
  mResultDir = SampleName_;
  Cut = Cut_;
  RunOnMC = runOnMC;
  Init(HWwBaseTree);
}

HWwBase::~HWwBase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HWwBase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HWwBase::LoadTree(Long64_t entry)
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


Bool_t HWwBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HWwBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
#endif // #ifdef HWwBase_cxx
