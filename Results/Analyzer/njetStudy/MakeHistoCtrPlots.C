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

  //string Cuts[]={"CommonCut_njet"};
  //string Cuts[]={"CommonCut_VBf_NoVetoCentralJet"};
  string Cuts[]={"CommonCut_VBFnjet"};
  TString SampleName = "Data";
  bool RunOnMC = false;

  for( int i(0); i < sizeof(Cuts)/sizeof(*Cuts);++i){
    cout<<"Cut is "<<Cuts[i]<<endl;
/******    
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

//POWHEG========================================
    cout<<"POWHEG===================="<<endl;
    RunOnMC = true;
    TChain *TC_POWHEG  = new TChain("latino","");
    SetupTree("POWHEG",TC_POWHEG);
    SampleName = "POWHEG";
    HWwNjetStudy HWwNjetStudyPOWHEG(TC_POWHEG,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwNjetStudyPOWHEG.Loop();
********/
/****
//phantom========================================
    cout<<"phantom===================="<<endl;
    RunOnMC = true;

    //TChain *TC_phantom_1SM  = new TChain("latino","");
    //SetupTree("phantom_1SM",TC_phantom_1SM);
    //SampleName = "phantom_1SM";
    //HWwNjetStudy HWwNjetStudyphantom_1SM(TC_phantom_1SM,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    //HWwNjetStudyphantom_1SM.Loop();
    //TChain *TC_phantom_9SM  = new TChain("latino","");
    //SetupTree("phantom_9SM",TC_phantom_9SM);
    //SampleName = "phantom_9SM";
    //HWwNjetStudy HWwNjetStudyphantom_9SM(TC_phantom_9SM,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    //HWwNjetStudyphantom_9SM.Loop();
    TChain *TC_phantom_25SM  = new TChain("latino","");
    SetupTree("phantom_25SM",TC_phantom_25SM);
    SampleName = "phantom_25SM";
    HWwNjetStudy HWwNjetStudyphantom_25SM(TC_phantom_25SM,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwNjetStudyphantom_25SM.Loop();

********/
//***********
//POWHEG_VBF========================================
    cout<<"POWHEG_VBF===================="<<endl;
    RunOnMC = true;
    TChain *TC_POWHEG_VBF  = new TChain("latino","");
    SetupTree("POWHEG_VBF",TC_POWHEG_VBF);
    SampleName = "POWHEG_VBF";
    HWwNjetStudy HWwNjetStudyPOWHEG_VBF(TC_POWHEG_VBF,LumiTotal8TeV,SampleName,Cuts[i], RunOnMC);
    HWwNjetStudyPOWHEG_VBF.Loop();
//***********/
  }
}
