import os
import sys

#cmd_string = "root -l -q MakeHistoCtrPlots.C"
#os.system(cmd_string)
#
#cmd_string = "python MHiggs.py"
#os.system(cmd_string)

#CutNames=['Loose']
#CutNames=['Tight']
#CutNames=['LooseCut','CommonCut']
CutNames=['CommonCut']
#CutNames=['SignalCut']
#CutNames=['SignalCutV3']
#VarNames=['dphill']
#VarNames=['mll','mth']
#VarNames=['channel']
VarNames=['channel','mll','dphill','mth','charge1','charge2','trigger','nextra','zveto','flavor','njet','bveto_mu','bveto_ip','nbjettche','ptll','pt1','pt2','pfmet','mpmet','ppfmet','dymva1','dphilljetjet']
#VarNames=['mll','dphill','mth','ptll','pt1','pt2','pfmet']
#DirName = "Plts"
#DirName = "Plts_SignalCutV3"
DirName = "tmpCtrlPlts_ggH_AN_14_192"
cmd_string = "mkdir " + DirName
os.system(cmd_string)
for Cut in CutNames:
  for Var in VarNames:
    cmd_string = "root -l -b -q CtrPlots.C\(\\\"%s\\\",\\\"%s\\\",\\\"%s\\\"\)" %(Cut,Var, DirName)
    os.system(cmd_string)

    cmd_string = "rm -f *.d *.so"
    os.system(cmd_string)
