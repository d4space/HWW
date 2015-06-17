import os
import sys

CutNames=['CommonCut']
sampleName = ['DYJetsToLL']
#sampleName = ['ggToH125toWWTo2LAndTau2Nu','DYJetsToLL']
#sampleName = ['ggToH125toWWTo2LAndTau2Nu']
#sampleName = ['WJetsToLNuMad','DYJetsToLL','ggToH125toWWTo2LAndTau2Nu']
#VarName=['pupMet','pfMet','genMet','genMet_pupMet','genMet_pfMet']
for Cut in CutNames:
  #for Var in VarName:
    for Sample in sampleName:
      cmd_string = "root -l -q metStudy.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(Sample,Cut)
      os.system(cmd_string)
      
      cmd_string = "rm -f *.d *.so"
      os.system(cmd_string)
