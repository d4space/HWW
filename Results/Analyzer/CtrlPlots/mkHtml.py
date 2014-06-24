import os
outF =open('index.html','w+')
print >>outF,'<html>'
print >>outF,'<head>'
print >>outF,'<title>HWW Width CtrPlts</title>'
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
print >>outF,'<h1>/afs/cern.ch/user/h/Hahaha/www/HWwCtrPlots</h1>'
print >>outF,'<h2><a name="HWW width Ctl Plts">Plots</a></h2>'
print >>outF,'<div>'
print >>outF,'<div class="pic">'
indir = 'Plts'
for dirpath, dirnames, filenames in os.walk(indir):
  for f in filenames:
    if "png" in f: 
      print >>outF, '<h3><a href="'+indir+'/'+f+'">'+f+'</a></h3><a href="'+indir+'/'+f+'"><img src="'+indir+'/'+f+'" style="border: none; width: 500px; "></a></div><div class="pic">'

print >>outF,'</div>'
print >>outF,'</div>'
print >>outF,'</body>'
print >>outF,'</html>'
