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
  Fout<<setprecision(8)<<endl;
  Fout<<"Total Events "<<Ntries<<endl;
  for(int i(0); i<Ntries;i++)
  //for(int i(0); i<40;i++)
  {
    if(i % 1000000 == 0) cout<<i<<"th event"<<endl;

    fChain->GetEntry(i);
    Init4Event();
    DumpParticles();
    //nEvents Counting for All Channel in OnPeak, Shoulder and Tail
    if(Hmass > 0 && Hmass <= 140 ) nEvents_OnPeak_AllCh++;
    if(Hmass > 140 && Hmass <= 300) nEvents_Shoulder_AllCh++;
    if(Hmass > 300) nEvents_Tail_AllCh++;

    if(isMuNuEleNu)
    {
      //cout<<Hig_mass<<" "<<HigT_mass<<" "<<DiLept_mass<<" "<<DiLept_pt<<" "<<pt1<<" "<<pt2<<" "<<MET<<" "<<mpMET<<" "<<ppfMET1<<" "<<ppfMET2<<" "<<DiLept_dphi<<" "<<mTTW<<endl;
      //cout<<pt1<<"\t"<<pt2<<"\t"<<MET<<"\t"<<DiLept_mass<<"\t"<<DiLept_pt<<"\t"<<mpMET<<endl;
      //cout<<i<<" Event Higgs Mass (from EleMu channel): "<<Hig_mass<<endl;
      FillHistNoCut();
      Nselected4Bin();
    }

    if(isMuNuEleNu)if(pt1_Cut()>0)
    {
      //if(pt1<20)
      //  cout<<"pt1<20:\t"<<pt1<<endl;
      h2_mH_pt1->Fill(Hig_mass,pt1);
      hN1Cut_pt1->Fill(pt1,mTTW);
    }
    if(pt2_Cut()>0)
    {
      h2_mH_pt2->Fill(Hig_mass,pt2);
      hN1Cut_pt2->Fill(pt2,mTTW);
    }
    if(MET_Cut()>0)
    {
      h2_mH_MET->Fill(Hig_mass,MET);
      hN1Cut_MET->Fill(MET,mTTW);
    }
    if(DiLept_mass_Cut()>0)
    {
      h2_mH_mll->Fill(Hig_mass,DiLept_mass);
      hN1Cut_mll->Fill(DiLept_mass,mTTW);
    }
    if(DiLept_pt_Cut()>0)
    {
      h2_mH_ptll->Fill(Hig_mass,DiLept_pt);
      hN1Cut_ptll->Fill(DiLept_pt,mTTW);
    }
    if(mpMET_Cut()>0)
    {
      h2_mH_mpMET->Fill(Hig_mass,mpMET);
      hN1Cut_mpMET->Fill(mpMET,mTTW);
    }
    if(CommonCut()>0)
    {
      FillHist();
      nPass++;
    }
    if(CommonCut_mll()>0)
      nPass_mll++;
  }
  Fout<<"ElMu Ch. - Selected Events(CommonCut): "<<nPass<<endl;
  Fout<<"ElMu Ch. - Events from CommonCut and mll>100: "<<nPass_mll<<endl;
  Fout<<"ElMu Ch. - Total nEvents: "<<Higgs_EM_N_Total<<endl;
  Fout<<"ElMu Ch. - CommonCut efficiency: "<<nPass/Higgs_EM_N_Total<<endl;
  Fout<<"ElMu Ch. - CommonCut plus mll>100 efficiency: "<<nPass_mll/Higgs_EM_N_Total<<endl;
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

  Fout<<"                 "<<endl;
  Fout<<"=============All channel============="<<endl;
  Fout<<"Total nEvents: "<<Ntries<<endl;
  Fout<<"OnPeak: "<<nEvents_OnPeak_AllCh<<endl;
  Fout<<"Shoulder: "<<nEvents_Shoulder_AllCh<<endl;
  Fout<<"Tail: "<<nEvents_Tail_AllCh<<endl;

  Fout<<"                 "<<endl;
  Fout<<"=============Electron Muon channel============="<<endl;
  Fout<<"Total nEvents: "<<Higgs_EM_N_Total<<endl;
  Fout<<"OnPeak: "    <<Npt0_140<<endl;
  Fout<<"Shoulder: "<<Npt0_140_300<<endl;
  Fout<<"Tail: "    <<Npt0_300<<endl;

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
  //if(Hig_mass >300   && Hig_mass <= 1000) Npt0_300++;
  if(Hig_mass >300) Npt0_300++;
  
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
  hNoCut_Hig_mass    = new TH1D("hNoCut_Hig_mass","m_{H} [GeV/c^{2}]",20,0,1000);
  hNoCut_HigT_mass   = new TH1D("hNoCut_HigT_mass","m_{T}^{H} [Gev/c^{2}]",12,0,600);
  hNoCut_mll = new TH1D("hNoCut_mll","m_{ll} [GeV/c^{2}]",10,0,600);
  hNoCut_ptll   = new TH1D("hNoCut_ptll","p_{T}^{ll} [GeV/c]",20,0,150);
  hNoCut_pt1    = new TH1D("hNoCut_pt1","p_{T}^{l, max} [GeV/c]",20,0,150);
  hNoCut_pt2    = new TH1D("hNoCut_pt2","p_{T}^{l, min} [GeV/c]",20,0,150);
  hNoCut_MET    = new TH1D("hNoCut_MET","PF #slash{E}_{T} [GeV]",25,0,200);
  hNoCut_mpMET  = new TH1D("hNoCut_mpMET","min(Proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  hNoCut_ppfMET = new TH1D("hNoCut_ppfMET","proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  hNoCut_dphill = new TH1D("hNoCut_dphill","#Delta#phi_{ll} [^{0}]",18,0,180);
  hNoCut_dphillmet = new TH1D("hNoCut_dphillmet","#Delta#phi_{ll-#slash{E}_{T}} [^{0}]",18,0,180);
  //Common Cut
  h_Hig_mass    = new TH1D("h_Hig_mass","m_{H} [GeV/c^{2}]",20,0,1000);
  h_HigT_mass   = new TH1D("h_HigT_mass","m_{T}^{H} [Gev/c^{2}]",12,0,600);
  h_mll = new TH1D("h_mll","m_{ll} [GeV/c^{2}]",10,0,600);
  h_ptll   = new TH1D("h_ptll","p_{T}^{ll} [GeV/c]",20,0,150);
  h_pt1    = new TH1D("h_pt1","p_{T}^{l, max} [GeV/c]",20,0,150);
  h_pt2    = new TH1D("h_pt2","p_{T}^{l, min} [GeV/c]",20,0,150);
  h_MET    = new TH1D("h_MET","PF #slash{E}_{T} [GeV]",25,0,200);
  h_mpMET  = new TH1D("h_mpMET","min(Proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  h_ppfMET = new TH1D("h_ppfMET","proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  h_dphill = new TH1D("h_dphill","#Delta#phi_{ll} [^{0}]",18,0,180);
  h_dphillmet = new TH1D("h_dphillmet","#Delta#phi_{ll-#slash{E}_{T}} [^{0}]",18,0,180);
  
  //N-1 cut study histograms
  hN1Cut_pt1 = new TH1D("hN1Cut_pt1","p_{T}^{l, max} [GeV/c]",20,0,150);
  hN1Cut_pt2 = new TH1D("hN1Cut_pt2","p_{T}^{l, min} [GeV/c]",20,0,150);
  hN1Cut_MET = new TH1D("hN1Cut_MET","PF #slash{E}_{T} [GeV]",25,0,200);
  hN1Cut_mll = new TH1D("hN1Cut_mll","m_{ll} [GeV/c^{2}]",10,0,600);
  hN1Cut_ptll = new TH1D("hN1Cut_ptll","p_{T}^{ll} [GeV/c]",20,0,150);
  hN1Cut_mpMET = new TH1D("hN1Cut_mpMET","min(Proj. PF #slash{E}_{T}, ch #slash{E}_{T}) [GeV]",25,0,200);
  h2_mH_pt1 = new TH2D("h2_mH_pt1","Higgs mass vs Leading lepton pt", 20,0,1000,20,0,150);
  h2_mH_pt2 = new TH2D("h2_mH_pt2","Higgs mass vs Trailing lepton pt",20,0,1000,20,0,150);
  h2_mH_MET = new TH2D("h2_mH_MET","Higgs mass vs MET",20,0,1000,25,0,200);
  h2_mH_mpMET = new TH2D("h2_mH_mpMET","Higgs mass vs min. proj. MET",20,0,1000,25,0,200);
  h2_mH_mll = new TH2D("h2_mH_mll","Higgs mass vs DiLepton mass",20,0,1000,20,0,600);
  h2_mH_ptll = new TH2D("h2_mH_ptll","Higgs mass vs DiLepton pt",20,0,1000,20,0,150);
  h2_mH_mtH = new TH2D("h2_mH_mtH","Higgs mass vs Higgs Transverse mass",20,0,1000,12,0,600);
  return 0;
}
int GGVvCtrPlt::FillHistNoCut()
{
  hNoCut_Hig_mass->Fill(Hig_mass,mTTW);
  hNoCut_HigT_mass->Fill(HigT_mass,mTTW);
  hNoCut_mll->Fill(DiLept_mass,mTTW);
  hNoCut_ptll->Fill(DiLept_pt,mTTW);
  hNoCut_pt1->Fill(pt1,mTTW);
  hNoCut_pt2->Fill(pt2,mTTW);
  hNoCut_MET->Fill(MET,mTTW);
  hNoCut_mpMET->Fill(mpMET,mTTW);
  hNoCut_ppfMET->Fill(ppfMET1,mTTW);
  hNoCut_ppfMET->Fill(ppfMET2,mTTW);
  hNoCut_dphill->Fill(180./PI*fabs(DiLept_dphi),mTTW);
  hNoCut_dphillmet->Fill(180./PI*fabs(dphi_MEtLL),mTTW);
  return 0;
}
int GGVvCtrPlt::FillHist()
{
  h_Hig_mass->Fill(Hig_mass,mTTW);
  h_HigT_mass->Fill(HigT_mass,mTTW);
  h_mll->Fill(DiLept_mass,mTTW);
  h_ptll->Fill(DiLept_pt,mTTW);
  h_pt1->Fill(pt1,mTTW);
  h_pt2->Fill(pt2,mTTW);
  h_MET->Fill(MET,mTTW);
  h_mpMET->Fill(mpMET,mTTW);
  h_ppfMET->Fill(ppfMET1,mTTW);
  h_ppfMET->Fill(ppfMET2,mTTW);
  h_dphill->Fill(180./PI*fabs(DiLept_dphi),mTTW);
  h_dphillmet->Fill(180./PI*fabs(dphi_MEtLL),mTTW);
  h2_mH_mtH->Fill(Hig_mass,HigT_mass,mTTW);
  return 0;
}
int GGVvCtrPlt::InitVar()
{
  nPass = 0;
  nPass_mll = 0;
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

  nEvents_OnPeak_AllCh = 0;
  nEvents_Shoulder_AllCh = 0;
  nEvents_Tail_AllCh = 0;
  return 0;
}
