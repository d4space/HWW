#!/bin/tcsh -f
set dirName_Base = "/terranova_1/GGRooT"
#set dirName_Base = "/terranova_0/HWWwidth/HWW/GGVvAnalyzer/MakeRooT"
#set dirName_Base = "/afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/GGVvAnalyzer/MakeRooT"

set dirName = "SigHw25RoScMiCut"
#set dirName = "$dirName_base/SigHw25RoScGeCut"
./chain_make.tcsh $dirName_Base $dirName

set dirName = "IntHw25RoScMiCut"
./chain_make.tcsh $dirName_Base $dirName

set dirName = "ContHw25RoScMiCut"
./chain_make.tcsh $dirName_Base $dirName
