// @(#)root/tmva $Id$
/**********************************************************************************
 * Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Root Macro: TMVAClassification                                                 *
 *                                                                                *
 * This macro provides examples for the training and testing of the               *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *                                                                                *
 *    root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)                     *
 *                                                                                *
 * (note that the backslashes are mandatory)                                      *
 * If no method given, a default set of classifiers is used.                      *
 *                                                                                *
 * The output file "TMVA.root" can be analysed with the use of dedicated          *
 * macros (simply say: root -l <macro.C>), which can be conveniently              *
 * invoked through a GUI that will appear at the end of the run of this macro.    *
 * Launch the GUI via the command:                                                *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 *                                                                                *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/MethodCategory.h"

#include "TMVA_Hww_Cuts.C"

#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

void TMVAClassificationHwwNtuple( TString myMethodList = "" )
{
   // This loads the library
   TMVA::Tools::Instance();

    gROOT->ProcessLine(".L TMVAGui.C");


   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Cut optimisation
   Use["Cuts"]            = 1;
   Use["CutsD"]           = 0;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   // 
   Use["BDT"]             = 0; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting 
   // 
   // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 0;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;
   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
	 cout<<regMethod<<" is on"<<endl;
      }
   }
   // -------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // For one variable
   //TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
   //                                            "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification" );
   // For Multiple Variables
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   //factory->AddVariable( "pt1",                "LeadLepton pt", "", 'F' );
   //factory->AddVariable( "pt2",                "TailLepton pt", "", 'F' );
   factory->AddVariable( "pfmet",                "MissingEt", "", 'F' );
   factory->AddVariable( "mpmet",              "Minimum Proj. Met", "", 'F' );
   factory->AddVariable( "dphill",             "DeltPhiOfLepLep", "", 'F' );
   //factory->AddVariable( "mll",                "DiLepton Mass", "", 'F' );
   factory->AddVariable( "ptll",               "DiLepton pt", "", 'F' );
   //
   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables
   //factory->AddSpectator( "spec1 := var1*2",  "Spectator 1", "units", 'F' );
   //factory->AddSpectator( "spec2 := var1*3",  "Spectator 2", "units", 'F' );
   //
   //factory->AddSpectator( "mWW",                "Higgs Mass", "", 'F' );
   factory->AddSpectator( "pt1",                "LeadLepton pt", "", 'F' );
   factory->AddSpectator( "pt2",                "TailLepton pt", "", 'F' );
   factory->AddSpectator( "pfmet",                "MissingEt", "", 'F' );
   factory->AddSpectator( "mpmet",              "Minimum Proj. Met", "", 'F' );
   factory->AddSpectator( "dphill",             "DeltPhiOfLepLep", "", 'F' );
   factory->AddSpectator( "mll",                "DiLepton Mass", "", 'F' );
   factory->AddSpectator( "ptll",               "DiLepton pt", "", 'F' );
   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   //TString fname = "./tmva_class_example.root";
   //TString fname = "/afs/cern.ch/work/s/salee/private/HWWwidth/HWW/GGVvAnalyzer/MkNtuple/Hw1Int8TeV/MkNtuple.root";
   //TString fname = "/terranova_0/HWWwidth/HWW/GGVvAnalyzer/MkNtuple/Hw1Int8TeV/MkNtuple.root";
   
   //if (gSystem->AccessPathName( fname ))  // file does not exist in local directory
    // exit(-1);
      //gSystem->Exec("wget http://root.cern.ch/files/tmva_class_example.root");
   
   //TFile *input = TFile::Open( fname );
   //TFile *SB_OnPeak = TFile::Open("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_IntOnPeak_8TeV.root");
   //TTree *SB_OnPeak_Tree = (TTree*)SB_OnPeak->Get("latino");
   
   TChain *S_Chain = new TChain("latino");
   TChain *C_Chain = new TChain("latino");
   TChain *SCI_Chain = new TChain("latino");
   TChain *qqWW_Chain = new TChain("latino");

   S_Chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_SigOnPeak_8TeV.root");
   S_Chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_SigShoulder_8TeV.root");
   S_Chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_SigTail_8TeV.root");
   SCI_Chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_IntOnPeak_8TeV.root");
   SCI_Chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_IntShoulder_8TeV.root");
   SCI_Chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw1_IntTail_8TeV.root");
   C_Chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw25_CotHead_8TeV.root");
   C_Chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw25_CotTail_8TeV.root");

   qqWW_Chain->Add("/afs/cern.ch/user/m/maiko/work/public/Tree/tree_skim_wwmin/nominals/latino_000_WWJets2LMad.root");
   
   // --- Register the training and test trees

   // You can add an arbitrary number of signal or background trees
   factory->AddSignalTree    ( S_Chain  );
   factory->AddBackgroundTree( qqWW_Chain );
   factory->AddBackgroundTree( C_Chain );
   // Classification training and test data in ROOT tree format with signal and background events being located in the same tree
   //factory->SetInputTrees(SCI_Chain, GenOffCut, GenOnCut);
   
   // To give different trees for training and testing, do as follows:
   //    factory->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
   //    factory->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );
   
   factory->SetWeightExpression          ("2.1*puW*baseW*effW*triggW*19.468");
   //factory->SetSignalWeightExpression    ("2.1*puW*baseW*effW*triggW*19.468");
   //factory->SetBackgroundWeightExpression("puW*baseW*effW*triggW*19.468");

   //factory->PrepareTrainingAndTestTree( ChanCommOff,
   //                                     "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=None:!V" );
                                        //"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V";
   factory->PrepareTrainingAndTestTree( ChanCommOff,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=None:!V" );
   // ---- Book MVA methods
   //
   // Cut optimisation
   if (Use["Cuts"])
      factory->BookMethod( TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDT",
                           "!H:V:NTrees=850:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
                           //"!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   // For an example of the category classifier usage, see: TMVAClassificationCategory

   // -----------------------------------------------------------------------------------------

   // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

   // ---- STILL EXPERIMENTAL and only implemented for BDT's ! 
   // factory->OptimizeAllMethods("SigEffAt001","Scan");
   // factory->OptimizeAllMethods("ROCIntegral","FitGA");

   // -----------------------------------------------------------------------------------------

   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;

   // Launch the GUI for the root macros
   //if (!gROOT->IsBatch()) TMVAGui( outfileName );
}
