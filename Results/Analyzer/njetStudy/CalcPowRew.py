import os

#cmd_string = "root -l -b -q CalcPowRew2Phn.C+"
cmd_string = "root -l -b -q CalcPowRew2gg2vv.C+"
os.system(cmd_string)
cmd_string = "rm -f *.d *.so"
os.system(cmd_string)
