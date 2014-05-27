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
  string Cuts[]={"Loose","Tight"}; // Loose, Tight
  TString SampleName = "Data";
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
}
}
