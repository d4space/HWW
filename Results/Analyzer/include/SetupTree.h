#include <TChain.h>
//=============
#include "chain_RD.h"
#include "chain_wjets.h"
#include "chain_dyll.h"
#include "chain_dytt.h"
#include "chain_h125.h"
#include "chain_top.h"
#include "chain_vv.h"
#include "chain_vvv.h"
#include "chain_ww.h"
#include "chain_gg2vvHw25.h"
#include "chain_gg2vvHw1.h"
#include "chain_gg2vvHw1SigOnPeak.h"
#include "chain_gg2vvHw1SigShoulder.h"
#include "chain_gg2vvHw1SigTail.h"
#include "chain_gg2vvHw1IntOnPeak.h"
#include "chain_gg2vvHw1IntShoulder.h"
#include "chain_gg2vvHw1IntTail.h"
#include "chain_gg2vvHw1Sig8TeV.h"
#include "chain_gg2vvHw1Int8TeV.h"
#include "chain_gg2vvHw25Cot8TeV.h"

#include "chain_gg2vvHw25SigShoulder.h"
//===============

void SetupTree( TString sample, TChain* chains )
{
  cout<<"SetupTree.h: "<<sample<<endl;
  //=========
  //LowPU
  //=========
  if(sample == "Data"){
    chain_RD(chains);
  }
  else if(sample == "WJet"){
    chain_wjets(chains);
  }
  else if(sample == "WW"){
    chain_ww(chains);
  }
  else if(sample == "Top"){
    chain_top(chains);
  }
  else if(sample == "DYll"){
    chain_dyll(chains);
  }
  else if(sample == "DYtt"){
    chain_dytt(chains);
  }
  else if(sample == "VV"){
    chain_vv(chains);
  }
  else if(sample == "VVV"){
    chain_vvv(chains);
  }
  else if( sample == "H125"){
    chain_h125(chains);
  }
  else if(sample == "gg2vvHw25"){
    chain_gg2vvHw25(chains);
  }
  else if(sample == "gg2vvHw1"){
    chain_gg2vvHw1(chains);
  }
  else if(sample == "gg2vvHw25SigShoulder"){
    chain_gg2vvHw25SigShoulder(chains);
  }
  else if(sample == "gg2vvHw1SigOnPeak"){
    chain_gg2vvHw1SigOnPeak(chains);
  }
  else if(sample == "gg2vvHw1SigShoulder"){
    chain_gg2vvHw1SigShoulder(chains);
  }
  else if(sample == "gg2vvHw1SigTail"){
    chain_gg2vvHw1SigTail(chains);
  }
  else if(sample == "gg2vvHw1IntOnPeak"){
    chain_gg2vvHw1IntOnPeak(chains);
  }
  else if(sample == "gg2vvHw1IntShoulder"){
    chain_gg2vvHw1IntShoulder(chains);
  }
  else if(sample == "gg2vvHw1IntTail"){
    chain_gg2vvHw1IntTail(chains);
  }
  else if(sample == "gg2vvHw1Sig8TeV"){
    chain_gg2vvHw1Sig8TeV(chains);
  }
  else if(sample == "gg2vvHw1Int8TeV"){
    chain_gg2vvHw1Int8TeV(chains);
  }
  else if(sample == "gg2vvHw25Cot8TeV"){
    chain_gg2vvHw25Cot8TeV(chains);
  }
  else
  {
    cout<<"[SetupTree.h] Nanigorae? "<<endl;
  }
}
