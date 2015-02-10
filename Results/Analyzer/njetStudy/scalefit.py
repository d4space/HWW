import os

cmd_string = "root -l -b -q scalefit.C+"
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
