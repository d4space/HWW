import os
import sys

CutNames=['NoCut']
sampleName = ['WJetsToLNuMad','DYJetsToLL','ggToH125toWWTo2LAndTau2Nu']
VarName=['pupMet','pfMet','genMet','genMet_pupMet','genMet_pfMet']
for Cut in CutNames:
  for Var in VarName:
    for Sample in sampleName:
      cmd_string = "root -l -q metStudy.C+\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var,Sample)
      os.system(cmd_string)
      
      cmd_string = "rm -f *.d *.so"
      os.system(cmd_string)
