
#include <iostream>
#include <map>

#include "TROOT.h"
#include "TApplication.h"

#include "TFile.h"
#include "TChain.h"
#include "TString.h"

#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLorentzVector.h"

#include "LHEF.h"

#include "ExRootAnalysis/ExRootClasses.h"

#include "ExRootAnalysis/ExRootTreeWriter.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"

#include "ExRootAnalysis/ExRootUtilities.h"
#include "ExRootAnalysis/ExRootProgressBar.h"

#include "../../Utils/const.h"

using namespace std;

//---------------------------------------------------------------------------

void AnalyseEvent(LHEF::Reader *reader, Long64_t eventNumber)
//void AnalyseEvent(LHEF::Reader *reader, ExRootTreeBranch *branch, Long64_t eventNumber)
{
  const LHEF::HEPEUP &hepeup = reader->hepeup;

  //TRootLHEFEvent *element;

  //element = (TRootLHEFEvent*) branch->NewEntry();


  //element->Number = eventNumber;
  //element->Nparticles = hepeup.NUP;
  //element->ProcessID = hepeup.IDPRUP;
  //element->Weight = hepeup.XWGTUP;
  //element->ScalePDF = hepeup.SCALUP;
  //element->CouplingQED = hepeup.AQEDUP;
  //element->CouplingQCD = hepeup.AQCDUP;
}

//---------------------------------------------------------------------------

int AnalyseParticles(LHEF::Reader *reader)
//void AnalyseParticles(LHEF::Reader *reader, ExRootTreeBranch *branch)
{
  const LHEF::HEPEUP &hepeup = reader->hepeup;

  Int_t particle;
  Double_t signPz, cosTheta;

  TLorentzVector	momentum;
  TLorentzVector	mu_TL;
  bool			mu_is = false;
  TLorentzVector	muNu_TL;
  bool			muNu_is = false;
  TLorentzVector	el_TL;
  bool			el_is = false;
  TLorentzVector	eNu_TL;
  bool			eNu_is = false;
  TLorentzVector	tau_TL;
  bool			tau_is = false;
  TLorentzVector	tauNu_TL;
  bool			tauNu_is = false;

  TLorentzVector	Lepton4_TL(0, 0, 0, 0);
  int numOfLeptons(0);
  double  ptc_PID; 
  double  ptc_Status;
  double  ptc_Mother1;
  double  ptc_Mother2;
  double  ptc_ColorLine1;
  double  ptc_ColorLine2;
  double  ptc_Px;
  double  ptc_Py;
  double  ptc_Pz;
  double  ptc_E;
  double  ptc_M;

  //TRootLHEFParticle *element;

  //cout<<"ID        status"<<endl;

  for(particle = 0; particle < hepeup.NUP; ++particle)
  {
    //element = (TRootLHEFParticle*) branch->NewEntry();

    //element->PID = hepeup.IDUP[particle];
    //element->Status = hepeup.ISTUP[particle];
    //element->Mother1 = hepeup.MOTHUP[particle].first;
    //element->Mother2 = hepeup.MOTHUP[particle].second;
    //element->ColorLine1 = hepeup.ICOLUP[particle].first;
    //element->ColorLine2 = hepeup.ICOLUP[particle].second;
    //element->Px = hepeup.PUP[particle][0];
    //element->Py = hepeup.PUP[particle][1];
    //element->Pz = hepeup.PUP[particle][2];
    //element->E = hepeup.PUP[particle][3];
    //element->M = hepeup.PUP[particle][4];
    ptc_PID = hepeup.IDUP[particle];
    ptc_Status = hepeup.ISTUP[particle];
    ptc_Mother1 = hepeup.MOTHUP[particle].first;
    ptc_Mother2 = hepeup.MOTHUP[particle].second;
    ptc_ColorLine1 = hepeup.ICOLUP[particle].first;
    ptc_ColorLine2 = hepeup.ICOLUP[particle].second;
    ptc_Px = hepeup.PUP[particle][0];
    ptc_Py = hepeup.PUP[particle][1];
    ptc_Pz = hepeup.PUP[particle][2];
    ptc_E = hepeup.PUP[particle][3];
    ptc_M = hepeup.PUP[particle][4];

    if(ptc_Status == 1)
    {
      if(fabs(ptc_PID) == GenType::kElectron)
      {
	el_is = true;
	el_TL.SetPxPyPzE(ptc_Px, ptc_Py, ptc_Pz, ptc_E);
	Lepton4_TL += el_TL;
	numOfLeptons++;
      }
      if(fabs(ptc_PID) == GenType::keNeutrino)
      {
	eNu_is = true;
	eNu_TL.SetPxPyPzE(ptc_Px, ptc_Py, ptc_Pz, ptc_E);
	Lepton4_TL += eNu_TL;
	numOfLeptons++;
      }
      if(fabs(ptc_PID) == GenType::kMuon)
      {
	mu_TL.SetPxPyPzE(ptc_Px, ptc_Py, ptc_Pz, ptc_E);
	Lepton4_TL += mu_TL;
	numOfLeptons++;
      }
      if(fabs(ptc_PID) == GenType::kmuNeutrino)
      {
	muNu_TL.SetPxPyPzE(ptc_Px, ptc_Py, ptc_Pz, ptc_E);
	Lepton4_TL += muNu_TL;
	numOfLeptons++;
      }
      if(fabs(ptc_PID) == GenType::kTau)
      {
	tau_TL.SetPxPyPzE(ptc_Px, ptc_Py, ptc_Pz, ptc_E);
	Lepton4_TL += tau_TL;
	numOfLeptons++;
      }
      if(fabs(ptc_PID) == GenType::ktauNeutrino)
      {
	tauNu_TL.SetPxPyPzE(ptc_Px, ptc_Py, ptc_Pz, ptc_E);
	Lepton4_TL += tauNu_TL;
	numOfLeptons++;
      }
    }

    //cout<<element->PID<<"	"<<element->Status<<endl;

    //momentum.SetPxPyPzE(element->Px, element->Py, element->Pz, element->E);

    //cosTheta = TMath::Abs(momentum.CosTheta());
    //signPz = (momentum.Pz() >= 0.0) ? 1.0 : -1.0;

    //element->PT = momentum.Perp();
    //element->Eta = (cosTheta == 1.0 ? signPz*999.9 : momentum.Eta());
    //element->Phi = (cosTheta == 1.0 ? signPz*999.9 : momentum.Rapidity());
    //element->Rapidity = (cosTheta == 1.0 ? signPz*999.9 : momentum.Rapidity());

    //element->LifeTime = hepeup.VTIMUP[particle];
    //element->Spin = hepeup.SPINUP[particle];
  }

  if(numOfLeptons != 4)
  {
    cout<<"Notice: Number of Leptons is "<<numOfLeptons<<"!!!!!!!!!!"<<endl;
  }
  //cout<<"mass of 4Leptons is "<<Lepton4_TL.M()<<endl;
  if( Lepton4_TL.M()                          <= 140 ){return 0;}
  if( Lepton4_TL.M() >  140 && Lepton4_TL.M() <= 300){return 1;}
  if( Lepton4_TL.M() >  300 ){return 2;}
  return -1;
}

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  char appName[] = "ExRootLHEFConverter";

  if(argc != 5)
  {
    cout << " Usage: " << appName << " input_file" << " outOnPeak_file" << " outShoulder_file" <<" outTail_file"<<endl;
    cout << " input_file - input file in LHEF format," << endl;
    cout << " outOnPeak_file - output file with m(H) <140 GeV." << endl;
    cout << " outShoulder_file - output file with 140<= m(H) <300 GeV." << endl;
    cout << " tail_file - output file with 300<= m(H) GeV." << endl;
    return 1;
  }

  gROOT->SetBatch();

  int appargc = 1;
  char *appargv[] = {appName};
  TApplication app(appName, &appargc, appargv);

  // Open a stream connected to an event file:
  ifstream inputFileStream(argv[1]);

  // Create the Reader object:
  LHEF::Reader *inputReader = new LHEF::Reader(inputFileStream);

  ofstream onPeakFile(argv[2]);
  ofstream shoulderFile(argv[3]);
  ofstream tailFile(argv[4]);
  LHEF::Writer *onPeakWriter   = new LHEF::Writer(onPeakFile);
  LHEF::Writer *shoulderWriter = new LHEF::Writer(shoulderFile);
  LHEF::Writer *tailWriter     = new LHEF::Writer(tailFile);
  onPeakWriter  ->heprup = inputReader->heprup;
  shoulderWriter->heprup = inputReader->heprup;
  tailWriter    ->heprup = inputReader->heprup;
  onPeakWriter  ->init();
  shoulderWriter->init();
  tailWriter    ->init();
  //TFile *outputFile = TFile::Open(argv[2], "RECREATE");
  //ExRootTreeWriter *treeWriter = new ExRootTreeWriter(outputFile, "LHEF");

  // generated event from LHEF
  //ExRootTreeBranch *branchEvent = treeWriter->NewBranch("Event", TRootLHEFEvent::Class());

  // generated partons from LHEF
 // ExRootTreeBranch *branchParticle = treeWriter->NewBranch("Particle", TRootLHEFParticle::Class());

  cout << "** Calculating number of events to process. Please wait..." << endl;
  Long64_t allEntries = inputReader->getNumberOfEvents();
  cout << "** Input file contains " << allEntries << " events" << endl;

  if(allEntries > 0)
  {
    ExRootProgressBar progressBar(allEntries);
    
    // Loop over all events
    Long64_t entry = 0;
    int area;
    while(inputReader->readEvent())
    {
      //treeWriter->Clear();

      AnalyseEvent(inputReader, entry + 1);
      //AnalyseEvent(inputReader, branchEvent, entry + 1);
      area = AnalyseParticles(inputReader );
      if( area == 0)if( entry % 10 == 0)
      {
        onPeakWriter->hepeup = inputReader->hepeup;
        onPeakWriter->writeEvent();
      }
      if( area == 1)//if( entry % 5 == 0)
      {
        shoulderWriter->hepeup = inputReader->hepeup;
        shoulderWriter->writeEvent();
      }
      if( area == 2 ){
        tailWriter->hepeup = inputReader->hepeup;
        tailWriter->writeEvent();
      }

      //AnalyseParticles(inputReader, branchParticle);


      //treeWriter->Fill();

      progressBar.Update(entry);

      ++entry;
    }

    progressBar.Finish();
  }

  //treeWriter->Write();

  cout << "** Exiting..." << endl;

  //delete treeWriter;
  //delete outputFile;
  delete inputReader;
  delete onPeakWriter;
  delete shoulderWriter;
  delete tailWriter;
  onPeakFile.close();
  shoulderFile.close();
  tailFile.close();
  inputFileStream.close();
}



