#include <iostream>
#include "../include/SetupTree.h"
#include "../../../Utils/const.h"

using namespace std;
void MakeHistoTempla()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
  gSystem->CompileMacro("../src/HWwNT.C","k");
  gSystem->CompileMacro("../src/HWwBase.C","k");
  gSystem->CompileMacro("../src/HWwTempla.C","k");

  //TString Cut = "Loose"; // Loose, Tight
  //TString Cut = "Tight"; // Loose, Tight
  string Cuts[]={"Loose","Tight"}; // Loose, Tight
  TString SampleName = "haha";
  TString Channel = "all"; //all, sf0j, of0j, sf1j, of1j
  // BaseName : Data, WJet, WW, Top, VVV, H125, DYll, DYtt, VV
  bool RunOnMC = false;

for( int i(0); i < sizeof(Cuts)/sizeof(*Cuts);++i){
  cout<<"Cut is "<<Cuts[i]<<endl;
//Data========================================
  cout<<"Data===================="<<endl;
  RunOnMC = false;
  TChain *TC_Data  = new TChain("latino","");
  SetupTree("Data",TC_Data);
  SampleName = "Data";
  HWwTempla HWwTemplaRD(TC_Data,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaRD.Loop();
//WJet========================================
  cout<<"WJet===================="<<endl;
  RunOnMC = true;
  TChain *TC_WJet  = new TChain("latino","");
  SetupTree("WJet",TC_WJet);
  SampleName = "WJet";
  HWwTempla HWwTemplaWJ(TC_WJet,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaWJ.Loop();

//ww========================================
  cout<<"WW===================="<<endl;
  RunOnMC = true;
  TChain *TC_WW  = new TChain("latino","");
  SetupTree("WW",TC_WW);
  SampleName = "WW";
  HWwTempla HWwTemplaWW(TC_WW,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaWW.Loop();

//top========================================
  cout<<"Top===================="<<endl;
  RunOnMC = true;
  TChain *TC_Top  = new TChain("latino","");
  SetupTree("Top",TC_Top);
  SampleName = "Top";
  HWwTempla HWwTemplaTop(TC_Top,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaTop.Loop();

//dyll========================================
  cout<<"DYll===================="<<endl;
  RunOnMC = true;
  TChain *TC_DYll  = new TChain("latino","");
  SetupTree("DYll",TC_DYll);
  SampleName = "DYll";
  HWwTempla HWwTemplaDYll(TC_DYll,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaDYll.Loop();

//dytt========================================
  cout<<"DYtt===================="<<endl;
  RunOnMC = true;
  TChain *TC_DYtt  = new TChain("latino","");
  SetupTree("DYtt",TC_DYtt);
  SampleName = "DYtt";
  HWwTempla HWwTemplaDYtt(TC_DYtt,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaDYtt.Loop();

//vv========================================
  cout<<"VV===================="<<endl;
  RunOnMC = true;
  TChain *TC_VV  = new TChain("latino","");
  SetupTree("VV",TC_VV);
  SampleName = "VV";
  HWwTempla HWwTemplaVV(TC_VV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaVV.Loop();

//vvv========================================
  cout<<"VVV===================="<<endl;
  RunOnMC = true;
  TChain *TC_VVV  = new TChain("latino","");
  SetupTree("VVV",TC_VVV);
  SampleName = "VVV";
  HWwTempla HWwTemplaVVV(TC_VVV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaVVV.Loop();

//h125========================================
  cout<<"H125===================="<<endl;
  RunOnMC = true;
  TChain *TC_H125  = new TChain("latino","");
  SetupTree("H125",TC_H125);
  SampleName = "H125";
  HWwTempla HWwTemplaH125(TC_H125,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC, Channel);
  HWwTemplaH125.Loop();
}
}
