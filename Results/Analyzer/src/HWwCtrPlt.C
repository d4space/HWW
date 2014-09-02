#define HWwCtrPlt_cxx
#include "HWwCtrPlt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include <algorithm>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

void HWwCtrPlt::Loop()
{
  gBenchmark->Start("HWwCtrPlt");
  if (fChain == 0) return;

  int Ntries = fChain->GetEntries();
  cout<<"Total: "<<Ntries<<endl;
  Fout<<"Total: "<<Ntries<<endl;
  cout<<"LumiW: "<<LumiW<<endl;
  
  for (int i(0); i<Ntries;i++)
  //for (int i(0); i<10;i++)
  {
    InitVar4Evt();
    evtCnt++;
    fChain->GetEntry(i);
    if (LooseCut() == 1) ncutLoose++;
    //if(SampleName == "gg2vvHw1SigOnPeak" || SampleName == "gg2vvHw1SigShoulder" || SampleName == "gg2vvHw1SigTail")
    if(SampleName == "gg2vvHw1Sig8TeV" || SampleName == "gg2vvHw1Int8TeV" || SampleName == "gg2vvHw25Cot8TeV")
      mH = CalcmWW();
    if(SampleName == "H125")
      mH = MHiggs;
    if (pt1<=20)ncut1++;
    if (pt2<=10)ncut2++;
    if (nextra!=0)ncut3++;
    if (pfmet<=20)ncut4++;
    if (mll<=12)ncut5++;
    //if (mll<=70)ncut5++;
    if (mpmet<=20)ncut6++;
    if (bveto_mu!=1)ncut7++;
    if (bveto_ip!=1)ncut8++;
    if (nbjettche!=0)ncut9++;
    if (ptll<=30)ncut10++;
    // NT already applied loose cuts
    // select channel
    if (SF0jCut() == 1)     evtChannel = Chan_sf0j;
    else if (OF0jCut() == 1)evtChannel = Chan_of0j;
    else if (SF1jCut() == 1)evtChannel = Chan_sf1j;
    else if (OF1jCut() == 1)evtChannel = Chan_of1j;
    else continue;

    EvtWeight = CalcWeight();
    if(CommonCut_Without_mpmetCut() ==1)
      h1_mpmet_FOM[evtChannel] ->Fill(mpmet,EvtWeight);
    
    if(SampleName == "gg2vvHw1SigOnPeak" || SampleName == "gg2vvHw1SigShoulder" || SampleName == "gg2vvHw1SigTail")if(CommonCut_Without_mll_ptll_Cut() ==1)
    {
      if(OF0jCut() == 1){
	Nmllptll_OF0j[0][0] += EvtWeight;
	for(int imll(1);imll<=60;imll++)
	{
	  if(mll >= mllBins[imll]){
	    for(int iptll(1);iptll<=30;iptll++)
	    {
	      if(ptll >= ptllBins[iptll]) Nmllptll_OF0j[imll][iptll] += EvtWeight;
	    }
	  }
	}
      }else if(OF1jCut() == 1){
	Nmllptll_OF1j[0][0] += EvtWeight;
	for(int imll(1);imll<=60;imll++)
	{
	  if(mll >= mllBins[imll]){
	    for(int iptll(1);iptll<=30;iptll++)
	    {
	      if(ptll >= ptllBins[iptll]) Nmllptll_OF1j[imll][iptll] += EvtWeight;
	    }
	  }
	}
      }
    }

    if( Cut == "LooseCut")if(LooseCut() !=1)continue;
    if( Cut == "CommonCut")if(CommonCut() !=1)continue;
    //EvtWeight = CalcWeight();
    Nselect += EvtWeight;
    if (SF0jCut() == 1)     NselectSF0j += EvtWeight;
    else if (OF0jCut() == 1)NselectOF0j += EvtWeight;
    else if (SF1jCut() == 1)NselectSF1j += EvtWeight;
    else if (OF1jCut() == 1)NselectOF1j += EvtWeight;

    //if(SampleName == "H125" || SampleName == "gg2vvHw1SigOnPeak" || SampleName == "gg2vvHw1SigShoulder" || SampleName == "gg2vvHw1SigTail")
    //{
    //  if(mH>160.)
    //    //if(mll>70.)
    //    {
    //      if (SF0jCut() == 1)     NselectSF0j_OffShell += EvtWeight;
    //      else if (OF0jCut() == 1)NselectOF0j_OffShell += EvtWeight;
    //      else if (SF1jCut() == 1)NselectSF1j_OffShell += EvtWeight;
    //      else if (OF1jCut() == 1)NselectOF1j_OffShell += EvtWeight;
    //    }else{
    //      if (SF0jCut() == 1)     NselectSF0j_OnShell += EvtWeight;
    //      else if (OF0jCut() == 1)NselectOF0j_OnShell += EvtWeight;
    //      else if (SF1jCut() == 1)NselectSF1j_OnShell += EvtWeight;
    //      else if (OF1jCut() == 1)NselectOF1j_OnShell += EvtWeight;
    //    }
    //}
    //cout<<"evtChannel: "<<evtChannel<<"  channel: "<<channel<<endl;
    Fill_Histo();
    //Fout<<i<<"\t"<<EvtWeight*mpmet<<endl;
  }
  Fout<<"Nselected: "<<Nselect<<endl;
  Fout<<"NselectSF0j: "<<NselectSF0j<<endl;
  Fout<<"NselectSF1j: "<<NselectSF1j<<endl;
  Fout<<"NselectOF0j: "<<NselectOF0j<<endl;
  Fout<<"NselectOF1j: "<<NselectOF1j<<endl;
  Fout<<"NselectSF0j_OffShell: "<<NselectSF0j_OffShell<<endl;
  Fout<<"NselectSF1j_OffShell: "<<NselectSF1j_OffShell<<endl;
  Fout<<"NselectOF0j_OffShell: "<<NselectOF0j_OffShell<<endl;
  Fout<<"NselectOF1j_OffShell: "<<NselectOF1j_OffShell<<endl;
  Fout<<"NselectSF0j_OnShell: "<<NselectSF0j_OnShell<<endl;
  Fout<<"NselectSF1j_OnShell: "<<NselectSF1j_OnShell<<endl;
  Fout<<"NselectOF0j_OnShell: "<<NselectOF0j_OnShell<<endl;
  Fout<<"NselectOF1j_OnShell: "<<NselectOF1j_OnShell<<endl;
  Fout<<"Cut1: "<<ncut1<<endl;
  Fout<<"Cut2: "<<ncut2<<endl;
  Fout<<"Cut3: "<<ncut3<<endl;
  Fout<<"Cut4: "<<ncut4<<endl;
  Fout<<"Cut5: "<<ncut5<<endl;
  Fout<<"Cut6: "<<ncut6<<endl;
  Fout<<"Cut7: "<<ncut7<<endl;
  Fout<<"Cut8: "<<ncut8<<endl;
  Fout<<"Cut9: "<<ncut9<<endl;
  Fout<<"Cut10: "<<ncut10<<endl;
  Fout<<"Loose Cut: "<<ncutLoose<<endl;

  if(SampleName == "gg2vvHw1SigOnPeak" || SampleName == "gg2vvHw1SigShoulder" || SampleName == "gg2vvHw1SigTail")
    for(int i1(0); i1<61; i1++)
    {
      for(int i2(0); i2<31; i2++)
      {
	Fout<<i1<<", "<<i2<<" : "<<Nmllptll_OF0j[i1][i2]<<", "<<Nmllptll_OF1j[i1][i2]<<"\t["<<mllBins[i1]<<", "<<ptllBins[i2]<<"]"<<endl;
	h2_mllptll[1]->SetBinContent(i1+1,i2+1,Nmllptll_OF0j[i1+1][i2+1]/Nmllptll_OF0j[0][0]);
	h2_mllptll[3]->SetBinContent(i1+1,i2+1,Nmllptll_OF1j[i1+1][i2+1]/Nmllptll_OF1j[0][0]);
      }
    }
  // Usie one of the Write_Histo ro myFile->Write
  // Write_Histo: to write specific ones
  // myFile->Write ==> All
    
  //Write_Histo();
  myFile->Write();
  myFile->Close();
  Fout.close();
  gBenchmark->Show("HWwCtrPlt");
}
int HWwCtrPlt::Fill_Histo()
{

  h1_channel[evtChannel] ->Fill(channel, EvtWeight); //channel 0,1,2,3 (mumu,elel,elmu,muel)
  h1_mll[evtChannel]     ->Fill(mll, EvtWeight);
  h1_dphill[evtChannel]  ->Fill(180./PI*fabs(dphill), EvtWeight);
  h1_mth[evtChannel]     ->Fill(mth, EvtWeight);
  h1_mH[evtChannel]      ->Fill(mH,  EvtWeight);
  if(mH<=160)
    h1_mH_OnShell[evtChannel] ->Fill(mH,EvtWeight);
  if(mH>160)
    h1_mH_OffShell[evtChannel]->Fill(mH,EvtWeight);
  h1_charge1[evtChannel]->Fill(ch1, EvtWeight);
  h1_charge2[evtChannel]->Fill(ch2, EvtWeight);
  h1_trigger[evtChannel]->Fill(trigger, EvtWeight);
  h1_nextra[evtChannel] ->Fill(nextra, EvtWeight);
  h1_zveto[evtChannel]  ->Fill(zveto, EvtWeight);
  h1_flavor[evtChannel] ->Fill(sameflav, EvtWeight);
  h1_njet[evtChannel]   ->Fill(njet, EvtWeight);
  h1_bveto_mu[evtChannel] ->Fill(bveto_mu, EvtWeight);
  h1_bveto_ip[evtChannel] ->Fill(bveto_ip, EvtWeight);
  h1_nbjettche[evtChannel]->Fill(nbjettche, EvtWeight);
  h1_ptll[evtChannel]   ->Fill(ptll,EvtWeight);
  h1_pt1[evtChannel]    ->Fill(pt1, EvtWeight);
  h1_pt2[evtChannel]    ->Fill(pt2, EvtWeight);
  h1_pfmet[evtChannel]  ->Fill(pfmet, EvtWeight);
  h1_mpmet[evtChannel] ->Fill(mpmet,EvtWeight);
  h1_ppfmet[evtChannel] ->Fill(ppfmet,EvtWeight);
  h1_dymva1[evtChannel] ->Fill(dymva1,EvtWeight);
  h1_dphilljetjet[evtChannel] ->Fill(180./PI*fabs(dphilljetjet),EvtWeight);

  return 0;
}
int HWwCtrPlt::InitVar()
{
  TString FoutName = mResultDir+"/"+SampleName+"_"+Cut+".txt";
  Fout.open(FoutName);
  evtCnt = 0;
  Nselect = 0;
  NselectSF0j = 0;
  NselectSF1j = 0;
  NselectOF0j = 0;
  NselectOF1j = 0;

  NselectSF0j_OffShell = 0;
  NselectSF1j_OffShell = 0;
  NselectOF0j_OffShell = 0;
  NselectOF1j_OffShell = 0;
  NselectSF0j_OnShell = 0;
  NselectSF1j_OnShell = 0;
  NselectOF0j_OnShell = 0;
  NselectOF1j_OnShell = 0;
  ncut1 = 0;
  ncut2 = 0;
  ncut3 = 0;
  ncut4 = 0;
  ncut5 = 0;
  ncut6 = 0;
  ncut7 = 0;
  ncut8 = 0;
  ncut9 = 0;
  ncut10 = 0;
  ncutLoose = 0;

  for(int i1(0); i1<61; i1++)
  {
   mllBins[i1] = i1*5.;
   if(i1<31)
     ptllBins[i1] = i1*5.;
    for(int i2(0); i2<31; i2++)
    {
      Nmllptll_OF0j[i1][i2] = 0;
      Nmllptll_OF1j[i1][i2] = 0;
    }
  }

  return 0;
}
int HWwCtrPlt::InitVar4Evt()
{
  return 0;
}
int HWwCtrPlt::InitHistogram()
{
  myFile = new TFile(mResultDir+"/"+SampleName+"_"+Cut+".root","RECREATE");
  char histName[30];
  for(int i(0); i<4; i++)
  {
    sprintf(histName, "h1_channel_%d",i);
    h1_channel[i] = new TH1D(histName,"channel", 4, 0, 4);
    sprintf(histName, "h1_mll_%d",i);
    h1_mll[i] = new TH1D(histName,"Dilepton mass", 30, 0, 300);
    sprintf(histName,"h1_dphill_%d",i);
    h1_dphill[i] = new TH1D(histName,"Dileptom dphi",18,0,180);
    sprintf(histName,"h1_mth_%d",i);
    //h1_mth[i] = new TH1D(histName,"Transverse Higgs mass",25,0,300);
    h1_mth[i] = new TH1D(histName,"Transverse Higgs mass",50,0,600);
    sprintf(histName,"h1_mH_%d",i);
    h1_mH[i] = new TH1D(histName,"Higgs mass",50,0,1000);
    sprintf(histName,"h1_mH_OffShell_%d",i);
    h1_mH_OffShell[i] = new TH1D(histName,"Off-Shell Higgs mass",21,160,1000);
    sprintf(histName,"h1_mH_OnShell_%d",i);
    h1_mH_OnShell[i] = new TH1D(histName,"On-Shell Higgs mass",50,124.95,125.05);

    sprintf(histName, "h1_charge1_%d",i);
    h1_charge1[i] = new TH1D(histName,"Leading lepton charge", 3, -1.5, 1.5);
    sprintf(histName, "h1_charge2_%d",i);
    h1_charge2[i] = new TH1D(histName,"Trailing lepton charge",3, -1.5, 1.5);
    sprintf(histName, "h1_trigger_%d",i);
    h1_trigger[i] = new TH1D(histName,"Passes trigger", 2, -0.5, 1.5);
    sprintf(histName, "h1_nextra_%d",i);
    h1_nextra[i] = new TH1D(histName,"Extra leptons", 3, -1.5, 1.5);
    sprintf(histName, "h1_zveto_%d",i);
    h1_zveto[i] = new TH1D(histName,"Z veto (abs(mll-91) > 15)", 4, -0.5, 3.5);
    sprintf(histName, "h1_flavor_%d",i);
    h1_flavor[i] = new TH1D(histName,"Same flavor", 3, -0.5, 2.5);
    sprintf(histName, "h1_njet_%d",i);
    h1_njet[i] = new TH1D(histName,"Jet numbers", 6, -0.5, 5.5);
    sprintf(histName, "h1_bveto_mu_%d",i);
    h1_bveto_mu[i] = new TH1D(histName,"Passes the soft muons anti-b-tagging", 3, -0.5, 2.5);
    sprintf(histName, "h1_bveto_ip_%d",i);
    h1_bveto_ip[i] = new TH1D(histName,"Passes the ip anti-b-tagging", 4, -0.5, 3.5);
    sprintf(histName, "h1_nbjettche_%d",i);
    h1_nbjettche[i] = new TH1D(histName,"Counted b-jets", 2, -0.5, 1.5);
    sprintf(histName, "h1_ptll_%d",i);
    h1_ptll[i] = new TH1D(histName,"Dilepton transverse momentum", 20, 0, 150);
    sprintf(histName, "h1_pt1_%d",i);
    h1_pt1[i] = new TH1D(histName,"Leading lepton transverse momentum", 20, 0, 150);
    sprintf(histName, "h1_pt2_%d",i);
    h1_pt2[i] = new TH1D(histName,"Trailing lepton transverse momentum", 20, 0, 100);
    sprintf(histName, "h1_pfmet_%d",i);
    h1_pfmet[i] = new TH1D(histName,"PF MET", 25, 0, 200);
    sprintf(histName, "h1_mpmet_%d",i);
    h1_mpmet[i] = new TH1D(histName,"Minimum proj. MET", 25, 0, 200);
    sprintf(histName, "h1_ppfmet_%d",i);
    h1_ppfmet[i] = new TH1D(histName,"Projected MET", 25, 0, 200);
    sprintf(histName, "h1_dymva1_%d",i);
    h1_dymva1[i] = new TH1D(histName,"DY MVA", 10, -1, 1);
    sprintf(histName, "h1_dphilljetjet_%d",i);
    h1_dphilljetjet[i] = new TH1D(histName,"Deltaphi between the dileptons and jets", 18, 0, 180);

    sprintf(histName, "h1_mpmet_FOM_%d",i);
    h1_mpmet_FOM[i] = new TH1D(histName,"Minimum proj. MET", 20, 0, 80);//F.O.M. study

    sprintf(histName, "h2_mllptll_%d",i);
    h2_mllptll[i] = new TH2D(histName,"mll vs ptll",60,0,300,30,0,150);//mll ptll cut study
  }
  return 0;
}
int Write_Histo()
{
  return 0;
}
