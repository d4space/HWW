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
#include "chain_gg2vvHw25SigOnPeak.h"
#include "chain_gg2vvHw25SigShoulder.h"
#include "chain_gg2vvHw25SigTail.h"
#include "chain_gg2vvHw25IntOnPeak.h"
#include "chain_gg2vvHw25IntShoulder.h"
#include "chain_gg2vvHw25IntTail.h"
#include "chain_gg2vvHw25CotHead.h"
#include "chain_gg2vvHw25CotTail.h"
#include "chain_gg2vvHw1Sig8TeV.h"
#include "chain_gg2vvHw1Int8TeV.h"
#include "chain_gg2vvHw25Cot8TeV.h"
#include "chain_gg2vvHw25Sig8TeV.h"

#include "chain_gg2vvHw25Int8TeV.h"
#include "chain_gg2vvHw25SigShoulder.h"

//njet Study
#include "chain_powheg.h"
#include "chain_sherpaHw1Sig8TeV.h"
#include "chain_powheg_vbf.h"
#include "chain_phantom.h"

//MET Study
#include "chain_WJetsToLNuMad.h"
#include "chain_DYJetsToLL.h"
#include "chain_ggToH125toWWTo2LAndTau2Nu.h"

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
  else if(sample == "WJetsToLNuMad"){
    chain_WJetsToLNuMad(chains);
  }
  else if(sample == "DYJetsToLL"){
    chain_DYJetsToLL(chains);
  }
  else if(sample == "ggToH125toWWTo2LAndTau2Nu"){
    chain_ggToH125toWWTo2LAndTau2Nu(chains);
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
  else if(sample == "gg2vvHw25CotHead"){
    chain_gg2vvHw25CotHead(chains);
  }
  else if(sample == "gg2vvHw25CotTail"){
    chain_gg2vvHw25CotTail(chains);
  }
  else if(sample == "gg2vvHw25SigOnPeak"){
    chain_gg2vvHw25SigOnPeak(chains);
  }
  else if(sample == "gg2vvHw25SigShoulder"){
    chain_gg2vvHw25SigShoulder(chains);
  }
  else if(sample == "gg2vvHw25SigTail"){
    chain_gg2vvHw25SigTail(chains);
  }
  else if(sample == "gg2vvHw25IntOnPeak"){
    chain_gg2vvHw25IntOnPeak(chains);
  }
  else if(sample == "gg2vvHw25IntShoulder"){
    chain_gg2vvHw25IntShoulder(chains);
  }
  else if(sample == "gg2vvHw25IntTail"){
    chain_gg2vvHw25IntTail(chains);
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
  else if(sample == "gg2vvHw25Sig8TeV"){
    chain_gg2vvHw25Sig8TeV(chains);
  }
  else if(sample == "gg2vvHw25Int8TeV"){
    chain_gg2vvHw25Int8TeV(chains);
  }
//njet Study
  else if( sample == "POWHEG"){
    chain_powheg(chains);
  }
  else if( sample == "POWHEG_VBF"){
    chain_powheg_vbf(chains);
  }
  else if( sample == "phantom"){
    chain_phantom(chains);
  }
  else if(sample == "sherpaHw1Sig8TeV"){
    chain_sherpaHw1Sig8TeV(chains);
  }
  else
  {
    cout<<"[SetupTree.h] Nanigorae? "<<endl;
  }
}
