#include "TChain.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMath.h"
#include "TSystem.h"
#include "TTree.h"
#include <iomanip>
#include <iostream>

// Constants
//------------------------------------------------------------------------------
const Double_t luminosity = 19.365;
const Double_t muMass  = 0.10566; // GeV
const Double_t eleMass = 0.00051; // GeV
const Double_t tauMass = 1.77682; // GeV

const UInt_t nLevels = 20;

const Int_t HwidthMVA_NoBin = 17 ;// sizeof(HwidthMVA_Bins);
const Double_t HwidthMVA_Bins[HwidthMVA_NoBin+1] = {-1.00, -0.70, -0.60, -0.50, -0.40, -0.30, -0.20, -0.10, 0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 1.00};

enum {
  Level_InclJet,
  Level_InclJet_emu,
  Level_InclJet_emu_SF,
  Level_InclJet_emu_OF,
  Level_InclJet_tau,
  Level_0Jet,
  Level_0Jet_emu,
  Level_0Jet_emu_SF,
  Level_0Jet_emu_OF,
  Level_0Jet_tau,
  Level_1Jet,
  Level_1Jet_emu,
  Level_1Jet_emu_SF,
  Level_1Jet_emu_OF,
  Level_1Jet_tau,
  Level_2Jet,
  Level_2Jet_emu,
  Level_2Jet_emu_SF,
  Level_2Jet_emu_OF,
  Level_2Jet_tau
};

const TString sLevel[nLevels] = {
  "_InclJet",
  "_InclJet_emu",
  "_InclJet_emu_SF",
  "_InclJet_emu_OF",
  "_InclJet_tau",
  "_0Jet",
  "_0Jet_emu",
  "_0Jet_emu_SF",
  "_0Jet_emu_OF",
  "_0Jet_tau",
  "_1Jet",
  "_1Jet_emu",
  "_1Jet_emu_SF",
  "_1Jet_emu_OF",
  "_1Jet_tau",
  "_2Jet",
  "_2Jet_emu",
  "_2Jet_emu_SF",
  "_2Jet_emu_OF",
  "_2Jet_tau"
};

namespace GenType
{
  enum{
    kElectron   = 11,
    keNeutrino  = 12,
    kMuon       = 13, //Muon (-)
    kmuNeutrino = 14,
    kTau        = 15, //Tau (-)
    ktauNeutrino = 16,
    kTauElectron= 150011,
    kTauMuon    = 150013,
    kGluon      = 21,
    kGamma      = 22,
    kZ         = 23,
    kW          = 24,
    kHiggs      = 25,
    kWW         = 24024,
    kVZ         = 26023,
    kZgamma     = 23022,
    kWgamma     = 24022
  };
}


// Member functions
//------------------------------------------------------------------------------
void FillHistograms(UInt_t level, UInt_t check);

// Data members
//------------------------------------------------------------------------------
TH1F*   h1genMet       [nLevels];
TH1F*   h1pfType1Met   [nLevels];
TH1F*   h1pfRawMet     [nLevels];
TH1F*   h1puppiMet     [nLevels];
TH1F*   h1trkMet       [nLevels];
TH1F*   h1ppfType1Met  [nLevels];
TH1F*   h1pfType1Metdn [nLevels];
TH1F*   h1pfType1Metup [nLevels];

TH2F*   h2pfType1MetResol  [nLevels];
TH2F*   h2pfRawMetResol    [nLevels];
TH2F*   h2puppiMetResol    [nLevels];
TH2F*   h2trkMetResol      [nLevels];
TH2F*   h2ppfType1MetResol [nLevels];

Float_t evtWeight;

// Tree variables
//------------------------------------------------------------------------------
Float_t         channel;
Float_t         ch1;
Float_t         ch2;
Float_t         njet;
Float_t         mll;
Float_t         pt1;
Float_t         pt2;
Float_t         metGenpt;
Float_t         pfType1Met;
Float_t         pfType1Metdn;
Float_t         pfType1Metup;
Float_t         pfRawMet;
Float_t         pupMet;
Float_t         trkMet;
Float_t         ppfMet;
Float_t         neutrinoGenpid1;
Float_t         neutrinoGenpid2;
Float_t         neutrinoGenpid3;
UInt_t          event;
vector<float>   *std_vector_leptonGen_pid;
vector<float>   *std_vector_leptonGen_status;
vector<float>   *std_vector_leptonGen_pt;
vector<float>   *std_vector_leptonGen_mpid;
vector<float>   *std_vector_leptonGen_mstatus;

//------------------------------------------------------------------------------
// MakeMetHistoScript
//------------------------------------------------------------------------------
void MakeGenHistoScript(TString theSample)
{
  TH1::SetDefaultSumw2();

  TString path = Form("rootfiles/%s/", theSample.Data());

  gSystem->mkdir(path, kTRUE);

  TFile* output = new TFile(path + theSample + ".root", "recreate");

  // Histograms
  //----------------------------------------------------------------------------
  for (UInt_t i=0; i<nLevels; i++) {
    h1genMet           [i] = new TH1F("h1genMet"            + sLevel[i], "", 50, 0, 120);
    h1pfType1Met       [i] = new TH1F("h1pfType1Met"        + sLevel[i], "", 50, 0, 120);
    h1pfRawMet         [i] = new TH1F("h1pfRawMet"          + sLevel[i], "", 50, 0, 120);
    h1puppiMet         [i] = new TH1F("h1puppiMet"          + sLevel[i], "", 50, 0, 120);
    h1trkMet           [i] = new TH1F("h1trkMet"            + sLevel[i], "", 50, 0, 120);
    h1ppfType1Met      [i] = new TH1F("h1ppfType1Met"       + sLevel[i], "", 50, 0, 120);
    h1pfType1Metdn     [i] = new TH1F("h1pfType1Metdn"      + sLevel[i], "", 50, 0, 120);
    h1pfType1Metup     [i] = new TH1F("h1pfType1Metup"      + sLevel[i], "", 50, 0, 120);

    h2pfType1MetResol       [i] = new TH2F("h2pfType1MetResol"        + sLevel[i], "", 50, 0, 120, -10, 20);
    h2pfRawMetResol         [i] = new TH2F("h2pfRawMetResol"          + sLevel[i], "", 50, 0, 120, -10, 20);
    h2puppiMetResol         [i] = new TH2F("h2puppiMetResol"          + sLevel[i], "", 50, 0, 120, -10, 20);
    h2trkMetResol           [i] = new TH2F("h2trkMetResol"            + sLevel[i], "", 50, 0, 120, -10, 20);
    h2ppfType1MetResol      [i] = new TH2F("h2ppfType1MetResol"       + sLevel[i], "", 50, 0, 120, -10, 20);
  }

  // Data-driven methods: Top
  //----------------------------------------------------------------------------
  //TH1F* hTopTaggedEvents            = new TH1F("hTopTaggedEvents",            "", 3, 0, 3);

  //----------------------------------------------------------------------------
  // Input files
  //----------------------------------------------------------------------------
  TString filesPath = "/d3/scratch/khakim/RunII/LatinosTrees/";
  //TString filesPath = "/d3/scratch/khakim/RunII/LatinosTrees/";

  TChain* tree = new TChain("latino", "latino");

  if(theSample == "ggWWto2L"){
    //tree->Add(filesPath + "ggHww_PU20bx25_V2/latino_stepB_MC_ggHww_1.root");
    //tree->Add(filesPath + "ggHww_PU20bx25_V2/latino_stepB_MC_ggHww_2.root");
    //tree->Add(filesPath + "ggHww_PU20bx25_V2/latino_stepB_MC_ggHww_3.root");
    //tree->Add(filesPath + "ggHww_PU20bx25_V2/latino_stepB_MC_ggHww_4.root");
    tree->Add("/u/user/khakim/HWWwidth/RunII/CMSSW_7_4_4/src/LatinoTrees/AnalysisStep/test/latino_stepB_MC_numEvent10.root");
  }
  else if(theSample == "WWTo2L2Nu"){
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_1.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_10.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_11.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_12.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_14.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_15.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_17.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_18.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_19.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_20.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_7.root");
    tree->Add(filesPath + "WW_PU20bx25_V2/latino_stepB_MC_WW_9.root");
  }
  else if(theSample == "WWTo2L2Nu50ns"){
    tree->Add("/u/user/salee/Latino/CMSSW_7_4_4/src/LatinoTrees/AnalysisStep/test/latino_stepB_latinosYieldSkim_MC_WWTo2L2Nu50ns_wPUPPI_numEvent200.root");
  }
  else{
    return;
  }

  // Declaration of leaf types
  //----------------------------------------------------------------------------
  tree->SetBranchAddress("channel",         &channel);
  tree->SetBranchAddress("ch1",             &ch1);
  tree->SetBranchAddress("ch2",             &ch2);
  tree->SetBranchAddress("njet",            &njet);
  tree->SetBranchAddress("mll",             &mll);
  tree->SetBranchAddress("pt1",             &pt1);
  tree->SetBranchAddress("pt2",             &pt2);
  tree->SetBranchAddress("metGenpt",        &metGenpt);
  tree->SetBranchAddress("pfType1Met",      &pfType1Met);
  tree->SetBranchAddress("pfType1Metdn",    &pfType1Metdn);
  tree->SetBranchAddress("pfType1Metup",    &pfType1Metup);
  tree->SetBranchAddress("pfRawMet",        &pfRawMet);
  tree->SetBranchAddress("pupMet",          &pupMet);
  tree->SetBranchAddress("trkMet",          &trkMet);
  tree->SetBranchAddress("ppfMet",          &ppfMet);
  tree->SetBranchAddress("neutrinoGenpid1", &neutrinoGenpid1);
  tree->SetBranchAddress("neutrinoGenpid2", &neutrinoGenpid2);
  tree->SetBranchAddress("neutrinoGenpid3", &neutrinoGenpid3);
  tree->SetBranchAddress("event",           &event);
  tree->SetBranchAddress("std_vector_leptonGen_pid",    &std_vector_leptonGen_pid);
  tree->SetBranchAddress("std_vector_leptonGen_status", &std_vector_leptonGen_status);
  tree->SetBranchAddress("std_vector_leptonGen_pt",     &std_vector_leptonGen_pt);
  tree->SetBranchAddress("std_vector_leptonGen_mpid",   &std_vector_leptonGen_mpid);
  tree->SetBranchAddress("std_vector_leptonGen_mstatus",&std_vector_leptonGen_mstatus);

  //----------------------------------------------------------------------------
  // Loop
  //----------------------------------------------------------------------------
  //for (int ievent=0; ievent<tree->GetEntries(); ievent++)
  for (int ievent=0; ievent<3; ievent++)
  {
    tree->GetEntry(ievent);

    printf("=============== Event %d ===============\n",event);
    printf("Index\tPID\tStatus\t\tmPID\tmStatus\tpT\n");
    printf("==========================================\n");
    for (UInt_t igen=0; igen<std_vector_leptonGen_pt->size(); igen++){
      printf("%d\t%.f\t%.f\t\t%.f\t%.f\t%.3f\n",
	  igen,
	  (*std_vector_leptonGen_pid)[igen],(*std_vector_leptonGen_status)[igen],
	  (*std_vector_leptonGen_mpid)[igen],(*std_vector_leptonGen_mstatus)[igen],
	  (*std_vector_leptonGen_pt)[igen]);
    }
    evtWeight = 1.0;

    if (theSample.Contains("ggWWto2L"))
    {
      evtWeight = 1.0;
    }
    else if (theSample.Contains("WWTo2L2Nu"))
    {
      evtWeight = 1.0;
    }

    // Help variables
    //--------------------------------------------------------------------------
    Int_t fidCut = ((ch1*ch2 ==-1.) && (mll>12.) && (pt1>20 && pt2>10));

    Float_t jetbin = njet;
    if(njet >= 2) jetbin = 2;

    if(!fidCut) continue;

    // Set the channel (decay, jet and channel)
    Int_t tauDecay = 0;
    for (UInt_t igen=0; igen<std_vector_leptonGen_mpid->size(); igen++){
      //printf("GenLvlInfo:\t%d\t%.f\t%.f\n", igen,(*std_vector_leptonGen_pid)[igen],(*std_vector_leptonGen_status)[igen]);
      if(fabs((*std_vector_leptonGen_mpid)[igen]) == 15) tauDecay = 1; 
    }

    //printf("Mother Info:\t%d\t%d\n", ievent,tauDecay);

    Int_t tauDecay_0jet = (tauDecay && jetbin == 0);
    Int_t tauDecay_1jet = (tauDecay && jetbin == 1);
    Int_t tauDecay_2jet = (tauDecay && jetbin == 2);

    Int_t emuDecay_0jet = (!tauDecay && jetbin == 0);
    Int_t emuDecay_1jet = (!tauDecay && jetbin == 1);
    Int_t emuDecay_2jet = (!tauDecay && jetbin == 2);

    Int_t emuDecay_SF = (!tauDecay && (channel == 0 || channel == 1));
    Int_t emuDecay_0jet_SF = (!tauDecay && jetbin == 0 && (channel == 0 || channel == 1));
    Int_t emuDecay_1jet_SF = (!tauDecay && jetbin == 1 && (channel == 0 || channel == 1));
    Int_t emuDecay_2jet_SF = (!tauDecay && jetbin == 2 && (channel == 0 || channel == 1));

    Int_t emuDecay_OF = (!tauDecay && (channel == 2 || channel == 3));
    Int_t emuDecay_0jet_OF = (!tauDecay && jetbin == 0 && (channel == 2 || channel == 3));
    Int_t emuDecay_1jet_OF = (!tauDecay && jetbin == 1 && (channel == 2 || channel == 3));
    Int_t emuDecay_2jet_OF = (!tauDecay && jetbin == 2 && (channel == 2 || channel == 3));

    //--------------------------------------------------------------------------

    //printf("\n%d\t\t%.0f\t%.0f\t%.0f\t%f\t%d\n", ievent,pt1,pt2,mll,channel,fidCut);
    for (UInt_t ilevel=0; ilevel<nLevels; ilevel++){
      if(ilevel == Level_InclJet)                         FillHistograms(Level_InclJet, jetbin);
      if(ilevel == Level_InclJet_emu && !tauDecay)        FillHistograms(Level_InclJet_emu, jetbin);
      if(ilevel == Level_InclJet_emu_SF && emuDecay_SF)   FillHistograms(Level_InclJet_emu_SF, jetbin);
      if(ilevel == Level_InclJet_emu_OF && emuDecay_OF)   FillHistograms(Level_InclJet_emu_OF, jetbin);
      if(ilevel == Level_InclJet_tau && tauDecay)         FillHistograms(Level_InclJet_tau, jetbin);
      if(ilevel == Level_0Jet && jetbin == 0)             FillHistograms(Level_0Jet, jetbin);
      if(ilevel == Level_0Jet_emu && emuDecay_0jet)       FillHistograms(Level_0Jet_emu, jetbin);
      if(ilevel == Level_0Jet_emu_SF && emuDecay_0jet_SF) FillHistograms(Level_0Jet_emu_SF, jetbin);
      if(ilevel == Level_0Jet_emu_OF && emuDecay_0jet_OF) FillHistograms(Level_0Jet_emu_OF, jetbin);
      if(ilevel == Level_0Jet_tau && tauDecay_0jet)       FillHistograms(Level_0Jet_tau, jetbin);
      if(ilevel == Level_1Jet && jetbin == 1)             FillHistograms(Level_1Jet, jetbin);
      if(ilevel == Level_1Jet_emu && emuDecay_1jet)       FillHistograms(Level_1Jet_emu, jetbin);
      if(ilevel == Level_1Jet_emu_SF && emuDecay_1jet_SF) FillHistograms(Level_1Jet_emu_SF, jetbin);
      if(ilevel == Level_1Jet_emu_OF && emuDecay_1jet_OF) FillHistograms(Level_1Jet_emu_OF, jetbin);
      if(ilevel == Level_1Jet_tau && tauDecay_1jet)       FillHistograms(Level_1Jet_tau, jetbin);
      if(ilevel == Level_2Jet && jetbin == 2)             FillHistograms(Level_2Jet, jetbin);
      if(ilevel == Level_2Jet_emu && emuDecay_2jet)       FillHistograms(Level_2Jet_emu, jetbin);
      if(ilevel == Level_2Jet_emu_SF && emuDecay_2jet_SF) FillHistograms(Level_2Jet_emu_SF, jetbin);
      if(ilevel == Level_2Jet_emu_OF && emuDecay_2jet_OF) FillHistograms(Level_2Jet_emu_OF, jetbin);
      if(ilevel == Level_2Jet_tau && tauDecay_2jet)       FillHistograms(Level_2Jet_tau, jetbin);
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  }

    // Save the histograms
    //----------------------------------------------------------------------------
    output->cd();
    output->Write("", TObject::kOverwrite);
    output->Close();
  }

  //------------------------------------------------------------------------------
  // FillHistograms
  //------------------------------------------------------------------------------
  void FillHistograms(UInt_t level, UInt_t jets)
  {
    h1genMet       [level]->Fill(metGenpt,     evtWeight);
    h1pfType1Met   [level]->Fill(pfType1Met,   evtWeight);
    h1pfRawMet     [level]->Fill(pfRawMet,     evtWeight);
    h1puppiMet     [level]->Fill(pupMet,       evtWeight);
    h1trkMet       [level]->Fill(trkMet,       evtWeight);
    h1ppfType1Met  [level]->Fill(ppfMet,       evtWeight);
    h1pfType1Metdn [level]->Fill(pfType1Metdn, evtWeight);
    h1pfType1Metup [level]->Fill(pfType1Metup, evtWeight);

    h2pfType1MetResol  [level]->Fill(metGenpt, (pfType1Met-metGenpt)/metGenpt, evtWeight);
    h2pfRawMetResol    [level]->Fill(metGenpt, (pfRawMet-metGenpt)/metGenpt,   evtWeight);
    h2puppiMetResol    [level]->Fill(metGenpt, (pupMet-metGenpt)/metGenpt,     evtWeight);
    h2trkMetResol      [level]->Fill(metGenpt, (trkMet-metGenpt)/metGenpt,     evtWeight);
    h2ppfType1MetResol [level]->Fill(metGenpt, (ppfMet-metGenpt)/metGenpt,     evtWeight);
  }
