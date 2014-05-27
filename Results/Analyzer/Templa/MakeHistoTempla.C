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

  TString Cut = "Loose"; // Loose, Tight
  // BaseName : Data, WJets, WW, Top, VVV, H125, DYLL, DYTT, VV
  bool RunOnMC = false;

//data========================================
  cout<<"data===================="<<endl;
  TChain *TC_data  = new TChain("latino","");
  SetupTree("data",TC_data);
  TString SampleName = "Data";
  HWwTempla HWwTemplaEg(TC_data,LumiTotal8TeV,SampleName,Cut, RunOnMC);
  HWwTemplaEg.Loop();
/************  
//wjets========================================
  cout<<"wjets===================="<<endl;
  TString AnaChannel = "wjets";
  TChain *TC_wjets  = new TChain("latino","");
  SetupTree("wjets",TC_wjets);
  TString wjets_File = "wjets";
  HWWwidth HWWwidth_wjets(TC_wjets,wjets_File,AnaChannel);
  HWWwidth_wjets.Loop();

//ww========================================
  cout<<"ww===================="<<endl;
  TString AnaChannel = "ww";
  TChain *TC_ww  = new TChain("latino","");
  SetupTree("ww",TC_ww);
  TString ww_File = "ww";
  HWWwidth HWWwidth_ww(TC_ww,ww_File,AnaChannel);
  HWWwidth_ww.Loop();

//top========================================
  cout<<"top===================="<<endl;
  TString AnaChannel = "top";
  TChain *TC_top  = new TChain("latino","");
  SetupTree("top",TC_top);
  TString top_File = "top";
  HWWwidth HWWwidth_top(TC_top,top_File,AnaChannel);
  HWWwidth_top.Loop();

//dyll========================================
  cout<<"dyll===================="<<endl;
  TString AnaChannel = "dyll";
  TChain *TC_dyll  = new TChain("latino","");
  SetupTree("dyll",TC_dyll);
  TString dyll_File = "dyll";
  HWWwidth HWWwidth_dyll(TC_dyll,dyll_File,AnaChannel);
  HWWwidth_dyll.Loop();

//dytt========================================
  cout<<"dytt===================="<<endl;
  TString AnaChannel = "dytt";
  TChain *TC_dytt  = new TChain("latino","");
  SetupTree("dytt",TC_dytt);
  TString dytt_File = "dytt";
  HWWwidth HWWwidth_dytt(TC_dytt,dytt_File,AnaChannel);
  HWWwidth_dytt.Loop();

//vv========================================
  cout<<"vv===================="<<endl;
  TString AnaChannel = "vv";
  TChain *TC_vv  = new TChain("latino","");
  SetupTree("vv",TC_vv);
  TString vv_File = "vv";
  HWWwidth HWWwidth_vv(TC_vv,vv_File,AnaChannel);
  HWWwidth_vv.Loop();

//vvv========================================
  cout<<"vvv===================="<<endl;
  TString AnaChannel = "vvv";
  TChain *TC_vvv  = new TChain("latino","");
  SetupTree("vvv",TC_vvv);
  TString vvv_File = "vvv";
  HWWwidth HWWwidth_vvv(TC_vvv,vvv_File,AnaChannel);
  HWWwidth_vvv.Loop();

//h125========================================
  cout<<"h125===================="<<endl;
  TString AnaChannel = "h125";
  TChain *TC_h125  = new TChain("latino","");
  SetupTree("h125",TC_h125);
  TString h125_File = "h125";
  HWWwidth HWWwidth_h125(TC_h125,h125_File,AnaChannel);
  HWWwidth_h125.Loop();
  ***********/
}
