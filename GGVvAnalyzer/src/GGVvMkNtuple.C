#define GGVvMkNtuple_cxx
#include "GGVvMkNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iomanip>

void GGVvMkNtuple::Loop()
{
  if (fChain == 0)
  {
    cout<<"GGvVTemplate: no fChain  Exit ############"<<endl;
    exit(-1);
  }
  gBenchmark->Start("GGVvMkNtuple");
  Ntries = fChain->GetEntries();
  cout<<"Total number of event is "<<Ntries<<endl;
  Fout<<setprecision(8)<<endl;
  Fout<<"Total Events "<<Ntries<<endl;
  for(int i(0); i<Ntries;i++)
  //for(int i(0); i<4;i++)
  {
    if(i % 1000000 == 0) cout<<i<<"th event"<<endl;

    fChain->GetEntry(i);
    Init4Event();
    DumpParticles();

    if(isMuNuEleNu)
    {
      //cout<<Hig_mass<<" "<<HigT_mass<<" "<<DiLept_mass<<" "<<DiLept_pt<<" "<<pt1<<" "<<pt2<<" "<<MET<<" "<<mpMET<<" "<<ppfMET1<<" "<<ppfMET2<<" "<<DiLept_dphi<<" "<<mTTW<<endl;
      //cout<<pt1<<"\t"<<pt2<<"\t"<<MET<<"\t"<<DiLept_mass<<"\t"<<DiLept_pt<<"\t"<<mpMET<<endl;
      //cout<<i<<" Event Higgs Mass (from EleMu channel): "<<Hig_mass<<endl;
      if(LooseCut()>0)
      //if(CommonCut()>0)
      {
        FillHist();
        nPass++;
      }
    }
  }
  Fout<<"ElMu Ch. - Selected Events(LooseCut): "<<nPass<<endl;
  OutTFile->Write();
  OutTFile->Close();
  Fout.close();
  gBenchmark->Show("GGVvMkNtuple");
  
}

int GGVvMkNtuple::InitHistogram()
{
  TString FoutName;
  FoutName = mDirName+"/"+mMode+".txt";
  Fout.open(FoutName);
  OutTFile = new TFile(mDirName+"/"+mMode+".root","RECREATE");
  h_Hig_mass    = new TH1D("h_Hig_mass","m_{H} [GeV/c^{2}]",100,0,1000);

  ggTree = new TTree("ggTree","variables from ggF");
  ggTree->Branch("mHig",&Hig_mass);
  ggTree->Branch("mll",&DiLept_mass);
  ggTree->Branch("ptll",&DiLept_pt);
  
  return 0;
}
int GGVvMkNtuple::FillHist()
{
  ggTree->Fill();
  h_Hig_mass->Fill(Hig_mass,mTTW);
  return 0;
}
int GGVvMkNtuple::InitVar()
{
  nPass = 0;
  return 0;
}
