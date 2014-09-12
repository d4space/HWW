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
  
  Fout<<fixed<<setprecision(2)<<endl;
  //Fout<<"Recolvl:\t Event\t Lumi\t Channel  lep1 ID(pt)\t nu1 ID(pt)\t lep2 ID(pt)\t nu2 ID(pt)"<<endl;
  //Fout<<"Recolvl:     Event   Channel   ch1	 ch2   sameflav"<<endl;
  for (int i(0); i<Ntries;i++)
  //for (int i(0); i<10;i++)
  {
    if (i==1)
      Fout<<"baseW: "<<baseW<<endl;
    InitVar4Evt();
    evtCnt++;
    fChain->GetEntry(i);
    //Fout<<"noSelect:\t"<<i<<"\t"<<channel<<"\t"<<ch1<<"\t"<<ch2<<"\t"<<sameflav<<endl;

    if(Cut == "LooseCut")if(LooseCut()!=1) continue;
    if(Cut == "CommonCut")if(CommonCut()!=1) continue;
    EvtWeight = CalcWeight();
    if (OF0jCut() == 1){
      //Fout<<"OF0j:\t\t"<<i<<"\t"<<channel<<"\t"<<ch1<<"\t"<<ch2<<"\t"<<sameflav<<endl;
      if (channel ==2 || channel ==3){}else{Fout<<"Channel is not OF0j: "<<channel<<endl;} //Checking channel from RecoLvl
      //NselectOF0j++;
      ntruth_OF0j[0] += EvtWeight; //RecoLvl OF elmu and muel events
      if (channel ==2)
	ntruth_OF0j[1] += EvtWeight; //RecoLvl OF elmu events
      if (channel ==3)
	ntruth_OF0j[2] += EvtWeight; //RecoLvl OF events muel events
      if((leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron) || (leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon)){
	ntruth_OF0j[3] += EvtWeight; //genLvl OF events
	if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon)
	  ntruth_OF0j[4] += EvtWeight; //genLvl OF events
	if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron)
	  ntruth_OF0j[5] += EvtWeight; //genLvl OF events
	//if(event<1001)
	//  Fout<<"OF0j(truth)\t"<<event<<"\t"<<lumi<<"\t"<<channel<<"\t"<<leptonGenpid1<<"("<<leptonGenpt1<<")\t"<<neutrinoGenpid1<<"("<<neutrinoGenpt1<<")\t"<<leptonGenpid2<<"("<<leptonGenpt2<<")\t"<<neutrinoGenpid2<<"("<<neutrinoGenpt2<<")"<<endl;
      }else{
	nfake_OF0j[0] += EvtWeight;  //genLvl total Fake events
	//if(event<1001)
	//  Fout<<"OF0j(fake)\t"<<event<<"\t"<<lumi<<"\t"<<channel<<"\t"<<leptonGenpid1<<"("<<leptonGenpt1<<")\t"<<neutrinoGenpid1<<"("<<neutrinoGenpt1<<")\t"<<leptonGenpid2<<"("<<leptonGenpt2<<")\t"<<neutrinoGenpid2<<"("<<neutrinoGenpt2<<")"<<endl;
      }
      if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kMuon){
	nfake_OF0j[1] += EvtWeight;  //genLvl Fake events - mumu
      }else if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kTau){
	nfake_OF0j[2] += EvtWeight;  //genLvl Fake events - mutau
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kElectron){
	nfake_OF0j[3] += EvtWeight;  //genLvl Fake events - elel
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kTau){
	nfake_OF0j[4] += EvtWeight;  //genLvl Fake events - eltau
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kMuon){
	nfake_OF0j[5] += EvtWeight;  //genLvl Fake events - taumu
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kElectron){
	nfake_OF0j[6] += EvtWeight;  //genLvl Fake events - tauel
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kTau){
	nfake_OF0j[7] += EvtWeight;  //genLvl Fake events - tautau
      }
    }else if(OF1jCut() == 1){
      //Fout<<"OF1j:\t\t"<<i<<"\t"<<channel<<"\t"<<ch1<<"\t"<<ch2<<"\t"<<sameflav<<endl;
      if(channel ==2 || channel ==3){}else{Fout<<"Channel is not OF1j: "<<channel<<endl;}
      //NselectOF1j++;
      ntruth_OF1j[0] += EvtWeight; //RecoLvl OF events
      if(channel ==2)
	ntruth_OF1j[1] += EvtWeight;
      if(channel ==3)
	ntruth_OF1j[2] += EvtWeight;
      if((leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron) || (leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon)){
	ntruth_OF1j[3] += EvtWeight; //genLvl OF events
	if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon)
	  ntruth_OF1j[4] += EvtWeight;
	if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron)
	  ntruth_OF1j[5] += EvtWeight;
	//if(event<1001)
	//  Fout<<"OF1j(truth)\t"<<event<<"\t"<<lumi<<"\t"<<channel<<"\t"<<leptonGenpid1<<"("<<leptonGenpt1<<")\t"<<neutrinoGenpid1<<"("<<neutrinoGenpt1<<")\t"<<leptonGenpid2<<"("<<leptonGenpt2<<")\t"<<neutrinoGenpid2<<"("<<neutrinoGenpt2<<")"<<endl;
      }else{
	//if(event<1001)
	//  Fout<<"OF1j(fake)\t"<<event<<"\t"<<lumi<<"\t"<<channel<<"\t"<<leptonGenpid1<<"("<<leptonGenpt1<<")\t"<<neutrinoGenpid1<<"("<<neutrinoGenpt1<<")\t"<<leptonGenpid2<<"("<<leptonGenpt2<<")\t"<<neutrinoGenpid2<<"("<<neutrinoGenpt2<<")"<<endl;
	nfake_OF1j[0] += EvtWeight;  //genLvl total Fake events
      }
      if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kMuon){
	nfake_OF1j[1] += EvtWeight;  //genLvl Fake events - mumu
      }else if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kTau){
	nfake_OF1j[2] += EvtWeight;  //genLvl Fake events - mutau
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kElectron){
	nfake_OF1j[3] += EvtWeight;  //genLvl Fake events - elel
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kTau){
	nfake_OF1j[4] += EvtWeight;  //genLvl Fake events - eltau
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kMuon){
	nfake_OF1j[5] += EvtWeight;  //genLvl Fake events - taumu
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kElectron){
	nfake_OF1j[6] += EvtWeight;  //genLvl Fake events - tauel
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kTau){
	nfake_OF1j[7] += EvtWeight;  //genLvl Fake events - tautau
      }
    }else if (SF0jCut() == 1){
      //Fout<<"SF0j:\t\t"<<i<<"\t"<<channel<<"\t"<<ch1<<"\t"<<ch2<<"\t"<<sameflav<<endl;
      if (channel ==0 || channel ==1){}else{Fout<<"Channel is not SF0j: "<<channel<<endl;} //Checking channel from RecoLvl
      //NselectSF0j++;
      ntruth_SF0j[0] += EvtWeight; //RecoLvl SF events
      if((leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kMuon) || (leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kElectron)){
	ntruth_SF0j[1] += EvtWeight; //genLvl SF events
	//if(event<1001)
	//  Fout<<"SF0j(truth)\t"<<event<<"\t"<<lumi<<"\t"<<channel<<"\t"<<leptonGenpid1<<"("<<leptonGenpt1<<")\t"<<neutrinoGenpid1<<"("<<neutrinoGenpt1<<")\t"<<leptonGenpid2<<"("<<leptonGenpt2<<")\t"<<neutrinoGenpid2<<"("<<neutrinoGenpt2<<")"<<endl;
      }else{
	nfake_SF0j[0] += EvtWeight;  //genLvl total Fake events
	//if(event<1001)
	//  Fout<<"SF0j(fake)\t"<<event<<"\t"<<lumi<<"\t"<<channel<<"\t"<<leptonGenpid1<<"("<<leptonGenpt1<<")\t"<<neutrinoGenpid1<<"("<<neutrinoGenpt1<<")\t"<<leptonGenpid2<<"("<<leptonGenpt2<<")\t"<<neutrinoGenpid2<<"("<<neutrinoGenpt2<<")"<<endl;
      }
      if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron){
	nfake_SF0j[1] += EvtWeight;  //genLvl Fake events - muele
      }else if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kTau){
	nfake_SF0j[2] += EvtWeight;  //genLvl Fake events - mutau
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon){
	nfake_SF0j[3] += EvtWeight;  //genLvl Fake events - elmu
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kTau){
	nfake_SF0j[4] += EvtWeight;  //genLvl Fake events - eltau
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kMuon){
	nfake_SF0j[5] += EvtWeight;  //genLvl Fake events - taumu
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kElectron){
	nfake_SF0j[6] += EvtWeight;  //genLvl Fake events - tauel
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kTau){
	nfake_SF0j[7] += EvtWeight;  //genLvl Fake events - tautau
      }
    }else if (SF1jCut() == 1){
      //Fout<<"SF1j:\t\t"<<i<<"\t"<<channel<<"\t"<<ch1<<"\t"<<ch2<<"\t"<<sameflav<<endl;
      if (channel ==0 || channel ==1){}else{Fout<<"Channel is not SF1j: "<<channel<<endl;}
      //NselectSF1j++;
      ntruth_SF1j[0] += EvtWeight; //RecoLvl SF events
      if((leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kMuon) || (leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kElectron)){
	ntruth_SF1j[1] += EvtWeight; //genLvl SF events
	//if(event<1001)
	//  Fout<<"SF1j(truth)\t"<<event<<"\t"<<lumi<<"\t"<<channel<<"\t"<<leptonGenpid1<<"("<<leptonGenpt1<<")\t"<<neutrinoGenpid1<<"("<<neutrinoGenpt1<<")\t"<<leptonGenpid2<<"("<<leptonGenpt2<<")\t"<<neutrinoGenpid2<<"("<<neutrinoGenpt2<<")"<<endl;
      }else{
	//if(event<1001)
	//  Fout<<"SF1j(fake)\t"<<event<<"\t"<<lumi<<"\t"<<channel<<"\t"<<leptonGenpid1<<"("<<leptonGenpt1<<")\t"<<neutrinoGenpid1<<"("<<neutrinoGenpt1<<")\t"<<leptonGenpid2<<"("<<leptonGenpt2<<")\t"<<neutrinoGenpid2<<"("<<neutrinoGenpt2<<")"<<endl;
	nfake_SF1j[0] += EvtWeight;  //genLvl total Fake events
      }
      if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kElectron){
	nfake_SF1j[1] += EvtWeight;  //genLvl Fake events - muel
      }else if(leptonGenpid1 == GenType::kMuon && leptonGenpid2 == GenType::kTau){
	nfake_SF1j[2] += EvtWeight;  //genLvl Fake events - mutau
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kMuon){
	nfake_SF1j[3] += EvtWeight;  //genLvl Fake events - elmu
      }else if(leptonGenpid1 == GenType::kElectron && leptonGenpid2 == GenType::kTau){
	nfake_SF1j[4] += EvtWeight;  //genLvl Fake events - eltau
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kMuon){
	nfake_SF1j[5] += EvtWeight;  //genLvl Fake events - taumu
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kElectron){
	nfake_SF1j[6] += EvtWeight;  //genLvl Fake events - tauel
      }else if(leptonGenpid1 == GenType::kTau && leptonGenpid2 == GenType::kTau){
	nfake_SF1j[7] += EvtWeight;  //genLvl Fake events - tautau
      }
    }
  }

  //Fout<<"NselectSF0j: "<<NselectSF0j<<endl;
  //Fout<<"NselectSF1j: "<<NselectSF1j<<endl;
  //Fout<<"Nselect: "<<Nselect<<endl;
  Fout<<"============================================="<<endl;
  Fout<<""<<endl;
  //Fout<<"Lept1_Plus Lept2_Minus"<<endl;
  Fout<<SampleName<<endl;
  Fout<<"OF0j"<<endl;
  Fout<<"EleMu (RecLvl):\t"<<ntruth_OF0j[0]<<endl;
  Fout<<"EleMu (only):\t"  <<ntruth_OF0j[1]<<" ("<<ntruth_OF0j[1]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"MuEle (only):\t"  <<ntruth_OF0j[2]<<" ("<<ntruth_OF0j[2]/ntruth_OF0j[0]*100<<" %)"<<endl;
  Fout<<"EleMu (genLvl):\t"<<ntruth_OF0j[3]<<" ("<<ntruth_OF0j[3]/ntruth_OF0j[0]*100<<" %)"<<endl;
  //Fout<<"EleMu (genLvl):\t"<<ntruth_OF0j[4]<<" ("<<ntruth_OF0j[4]/ntruth_OF0j[0]*100<<" %)"<<endl;
  //Fout<<"MuEle (genLvl):\t"<<ntruth_OF0j[5]<<" ("<<ntruth_OF0j[5]/ntruth_OF0j[0]*100<<" %)"<<endl;
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
  Fout<<"EleMu (only):\t"  <<ntruth_OF1j[1]<<" ("<<ntruth_OF1j[1]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"MuEle (only):\t"  <<ntruth_OF1j[2]<<" ("<<ntruth_OF1j[2]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"EleMu (genLvl):\t"<<ntruth_OF1j[3]<<" ("<<ntruth_OF1j[3]/ntruth_OF1j[0]*100<<" %)"<<endl;
  //Fout<<"EleMu (genLvl):\t"<<ntruth_OF1j[4]<<" ("<<ntruth_OF1j[4]/ntruth_OF1j[0]*100<<" %)"<<endl;
  //Fout<<"MuEle (genLvl):\t"<<ntruth_OF1j[5]<<" ("<<ntruth_OF1j[5]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"Tot.Fake (genLvl):\t"<<nfake_OF1j[0]<<" ("<<nfake_OF1j[0]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"mumu fake (genLvl):\t"<<nfake_OF1j[1]<<" ("<<nfake_OF1j[1]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"mutau fake (genLvl):\t"<<nfake_OF1j[2]<<" ("<<nfake_OF1j[2]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"elel fake (genLvl):\t"<<nfake_OF1j[3]<<" ("<<nfake_OF1j[3]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"eltau fake (genLvl):\t"<<nfake_OF1j[4]<<" ("<<nfake_OF1j[4]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"taumu fake (genLvl):\t"<<nfake_OF1j[5]<<" ("<<nfake_OF1j[5]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"tauel fake (genLvl):\t"<<nfake_OF1j[6]<<" ("<<nfake_OF1j[6]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"tautau fake (genLvl):\t"<<nfake_OF1j[7]<<" ("<<nfake_OF1j[7]/ntruth_OF1j[0]*100<<" %)"<<endl;
  Fout<<"Checking Fake nEvents (genLvl):\t"<< nfake_OF1j[0]<<" = "<<nfake_OF1j[1]+nfake_OF1j[2]+nfake_OF1j[3]+nfake_OF1j[4]+nfake_OF1j[5]+nfake_OF1j[6]+nfake_OF1j[7]<<endl;
  Fout<<""<<endl;
  Fout<<"SF0j"<<endl;
  Fout<<"EleEle & MuMu (RecLvl):\t"<<ntruth_SF0j[0]<<endl;
  Fout<<"EleEle & MuMu (genLvl):\t"<<ntruth_SF0j[1]<<" ("<<ntruth_SF0j[1]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"Tot.Fake (genLvl):\t"<<nfake_SF0j[0]<<" ("<<nfake_SF0j[0]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"muel fake (genLvl):\t"<<nfake_SF0j[1]<<" ("<<nfake_SF0j[1]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"mutau fake (genLvl):\t"<<nfake_SF0j[2]<<" ("<<nfake_SF0j[2]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"elmu fake (genLvl):\t"<<nfake_SF0j[3]<<" ("<<nfake_SF0j[3]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"eltau fake (genLvl):\t"<<nfake_SF0j[4]<<" ("<<nfake_SF0j[4]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"taumu fake (genLvl):\t"<<nfake_SF0j[5]<<" ("<<nfake_SF0j[5]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"tauel fake (genLvl):\t"<<nfake_SF0j[6]<<" ("<<nfake_SF0j[6]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"tautau fake (genLvl):\t"<<nfake_SF0j[7]<<" ("<<nfake_SF0j[7]/ntruth_SF0j[0]*100<<" %)"<<endl;
  Fout<<"Checking Fake nEvents (genLvl):\t"<< nfake_SF0j[0]<<" = "<<nfake_SF0j[1]+nfake_SF0j[2]+nfake_SF0j[3]+nfake_SF0j[4]+nfake_SF0j[5]+nfake_SF0j[6]+nfake_SF0j[7]<<endl;
  Fout<<""<<endl;
  Fout<<"SF1j"<<endl;
  Fout<<"EleEle & MuMu (RecLvl):\t"<<ntruth_SF1j[0]<<endl;
  Fout<<"EleEle & MuMu (genLvl):\t"<<ntruth_SF1j[1]<<" ("<<ntruth_SF1j[1]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"Tot.Fake (genLvl):\t"<<nfake_SF1j[0]<<" ("<<nfake_SF1j[0]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"muel fake (genLvl):\t"<<nfake_SF1j[1]<<" ("<<nfake_SF1j[1]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"mutau fake (genLvl):\t"<<nfake_SF1j[2]<<" ("<<nfake_SF1j[2]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"elmu fake (genLvl):\t"<<nfake_SF1j[3]<<" ("<<nfake_SF1j[3]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"eltau fake (genLvl):\t"<<nfake_SF1j[4]<<" ("<<nfake_SF1j[4]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"taumu fake (genLvl):\t"<<nfake_SF1j[5]<<" ("<<nfake_SF1j[5]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"tauel fake (genLvl):\t"<<nfake_SF1j[6]<<" ("<<nfake_SF1j[6]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"tautau fake (genLvl):\t"<<nfake_SF1j[7]<<" ("<<nfake_SF1j[7]/ntruth_SF1j[0]*100<<" %)"<<endl;
  Fout<<"Checking Fake nEvents (genLvl):\t"<< nfake_SF1j[0]<<" = "<<nfake_SF1j[1]+nfake_SF1j[2]+nfake_SF1j[3]+nfake_SF1j[4]+nfake_SF1j[5]+nfake_SF1j[6]+nfake_SF1j[7]<<endl;
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
  //Nselect = 0;
  //NselectSF0j = 0;
  //NselectSF1j = 0;
  //NselectOF0j = 0;
  //NselectOF1j = 0;

  //Efficiency
  for(int i1(0); i1<6; i1++)
  {
    ntruth_OF0j[i1] = 0;
    ntruth_OF1j[i1] = 0;
    ntruth_SF0j[i1] = 0;
    ntruth_SF1j[i1] = 0;
  }
  for(int i1(0); i1<8; i1++)
  {
    nfake_OF0j[i1] = 0;
    nfake_OF1j[i1] = 0;
    nfake_SF0j[i1] = 0;
    nfake_SF1j[i1] = 0;
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
