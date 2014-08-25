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
  gSystem->CompileMacro("../src/HWwCtrPlt.C","k");

  //TString Cut = "Loose"; // Loose, Tight
  //TString Cut = "Tight"; // Loose, Tight
  string Cuts[]={"LooseCut","CommonCut"}; // Loose, Tight
  //string Cuts[]={"Loose"}; // Loose, Tight
  //string Cuts[]={"CommonCut"}; // Loose, Tight
  TString SampleName = "Data";
  // BaseName : Data, WJet, WW, Top, VVV, H125, DYll, DYtt, VV
  bool RunOnMC = false;

for( int i(0); i < sizeof(Cuts)/sizeof(*Cuts);++i){
  cout<<"Cut is "<<Cuts[i]<<endl;
//*
//Data========================================
  cout<<"Data===================="<<endl;
  RunOnMC = false;
  TChain *TC_Data  = new TChain("latino","");
  SetupTree("Data",TC_Data);
  SampleName = "Data";
  HWwCtrPlt HWwCtrPltRD(TC_Data,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltRD.Loop();

//WJet========================================
  cout<<"WJet===================="<<endl;
  RunOnMC = true;
  TChain *TC_WJet  = new TChain("latino","");
  SetupTree("WJet",TC_WJet);
  SampleName = "WJet";
  HWwCtrPlt HWwCtrPltWJ(TC_WJet,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltWJ.Loop();

//ww========================================
  cout<<"WW===================="<<endl;
  RunOnMC = true;
  TChain *TC_WW  = new TChain("latino","");
  SetupTree("WW",TC_WW);
  SampleName = "WW";
  HWwCtrPlt HWwCtrPltWW(TC_WW,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltWW.Loop();

//top========================================
  cout<<"Top===================="<<endl;
  RunOnMC = true;
  TChain *TC_Top  = new TChain("latino","");
  SetupTree("Top",TC_Top);
  SampleName = "Top";
  HWwCtrPlt HWwCtrPltTop(TC_Top,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltTop.Loop();

//dyll========================================
  cout<<"DYll===================="<<endl;
  RunOnMC = true;
  TChain *TC_DYll  = new TChain("latino","");
  SetupTree("DYll",TC_DYll);
  SampleName = "DYll";
  HWwCtrPlt HWwCtrPltDYll(TC_DYll,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltDYll.Loop();

//dytt========================================
  cout<<"DYtt===================="<<endl;
  RunOnMC = true;
  TChain *TC_DYtt  = new TChain("latino","");
  SetupTree("DYtt",TC_DYtt);
  SampleName = "DYtt";
  HWwCtrPlt HWwCtrPltDYtt(TC_DYtt,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltDYtt.Loop();

//vv========================================
  cout<<"VV===================="<<endl;
  RunOnMC = true;
  TChain *TC_VV  = new TChain("latino","");
  SetupTree("VV",TC_VV);
  SampleName = "VV";
  HWwCtrPlt HWwCtrPltVV(TC_VV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltVV.Loop();

//vvv========================================
  cout<<"VVV===================="<<endl;
  RunOnMC = true;
  TChain *TC_VVV  = new TChain("latino","");
  SetupTree("VVV",TC_VVV);
  SampleName = "VVV";
  HWwCtrPlt HWwCtrPltVVV(TC_VVV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltVVV.Loop();

//h125========================================
  cout<<"H125===================="<<endl;
  RunOnMC = true;
  TChain *TC_H125  = new TChain("latino","");
  SetupTree("H125",TC_H125);
  SampleName = "H125";
  HWwCtrPlt HWwCtrPltH125(TC_H125,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltH125.Loop();
//*/
//gg2vvHw25========================================
  //cout<<"gg2vvHw25===================="<<endl;
  //RunOnMC = true;
  //TChain *TC_gg2vvHw25  = new TChain("latino","");
  //SetupTree("gg2vvHw25",TC_gg2vvHw25);
  //SampleName = "gg2vvHw25";
  //HWwCtrPlt HWwCtrPltgg2vvHw25(TC_gg2vvHw25,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  //HWwCtrPltgg2vvHw25.Loop();

//gg2vvHw1========================================
  //cout<<"gg2vvHw1===================="<<endl;
  //RunOnMC = true;
  //TChain *TC_gg2vvHw1  = new TChain("latino","");
  //SetupTree("gg2vvHw1",TC_gg2vvHw1);
  //SampleName = "gg2vvHw1";
  //HWwCtrPlt HWwCtrPltgg2vvHw1(TC_gg2vvHw1,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  //HWwCtrPltgg2vvHw1.Loop();
/*
//gg2vvHw1SigOnPeak========================================
  cout<<"gg2vvHw1SigOnPeak===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1SigOnPeak  = new TChain("latino","");
  SetupTree("gg2vvHw1SigOnPeak",TC_gg2vvHw1SigOnPeak);
  SampleName = "gg2vvHw1SigOnPeak";
  HWwCtrPlt HWwCtrPltgg2vvHw1SigOnPeak(TC_gg2vvHw1SigOnPeak,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw1SigOnPeak.Loop();

//gg2vvHw1SigShoulder========================================
  cout<<"gg2vvHw1SigShoulder===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1SigShoulder  = new TChain("latino","");
  SetupTree("gg2vvHw1SigShoulder",TC_gg2vvHw1SigShoulder);
  SampleName = "gg2vvHw1SigShoulder";
  HWwCtrPlt HWwCtrPltgg2vvHw1SigShoulder(TC_gg2vvHw1SigShoulder,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw1SigShoulder.Loop();

//gg2vvHw1SigTail========================================
  cout<<"gg2vvHw1SigTail===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1SigTail  = new TChain("latino","");
  SetupTree("gg2vvHw1SigTail",TC_gg2vvHw1SigTail);
  SampleName = "gg2vvHw1SigTail";
  HWwCtrPlt HWwCtrPltgg2vvHw1SigTail(TC_gg2vvHw1SigTail,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw1SigTail.Loop();

//gg2vvHw1IntOnPeak========================================
  cout<<"gg2vvHw1IntOnPeak===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1IntOnPeak  = new TChain("latino","");
  SetupTree("gg2vvHw1IntOnPeak",TC_gg2vvHw1IntOnPeak);
  SampleName = "gg2vvHw1IntOnPeak";
  HWwCtrPlt HWwCtrPltgg2vvHw1IntOnPeak(TC_gg2vvHw1IntOnPeak,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw1IntOnPeak.Loop();

//gg2vvHw1IntShoulder========================================
  cout<<"gg2vvHw1IntShoulder===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1IntShoulder  = new TChain("latino","");
  SetupTree("gg2vvHw1IntShoulder",TC_gg2vvHw1IntShoulder);
  SampleName = "gg2vvHw1IntShoulder";
  HWwCtrPlt HWwCtrPltgg2vvHw1IntShoulder(TC_gg2vvHw1IntShoulder,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw1IntShoulder.Loop();

//gg2vvHw1IntTail========================================
  cout<<"gg2vvHw1IntTail===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1IntTail  = new TChain("latino","");
  SetupTree("gg2vvHw1IntTail",TC_gg2vvHw1IntTail);
  SampleName = "gg2vvHw1IntTail";
  HWwCtrPlt HWwCtrPltgg2vvHw1IntTail(TC_gg2vvHw1IntTail,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw1IntTail.Loop();
*/
//gg2vvHw1Sig8TeV========================================
  cout<<"gg2vvHw1Sig8TeV===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1Sig8TeV  = new TChain("latino","");
  SetupTree("gg2vvHw1Sig8TeV",TC_gg2vvHw1Sig8TeV);
  SampleName = "gg2vvHw1Sig8TeV";
  HWwCtrPlt HWwCtrPltgg2vvHw1Sig8TeV(TC_gg2vvHw1Sig8TeV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw1Sig8TeV.Loop();

//gg2vvHw1Int8TeV========================================
  cout<<"gg2vvHw1Int8TeV===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw1Int8TeV  = new TChain("latino","");
  SetupTree("gg2vvHw1Int8TeV",TC_gg2vvHw1Int8TeV);
  SampleName = "gg2vvHw1Int8TeV";
  HWwCtrPlt HWwCtrPltgg2vvHw1Int8TeV(TC_gg2vvHw1Int8TeV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw1Int8TeV.Loop();

//gg2vvHw25Cot8TeV========================================
  cout<<"gg2vvHw25Cot8TeV===================="<<endl;
  RunOnMC = true;
  TChain *TC_gg2vvHw25Cot8TeV  = new TChain("latino","");
  SetupTree("gg2vvHw25Cot8TeV",TC_gg2vvHw25Cot8TeV);
  SampleName = "gg2vvHw25Cot8TeV";
  HWwCtrPlt HWwCtrPltgg2vvHw25Cot8TeV(TC_gg2vvHw25Cot8TeV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
  HWwCtrPltgg2vvHw25Cot8TeV.Loop();
}
}
