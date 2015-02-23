import os

cmd_string = "root -l -b -q ratiofit_vbf.C+"
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
