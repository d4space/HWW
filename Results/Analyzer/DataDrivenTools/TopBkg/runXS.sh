#!/bin/bash



# void runXS(Int_t    njet          = 0,
# Int_t    ichannel      = All,
# Double_t luminosity    = 19365,
# TString  cutLevel      = "TopTagging",
# Bool_t   useNM1        = false,
# Int_t    printLevel    = NOTE,
# Bool_t   useDataDriven = true,  // false => DY and Top from MC
# Bool_t   drawTheXS     = true,
# Double_t yMin          = -999,
# Double_t yMax          = -999)

NJET=0
CHANNEL=All
root -b -q runXS.C\($NJET,$CHANNEL,19365,\"TopTagging\",false,NOTE,true,-999,-999\) | tee runXS.C_${NJET}jet_${CHANNEL}.log
NJET=1
#root -b -q runXS.C\($NJET,$CHANNEL,19365,\"TopTagging\",false,NOTE,true,-999,-999\) | tee runXS.C_${NJET}jet_${CHANNEL}.log
