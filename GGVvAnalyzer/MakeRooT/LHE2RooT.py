import os
Sample = 'SigHw25RoScMiCut'
print 'Processing data set of '+Sample +'##################'
#Sample = 'ContHw25RoScGeCut'
indir = '/afs/cern.ch/work/s/salee/private/HWWwidth/GG2VV/test/' + Sample
outDir = Sample
os.system('mkdir '+outDir)
for root, dirs, filenames in os.walk(indir):
  for f in filenames:
    print f
    cmd_str = "ExRootLHEFConverter " +indir+"/"+ f + " "+outDir+"/" +f+".root"
    print cmd_str
    os.system(cmd_str)

print "END hahahahahahaha"
