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
  Fout<<"Total Events "<<Ntries<<endl;
  for(int i(0); i<Ntries;i++)
  //for(int i(0); i<100;i++)
  {
    if(i % 1000000 == 0) cout<<i<<"th event"<<endl;

    fChain->GetEntry(i);
    Init4Event();
    DumpParticles();
    if(isMuNuEleNu)
    {
      //cout<<Hig_mass<<" "<<HigT_mass<<" "<<DiLept_mass<<" "<<DiLept_pt<<" "<<pt1<<" "<<pt2<<" "<<MET<<" "<<mpMET<<" "<<ppfMET1<<" "<<ppfMET2<<" "<<DiLept_dphi<<" "<<mTTW<<endl;
      //cout<<pt1<<"\t"<<pt2<<"\t"<<MET<<"\t"<<DiLept_mass<<"\t"<<DiLept_pt<<"\t"<<mpMET<<endl;

      FillHistNoCut();
      Nselected4Bin();
    }

    if(isMuNuEleNu)if(pt1_Cut()>0)
    {
      if(pt1<20)
	cout<<"pt1<20:\t"<<pt1<<endl;
      h2_Hmass_pt1->Fill(Hig_mass,pt1);
      h_n1_pt1->Fill(pt1,mTTW);
    }
    if(pt2_Cut()>0)
    {
      h2_Hmass_pt2->Fill(Hig_mass,pt2);
      h_n1_pt2->Fill(pt2,mTTW);
    }
    if(MET_Cut()>0)
    {
      h2_Hmass_MET->Fill(Hig_mass,MET);
      h_n1_MET->Fill(MET,mTTW);
    }
    if(DiLept_mass_Cut()>0)
    {
      h2_Hmass_DiLept_mass->Fill(Hig_mass,DiLept_mass);
      h_n1_DiLept_mass->Fill(DiLept_mass,mTTW);
    }
    if(DiLept_pt_Cut()>0)
    {
      h2_Hmass_DiLept_pt->Fill(Hig_mass,DiLept_pt);
      h_n1_DiLept_pt->Fill(DiLept_pt,mTTW);
    }
    if(mpMET_Cut()>0)
    {
      h2_Hmass_mpMET->Fill(Hig_mass,mpMET);
      h_n1_mpMET->Fill(mpMET,mTTW);
    }
    if(CommonCut()>0)
    {
      FillHist();
      nPass++;
    }
  }
  Fout<<"Selected Events: "<<nPass<<endl;
  Fout<<"Higgs_EM_N_Total: "<<Higgs_EM_N_Total<<endl;
  Fout<<"Cut efficiency: "<<nPass/Higgs_EM_N_Total<<endl;
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
  //No Cut
  hNoCut_Hig_Mass    = new TH1D("hNoCut_Hig_Mass","m_{H} [GeV/c^{2}]",20,0,1000);
  hNoCut_HigT_Mass   = new TH1D("hNoCut_HigT_Mass","m_{T}^{H} [Gev/c^{2}]",12,0,600);
  hNoCut_DiLept_mass = new TH1D("hNoCut_DiLept_mass","m_{ll} [GeV/c^{2}]",10,0,600);
  hNoCut_DiLept_pt   = new TH1D("hNoCut_DiLept_pt","p_{T}^{ll} [GeV/c]",20,0,150);
  hNoCut_pt1    = new TH1D("hNoCut_pt1","p_{T}^{l, max} [GeV/c]",20,0,150);
  hNoCut_pt2    = new TH1D("hNoCut_pt2","p_{T}^{l, min} [GeV/c]",20,0,150);
  hNoCut_MET    = new TH1D("hNoCut_MET","PF #slash{E}_{T} [GeV]",25,0,200);
  hNoCut_mpMET  = new TH1D("hNoCut_mpMET","min(Proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  hNoCut_ppfMET = new TH1D("hNoCut_ppfMET","proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  hNoCut_dphill = new TH1D("hNoCut_dphill","#Delta#phi_{ll} [^{0}]",18,0,180);
  //Common Cut
  h_Hig_Mass    = new TH1D("h_Hig_Mass","m_{H} [GeV/c^{2}]",20,0,1000);
  h_HigT_Mass   = new TH1D("h_HigT_Mass","m_{T}^{H} [Gev/c^{2}]",12,0,600);
  h_DiLept_mass = new TH1D("h_DiLept_mass","m_{ll} [GeV/c^{2}]",10,0,600);
  h_DiLept_pt   = new TH1D("h_DiLept_pt","p_{T}^{ll} [GeV/c]",20,0,150);
  h_pt1    = new TH1D("h_pt1","p_{T}^{l, max} [GeV/c]",20,0,150);
  h_pt2    = new TH1D("h_pt2","p_{T}^{l, min} [GeV/c]",20,0,150);
  h_MET    = new TH1D("h_MET","PF #slash{E}_{T} [GeV]",25,0,200);
  h_mpMET  = new TH1D("h_mpMET","min(Proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  h_ppfMET = new TH1D("h_ppfMET","proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  h_dphill = new TH1D("h_dphill","#Delta#phi_{ll} [^{0}]",18,0,180);
  
  //N-1 cut study histograms
  h_n1_pt1 = new TH1D("h_n1_pt1","p_{T}^{l, max} [GeV/c]",20,0,150);
  h_n1_pt2 = new TH1D("h_n1_pt2","p_{T}^{l, min} [GeV/c]",20,0,150);
  h_n1_MET = new TH1D("h_n1_MET","PF #slash{E}_{T} [GeV]",25,0,200);
  h_n1_DiLept_mass = new TH1D("h_n1_DiLept_mass","m_{ll} [GeV/c^{2}]",10,0,600);
  h_n1_DiLept_pt = new TH1D("h_n1_DiLept_pt","p_{T}^{ll} [GeV/c]",20,0,150);
  h_n1_mpMET = new TH1D("h_n1_mpMET","min(Proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  h2_Hmass_pt1 = new TH2D("h2_Hmass_pt1","Higgs mass vs Leading lepton pt", 20,0,1000,20,0,150);
  h2_Hmass_pt2 = new TH2D("h2_Hmass_pt2","Higgs mass vs Trailing lepton pt",20,0,1000,20,0,150);
  h2_Hmass_MET = new TH2D("h2_Hmass_MET","Higgs mass vs MET",20,0,1000,25,0,200);
  h2_Hmass_mpMET = new TH2D("h2_Hmass_mpMET","Higgs mass vs min. proj. MET",20,0,1000,25,0,200);
  h2_Hmass_DiLept_mass = new TH2D("h2_Hmass_DiLept_mass","Higgs mass vs DiLepton mass",20,0,1000,20,0,600);
  h2_Hmass_DiLept_pt = new TH2D("h2_Hmass_DiLept_pt","Higgs mass vs DiLepton pt",20,0,1000,20,0,150);
  h2_Hmass_HTmass = new TH2D("h2_Hmass_HTmass","Higgs mass vs Higgs Transverse mass",20,0,1000,12,0,600);
  return 0;
}
int GGVvCtrPlt::FillHistNoCut()
{
  hNoCut_Hig_Mass->Fill(Hig_mass,mTTW);
  hNoCut_HigT_Mass->Fill(HigT_mass,mTTW);
  hNoCut_DiLept_mass->Fill(DiLept_mass,mTTW);
  hNoCut_DiLept_pt->Fill(DiLept_pt,mTTW);
  hNoCut_pt1->Fill(pt1,mTTW);
  hNoCut_pt2->Fill(pt2,mTTW);
  hNoCut_MET->Fill(MET,mTTW);
  hNoCut_mpMET->Fill(mpMET,mTTW);
  hNoCut_ppfMET->Fill(ppfMET1,mTTW);
  hNoCut_ppfMET->Fill(ppfMET2,mTTW);
  hNoCut_dphill->Fill(180./PI*fabs(DiLept_dphi),mTTW);
  return 0;
}
int GGVvCtrPlt::FillHist()
{
  h_Hig_Mass->Fill(Hig_mass,mTTW);
  h_HigT_Mass->Fill(HigT_mass,mTTW);
  h_DiLept_mass->Fill(DiLept_mass,mTTW);
  h_DiLept_pt->Fill(DiLept_pt,mTTW);
  h_pt1->Fill(pt1,mTTW);
  h_pt2->Fill(pt2,mTTW);
  h_MET->Fill(MET,mTTW);
  h_mpMET->Fill(mpMET,mTTW);
  h_ppfMET->Fill(ppfMET1,mTTW);
  h_ppfMET->Fill(ppfMET2,mTTW);
  h_dphill->Fill(180./PI*fabs(DiLept_dphi),mTTW);
  h2_Hmass_HTmass->Fill(Hig_mass,HigT_mass,mTTW);
  return 0;
}
int GGVvCtrPlt::InitVar()
{
  nPass = 0;
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
