import os

# Specify "Sample and indir"

Sample = 'IntHw25RoScMiCutOnPeak'
#Sample = 'IntHw25RoScMiCutOffPeak'
#Sample = 'SigHw25RoScMiCutOnPeak'
#Sample = 'SigHw25RoScMiCutOffPeak'
#Sample = 'ContHw25RoScGeCut'
indir = '/terranova_0/HWWwidth/HWW/GGVvAnalyzer/LHeSplitter/' + Sample
#indir = '/afs/cern.ch/work/s/salee/private/HWWwidth/GG2VV/test/' + Sample

print 'Processing data set of '+Sample +'##################'
outDir = Sample
os.system('mkdir '+outDir)
for root, dirs, filenames in os.walk(indir):
  for f in filenames:
    print f
    cmd_str = "ExRootLHEFConverter " +indir+"/"+ f + " "+outDir+"/" +f+".root"
    print cmd_str
    os.system(cmd_str)

print "END hahahahahahaha"
