#!/bin/tcsh -f
set dirName_Base = "/afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/GGVvAnalyzer/MakeRooT"

set dirName = "SigHw25RoScGeCut"
#set dirName = "$dirName_base/SigHw25RoScGeCut"
./chain_make.tcsh $dirName_Base $dirName

set dirName = "IntHw25RoScGeCut"
./chain_make.tcsh $dirName_Base $dirName

set dirName = "ContHw25RoScGeCut"
./chain_make.tcsh $dirName_Base $dirName
