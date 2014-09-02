#define HWwNEvents_cxx
#include "HWwNEvents.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include <algorithm>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

void HWwNEvents::Loop()
{
  gBenchmark->Start("HWwNEvents");
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
    //cout<<"Event #"<<i<<" Neu(Lept) "<<neutrinoGenpid1<<" "<<leptonGenpid1<<" "<<neutrinoGenpid2<<" "<<leptonGenpid2<<" "<<ch1<<" "<<ch2<<endl;

    if(Cut == "LooseCut")if(LooseCut()!=1) continue;
    if(Cut == "CommonCut")if(CommonCut()!=1) continue;
    if (OF0jCut() == 1){
      if (channel ==2 || channel ==3){}else{Fout<<"Channel is not OF0j: "<<channel<<endl;} //Checking channel from RecoLvl
      //NselectOF0j++;
      ntruth_OF0j[0]++; //RecoLvl OF events
      if((leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron) || (leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon)){
	ntruth_OF0j[1]++; //genLvl OF events
      }else{
	nfake_OF0j[0]++;  //genLvl total Fake events
      }
      if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kMuon){
	nfake_OF0j[1]++;  //genLvl Fake events - mumu
      }else if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kTau){
	nfake_OF0j[2]++;  //genLvl Fake events - mutau
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kElectron){
	nfake_OF0j[3]++;  //genLvl Fake events - elel
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kTau){
	nfake_OF0j[4]++;  //genLvl Fake events - eltau
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kMuon){
	nfake_OF0j[5]++;  //genLvl Fake events - taumu
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kElectron){
	nfake_OF0j[6]++;  //genLvl Fake events - tauel
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kTau){
	nfake_OF0j[7]++;  //genLvl Fake events - tautau
      }
    }else if (OF1jCut() == 1){
      if (channel ==2 || channel ==3){}else{Fout<<"Channel is not OF1j: "<<channel<<endl;}
      //NselectOF1j++;
      ntruth_OF1j[0]++; //RecoLvl OF events
      if((leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron) || (leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon)){
	ntruth_OF1j[1]++; //genLvl OF events
      }else{
	nfake_OF1j[0]++;  //genLvl total Fake events
      }
      if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kMuon){
	nfake_OF1j[1]++;  //genLvl Fake events - mumu
      }else if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kTau){
	nfake_OF1j[2]++;  //genLvl Fake events - mutau
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kElectron){
	nfake_OF1j[3]++;  //genLvl Fake events - elel
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kTau){
	nfake_OF1j[4]++;  //genLvl Fake events - eltau
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kMuon){
	nfake_OF1j[5]++;  //genLvl Fake events - taumu
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kElectron){
	nfake_OF1j[6]++;  //genLvl Fake events - tauel
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kTau){
	nfake_OF1j[7]++;  //genLvl Fake events - tautau
      }
    }else if (SF0jCut() == 1)NselectSF0j++;
    else if (SF1jCut() == 1) NselectSF1j++;
  }

  Fout<<"NselectSF0j: "<<NselectSF0j<<endl;
  Fout<<"NselectSF1j: "<<NselectSF1j<<endl;
  Fout<<"Nselect: "<<Nselect<<endl;
  Fout<<"============================================="<<endl;
  Fout<<""<<endl;
  //Fout<<"Lept1_Plus Lept2_Minus"<<endl;
  Fout<<SampleName<<endl;
  Fout<<"OF0j"<<endl;
  Fout<<"EleMu (RecLvl):\t"<<ntruth_OF0j[0]<<endl;
  Fout<<"EleMu (genLvl):\t"<<ntruth_OF0j[1]<<" ("<<ntruth_OF0j[1]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"Tot.Fake (genLvl):\t"<<nfake_OF0j[0]<<" ("<<nfake_OF0j[0]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"mumu fake (genLvl):\t"<<nfake_OF0j[1]<<" ("<<nfake_OF0j[1]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"mutau fake (genLvl):\t"<<nfake_OF0j[2]<<" ("<<nfake_OF0j[2]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"elel fake (genLvl):\t"<<nfake_OF0j[3]<<" ("<<nfake_OF0j[3]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"eltau fake (genLvl):\t"<<nfake_OF0j[4]<<" ("<<nfake_OF0j[4]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"taumu fake (genLvl):\t"<<nfake_OF0j[5]<<" ("<<nfake_OF0j[5]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"tauel fake (genLvl):\t"<<nfake_OF0j[6]<<" ("<<nfake_OF0j[6]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"tautau fake (genLvl):\t"<<nfake_OF0j[7]<<" ("<<nfake_OF0j[7]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"Checking Fake nEvents (genLvl):\t"<< nfake_OF0j[0]<<" = "<<nfake_OF0j[1]+nfake_OF0j[2]+nfake_OF0j[3]+nfake_OF0j[4]+nfake_OF0j[5]+nfake_OF0j[6]+nfake_OF0j[7]<<endl;
  Fout<<""<<endl;
  Fout<<"OF1j"<<endl;
  Fout<<"EleMu (RecLvl):\t"<<ntruth_OF1j[0]<<endl;
  Fout<<"EleMu (genLvl):\t"<<ntruth_OF1j[1]<<" ("<<ntruth_OF1j[1]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"Tot.Fake (genLvl):\t"<<nfake_OF1j[0]<<" ("<<nfake_OF1j[0]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"mumu fake (genLvl):\t"<<nfake_OF1j[1]<<" ("<<nfake_OF1j[1]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"mutau fake (genLvl):\t"<<nfake_OF1j[2]<<" ("<<nfake_OF1j[2]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"elel fake (genLvl):\t"<<nfake_OF1j[3]<<" ("<<nfake_OF1j[3]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"eltau fake (genLvl):\t"<<nfake_OF1j[4]<<" ("<<nfake_OF1j[4]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"taumu fake (genLvl):\t"<<nfake_OF1j[5]<<" ("<<nfake_OF1j[5]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"tauel fake (genLvl):\t"<<nfake_OF1j[6]<<" ("<<nfake_OF1j[6]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"tautau fake (genLvl):\t"<<nfake_OF1j[7]<<" ("<<nfake_OF1j[7]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"Checking Fake nEvents (genLvl):\t"<< nfake_OF1j[0]<<" = "<<nfake_OF1j[1]+nfake_OF1j[2]+nfake_OF1j[3]+nfake_OF1j[4]+nfake_OF1j[5]+nfake_OF1j[6]+nfake_OF1j[7]<<endl;
  // Usie one of the Write_Histo ro myFile->Write
  // Write_Histo: to write specific ones
  // myFile->Write ==> All
    
  //Write_Histo();
  //myFile->Write();
  //myFile->Close();
  Fout.close();
  gBenchmark->Show("HWwNEvents");
}
int HWwNEvents::Fill_Histo()
{
  return 0;
}
int HWwNEvents::InitVar()
{
  TString FoutName = mResultDir+"/"+SampleName+"_"+Cut+".txt";
  Fout.open(FoutName);
  evtCnt = 0;
  Nselect = 0;
  NselectSF0j = 0;
  NselectSF1j = 0;
  NselectOF0j = 0;
  NselectOF1j = 0;

  //Efficiency
  for(int i1(0); i1<2; i1++)
  {
    ntruth_OF0j[i1] = 0;
    ntruth_OF1j[i1] = 0;
  }
  for(int i1(0); i1<8; i1++)
  {
    nfake_OF0j[i1] = 0;
    nfake_OF1j[i1] = 0;
  }

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
int HWwNEvents::InitVar4Evt()
{
  return 0;
}
int HWwNEvents::InitHistogram()
{
  //myFile = new TFile(mResultDir+"/"+SampleName+"_"+Cut+".root","RECREATE");
  return 0;
}
int Write_Histo()
{
  return 0;
}
