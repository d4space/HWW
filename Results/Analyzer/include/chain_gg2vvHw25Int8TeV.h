void chain_gg2vvHw25Int8TeV( TChain *chains)
{
  chains->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw25_IntOnPeak_8TeV.root");
  chains->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw25_IntShoulder_8TeV.root");
  chains->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw25_IntTail_8TeV.root");
}
