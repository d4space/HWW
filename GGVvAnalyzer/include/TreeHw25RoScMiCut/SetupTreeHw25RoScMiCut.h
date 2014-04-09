#include <TChain.h>
#include "chain_SigHw25RoScMiCut.h" 
#include "chain_IntHw25RoScMiCut.h" 
#include "chain_ContHw25RoScMiCut.h" 

void SetupTreeHw25RoScMiCut( TString sample, TChain* chains )
{
  cout<<"SetupTreeHw25RoScMiCut.h: "<<sample<<endl;
  //=========
  //LowPU
  //=========
  if( sample == "SigHw25RoScMiCut"){
    chain_SigHw25RoScMiCut(chains);
  }
  else if( sample == "IntHw25RoScMiCut"){
    chain_IntHw25RoScMiCut(chains);
  }
  else if( sample == "ContHw25RoScMiCut")
  {
    chain_ContHw25RoScMiCut(chains);
  }else
    cout<<"[SetupTreeHw25RoScMiCut.h] Nanigorae? "<<endl;
}
