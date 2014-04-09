#include <iostream>
#include "../include/TreeHw25RoScMiCut/SetupTreeHw25RoScMiCut.h" 
//#include "../include/TreeHw25RoScGeCut/SetupTreeHw25RoScGeCut.h" 
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
  gSystem->CompileMacro("../src/GGVvCtrPlt.C","k");

  double LumiWeight = 1;

  cout<<"TreeHw25RoScMiCut============================"<<endl;
  TChain *Ch_SigHw25RoScMiCut     = new TChain("LHEF","");
  SetupTreeHw25RoScMiCut("SigHw25RoScMiCut",Ch_SigHw25RoScMiCut);
  TString DirName = "SigHw25RoScMiCut";
  GGVvCtrPlt SigHw25RoScMiCutBeatles(Ch_SigHw25RoScMiCut,DirName,Mode);
  SigHw25RoScMiCutBeatles.Loop();

  cout<<"TreeHw25RoScMiCut============================"<<endl;
  TChain *Ch_ContHw25RoScMiCut     = new TChain("LHEF","");
  SetupTreeHw25RoScMiCut("ContHw25RoScMiCut",Ch_ContHw25RoScMiCut);
  TString DirName = "CotHw25RoScMiCut";
  GGVvCtrPlt ContHw25RoScMiCutBeatles(Ch_ContHw25RoScMiCut,DirName,Mode);
  ContHw25RoScMiCutBeatles.Loop();

  cout<<"TreeHw25RoScMiCut============================"<<endl;
  TChain *Ch_IntHw25RoScMiCut     = new TChain("LHEF","");
  SetupTreeHw25RoScMiCut("IntHw25RoScMiCut",Ch_IntHw25RoScMiCut);
  TString DirName = "IntHw25RoScMiCut";
  GGVvCtrPlt IntHw25RoScMiCutBeatles(Ch_IntHw25RoScMiCut,DirName,Mode);
  IntHw25RoScMiCutBeatles.Loop();
}
