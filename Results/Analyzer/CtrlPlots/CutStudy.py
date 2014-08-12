import os
import sys

CutNames=['CommonCut']
VarNames=['mpmet']
DirName = "CutStudy"
#cmd_string = "mkdir " + DirName
#os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    cmd_string = "root -l -b -q CutStudy.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var, DirName)
    os.system(cmd_string)
    
    cmd_string = "rm -f *.d *.so"
    os.system(cmd_string)
