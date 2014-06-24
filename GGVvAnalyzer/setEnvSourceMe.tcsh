#!/bin/tcsh -f
#setenv PATH "${PATH}:/afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/GGVvAnalyzer/ExRootAnalysis"
setenv PATH "${PATH}:/afs/cern.ch/work/k/kbutanov/private/HWWwidth/CMSSW_5_3_14_patch1/src/HWW/GGVvAnalyzer/ExRootAnalysis"
source /afs/cern.ch/sw/lcg/contrib/gcc/4.6.3/x86_64-slc5-gcc46-opt/setup.csh
cd /afs/cern.ch/sw/lcg/app/releases/ROOT/5.32.00/x86_64-slc5-gcc46-opt/root
source bin/thisroot.csh
cd -
