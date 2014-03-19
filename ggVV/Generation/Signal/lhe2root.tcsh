#!/bin/tcsh
setenv PATH "${PATH}:/afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/ggVV/Analysis/ExRootAnalysis"
ExRootLHEFConverter gg2VV_SIGNAL_1_unweightedEvents.lhe RootFormat/gg2VV_SIGNAL_1_unweightedEvents.root
