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
  int Higgs_EM_N_Total(0);
  for (int i(0); i<Ntries;i++)
//  for (int i(0); i<20;i++)
  {
    if(i % 1000000 == 0) cout<<i<<"th event"<<endl;

    fChain->GetEntry(i);
    Init4Event();
    DumpParticles();

 //   if(isEl && isMu)
 //   {
//      Mu_mass = el_TL.M();
//      elmu_TL = el_TL + mu_TL;
//      EleMu_mass = elmu_TL.Mt();
//      hEleMu_Mass->Fill(EleMu_mass);
//    }
//    if(isEl && isElNu && isMu && isMuNu)
//    {
//      higgsT_TL = el_TL + elNu_TL + mu_TL + muNu_TL;
//      HigT_mass = higgsT_TL.Mt();
//      hHigT_Mass->Fill(HigT_mass);
//    }
//    if(isEl)
//    {
//      Ele_mass = el_TL.M();
//      Ele_mass = el_TL.Mt();
//      cout<<"Electron Mass: "<<Ele_mass<<" SpericalCoor: "<<el_TL.Rho()<<" Transrevse Mass: "<<el_TL.Mt()<<endl;
//      hEle_Mass->Fill(Ele_mass);
//    }
    if(isEl && isElNu && isMu && isMuNu)
    {
      Higgs_EM_N_Total++;
      higgs_TL = el_TL + elNu_TL + mu_TL + muNu_TL;
      higgsEM_TL = el_TL + mu_TL; 
      Hig_mass = higgs_TL.M();
      Hig_Et = higgs_TL.Et();
      HigEM_mass = higgsEM_TL.M();
      
      hHigEM_Mass->Fill(HigEM_mass);
//     hHig_Mass->Fill(Hig_mass);
      
//      double h_leading;
//      double h_trailing;
      double el_pt = el_TL.Pt();
      double mu_pt = mu_TL.Pt();
      double el_e = el_TL.Et();
      double mu_e = mu_TL.Et();
      double el_px = el_TL.Px();
      double el_py = el_TL.Py();
      double mu_px = mu_TL.Px();
      double mu_py = mu_TL.Py();
      double mt2 = el_e*mu_e - el_px*mu_px - el_py*mu_py;
      double Mt = (mt2 > 0) ? TMath::Sqrt(mt2) : 0;
      hHigT_Mass->Fill(Mt);

      if( el_pt > mu_pt ){
	  h_leadingPt->Fill(el_pt); 
//	el_pt > 20 && mu_pt > 10;
	if( el_pt > 20 && mu_pt > 10 ){
	  higgsl_TL = el_TL + elNu_TL + mu_TL + muNu_TL;
          Hig_cut_mass = higgsl_TL.M();
	  h_leadingM->Fill(Hig_cut_mass);
	}
      }
      else{
//	h_trailing = (el_pt > 10 && mu_pt > 20);
	h_leadingPt->Fill(mu_pt); 
        if( mu_pt > 20 && el_pt >10 ){
	  higgsl_TL = el_TL + elNu_TL + mu_TL + muNu_TL;
          Hig_cut_mass = higgsl_TL.M();
	  h_leadingM->Fill(Hig_cut_mass);
          } 
      }    

      if( Hig_Et > 0 ){
	hHig_Et->Fill(Hig_Et);
      }


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

      if( el_TL.Pt() > 8 )
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
      
      hHig_Mass->Fill(Hig_mass);
    }
  }
  Fout<<"Higgs_EM_N_Total"<<Higgs_EM_N_Total<<endl;
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
//  hEle_Mass = new TH1D("hEle_Mass","Mass of Electron",100,0,200);
//  hMu_Mass = new TH1D("hMu_Mass","Mass of Muon",100,0,200);
//  hEleMu_Mass = new TH1D("hEleMu_Mass","Mass of EleMuon",200,0,1000);
  h_leadingPt = new TH1D("h_leadingPt","LeadingPT",200,0,1000);
  hHigT_Mass = new TH1D("hHigT_Mass","Transverse Mass of Higgs",200,0,1000);
  h_leadingM = new TH1D("h_leadingM","Pt Cut Mass",200,0,1000);
  hHig_Et = new TH1D("hHig_Et","Et cut of Higgs",200,0,100);
  hHigEM_Mass = new TH1D("hHigEM_Mass","Mass of EMu",200,0,1000);

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
