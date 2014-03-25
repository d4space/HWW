#include <iostream>
#include "../include/TreeHw25RoScGeCut/SetupTreeHw25RoScGeCut.h" 
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

  TString Mode = "CtrPlt";

  gSystem->Load("../ExRootAnalysis/lib/libExRootAnalysis.so");
  gSystem->CompileMacro("../src/GGVvNT.C","k");
  gSystem->CompileMacro("../src/GGVvBase.C","k");
  gSystem->CompileMacro("../src/GGVvTemplate.C","k");

  double LumiWeight = 1;

  cout<<"TreeHw25RoScGeCut============================"<<endl;
  TChain *Ch_SigHw25RoScGeCut     = new TChain("LHEF","");
  SetupTreeHw25RoScGeCut("SigHw25RoScGeCut",Ch_SigHw25RoScGeCut);
  TString DirName = "SigHw25RoScGeCut";
  GGVvTemplate SigHw25RoScGeCutBeatles(Ch_SigHw25RoScGeCut,DirName,Mode);
  SigHw25RoScGeCutBeatles.Loop();
}
