#include <TChain.h>
#include "chain_SigHw1gg2vv8TeV.h" 
#include "chain_IntHw1gg2vv8TeV.h" 
#include "chain_CotHw1gg2vv8TeV.h" 
#include "chain_SigHw25gg2vv8TeV.h" 
#include "chain_IntHw25gg2vv8TeV.h" 
#include "chain_CotHw25gg2vv8TeV.h" 
#include "chain_SigHw1gg2vv8TeVOnPeak.h" 
#include "chain_SigHw1gg2vv8TeVShoulder.h" 
#include "chain_SigHw1gg2vv8TeVTail.h" 
#include "chain_IntHw1gg2vv8TeVOnPeak.h" 
#include "chain_IntHw1gg2vv8TeVShoulder.h" 
#include "chain_IntHw1gg2vv8TeVTail.h" 
#include "chain_SigHw25gg2vv8TeVOnPeak.h" 
#include "chain_SigHw25gg2vv8TeVShoulder.h" 
#include "chain_SigHw25gg2vv8TeVTail.h" 
#include "chain_IntHw25gg2vv8TeVOnPeak.h" 
#include "chain_IntHw25gg2vv8TeVShoulder.h" 
#include "chain_IntHw25gg2vv8TeVTail.h" 
#include "chain_CotHw25gg2vv8TeVHead.h" 
#include "chain_CotHw25gg2vv8TeVTail.h" 

void SetupTreeHWWgg2vv8TeV(TString sample, TChain* chains )
{
  cout<<"SetupTreeHWWgg2vv8TeV.h: "<<sample<<endl;
  //=========
  //gg2vv 8TeV
  //=========
  if( sample == "Hw1Sig8TeV"){
    chain_SigHw1gg2vv8TeV(chains);
  }else if( sample == "Hw1Int8TeV"){
    chain_IntHw1gg2vv8TeV(chains);
  }else if( sample == "Hw1Cot8TeV"){
    chain_CotHw1gg2vv8TeV(chains);
  }else if( sample == "Hw25Sig8TeV"){
    chain_SigHw25gg2vv8TeV(chains);
  }else if( sample == "Hw25Int8TeV"){
    chain_IntHw25gg2vv8TeV(chains);
  }else if( sample == "Hw25Cot8TeV"){
    chain_CotHw25gg2vv8TeV(chains);
  }else if(sample == "Hw1Sig8TeVOnPeak"){
    chain_SigHw1gg2vv8TeVOnPeak(chains);
  }else if(sample == "Hw1Sig8TeVShoulder"){
    chain_SigHw1gg2vv8TeVShoulder(chains);
  }else if(sample == "Hw1Sig8TeVTail"){
    chain_SigHw1gg2vv8TeVTail(chains);
  }else if(sample == "Hw1Int8TeVOnPeak"){
    chain_IntHw1gg2vv8TeVOnPeak(chains);
  }else if(sample == "Hw1Int8TeVShoulder"){
    chain_IntHw1gg2vv8TeVShoulder(chains);
  }else if(sample == "Hw1Int8TeVTail"){
    chain_IntHw1gg2vv8TeVTail(chains);
  }else if(sample == "Hw25Sig8TeVOnPeak"){
    chain_SigHw25gg2vv8TeVOnPeak(chains);
  }else if(sample == "Hw25Sig8TeVShoulder"){
    chain_SigHw25gg2vv8TeVShoulder(chains);
  }else if(sample == "Hw25Sig8TeVTail"){
    chain_SigHw25gg2vv8TeVTail(chains);
  }else if(sample == "Hw25Int8TeVOnPeak"){
    chain_IntHw25gg2vv8TeVOnPeak(chains);
  }else if(sample == "Hw25Int8TeVShoulder"){
    chain_IntHw25gg2vv8TeVShoulder(chains);
  }else if(sample == "Hw25Int8TeVTail"){
    chain_IntHw25gg2vv8TeVTail(chains);
  }else if(sample == "Hw25Cot8TeVHead"){
    chain_CotHw25gg2vv8TeVHead(chains);
  }else if(sample == "Hw25Cot8TeVTail"){
    chain_CotHw25gg2vv8TeVTail(chains);
  }else
    cout<<"[SetupTreeHw1gg2vv8TeV.h] Nanigorae? "<<endl;
}
