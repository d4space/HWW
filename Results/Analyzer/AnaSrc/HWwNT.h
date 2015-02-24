//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Feb 24 15:57:51 2015 by ROOT version 5.34/18
// from TChain latino/
//////////////////////////////////////////////////////////

#ifndef HWwNT_h
#define HWwNT_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class HWwNT {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         MHiggs;
   Float_t         PtHiggs;
   Float_t         baseW;
   Float_t         bdt1;
   Float_t         bdt2;
   Float_t         bdt3;
   Float_t         bdt4;
   Float_t         ch1;
   Float_t         ch2;
   Float_t         ch3;
   Float_t         ch4;
   Float_t         chSumEt;
   Float_t         channel;
   Float_t         chmet;
   Float_t         chmetphi;
   Float_t         cjeteta1;
   Float_t         cjeteta2;
   Float_t         cjetid1;
   Float_t         cjetid2;
   Float_t         cjetmva1;
   Float_t         cjetmva2;
   Float_t         cjetphi1;
   Float_t         cjetphi2;
   Float_t         cjetpt1;
   Float_t         cjetpt2;
   Float_t         dataset;
   Float_t         detajj;
   Float_t         dphill;
   Float_t         dphilljet;
   Float_t         dphilljetjet;
   Float_t         drll;
   Float_t         eta1;
   Float_t         eta2;
   Float_t         eta3;
   Float_t         eta4;
   Float_t         fakeAW;
   Float_t         fakeBW;
   Float_t         fakeW;
   Float_t         fermiW;
   Float_t         fourW;
   Float_t         gammaMRStar;
   Float_t         hardbjpb;
   Float_t         hardtche;
   Float_t         hypo;
   Float_t         imet;
   Float_t         isSTA1;
   Float_t         isSTA2;
   Float_t         isSTA3;
   Float_t         isSTA4;
   Float_t         iso1;
   Float_t         iso2;
   Float_t         iso3;
   Float_t         iso4;
   Float_t         isomva1;
   Float_t         isomva2;
   Float_t         isomva3;
   Float_t         isomva4;
   Float_t         jetCHM1;
   Float_t         jetCHM2;
   Float_t         jetCHM3;
   Float_t         jetCHM4;
   Float_t         jetNHM1;
   Float_t         jetNHM2;
   Float_t         jetNHM3;
   Float_t         jetNHM4;
   Float_t         jetPhM1;
   Float_t         jetPhM2;
   Float_t         jetPhM3;
   Float_t         jetPhM4;
   Float_t         jetRho;
   Float_t         jetbjpb1;
   Float_t         jetbjpb2;
   Float_t         jetbjpb3;
   Float_t         jetbjpb4;
   Float_t         jeteta1;
   Float_t         jeteta2;
   Float_t         jeteta3;
   Float_t         jeteta4;
   Float_t         jetid1;
   Float_t         jetid2;
   Float_t         jetid3;
   Float_t         jetid4;
   Float_t         jetmva1;
   Float_t         jetmva2;
   Float_t         jetmva3;
   Float_t         jetmva4;
   Float_t         jetphi1;
   Float_t         jetphi2;
   Float_t         jetphi3;
   Float_t         jetphi4;
   Float_t         jetpt1;
   Float_t         jetpt2;
   Float_t         jetpt3;
   Float_t         jetpt4;
   Float_t         jetptd1;
   Float_t         jetptd2;
   Float_t         jetptd3;
   Float_t         jetptd4;
   Float_t         jettche1;
   Float_t         jettche2;
   Float_t         jettche3;
   Float_t         jettche4;
   Float_t         jettchp1;
   Float_t         jettchp2;
   Float_t         jettchp3;
   Float_t         jettchp4;
   Float_t         lh1;
   Float_t         lh2;
   Float_t         lh3;
   Float_t         lh4;
   Float_t         mctruth;
   Float_t         mjj;
   Float_t         mll;
   Float_t         nbjet;
   Float_t         nbjettche;
   Float_t         nbrem1;
   Float_t         nbrem2;
   Float_t         nbrem3;
   Float_t         nbrem4;
   Float_t         nextra;
   Float_t         njet;
   Float_t         njetid;
   Float_t         njetvbf;
   Float_t         pchmet;
   Float_t         pdfid1;
   Float_t         pdfid2;
   Float_t         pdfscalePDF;
   Float_t         pdfx1;
   Float_t         pdfx1PDF;
   Float_t         pdfx2;
   Float_t         pdfx2PDF;
   Float_t         peaking;
   Float_t         pfSumEt;
   Float_t         pfmetSignificance;
   Float_t         phi1;
   Float_t         phi2;
   Float_t         phi3;
   Float_t         phi4;
   Float_t         predmet;
   Float_t         pt1;
   Float_t         pt2;
   Float_t         pt3;
   Float_t         pt4;
   Float_t         ptll;
   Float_t         redmet;
   Float_t         sceta1;
   Float_t         sceta2;
   Float_t         sceta3;
   Float_t         sceta4;
   Float_t         softbjpb;
   Float_t         softtche;
   Float_t         tightmu;
   Float_t         triggAW;
   Float_t         triggBW;
   Float_t         trigger;
   Float_t         worstJetLepPt;
   Float_t         yll;
   Float_t         itpu;
   Float_t         nvtx;
   Float_t         ootpum1;
   Float_t         ootpup1;
   Float_t         puAW;
   Float_t         puBW;
   Float_t         trpu;
   Int_t           bveto;
   Int_t           bveto_ip;
   Int_t           bveto_mu;
   Int_t           bveto_munj;
   Int_t           bveto_munj05;
   Int_t           bveto_munj30;
   Int_t           bveto_munj3005;
   Int_t           bveto_nj;
   Int_t           bveto_nj05;
   Int_t           bveto_nj30;
   Int_t           bveto_nj3005;
   Int_t           dphiveto;
   Int_t           pass2012ICHEP1;
   Int_t           pass2012ICHEP2;
   Int_t           pass2012ICHEP3;
   Int_t           pass2012ICHEP4;
   Int_t           sameflav;
   Int_t           zveto;
   UInt_t          run;
   UInt_t          lumi;
   UInt_t          event;
   Float_t         puW;
   Float_t         dphillmet;
   Float_t         dphilmet;
   Float_t         dphilmet1;
   Float_t         dphilmet2;
   Float_t         mth;
   Float_t         mtw1;
   Float_t         mtw2;
   Float_t         pfmet;
   Float_t         pfmetphi;
   Float_t         ppfmet;
   Float_t         mpmet;
   Float_t         dymva0;
   Float_t         dymva1;
   Float_t         dphilljet1;
   Float_t         dphimetjet1;
   Float_t         recoil;
   Float_t         pfmetMEtSig;
   Float_t         kfW;
   Float_t         effW;
   Float_t         effAW;
   Float_t         effBW;
   Float_t         effCW;
   Float_t         effDW;
   Float_t         puWD;
   Float_t         puWA;
   Float_t         puWB;
   Float_t         puWC;
   Float_t         puWABC;
   Float_t         effABCW;
   Float_t         triggW;
   Float_t         effWMuUp;
   Float_t         effWElUp;
   Float_t         effWMuDown;
   Float_t         effWElDown;
   Float_t         effWUp;
   Float_t         effWDown;
   Float_t         HwidthMVAbkg;
   Float_t         HwidthMVAggH;

   // List of branches
   TBranch        *b_MHiggs;   //!
   TBranch        *b_PtHiggs;   //!
   TBranch        *b_baseW;   //!
   TBranch        *b_bdt1;   //!
   TBranch        *b_bdt2;   //!
   TBranch        *b_bdt3;   //!
   TBranch        *b_bdt4;   //!
   TBranch        *b_ch1;   //!
   TBranch        *b_ch2;   //!
   TBranch        *b_ch3;   //!
   TBranch        *b_ch4;   //!
   TBranch        *b_chSumEt;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_chmet;   //!
   TBranch        *b_chmetphi;   //!
   TBranch        *b_cjeteta1;   //!
   TBranch        *b_cjeteta2;   //!
   TBranch        *b_cjetid1;   //!
   TBranch        *b_cjetid2;   //!
   TBranch        *b_cjetmva1;   //!
   TBranch        *b_cjetmva2;   //!
   TBranch        *b_cjetphi1;   //!
   TBranch        *b_cjetphi2;   //!
   TBranch        *b_cjetpt1;   //!
   TBranch        *b_cjetpt2;   //!
   TBranch        *b_dataset;   //!
   TBranch        *b_detajj;   //!
   TBranch        *b_dphill;   //!
   TBranch        *b_dphilljet;   //!
   TBranch        *b_dphilljetjet;   //!
   TBranch        *b_drll;   //!
   TBranch        *b_eta1;   //!
   TBranch        *b_eta2;   //!
   TBranch        *b_eta3;   //!
   TBranch        *b_eta4;   //!
   TBranch        *b_fakeAW;   //!
   TBranch        *b_fakeBW;   //!
   TBranch        *b_fakeW;   //!
   TBranch        *b_fermiW;   //!
   TBranch        *b_fourW;   //!
   TBranch        *b_gammaMRStar;   //!
   TBranch        *b_hardbjpb;   //!
   TBranch        *b_hardtche;   //!
   TBranch        *b_hypo;   //!
   TBranch        *b_imet;   //!
   TBranch        *b_isSTA1;   //!
   TBranch        *b_isSTA2;   //!
   TBranch        *b_isSTA3;   //!
   TBranch        *b_isSTA4;   //!
   TBranch        *b_iso1;   //!
   TBranch        *b_iso2;   //!
   TBranch        *b_iso3;   //!
   TBranch        *b_iso4;   //!
   TBranch        *b_isomva1;   //!
   TBranch        *b_isomva2;   //!
   TBranch        *b_isomva3;   //!
   TBranch        *b_isomva4;   //!
   TBranch        *b_jetCHM1;   //!
   TBranch        *b_jetCHM2;   //!
   TBranch        *b_jetCHM3;   //!
   TBranch        *b_jetCHM4;   //!
   TBranch        *b_jetNHM1;   //!
   TBranch        *b_jetNHM2;   //!
   TBranch        *b_jetNHM3;   //!
   TBranch        *b_jetNHM4;   //!
   TBranch        *b_jetPhM1;   //!
   TBranch        *b_jetPhM2;   //!
   TBranch        *b_jetPhM3;   //!
   TBranch        *b_jetPhM4;   //!
   TBranch        *b_jetRho;   //!
   TBranch        *b_jetbjpb1;   //!
   TBranch        *b_jetbjpb2;   //!
   TBranch        *b_jetbjpb3;   //!
   TBranch        *b_jetbjpb4;   //!
   TBranch        *b_jeteta1;   //!
   TBranch        *b_jeteta2;   //!
   TBranch        *b_jeteta3;   //!
   TBranch        *b_jeteta4;   //!
   TBranch        *b_jetid1;   //!
   TBranch        *b_jetid2;   //!
   TBranch        *b_jetid3;   //!
   TBranch        *b_jetid4;   //!
   TBranch        *b_jetmva1;   //!
   TBranch        *b_jetmva2;   //!
   TBranch        *b_jetmva3;   //!
   TBranch        *b_jetmva4;   //!
   TBranch        *b_jetphi1;   //!
   TBranch        *b_jetphi2;   //!
   TBranch        *b_jetphi3;   //!
   TBranch        *b_jetphi4;   //!
   TBranch        *b_jetpt1;   //!
   TBranch        *b_jetpt2;   //!
   TBranch        *b_jetpt3;   //!
   TBranch        *b_jetpt4;   //!
   TBranch        *b_jetptd1;   //!
   TBranch        *b_jetptd2;   //!
   TBranch        *b_jetptd3;   //!
   TBranch        *b_jetptd4;   //!
   TBranch        *b_jettche1;   //!
   TBranch        *b_jettche2;   //!
   TBranch        *b_jettche3;   //!
   TBranch        *b_jettche4;   //!
   TBranch        *b_jettchp1;   //!
   TBranch        *b_jettchp2;   //!
   TBranch        *b_jettchp3;   //!
   TBranch        *b_jettchp4;   //!
   TBranch        *b_lh1;   //!
   TBranch        *b_lh2;   //!
   TBranch        *b_lh3;   //!
   TBranch        *b_lh4;   //!
   TBranch        *b_mctruth;   //!
   TBranch        *b_mjj;   //!
   TBranch        *b_mll;   //!
   TBranch        *b_nbjet;   //!
   TBranch        *b_nbjettche;   //!
   TBranch        *b_nbrem1;   //!
   TBranch        *b_nbrem2;   //!
   TBranch        *b_nbrem3;   //!
   TBranch        *b_nbrem4;   //!
   TBranch        *b_nextra;   //!
   TBranch        *b_njet;   //!
   TBranch        *b_njetid;   //!
   TBranch        *b_njetvbf;   //!
   TBranch        *b_pchmet;   //!
   TBranch        *b_pdfid1;   //!
   TBranch        *b_pdfid2;   //!
   TBranch        *b_pdfscalePDF;   //!
   TBranch        *b_pdfx1;   //!
   TBranch        *b_pdfx1PDF;   //!
   TBranch        *b_pdfx2;   //!
   TBranch        *b_pdfx2PDF;   //!
   TBranch        *b_peaking;   //!
   TBranch        *b_pfSumEt;   //!
   TBranch        *b_pfmetSignificance;   //!
   TBranch        *b_phi1;   //!
   TBranch        *b_phi2;   //!
   TBranch        *b_phi3;   //!
   TBranch        *b_phi4;   //!
   TBranch        *b_predmet;   //!
   TBranch        *b_pt1;   //!
   TBranch        *b_pt2;   //!
   TBranch        *b_pt3;   //!
   TBranch        *b_pt4;   //!
   TBranch        *b_ptll;   //!
   TBranch        *b_redmet;   //!
   TBranch        *b_sceta1;   //!
   TBranch        *b_sceta2;   //!
   TBranch        *b_sceta3;   //!
   TBranch        *b_sceta4;   //!
   TBranch        *b_softbjpb;   //!
   TBranch        *b_softtche;   //!
   TBranch        *b_tightmu;   //!
   TBranch        *b_triggAW;   //!
   TBranch        *b_triggBW;   //!
   TBranch        *b_trigger;   //!
   TBranch        *b_worstJetLepPt;   //!
   TBranch        *b_yll;   //!
   TBranch        *b_itpu;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_ootpum1;   //!
   TBranch        *b_ootpup1;   //!
   TBranch        *b_puAW;   //!
   TBranch        *b_puBW;   //!
   TBranch        *b_trpu;   //!
   TBranch        *b_bveto;   //!
   TBranch        *b_bveto_ip;   //!
   TBranch        *b_bveto_mu;   //!
   TBranch        *b_bveto_munj;   //!
   TBranch        *b_bveto_munj05;   //!
   TBranch        *b_bveto_munj30;   //!
   TBranch        *b_bveto_munj3005;   //!
   TBranch        *b_bveto_nj;   //!
   TBranch        *b_bveto_nj05;   //!
   TBranch        *b_bveto_nj30;   //!
   TBranch        *b_bveto_nj3005;   //!
   TBranch        *b_dphiveto;   //!
   TBranch        *b_pass2012ICHEP1;   //!
   TBranch        *b_pass2012ICHEP2;   //!
   TBranch        *b_pass2012ICHEP3;   //!
   TBranch        *b_pass2012ICHEP4;   //!
   TBranch        *b_sameflav;   //!
   TBranch        *b_zveto;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_puW;   //!
   TBranch        *b_dphillmet;   //!
   TBranch        *b_dphilmet;   //!
   TBranch        *b_dphilmet1;   //!
   TBranch        *b_dphilmet2;   //!
   TBranch        *b_mth;   //!
   TBranch        *b_mtw1;   //!
   TBranch        *b_mtw2;   //!
   TBranch        *b_pfmet;   //!
   TBranch        *b_pfmetphi;   //!
   TBranch        *b_ppfmet;   //!
   TBranch        *b_mpmet;   //!
   TBranch        *b_dymva0;   //!
   TBranch        *b_dymva1;   //!
   TBranch        *b_dphilljet1;   //!
   TBranch        *b_dphimetjet1;   //!
   TBranch        *b_recoil;   //!
   TBranch        *b_pfmetMEtSig;   //!
   TBranch        *b_kfW;   //!
   TBranch        *b_effW;   //!
   TBranch        *b_effAW;   //!
   TBranch        *b_effBW;   //!
   TBranch        *b_effCW;   //!
   TBranch        *b_effDW;   //!
   TBranch        *b_puWD;   //!
   TBranch        *b_puWA;   //!
   TBranch        *b_puWB;   //!
   TBranch        *b_puWC;   //!
   TBranch        *b_puWABC;   //!
   TBranch        *b_effABCW;   //!
   TBranch        *b_triggW;   //!
   TBranch        *b_effWMuUp;   //!
   TBranch        *b_effWElUp;   //!
   TBranch        *b_effWMuDown;   //!
   TBranch        *b_effWElDown;   //!
   TBranch        *b_effWUp;   //!
   TBranch        *b_effWDown;   //!
   TBranch        *b_HwidthMVAbkg;   //!
   TBranch        *b_HwidthMVAggH;   //!

   HWwNT(TTree *tree=0);
   virtual ~HWwNT();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HWwNT_cxx
HWwNT::HWwNT(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("latino",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("latino","");
      chain->Add("latino_2130_vbfToH130toWWTo2LAndTau2Nu.root/latino");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

HWwNT::~HWwNT()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HWwNT::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HWwNT::LoadTree(Long64_t entry)
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

void HWwNT::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("MHiggs", &MHiggs, &b_MHiggs);
   fChain->SetBranchAddress("PtHiggs", &PtHiggs, &b_PtHiggs);
   fChain->SetBranchAddress("baseW", &baseW, &b_baseW);
   fChain->SetBranchAddress("bdt1", &bdt1, &b_bdt1);
   fChain->SetBranchAddress("bdt2", &bdt2, &b_bdt2);
   fChain->SetBranchAddress("bdt3", &bdt3, &b_bdt3);
   fChain->SetBranchAddress("bdt4", &bdt4, &b_bdt4);
   fChain->SetBranchAddress("ch1", &ch1, &b_ch1);
   fChain->SetBranchAddress("ch2", &ch2, &b_ch2);
   fChain->SetBranchAddress("ch3", &ch3, &b_ch3);
   fChain->SetBranchAddress("ch4", &ch4, &b_ch4);
   fChain->SetBranchAddress("chSumEt", &chSumEt, &b_chSumEt);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("chmet", &chmet, &b_chmet);
   fChain->SetBranchAddress("chmetphi", &chmetphi, &b_chmetphi);
   fChain->SetBranchAddress("cjeteta1", &cjeteta1, &b_cjeteta1);
   fChain->SetBranchAddress("cjeteta2", &cjeteta2, &b_cjeteta2);
   fChain->SetBranchAddress("cjetid1", &cjetid1, &b_cjetid1);
   fChain->SetBranchAddress("cjetid2", &cjetid2, &b_cjetid2);
   fChain->SetBranchAddress("cjetmva1", &cjetmva1, &b_cjetmva1);
   fChain->SetBranchAddress("cjetmva2", &cjetmva2, &b_cjetmva2);
   fChain->SetBranchAddress("cjetphi1", &cjetphi1, &b_cjetphi1);
   fChain->SetBranchAddress("cjetphi2", &cjetphi2, &b_cjetphi2);
   fChain->SetBranchAddress("cjetpt1", &cjetpt1, &b_cjetpt1);
   fChain->SetBranchAddress("cjetpt2", &cjetpt2, &b_cjetpt2);
   fChain->SetBranchAddress("dataset", &dataset, &b_dataset);
   fChain->SetBranchAddress("detajj", &detajj, &b_detajj);
   fChain->SetBranchAddress("dphill", &dphill, &b_dphill);
   fChain->SetBranchAddress("dphilljet", &dphilljet, &b_dphilljet);
   fChain->SetBranchAddress("dphilljetjet", &dphilljetjet, &b_dphilljetjet);
   fChain->SetBranchAddress("drll", &drll, &b_drll);
   fChain->SetBranchAddress("eta1", &eta1, &b_eta1);
   fChain->SetBranchAddress("eta2", &eta2, &b_eta2);
   fChain->SetBranchAddress("eta3", &eta3, &b_eta3);
   fChain->SetBranchAddress("eta4", &eta4, &b_eta4);
   fChain->SetBranchAddress("fakeAW", &fakeAW, &b_fakeAW);
   fChain->SetBranchAddress("fakeBW", &fakeBW, &b_fakeBW);
   fChain->SetBranchAddress("fakeW", &fakeW, &b_fakeW);
   fChain->SetBranchAddress("fermiW", &fermiW, &b_fermiW);
   fChain->SetBranchAddress("fourW", &fourW, &b_fourW);
   fChain->SetBranchAddress("gammaMRStar", &gammaMRStar, &b_gammaMRStar);
   fChain->SetBranchAddress("hardbjpb", &hardbjpb, &b_hardbjpb);
   fChain->SetBranchAddress("hardtche", &hardtche, &b_hardtche);
   fChain->SetBranchAddress("hypo", &hypo, &b_hypo);
   fChain->SetBranchAddress("imet", &imet, &b_imet);
   fChain->SetBranchAddress("isSTA1", &isSTA1, &b_isSTA1);
   fChain->SetBranchAddress("isSTA2", &isSTA2, &b_isSTA2);
   fChain->SetBranchAddress("isSTA3", &isSTA3, &b_isSTA3);
   fChain->SetBranchAddress("isSTA4", &isSTA4, &b_isSTA4);
   fChain->SetBranchAddress("iso1", &iso1, &b_iso1);
   fChain->SetBranchAddress("iso2", &iso2, &b_iso2);
   fChain->SetBranchAddress("iso3", &iso3, &b_iso3);
   fChain->SetBranchAddress("iso4", &iso4, &b_iso4);
   fChain->SetBranchAddress("isomva1", &isomva1, &b_isomva1);
   fChain->SetBranchAddress("isomva2", &isomva2, &b_isomva2);
   fChain->SetBranchAddress("isomva3", &isomva3, &b_isomva3);
   fChain->SetBranchAddress("isomva4", &isomva4, &b_isomva4);
   fChain->SetBranchAddress("jetCHM1", &jetCHM1, &b_jetCHM1);
   fChain->SetBranchAddress("jetCHM2", &jetCHM2, &b_jetCHM2);
   fChain->SetBranchAddress("jetCHM3", &jetCHM3, &b_jetCHM3);
   fChain->SetBranchAddress("jetCHM4", &jetCHM4, &b_jetCHM4);
   fChain->SetBranchAddress("jetNHM1", &jetNHM1, &b_jetNHM1);
   fChain->SetBranchAddress("jetNHM2", &jetNHM2, &b_jetNHM2);
   fChain->SetBranchAddress("jetNHM3", &jetNHM3, &b_jetNHM3);
   fChain->SetBranchAddress("jetNHM4", &jetNHM4, &b_jetNHM4);
   fChain->SetBranchAddress("jetPhM1", &jetPhM1, &b_jetPhM1);
   fChain->SetBranchAddress("jetPhM2", &jetPhM2, &b_jetPhM2);
   fChain->SetBranchAddress("jetPhM3", &jetPhM3, &b_jetPhM3);
   fChain->SetBranchAddress("jetPhM4", &jetPhM4, &b_jetPhM4);
   fChain->SetBranchAddress("jetRho", &jetRho, &b_jetRho);
   fChain->SetBranchAddress("jetbjpb1", &jetbjpb1, &b_jetbjpb1);
   fChain->SetBranchAddress("jetbjpb2", &jetbjpb2, &b_jetbjpb2);
   fChain->SetBranchAddress("jetbjpb3", &jetbjpb3, &b_jetbjpb3);
   fChain->SetBranchAddress("jetbjpb4", &jetbjpb4, &b_jetbjpb4);
   fChain->SetBranchAddress("jeteta1", &jeteta1, &b_jeteta1);
   fChain->SetBranchAddress("jeteta2", &jeteta2, &b_jeteta2);
   fChain->SetBranchAddress("jeteta3", &jeteta3, &b_jeteta3);
   fChain->SetBranchAddress("jeteta4", &jeteta4, &b_jeteta4);
   fChain->SetBranchAddress("jetid1", &jetid1, &b_jetid1);
   fChain->SetBranchAddress("jetid2", &jetid2, &b_jetid2);
   fChain->SetBranchAddress("jetid3", &jetid3, &b_jetid3);
   fChain->SetBranchAddress("jetid4", &jetid4, &b_jetid4);
   fChain->SetBranchAddress("jetmva1", &jetmva1, &b_jetmva1);
   fChain->SetBranchAddress("jetmva2", &jetmva2, &b_jetmva2);
   fChain->SetBranchAddress("jetmva3", &jetmva3, &b_jetmva3);
   fChain->SetBranchAddress("jetmva4", &jetmva4, &b_jetmva4);
   fChain->SetBranchAddress("jetphi1", &jetphi1, &b_jetphi1);
   fChain->SetBranchAddress("jetphi2", &jetphi2, &b_jetphi2);
   fChain->SetBranchAddress("jetphi3", &jetphi3, &b_jetphi3);
   fChain->SetBranchAddress("jetphi4", &jetphi4, &b_jetphi4);
   fChain->SetBranchAddress("jetpt1", &jetpt1, &b_jetpt1);
   fChain->SetBranchAddress("jetpt2", &jetpt2, &b_jetpt2);
   fChain->SetBranchAddress("jetpt3", &jetpt3, &b_jetpt3);
   fChain->SetBranchAddress("jetpt4", &jetpt4, &b_jetpt4);
   fChain->SetBranchAddress("jetptd1", &jetptd1, &b_jetptd1);
   fChain->SetBranchAddress("jetptd2", &jetptd2, &b_jetptd2);
   fChain->SetBranchAddress("jetptd3", &jetptd3, &b_jetptd3);
   fChain->SetBranchAddress("jetptd4", &jetptd4, &b_jetptd4);
   fChain->SetBranchAddress("jettche1", &jettche1, &b_jettche1);
   fChain->SetBranchAddress("jettche2", &jettche2, &b_jettche2);
   fChain->SetBranchAddress("jettche3", &jettche3, &b_jettche3);
   fChain->SetBranchAddress("jettche4", &jettche4, &b_jettche4);
   fChain->SetBranchAddress("jettchp1", &jettchp1, &b_jettchp1);
   fChain->SetBranchAddress("jettchp2", &jettchp2, &b_jettchp2);
   fChain->SetBranchAddress("jettchp3", &jettchp3, &b_jettchp3);
   fChain->SetBranchAddress("jettchp4", &jettchp4, &b_jettchp4);
   fChain->SetBranchAddress("lh1", &lh1, &b_lh1);
   fChain->SetBranchAddress("lh2", &lh2, &b_lh2);
   fChain->SetBranchAddress("lh3", &lh3, &b_lh3);
   fChain->SetBranchAddress("lh4", &lh4, &b_lh4);
   fChain->SetBranchAddress("mctruth", &mctruth, &b_mctruth);
   fChain->SetBranchAddress("mjj", &mjj, &b_mjj);
   fChain->SetBranchAddress("mll", &mll, &b_mll);
   fChain->SetBranchAddress("nbjet", &nbjet, &b_nbjet);
   fChain->SetBranchAddress("nbjettche", &nbjettche, &b_nbjettche);
   fChain->SetBranchAddress("nbrem1", &nbrem1, &b_nbrem1);
   fChain->SetBranchAddress("nbrem2", &nbrem2, &b_nbrem2);
   fChain->SetBranchAddress("nbrem3", &nbrem3, &b_nbrem3);
   fChain->SetBranchAddress("nbrem4", &nbrem4, &b_nbrem4);
   fChain->SetBranchAddress("nextra", &nextra, &b_nextra);
   fChain->SetBranchAddress("njet", &njet, &b_njet);
   fChain->SetBranchAddress("njetid", &njetid, &b_njetid);
   fChain->SetBranchAddress("njetvbf", &njetvbf, &b_njetvbf);
   fChain->SetBranchAddress("pchmet", &pchmet, &b_pchmet);
   fChain->SetBranchAddress("pdfid1", &pdfid1, &b_pdfid1);
   fChain->SetBranchAddress("pdfid2", &pdfid2, &b_pdfid2);
   fChain->SetBranchAddress("pdfscalePDF", &pdfscalePDF, &b_pdfscalePDF);
   fChain->SetBranchAddress("pdfx1", &pdfx1, &b_pdfx1);
   fChain->SetBranchAddress("pdfx1PDF", &pdfx1PDF, &b_pdfx1PDF);
   fChain->SetBranchAddress("pdfx2", &pdfx2, &b_pdfx2);
   fChain->SetBranchAddress("pdfx2PDF", &pdfx2PDF, &b_pdfx2PDF);
   fChain->SetBranchAddress("peaking", &peaking, &b_peaking);
   fChain->SetBranchAddress("pfSumEt", &pfSumEt, &b_pfSumEt);
   fChain->SetBranchAddress("pfmetSignificance", &pfmetSignificance, &b_pfmetSignificance);
   fChain->SetBranchAddress("phi1", &phi1, &b_phi1);
   fChain->SetBranchAddress("phi2", &phi2, &b_phi2);
   fChain->SetBranchAddress("phi3", &phi3, &b_phi3);
   fChain->SetBranchAddress("phi4", &phi4, &b_phi4);
   fChain->SetBranchAddress("predmet", &predmet, &b_predmet);
   fChain->SetBranchAddress("pt1", &pt1, &b_pt1);
   fChain->SetBranchAddress("pt2", &pt2, &b_pt2);
   fChain->SetBranchAddress("pt3", &pt3, &b_pt3);
   fChain->SetBranchAddress("pt4", &pt4, &b_pt4);
   fChain->SetBranchAddress("ptll", &ptll, &b_ptll);
   fChain->SetBranchAddress("redmet", &redmet, &b_redmet);
   fChain->SetBranchAddress("sceta1", &sceta1, &b_sceta1);
   fChain->SetBranchAddress("sceta2", &sceta2, &b_sceta2);
   fChain->SetBranchAddress("sceta3", &sceta3, &b_sceta3);
   fChain->SetBranchAddress("sceta4", &sceta4, &b_sceta4);
   fChain->SetBranchAddress("softbjpb", &softbjpb, &b_softbjpb);
   fChain->SetBranchAddress("softtche", &softtche, &b_softtche);
   fChain->SetBranchAddress("tightmu", &tightmu, &b_tightmu);
   fChain->SetBranchAddress("triggAW", &triggAW, &b_triggAW);
   fChain->SetBranchAddress("triggBW", &triggBW, &b_triggBW);
   fChain->SetBranchAddress("trigger", &trigger, &b_trigger);
   fChain->SetBranchAddress("worstJetLepPt", &worstJetLepPt, &b_worstJetLepPt);
   fChain->SetBranchAddress("yll", &yll, &b_yll);
   fChain->SetBranchAddress("itpu", &itpu, &b_itpu);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("ootpum1", &ootpum1, &b_ootpum1);
   fChain->SetBranchAddress("ootpup1", &ootpup1, &b_ootpup1);
   fChain->SetBranchAddress("puAW", &puAW, &b_puAW);
   fChain->SetBranchAddress("puBW", &puBW, &b_puBW);
   fChain->SetBranchAddress("trpu", &trpu, &b_trpu);
   fChain->SetBranchAddress("bveto", &bveto, &b_bveto);
   fChain->SetBranchAddress("bveto_ip", &bveto_ip, &b_bveto_ip);
   fChain->SetBranchAddress("bveto_mu", &bveto_mu, &b_bveto_mu);
   fChain->SetBranchAddress("bveto_munj", &bveto_munj, &b_bveto_munj);
   fChain->SetBranchAddress("bveto_munj05", &bveto_munj05, &b_bveto_munj05);
   fChain->SetBranchAddress("bveto_munj30", &bveto_munj30, &b_bveto_munj30);
   fChain->SetBranchAddress("bveto_munj3005", &bveto_munj3005, &b_bveto_munj3005);
   fChain->SetBranchAddress("bveto_nj", &bveto_nj, &b_bveto_nj);
   fChain->SetBranchAddress("bveto_nj05", &bveto_nj05, &b_bveto_nj05);
   fChain->SetBranchAddress("bveto_nj30", &bveto_nj30, &b_bveto_nj30);
   fChain->SetBranchAddress("bveto_nj3005", &bveto_nj3005, &b_bveto_nj3005);
   fChain->SetBranchAddress("dphiveto", &dphiveto, &b_dphiveto);
   fChain->SetBranchAddress("pass2012ICHEP1", &pass2012ICHEP1, &b_pass2012ICHEP1);
   fChain->SetBranchAddress("pass2012ICHEP2", &pass2012ICHEP2, &b_pass2012ICHEP2);
   fChain->SetBranchAddress("pass2012ICHEP3", &pass2012ICHEP3, &b_pass2012ICHEP3);
   fChain->SetBranchAddress("pass2012ICHEP4", &pass2012ICHEP4, &b_pass2012ICHEP4);
   fChain->SetBranchAddress("sameflav", &sameflav, &b_sameflav);
   fChain->SetBranchAddress("zveto", &zveto, &b_zveto);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("puW", &puW, &b_puW);
   fChain->SetBranchAddress("dphillmet", &dphillmet, &b_dphillmet);
   fChain->SetBranchAddress("dphilmet", &dphilmet, &b_dphilmet);
   fChain->SetBranchAddress("dphilmet1", &dphilmet1, &b_dphilmet1);
   fChain->SetBranchAddress("dphilmet2", &dphilmet2, &b_dphilmet2);
   fChain->SetBranchAddress("mth", &mth, &b_mth);
   fChain->SetBranchAddress("mtw1", &mtw1, &b_mtw1);
   fChain->SetBranchAddress("mtw2", &mtw2, &b_mtw2);
   fChain->SetBranchAddress("pfmet", &pfmet, &b_pfmet);
   fChain->SetBranchAddress("pfmetphi", &pfmetphi, &b_pfmetphi);
   fChain->SetBranchAddress("ppfmet", &ppfmet, &b_ppfmet);
   fChain->SetBranchAddress("mpmet", &mpmet, &b_mpmet);
   fChain->SetBranchAddress("dymva0", &dymva0, &b_dymva0);
   fChain->SetBranchAddress("dymva1", &dymva1, &b_dymva1);
   fChain->SetBranchAddress("dphilljet1", &dphilljet1, &b_dphilljet1);
   fChain->SetBranchAddress("dphimetjet1", &dphimetjet1, &b_dphimetjet1);
   fChain->SetBranchAddress("recoil", &recoil, &b_recoil);
   fChain->SetBranchAddress("pfmetMEtSig", &pfmetMEtSig, &b_pfmetMEtSig);
   fChain->SetBranchAddress("kfW", &kfW, &b_kfW);
   fChain->SetBranchAddress("effW", &effW, &b_effW);
   fChain->SetBranchAddress("effAW", &effAW, &b_effAW);
   fChain->SetBranchAddress("effBW", &effBW, &b_effBW);
   fChain->SetBranchAddress("effCW", &effCW, &b_effCW);
   fChain->SetBranchAddress("effDW", &effDW, &b_effDW);
   fChain->SetBranchAddress("puWD", &puWD, &b_puWD);
   fChain->SetBranchAddress("puWA", &puWA, &b_puWA);
   fChain->SetBranchAddress("puWB", &puWB, &b_puWB);
   fChain->SetBranchAddress("puWC", &puWC, &b_puWC);
   fChain->SetBranchAddress("puWABC", &puWABC, &b_puWABC);
   fChain->SetBranchAddress("effABCW", &effABCW, &b_effABCW);
   fChain->SetBranchAddress("triggW", &triggW, &b_triggW);
   fChain->SetBranchAddress("effWMuUp", &effWMuUp, &b_effWMuUp);
   fChain->SetBranchAddress("effWElUp", &effWElUp, &b_effWElUp);
   fChain->SetBranchAddress("effWMuDown", &effWMuDown, &b_effWMuDown);
   fChain->SetBranchAddress("effWElDown", &effWElDown, &b_effWElDown);
   fChain->SetBranchAddress("effWUp", &effWUp, &b_effWUp);
   fChain->SetBranchAddress("effWDown", &effWDown, &b_effWDown);
   fChain->SetBranchAddress("HwidthMVAbkg", &HwidthMVAbkg, &b_HwidthMVAbkg);
   fChain->SetBranchAddress("HwidthMVAggH", &HwidthMVAggH, &b_HwidthMVAggH);
   Notify();
}

Bool_t HWwNT::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HWwNT::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HWwNT::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HWwNT_cxx
