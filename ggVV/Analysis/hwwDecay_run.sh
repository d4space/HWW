root -b <<EOF
{
  gSystem->Load("lib/libExRootAnalysis.so");
  gROOT->ProcessLine(".L hwwDecay.C++");
  hwwDecay ana;
  ana.Loop();
}