import os
cmd_string = "root -l -q CtrPlots.C+"
#cmd_string = "root -l -q theoryComp.C+\(\\\"%s\\\"\)" %(BaseName)
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
