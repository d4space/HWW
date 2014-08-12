#include <iostream>
#include "../include/TreeHWWgg2vv8TeV/SetupTreeHWWgg2vv8TeV.h" 
using namespace std;
void MakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================

  TString Mode = "CtrPlt";
  double LumiWeight = 1;

  gSystem->Load("../ExRootAnalysis/lib/libExRootAnalysis.so");
  gSystem->CompileMacro("../src/GGVvNT.C","k");
  gSystem->CompileMacro("../src/GGVvBase.C","k");
  gSystem->CompileMacro("../src/GGVvNEvents.C","k");

  cout<<"TreeHw1Sig8TeV============================"<<endl;
  TChain *Ch_Hw1Sig8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Sig8TeV",Ch_Hw1Sig8TeV);
  TString DirName = "Hw1Sig8TeV";
  GGVvNEvents Hw1Sig8TeVCutBeatles(Ch_Hw1Sig8TeV,DirName,Mode,LumiWeight);
  Hw1Sig8TeVCutBeatles.Loop();

  cout<<"TreeHw1Int8TeV============================"<<endl;
  TChain *Ch_Hw1Int8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Int8TeV",Ch_Hw1Int8TeV);
  TString DirName = "Hw1Int8TeV";
  GGVvNEvents Hw1Int8TeVCutBeatles(Ch_Hw1Int8TeV,DirName,Mode,LumiWeight);
  Hw1Int8TeVCutBeatles.Loop();

  cout<<"TreeHw1Cot8TeV============================"<<endl;
  TChain *Ch_Hw1Cot8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Cot8TeV",Ch_Hw1Cot8TeV);
  TString DirName = "Hw1Cot8TeV";
  GGVvNEvents Hw1Cot8TeVCutBeatles(Ch_Hw1Cot8TeV,DirName,Mode,LumiWeight);
  Hw1Cot8TeVCutBeatles.Loop();

  cout<<"TreeHw25Sig8TeV============================"<<endl;
  TChain *Ch_Hw25Sig8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Sig8TeV",Ch_Hw25Sig8TeV);
  TString DirName = "Hw25Sig8TeV";
  GGVvNEvents Hw25Sig8TeVCutBeatles(Ch_Hw25Sig8TeV,DirName,Mode,LumiWeight);
  Hw25Sig8TeVCutBeatles.Loop();

  cout<<"TreeHw25Int8TeV============================"<<endl;
  TChain *Ch_Hw25Int8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Int8TeV",Ch_Hw25Int8TeV);
  TString DirName = "Hw25Int8TeV";
  GGVvNEvents Hw25Int8TeVCutBeatles(Ch_Hw25Int8TeV,DirName,Mode,LumiWeight);
  Hw25Int8TeVCutBeatles.Loop();

  cout<<"TreeHw25Cot8TeV============================"<<endl;
  TChain *Ch_Hw25Cot8TeV     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Cot8TeV",Ch_Hw25Cot8TeV);
  TString DirName = "Hw25Cot8TeV";
  GGVvNEvents Hw25Cot8TeVCutBeatles(Ch_Hw25Cot8TeV,DirName,Mode,LumiWeight);
  Hw25Cot8TeVCutBeatles.Loop();

  cout<<"TreeHw1Sig8TeVOnPeak============================"<<endl;
  TChain *Ch_Hw1Sig8TeVOnPeak     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Sig8TeVOnPeak",Ch_Hw1Sig8TeVOnPeak);
  TString DirName = "Hw1Sig8TeVOnPeak";
  GGVvNEvents Hw1Sig8TeVCutBeatlesOnPeak(Ch_Hw1Sig8TeVOnPeak,DirName,Mode,LumiWeight);
  Hw1Sig8TeVCutBeatlesOnPeak.Loop();

  cout<<"TreeHw1Sig8TeVShoulder============================"<<endl;
  TChain *Ch_Hw1Sig8TeVShoulder     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Sig8TeVShoulder",Ch_Hw1Sig8TeVShoulder);
  TString DirName = "Hw1Sig8TeVShoulder";
  GGVvNEvents Hw1Sig8TeVCutBeatlesShoulder(Ch_Hw1Sig8TeVShoulder,DirName,Mode,LumiWeight);
  Hw1Sig8TeVCutBeatlesShoulder.Loop();

  cout<<"TreeHw1Sig8TeVTail============================"<<endl;
  TChain *Ch_Hw1Sig8TeVTail     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Sig8TeVTail",Ch_Hw1Sig8TeVTail);
  TString DirName = "Hw1Sig8TeVTail";
  GGVvNEvents Hw1Sig8TeVCutBeatlesTail(Ch_Hw1Sig8TeVTail,DirName,Mode,LumiWeight);
  Hw1Sig8TeVCutBeatlesTail.Loop();
 
  cout<<"TreeHw1Int8TeVOnPeak============================"<<endl;
  TChain *Ch_Hw1Int8TeVOnPeak     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Int8TeVOnPeak",Ch_Hw1Int8TeVOnPeak);
  TString DirName = "Hw1Int8TeVOnPeak";
  GGVvNEvents Hw1Int8TeVCutBeatlesOnPeak(Ch_Hw1Int8TeVOnPeak,DirName,Mode,LumiWeight);
  Hw1Int8TeVCutBeatlesOnPeak.Loop();

  cout<<"TreeHw1Int8TeVShoulder============================"<<endl;
  TChain *Ch_Hw1Int8TeVShoulder     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Int8TeVShoulder",Ch_Hw1Int8TeVShoulder);
  TString DirName = "Hw1Int8TeVShoulder";
  GGVvNEvents Hw1Int8TeVCutBeatlesShoulder(Ch_Hw1Int8TeVShoulder,DirName,Mode,LumiWeight);
  Hw1Int8TeVCutBeatlesShoulder.Loop();

  cout<<"TreeHw1Int8TeVTail============================"<<endl;
  TChain *Ch_Hw1Int8TeVTail     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw1Int8TeVTail",Ch_Hw1Int8TeVTail);
  TString DirName = "Hw1Int8TeVTail";
  GGVvNEvents Hw1Int8TeVCutBeatlesTail(Ch_Hw1Int8TeVTail,DirName,Mode,LumiWeight);
  Hw1Int8TeVCutBeatlesTail.Loop();

  cout<<"TreeHw25Sig8TeVOnPeak============================"<<endl;
  TChain *Ch_Hw25Sig8TeVOnPeak     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Sig8TeVOnPeak",Ch_Hw25Sig8TeVOnPeak);
  TString DirName = "Hw25Sig8TeVOnPeak";
  GGVvNEvents Hw25Sig8TeVCutBeatlesOnPeak(Ch_Hw25Sig8TeVOnPeak,DirName,Mode,LumiWeight);
  Hw25Sig8TeVCutBeatlesOnPeak.Loop();

  cout<<"TreeHw25Sig8TeVShoulder============================"<<endl;
  TChain *Ch_Hw25Sig8TeVShoulder     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Sig8TeVShoulder",Ch_Hw25Sig8TeVShoulder);
  TString DirName = "Hw25Sig8TeVShoulder";
  GGVvNEvents Hw25Sig8TeVCutBeatlesShoulder(Ch_Hw25Sig8TeVShoulder,DirName,Mode,LumiWeight);
  Hw25Sig8TeVCutBeatlesShoulder.Loop();

  cout<<"TreeHw25Sig8TeVTail============================"<<endl;
  TChain *Ch_Hw25Sig8TeVTail     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Sig8TeVTail",Ch_Hw25Sig8TeVTail);
  TString DirName = "Hw25Sig8TeVTail";
  GGVvNEvents Hw25Sig8TeVCutBeatlesTail(Ch_Hw25Sig8TeVTail,DirName,Mode,LumiWeight);
  Hw25Sig8TeVCutBeatlesTail.Loop();

  cout<<"TreeHw25Int8TeVOnPeak============================"<<endl;
  TChain *Ch_Hw25Int8TeVOnPeak     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Int8TeVOnPeak",Ch_Hw25Int8TeVOnPeak);
  TString DirName = "Hw25Int8TeVOnPeak";
  GGVvNEvents Hw25Int8TeVCutBeatlesOnPeak(Ch_Hw25Int8TeVOnPeak,DirName,Mode,LumiWeight);
  Hw25Int8TeVCutBeatlesOnPeak.Loop();

  cout<<"TreeHw25Int8TeVShoulder============================"<<endl;
  TChain *Ch_Hw25Int8TeVShoulder     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Int8TeVShoulder",Ch_Hw25Int8TeVShoulder);
  TString DirName = "Hw25Int8TeVShoulder";
  GGVvNEvents Hw25Int8TeVCutBeatlesShoulder(Ch_Hw25Int8TeVShoulder,DirName,Mode,LumiWeight);
  Hw25Int8TeVCutBeatlesShoulder.Loop();

  cout<<"TreeHw25Int8TeVTail============================"<<endl;
  TChain *Ch_Hw25Int8TeVTail     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Int8TeVTail",Ch_Hw25Int8TeVTail);
  TString DirName = "Hw25Int8TeVTail";
  GGVvNEvents Hw25Int8TeVCutBeatlesTail(Ch_Hw25Int8TeVTail,DirName,Mode,LumiWeight);
  Hw25Int8TeVCutBeatlesTail.Loop();

  cout<<"TreeHw25Cot8TeVHead============================"<<endl;
  TChain *Ch_Hw25Cot8TeVHead     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Cot8TeVHead",Ch_Hw25Cot8TeVHead);
  TString DirName = "Hw25Cot8TeVHead";
  GGVvNEvents Hw25Cot8TeVCutBeatlesHead(Ch_Hw25Cot8TeVHead,DirName,Mode,LumiWeight);
  Hw25Cot8TeVCutBeatlesHead.Loop();

  cout<<"TreeHw25Cot8TeVTail============================"<<endl;
  TChain *Ch_Hw25Cot8TeVTail     = new TChain("LHEF","");
  SetupTreeHWWgg2vv8TeV("Hw25Cot8TeVTail",Ch_Hw25Cot8TeVTail);
  TString DirName = "Hw25Cot8TeVTail";
  GGVvNEvents Hw25Cot8TeVCutBeatlesTail(Ch_Hw25Cot8TeVTail,DirName,Mode,LumiWeight);
  Hw25Cot8TeVCutBeatlesTail.Loop();
}
