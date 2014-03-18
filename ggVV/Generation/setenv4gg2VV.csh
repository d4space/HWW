#!/bin/tcsh -f
setenv gg2VV_PATH /afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/ggVV/Generation
#setenv gg2VV_PATH /afs/cern.ch/work/a/asakharo/gg2VV
setenv TOPDIR $gg2VV_PATH/gg2VV/gg2VV-3.1.5
setenv LOOPTOOLS_TOPDIR $gg2VV_PATH/LoopTools-2.8
source /afs/cern.ch/sw/IntelSoftware/linux/all-setup.csh
setenv PATH ${PATH}:${gg2VV_PATH}/omniORB-4.1.6/bin
