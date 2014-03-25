#include <iostream>
#include "../include/TreeHw25RoScGeCut/SetupTree.h" 
using namespace std;
//#define	RealLumi	(19619) //pb
//#define	RealLumi	(890.608) //pb
//#define	RealLumi	(4429) //pb
//#define	RealLumi	(7026.245) //pb
#define	RealLumi	(7274) //pb
void MakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Resolution";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

TString Mode = "MET";//Analysis,Recoil, RecoilMC, RecoilCorr, Resolution,
TString AnaChannelEle = "Electron2012";//ElectronLowPU
TString AnaChannelMu  = "Muon2012";
TString AnaChannelTau  = "Tau2012";

  gSystem->Load("../ExRootAnalysis/lib/libExRootAnalysis.so");
  gSystem->CompileMacro("../src/GGVvNT.C","k");
  gSystem->CompileMacro("../src/GGVvBase.C","k");
  gSystem->CompileMacro("../src/GGVvTemplate.C","k");

  double LumiWeight = 1;

  cout<<"TreeHw25RoScGeCut============================"<<endl;
  TChain *Ch_SigHw25RoScGeCut     = new TChain("LHEF","");
  SetupTreeHw25RoScGeCut("SigHw25RoScGeCut",Ch_SigHw25RoScGeCut);
  TString DirName = "TTsemiMuon";
  TTsemiMET TTsemiMET_Mu(TC_TTsemi_S10,TC_TTsemi_Muon,
        LumiWeight, DirName, Mode, AnaChannelMu, 0, true, -999);
  TTsemiMET_Mu.Loop();
}
