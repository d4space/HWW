import os

BaseName="Hw1gg2vv8TeV"
CutName="NoCut"
cmd_string = "root -l -q CtrPlotsIntOnly.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

CutName="CommonCut"
cmd_string = "root -l -q CtrPlotsIntOnly.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)

#BaseName="Hw25gg2vv8TeV"
#CutName="NoCut"
#cmd_string = "root -l -q CtrPlotsIntOnly.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
#os.system(cmd_string)
#cmd_string = "rm -f *.d *.so"
#os.system(cmd_string)
#
#CutName="CommonCut"
#cmd_string = "root -l -q CtrPlotsIntOnly.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
#os.system(cmd_string)
#cmd_string = "rm -f *.d *.so"
#os.system(cmd_string)
