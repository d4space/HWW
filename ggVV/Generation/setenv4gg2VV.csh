#!/bin/tcsh -f
setenv gg2VV_PATH /afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/ggVV/Generation
#setenv gg2VV_PATH /afs/cern.ch/work/a/asakharo/gg2VV
setenv TOPDIR $gg2VV_PATH/gg2VV-3.1.5
setenv LOOPTOOLS_TOPDIR $gg2VV_PATH/LoopTools-2.8
#setenv LHAPATH /afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/ggVV/Generation/lhapdf-5.9.1/lhapdf-5.9.1-out/share/lhapdf
source /afs/cern.ch/sw/IntelSoftware/linux/all-setup.csh
setenv PATH ${PATH}:${gg2VV_PATH}/omniORB-4.1.6/bin
