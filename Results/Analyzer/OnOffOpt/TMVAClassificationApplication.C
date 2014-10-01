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

using namespace TMVA;

void TMVAClassificationApplication( TString myMethodList = "" ) 
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
   Use["Category"]        = 1;

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
   Float_t met;
   Float_t HT;
   Float_t minMLB;
   Float_t leptonJetsMETSum;
   reader->AddVariable( "met",              &met );
   reader->AddVariable( "HT",               &HT );
   reader->AddVariable( "minMLB",           &minMLB );
   reader->AddVariable( "leptonJetsMETSum", &leptonJetsMETSum );



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
   Int_t nBTag;
   Int_t nJets;
   Int_t nLeptons;
   Int_t isMuon1;
   Int_t isMuon2;
   Int_t isMuon3;
   Int_t isMuon4;
   Float_t nBTagFloat;
   Float_t nJetsFloat;
   Float_t nLeptonsFloat;
   Float_t isMuon1Float;
   Float_t isMuon2Float;
   Float_t isMuon3Float;
   Float_t isMuon4Float;
   Float_t leptonSumMass;
   reader->AddSpectator( "nBTag", &nBTagFloat );
   reader->AddSpectator( "nJets", &nJetsFloat );
   reader->AddSpectator( "nLeptons", &nLeptonsFloat );
   reader->AddSpectator( "isMuon1", &isMuon1Float );
   reader->AddSpectator( "isMuon2", &isMuon2Float );
   reader->AddSpectator( "isMuon3", &isMuon3Float );
   reader->AddSpectator( "isMuon4", &isMuon4Float );
   reader->AddSpectator( "leptonSumMass", &leptonSumMass );



   // CMS STATS:
   // cut definitions. Define categories and overall selection.
#include "TMVA_tprime_cuts.C"



   // Add artificial spectators for distinguishing categories
   Float_t Category_mycat1, Category_mycat2, Category_mycat3, Category_mycat4;
   TString sCat1("Category_cat1:=");
   TString sCat2("Category_cat2:=");
   TString sCat3("Category_cat3:=");
   TString sCat4("Category_cat4:=");
   sCat1.Append(cut_os_cat1);
   sCat2.Append(cut_os_cat2);
   sCat3.Append(cut_ss);
   sCat4.Append(cut_tri);
   reader->AddSpectator( sCat1, &Category_mycat1 );
   reader->AddSpectator( sCat2, &Category_mycat2 );
   reader->AddSpectator( sCat3, &Category_mycat3 );
   reader->AddSpectator( sCat4, &Category_mycat4 );


   // --- Book the MVA methods

   TString dir    = "weights/";
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
   TFile *input(0);


   // CMS STATS:
   // Specify files with data, for which you want to compute the classifier values
   TString fname = "./data/pass7_OS_test1/TTbar_MuMu/all.root";   
   //TString fname = "./data/pass7_TRI_test1/TTbar_MuMu/all.root";   


   if (!gSystem->AccessPathName( fname )) 
      input = TFile::Open( fname ); // check if file in local directory exists
   
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;
   
   // --- Event loop

   // Prepare the event tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   std::cout << "--- Select signal sample" << std::endl;
   TTree* theTree = (TTree*)input->Get("MVA");
   //Float_t userVar1, userVar2;
   theTree->SetBranchAddress( "met",              &met );
   theTree->SetBranchAddress( "HT",               &HT );
   theTree->SetBranchAddress( "minMLB",           &minMLB );
   theTree->SetBranchAddress( "leptonJetsMETSum", &leptonJetsMETSum );


   // spectators
   theTree->SetBranchAddress( "leptonSumMass", &leptonSumMass );
   theTree->SetBranchAddress( "nJets", &nJets );
   theTree->SetBranchAddress( "nBTag", &nBTag );
   theTree->SetBranchAddress( "nLeptons", &nLeptons );
   theTree->SetBranchAddress( "isMuon1", &isMuon1 );
   theTree->SetBranchAddress( "isMuon2", &isMuon2 );
   theTree->SetBranchAddress( "isMuon3", &isMuon3 );
   theTree->SetBranchAddress( "isMuon4", &isMuon4 );


   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests


   // CMS STATS:
   //       
   //       A little trick: loop over only selected events

   // make event list
   theTree->Draw(">>EvtList", mycut);
   TEventList * pEvtList = (TEventList *)gROOT->FindObject("EvtList");
   long int nEvents = pEvtList->GetN();

   //std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   std::cout << "--- Processing: " << nEvents << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   //for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
   for (Long64_t ievt=0; ievt<nEvents; ++ievt) {

      if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      //theTree->GetEntry(ievt);
      theTree->GetEntry(pEvtList->GetEntry(ievt));


      // CMS STATS:
      // *** HERE we assign integer branches' values to float spectator variables
      //     Otherwise our category cuts would fail
      //
      nBTagFloat=(Float_t)nBTag;
      nJetsFloat=(Float_t)nJets;
      nLeptonsFloat=(Float_t)nLeptons;
      isMuon1Float  = (Float_t)isMuon1;
      isMuon2Float  = (Float_t)isMuon2;
      isMuon3Float  = (Float_t)isMuon3;
      isMuon4Float  = (Float_t)isMuon4;



      // --- Return the MVA outputs and fill into histograms

      if (Use["BDT"          ])   histBdt    ->Fill( reader->EvaluateMVA( "BDT method"           ) );
      if (Use["Category"     ])   histCat    ->Fill( reader->EvaluateMVA( "Category method"      ) );

   }

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();


   // --- Write histograms

   TFile *target  = new TFile( "TMVApp.root","RECREATE" );
   if (Use["BDT"          ])   histBdt    ->Write();
   if (Use["Category"     ])   histCat    ->Write();

   target->Close();

   std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVAClassificationApplication is done!" << endl << std::endl;
} 
