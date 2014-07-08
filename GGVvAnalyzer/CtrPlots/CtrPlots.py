import os

cmd_string = "root -l -q MakeHisto.C"
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="Hw1Sig8TeV"
CutName="NoCut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

CutName="CommonCut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

CutName="N1Cut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="Hw1Int8TeV"
CutName="NoCut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

CutName="CommonCut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

CutName="N1Cut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

BaseName="Hw1Cot8TeV"
CutName="NoCut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

CutName="CommonCut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

CutName="N1Cut"
cmd_string = "root -l -q CtrPlots.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
