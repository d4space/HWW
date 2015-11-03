#!/bin/bash


#void drawDistributions(Int_t    njet       = 1,
#		       TString  channel    = "All",
#		       Double_t luminosity = 19365,
#		       TString  format     = "png",
#		       Bool_t   drawRatio  = true,
#		       Bool_t   dataDriven = true,
#		       Bool_t   setLogy    = false)
#{

#NJET=0
NJET=1
#CHANNEL=\"All\"
CHANNEL=\"OF\"
root -b -q drawDistributions_Subtraction.C\($NJET,$CHANNEL,19365,\"pdf\",true,true,false\)
#root -b -q drawDistributions.C\($NJET,$CHANNEL,19365,\"png\",true,true,false\)
