#include <TChain.h>
#include "chain_SigHw1gg2vv8TeV.h" 
#include "chain_IntHw1gg2vv8TeV.h" 
#include "chain_CotHw1gg2vv8TeV.h" 

void SetupTreeHw1gg2vv8TeV( TString sample, TChain* chains )
{
  cout<<"SetupTreeHw1gg2vv8TeV.h: "<<sample<<endl;
  //=========
  //LowPU
  //=========
  if( sample == "Hw1Sig8TeV"){
    chain_SigHw1gg2vv8TeV(chains);
  }else if( sample == "Hw1Int8TeV"){
    chain_IntHw1gg2vv8TeV(chains);
  }else if( sample == "Hw1Cot8TeV"){
    chain_CotHw1gg2vv8TeV(chains);
  }else
    cout<<"[SetupTreeHw1gg2vv8TeV.h] Nanigorae? "<<endl;
}
