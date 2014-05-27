import os
import sys


#CutNames=['Loose']
#CutNames=['Tight']
CutNames=['Loose','Tight']
VarNames=['channel','mll','dphill','mth']
DirName = "Plts"
cmd_string = "mkdir " + DirName
os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    cmd_string = "root -l -q CtrPlots.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var, DirName)
    os.system(cmd_string)

    cmd_string = "rm -f *.d *.so"
    os.system(cmd_string)
