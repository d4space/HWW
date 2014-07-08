#include <iostream>
#include "../include/TreeHw1gg2vv8TeV/SetupTreeHw1gg2vv8TeV.h" 
using namespace std;
void MakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================

  TString Mode = "CtrPlt";
  //double LumiWeight = 19.468*17.9978/(160*25000);
  double LumiWeight = 1;

  gSystem->Load("../ExRootAnalysis/lib/libExRootAnalysis.so");
  gSystem->CompileMacro("../src/GGVvNT.C","k");
  gSystem->CompileMacro("../src/GGVvBase.C","k");
  gSystem->CompileMacro("../src/GGVvCtrPlt.C","k");

  cout<<"TreeHw1Sig8TeV============================"<<endl;
  TChain *Ch_Hw1Sig8TeV     = new TChain("LHEF","");
  SetupTreeHw1gg2vv8TeV("Hw1Sig8TeV",Ch_Hw1Sig8TeV);
  TString DirName = "Hw1Sig8TeV";
  GGVvCtrPlt Hw1Sig8TeVCutBeatles(Ch_Hw1Sig8TeV,DirName,Mode,LumiWeight);
  Hw1Sig8TeVCutBeatles.Loop();

  cout<<"TreeHw1Int8TeV============================"<<endl;
  TChain *Ch_Hw1Int8TeV     = new TChain("LHEF","");
  SetupTreeHw1gg2vv8TeV("Hw1Int8TeV",Ch_Hw1Int8TeV);
  TString DirName = "Hw1Int8TeV";
  GGVvCtrPlt Hw1Int8TeVCutBeatles(Ch_Hw1Int8TeV,DirName,Mode,LumiWeight);
  Hw1Int8TeVCutBeatles.Loop();

  cout<<"TreeHw1Cot8TeV============================"<<endl;
  TChain *Ch_Hw1Cot8TeV     = new TChain("LHEF","");
  SetupTreeHw1gg2vv8TeV("Hw1Cot8TeV",Ch_Hw1Cot8TeV);
  TString DirName = "Hw1Cot8TeV";
  GGVvCtrPlt Hw1Cot8TeVCutBeatles(Ch_Hw1Cot8TeV,DirName,Mode,LumiWeight);
  Hw1Cot8TeVCutBeatles.Loop();
}
