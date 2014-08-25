void chain_gg2vvHw1Sig8TeV( TChain *chains)
{
  chains->Add("root://eoscms.cern.ch//eos/cms/store/user/kbutanov/HWWwidth/LatinosTrees/gg2vv/latinogg2vv_Hw1_SigOnPeak_8TeV.root");
  chains->Add("root://eoscms.cern.ch//eos/cms/store/user/kbutanov/HWWwidth/LatinosTrees/gg2vv/latinogg2vv_Hw1_SigShoulder_8TeV.root");
  chains->Add("root://eoscms.cern.ch//eos/cms/store/user/kbutanov/HWWwidth/LatinosTrees/gg2vv/latinogg2vv_Hw1_SigTail_8TeV.root");
}
