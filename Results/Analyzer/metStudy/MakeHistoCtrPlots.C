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

  string Cuts[]={"NoCut","CommonCut","CommonCut_OffShell"};
  TString SampleName = "Data";
  // BaseName : Data, WJet, WW, Top, VVV, H125, DYll, DYtt, VV
  bool RunOnMC = false;

  for( int i(0); i < sizeof(Cuts)/sizeof(*Cuts);++i){
    cout<<"Cut is "<<Cuts[i]<<endl;
    
//WJetsToLNuMad========================================
    cout<<"WJetsToLNuMad===================="<<endl;
    RunOnMC = true;
    TChain *TC_WJetsToLNuMad  = new TChain("latino","");
    SetupTree("WJetsToLNuMad",TC_WJetsToLNuMad);
    SampleName = "WJetsToLNuMad";
    HWwMET HWwMETWJetsToLNuMad(TC_WJetsToLNuMad,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwMETWJetsToLNuMad.Loop();
  }
}
