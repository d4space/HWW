#define GGVvTemplate_cxx
#include "GGVvTemplate.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void GGVvTemplate::Loop()
{
  if (fChain == 0)
  {
    cout<<"GGvVTemplate: no fChain  Exit ############"<<endl;
    exit(-1);
  }
  gBenchmark->Start("GGVvTemplate");
  Ntries = fChain->GetEntries();
  cout<<"Total number of event is "<<Ntries<<endl;
  for (int i(0); i<Ntries;i++)
  {
    if(i % 1000 == 0) cout<<i<<"th event"<<endl;
    fChain->GetEntry(i);
  }
  OutTFile->Write();
  gBenchmark->Show("GGVvTemplate");
}

int GGVvTemplate::InitHistogram()
{
  OutTFile = new TFile(mDirName+"/"+mMode+".root","RECREATE");
  return 0;
}
int GGVvTemplate::InitVar()
{
  return 0;
}
