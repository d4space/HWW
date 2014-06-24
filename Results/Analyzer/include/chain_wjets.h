void chain_wjets( TChain *chains)
{
  chains->Add("/afs/cern.ch/user/m/maiko/work/public/Tree/tree_skim_wwmin/wjets/latino_RunA_892pbinv_LooseLoose.root");
  chains->Add("/afs/cern.ch/user/m/maiko/work/public/Tree/tree_skim_wwmin/wjets/latino_RunB_4404pbinv_LooseLoose.root");
  chains->Add("/afs/cern.ch/user/m/maiko/work/public/Tree/tree_skim_wwmin/wjets/latino_RunC_7032pbinv_LooseLoose.root");
  chains->Add("/afs/cern.ch/user/m/maiko/work/public/Tree/tree_skim_wwmin/wjets/latino_RunD_7274pbinv_LooseLoose.root");
  //chains->Add("/terranova_1/HWW/tree_skim_wwmin/wjets/latino_RunA_892pbinv_LooseLoose.root");
  //chains->Add("/terranova_1/HWW/tree_skim_wwmin/wjets/latino_RunB_4404pbinv_LooseLoose.root");
  //chains->Add("/terranova_1/HWW/tree_skim_wwmin/wjets/latino_RunC_7032pbinv_LooseLoose.root");
  //chains->Add("/terranova_1/HWW/tree_skim_wwmin/wjets/latino_RunD_7274pbinv_LooseLoose.root");
}
