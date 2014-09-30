import os
import sys

CutNames=['CommonCut']
#VarNames=['mthmll','mthptll','mllptll','mll','mth']
vSigBkgInt=['SCI','SigInt','Int']
VarNames=['mthmll']
cmd_string = "mkdir OnOffShell"
os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    for Dir in vSigBkgInt:
      cmd_string = "root -l -b -q OnShOffSh.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var,Dir)
      os.system(cmd_string)
      
      cmd_string = "rm -f *.d *.so"
      os.system(cmd_string)
