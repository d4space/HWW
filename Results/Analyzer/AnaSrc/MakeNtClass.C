{
  TChain *myChain = new TChain("latino");
  //myChain->Add("/terranova_1/HWW/tree_skim_wwmin/nominals/latino_036_DY10toLLMad.root");
  //myChain->MakeClass("HWwNT");
  //myChain->Add("/afs/cern.ch/user/j/jfernan2/public/forAndrea/latino_250_ggww1sm000140.root");
  myChain->Add("latino_160_qqww1smEM_baseW.root");
  //myChain->Add("latino_2130_vbfToH130toWWTo2LAndTau2Nu.root");
  //myChain->Add("/afs/cern.ch/user/m/maiko/work/public/Tree/tree_skim_wwmin/nominals/latino_2125_vbfToH125toWWTo2LAndTau2Nu.root");
  myChain->MakeClass("HWwNT");
}
