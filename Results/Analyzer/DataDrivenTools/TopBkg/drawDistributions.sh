#!/bin/bash


#void drawDistributions(Int_t    njet       = 1,
#		       TString  channel    = "All",
#		       Double_t luminosity = 19365,
#		       TString  format     = "png",
#		       Bool_t   drawRatio  = true,
#		       Bool_t   dataDriven = true,
#		       Bool_t   setLogy    = false)
#{

##CHANNEL=\"All\"
#CHANNEL=\"OF\"
#NJET=0
#root -l -b -q drawDistributions.C\($NJET,$CHANNEL,19365,\"pdf\",true,true,false\)
#root -l -q drawDistributions.C\($NJET,$CHANNEL,19365,\"png\",true,true,false\)

#NJET=1
#root -l -b -q drawDistributions.C\($NJET,$CHANNEL,19365,\"pdf\",true,true,false\)

# For the same sign 0, 1, 2 jet
CHANNEL=\"SS\"
NJET=10
root -l -b -q drawDistributions_SS.C\($NJET,$CHANNEL,19365,\"pdf\",true,true,false\)
