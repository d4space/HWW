#include <iostream>
#include "../include/TreeHWWgg2vv8TeV/SetupTreeHWWgg2vv8TeV.h" 
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
  SetupTreeHWWgg2vv8TeV("Hw1Sig8TeV",Ch_Hw1Sig8TeV);
  TString DirName = "Hw1Sig8TeV";
  GGVvCtrPlt Hw1Sig8TeVCutBeatles(Ch_Hw1Sig8TeV,DirName,Mode,LumiWeight);
  Hw1Sig8TeVCutBeatles.Loop();

  cout<<"TreeHw1Int8TeV============================"<<endl;
  TChain *Ch_Hw1Int8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Int8TeV",Ch_Hw1Int8TeV);
  TString DirName = "Hw1Int8TeV";
  GGVvCtrPlt Hw1Int8TeVCutBeatles(Ch_Hw1Int8TeV,DirName,Mode,LumiWeight);
  Hw1Int8TeVCutBeatles.Loop();

  cout<<"TreeHw1Cot8TeV============================"<<endl;
  TChain *Ch_Hw1Cot8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Cot8TeV",Ch_Hw1Cot8TeV);
  TString DirName = "Hw1Cot8TeV";
  GGVvCtrPlt Hw1Cot8TeVCutBeatles(Ch_Hw1Cot8TeV,DirName,Mode,LumiWeight);
  Hw1Cot8TeVCutBeatles.Loop();

  cout<<"TreeHw25Sig8TeV============================"<<endl;
  TChain *Ch_Hw25Sig8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Sig8TeV",Ch_Hw25Sig8TeV);
  TString DirName = "Hw25Sig8TeV";
  GGVvCtrPlt Hw25Sig8TeVCutBeatles(Ch_Hw25Sig8TeV,DirName,Mode,LumiWeight);
  Hw25Sig8TeVCutBeatles.Loop();

  cout<<"TreeHw25Int8TeV============================"<<endl;
  TChain *Ch_Hw25Int8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Int8TeV",Ch_Hw25Int8TeV);
  TString DirName = "Hw25Int8TeV";
  GGVvCtrPlt Hw25Int8TeVCutBeatles(Ch_Hw25Int8TeV,DirName,Mode,LumiWeight);
  Hw25Int8TeVCutBeatles.Loop();

  cout<<"TreeHw25Cot8TeV============================"<<endl;
  TChain *Ch_Hw25Cot8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Cot8TeV",Ch_Hw25Cot8TeV);
  TString DirName = "Hw25Cot8TeV";
  GGVvCtrPlt Hw25Cot8TeVCutBeatles(Ch_Hw25Cot8TeV,DirName,Mode,LumiWeight);
  Hw25Cot8TeVCutBeatles.Loop();
  
  cout<<"TreeHw25Sig8TeVOnPeak============================"<<endl;
  TChain *Ch_Hw25Sig8TeVOnPeak     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Sig8TeVOnPeak",Ch_Hw25Sig8TeVOnPeak);
  TString DirName = "Hw25Sig8TeVOnPeak";
  GGVvCtrPlt Hw25Sig8TeVCutBeatlesOnPeak(Ch_Hw25Sig8TeVOnPeak,DirName,Mode,LumiWeight);
  Hw25Sig8TeVCutBeatlesOnPeak.Loop();
  
  cout<<"TreeHw25Sig8TeVShoulder============================"<<endl;
  TChain *Ch_Hw25Sig8TeVShoulder     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Sig8TeVShoulder",Ch_Hw25Sig8TeVShoulder);
  TString DirName = "Hw25Sig8TeVShoulder";
  GGVvCtrPlt Hw25Sig8TeVCutBeatlesShoulder(Ch_Hw25Sig8TeVShoulder,DirName,Mode,LumiWeight);
  Hw25Sig8TeVCutBeatlesShoulder.Loop();
  
  cout<<"TreeHw25Sig8TeVTail============================"<<endl;
  TChain *Ch_Hw25Sig8TeVTail     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Sig8TeVTail",Ch_Hw25Sig8TeVTail);
  TString DirName = "Hw25Sig8TeVTail";
  GGVvCtrPlt Hw25Sig8TeVCutBeatlesTail(Ch_Hw25Sig8TeVTail,DirName,Mode,LumiWeight);
  Hw25Sig8TeVCutBeatlesTail.Loop();
}
