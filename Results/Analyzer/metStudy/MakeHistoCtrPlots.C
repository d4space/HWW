#include <iostream>
#include "../include/SetupTree.h"
#include "../../../Utils/const.h"

using namespace std;
void MakeHistoCtrPlots()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
  gSystem->CompileMacro("../AnaSrc/HWwNT.C","k");
  gSystem->CompileMacro("../AnaSrc/HWwBase.C","k");
  gSystem->CompileMacro("../AnaSrc/HWwMET.C","k");

  string Cuts[]={"CommonCut"};
  //string Cuts[]={"NoCut"};
  TString SampleName = "WJetsToLNuMad";
  bool RunOnMC = false;

  for( int i(0); i < sizeof(Cuts)/sizeof(*Cuts);++i){
    cout<<"Cut is "<<Cuts[i]<<endl;
    
//WJetsToLNuMad========================================
/***
    cout<<"WJetsToLNuMad===================="<<endl;
    RunOnMC = true;
    TChain *TC_WJetsToLNuMad  = new TChain("latino","");
    SetupTree("WJetsToLNuMad",TC_WJetsToLNuMad);
    SampleName = "WJetsToLNuMad";
    HWwMET HWwMETWJetsToLNuMad(TC_WJetsToLNuMad,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwMETWJetsToLNuMad.Loop();
    ***/
    
//DYJetsToLL========================================
///****
    cout<<"DYJetsToLL===================="<<endl;
    RunOnMC = true;
    TChain *TC_DYJetsToLL  = new TChain("latino","");
    SetupTree("DYJetsToLL",TC_DYJetsToLL);
    SampleName = "DYJetsToLL";
    HWwMET HWwMETDYJetsToLL(TC_DYJetsToLL,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwMETDYJetsToLL.Loop();
    //***/
//***************    
//ggToH125toWWTo2LAndTau2Nu========================================
    cout<<"ggToH125toWWTo2LAndTau2Nu===================="<<endl;
    RunOnMC = true;
    TChain *TC_ggToH125toWWTo2LAndTau2Nu  = new TChain("latino","");
    SetupTree("ggToH125toWWTo2LAndTau2Nu",TC_ggToH125toWWTo2LAndTau2Nu);
    SampleName = "ggToH125toWWTo2LAndTau2Nu";
    HWwMET HWwMETggToH125toWWTo2LAndTau2Nu(TC_ggToH125toWWTo2LAndTau2Nu,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwMETggToH125toWWTo2LAndTau2Nu.Loop();

//******************/
  }
}
