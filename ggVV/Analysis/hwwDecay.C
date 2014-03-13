#define hwwDecay_cxx
#include "hwwDecay.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>

#include "TLorentzVector.h"
#include "TEfficiency.h"
//#include "TGraphErrors.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <set>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void hwwDecay::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L hwwDecay.C
//      Root > hwwDecay t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   /// Book the histogramms
   TH1F*  mass4leptons =  new TH1F ("mass4leptons","emuvv Invariant Mass",1000,0,1000);
   TH1F*  massT4leptons =  new TH1F ("massT4leptons","emuvv Transverse Mass",1000,0,1000);
   TH1F*  mass2leptons =  new TH1F ("mass2leptons","em Invariant Mass",1000,0,1000);
   TH1F*  pTlMin =  new TH1F ("pTlMin","p_{T}^{l,min}",300,0,300);
   TH1F*  pTlMax =  new TH1F ("pTlMax","p_{T}^{l,max}",300,0,300);
   TH1F*  deltaPhiLeptons =  new TH1F ("deltaPhiLeptons","#Delta#phi^{ll}",18,0,180);
   /// ********************

   if (fChain == 0) return;

   /// Particle masses
   Float_t electron_M = 0.000511;
   Float_t muon_M     = 0.1057;

   Long64_t nentries = fChain->GetEntriesFast();

   Int_t nentryToPrint = 0;
   Int_t incrementEntry = 0;

   //nentries = 100;   

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      nentryToPrint++;
      incrementEntry++;
      if(incrementEntry>9999){
           std::cout << " # Events entered <-- " << nentryToPrint << std::endl;
           incrementEntry=0;
         }
      Int_t maxNumberOfParticles = kMaxParticle;
      //cout << "maxNumberOfParticles " << maxNumberOfParticles << endl;
      TLorentzVector electronLorentz;
      Bool_t isElectron = false;
      TLorentzVector muonLorentz;
      Bool_t isMuon = false;
      TLorentzVector electronNuLorentz;
      Bool_t isElectronNu = false;
      TLorentzVector muonNuLorentz;
      Bool_t isMuonNu = false;
      TLorentzVector higgsLorentz;
      TLorentzVector lepton2Lorentz;
      for(int it = 0; it < maxNumberOfParticles ; it ++) {
      //cout << "Particle ID: " << Particle_PID[it] << " Particle_M: " << Particle_M[it] << endl;
         if(fabs(Particle_PID[it]) == 11){
            electronLorentz.SetXYZM(Particle_Px[it],Particle_Py[it],Particle_Pz[it],electron_M);
            isElectron = true;
         }
         if(fabs(Particle_PID[it]) == 13){
            muonLorentz.SetXYZM(Particle_Px[it],Particle_Py[it],Particle_Pz[it],muon_M);
            isMuon = true;
         }
         if(fabs(Particle_PID[it]) == 12){
            electronNuLorentz.SetXYZM(Particle_Px[it],Particle_Py[it],Particle_Pz[it],0.0);
            isElectronNu = true;
         }
         if(fabs(Particle_PID[it]) == 14){
            muonNuLorentz.SetXYZM(Particle_Px[it],Particle_Py[it],Particle_Pz[it],0.0);
            isMuonNu = true;
         }
      }
      if(isElectron && isMuon && isElectronNu && isMuonNu){
         higgsLorentz = electronLorentz + muonLorentz + electronNuLorentz + muonNuLorentz;
         lepton2Lorentz = electronLorentz + muonLorentz;
         mass4leptons -> Fill(higgsLorentz.M());
         massT4leptons -> Fill(higgsLorentz.Mt());
         mass2leptons -> Fill(lepton2Lorentz.M());
         /// Fill in max and min lepton pT
         Double_t pTe = electronLorentz.Pt();
         Double_t pTmu = muonLorentz.Pt();
         Double_t deltaPhi_ll = electronLorentz.DeltaPhi(muonLorentz);
         deltaPhiLeptons->Fill(((180/M_PI)*(fabs(deltaPhi_ll))));
         if(pTe <= pTmu){
           pTlMin->Fill(pTe);
           pTlMax->Fill(pTmu);
         }
         else{
             pTlMin->Fill(pTmu);
             pTlMax->Fill(pTe);
         }

         //cout << " WW-> e mu nue num " << endl;
         //cout << "Higgs Mass = " <<  higgsLorentz.M() << endl;
      }
   }
   
   /// Produce plots
   
   /// Invariant Mass
   TCanvas *invMass=new TCanvas("invMass","Invariant Mass",600,400);

   mass4leptons -> SetLineColor(kRed+2);
   mass2leptons -> SetLineColor(kGreen+2);
   
   mass4leptons -> Draw();
   mass2leptons -> Draw("same");

   mass4leptons -> GetXaxis()->SetTitle("M[GeV/c^2]");
   mass4leptons ->SetTitle("M_{e#mu#nu#nu} and M_{e#mu}"); 

   TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
   //TLegend *legend = new TLegend(0.4,0.6,0.89,0.89);
   legend->AddEntry(mass4leptons,"M_{e#mu#nu#nu}","l");
   legend->AddEntry(mass2leptons,"M_{e#mu}","l");
   legend->Draw();
   
   invMass->SetLogy();
   invMass->Print("invMass.png");

   /// Lepton pT
   TCanvas *leptonPt=new TCanvas("leptonPt","p_{T}^{l,min} and p_{T}^{l,max}",600,400);

   pTlMin -> SetLineColor(kRed+2);
   pTlMax -> SetLineColor(kGreen+2);
   
   pTlMin -> Draw();
   pTlMax -> Draw("same");

   pTlMin -> GetXaxis()->SetTitle("p_{T}[GeV/c]");

   TLegend *legendPt = new TLegend(0.55,0.65,0.76,0.82);
   //TLegend *legend = new TLegend(0.4,0.6,0.89,0.89);
   legendPt->AddEntry(pTlMin,"p_{T}^{l,min}","l");
   legendPt->AddEntry(pTlMax,"p_{T}^{l,max}","l");
   legendPt->Draw();
   
   //invMass->SetLogy();
   leptonPt->Print("leptonPt.png");

   /// Save plots in a file
   TFile* Plots = new TFile ("higgsPlots.root","recreate");
   mass4leptons->Write();
   mass2leptons->Write();
   massT4leptons->Write();
   pTlMin->Write();
   pTlMax->Write();
   deltaPhiLeptons->Write();
   Plots->Close();
}
