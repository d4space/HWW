import os

cmd_string = "root -l -b -q Kfactor.C+"
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
