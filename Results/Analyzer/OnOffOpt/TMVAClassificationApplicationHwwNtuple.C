/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/


//
// Comments from Gena Kukartsev
//
// This is an example of using the Category classifier. It is extremely convenient
// but it also has some idiosyncrasies, keep an eye on:
//  - make sure you SetBranchAddress not only for MVA variables but all variables
//    in cuts and all spectator variables
//


#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TEventList.h"
#include "TStopwatch.h"

#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

#include "TMVA_Hww_Cuts.C"

using namespace TMVA;

void TMVAClassificationApplicationHwwNtuple( TString myMethodList = "" ) 
{
#ifdef __CINT__
   gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();
   // set verbosity
   //TMVA::Tools::Instance().Log().SetMinType(kINFO);

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["Cuts"]            = 1;
   Use["Category"]        = 0;

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod 
                      << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
               std::cout << it->first << " ";
            }
            std::cout << std::endl;
            return;
         }
	 cout<<regMethod<<" is on by user"<<endl;
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "Color:!Silent" );    
   reader->SetMsgType(kINFO);


   // CMS STATS:
   //
   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   Float_t mWW;
   Float_t pt1;
   Float_t pt2;
   Float_t pfmet;
   Float_t mpmet;
   Float_t dphill;
   Float_t mll;
   Float_t ptll;

   reader->AddVariable( "mll",              &mll );
   reader->AddVariable( "ptll",             &ptll );

   // CMS STATS:
   // *** VERY IMPORTANT! ***
   // TMVA notoriously has problems with integer and other non-float branches.
   // Better not to use them at all and convert them to Float_t. If you happen
   // to have integer branches that you need, as in this example, you should create
   // corresponding float spectator variables and assign them in the event loop.
   // 
   // Spectator variables declared in the training have to be added to the reader, too
   //
   // Note that the corresponding branches are integer, so we create floats too!
   reader->AddSpectator( "mWW",                &mWW );
   reader->AddSpectator( "pt1",                &pt1 );
   reader->AddSpectator( "pt2",                &pt2 );
   reader->AddSpectator( "pfmet",              &pfmet );
   reader->AddSpectator( "mpmet",              &mpmet );
   reader->AddSpectator( "dphill",             &dphill );
   reader->AddSpectator( "mll",                &mll );
   reader->AddSpectator( "ptll",               &ptll );

   // --- Book the MVA methods

   TString dir    = "weights_MllPtll/";
   TString prefix = "TMVAClassification";

   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile ); 
      }
   }

   
   // Book output histograms
   UInt_t nbin = 100;
   TH1F * histBdt(0);
   TH1F * histCat(0);

   if (Use["BDT"])           histBdt     = new TH1F( "MVA_BDT",           "MVA_BDT",           nbin, -0.8, 0.8 );
   if (Use["Category"])      histCat     = new TH1F( "MVA_Category",      "MVA_Category",      nbin, -2., 2. );


   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //   
   //TFile *input(0);


   // CMS STATS:
   // Specify files with data, for which you want to compute the classifier values
   //TString fname = "./data/pass7_OS_test1/TTbar_MuMu/all.root";   
   //TString fname = "./data/pass7_TRI_test1/TTbar_MuMu/all.root";   


   //if (!gSystem->AccessPathName( fname )) 
   //   input = TFile::Open( fname ); // check if file in local directory exists
   //
   //if (!input) {
   //   std::cout << "ERROR: could not open data file" << std::endl;
   //   exit(1);
   //}
   //std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;
   
   // --- Event loop

   // Prepare the event tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   //std::cout << "--- Select signal sample" << std::endl;
   //TTree* theTree = (TTree*)input->Get("MVA");
   TChain *theTree = new TChain("latino");
   theTree->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_SigOnPeak_8TeV.root");
   theTree->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_SigShoulder_8TeV.root");
   theTree->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_SigTail_8TeV.root");
   //Double_t DmWW, Dmll, Dptll;
   Float_t puW, baseW, effW, triggW;
   //Double_t puW, baseW, effW, triggW;
   //Float_t userVar1, userVar2;
   theTree->SetBranchAddress( "mll",            &mll );
   theTree->SetBranchAddress( "ptll",           &ptll );
   // spectators
   theTree->SetBranchAddress( "mWW",           &mWW );
   theTree->SetBranchAddress( "pt1",           &pt1 );
   theTree->SetBranchAddress( "pt2",           &pt2 );
   theTree->SetBranchAddress( "pfmet",         &pfmet );
   theTree->SetBranchAddress( "mpmet",         &mpmet );
   theTree->SetBranchAddress( "dphill",        &dphill );
   theTree->SetBranchAddress( "mll",           &mll );
   theTree->SetBranchAddress( "ptll",          &ptll );
   // Others
   theTree->SetBranchAddress( "puW",            &puW );
   theTree->SetBranchAddress( "baseW",          &baseW );
   theTree->SetBranchAddress( "effW",           &effW );
   theTree->SetBranchAddress( "triggW",         &triggW );

   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests

   // CMS STATS:
   //       
   //       A little trick: loop over only selected events

   // make event list

   theTree->Draw(">>EvtList", ChannelCommonCut);
   TEventList * pEvtList = (TEventList *)gROOT->FindObject("EvtList");
   long int nEvents = pEvtList->GetN();

   //std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   std::cout << "--- Processing: " << nEvents << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   //for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++)
   double Nsignal(0);
   double Nbkg(0);
   double weight;

   double Nsel_Sig(0);
   double Nsel_Bkg(0);

   Bool_t passed;
   double effS(0.7);

   if (Use["Cuts"]) {
      // test: retrieve cuts for particular signal efficiency
      // CINT ignores dynamic_casts so we have to use a cuts-secific Reader function to acces the pointer  
      TMVA::MethodCuts* mcuts = reader->FindCutsMVA( "Cuts method" ) ;
      //TMVA::MethodCuts* mcuts = reader->FindCutsMVA( "CutsGA method" ) ;

      if (mcuts) {      
         std::vector<Double_t> cutsMin;
         std::vector<Double_t> cutsMax;
         mcuts->GetCuts( 0.7, cutsMin, cutsMax );
         std::cout << "--- -------------------------------------------------------------" << std::endl;
         std::cout << "--- Retrieve cut values for signal efficiency of 0.7 from Reader" << std::endl;
         for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) {
            std::cout << "... Cut: " 
                      << cutsMin[ivar] 
                      << " < \"" 
                      << mcuts->GetInputVar(ivar)
                      << "\" <= " 
                      << cutsMax[ivar] << std::endl;
         }
         std::cout << "--- -------------------------------------------------------------" << std::endl;
      }
   }
#if 1==1
   for (Long64_t ievt=0; ievt<nEvents; ++ievt) {
      if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      //theTree->GetEntry(ievt);
      //cout<<"ntry number: "<<pEvtList->GetEntry(ievt)<<endl;
      theTree->GetEntry(pEvtList->GetEntry(ievt));
      //mll  = Dmll;
      //ptll = Dptll;

      //cout<<"puW: "<<puW<<" baseW: "<<baseW<<" effW: "<<effW<<" triggW: "<<triggW<<endl;
      weight = 2.5*puW*baseW*effW*triggW*19.468;
      //cout<<"weight: "<<weight<<endl;
      if(mWW >= 160) Nsignal+=weight;
      if(mWW <  160) Nbkg+=weight;
      
      if(Use["Cuts"])
      {
        //passed = reader->EvaluateMVA( "Cuts method", effS );
        //if (passed)if(mWW >= 160) Nsel_Sig++;
        //if (passed)if(mWW <  160) Nsel_Bkg++;
        if (mll > 84.04 && ptll > 29.9)if(mWW >= 160) Nsel_Sig+=weight;
        if (mll > 84.04 && ptll > 29.9)if(mWW <  160) Nsel_Bkg+=weight;
	
      }
      // CMS STATS:
      // *** HERE we assign integer branches' values to float spectator variables
      //     Otherwise our category cuts would fail
      //
      //nBTagFloat=(Float_t)nBTag;

      // --- Return the MVA outputs and fill into histograms

      if (Use["BDT"          ])   histBdt    ->Fill( reader->EvaluateMVA( "BDT method"           ) );
      if (Use["Category"     ])   histCat    ->Fill( reader->EvaluateMVA( "Category method"      ) );

   }
#endif

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   cout<<"Nsignal: "<<Nsignal<<" Selected:"<<Nsel_Sig<<" eff: "<<Nsel_Sig/Nsignal<<endl;
   cout<<"Nbak: "<<Nbkg<<" Selected:"<<Nsel_Bkg<<" eff: "<<Nsel_Bkg/Nbkg<<endl;

   // --- Write histograms

   TFile *target  = new TFile( "TMVApp.root","RECREATE" );
   if (Use["BDT"          ])   histBdt    ->Write();
   if (Use["Category"     ])   histCat    ->Write();

   target->Close();

   std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVAClassificationApplication is done!" << endl << std::endl;

} 
