#!/bin/tcsh -f
#set dirName_Base = "/terranova_0/HWWwidth/HWW/GGVvAnalyzer/MakeRooT"
set dirName_Base = "/terranova_1/HWWwidth/gg2vv"
#set dirName_Base = "/afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/GGVvAnalyzer/MakeRooT"

set dirName = "IntHw1RoScMiCut"
set fileName = "IntHw1gg2vv8TeV"
./chain_make.tcsh $dirName_Base $dirName $fileName
