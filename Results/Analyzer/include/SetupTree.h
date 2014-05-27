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
  else
  {
    cout<<"[SetupTree.h] Nanigorae? "<<endl;
  }
}
