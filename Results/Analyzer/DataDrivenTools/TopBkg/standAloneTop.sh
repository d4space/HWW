#!/bin/bash


NJET=0
root -b -q ./standAloneTop.C++\($NJET,true,2\) | tee standAloneTop${NJET}jet.log
NJET=1
#root -b -q ./standAloneTop.C++\($NJET,true,2\) | tee standAloneTop${NJET}jet.log



