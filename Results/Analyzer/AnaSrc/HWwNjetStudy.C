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
    {
      mWW = MHiggs; // Activate mWW at HWwBase.h
    }
    if(SampleName == "SHERPA")mWW = CalcmWW();

    if(mWW <= 130.) continue;

    EvtWeight = CalcWeight();
    
    if(SampleName == "POWHEG")
    {
      //Step1 reweighting Powheg to gg2VV
      if(mWW > 130 && mWW <= 140)WevtPow2Gen= EvtWeight *0;
      if(mWW > 140 && mWW <= 150)WevtPow2Gen= EvtWeight *51.1303;
      if(mWW > 150 && mWW <= 160)WevtPow2Gen= EvtWeight *0.0478779;
      if(mWW > 160 && mWW <= 170)WevtPow2Gen= EvtWeight *0.122384;
      if(mWW > 170 && mWW <= 180)WevtPow2Gen= EvtWeight *0.148526;
      if(mWW > 180 && mWW <= 190)WevtPow2Gen= EvtWeight *0.189493;
      if(mWW > 190 && mWW <= 200)WevtPow2Gen= EvtWeight *0.23596;
      if(mWW > 200 && mWW <= 210)WevtPow2Gen= EvtWeight *0.48091;
      if(mWW > 210 && mWW <= 220)WevtPow2Gen= EvtWeight *19.4147;
      if(mWW > 220 && mWW <= 230)WevtPow2Gen= EvtWeight *22.3205;
      if(mWW > 230 && mWW <= 240)WevtPow2Gen= EvtWeight *7.22016;
      if(mWW > 240 && mWW <= 250)WevtPow2Gen= EvtWeight *0.62342;
      if(mWW > 250 && mWW <= 260)WevtPow2Gen= EvtWeight *0.613474;
      if(mWW > 260 && mWW <= 270)WevtPow2Gen= EvtWeight *5.97016;
      if(mWW > 270 && mWW <= 280)WevtPow2Gen= EvtWeight *7.93497;
      if(mWW > 280 && mWW <= 290)WevtPow2Gen= EvtWeight *4.19944;
      if(mWW > 290 && mWW <= 300)WevtPow2Gen= EvtWeight *0.769442;
      if(mWW > 300 && mWW <= 310)WevtPow2Gen= EvtWeight *0.757447;
      if(mWW > 310 && mWW <= 320)WevtPow2Gen= EvtWeight *5.3415;
      if(mWW > 320 && mWW <= 330)WevtPow2Gen= EvtWeight *10.2543;
      if(mWW > 330 && mWW <= 340)WevtPow2Gen= EvtWeight *15.1817;
      if(mWW > 340 && mWW <= 350)WevtPow2Gen= EvtWeight *15.8538;
      if(mWW > 350 && mWW <= 360)WevtPow2Gen= EvtWeight *16.8142;
      if(mWW > 360 && mWW <= 370)WevtPow2Gen= EvtWeight *12.5228;
      if(mWW > 370 && mWW <= 380)WevtPow2Gen= EvtWeight *7.53283;
      if(mWW > 380 && mWW <= 390)WevtPow2Gen= EvtWeight *4.15059;
      if(mWW > 390 && mWW <= 400)WevtPow2Gen= EvtWeight *2.46605;
      if(mWW > 400 && mWW <= 410)WevtPow2Gen= EvtWeight *2.79782;
      if(mWW > 410 && mWW <= 420)WevtPow2Gen= EvtWeight *4.55461;
      if(mWW > 420 && mWW <= 430)WevtPow2Gen= EvtWeight *6.92859;
      if(mWW > 430 && mWW <= 440)WevtPow2Gen= EvtWeight *10.0075;
      if(mWW > 440 && mWW <= 450)WevtPow2Gen= EvtWeight *10.9316;
      if(mWW > 450 && mWW <= 460)WevtPow2Gen= EvtWeight *10.983;
      if(mWW > 460 && mWW <= 470)WevtPow2Gen= EvtWeight *10.5683;
      if(mWW > 470 && mWW <= 480)WevtPow2Gen= EvtWeight *7.84492;
      if(mWW > 480 && mWW <= 490)WevtPow2Gen= EvtWeight *6.04171;
      if(mWW > 490 && mWW <= 500)WevtPow2Gen= EvtWeight *6.34104;
      if(mWW > 500 && mWW <= 510)WevtPow2Gen= EvtWeight *5.87117;
      if(mWW > 510 && mWW <= 520)WevtPow2Gen= EvtWeight *7.04725;
      if(mWW > 520 && mWW <= 530)WevtPow2Gen= EvtWeight *8.05815;
      if(mWW > 530 && mWW <= 540)WevtPow2Gen= EvtWeight *9.74238;
      if(mWW > 540 && mWW <= 550)WevtPow2Gen= EvtWeight *10.8453;
      if(mWW > 550 && mWW <= 560)WevtPow2Gen= EvtWeight *9.67099;
      if(mWW > 560 && mWW <= 570)WevtPow2Gen= EvtWeight *10.8926;
      if(mWW > 570 && mWW <= 580)WevtPow2Gen= EvtWeight *10.4321;
      if(mWW > 580 && mWW <= 590)WevtPow2Gen= EvtWeight *10.7205;
      if(mWW > 590 && mWW <= 600)WevtPow2Gen= EvtWeight *10.8797;
      if(mWW > 600 && mWW <= 610)WevtPow2Gen= EvtWeight *11.4627;
      if(mWW > 610 && mWW <= 620)WevtPow2Gen= EvtWeight *10.0712;
      if(mWW > 620 && mWW <= 630)WevtPow2Gen= EvtWeight *10.759;
      if(mWW > 630 && mWW <= 640)WevtPow2Gen= EvtWeight *12.9894;
      if(mWW > 640 && mWW <= 650)WevtPow2Gen= EvtWeight *15.5317;
      if(mWW > 650 && mWW <= 660)WevtPow2Gen= EvtWeight *20.0885;
      if(mWW > 660 && mWW <= 670)WevtPow2Gen= EvtWeight *18.7505;
      if(mWW > 670 && mWW <= 680)WevtPow2Gen= EvtWeight *19.5823;
      if(mWW > 680 && mWW <= 690)WevtPow2Gen= EvtWeight *18.7507;
      if(mWW > 690 && mWW <= 700)WevtPow2Gen= EvtWeight *24.2711;
      if(mWW > 700 && mWW <= 710)WevtPow2Gen= EvtWeight *27.1249;
      if(mWW > 710 && mWW <= 720)WevtPow2Gen= EvtWeight *26.0178;
      if(mWW > 720 && mWW <= 730)WevtPow2Gen= EvtWeight *30.3208;
      if(mWW > 730 && mWW <= 740)WevtPow2Gen= EvtWeight *42.7271;
      if(mWW > 740 && mWW <= 750)WevtPow2Gen= EvtWeight *28.9253;
      if(mWW > 750 && mWW <= 760)WevtPow2Gen= EvtWeight *31.6985;
      if(mWW > 760 && mWW <= 770)WevtPow2Gen= EvtWeight *43.9006;
      if(mWW > 770 && mWW <= 780)WevtPow2Gen= EvtWeight *43.8016;
      if(mWW > 780 && mWW <= 790)WevtPow2Gen= EvtWeight *32.9426;
      if(mWW > 790 && mWW <= 800)WevtPow2Gen= EvtWeight *60.615;
      if(mWW > 800 && mWW <= 810)WevtPow2Gen= EvtWeight *32.0942;
      if(mWW > 810 && mWW <= 820)WevtPow2Gen= EvtWeight *28.3471;
      if(mWW > 820 && mWW <= 830)WevtPow2Gen= EvtWeight *44.8383;
      if(mWW > 830 && mWW <= 840)WevtPow2Gen= EvtWeight *31.2978;
      if(mWW > 840 && mWW <= 850)WevtPow2Gen= EvtWeight *41.6292;
      if(mWW > 850 && mWW <= 860)WevtPow2Gen= EvtWeight *55.7313;
      if(mWW > 860 && mWW <= 870)WevtPow2Gen= EvtWeight *37.3944;
      if(mWW > 870 && mWW <= 880)WevtPow2Gen= EvtWeight *45.1447;
      if(mWW > 880 && mWW <= 890)WevtPow2Gen= EvtWeight *45.2296;
      if(mWW > 890 && mWW <= 900)WevtPow2Gen= EvtWeight *55.7684;
      if(mWW > 900 && mWW <= 910)WevtPow2Gen= EvtWeight *62.7376;
      if(mWW > 910 && mWW <= 920)WevtPow2Gen= EvtWeight *55.7921;
      if(mWW > 920 && mWW <= 930)WevtPow2Gen= EvtWeight *54.3934;
      if(mWW > 930 && mWW <= 940)WevtPow2Gen= EvtWeight *102.145;
      if(mWW > 940 && mWW <= 950)WevtPow2Gen= EvtWeight *37.2144;
      if(mWW > 950 && mWW <= 960)WevtPow2Gen= EvtWeight *50.58;
      if(mWW > 960 && mWW <= 970)WevtPow2Gen= EvtWeight *44.3337;
      if(mWW > 970 && mWW <= 980)WevtPow2Gen= EvtWeight *60.3516;
      if(mWW > 980 && mWW <= 990)WevtPow2Gen= EvtWeight *74.0306;
      if(mWW > 990 && mWW <= 1000)WevtPow2Gen= EvtWeight *67.2666;
      if(mWW > 1000 && mWW <= 1010)WevtPow2Gen= EvtWeight *19.5773;
      if(mWW > 1010 && mWW <= 1020)WevtPow2Gen= EvtWeight *66.0482;
      if(mWW > 1020 && mWW <= 1030)WevtPow2Gen= EvtWeight *73.4724;
      if(mWW > 1030 && mWW <= 1040)WevtPow2Gen= EvtWeight *44.6105;
      if(mWW > 1040 && mWW <= 1050)WevtPow2Gen= EvtWeight *95.411;
      if(mWW > 1050 && mWW <= 1060)WevtPow2Gen= EvtWeight *81.114;
      if(mWW > 1060 && mWW <= 1070)WevtPow2Gen= EvtWeight *42.0407;
      if(mWW > 1070 && mWW <= 1080)WevtPow2Gen= EvtWeight *116.167;
      if(mWW > 1080 && mWW <= 1090)WevtPow2Gen= EvtWeight *118.585;
      if(mWW > 1090 && mWW <= 1100)WevtPow2Gen= EvtWeight *50.1939;
      if(mWW > 1100 && mWW <= 1110)WevtPow2Gen= EvtWeight *81.9378;
      if(mWW > 1110 && mWW <= 1120)WevtPow2Gen= EvtWeight *50.4567;
      if(mWW > 1120 && mWW <= 1130)WevtPow2Gen= EvtWeight *70.9683;
      if(mWW > 1130 && mWW <= 1140)WevtPow2Gen= EvtWeight *18.4721;
      if(mWW > 1140 && mWW <= 1150)WevtPow2Gen= EvtWeight *53.0915;
      if(mWW > 1150 && mWW <= 1160)WevtPow2Gen= EvtWeight *47.0092;
      if(mWW > 1160 && mWW <= 1170)WevtPow2Gen= EvtWeight *42.3676;
      if(mWW > 1170 && mWW <= 1180)WevtPow2Gen= EvtWeight *53.8578;
      if(mWW > 1180 && mWW <= 1190)WevtPow2Gen= EvtWeight *142.918;
      if(mWW > 1190 && mWW <= 1200)WevtPow2Gen= EvtWeight *43.5121;
      if(mWW > 1200 && mWW <= 1210)WevtPow2Gen= EvtWeight *64.1233;
      if(mWW > 1210 && mWW <= 1220)WevtPow2Gen= EvtWeight *18.6497;
      if(mWW > 1220 && mWW <= 1230)WevtPow2Gen= EvtWeight *148.524;
      if(mWW > 1230 && mWW <= 1240)WevtPow2Gen= EvtWeight *53.3047;
      if(mWW > 1240 && mWW <= 1250)WevtPow2Gen= EvtWeight *174.73;
      if(mWW > 1250 && mWW <= 1260)WevtPow2Gen= EvtWeight *82.8151;
      if(mWW > 1260 && mWW <= 1270)WevtPow2Gen= EvtWeight *76.0686;
      if(mWW > 1270 && mWW <= 1280)WevtPow2Gen= EvtWeight *224.172;
      if(mWW > 1280 && mWW <= 1290)WevtPow2Gen= EvtWeight *95.0422;
      if(mWW > 1290 && mWW <= 1300)WevtPow2Gen= EvtWeight *140.862;
      if(mWW > 1300 && mWW <= 1310)WevtPow2Gen= EvtWeight *332.692;
      if(mWW > 1310 && mWW <= 1320)WevtPow2Gen= EvtWeight *122.033;
      if(mWW > 1320 && mWW <= 1330)WevtPow2Gen= EvtWeight *300.629;
      if(mWW > 1330 && mWW <= 1340)WevtPow2Gen= EvtWeight *84.3002;
      if(mWW > 1340 && mWW <= 1350)WevtPow2Gen= EvtWeight *0;
      if(mWW > 1350 && mWW <= 1360)WevtPow2Gen= EvtWeight *0;
      if(mWW > 1360 && mWW <= 1370)WevtPow2Gen= EvtWeight *303.616;
      if(mWW > 1370 && mWW <= 1380)WevtPow2Gen= EvtWeight *88.6832;
      if(mWW > 1380 && mWW <= 1390)WevtPow2Gen= EvtWeight *47.9035;
      if(mWW > 1390 && mWW <= 1400)WevtPow2Gen= EvtWeight *3160.08;
      if(mWW > 1400 && mWW <= 1410)WevtPow2Gen= EvtWeight *0;
      if(mWW > 1410 && mWW <= 1420)WevtPow2Gen= EvtWeight *0;
      if(mWW > 1420 && mWW <= 1430)WevtPow2Gen= EvtWeight *259.887;
      if(mWW > 1430 && mWW <= 1440)WevtPow2Gen= EvtWeight *147.746;
      if(mWW > 1440 && mWW <= 1450)WevtPow2Gen= EvtWeight *0;
      if(mWW > 1450 && mWW <= 1460)WevtPow2Gen= EvtWeight *0;
      if(mWW > 1460 && mWW <= 1470)WevtPow2Gen= EvtWeight *0;
      if(mWW > 1470 && mWW <= 1480)WevtPow2Gen= EvtWeight *134.284;
      if(mWW > 1480 && mWW <= 1490)WevtPow2Gen= EvtWeight *0;
      if(mWW >= 1490)              WevtPow2Gen= EvtWeight *0;
    }
    if(SampleName == "POWHEG_VBF")
    {
      //if(mWW <= 130)               WevtPow2Gen= EvtWeight *0;
      //if(mWW > 130 && mWW <= 200)  WevtPow2Gen= EvtWeight *0.153388;
      //if(mWW > 200 && mWW <= 300)  WevtPow2Gen= EvtWeight *1.78492;
      //if(mWW > 300 && mWW <= 400)  WevtPow2Gen= EvtWeight *2.15192;
      //if(mWW > 400 && mWW <= 500)  WevtPow2Gen= EvtWeight *3.29945;
      //if(mWW > 500 && mWW <= 600)  WevtPow2Gen= EvtWeight *5.25967;
      //if(mWW > 600 && mWW <= 700)  WevtPow2Gen= EvtWeight *10.6058;
      //if(mWW > 700 && mWW <= 800)  WevtPow2Gen= EvtWeight *18.1124;
      //if(mWW > 800 && mWW <= 900)  WevtPow2Gen= EvtWeight *22.0678;
      //if(mWW > 900 && mWW <= 1000) WevtPow2Gen= EvtWeight *36.0357;
      //if(mWW > 1000 && mWW <= 1250)WevtPow2Gen= EvtWeight *77.5059;
      //if(mWW > 1250 && mWW <= 1500)WevtPow2Gen= EvtWeight *234.308;
      //
      //
      //
      //
      if(             mWW <= 100)  WevtPow2Gen= EvtWeight *0;
      if(mWW > 100 && mWW <= 150)  WevtPow2Gen= EvtWeight *0.0378106;
      if(mWW > 150 && mWW <= 200)  WevtPow2Gen= EvtWeight *0.193764;
      if(mWW > 200 && mWW <= 250)  WevtPow2Gen= EvtWeight *1.91155;
      if(mWW > 250 && mWW <= 300)  WevtPow2Gen= EvtWeight *1.61777;
      if(mWW > 300 && mWW <= 350)  WevtPow2Gen= EvtWeight *1.91598;
      if(mWW > 350 && mWW <= 400)  WevtPow2Gen= EvtWeight *2.46773;
      if(mWW > 400 && mWW <= 450)  WevtPow2Gen= EvtWeight *3.14148;
      if(mWW > 450 && mWW <= 500)  WevtPow2Gen= EvtWeight *3.51853;
      if(mWW > 500 && mWW <= 550)  WevtPow2Gen= EvtWeight *5.0784;
      if(mWW > 550 && mWW <= 600)  WevtPow2Gen= EvtWeight *5.52486;
      if(mWW > 600 && mWW <= 650)  WevtPow2Gen= EvtWeight *9.09672;
      if(mWW > 650 && mWW <= 700)  WevtPow2Gen= EvtWeight *13.028;
      if(mWW > 700 && mWW <= 750)  WevtPow2Gen= EvtWeight *16.6288;
      if(mWW > 750 && mWW <= 800)  WevtPow2Gen= EvtWeight *20.2633;
      if(mWW > 800 && mWW <= 850)  WevtPow2Gen= EvtWeight *21.7923;
      if(mWW > 850 && mWW <= 900)  WevtPow2Gen= EvtWeight *22.4597;
      if(mWW > 900 && mWW <= 950)  WevtPow2Gen= EvtWeight *29.4206;
      if(mWW > 950 && mWW <= 1000) WevtPow2Gen= EvtWeight *45.3205;
      if(mWW > 1000 && mWW <= 1050)WevtPow2Gen= EvtWeight *58.3006;
      if(mWW > 1050 && mWW <= 1100)WevtPow2Gen= EvtWeight *68.2147;
      if(mWW > 1100 && mWW <= 1150)WevtPow2Gen= EvtWeight *79.023;
      if(mWW > 1150 && mWW <= 1200)WevtPow2Gen= EvtWeight *117.26;
      if(mWW > 1200 && mWW <= 1250)WevtPow2Gen= EvtWeight *129.333;
      if(mWW > 1250 && mWW <= 1300)WevtPow2Gen= EvtWeight *166.973;
      if(mWW > 1300 && mWW <= 1350)WevtPow2Gen= EvtWeight *141.288;
      if(mWW > 1350 && mWW <= 1400)WevtPow2Gen= EvtWeight *289.653;
      if(mWW > 1400 && mWW <= 1450)WevtPow2Gen= EvtWeight *393.112;
      if(mWW > 1450 && mWW <= 1500)WevtPow2Gen= EvtWeight *428.126;
      //
      //
      //
    }

    if( Cut == "CommonCut_njet")if(CommonCut_njet() !=1)continue;
    if( Cut == "CommonCut_VBFnjet")if(CommonCut_VBFnjet() !=1)continue;

    if( Cut == "CommonCut_njet")
    {
      nnjet = njet;
      if(njet>=2) nnjet = 2;
      Fill_Histo();
    }
    if( Cut == "CommonCut_VBFnjet")
    {
      nnjet = njet;
      if(njet>=3) nnjet = 3;
      Fill_Histo();
    }
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
  if(mWW>130)
  {
    h1_njet_Off_Wevt[11] 	-> Fill(nnjet,EvtWeight);
    h1_njet_Off_WevtPow2Gen[11]	-> Fill(nnjet,WevtPow2Gen);
    h1_njet_Off_noWeight[11]	-> Fill(nnjet);
  }
  for(int iBin(0);iBin<11;iBin++){
    if(mWW > mWWBins[iBin] && mWW <= mWWBins[iBin+1])
    {
      h1_njet_Off_Wevt[iBin] 		-> Fill(nnjet,EvtWeight);
      h1_njet_Off_WevtPow2Gen[iBin] 	-> Fill(nnjet,WevtPow2Gen);
      h1_njet_Off_noWeight[iBin]	-> Fill(nnjet);
    }
  }
  
  h1_mWW_Off_Wevt[4] 		-> Fill(mWW, EvtWeight);
  h1_mWW_Off_WevtPow2Gen[4] 	-> Fill(mWW, WevtPow2Gen);
  h1_mWW_Off_noWeight[4]	-> Fill(mWW);
  h1_mjj[4]			-> Fill(mjj,    WevtPow2Gen);
  h1_detajj[4]			-> Fill(detajj, WevtPow2Gen);
  
  if(nnjet==0){
    h1_mWW_Off_Wevt[0]		-> Fill(mWW, EvtWeight);
    h1_mWW_Off_WevtPow2Gen[0]	-> Fill(mWW, WevtPow2Gen);
    h1_mWW_Off_noWeight[0]	-> Fill(mWW);
    h1_mjj[0]			-> Fill(mjj,    WevtPow2Gen);
    h1_detajj[0]		-> Fill(detajj, WevtPow2Gen);
  }else if(nnjet==1){
    h1_mWW_Off_Wevt[1] 		-> Fill(mWW, EvtWeight);
    h1_mWW_Off_WevtPow2Gen[1] 	-> Fill(mWW, WevtPow2Gen);
    h1_mWW_Off_noWeight[1]	-> Fill(mWW);
    h1_mjj[1]			-> Fill(mjj,    WevtPow2Gen);
    h1_detajj[1]		-> Fill(detajj, WevtPow2Gen);
  }else if(nnjet==2){
    h1_mWW_Off_Wevt[2] 		-> Fill(mWW, EvtWeight);
    h1_mWW_Off_WevtPow2Gen[2] 	-> Fill(mWW, WevtPow2Gen);
    h1_mWW_Off_noWeight[2]	-> Fill(mWW);
    h1_mjj[2]			-> Fill(mjj,    WevtPow2Gen);
    h1_detajj[2]		-> Fill(detajj, WevtPow2Gen);
  }else if(nnjet==3){
    h1_mWW_Off_Wevt[3] 		-> Fill(mWW, EvtWeight);
    h1_mWW_Off_WevtPow2Gen[3] 	-> Fill(mWW, WevtPow2Gen);
    h1_mWW_Off_noWeight[3]	-> Fill(mWW);
    h1_mjj[3]			-> Fill(mjj,    WevtPow2Gen);
    h1_detajj[3]		-> Fill(detajj, WevtPow2Gen);
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
    sprintf(histName, "h1_njet_Off_Wevt_%d",i);
    h1_njet_Off_Wevt[i] = new TH1D(histName,"Jet numbers in off-shell", 4, 0, 4);

    sprintf(histName, "h1_njet_Off_WevtPow2Gen_%d",i);
    h1_njet_Off_WevtPow2Gen[i] = new TH1D(histName,"Jet numbers in off-shell", 4, 0, 4);

    sprintf(histName, "h1_njet_Off_noWeight_%d",i);
    h1_njet_Off_noWeight[i] = new TH1D(histName,"Jet numbers in off-shell", 4, 0, 4);
  }


  for(int i(0); i<5; i++)
  {
    sprintf(histName, "h1_mWW_Off_Wevt_%d",i);
    h1_mWW_Off_Wevt[i] = new TH1D(histName,"mWW", 30, 0, 1500);
    //h1_mWW_Off_Wevt[i] = new TH1D(histName,"mWW", 150, 0, 1500); // gg2Vv

    sprintf(histName, "h1_mWW_Off_WevtPow2Gen_%d",i);
    h1_mWW_Off_WevtPow2Gen[i] = new TH1D(histName,"mWW", 30, 0, 1500);

    sprintf(histName, "h1_mWW_Off_noWeight_%d",i);
    h1_mWW_Off_noWeight[i] = new TH1D(histName,"mWW", 30, 0, 1500);
    //h1_mWW_Off_noWeight[i] = new TH1D(histName,"mWW", 150, 0, 1500);


    sprintf(histName, "h1_mjj_%d",i);
    h1_mjj[i] = new TH1D(histName,"mjj", 20, 0, 2000);

    sprintf(histName, "h1_detajj_%d",i);
    h1_detajj[i] = new TH1D(histName,"detajj", 16, 0, 8);
    
    
  }
  return 0;
}
int Write_Histo()
{
  return 0;
}
