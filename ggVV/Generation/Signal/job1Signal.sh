#!/bin/bash
DirGg2VV="/afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/ggVV/Generation/gg2VV-3.1.5/gg2VV"
PATH=$PATH:$DirGg2VV
COMMAND="gg2VV_signal"
RND_TAIL=".rngseed"
RND_SEED="10"
GEN_FILE_TAIL="_unweightedEvents.dat"
RES_FILE_TAIL="_1_unweightedEvents.lhe"
DATA_DIRECTORY="/afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/ggVV/Generation/Signal/"
rm -f $COMMAND$RND_SEED$RND_TAIL
touch $COMMAND$RND_SEED$RND_TAIL
echo $RND_SEED >> $DATA_DIRECTOR$COMMAND$RND_SEED$RND_TAIL
#jam clean
#jam gg2VV
cd $DirGg2VV
cp gg2VV_signal $COMMAND$RND_SEED
cd -
$COMMAND$RND_SEED

cp $COMMAND$RND_SEED$GEN_FILE_TAIL $DATA_DIRECTORY$COMMAND$RND_SEED$RES_FILE_TAIL
