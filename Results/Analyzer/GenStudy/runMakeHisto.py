import os
import sys

#SAMPLES = ['ggWWto2L','WWTo2L2Nu']
SAMPLES = ['WWTo2L2Nu50ns']
#SAMPLES = ['ggWWto2L']

#rm -rf rootfiles/${SAMPLES}

# Loop
for SAMPLE in SAMPLES:
  cmd_string = "root -l -b -q MakeGenHistoScript.C\(\\\"%s\\\"\)" %(SAMPLE)
  os.system(cmd_string)
  
  cmd_string = "rm -f *.d *.so"
  os.system(cmd_string)
