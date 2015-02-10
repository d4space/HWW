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
  gSystem->CompileMacro("../AnaSrc/HWwNjetStudy.C","k");

  string Cuts[]={"CommonCut_njet"};
  TString SampleName = "Data";
  bool RunOnMC = false;

  for( int i(0); i < sizeof(Cuts)/sizeof(*Cuts);++i){
    cout<<"Cut is "<<Cuts[i]<<endl;
/*    
//gg2vvHw1Sig8TeV========================================
    cout<<"gg2vvHw1Sig8TeV===================="<<endl;
    RunOnMC = true;
    TChain *TC_gg2vvHw1Sig8TeV  = new TChain("latino","");
    SetupTree("gg2vvHw1Sig8TeV",TC_gg2vvHw1Sig8TeV);
    SampleName = "gg2vvHw1Sig8TeV";
    HWwNjetStudy HWwNjetStudygg2vvHw1Sig8TeV(TC_gg2vvHw1Sig8TeV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwNjetStudygg2vvHw1Sig8TeV.Loop();

//sherpaHw1Sig8TeV========================================
    cout<<"sherpaHw1Sig8TeV===================="<<endl;
    RunOnMC = true;
    TChain *TC_sherpaHw1Sig8TeV  = new TChain("latino","");
    SetupTree("sherpaHw1Sig8TeV",TC_sherpaHw1Sig8TeV);
    SampleName = "SHERPA";
    HWwNjetStudy HWwNjetStudysherpaHw1Sig8TeV(TC_sherpaHw1Sig8TeV,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwNjetStudysherpaHw1Sig8TeV.Loop();
*/
//POWHEG========================================
    cout<<"POWHEG===================="<<endl;
    RunOnMC = true;
    TChain *TC_POWHEG  = new TChain("latino","");
    SetupTree("POWHEG",TC_POWHEG);
    SampleName = "POWHEG";
    HWwNjetStudy HWwNjetStudyPOWHEG(TC_POWHEG,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwNjetStudyPOWHEG.Loop();
  }
}
