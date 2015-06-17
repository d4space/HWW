{
  TChain *myChain = new TChain("latino");
  //myChain->Add("/terranova_1/HWW/tree_skim_wwmin/nominals/latino_036_DY10toLLMad.root");
  //myChain->MakeClass("HWwNT");
  //myChain->Add("/afs/cern.ch/user/j/jfernan2/public/forAndrea/latino_250_ggww1sm000140.root");
  myChain->Add("/terranova_1/HWWwidth/Phys14/DYPU30bx50/latino_stepB_latinosYieldSkim_MC_DYPU30bx50_wPUPPI.root");
  //myChain->Add("/terranova_1/HWWwidth/Phys14/gg2hPU40bx25/latino_stepB_latinosYieldSkim_MC_gg2hPU40bx25_wPUPPI.root");
  myChain->MakeClass("HWwNT");
}
