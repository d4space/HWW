import os
Sample = 'IntHw25RoScMiCut'
print 'Processing data set of '+Sample +'##################'
#indir = '/afs/cern.ch/work/s/salee/private/HWWwidth/GG2VV/test/' + Sample
indir = '/terranova_1/GGRooT/LHE_Files/' + Sample
onPeakDir = Sample+"OnPeak"
soulderDir = Sample+"Soulder"
tailDir = Sample+"Tail"
print onPeakDir
print soulderDir
print tailDir
os.system('mkdir '+onPeakDir)
os.system('mkdir '+soulderDir)
os.system('mkdir '+tailDir)
for root, dirs, filenames in os.walk(indir):
  for f in filenames:
    print f
    cmd_str = "LHeSplitterInt " +indir+"/"+ f + " "+onPeakDir+"/" +f+" "+soulderDir+"/"+f+" "+tailDir+"/"+f
    print cmd_str
    os.system(cmd_str)

#cms_str = "LHeSplitter /terranova_1/GGRooT/LHE_Files/IntHw25RoScMiCut/gg2VV_IntHw25RoScMiCut52_unweightedEvents.lhe haha_OnPeak.lhe haha_OffPeak.lhe"
#cms_str = "LHeSplitter /terranova_1/GGRooT/LHE_Files/ContHw25RoScMiCut/gg2VV_ContHw25RoScMiCut63_unweightedEvents.lhe haha.root"
#cms_str = "LHeSplitter /terranova_1/GGRooT/LHE_Files/SigHw25RoScMiCut/gg2VV_SigHw25RoScMiCut101_unweightedEvents.lhe haha.root"
#os.system(cms_str)

print "END hahahahahahaha"
