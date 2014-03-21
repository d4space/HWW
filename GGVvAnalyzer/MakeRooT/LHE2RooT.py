import os
indir = '/afs/cern.ch/work/s/salee/private/HWWwidth/GG2VV/test/TestResults'
outDir = 'TestRst'
os.system('mkdir '+outDir)
for root, dirs, filenames in os.walk(indir):
  for f in filenames:
    print f
    cmd_str = "ExRootLHEFConverter " +indir+"/"+ f + " "+outDir+"/" +f+".root"
    print cmd_str
    os.system(cmd_str)

print "END hahahahahahaha"
