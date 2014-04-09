#define GGVvCtrPlt_cxx
#include "GGVvCtrPlt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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
  int Npt0_140(0),     Npt8_140(0),     Npt20_140(0);
  int Npt0_140_300(0), Npt8_140_300(0), Npt20_140_300(0);
  int Npt0_300(0),     Npt8_300(0),     Npt20_300(0);
  for (int i(0); i<Ntries;i++)
  {
    if(i % 10000 == 0) cout<<i<<"th event"<<endl;

    fChain->GetEntry(i);
    Init4Event();
    DumpParticles();
    if(isEl && isElNu && isMu && isMuNu)
    {
      higgs_TL = el_TL + elNu_TL + mu_TL + muNu_TL;
      Hig_mass = higgs_TL.M();
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

      if( el_TL.Pt() > 8 && mu_TL.Pt() > 8 )
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

      if( el_TL.Pt() > 20 && mu_TL.Pt() > 20 )
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

      hHig_Mass->Fill(Hig_mass);
    }
  }
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
  Fout.close();
  gBenchmark->Show("GGVvCtrPlt");
}

int GGVvCtrPlt::InitHistogram()
{
  TString FoutName;
  FoutName = mDirName+"/"+mMode+".txt";
  Fout.open(FoutName);
  OutTFile = new TFile(mDirName+"/"+mMode+".root","RECREATE");
  hHig_Mass = new TH1D("hHig_Mass","Mass of Higgs",200,0,1000);
  return 0;
}
int GGVvCtrPlt::InitVar()
{
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
