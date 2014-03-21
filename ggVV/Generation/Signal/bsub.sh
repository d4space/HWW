#!/bin/sh
bsub -q 8nh -J job1SigGenCut <job1Sig_GenCut.sh
bsub -q 8nh -J job1IntGen <job1Int_GenCut.sh
bsub -q 8nh -J job1ContGen <job1Cont_GenCut.sh
