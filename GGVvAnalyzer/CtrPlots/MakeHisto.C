#include <iostream>
//#include "../include/TreeHw1RoScMiCut/SetupTreeHw1RoScMiCut.h" 
#include "../include/TreeHw1SigFull8TeV/SetupTreeHw1SigFull8TeV.h" 
//#include "../include/TreeHw25RoScGeCut/SetupTreeHw25RoScGeCut.h" 
using namespace std;
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

  cout<<"TreeHw1SigFull8TeV============================"<<endl;
  TChain *Ch_SigHw1Full8TeV     = new TChain("LHEF","");
  SetupTreeHw1SigFull8TeV("SigHw1Full8TeV",Ch_SigHw1Full8TeV);
  TString DirName = "SigHw1Full8TeV";
  GGVvCtrPlt SigHw1Full8TeVCutBeatles(Ch_SigHw1Full8TeV,DirName,Mode);
  SigHw1Full8TeVCutBeatles.Loop();

  //cout<<"TreeHw1RoScMiCut============================"<<endl;
  //TChain *Ch_SigHw1RoScMiCut     = new TChain("LHEF","");
  //SetupTreeHw1RoScMiCut("SigHw1RoScMiCut",Ch_SigHw1RoScMiCut);
  //TString DirName = "SigHw1RoScMiCut";
  //GGVvCtrPlt SigHw1RoScMiCutBeatles(Ch_SigHw1RoScMiCut,DirName,Mode);
  //SigHw1RoScMiCutBeatles.Loop();

  //cout<<"TreeHw1RoScMiCut============================"<<endl;
  //TChain *Ch_CotHw1RoScMiCut     = new TChain("LHEF","");
  //SetupTreeHw1RoScMiCut("CotHw1RoScMiCut",Ch_CotHw1RoScMiCut);
  //TString DirName = "CotHw1RoScMiCut";
  //GGVvCtrPlt CotHw1RoScMiCutBeatles(Ch_CotHw1RoScMiCut,DirName,Mode);
  //CotHw1RoScMiCutBeatles.Loop();

  //cout<<"TreeHw1RoScMiCut============================"<<endl;
  //TChain *Ch_IntHw1RoScMiCut     = new TChain("LHEF","");
  //SetupTreeHw1RoScMiCut("IntHw1RoScMiCut",Ch_IntHw1RoScMiCut);
  //TString DirName = "IntHw1RoScMiCut";
  //GGVvCtrPlt IntHw1RoScMiCutBeatles(Ch_IntHw1RoScMiCut,DirName,Mode);
  //IntHw1RoScMiCutBeatles.Loop();
}
