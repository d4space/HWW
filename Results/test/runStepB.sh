#!/bin/bash

##miniAOD samples at lxplus
##------------------------------------------------
#gg2hPU40bx25=file:/afs/cern.ch/user/s/salee/WorkSpace/DataSample/Phys14DR/GluGluToHToWWTo2LAndTau2Nu_M-125_13TeV-powheg-pythia6/Phys14DR-PU40bx25_PHYS14_25_V1-v1/MINIAODSIM/F42379EA-1880-E411-8CDC-00266CFFA768.root

#gg2hPU20bx25=file:/afs/cern.ch/user/s/salee/WorkSpace/DataSample/Phys14DR/GluGluToHToWWTo2LAndTau2Nu_M-125_13TeV-powheg-pythia6/MINIAODSIM/PU20bx25_tsg_PHYS14_25_V1-v1/08CFEF83-586C-E411-8D7C-002590A2CCF2.root

#DYJetsToLLPU30bx50=file:/afs/cern.ch/user/s/salee/WorkSpace/DataSample/Phys14DR/DYJetsToLL_M-50_13TeV-madgraph-pythia8-tauola_v2/Phys14DR-AVE30BX50_tsg_PHYS14_ST_V1-v1/MINIAODSIM/0080FDC4-5A8B-E411-AA4A-00259073E4F0.root

#WJet2LNPU4bx50=file:/afs/cern.ch/user/s/salee/WorkSpace/DataSample/Phys14DR/WJetsToLNu_13TeV-madgraph-pythia8-tauola/Phys14DR-PU4bx50_PHYS14_25_V1-v1/MINIAODSIM/001E43FE-4470-E411-8DC5-0025905A60CE.root
##------------------------------------------------


#miniAOD samples at T2 KNU
#------------------------------------------------
gg2hPU40bx25=file:/d3/scratch/khakim/RunII/miniAODsamples/Phys14DR/1125_ggToH125toWWTo2LAndTau2Nu_PU40bx25/F42379EA-1880-E411-8CDC-00266CFFA768.root

gg2hPU20bx25=file:/d3/scratch/khakim/RunII/miniAODsamples/Phys14DR/3125_ggToH125toWWTo2LAndTau2Nu_PU20bx25/08CFEF83-586C-E411-8D7C-002590A2CCF2.root

gg2hPU30bx50=file:/d3/scratch/khakim/RunII/miniAODsamples/Phys14DR/4125_ggToH125toWWTo2LAndTau2Nu_AVE30bx50/440AA9AF-9988-E411-9786-00266CFFA038.root

DYJetsToLLPU30bx50=file:/d3/scratch/khakim/RunII/miniAODsamples/Phys14DR/037_DY50toLLMad50ns_AVE30bx50/0080FDC4-5A8B-E411-AA4A-00259073E4F0.root

DYJetsToLLPU4bx50=file:/d3/scratch/khakim/RunII/miniAODsamples/Phys14DR/038_DY50toLLMad50ns_PU4bx50/080957A7-C36E-E411-A5BC-00266CF327C4.root

DYJetsToLLPU20bx25=file:/d3/scratch/khakim/RunII/miniAODsamples/Phys14DR/039_DY50toLLMad25ns_PU20bx25/0432E62A-7A6C-E411-87BB-002590DB92A8.root

WJet2LNPU4bx50=file:/d3/scratch/khakim/RunII/miniAODsamples/Phys14DR/080_WJetsToLNuMad50ns_PU4bx50/001E43FE-4470-E411-8DC5-0025905A60CE.root

WJet2LNPU20bx25=file:/d3/scratch/khakim/RunII/miniAODsamples/Phys14DR/081_WJetsToLNuMad25ns_PU20bx25/02215B44-2D70-E411-90A3-0025905A60B8.root
#------------------------------------------------


MyInput=$gg2hPU40bx25
MyOutName="gg2hPU40bx25"
echo "The sample is: "$MyInput


#cmsRun stepB.py inputFiles=$DYJetsToLLPU30bx50 label=WW id=12345 scale=1 outputFile=stepB_latinosYieldSkim_MC_DY_wPUPPI.root doNoFilter=True doMuonIsoId=True runPUPPISequence=True
#cmsRun stepB.py inputFiles=$DYJetsToLLPU30bx50 label=WW id=12345 scale=1 outputFile=stepB_latinosYieldSkim_MC_DY_wPUPPI.root doNoFilter=True doMuonIsoId=True maxEvents=200 runPUPPISequence=True doGen=True

cmsRun stepB.py inputFiles=$MyInput label=WW id=12345 scale=1 outputFile=stepB_latinosYieldSkim_MC_"$MyOutName"_wPUPPI.root doNoFilter=True doMuonIsoId=True maxEvents=200 runPUPPISequence=True doGen=True

#python cmssw2latino.py stepB_latinosYieldSkim_MC_DY_wPUPPI_numEvent.root
