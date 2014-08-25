import os
import sys

CutNames=['LooseCut','CommonCut']
#CutNames=['CommonCut']
VarNames=['mth']
DirName = "RecoPlts_mtH"
cmd_string = "mkdir " + DirName
os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    cmd_string = "root -l -b -q CtrPlots_mth.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var, DirName)
    os.system(cmd_string)

    cmd_string = "rm -f *.d *.so"
    os.system(cmd_string)
