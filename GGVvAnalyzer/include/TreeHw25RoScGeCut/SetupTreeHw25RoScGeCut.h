#include <TChain.h>
#include "chain_SigHw25RoScGeCut.h" 
#include "chain_IntHw25RoScGeCut.h" 
#include "chain_ContHw25RoScGeCut.h" 

void SetupTreeHw25RoScGeCut( TString sample, TChain* chains )
{
  cout<<"SetupTreeHw25RoScGeCut.h: "<<sample<<endl;
  //=========
  //LowPU
  //=========
  if( sample == "SigHw25RoScGeCut"){
    chain_SigHw25RoScGeCut(chains);
  }
  else if( sample == "IntHw25RoScGeCut"){
    chain_IntHw25RoScGeCut(chains);
  }
  else if( sample == "ContHw25RoScGeCut")
  {
    chain_ContHw25RoScGeCut(chains);
  }else
    cout<<"[SetupTreeHw25RoScGeCut.h] Nanigorae? "<<endl;
}
