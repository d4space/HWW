void chain_gg2vvHw25Sig8TeV( TChain *chains)
{
  chains->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw25_SigOnPeak_8TeV.root");
  chains->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw25_SigShoulder_8TeV.root");
  chains->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/cmshww/amassiro/HiggsWidth/gg2vv/latinogg2vv_Hw25_SigTail_8TeV.root");
}
