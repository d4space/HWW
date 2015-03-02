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
   virtual Int_t    CommonCut_njet();
   virtual Int_t    CommonCut_VBFnjet();
   virtual Int_t    CommonCut_VBf_NoVetoCentralJet();
   virtual Int_t    LooseCut();
   virtual Int_t    SignalCutV1();
   virtual Int_t    SignalCutV2();
   virtual Int_t    SignalCutV3();

   double 	CalcWeight();
   double 	CalcmWW();
<<<<<<< HEAD
   double mWW; // For POWHEG
=======
#if SAMPLE == "POWHEG_VBF"
   double mWW; // For POWHEG
#endif
>>>>>>> 1c65f6e1601999258522700ea07f41348bba62e8
   double mH;
   double mllBins[12];
   double mthBins[12];
   double Nmllptll_OF0j[61][31];
   double Nmllptll_OF1j[61][31];
   double mWWBins[12];
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
  mthBins[0]  = 80;
  mthBins[1]  = 110;
  mthBins[2]  = 140;
  mthBins[3]  = 170;
  mthBins[4]  = 200;
  mthBins[5]  = 230;
  mthBins[6]  = 260;
  mthBins[7]  = 290;
  mthBins[8]  = 320;
  mthBins[9]  = 350;
  mthBins[10] = 380;
  mthBins[11] = 600;
  
  mllBins[0]  = 0;
  mllBins[1]  = 45;
  mllBins[2]  = 90;
  mllBins[3]  = 145;
  mllBins[4]  = 180;
  mllBins[5]  = 225;
  mllBins[6]  = 270;
  mllBins[7]  = 315;
  mllBins[8]  = 360;
  mllBins[9]  = 405;
  mllBins[10] = 450;
  mllBins[11] = 600;
  
  mWWBins[0]  = 130;
  mWWBins[1]  = 200;
  mWWBins[2]  = 300;
  mWWBins[3]  = 400;
  mWWBins[4]  = 500;
  mWWBins[5]  = 600;
  mWWBins[6]  = 700;
  mWWBins[7]  = 800;
  mWWBins[8]  = 900;
  mWWBins[9]  = 1000;
  mWWBins[10] = 1250;
  mWWBins[11] = 1500;
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
