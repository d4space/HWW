import os
#outF =open('index.html','w+')
#outF =open('MHiggs.html','w+')
outF =open('recoCutStudy.html','w+')
#outF =open('nTupleCtrPlots_mllCut70.html','w+')
#outF =open('index_OF_CommonCut.html','w+')
#outF =open('index_OF_LooseCut.html','w+')
print >>outF,'<html>'
print >>outF,'<head>'
#print >>outF,'<title>HWW Width CtrPlts: CommonCut + mll>70</title>'
#print >>outF,'<title>Higgs mass</title>'
print >>outF,'<title>Reconstruction level Cut optimization</title>'
print >>outF,'<style type="text/css">'
print >>outF,'div.pic {'
print >>outF,'    display: block;'
print >>outF,'    float: left;'
print >>outF,'    border: 1px solid gray;'
print >>outF,'    margin: 3px;'
print >>outF,'}'
print >>outF,'</style>'
print >>outF,'</head>'
print >>outF,'<body>'
#print >>outF,'<h1>/afs/cern.ch/user/k/kbutanov/www/HWwCtrPlots</h1>'
#print >>outF,'<h2><a name="HWW width Ctl Plts: CommonCut + mll>70">Plots</a></h2>'
#print >>outF,'<h1>/afs/cern.ch/user/k/kbutanov/www/MHiggs</h1>'
print >>outF,'<h1>/afs/cern.ch/user/k/kbutanov/www/CutStudy</h1>'
#print >>outF,'<h2><a name="Higgs mass">Plots</a></h2>'
print >>outF,'<h2><a name="Cut Study">Plots</a></h2>'
print >>outF,'<div>'
print >>outF,'<div class="pic">'
#indir = 'MHiggs'
indir = 'CutStudy'
#indir = 'Plts'
#indir = 'Plts_mllCut_70'
#indir = 'Plts_OF_CommonCut'
#indir = 'Plts_OF_LooseCut'
for dirpath, dirnames, filenames in os.walk(indir):
  for f in filenames:
    if "png" in f: 
      print >>outF, '<h3><a href="'+indir+'/'+f+'">'+f+'</a></h3><a href="'+indir+'/'+f+'"><img src="'+indir+'/'+f+'" style="border: none; width: 500px; "></a></div><div class="pic">'

print >>outF,'</div>'
print >>outF,'</div>'
print >>outF,'</body>'
print >>outF,'</html>'
