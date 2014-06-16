//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 25 16:28:28 2014 by ROOT version 5.32/00
// from TChain LHEF/
//////////////////////////////////////////////////////////

#ifndef GGVvBase_h
#define GGVvBase_h

#include <iostream>
#include <fstream>
#include "../ExRootAnalysis/ExRootAnalysis/ExRootAnalysis.h"
#include "../../Utils/const.h"
#include <TSystem.h>
#include <TBenchmark.h>                   // class to track macro running statistics
#include <TLorentzVector.h>
#include "GGVvNT.h"
// Fixed size dimensions of array or collections stored in the TTree if any.

class GGVvBase: public GGVvNT {
public :

   GGVvBase(TTree *tree=0, TString DirName="OutDir", TString Mode="Test");
   virtual ~GGVvBase();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
protected:
   virtual int Init4Event();
   int DumpParticles();
   int EmuFidCut();

   TString mDirName;
   TString mMode;

   TLorentzVector mu_TL;
   bool isMu;
   TLorentzVector muNu_TL;
   bool isMuNu;
   TLorentzVector el_TL;
   bool isEl;
   TLorentzVector elNu_TL;
   bool isElNu;

   TLorentzVector higgs_TL;
   TLorentzVector higgsT_TL;
   TLorentzVector elmu_TL;
   TLorentzVector higgsl_TL;
   TLorentzVector higgsEM_TL;

   double Hig_mass;
   double Ele_mass;
   double Mu_mass;
   double EleMu_mass;
   double HigT_mass;
   double Higl_mass;
   double Hig_cut_mass;
   double Hig_Et;
   double HigEM_mass;

   bool PassFid;
};

#endif

#ifdef GGVvBase_cxx
GGVvBase::GGVvBase(TTree *tree, TString DirName, TString Mode)
{
  fChain = 0;
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     cout<<"GGVvBase: tree is empty"<<endl;
     exit(-1);
   }
   mDirName = DirName;
   mMode = Mode;

   Init(tree);
}

GGVvBase::~GGVvBase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GGVvBase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GGVvBase::LoadTree(Long64_t entry)
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

void GGVvBase::Init(TTree *tree)
{
   gSystem->mkdir(mDirName);
   GGVvNT::Init(tree);
}

Bool_t GGVvBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GGVvBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GGVvBase::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
int GGVvBase::Init4Event()
{
  isMu = false;
  isMuNu = false;
  isEl = false;
  isElNu = false;
  return 0;
}
int GGVvBase::DumpParticles()
{
  for(int i(0); i<kMaxParticle;i++)
  {
    //cout<<"Particle (idx,Id, Status): "<<i<<"  "<<Particle_PID[i]<<" "<<Particle_Status[i]<<endl;
    if(fabs(Particle_PID[i]) == int(GenType::kElectron))
    {
      el_TL.SetXYZM(Particle_Px[i], Particle_Py[i], Particle_Pz[i], GenType::M_ele);
      isEl = true;
    }
    else if(fabs(Particle_PID[i]) == GenType::keNeutrino)
    {
      elNu_TL.SetXYZM(Particle_Px[i], Particle_Py[i], Particle_Pz[i], 0.0);
      isElNu = true;
    }
    else if(fabs(Particle_PID[i]) == GenType::kMuon)
    {
      mu_TL.SetXYZM(Particle_Px[i], Particle_Py[i], Particle_Pz[i], GenType::M_mu);
      isMu = true;
    }
    else if(fabs(Particle_PID[i]) == GenType::kmuNeutrino)
    {
      muNu_TL.SetXYZM(Particle_Px[i], Particle_Py[i], Particle_Pz[i], 0.0);
      isMuNu = true;
    }
  }
  return 0;
}
#endif // #ifdef GGVvBase_cxx
