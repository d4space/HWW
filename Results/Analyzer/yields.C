

void yields(){

  TString LumiW = "*19.468" ;

  TString CutsName[4] ; 
  TString CutsCut [4] ; 

  CutsName [0] = "sf0j" ;  
  CutsCut  [0] = "( sameflav&&njet==0)" ;
  CutsName [1] = "of0j" ;
  CutsCut  [1] = "(!sameflav&&njet==0)" ;
  CutsName [2] = "sf1j" ;
  CutsCut  [2] = "( sameflav&&njet==1)" ;
  CutsName [3] = "of1j" ;
  CutsCut  [3] = "(!sameflav&&njet==1)" ;

  TString Dir = "/afs/cern.ch/user/m/maiko/work/public/Tree/tree_skim_wwmin/";

  // DATA

  TChain * Data = new TChain("Data");
  Data->Add(Dir+"/data/latino_RunA_892pbinv.root/latino") ;
  Data->Add(Dir+"/data/latino_RunB_4404pbinv.root/latino") ;
  Data->Add(Dir+"/data/latino_RunC_7032pbinv.root/latino") ;
  Data->Add(Dir+"/data/latino_RunD_7274pbinv.root/latino") ;

  cout << "DATA:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    Data->Draw("0.5 >> h",CutsCut[iCut]);
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete Data;

  // WJET

  TChain * WJet = new TChain("WJet");
  WJet->Add(Dir+"/wjets/latino_RunA_892pbinv_LooseLoose.root/latino") ;
  WJet->Add(Dir+"/wjets/latino_RunB_4404pbinv_LooseLoose.root/latino") ;
  WJet->Add(Dir+"/wjets/latino_RunC_7032pbinv_LooseLoose.root/latino") ;
  WJet->Add(Dir+"/wjets/latino_RunD_7274pbinv_LooseLoose.root/latino") ;

  cout << "WJet:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    WJet->Draw("0.5 >> h",CutsCut[iCut]+"*fakeW*(run!=201191)");
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete WJet;  

  // WW

  TChain * WW =  new TChain("WW");
  WW->Add(Dir+"/nominals/latino_000_WWJets2LMad.root/latino") ;
  WW->Add(Dir+"/nominals/latino_001_GluGluToWWTo4L.root/latino");  

  cout << "WW:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    WW->Draw("0.5 >> h",CutsCut[iCut]+"*puW*baseW*effW*triggW"+LumiW);
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete WW;

  // Top
 
  TChain * Top =  new TChain("Top");
  Top->Add(Dir+"/nominals/latino_019_TTTo2L2Nu2B.root/latino");
  Top->Add(Dir+"/nominals/latino_011_TtWFullDR.root/latino");
  Top->Add(Dir+"/nominals/latino_012_TbartWFullDR.root/latino");

  cout << "Top:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    Top->Draw("0.5 >> h",CutsCut[iCut]+"*puW*baseW*effW*triggW"+LumiW);
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete Top;

  // DYll

  TChain * DYll =  new TChain("DYll");
  DYll->Add(Dir+"/nominals/latino_036_DY10toLLMad.root/latino");
  DYll->Add(Dir+"/nominals/latino_037_DY50toLLMad.root/latino");

  cout << "DYll:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    DYll->Draw("0.5 >> h",CutsCut[iCut]+"*puW*baseW*effW*triggW*sameflav"+LumiW);
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete DYll;

  // DYtt

  TChain * DYtt =  new TChain("DYtt");
  DYtt->Add(Dir+"/nominals/latino_DYtt_19.5fb.root/latino");

  cout << "DYtt:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    DYtt->Draw("0.5 >> h",CutsCut[iCut]+"*puW*baseW*effW*triggW*(!sameflav)"+LumiW);
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete DYtt;

  // VV = WZ ZZ  WGsToElNuM WGsToMuNu WGsToTauNu WG WZ2L2Q ZZ2L2Q ZGToLLuG

  TChain * VV =  new TChain("VV");
  VV->Add(Dir+"/nominals/latino_082_WGstarToElNuMad.root/latino");
  VV->Add(Dir+"/nominals/latino_083_WGstarToMuNuMad.root/latino");
  VV->Add(Dir+"/nominals/latino_084_WGstarToTauNuMad.root/latino");
  VV->Add(Dir+"/nominals/latino_085_WgammaToLNuG.root/latino");
  VV->Add(Dir+"/nominals/latino_086_ZgammaToLLuG.root/latino");
  VV->Add(Dir+"/nominals/latino_074_WZJetsMad.root /latino");
  VV->Add(Dir+"/nominals/latino_078_WZTo2L2QMad.root/latino");
  VV->Add(Dir+"/nominals/latino_075_ZZJetsMad.root/latino");
  VV->Add(Dir+"/nominals/latino_079_ZZTo2L2QMad.root /latino");

  cout << "VV:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    VV->Draw("0.5 >> h",CutsCut[iCut]+"*puW*baseW*effW*triggW*(1+0.5*(dataset>=82&&dataset<=84))"+LumiW);
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete VV;

  // VVV = WWGJets WZZJets ZZZJets WWZJets WWWJets TTWJets TTZJets TTWWJets TTGJets

  TChain * VVV =  new TChain("VVV");
  VVV->Add(Dir+"/nominals/latino_088_WWGJets.root/latino");
  VVV->Add(Dir+"/nominals/latino_089_WZZJets.root/latino");
  VVV->Add(Dir+"/nominals/latino_090_ZZZJets.root/latino");
  VVV->Add(Dir+"/nominals/latino_091_WWZJets.root/latino");
  VVV->Add(Dir+"/nominals/latino_092_WWWJets.root/latino");
  VVV->Add(Dir+"/nominals/latino_093_TTWJets.root/latino");
  VVV->Add(Dir+"/nominals/latino_094_TTZJets.root/latino");
  VVV->Add(Dir+"/nominals/latino_095_TTWWJets.root/latino");
  VVV->Add(Dir+"/nominals/latino_096_TTGJets.root/latino");

  cout << "VVV:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    VVV->Draw("0.5 >> h",CutsCut[iCut]+"*puW*baseW*effW*triggW"+LumiW);
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete VVV;

  // H125 

  TChain * H125 =  new TChain("H125");
  H125->Add(Dir+"/nominals/latino_1125_ggToH125toWWTo2LAndTau2Nu.root/latino");
  H125->Add(Dir+"/nominals/latino_2125_vbfToH125toWWTo2LAndTau2Nu.root/latino");
  H125->Add(Dir+"/nominals/latino_3125_wzttH125ToWW.root/latino");

  cout << "H125:" << endl;
  for (int iCut = 0 ; iCut < 4 ; ++iCut) {
    TH1F* h = new TH1F("h","h",1,0,1);
    H125->Draw("0.5 >> h",CutsCut[iCut]+"*puW*baseW*effW*triggW"+LumiW);
    cout << CutsName[iCut] << " = " << h->Integral() << endl ;
    delete h;
  }

  delete H125;
}
