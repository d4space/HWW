#include <iostream>
#include "../include/SetupTree.h"
#include "../../../Utils/const.h"

using namespace std;
void MakeHistoCtrPlots()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
  gSystem->CompileMacro("../src/HWwNT.C","k");
  gSystem->CompileMacro("../src/HWwBase.C","k");
  gSystem->CompileMacro("../src/HWwNEvents.C","k");

  //TString Cut = "Loose"; // Loose, Tight
  //TString Cut = "Tight"; // Loose, Tight
  string Cuts[]={"NoCut","LooseCut","CommonCut"}; // Loose, Tight
  //string Cuts[]={"LooseCut"}; // Loose, Tight
  //string Cuts[]={"CommonCut"}; // Loose, Tight
  TString SampleName = "Data";
  // BaseName : Data, WJet, WW, Top, VVV, H125, DYll, DYtt, VV
  bool RunOnMC = false;

for( int i(0); i < sizeof(Cuts)/sizeof(*Cuts);++i){
  cout<<"Cut is "<<Cuts[i]<<endl;

//gg2vvHw1SigOnPeak========================================
  cout<<"gg2vvHw1SigOnPeak===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1SigOnPeak  = new TChain("latino","");
  SetupTree("gg2vvHw1SigOnPeak",TC_gg2vvHw1SigOnPeak);
  SampleName = "gg2vvHw1SigOnPeak";
  HWwNEvents HWwNEventsgg2vvHw1SigOnPeak(TC_gg2vvHw1SigOnPeak,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw1SigOnPeak.Loop();

//gg2vvHw1SigShoulder========================================
  cout<<"gg2vvHw1SigShoulder===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1SigShoulder  = new TChain("latino","");
  SetupTree("gg2vvHw1SigShoulder",TC_gg2vvHw1SigShoulder);
  SampleName = "gg2vvHw1SigShoulder";
  HWwNEvents HWwNEventsgg2vvHw1SigShoulder(TC_gg2vvHw1SigShoulder,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw1SigShoulder.Loop();

//gg2vvHw1SigTail========================================
  cout<<"gg2vvHw1SigTail===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1SigTail  = new TChain("latino","");
  SetupTree("gg2vvHw1SigTail",TC_gg2vvHw1SigTail);
  SampleName = "gg2vvHw1SigTail";
  HWwNEvents HWwNEventsgg2vvHw1SigTail(TC_gg2vvHw1SigTail,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw1SigTail.Loop();

//gg2vvHw1IntOnPeak========================================
  cout<<"gg2vvHw1IntOnPeak===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1IntOnPeak  = new TChain("latino","");
  SetupTree("gg2vvHw1IntOnPeak",TC_gg2vvHw1IntOnPeak);
  SampleName = "gg2vvHw1IntOnPeak";
  HWwNEvents HWwNEventsgg2vvHw1IntOnPeak(TC_gg2vvHw1IntOnPeak,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw1IntOnPeak.Loop();

//gg2vvHw1IntShoulder========================================
  cout<<"gg2vvHw1IntShoulder===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1IntShoulder  = new TChain("latino","");
  SetupTree("gg2vvHw1IntShoulder",TC_gg2vvHw1IntShoulder);
  SampleName = "gg2vvHw1IntShoulder";
  HWwNEvents HWwNEventsgg2vvHw1IntShoulder(TC_gg2vvHw1IntShoulder,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw1IntShoulder.Loop();

//gg2vvHw1IntTail========================================
  cout<<"gg2vvHw1IntTail===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1IntTail  = new TChain("latino","");
  SetupTree("gg2vvHw1IntTail",TC_gg2vvHw1IntTail);
  SampleName = "gg2vvHw1IntTail";
  HWwNEvents HWwNEventsgg2vvHw1IntTail(TC_gg2vvHw1IntTail,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw1IntTail.Loop();

//gg2vvHw25CotHead========================================
  cout<<"gg2vvHw25CotHead===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw25CotHead  = new TChain("latino","");
  SetupTree("gg2vvHw25CotHead",TC_gg2vvHw25CotHead);
  SampleName = "gg2vvHw25CotHead";
  HWwNEvents HWwNEventsgg2vvHw25CotHead(TC_gg2vvHw25CotHead,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw25CotHead.Loop();

//gg2vvHw25CotTail========================================
  cout<<"gg2vvHw25CotTail===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw25CotTail  = new TChain("latino","");
  SetupTree("gg2vvHw25CotTail",TC_gg2vvHw25CotTail);
  SampleName = "gg2vvHw25CotTail";
  HWwNEvents HWwNEventsgg2vvHw25CotTail(TC_gg2vvHw25CotTail,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw25CotTail.Loop();

/*
//gg2vvHw1Sig8TeV========================================
  cout<<"gg2vvHw1Sig8TeV===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1Sig8TeV  = new TChain("latino","");
  SetupTree("gg2vvHw1Sig8TeV",TC_gg2vvHw1Sig8TeV);
  SampleName = "gg2vvHw1Sig8TeV";
  HWwNEvents HWwNEventsgg2vvHw1Sig8TeV(TC_gg2vvHw1Sig8TeV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw1Sig8TeV.Loop();

//gg2vvHw1Int8TeV========================================
  cout<<"gg2vvHw1Int8TeV===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1Int8TeV  = new TChain("latino","");
  SetupTree("gg2vvHw1Int8TeV",TC_gg2vvHw1Int8TeV);
  SampleName = "gg2vvHw1Int8TeV";
  HWwNEvents HWwNEventsgg2vvHw1Int8TeV(TC_gg2vvHw1Int8TeV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw1Int8TeV.Loop();

//gg2vvHw25Cot8TeV========================================
  cout<<"gg2vvHw25Cot8TeV===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw25Cot8TeV  = new TChain("latino","");
  SetupTree("gg2vvHw25Cot8TeV",TC_gg2vvHw25Cot8TeV);
  SampleName = "gg2vvHw25Cot8TeV";
  HWwNEvents HWwNEventsgg2vvHw25Cot8TeV(TC_gg2vvHw25Cot8TeV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwNEventsgg2vvHw25Cot8TeV.Loop();
*/
}
}
