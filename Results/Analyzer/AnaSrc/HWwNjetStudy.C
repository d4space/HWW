#define HWwNjetStudy_cxx
#include "HWwNjetStudy.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include <algorithm>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

void HWwNjetStudy::Loop()
{
  gBenchmark->Start("HWwNjetStudy");
  if (fChain == 0) return;

  int Ntries = fChain->GetEntries();
  cout<<"Total: "<<Ntries<<endl;
  Fout<<"Total: "<<Ntries<<endl;
  cout<<"LumiW: "<<LumiW<<endl;
  Fout<<"LumiW: "<<LumiW<<endl;
 
  for (int i(0); i<Ntries;i++)
  {
    InitVar4Evt();
    evtCnt++;
    fChain->GetEntry(i);

    if(SampleName == "POWHEG" || SampleName == "POWHEG_VBF")
      //mWW = MHiggs;
    if(SampleName == "SHERPA")
      mWW = CalcmWW();
    if(mWW <= 130.) continue;

    EvtWeight = CalcWeight();
    
    if(SampleName == "POWHEG")
    {
      //Step1 reweighting Powheg to gg2VV
      if(mWW > 130 && mWW <= 140) EvtWeight *=0;
      if(mWW > 140 && mWW <= 150) EvtWeight *=51.1303;
      if(mWW > 150 && mWW <= 160) EvtWeight *=0.0478779;
      if(mWW > 160 && mWW <= 170) EvtWeight *=0.122384;
      if(mWW > 170 && mWW <= 180) EvtWeight *=0.148526;
      if(mWW > 180 && mWW <= 190) EvtWeight *=0.189493;
      if(mWW > 190 && mWW <= 200) EvtWeight *=0.23596;
      if(mWW > 200 && mWW <= 210) EvtWeight *=0.48091;
      if(mWW > 210 && mWW <= 220) EvtWeight *=19.4147;
      if(mWW > 220 && mWW <= 230) EvtWeight *=22.3205;
      if(mWW > 230 && mWW <= 240) EvtWeight *=7.22016;
      if(mWW > 240 && mWW <= 250) EvtWeight *=0.62342;
      if(mWW > 250 && mWW <= 260) EvtWeight *=0.613474;
      if(mWW > 260 && mWW <= 270) EvtWeight *=5.97016;
      if(mWW > 270 && mWW <= 280) EvtWeight *=7.93497;
      if(mWW > 280 && mWW <= 290) EvtWeight *=4.19944;
      if(mWW > 290 && mWW <= 300) EvtWeight *=0.769442;
      if(mWW > 300 && mWW <= 310) EvtWeight *=0.757447;
      if(mWW > 310 && mWW <= 320) EvtWeight *=5.3415;
      if(mWW > 320 && mWW <= 330) EvtWeight *=10.2543;
      if(mWW > 330 && mWW <= 340) EvtWeight *=15.1817;
      if(mWW > 340 && mWW <= 350) EvtWeight *=15.8538;
      if(mWW > 350 && mWW <= 360) EvtWeight *=16.8142;
      if(mWW > 360 && mWW <= 370) EvtWeight *=12.5228;
      if(mWW > 370 && mWW <= 380) EvtWeight *=7.53283;
      if(mWW > 380 && mWW <= 390) EvtWeight *=4.15059;
      if(mWW > 390 && mWW <= 400) EvtWeight *=2.46605;
      if(mWW > 400 && mWW <= 410) EvtWeight *=2.79782;
      if(mWW > 410 && mWW <= 420) EvtWeight *=4.55461;
      if(mWW > 420 && mWW <= 430) EvtWeight *=6.92859;
      if(mWW > 430 && mWW <= 440) EvtWeight *=10.0075;
      if(mWW > 440 && mWW <= 450) EvtWeight *=10.9316;
      if(mWW > 450 && mWW <= 460) EvtWeight *=10.983;
      if(mWW > 460 && mWW <= 470) EvtWeight *=10.5683;
      if(mWW > 470 && mWW <= 480) EvtWeight *=7.84492;
      if(mWW > 480 && mWW <= 490) EvtWeight *=6.04171;
      if(mWW > 490 && mWW <= 500) EvtWeight *=6.34104;
      if(mWW > 500 && mWW <= 510) EvtWeight *=5.87117;
      if(mWW > 510 && mWW <= 520) EvtWeight *=7.04725;
      if(mWW > 520 && mWW <= 530) EvtWeight *=8.05815;
      if(mWW > 530 && mWW <= 540) EvtWeight *=9.74238;
      if(mWW > 540 && mWW <= 550) EvtWeight *=10.8453;
      if(mWW > 550 && mWW <= 560) EvtWeight *=9.67099;
      if(mWW > 560 && mWW <= 570) EvtWeight *=10.8926;
      if(mWW > 570 && mWW <= 580) EvtWeight *=10.4321;
      if(mWW > 580 && mWW <= 590) EvtWeight *=10.7205;
      if(mWW > 590 && mWW <= 600) EvtWeight *=10.8797;
      if(mWW > 600 && mWW <= 610) EvtWeight *=11.4627;
      if(mWW > 610 && mWW <= 620) EvtWeight *=10.0712;
      if(mWW > 620 && mWW <= 630) EvtWeight *=10.759;
      if(mWW > 630 && mWW <= 640) EvtWeight *=12.9894;
      if(mWW > 640 && mWW <= 650) EvtWeight *=15.5317;
      if(mWW > 650 && mWW <= 660) EvtWeight *=20.0885;
      if(mWW > 660 && mWW <= 670) EvtWeight *=18.7505;
      if(mWW > 670 && mWW <= 680) EvtWeight *=19.5823;
      if(mWW > 680 && mWW <= 690) EvtWeight *=18.7507;
      if(mWW > 690 && mWW <= 700) EvtWeight *=24.2711;
      if(mWW > 700 && mWW <= 710) EvtWeight *=27.1249;
      if(mWW > 710 && mWW <= 720) EvtWeight *=26.0178;
      if(mWW > 720 && mWW <= 730) EvtWeight *=30.3208;
      if(mWW > 730 && mWW <= 740) EvtWeight *=42.7271;
      if(mWW > 740 && mWW <= 750) EvtWeight *=28.9253;
      if(mWW > 750 && mWW <= 760) EvtWeight *=31.6985;
      if(mWW > 760 && mWW <= 770) EvtWeight *=43.9006;
      if(mWW > 770 && mWW <= 780) EvtWeight *=43.8016;
      if(mWW > 780 && mWW <= 790) EvtWeight *=32.9426;
      if(mWW > 790 && mWW <= 800) EvtWeight *=60.615;
      if(mWW > 800 && mWW <= 810) EvtWeight *=32.0942;
      if(mWW > 810 && mWW <= 820) EvtWeight *=28.3471;
      if(mWW > 820 && mWW <= 830) EvtWeight *=44.8383;
      if(mWW > 830 && mWW <= 840) EvtWeight *=31.2978;
      if(mWW > 840 && mWW <= 850) EvtWeight *=41.6292;
      if(mWW > 850 && mWW <= 860) EvtWeight *=55.7313;
      if(mWW > 860 && mWW <= 870) EvtWeight *=37.3944;
      if(mWW > 870 && mWW <= 880) EvtWeight *=45.1447;
      if(mWW > 880 && mWW <= 890) EvtWeight *=45.2296;
      if(mWW > 890 && mWW <= 900) EvtWeight *=55.7684;
      if(mWW > 900 && mWW <= 910) EvtWeight *=62.7376;
      if(mWW > 910 && mWW <= 920) EvtWeight *=55.7921;
      if(mWW > 920 && mWW <= 930) EvtWeight *=54.3934;
      if(mWW > 930 && mWW <= 940) EvtWeight *=102.145;
      if(mWW > 940 && mWW <= 950) EvtWeight *=37.2144;
      if(mWW > 950 && mWW <= 960) EvtWeight *=50.58;
      if(mWW > 960 && mWW <= 970) EvtWeight *=44.3337;
      if(mWW > 970 && mWW <= 980) EvtWeight *=60.3516;
      if(mWW > 980 && mWW <= 990) EvtWeight *=74.0306;
      if(mWW > 990 && mWW <= 1000) EvtWeight *=67.2666;
      if(mWW > 1000 && mWW <= 1010) EvtWeight *=19.5773;
      if(mWW > 1010 && mWW <= 1020) EvtWeight *=66.0482;
      if(mWW > 1020 && mWW <= 1030) EvtWeight *=73.4724;
      if(mWW > 1030 && mWW <= 1040) EvtWeight *=44.6105;
      if(mWW > 1040 && mWW <= 1050) EvtWeight *=95.411;
      if(mWW > 1050 && mWW <= 1060) EvtWeight *=81.114;
      if(mWW > 1060 && mWW <= 1070) EvtWeight *=42.0407;
      if(mWW > 1070 && mWW <= 1080) EvtWeight *=116.167;
      if(mWW > 1080 && mWW <= 1090) EvtWeight *=118.585;
      if(mWW > 1090 && mWW <= 1100) EvtWeight *=50.1939;
      if(mWW > 1100 && mWW <= 1110) EvtWeight *=81.9378;
      if(mWW > 1110 && mWW <= 1120) EvtWeight *=50.4567;
      if(mWW > 1120 && mWW <= 1130) EvtWeight *=70.9683;
      if(mWW > 1130 && mWW <= 1140) EvtWeight *=18.4721;
      if(mWW > 1140 && mWW <= 1150) EvtWeight *=53.0915;
      if(mWW > 1150 && mWW <= 1160) EvtWeight *=47.0092;
      if(mWW > 1160 && mWW <= 1170) EvtWeight *=42.3676;
      if(mWW > 1170 && mWW <= 1180) EvtWeight *=53.8578;
      if(mWW > 1180 && mWW <= 1190) EvtWeight *=142.918;
      if(mWW > 1190 && mWW <= 1200) EvtWeight *=43.5121;
      if(mWW > 1200 && mWW <= 1210) EvtWeight *=64.1233;
      if(mWW > 1210 && mWW <= 1220) EvtWeight *=18.6497;
      if(mWW > 1220 && mWW <= 1230) EvtWeight *=148.524;
      if(mWW > 1230 && mWW <= 1240) EvtWeight *=53.3047;
      if(mWW > 1240 && mWW <= 1250) EvtWeight *=174.73;
      if(mWW > 1250 && mWW <= 1260) EvtWeight *=82.8151;
      if(mWW > 1260 && mWW <= 1270) EvtWeight *=76.0686;
      if(mWW > 1270 && mWW <= 1280) EvtWeight *=224.172;
      if(mWW > 1280 && mWW <= 1290) EvtWeight *=95.0422;
      if(mWW > 1290 && mWW <= 1300) EvtWeight *=140.862;
      if(mWW > 1300 && mWW <= 1310) EvtWeight *=332.692;
      if(mWW > 1310 && mWW <= 1320) EvtWeight *=122.033;
      if(mWW > 1320 && mWW <= 1330) EvtWeight *=300.629;
      if(mWW > 1330 && mWW <= 1340) EvtWeight *=84.3002;
      if(mWW > 1340 && mWW <= 1350) EvtWeight *=0;
      if(mWW > 1350 && mWW <= 1360) EvtWeight *=0;
      if(mWW > 1360 && mWW <= 1370) EvtWeight *=303.616;
      if(mWW > 1370 && mWW <= 1380) EvtWeight *=88.6832;
      if(mWW > 1380 && mWW <= 1390) EvtWeight *=47.9035;
      if(mWW > 1390 && mWW <= 1400) EvtWeight *=3160.08;
      if(mWW > 1400 && mWW <= 1410) EvtWeight *=0;
      if(mWW > 1410 && mWW <= 1420) EvtWeight *=0;
      if(mWW > 1420 && mWW <= 1430) EvtWeight *=259.887;
      if(mWW > 1430 && mWW <= 1440) EvtWeight *=147.746;
      if(mWW > 1440 && mWW <= 1450) EvtWeight *=0;
      if(mWW > 1450 && mWW <= 1460) EvtWeight *=0;
      if(mWW > 1460 && mWW <= 1470) EvtWeight *=0;
      if(mWW > 1470 && mWW <= 1480) EvtWeight *=134.284;
      if(mWW > 1480 && mWW <= 1490) EvtWeight *=0;
      if(mWW >= 1490) EvtWeight *=0;
    }
    if(SampleName == "POWHEG_VBF")
    {
      if(mWW <= 130) EvtWeight *=0;
      if(mWW > 130 && mWW <= 200) EvtWeight *=0.153388;
      if(mWW > 200 && mWW <= 300) EvtWeight *=1.78492;
      if(mWW > 300 && mWW <= 400) EvtWeight *=2.15192;
      if(mWW > 400 && mWW <= 500) EvtWeight *=3.29945;
      if(mWW > 500 && mWW <= 600) EvtWeight *=5.25967;
      if(mWW > 600 && mWW <= 700) EvtWeight *=10.6058;
      if(mWW > 700 && mWW <= 800) EvtWeight *=18.1124;
      if(mWW > 800 && mWW <= 900) EvtWeight *=22.0678;
      if(mWW > 900 && mWW <= 1000) EvtWeight *=36.0357;
      if(mWW > 1000 && mWW <= 1250) EvtWeight *=77.5059;
      if(mWW > 1250 && mWW <= 1500) EvtWeight *=234.308;
    }

    if( Cut == "CommonCut_njet")if(CommonCut_njet() !=1)continue;
    if( Cut == "CommonCut_VBFnjet")if(CommonCut_VBFnjet() !=1)continue;

    if( Cut == "CommonCut_njet") Fill_Histo();
    if( Cut == "CommonCut_VBFnjet") Fill_vbfHisto();
  }
  // Usie one of the Write_Histo ro myFile->Write
  // Write_Histo: to write specific ones
  // myFile->Write ==> All
    
  //Write_Histo();
  myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("HWwNjetStudy");
}
int HWwNjetStudy::Fill_Histo()
{
  double nnjet(0);
  nnjet=njet;
  if(njet>=2)
    nnjet=2;
  
  if(mWW>130)
  {
    h1_njet_OffSh[11] 		-> Fill(nnjet,EvtWeight);
    h1_njet_OffSh_noWeight[11]	-> Fill(nnjet);
  }
  for(int iBin(0);iBin<11;iBin++){
    if(mWW > mWWBins[iBin] && mWW <= mWWBins[iBin+1])
    {
      h1_njet_OffSh[iBin] 		-> Fill(nnjet,EvtWeight);
      h1_njet_OffSh_noWeight[iBin]	-> Fill(nnjet);
    }
  }
  
  h1_mWW_OffSh[3] 		-> Fill(mWW, EvtWeight);
  h1_mWW_OffSh_noWeight[3]	-> Fill(mWW);
  h1_mWWbin_OffSh[3] 		-> Fill(mWW, EvtWeight);
  h1_mWWbin_OffSh_noWeight[3]	-> Fill(mWW);
  h1_mjj[3]			-> Fill(mjj, EvtWeight);
  h1_detajj[3]		-> Fill(detajj, EvtWeight);
  
  if(njet==0){
    h1_mWW_OffSh[0]		-> Fill(mWW, EvtWeight);
    h1_mWW_OffSh_noWeight[0]	-> Fill(mWW);
    h1_mWWbin_OffSh[0]	-> Fill(mWW, EvtWeight);
    h1_mWWbin_OffSh_noWeight[0]-> Fill(mWW);
    h1_mjj[0]			-> Fill(mjj, EvtWeight);
    h1_detajj[0]		-> Fill(detajj, EvtWeight);
  }else if(njet==1){
    h1_mWW_OffSh[1] 		-> Fill(mWW, EvtWeight);
    h1_mWW_OffSh_noWeight[1]	-> Fill(mWW);
    h1_mWWbin_OffSh[1] 	-> Fill(mWW, EvtWeight);
    h1_mWWbin_OffSh_noWeight[1]-> Fill(mWW);
    h1_mjj[1]			-> Fill(mjj, EvtWeight);
    h1_detajj[1]		-> Fill(detajj, EvtWeight);
  }else if(njet>=2){
    h1_mWW_OffSh[2] 		-> Fill(mWW, EvtWeight);
    h1_mWW_OffSh_noWeight[2]	-> Fill(mWW);
    h1_mWWbin_OffSh[2] 	-> Fill(mWW, EvtWeight);
    h1_mWWbin_OffSh_noWeight[2]-> Fill(mWW);
    h1_mjj[2]			-> Fill(mjj, EvtWeight);
    h1_detajj[2]		-> Fill(detajj, EvtWeight);
  }
  return 0;
}
int HWwNjetStudy::Fill_vbfHisto()
{
  double nnjet(0);
  nnjet=njet;
  if(njet>=3)
    nnjet=3;
  
  //Fill mWW, mjj and detajj for each njet
  h1_mww_off_CalcPowRew[4]              -> Fill(mWW,EvtWeight);
  h1_mww_off_CalcPowRew_noWeight[4]     -> Fill(mWW);
  h1_mjj[4]				-> Fill(mjj, EvtWeight);
  h1_detajj[4]				-> Fill(detajj, EvtWeight);

  if(njet==0)
  {
    h1_mww_off_CalcPowRew[0]          	-> Fill(mWW,EvtWeight);
    h1_mww_off_CalcPowRew_noWeight[0] 	-> Fill(mWW);
    h1_mjj[0]				-> Fill(mjj, EvtWeight);
    h1_detajj[0]			-> Fill(detajj, EvtWeight);
  }else if(njet==1)
  {
    h1_mww_off_CalcPowRew[1]          	-> Fill(mWW,EvtWeight);
    h1_mww_off_CalcPowRew_noWeight[1] 	-> Fill(mWW);
    h1_mjj[1]				-> Fill(mjj, EvtWeight);
    h1_detajj[1]			-> Fill(detajj, EvtWeight);
  }else if(njet==2)
  {
    h1_mww_off_CalcPowRew[2]          	-> Fill(mWW,EvtWeight);
    h1_mww_off_CalcPowRew_noWeight[2] 	-> Fill(mWW);
    h1_mjj[2]				-> Fill(mjj, EvtWeight);
    h1_detajj[2]			-> Fill(detajj, EvtWeight);
  }else if(njet>=3)
  {
    h1_mww_off_CalcPowRew[3]          	-> Fill(mWW,EvtWeight);
    h1_mww_off_CalcPowRew_noWeight[3] 	-> Fill(mWW);
    h1_mjj[3]				-> Fill(mjj, EvtWeight);
    h1_detajj[3]			-> Fill(detajj, EvtWeight);
  }

  //Fill njet for each mWW windows
  h1_njet_OffSh[11] 		        -> Fill(nnjet,EvtWeight);
  h1_njet_OffSh_noWeight[11]	        -> Fill(nnjet);
  for(int iBin(0);iBin<11;iBin++){
    if(mWW > mWWBins[iBin] && mWW <= mWWBins[iBin+1])
    {
      h1_njet_OffSh[iBin] 		-> Fill(nnjet,EvtWeight);
      h1_njet_OffSh_noWeight[iBin]	-> Fill(nnjet);
    }
  }
  return 0;
}
int HWwNjetStudy::InitVar()
{
  TString FoutName = mResultDir+"/"+SampleName+"_"+Cut+".txt";
  Fout.open(FoutName);
  evtCnt = 0;
  return 0;
}
int HWwNjetStudy::InitVar4Evt()
{
  return 0;
}
int HWwNjetStudy::InitHistogram()
{
  myFile = new TFile(mResultDir+"/"+SampleName+"_"+Cut+".root","RECREATE");
  char histName[30];
  for(int i(0); i<12; i++)
  {
    sprintf(histName, "h1_njet_OffSh_%d",i);
    h1_njet_OffSh[i] = new TH1D(histName,"Jet numbers in off-shell", 4, 0, 4);

    sprintf(histName, "h1_njet_OffSh_noWeight_%d",i);
    h1_njet_OffSh_noWeight[i] = new TH1D(histName,"Jet numbers in off-shell", 4, 0, 4);
  }

  for(int i(0); i<5; i++)
  {
    sprintf(histName, "h1_mww_off_CalcPowRew_%d",i);
    h1_mww_off_CalcPowRew[i] = new TH1D(histName,"mWW", 11, mWWBins);
    
    sprintf(histName, "h1_mww_off_CalcPowRew_noWeight_%d",i);
    h1_mww_off_CalcPowRew_noWeight[i] = new TH1D(histName,"mWW", 11, mWWBins);
    
    sprintf(histName, "h1_mjj_%d",i);
    h1_mjj[i] = new TH1D(histName,"mjj", 20, 0, 2000);

    sprintf(histName, "h1_detajj_%d",i);
    h1_detajj[i] = new TH1D(histName,"detajj", 16, 0, 8);
  }

  for(int i(0); i<4; i++)
  {
    sprintf(histName, "h1_mWW_OffSh_%d",i);
    h1_mWW_OffSh[i] = new TH1D(histName,"mWW", 150, 0, 1500);
    
    sprintf(histName, "h1_mWWbin_OffSh_%d",i);
    h1_mWWbin_OffSh[i] = new TH1D(histName,"mWW", 11, mWWBins);
    
    sprintf(histName, "h1_mWW_OffSh_noWeight_%d",i);
    h1_mWW_OffSh_noWeight[i] = new TH1D(histName,"mWW", 150, 0, 1500);
    
    sprintf(histName, "h1_mWWbin_OffSh_noWeight_%d",i);
    h1_mWWbin_OffSh_noWeight[i] = new TH1D(histName,"mWW", 11, mWWBins);
  }
  return 0;
}
int Write_Histo()
{
  return 0;
}
