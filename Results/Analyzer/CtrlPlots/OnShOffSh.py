import os
import sys

#cmd_string = "root -l -q MakeHistoCtrPlots.C"
#os.system(cmd_string)

CutNames=['OnShvsOffShCut']
#VarNames=['mthmll','mthptll','mllptll','mll','mth']
DirNames=['SBI','SigInt']
VarNames=['mll']
#VarNames=['mthmll']
#VarNames=['mth']
#DirNames=['SigInt']
#DirNames = ["SBI"]
cmd_string = "mkdir OnOffShell"
os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    for Dir in DirNames:
      cmd_string = "root -l -b -q OnShOffSh.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var,Dir)
      os.system(cmd_string)
      
      cmd_string = "rm -f *.d *.so"
      os.system(cmd_string)
