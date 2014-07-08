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

   GGVvBase(TTree *tree=0, TString DirName="OutDir", TString Mode="Test",double weight=1);
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
   int CommonCut();
   int pt1_Cut();
   int pt2_Cut();
   int MET_Cut();
   int DiLept_mass_Cut();
   int DiLept_pt_Cut();
   int mpMET_Cut();
   Double_t deltaPhi(double phi1, double phi2);

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
   TLorentzVector DiLept_TL;
   TLorentzVector MET_TL;

   double elPt;
   double muPt;
   double elMass;
   double muMass;
   double Hig_mass;
   double HigT_mass;
   double Hig_Et;
   double DiLept_mass;
   double MET;
   double mpMET;
   double ppfMET1;
   double ppfMET2;
   double DiLept_dphi;
   double dphi_MEtLL;
   double DiLept_pt;
   double pt1;
   double pt2;
   
   bool PassFid;
   bool isMuNuEleNu;
   double mTTW;
};

#endif

#ifdef GGVvBase_cxx
GGVvBase::GGVvBase(TTree *tree, TString DirName, TString Mode,double lumiweight)
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
   mTTW = lumiweight;

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
  isMuNuEleNu = false;
  elPt = 0;
  muPt = 0;
  elMass = 0;
  muMass = 0;
  Hig_mass = 0;
  HigT_mass = 0;
  Hig_Et = 0;
  DiLept_mass = 0;
  MET = 0;
  mpMET = 0;
  ppfMET1 = 0;
  ppfMET2 = 0;
  DiLept_dphi = 0;
  dphi_MEtLL = 0;
  DiLept_pt = 0;
  pt1 = 0;
  pt2 = 0;
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
  
  //Variables
  if(isEl && isElNu && isMu && isMuNu)
  {
    isMuNuEleNu = true;
    //Leading and Trailing lepton pt
    elPt = el_TL.Pt();
    muPt = mu_TL.Pt();
    if(elPt > muPt){
      pt1 = elPt; 
      pt2 = muPt;
    }else if(elPt < muPt){
      pt1 = muPt; 
      pt2 = elPt;
    }

    //pfMET
    MET_TL = elNu_TL + muNu_TL; 
    MET = MET_TL.Pt();

    //DiLepton variables
    DiLept_TL = el_TL + mu_TL;
    DiLept_pt = DiLept_TL.Pt();
    DiLept_mass = DiLept_TL.M();
    DiLept_dphi = deltaPhi(el_TL.Phi(), mu_TL.Phi());
    
    //dPhi between MET and DiLepton
    dphi_MEtLL = deltaPhi(MET_TL.Phi(), DiLept_TL.Phi());
    
    //Higgs variables
    double mt2 = 2.*DiLept_pt*MET*(1.-TMath::Cos(dphi_MEtLL));
    HigT_mass = (mt2 > 0) ? TMath::Sqrt(mt2) : 0;
    higgs_TL = el_TL + elNu_TL + mu_TL + muNu_TL;
    Hig_mass = higgs_TL.M();
    Hig_Et = higgs_TL.Et();

    //Projected pfMET
    double dphi_min;
    double dphi_lept1met;
    double dphi_lept2met;
    dphi_lept1met = deltaPhi(MET_TL.Phi(), el_TL.Phi());
    dphi_lept2met = deltaPhi(MET_TL.Phi(), mu_TL.Phi());
    dphi_min = TMath::Min(dphi_lept1met,dphi_lept2met);
    if(dphi_min>PI/2) mpMET = MET;
    if(dphi_min<PI/2) mpMET = MET*TMath::Sin(dphi_min);

    //Minimum of projected METs
    if(dphi_lept1met>PI/2) ppfMET1 = MET;
    if(dphi_lept1met<PI/2) ppfMET1 = MET*TMath::Sin(dphi_lept1met);
    if(dphi_lept2met>PI/2) ppfMET2 = MET;
    if(dphi_lept2met<PI/2) ppfMET2 = MET*TMath::Sin(dphi_lept2met);
    //cout<<ppfMET1<<"\t"<<ppfMET2<<"\t"<<mpMET<<endl;
  }
  return 0;
}

int GGVvBase::CommonCut()
{
  if(pt1>20 && pt2>10){}else{return -1;}
  if(MET>20){}else{return -1;}
  if(DiLept_mass>12){}else{return -1;}
  if(DiLept_pt>30){}else{return -1;}
  if(mpMET>20 && MET>45){}else{return -1;}
  return 1;
}
int GGVvBase::pt1_Cut()
{
  //if(pt1>20 && pt2>10){}else{return -1;}
  if(pt2>10){}else{return -1;}
  if(MET>20){}else{return -1;}
  if(DiLept_mass>12){}else{return -1;}
  if(DiLept_pt>30){}else{return -1;}
  if(mpMET>20 && MET>45){}else{return -1;}
  return 1;
}
int GGVvBase::pt2_Cut()
{
  //if(pt1>20 && pt2>10){}else{return -1;}
  if(pt1>20){}else{return -1;}
  if(MET>20){}else{return -1;}
  if(DiLept_mass>12){}else{return -1;}
  if(DiLept_pt>30){}else{return -1;}
  if(mpMET>20 && MET>45){}else{return -1;}
  return 1;
}
int GGVvBase::MET_Cut()
{
  if(pt1>20 && pt2>10){}else{return -1;}
  //if(MET>20){}else{return -1;}
  if(DiLept_mass>12){}else{return -1;}
  if(DiLept_pt>30){}else{return -1;}
  if(mpMET>20 && MET>45){}else{return -1;}
  return 1;
}
int GGVvBase::DiLept_mass_Cut()
{
  if(pt1>20 && pt2>10){}else{return -1;}
  if(MET>20){}else{return -1;}
  //if(DiLept_mass>12){}else{return -1;}
  if(DiLept_pt>30){}else{return -1;}
  if(mpMET>20 && MET>45){}else{return -1;}
  return 1;
}
int GGVvBase::DiLept_pt_Cut()
{
  if(pt1>20 && pt2>10){}else{return -1;}
  if(MET>20){}else{return -1;}
  if(DiLept_mass>12){}else{return -1;}
  //if(DiLept_pt>30){}else{return -1;}
  if(mpMET>20 && MET>45){}else{return -1;}
  return 1;
}
int GGVvBase::mpMET_Cut()
{
  if(pt1>20 && pt2>10){}else{return -1;}
  if(MET>20){}else{return -1;}
  if(DiLept_mass>12){}else{return -1;}
  if(DiLept_pt>30){}else{return -1;}
  //if(mpMET>20 && MET>45){}else{return -1;}
  return 1;
}

Double_t GGVvBase::deltaPhi(double phi1,double phi2)
{
  double deltaphi = fabs(phi1-phi2);
  if(deltaphi>(2.*PI))deltaphi-=2.*PI;
  if(deltaphi>PI)deltaphi=2.*PI-deltaphi;
  return deltaphi;
}
#endif // #ifdef GGVvBase_cxx
