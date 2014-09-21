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
  Fout<<"LumiW: "<<LumiW<<endl;
  
  for (int i(0); i<Ntries;i++)
  //for (int i(0); i<10;i++)
  {
    InitVar4Evt();
    evtCnt++;
    fChain->GetEntry(i);
    if (LooseCut() == 1) ncutLoose++;

    if(SampleName == "H125")
      mWW = MHiggs;
    if (pt1<=20)ncut1++;
    if (pt2<=10)ncut2++;
    if (nextra!=0)ncut3++;
    if (pfmet<=20)ncut4++;
    if (mll<=12)ncut5++;
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

    if( Cut == "LooseCut") if(LooseCut()  !=1)continue;
    if( Cut == "CommonCut")if(CommonCut() !=1)continue;
    if( Cut == "SignalCutV1")if(SignalCutV1() !=1)continue;
    if( Cut == "SignalCutV2")if(SignalCutV2() !=1)continue;
    if( Cut == "SignalCutV3")if(SignalCutV3() !=1)continue;
    Nselect[0] += EvtWeight;
    if (OF0jCut() == 1){NselectOF0j[0] += EvtWeight;}
    else if (OF1jCut() == 1){NselectOF1j[0] += EvtWeight;}

    //if(mth<=130){
    if(mth<=120 && mll<=50){
      if(mWW<=160){
	if (OF0jCut() == 1){NselectOF0j[1] += EvtWeight;}
	else if (OF1jCut() == 1){NselectOF1j[1] += EvtWeight;}
      }else if(mWW>160){
	if (OF0jCut() == 1){NselectOF0j[2] += EvtWeight;}
	else if (OF1jCut() == 1){NselectOF1j[2] += EvtWeight;}
      }
    //}else if(mth>130){
    }else if(mll>50 || mth>120){
      if(mWW<=160){
	if (OF0jCut() == 1){NselectOF0j[3] += EvtWeight;}
	else if (OF1jCut() == 1){NselectOF1j[3] += EvtWeight;}
      }else if(mWW>160){
	if (OF0jCut() == 1){NselectOF0j[4] += EvtWeight;}
	else if (OF1jCut() == 1){NselectOF1j[4] += EvtWeight;}
      }
    }
    Fill_Histo();
    //FillHisto();
  }
  //Fout<<"Weighted (Counted)"<<endl;
  //Fout<<"Nselected: "<<Nselect[1]<<" ("<<Nselect[0]<<")"<<endl;
  //Fout<<"Nselected mWW<160: "<<Nselect[3]<<" ("<<Nselect[2]<<")"<<endl;
  //Fout<<"Nselected mWW>160: "<<Nselect[5]<<" ("<<Nselect[4]<<")"<<endl;
  //Fout<<"NselectSF0j: "<<NselectSF0j[1]<<" ("<<NselectSF0j[0]<<")"<<endl;
  //Fout<<"NselectSF1j: "<<NselectSF1j[1]<<" ("<<NselectSF1j[0]<<")"<<endl;
  //Fout<<"NselectOF0j: "<<NselectOF0j[1]<<" ("<<NselectOF0j[0]<<")"<<endl;
  //Fout<<"NselectOF1j: "<<NselectOF1j[1]<<" ("<<NselectOF1j[0]<<")"<<endl;
  //Fout<<"NselectSF0j mWW<160: "<<NselectSF0j[3]<<" ("<<NselectSF0j[2]<<")"<<endl;
  //Fout<<"NselectSF1j mWW<160: "<<NselectSF1j[3]<<" ("<<NselectSF1j[2]<<")"<<endl;
  //Fout<<"NselectOF0j mWW<160: "<<NselectOF0j[3]<<" ("<<NselectOF0j[2]<<")"<<endl;
  //Fout<<"NselectOF1j mWW<160: "<<NselectOF1j[3]<<" ("<<NselectOF1j[2]<<")"<<endl;
  //Fout<<"NselectSF0j mWW>160: "<<NselectSF0j[5]<<" ("<<NselectSF0j[4]<<")"<<endl;
  //Fout<<"NselectSF1j mWW>160: "<<NselectSF1j[5]<<" ("<<NselectSF1j[4]<<")"<<endl;
  //Fout<<"NselectOF0j mWW>160: "<<NselectOF0j[5]<<" ("<<NselectOF0j[4]<<")"<<endl;
  //Fout<<"NselectOF1j mWW>160: "<<NselectOF1j[5]<<" ("<<NselectOF1j[4]<<")"<<endl;
  //Fout<<"NselectOF mWW<160: "<<NselectOF0j[3]+NselectOF1j[3]<<" ("<<NselectOF0j[2]+NselectOF1j[2]<<")"<<endl;
  //Fout<<"NselectOF mWW>160: "<<NselectOF0j[5]+NselectOF1j[5]<<" ("<<NselectOF0j[4]+NselectOF1j[4]<<")"<<endl;
  Fout<<"Weighted ( %)"<<endl;
  Fout<<"Nselected: "<<Nselect[0]<<endl;
  Fout<<"OF0j"<<endl;
  Fout<<"NselectOF0j(before mth&mll Cut): "<<NselectOF0j[0]<<endl;
  Fout<<"NselectOF0j mth<120,mll<50, mWW<160: "<<NselectOF0j[1]<<" ("<<100*NselectOF0j[1]/NselectOF0j[0]<<" %)"<<endl;
  Fout<<"NselectOF0j mth<120,mll<50, mWW>160: "<<NselectOF0j[2]<<" ("<<100*NselectOF0j[2]/NselectOF0j[0]<<" %)"<<endl;
  Fout<<"NselectOF0j mth>120,mll>50, mWW<160: "<<NselectOF0j[3]<<" ("<<100*NselectOF0j[3]/NselectOF0j[0]<<" %)"<<endl;
  Fout<<"NselectOF0j mth>120,mll>50, mWW>160: "<<NselectOF0j[4]<<" ("<<100*NselectOF0j[4]/NselectOF0j[0]<<" %)"<<endl;
  Fout<<"OF1j"<<endl;
  Fout<<"NselectOF1j(before mth&mll Cut): "<<NselectOF1j[0]<<endl;
  Fout<<"NselectOF1j mth<120,mll<50, mWW<160: "<<NselectOF1j[1]<<" ("<<100*NselectOF1j[1]/NselectOF1j[0]<<" %)"<<endl;
  Fout<<"NselectOF1j mth<120,mll<50, mWW>160: "<<NselectOF1j[2]<<" ("<<100*NselectOF1j[2]/NselectOF1j[0]<<" %)"<<endl;
  Fout<<"NselectOF1j mth>120,mll>50, mWW<160: "<<NselectOF1j[3]<<" ("<<100*NselectOF1j[3]/NselectOF1j[0]<<" %)"<<endl;
  Fout<<"NselectOF1j mth>120,mll>50, mWW>160: "<<NselectOF1j[4]<<" ("<<100*NselectOF1j[4]/NselectOF1j[0]<<" %)"<<endl;
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
  h1_mH[evtChannel]      ->Fill(mWW,  EvtWeight);
  if(mWW<=160)
    h1_mH_OnShell[evtChannel] ->Fill(mWW,EvtWeight);
  if(mWW>160)
    h1_mH_OffShell[evtChannel]->Fill(mWW,EvtWeight);
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
  //if((leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron) || (leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon))
  h2_mthdphill[evtChannel] ->Fill(mth,180./PI*fabs(dphill),EvtWeight);
  h2_mlldphill[evtChannel] ->Fill(mll,180./PI*fabs(dphill),EvtWeight);
  h2_mthmllBins[evtChannel] ->Fill(mth,mll,EvtWeight);
  h2_mthmll[evtChannel]  ->Fill(mth,mll,EvtWeight);
  h2_mthptll[evtChannel] ->Fill(mth,ptll,EvtWeight);
  h2_mllptll[evtChannel] ->Fill(mll,ptll,EvtWeight);
  if(mWW<160)
    h2_mthmll_OnSh[evtChannel] ->Fill(mth,mll,EvtWeight);
  if(mWW>=160)
    h2_mthmll_OffSh[evtChannel]->Fill(mth,mll,EvtWeight);
  return 0;
}
int HWwCtrPlt::FillHisto()
{
  //On-shell
  if(mWW<160){
    if(CommonCut() ==1){
      h2_mthmll_OnSh[evtChannel] ->Fill(mth,mll,EvtWeight);
      h2_mthptll_OnSh[evtChannel]->Fill(mth,ptll,EvtWeight);
      h2_mllptll_OnSh[evtChannel]->Fill(mll,ptll,EvtWeight);
      if(mth<=120 && mll<=50){
	h1_mll_OnSh_mth_l120[evtChannel]->Fill(mll, EvtWeight);
      }else if(mth>120 || mll>50){
	h1_mll_OnSh_mth_g120[evtChannel]->Fill(mll, EvtWeight);
      }
      
      if(mth<=130){
	h1_mll_OnSh_mth_l130[evtChannel]->Fill(mll, EvtWeight);
      }else if(mth>130){
	h1_mll_OnSh_mth_g130[evtChannel]->Fill(mll, EvtWeight);
      }
      
      if(mll<=83){
	h1_mth_OnSh_mll_l83[evtChannel] ->Fill(mth, EvtWeight);
      }else if(mll>83){
	h1_mth_OnSh_mll_g83[evtChannel] ->Fill(mth, EvtWeight);
      }
    }
  }
  
  //Off-shell
  if(mWW>=160){
    //if(CommonCut_Without_ptllCut() ==1){
    if(CommonCut() ==1){
      h2_mthmll_OffSh[evtChannel] ->Fill(mth,mll,EvtWeight);
      h2_mthptll_OffSh[evtChannel]->Fill(mth,ptll,EvtWeight);
      h2_mllptll_OffSh[evtChannel]->Fill(mll,ptll,EvtWeight);
      if(mth<=120 && mll<=50){
	h1_mll_OffSh_mth_l120[evtChannel]->Fill(mll, EvtWeight);
      }else if(mth>120 || mll>50){
	h1_mll_OffSh_mth_g120[evtChannel]->Fill(mll, EvtWeight);
      }

      if(mth<=130){
	h1_mll_OffSh_mth_l130[evtChannel]->Fill(mll, EvtWeight);
      }else if(mth>130){
	h1_mll_OffSh_mth_g130[evtChannel]->Fill(mll, EvtWeight);
      }

      if(mll<=83){
	h1_mth_OffSh_mll_l83[evtChannel] ->Fill(mth, EvtWeight);
      }else if(mll>83){
	h1_mth_OffSh_mll_g83[evtChannel] ->Fill(mth, EvtWeight);
      }
    }
  }
  return 0;
}
int HWwCtrPlt::InitVar()
{
  TString FoutName = mResultDir+"/"+SampleName+"_"+Cut+".txt";
  Fout.open(FoutName);
  evtCnt = 0;

  for(int j(0); j<6; j++)
  {
    Nselect[j] = 0;
    NselectSF0j[j] = 0;
    NselectSF1j[j] = 0;
    NselectOF0j[j] = 0;
    NselectOF1j[j] = 0;
  }
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
  //mH = 0;

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
    sprintf(histName, "h1_dymva1_%d",i);
    h1_dymva1[i] = new TH1D(histName,"DY MVA", 10, -1, 1);
    sprintf(histName, "h1_dphilljetjet_%d",i);
    h1_dphilljetjet[i] = new TH1D(histName,"Deltaphi between the dileptons and jets", 18, 0, 180);
    sprintf(histName, "h1_mpmet_FOM_%d",i);
    h1_mpmet_FOM[i] = new TH1D(histName,"Minimum proj. MET", 20, 0, 80);//F.O.M. study
    sprintf(histName, "h2_mthmllBins_%d",i);
    h2_mthmllBins[i] = new TH2D(histName,"mth vs mll",11,mthBins,11,mllBins);//mth vs mll fixed bins
    sprintf(histName, "h2_mthmll_%d",i);
    h2_mthmll[i] = new TH2D(histName,"mth vs mll",40,0,400,40,0,400);//mth vs mll
    sprintf(histName, "h2_mthptll_%d",i);
    h2_mthptll[i] = new TH2D(histName,"mth vs ptll",40,0,400,40,0,400);//mth vs ptll
    sprintf(histName, "h2_mllptll_%d",i);
    h2_mllptll[i] = new TH2D(histName,"mll vs ptll",40,0,400,40,0,400);//mll vs ptll
    sprintf(histName, "h2_mthdphill_%d",i);
    h2_mthdphill[i] = new TH2D(histName,"mth vs dphill",40,0,400,18,0,180);//mth vs dphill
    sprintf(histName, "h2_mlldphill_%d",i);
    h2_mlldphill[i] = new TH2D(histName,"mll vs dphill",40,0,400,18,0,180);//mth vs dphill
    sprintf(histName, "h1_mll_%d",i);
    h1_mll[i] = new TH1D(histName,"Dilepton mass", 60, 0, 600);
    sprintf(histName,"h1_dphill_%d",i);
    h1_dphill[i] = new TH1D(histName,"Dileptom dphi",18,0,180);
    sprintf(histName, "h1_pfmet_%d",i);
    h1_pfmet[i] = new TH1D(histName,"PF MET", 25, 0, 200);
    sprintf(histName, "h1_ptll_%d",i);
    h1_ptll[i] = new TH1D(histName,"Dilepton transverse momentum", 20, 0, 150);
    sprintf(histName, "h1_pt1_%d",i);
    h1_pt1[i] = new TH1D(histName,"Leading lepton transverse momentum", 30, 0, 300);
    sprintf(histName, "h1_pt2_%d",i);
    h1_pt2[i] = new TH1D(histName,"Trailing lepton transverse momentum", 30, 0, 300);
    sprintf(histName, "h1_mpmet_%d",i);
    h1_mpmet[i] = new TH1D(histName,"Minimum proj. MET", 25, 0, 200);
    sprintf(histName, "h1_ppfmet_%d",i);
    h1_ppfmet[i] = new TH1D(histName,"Projected MET", 25, 0, 200);

    //On-shell vs Off-shell
    sprintf(histName, "h2_mthmll_OnSh_%d",i);
    h2_mthmll_OnSh[i] = new TH2D(histName,"mth vs mll",40,0,400,40,0,400);//mth vs mll
    sprintf(histName, "h2_mthptll_OnSh_%d",i);
    h2_mthptll_OnSh[i] = new TH2D(histName,"mth vs ptll",40,0,400,40,0,400);//mth vs ptll
    sprintf(histName, "h2_mllptll_OnSh_%d",i);
    h2_mllptll_OnSh[i] = new TH2D(histName,"mll vs ptll",40,0,400,40,0,400);//mll vs ptll
    sprintf(histName, "h1_mll_OnSh_mth_l130_%d",i);
    h1_mll_OnSh_mth_l130[i] = new TH1D(histName,"Dilepton mass", 40, 0, 400);
    sprintf(histName, "h1_mll_OnSh_mth_g130_%d",i);
    h1_mll_OnSh_mth_g130[i] = new TH1D(histName,"Dilepton mass", 40, 0, 400);
    sprintf(histName, "h1_mll_OnSh_mth_l120_%d",i);
    h1_mll_OnSh_mth_l120[i] = new TH1D(histName,"Dilepton mass", 40, 0, 400);
    sprintf(histName, "h1_mll_OnSh_mth_g120_%d",i);
    h1_mll_OnSh_mth_g120[i] = new TH1D(histName,"Dilepton mass", 40, 0, 400);
    sprintf(histName,"h1_mth_OnSh_mll_l83_%d",i);
    h1_mth_OnSh_mll_l83[i] = new TH1D(histName,"Transverse Higgs mass",40,0,400);
    sprintf(histName,"h1_mth_OnSh_mll_g83_%d",i);
    h1_mth_OnSh_mll_g83[i] = new TH1D(histName,"Transverse Higgs mass",40,0,400);

    sprintf(histName, "h2_mthmll_OffSh_%d",i);
    h2_mthmll_OffSh[i] = new TH2D(histName,"mth vs mll",40,0,400,40,0,400);//mth vs mll
    sprintf(histName, "h2_mthptll_OffSh_%d",i);
    h2_mthptll_OffSh[i] = new TH2D(histName,"mth vs ptll",40,0,400,40,0,400);//mth vs ptll
    sprintf(histName, "h2_mllptll_OffSh_%d",i);
    h2_mllptll_OffSh[i] = new TH2D(histName,"mll vs ptll",40,0,400,40,0,400);//mll vs ptll
    sprintf(histName, "h1_mll_OffSh_mth_l130_%d",i);
    h1_mll_OffSh_mth_l130[i] = new TH1D(histName,"Dilepton mass", 40, 0, 400);
    sprintf(histName, "h1_mll_OffSh_mth_g130_%d",i);
    h1_mll_OffSh_mth_g130[i] = new TH1D(histName,"Dilepton mass", 40, 0, 400);
    sprintf(histName, "h1_mll_OffSh_mth_l120_%d",i);
    h1_mll_OffSh_mth_l120[i] = new TH1D(histName,"Dilepton mass", 40, 0, 400);
    sprintf(histName, "h1_mll_OffSh_mth_g120_%d",i);
    h1_mll_OffSh_mth_g120[i] = new TH1D(histName,"Dilepton mass", 40, 0, 400);
    sprintf(histName,"h1_mth_OffSh_mll_l83_%d",i);
    h1_mth_OffSh_mll_l83[i] = new TH1D(histName,"Transverse Higgs mass",40,0,400);
    sprintf(histName,"h1_mth_OffSh_mll_g83_%d",i);
    h1_mth_OffSh_mll_g83[i] = new TH1D(histName,"Transverse Higgs mass",40,0,400);
  }
  return 0;
}
int Write_Histo()
{
  return 0;
}
