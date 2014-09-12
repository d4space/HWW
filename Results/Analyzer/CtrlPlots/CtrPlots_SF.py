import os

BaseName="SF_Hw1g2vvInt8TeV"
CutName="NoCut"
cmd_string = "root -l -b -q CtrPlots_SF.C+\(\\\"%s\\\",\\\"%s\\\"\)" %(BaseName,CutName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
