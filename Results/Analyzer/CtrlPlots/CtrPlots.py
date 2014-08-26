import os
import sys

#cmd_string = "root -l -q MakeHistoCtrPlots.C"
#os.system(cmd_string)

#CutNames=['Loose']
#CutNames=['Tight']
CutNames=['LooseCut','CommonCut']
#CutNames=['CommonCut']
#VarNames=['channel','mll','dphill','mth']
#VarNames=['channel']
VarNames=['channel','mll','dphill','mth','charge1','charge2','trigger','nextra','zveto','flavor','njet','bveto_mu','bveto_ip','nbjettche','ptll','pt1','pt2','pfmet','mpmet','ppfmet','dymva1','dphilljetjet']
DirName = "Plts"
#DirName = "Plts_mllCut_70"
cmd_string = "mkdir " + DirName
os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    cmd_string = "root -l -b -q CtrPlots.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var, DirName)
    os.system(cmd_string)

    cmd_string = "rm -f *.d *.so"
    os.system(cmd_string)
