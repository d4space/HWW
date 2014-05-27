{
  TChain *myChain = new TChain("latino");
  myChain->Add("/terranova_1/HWW/tree_skim_wwmin/nominals/latino_036_DY10toLLMad.root");
  myChain->MakeClass("HWwNT");
}
