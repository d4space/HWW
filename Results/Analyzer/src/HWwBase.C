#define HWwBase_cxx
#include "HWwBase.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include <algorithm>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

void HWwBase::Loop()
{
  gBenchmark->Start("HWwBase");
  if (fChain == 0) return;

  int Ntries = fChain->GetEntries();
  cout<<"Total: "<<Ntries<<endl;

  for (int i(0); i<Ntries;i++)
  {
    evtCnt = i;
    fChain->GetEntry(i);
  }
  gBenchmark->Show("HWwBase");
}
//Loose selection cuts
Int_t HWwBase::SF0jCut()
{
  if (!sameflav) return -1;
  if (njet != 0) return -1;
  return 1;
}
Int_t HWwBase::DF0jCut()
{
  if (sameflav)  return -1;
  if (njet != 0) return -1;
  return 1;
}
Int_t HWwBase::SF1jCut()
{
  if (!sameflav) return -1;
  if (njet != 1) return -1;
  return 1;
}
Int_t HWwBase::DF1jCut()
{
  if (sameflav)  return -1;
  if (njet != 1) return -1;
  return 1;
}
//CommonCuts from Xavier for Same Flavor
Int_t HWwBase::CommonCut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{ return -1;}
  if (pt1>20 && pt2>10){;}else{ return -1;}
  if (nextra==0){;}else{ return -1;}
  if (pfmet>20.){;}else{ return -1;}
  if (mll>12.){;}else{ return -1;}
  if (zveto==1 || !sameflav){;}else{ return -1;}
  if (mpmet>20.&&
      (!sameflav||
	( (njet!=0||dymva1>0.88) && (njet!=1||dymva1>0.84) && (njet==0||njet==1||(pfmet>45.0)))
      )
     ){;}else{ return -1;}
  if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  if (bveto_mu==1){;}else{ return -1;}
  if (bveto_ip==1 && nbjettche==0){;}else{ return -1;}
  if (ptll>30.){;}else{ return -1;}
  return 1;
}
int HWwBase::CalcWeight()
{
  if(SampleName == "Data")
  {
    EvtWeight = 1;
  }else if(SampleName == "WJet")
  {
    EvtWeight = fakeW*(run!=201191);
  }else if(SampleName == "WW")
  {
    EvtWeight = puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "Top")
  {
    EvtWeight = puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "DYll")
  {
    EvtWeight = puW*baseW*effW*triggW*sameflav*LumiW;
  }else if(SampleName == "DYtt")
  {
    EvtWeight = puW*baseW*effW*triggW*(!sameflav)*LumiW;
  }else if(SampleName == "VV")
  {
    EvtWeight = puW*baseW*effW*triggW*(1+0.5*(dataset>=82&&dataset<=84))*LumiW;
  }else if(SampleName == "VVV")
  {
    EvtWeight = puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "H125")
  {
    EvtWeight = puW*baseW*effW*triggW*LumiW;
  }
  return EvtWeight;
}
