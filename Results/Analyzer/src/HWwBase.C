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
Int_t HWwBase::OF0jCut()
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
Int_t HWwBase::OF1jCut()
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
double HWwBase::CalcWeight()
{
  double evtWeight(1);
  if(SampleName == "Data")
  {
    evtWeight = 1;
  }else if(SampleName == "WJet")
  {
    evtWeight = fakeW*(run!=201191);
  }else if(SampleName == "WW")
  {
    evtWeight = puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "Top")
  {
    evtWeight = puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "DYll")
  {
    evtWeight = puW*baseW*effW*triggW*sameflav*LumiW;
  }else if(SampleName == "DYtt")
  {
    evtWeight = puW*baseW*effW*triggW*(!sameflav)*LumiW;
  }else if(SampleName == "VV")
  {
    evtWeight = puW*baseW*effW*triggW*(1+0.5*(dataset>=82&&dataset<=84))*LumiW;
  }else if(SampleName == "VVV")
  {
    evtWeight = puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "H125")
  {
    evtWeight = puW*baseW*effW*triggW*LumiW;
  }
  return evtWeight;
}
double HWwBase::ScaleFactor()
{
  double scaleF(1);
  // TODO same flavor scale factor not decided
  if( (myChannel == AC_sf0j) || (myChannel == AC_sf1j) )
  {
    return 1;
  }
  if(SampleName == "Data")
  {
    scaleF = 1;
  }else if(SampleName == "WJet")
  {
    scaleF = 1;
  }else if(SampleName == "WW")
  {
    if(myChannel == AC_of0j) scaleF = 1.0364;
    if(myChannel == AC_of1j) scaleF = 0.84151;
  }else if(SampleName == "Top")
  {
    if(myChannel == AC_of0j) scaleF = 1.01264;
    if(myChannel == AC_of1j) scaleF = 1.11272;
  }else if(SampleName == "DYll")
  {
    if(myChannel == AC_of0j) scaleF = 6.98418;
    if(myChannel == AC_of1j) scaleF = 3.73978;
  }else if(SampleName == "DYtt")
  {
    scaleF = 1;
  }else if(SampleName == "VV")
  {
    scaleF = 1;
  }else if(SampleName == "VVV")
  {
    scaleF = 1;
  }else if(SampleName == "H125")
  {
    scaleF = 1;
  }
  return scaleF;
}
