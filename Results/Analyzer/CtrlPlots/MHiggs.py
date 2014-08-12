import os
import sys

CutNames=['Loose','CommonCut']
#CutNames=['CommonCut']
VarNames=['MHiggs','OnShell','OffShell']
#VarNames=['MHiggs']
DirName = "MHiggs"
cmd_string = "mkdir " + DirName
os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    cmd_string = "root -l -b -q MHiggs.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var, DirName)
    os.system(cmd_string)

    cmd_string = "rm -f *.d *.so"
    os.system(cmd_string)
