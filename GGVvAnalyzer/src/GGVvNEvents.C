#define GGVvNEvents_cxx
#include "GGVvNEvents.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iomanip>

void GGVvNEvents::Loop()
{
  if (fChain == 0)
  {
    cout<<"GGvVTemplate: no fChain  Exit ############"<<endl;
    exit(-1);
  }
  gBenchmark->Start("GGVvNEvents");
  Ntries = fChain->GetEntries();
  cout<<"Total number of event is "<<Ntries<<endl;
  Fout<<setprecision(8)<<endl;
  Fout<<"Total Events "<<Ntries<<endl;
  for(int i(0); i<Ntries;i++)
  //for(int i(0); i<10;i++)
  {
    if(i % 1000000 == 0) cout<<i<<"th event"<<endl;

    fChain->GetEntry(i);
    Init4Event();
    //for(int j(0); j<kMaxParticle;j++)
    //{
    //  cout<<i<<" Event - Particle (idx,Id, Status): "<<j<<"  "<<Particle_PID[j]<<" "<<Particle_Status[j]<<endl;
    //}
    Nselected4Bin();
  }
  Fout<<""<<endl;
  Fout<<"Lept1_Lept2 (Charge free)"<<endl;
  Fout<<"MuEle:\t"<<numOfmuele<<"\t"<<numOfmuele/Ntries*100<<" %"<<endl;
  Fout<<"MuTau:\t"<<numOfmutau<<"\t"<<numOfmutau/Ntries*100<<" %"<<endl;
  Fout<<"EleMu:\t"<<numOfelemu<<"\t"<<numOfelemu/Ntries*100<<" %"<<endl;
  Fout<<"EleTau:\t"<<numOfeletau<<"\t"<<numOfeletau/Ntries*100<<" %"<<endl;
  Fout<<"TauMu:\t"<<numOftaumu<<"\t"<<numOftaumu/Ntries*100<<" %"<<endl;
  Fout<<"TauEle:\t"<<numOftauele<<"\t"<<numOftauele/Ntries*100<<" %"<<endl;
  Fout<<"Sum:\t"<<numOfmuele+numOfmutau+numOfelemu+numOfeletau+numOftaumu+numOftauele<<endl;

  Fout<<""<<endl;
  Fout<<"Lept1_Plus Lept2_Minus"<<endl;
  Fout<<"MuP_EleM:\t" <<numOf_mp_em<<"\t"<<numOf_mp_em/Ntries*100<<" %"<<endl;
  Fout<<"MuP_TauM:\t" <<numOf_mp_tm<<"\t"<<numOf_mp_tm/Ntries*100<<" %"<<endl;
  Fout<<"EleP_MuM:\t" <<numOf_ep_mm<<"\t"<<numOf_ep_mm/Ntries*100<<" %"<<endl;
  Fout<<"EleP_TauM:\t"<<numOf_ep_tm<<"\t"<<numOf_ep_tm/Ntries*100<<" %"<<endl;
  Fout<<"TauP_MuM:\t" <<numOf_tp_mm<<"\t"<<numOf_tp_mm/Ntries*100<<" %"<<endl;
  Fout<<"TauP_EleM:\t"<<numOf_tp_em<<"\t"<<numOf_tp_em/Ntries*100<<" %"<<endl;
  Fout<<"Sum:\t"<<numOf_mp_em+numOf_mp_tm+numOf_ep_mm+numOf_ep_tm+numOf_tp_mm+numOf_tp_em<<endl;

  Fout<<""<<endl;
  Fout<<"Lept1_Minus Lept2_Plus"<<endl;
  Fout<<"MuM_EleP:\t" <<numOf_mm_ep<<"\t"<<numOf_mm_ep/Ntries*100<<" %"<<endl;
  Fout<<"MuM_TauP:\t" <<numOf_mm_tp<<"\t"<<numOf_mm_tp/Ntries*100<<" %"<<endl;
  Fout<<"EleM_MuP:\t" <<numOf_em_mp<<"\t"<<numOf_em_mp/Ntries*100<<" %"<<endl;
  Fout<<"EleM_TauP:\t"<<numOf_em_tp<<"\t"<<numOf_em_tp/Ntries*100<<" %"<<endl;
  Fout<<"TauM_MuP:\t" <<numOf_tm_mp<<"\t"<<numOf_tm_mp/Ntries*100<<" %"<<endl;
  Fout<<"TauM_EleP:\t"<<numOf_tm_ep<<"\t"<<numOf_tm_ep/Ntries*100<<" %"<<endl;
  Fout<<"Sum:\t"<<numOf_mm_ep+numOf_mm_tp+numOf_em_mp+numOf_em_tp+numOf_tm_mp+numOf_tm_ep<<endl;
  Fout.close();
  gBenchmark->Show("GGVvNEvents");
}

int GGVvNEvents::Nselected4Bin()
{
  //No charge dependence
  if(fabs(Particle_PID[3]) == int(GenType::kMuon) && fabs(Particle_PID[2]) == int(GenType::kmuNeutrino))
  {
    if(fabs(Particle_PID[5]) == int(GenType::kElectron) && fabs(Particle_PID[4]) == int(GenType::keNeutrino))
    {
      numOfmuele++;
    }else if(fabs(Particle_PID[5]) == int(GenType::kTau) && fabs(Particle_PID[4]) == int(GenType::ktauNeutrino))
    {
      numOfmutau++;
    }
  }else if(fabs(Particle_PID[3]) == int(GenType::kElectron) && fabs(Particle_PID[2]) == int(GenType::keNeutrino))
  {
    if(fabs(Particle_PID[5]) == int(GenType::kMuon) && fabs(Particle_PID[4]) == int(GenType::kmuNeutrino))
    {
      numOfelemu++;
    }else if(fabs(Particle_PID[5]) == int(GenType::kTau) && fabs(Particle_PID[4]) == int(GenType::ktauNeutrino))
    {
      numOfeletau++;
    }
  }else if(fabs(Particle_PID[3]) == int(GenType::kTau) && fabs(Particle_PID[2]) == int(GenType::ktauNeutrino))
  {
    if(fabs(Particle_PID[5]) == int(GenType::kMuon) && fabs(Particle_PID[4]) == int(GenType::kmuNeutrino))
    {
      numOftaumu++;
    }else if(fabs(Particle_PID[5]) == int(GenType::kElectron) && fabs(Particle_PID[4]) == int(GenType::keNeutrino))
    {
      numOftauele++;
    }
  }else{
    Fout<<"Some Event is strange!"<<endl;
  }
  
  //Charge dependence: Lept1P_Lept2M
  if(Particle_PID[3] == -int(GenType::kMuon) && Particle_PID[2] == int(GenType::kmuNeutrino))
  {
    if(Particle_PID[5] == int(GenType::kElectron) && Particle_PID[4] == -int(GenType::keNeutrino))
    {
      numOf_mp_em++;
    }else if(Particle_PID[5] == int(GenType::kTau) && Particle_PID[4] == -int(GenType::ktauNeutrino))
    {
      numOf_mp_tm++;
    }
  }else if(Particle_PID[3] == -int(GenType::kElectron) && Particle_PID[2] == int(GenType::keNeutrino))
  {
    if(Particle_PID[5] == int(GenType::kMuon) && Particle_PID[4] == -int(GenType::kmuNeutrino))
    {
      numOf_ep_mm++;
    }else if(Particle_PID[5] == int(GenType::kTau) && Particle_PID[4] == -int(GenType::ktauNeutrino))
    {
      numOf_ep_tm++;
    }
  }else if(Particle_PID[3] == -int(GenType::kTau) && Particle_PID[2] == int(GenType::ktauNeutrino))
  {
    if(Particle_PID[5] == int(GenType::kMuon) && Particle_PID[4] == -int(GenType::kmuNeutrino))
    {
      numOf_tp_mm++;
    }else if(Particle_PID[5] == int(GenType::kElectron) && Particle_PID[4] == -int(GenType::keNeutrino))
    {
      numOf_tp_em++;
    }
  }

  //Charge dependence: Lept1M_Lept2P
  if(Particle_PID[3] == int(GenType::kMuon) && Particle_PID[2] == -int(GenType::kmuNeutrino))
  {
    if(Particle_PID[5] == -int(GenType::kElectron) && Particle_PID[4] == int(GenType::keNeutrino))
    {
      numOf_mm_ep++;
    }else if(Particle_PID[5] == -int(GenType::kTau) && Particle_PID[4] == int(GenType::ktauNeutrino))
    {
      numOf_mm_tp++;
    }
  }else if(Particle_PID[3] == int(GenType::kElectron) && Particle_PID[2] == -int(GenType::keNeutrino))
  {
    if(Particle_PID[5] == -int(GenType::kMuon) && Particle_PID[4] == int(GenType::kmuNeutrino))
    {
      numOf_em_mp++;
    }else if(Particle_PID[5] == -int(GenType::kTau) && Particle_PID[4] == int(GenType::ktauNeutrino))
    {
      numOf_em_tp++;
    }
  }else if(Particle_PID[3] == int(GenType::kTau) && Particle_PID[2] == -int(GenType::ktauNeutrino))
  {
    if(Particle_PID[5] == -int(GenType::kMuon) && Particle_PID[4] == int(GenType::kmuNeutrino))
    {
      numOf_tm_mp++;
    }else if(Particle_PID[5] == -int(GenType::kElectron) && Particle_PID[4] == int(GenType::keNeutrino))
    {
      numOf_tm_ep++;
    }
  }
}
int GGVvNEvents::InitHistogram()
{
  TString FoutName;
  FoutName = mDirName+"/"+mMode+".txt";
  Fout.open(FoutName);
  return 0;
}
int GGVvNEvents::InitVar()
{
  numOfmuele = 0;
  numOfelemu = 0;
  numOfmutau = 0;
  numOftaumu = 0;
  numOfeletau = 0;
  numOftauele = 0;
  
  numOf_mp_em = 0;
  numOf_mp_tm = 0;
  numOf_ep_mm = 0;
  numOf_ep_tm = 0;
  numOf_tp_mm = 0;
  numOf_tp_em = 0;

  numOf_mm_ep = 0;
  numOf_mm_tp = 0;
  numOf_em_mp = 0;
  numOf_em_tp = 0;
  numOf_tm_mp = 0;
  numOf_tm_ep = 0;
  return 0;
}
