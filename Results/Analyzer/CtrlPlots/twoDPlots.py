import os
import sys

CutNames=['SignalCutV1','SignalCutV2']
VarNames=['mthmll','mthdphill','mlldphill']
DirName = "2DPlts"
cmd_string = "mkdir " + DirName
os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    cmd_string = "root -l -b -q twoDPlots.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var, DirName)
    os.system(cmd_string)

    cmd_string = "rm -f *.d *.so"
    os.system(cmd_string)
