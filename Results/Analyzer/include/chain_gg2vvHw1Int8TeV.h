void chain_gg2vvHw1Int8TeV( TChain *chains)
{
  chains->Add("root://eoscms.cern.ch//eos/cms/store/user/kbutanov/HWWwidth/LatinosTrees/gg2vv/latinogg2vv_Hw1_IntOnPeak_8TeV.root");
  chains->Add("root://eoscms.cern.ch//eos/cms/store/user/kbutanov/HWWwidth/LatinosTrees/gg2vv/latinogg2vv_Hw1_IntShoulder_8TeV.root");
  chains->Add("root://eoscms.cern.ch//eos/cms/store/user/kbutanov/HWWwidth/LatinosTrees/gg2vv/latinogg2vv_Hw1_IntTail_8TeV.root");
}
