import os

cmd_string = "root -l -b -q njet_mjj_detajj_Scale.C+"
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
