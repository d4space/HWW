#define GGVvCtrPlt_cxx
#include "GGVvCtrPlt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iomanip>

void GGVvCtrPlt::Loop()
{
  if (fChain == 0)
  {
    cout<<"GGvVTemplate: no fChain  Exit ############"<<endl;
    exit(-1);
  }
  gBenchmark->Start("GGVvCtrPlt");
  Ntries = fChain->GetEntries();
  cout<<"Total number of event is "<<Ntries<<endl;
  for (int i(0); i<Ntries;i++)
  //for (int i(0); i<10;i++)
  {
    if(i % 1000000 == 0) cout<<i<<"th event"<<endl;

    fChain->GetEntry(i);
    Init4Event();
    DumpParticles();
    if(SelectParticles()>0)
    {
      FillHist();
      Nselected4Bin();
    }
  }
  Fout<<"Higgs_EM_N_Total: "<<Higgs_EM_N_Total<<endl;
  Fout<<"Higg_N_LowReso: "<<Hig_N_LowReso<<endl;
  Fout<<"Hig_N_LowReso: "<<Hig_N_LowReso<<endl;
  Fout<<"Hig_N_Reso: "<<Hig_N_Reso<<endl;
  Fout<<"Hig_N_HighReso: "<<Hig_N_HighReso<<endl;
  Fout<<"Hig_N_Sig: "<<Hig_N_Sig<<endl;
  Fout<<"Hig_N_Total: "<<Hig_N_Total<<endl;
  Fout<<"Hig_N_OnPeak: "<<Hig_N_OnPeak<<endl;
  Fout<<"Hig_N_OffPeak: "<<Hig_N_OffPeak<<endl;

  Fout<<"                 "<<endl;
  Fout<<"Hig_N_LowReso8: "<<Hig_N_LowReso8<<endl;
  Fout<<"Hig_N_Reso8: "<<Hig_N_Reso8<<endl;
  Fout<<"Hig_N_HighReso8: "<<Hig_N_HighReso8<<endl;
  Fout<<"Hig_N_Sig8: "<<Hig_N_Sig8<<endl;
  Fout<<"Hig_N_Total8: "<<Hig_N_Total8<<endl;
  Fout<<"Hig_N_OnPeak8: "<<Hig_N_OnPeak8<<endl;
  Fout<<"Hig_N_OffPeak8: "<<Hig_N_OffPeak8<<endl;

  Fout<<"                 "<<endl;
  Fout<<"Hig_N_LowReso20: "<<Hig_N_LowReso20<<endl;
  Fout<<"Hig_N_Reso20: "<<Hig_N_Reso20<<endl;
  Fout<<"Hig_N_HighReso20: "<<Hig_N_HighReso20<<endl;
  Fout<<"Hig_N_Sig20: "<<Hig_N_Sig20<<endl;
  Fout<<"Hig_N_Total20: "<<Hig_N_Total20<<endl;
  Fout<<"Hig_N_OnPeak20: "<<Hig_N_OnPeak20<<endl;
  Fout<<"Hig_N_OffPeak20: "<<Hig_N_OffPeak20<<endl;

  Fout<<"                 "<<endl;
  Fout<<"Npt0_140: "    <<Npt0_140<<endl;
  Fout<<"Npt0_140_300: "<<Npt0_140_300<<endl;
  Fout<<"Npt0_300: "    <<Npt0_300<<endl;
  Fout<<"                 "<<endl;
  Fout<<"Npt8_140: "    <<Npt8_140<<endl;
  Fout<<"Npt8_140_300: "<<Npt8_140_300<<endl;
  Fout<<"Npt8_300: "    <<Npt8_300<<endl;
  Fout<<"                 "<<endl;
  Fout<<"Npt20_140: "    <<Npt20_140<<endl;
  Fout<<"Npt20_140_300: "<<Npt20_140_300<<endl;
  Fout<<"Npt20_300: "    <<Npt20_300<<endl;

  OutTFile->Write();
  OutTFile->Close();
  Fout.close();
  gBenchmark->Show("GGVvCtrPlt");
}

int GGVvCtrPlt::Nselected4Bin()
{
  Higgs_EM_N_Total++;
  if(Hig_mass >0   && Hig_mass <= 124) Hig_N_LowReso++;
  if(Hig_mass >124 && Hig_mass <= 128) Hig_N_Reso++;
  if(Hig_mass >0   && Hig_mass <= 140) Hig_N_OnPeak++;
  if(Hig_mass >140 && Hig_mass <= 1000) Hig_N_OffPeak++;
  if(Hig_mass >128 && Hig_mass <= GenType::M_W*2) Hig_N_HighReso++;
  if(Hig_mass >GenType::M_W*2 && Hig_mass <= 1000) Hig_N_Sig++;
  if(Hig_mass >0   && Hig_mass <= 1000) Hig_N_Total++;
  if(Hig_mass >0     && Hig_mass <= 140)  Npt0_140++;
  if(Hig_mass >140   && Hig_mass <= 300)  Npt0_140_300++;
  if(Hig_mass >300   && Hig_mass <= 1000) Npt0_300++;
  
  if(el_TL.Pt() > 8)
  {
    if(Hig_mass >0   && Hig_mass <= 124) Hig_N_LowReso8++;
    if(Hig_mass >124 && Hig_mass <= 128) Hig_N_Reso8++;
    if(Hig_mass >0   && Hig_mass <= 140) Hig_N_OnPeak8++;
    if(Hig_mass >140 && Hig_mass <= 1000) Hig_N_OffPeak8++;
    if(Hig_mass >128 && Hig_mass <= GenType::M_W*2) Hig_N_HighReso8++;
    if(Hig_mass >GenType::M_W*2 && Hig_mass <= 1000) Hig_N_Sig8++;
    if(Hig_mass >0   && Hig_mass <= 1000) Hig_N_Total8++;
    
    if(Hig_mass >0     && Hig_mass <= 140)  Npt8_140++;
    if(Hig_mass >140   && Hig_mass <= 300)  Npt8_140_300++;
    if(Hig_mass >300   && Hig_mass <= 1000) Npt8_300++;
  }
  
  if( el_TL.Pt() > 20 )
  {
    if(Hig_mass >0   && Hig_mass <= 124) Hig_N_LowReso20++;
    if(Hig_mass >124 && Hig_mass <= 128) Hig_N_Reso20++;
    if(Hig_mass >0   && Hig_mass <= 140) Hig_N_OnPeak20++;
    if(Hig_mass >140 && Hig_mass <= 1000) Hig_N_OffPeak20++;
    if(Hig_mass >128 && Hig_mass <= GenType::M_W*2) Hig_N_HighReso20++;
    if(Hig_mass >GenType::M_W*2 && Hig_mass <= 1000) Hig_N_Sig20++;
    if(Hig_mass >0   && Hig_mass <= 1000) Hig_N_Total20++;
    
    if(Hig_mass >0     && Hig_mass <= 140)  Npt20_140++;
    if(Hig_mass >140   && Hig_mass <= 300)  Npt20_140_300++;
    if(Hig_mass >300   && Hig_mass <= 1000) Npt20_300++;
  }
}
int GGVvCtrPlt::InitHistogram()
{
  TString FoutName;
  FoutName = mDirName+"/"+mMode+".txt";
  Fout.open(FoutName);
  OutTFile = new TFile(mDirName+"/"+mMode+".root","RECREATE");
  hHig_Mass = new TH1D("hHig_Mass","Higgs Mass",200,0,1000);
  h_leadingPt = new TH1D("h_leadingPt","LeadingPT",100,0,500);
  h_trailingPt = new TH1D("h_trailingPt","TrailingPT",80,0,400);
  hHigT_Mass = new TH1D("hHigT_Mass","Transverse Mass of Higgs",100,0,500);
  //h_leadingM = new TH1D("h_leadingM","Pt Cut Mass",200,0,1000);
  hHig_Et = new TH1D("hHig_Et","Et cut of Higgs",200,0,100);
  h_DiLept_Mass = new TH1D("h_DiLept_Mass","Mass of EMu",200,0,1000);
  h_MET = new TH1D("h_MET","MET",60,0,300);
  h_mpMET = new TH1D("h_mpMET","mpMET",60,0,300);
  h_dphill = new TH1D("h_dphill","Delta phi between two leptons",18,0,180);
  return 0;
}
int GGVvCtrPlt::FillHist()
{
  h_MET->Fill(MET);
  h_mpMET->Fill(mpMET);
  h_dphill->Fill(180./PI*fabs(DiLept_dphi));
  h_DiLept_Mass->Fill(DiLept_mass);
  h_leadingPt ->Fill(pt1);
  h_trailingPt->Fill(pt2);
  hHig_Mass->Fill(Hig_mass);
  hHigT_Mass->Fill(HigT_mass);
  hHig_Et->Fill(Hig_Et);
  return 0;
}
int GGVvCtrPlt::InitVar()
{
  Higgs_EM_N_Total = 0;
  Npt0_140 = 0;
  Npt8_140 = 0;
  Npt20_140 = 0;
  Npt0_140_300 = 0;
  Npt8_140_300 = 0;
  Npt20_140_300 = 0;
  Npt0_300 = 0;
  Npt8_300 = 0;
  Npt20_300 = 0;

  Hig_N_LowReso = 0;
  Hig_N_Reso = 0;
  Hig_N_HighReso = 0;
  Hig_N_Sig = 0;
  Hig_N_Total = 0;
  Hig_N_OnPeak = 0;
  Hig_N_OffPeak = 0;

  Hig_N_LowReso8 = 0;
  Hig_N_Reso8 = 0;
  Hig_N_HighReso8 = 0;
  Hig_N_Sig8 = 0;
  Hig_N_Total8 = 0;
  Hig_N_OnPeak8 = 0;
  Hig_N_OffPeak8 = 0;

  Hig_N_LowReso20 = 0;
  Hig_N_Reso20 = 0;
  Hig_N_HighReso20 = 0;
  Hig_N_Sig20 = 0;
  Hig_N_Total20 = 0;
  Hig_N_OnPeak20 = 0;
  Hig_N_OffPeak20 = 0;

  return 0;
}
