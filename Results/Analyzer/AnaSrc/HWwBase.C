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
    //evtCnt = i;
    fChain->GetEntry(i);
  }
  gBenchmark->Show("HWwBase");
}
//Loose selection cuts
Int_t HWwBase::SF0jCut()
{

  if (ch1*ch2 ==-1.){;}else{return -1;}
  //if (!sameflav) return -1;
  if (njet != 0) return -1;
  return 1;
}
Int_t HWwBase::OF0jCut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  //if (sameflav)  return -1;
  if (njet != 0) return -1;
  return 1;
}
Int_t HWwBase::SF1jCut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  //if (!sameflav) return -1;
  if (njet != 1) return -1;
  return 1;
}
Int_t HWwBase::OF1jCut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  //if (sameflav)  return -1;
  if (njet != 1) return -1;
  return 1;
}
//CommonCuts from Xavier for Same Flavor
Int_t HWwBase::CommonCut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  //if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>10){;}else{return -1;}
  //if (nextra==0){;}else{return -1;}
  //if (pfmet>20.){;}else{return -1;}
  if (mll>12.){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /***
  if (mpmet>20.&&
      (!sameflav||
	(
	  (njet!=0||dymva1>0.88) &&
	  (njet!=1||dymva1>0.84) &&
	  (njet==0||njet==1||(pfmet>45.0))
	)
      )
     ){;}else{return -1;}
     ****/
  //if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  //if (bveto_mu==1){;}else{return -1;}
  //if (bveto_ip==1 && nbjettche==0){;}else{return -1;}
  //if (ptll>30.){;}else{return -1;}
  /***
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    ****/
  return 1;
}
//Optimized Cuts V1 
Int_t HWwBase::SignalCutV1()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>10){;}else{return -1;}
  if (nextra==0){;}else{return -1;}
  if (pfmet>20.){;}else{return -1;}
  if (mll>84){;}else{return -1;} //Optimized Cut
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /****
  if (mpmet>20.&&
      (!sameflav||
	(
	  (njet!=0||dymva1>0.88) &&
	  (njet!=1||dymva1>0.84) &&
	  (njet==0||njet==1||(pfmet>45.0))
	)
      )
     ){;}else{return -1;}
     ***/
  //if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  if (bveto_mu==1){;}else{return -1;}
  if (bveto_ip==1 && nbjettche==0){;}else{return -1;}
  if (ptll>30.){;}else{return -1;}
  /*****
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    *****/

  return 1;
}
//Optimized Cuts V2 
Int_t HWwBase::SignalCutV2()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>10){;}else{return -1;}
  if (nextra==0){;}else{return -1;}
  if (pfmet>20.){;}else{return -1;}
  if (mll>82.6283){;}else{return -1;} //Optimized Cut
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /*****
  if (mpmet>20.&&
      (!sameflav||
	(
	  (njet!=0||dymva1>0.88) &&
	  (njet!=1||dymva1>0.84) &&
	  (njet==0||njet==1||(pfmet>45.0))
	)
      )
     ){;}else{return -1;}
     ***************/
  //if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  if (bveto_mu==1){;}else{return -1;}
  if (bveto_ip==1 && nbjettche==0){;}else{return -1;}
  if (ptll>9.89954){;}else{return -1;} //Optimized Cut
  /*********
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    ***************/

  return 1;
}
//Optimized Cuts V3
Int_t HWwBase::SignalCutV3()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>10){;}else{return -1;}
  if (nextra==0){;}else{return -1;}
  if (pfmet>20.){;}else{return -1;}
  //if (mll>83.){;}else{return -1;}
  if (mll>12.){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /***************
  if (mpmet>20.&&
      (!sameflav||
	(
	  (njet!=0||dymva1>0.88) &&
	  (njet!=1||dymva1>0.84) &&
	  (njet==0||njet==1||(pfmet>45.0))
	)
      )
     ){;}else{return -1;}
     *************/
  //if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  if (bveto_mu==1){;}else{return -1;}
  if (bveto_ip==1 && nbjettche==0){;}else{return -1;}
  //if (ptll>10.){;}else{return -1;}
  //if (mth>130.){;}else{return -1;}
  /***************
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    ****************/

  return 1;
}
Int_t HWwBase::CommonCut_Without_mll_ptll_Cut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>10){;}else{return -1;}
  if (nextra==0){;}else{return -1;}
  if (pfmet>20.){;}else{return -1;}
  //if (mll>12.){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /****************
  if (mpmet>20.&&
      (!sameflav||
	(
	  (njet!=0||dymva1>0.88) &&
	  (njet!=1||dymva1>0.84) &&
	  (njet==0||njet==1||(pfmet>45.0))
	)
      )
     ){;}else{return -1;}
     ******************/
  //if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  if (bveto_mu==1){;}else{return -1;}
  if (bveto_ip==1 && nbjettche==0){;}else{return -1;}
  //if (ptll>30.){;}else{return -1;}
  /***************
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    ****************/

  return 1;
}
Int_t HWwBase::CommonCut_Without_mllCut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>10){;}else{return -1;}
  if (nextra==0){;}else{return -1;}
  if (pfmet>20.){;}else{return -1;}
  //if (mll>12.){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /*****
  if (mpmet>20.&&
      (!sameflav||
	(
	  (njet!=0||dymva1>0.88) &&
	  (njet!=1||dymva1>0.84) &&
	  (njet==0||njet==1||(pfmet>45.0))
	)
      )
     ){;}else{return -1;}
     ****/
  //if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  if (bveto_mu==1){;}else{return -1;}
  if (bveto_ip==1 && nbjettche==0){;}else{return -1;}
  if (ptll>30.){;}else{return -1;}
  /****
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    *****/

  return 1;
}
Int_t HWwBase::CommonCut_Without_ptllCut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>10){;}else{return -1;}
  if (nextra==0){;}else{return -1;}
  if (pfmet>20.){;}else{return -1;}
  if (mll>12.){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /****
  if (mpmet>20.&&
      (!sameflav||
	(
	  (njet!=0||dymva1>0.88) &&
	  (njet!=1||dymva1>0.84) &&
	  (njet==0||njet==1||(pfmet>45.0))
	)
      )
     ){;}else{return -1;}
     *****/
  //if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  if (bveto_mu==1){;}else{return -1;}
  if (bveto_ip==1 && nbjettche==0){;}else{return -1;}
  //if (ptll>30.){;}else{return -1;}
  /****
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    ******/

  return 1;
}
Int_t HWwBase::CommonCut_Without_mpmetCut()
{
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>10){;}else{return -1;}
  if (nextra==0){;}else{return -1;}
  if (pfmet>20.){;}else{return -1;}
  if (mll>12.){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  //if (mpmet>20.&&
  /*****
  if (!sameflav||
	(
	  (njet!=0||dymva1>0.88) &&
	  (njet!=1||dymva1>0.84) &&
	  (njet==0||njet==1||(pfmet>45.0))
	)
      //)
     ){;}else{return -1;}
     *****/
  //if( njet == 0 ||  njet ==1 || (dphilljetjet < PI/180.*165 || !sameflav)){;}else{ return -1;}
  if (bveto_mu==1){;}else{return -1;}
  if (bveto_ip==1 && nbjettche==0){;}else{return -1;}
  if (ptll>30.){;}else{return -1;}
  /******
  if(!sameflav ||
      (
        //(njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        //(njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    *****/

  return 1;
}
Int_t HWwBase::LooseCut()
{
  if (isSTA1 == 0 && isSTA2 == 0 && pt1>17 && pt2>8){;}else{return -1;} //These cuts are applied to gg2vv nTuple
  //if (isSTA1 == 0 && isSTA2 == 0 && pt1>20 && pt2>10){;}else{return -1;}
  return 1;
}
//njet Study
Int_t HWwBase::CommonCut_njet()
{
  //if (!sameflav){;}else{return -1;}
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>20){;}else{return -1;}
  if (mll>12.){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /*******
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    ******/
  if(njet==0 || njet==1 || (njet >= 2 && njet <= 3 && (jetpt3 <= 30 || !(jetpt3 > 30 && ( (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))){;}else{return -1;}
  if ((nextra==0) * (bveto_mu && bveto_ip && nbjettche==0)){;}else{return -1;}

  return 1;
}
//njet Study
Int_t HWwBase::CommonCut_VBFnjet()
{
  //if (!sameflav){;}else{return -1;}
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>20){;}else{return -1;}
  if (mll>12.){;}else{return -1;}
  if (mjj>300){;}else{return -1;}
  if(njet>=2 && njet<=3){;}else return -1; 
  //if( mjj>500){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /*******
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    ******/
  //if(njet==0 || njet==1 || (njet >= 2 && njet <= 3 && (jetpt3 <= 30 || !(jetpt3 > 30 && ( (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))){;}else{return -1;}
  if ((nextra==0) * (bveto_mu && bveto_ip && nbjettche==0)){;}else{return -1;}
  if(ptll>45){;}else return -1;
  //if(njet>=3){;}else return -1; 
  if(njet==3)
  {
    if(jetpt3<=30 || !(jetpt3 > 30 && ( (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))){;}
    else return -1;
  }
  if(njet>=2)
  {
    if(abs(eta1 - (jeteta1+jeteta2)/2)/detajj < 0.5 && abs(eta2 - (jeteta1+jeteta2)/2)/detajj < 0.5){;}else return -1;
  }
  if(detajj>2.5){;}else return -1;

  return 1;
}
Int_t HWwBase::CommonCut_VBf_NoVetoCentralJet()
{
  //if (!sameflav){;}else{return -1;}
  if (ch1*ch2 ==-1.){;}else{return -1;}
  if (trigger==1.){;}else{return -1;}
  if (pt1>20 && pt2>20){;}else{return -1;}
  if (mll>12.){;}else{return -1;}
  if (mjj>300){;}else{return -1;}
  //if (zveto==1 || !sameflav){;}else{return -1;}
  /*******
  if(!sameflav ||
      (
        (njet != 0 || dymva1 > 0.88 || mpmet> 35) &&
        (njet != 1 || dymva1 > 0.84 || mpmet> 35) &&
        (njet != 0 || dymva1 > 0.88) &&
        (njet != 1 || dymva1 > 0.84) &&
	(njet==0 || njet==1 || (pfmet > 45.0))
      )
    ){;}else{return -1;}
    ******/
  //if(njet==0 || njet==1 || (njet >= 2 && njet <= 3 && (jetpt3 <= 30 || !(jetpt3 > 30 && ( (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))){;}else{return -1;}
  if ((nextra==0) * (bveto_mu && bveto_ip && nbjettche==0)){;}else{return -1;}
  if (njet>=2){;}else{return -1;}
  if(((njet>=2)*(ptll>45 && abs(eta1 - (jeteta1+jeteta2)/2)/detajj < 0.5 && abs(eta2 - (jeteta1+jeteta2)/2)/detajj < 0.5 && detajj>2.5 && mjj>500))){;}else{return -1;}

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
    if(njet == 0)evtWeight *= 1.0364;
    if(njet == 1)evtWeight *= 0.84151;
  }else if(SampleName == "Top")
  {
    evtWeight = puW*baseW*effW*triggW*LumiW;
    if(njet == 0)evtWeight *= 1.01264;
    if(njet == 1)evtWeight *= 1.11272;
  }else if(SampleName == "DYll")
  {
    //evtWeight = puW*baseW*effW*triggW*sameflav*LumiW;
    if(njet == 0) evtWeight *= 6.98418;
    if(njet == 1) evtWeight *= 3.73978;
  }else if(SampleName == "DYtt")
  {
    //evtWeight = puW*baseW*effW*triggW*(!sameflav)*LumiW;
  }else if(SampleName == "VV")
  {
    evtWeight = puW*baseW*effW*triggW*(1+0.5*(dataset>=82&&dataset<=84))*LumiW;
  }else if(SampleName == "VVV")
  {
    evtWeight = puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "H125" || SampleName == "POWHEG" ||  SampleName == "POWHEG_VBF")
  {
    evtWeight = puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "gg2vvHw1SigOnPeak" || SampleName == "gg2vvHw1SigShoulder" || SampleName == "gg2vvHw1SigTail")
  {
    evtWeight = 2.1*puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "gg2vvHw1IntOnPeak" || SampleName == "gg2vvHw1IntShoulder" || SampleName == "gg2vvHw1IntTail")
  {
    evtWeight = puW*baseW*effW*triggW*LumiW;
    if(njet == 0)evtWeight *= 13.3258/5.85323;  //njet Study: comment out this line 
    if(njet == 1)evtWeight *= 5.78547/1.40855;  //njet Study: comment out this line
    if(njet == 2)evtWeight *= 1.79911/0.195922; //njet Study: comment out this line
  }else if(SampleName == "gg2vvHw25CotHead" || SampleName == "gg2vvHw25CotTail")
  {
    evtWeight = 2.1*puW*baseW*effW*triggW*LumiW;
  }else if(SampleName == "gg2vvHw1Sig8TeV" || SampleName == "gg2vvHw1Int8TeV" || SampleName == "gg2vvHw25Cot8TeV")
  {
    evtWeight = 2.1*puW*baseW*effW*triggW*LumiW; //Coeff. 2.1 is NLO/LO K-Factor
  }else if(SampleName == "gg2vvHw25Sig8TeV" || SampleName == "gg2vvHw25Int8TeV" || SampleName == "gg2vvHw25Cot8TeV")
  {
    evtWeight = 2.1*puW*baseW*effW*triggW*LumiW; //Coeff. 2.1 is NLO/LO K-Factor
  }else if(SampleName == "phantom" || SampleName == "phantom_1SM" || SampleName == "phantom_9SM" || SampleName == "phantom_25SM")
  {
    //cout<<SampleName<<endl;
    evtWeight = puW*baseW*effW*triggW*LumiW*( 0.125*( (dataset == 160) || (dataset == 169) || (dataset == 176) || (dataset == 172)) - 0.250*( (dataset == 161) || (dataset == 175) || (dataset == 173) || (dataset == 170)) + 0.125*( (dataset == 162) || (dataset == 171) || (dataset == 174) || (dataset == 177)));
  }
  return evtWeight;
}
double HWwBase::CalcmWW()
{
  TLorentzVector mu_TL;
  TLorentzVector el_TL;
  TLorentzVector nu1_TL;
  TLorentzVector nu2_TL;
  TLorentzVector Lepton4_TL;
  double mHiggs(0);
  /****************
  
  if((leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon) || (leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron))
  {
    if((neutrinoGenpid1 == GenType::keNeutrino && neutrinoGenpid2 == GenType::kmuNeutrino) || (neutrinoGenpid1 == GenType::kmuNeutrino && neutrinoGenpid2 == GenType::keNeutrino))
    {
      if(leptonGenpid1 == int(GenType::kMuon) && leptonGenpid2 == int(GenType::kElectron))
      {
	mu_TL.SetPtEtaPhiM(leptonGenpt1, leptonGeneta1, leptonGenphi1, GenType::M_mu);
	el_TL.SetPtEtaPhiM(leptonGenpt2, leptonGeneta2, leptonGenphi2, GenType::M_ele);
      }else if(leptonGenpid1 == int(GenType::kElectron) && leptonGenpid2 == int(GenType::kMuon))
      {
	el_TL.SetPtEtaPhiM(leptonGenpt1, leptonGeneta1, leptonGenphi1, GenType::M_ele);
	mu_TL.SetPtEtaPhiM(leptonGenpt2, leptonGeneta2, leptonGenphi2, GenType::M_mu);
      }
      
      nu1_TL.SetPtEtaPhiM(neutrinoGenpt1, neutrinoGeneta1, neutrinoGenphi1, 0.0);
      nu2_TL.SetPtEtaPhiM(neutrinoGenpt2, neutrinoGeneta2, neutrinoGenphi2, 0.0);
      Lepton4_TL = mu_TL + el_TL + nu1_TL + nu2_TL;
      mHiggs = Lepton4_TL.M();
    }else{
      cout<<"Strange Higgs mass!"<<endl;
      exit(-1);
    }
  }
  ******/
  return mHiggs;
}
