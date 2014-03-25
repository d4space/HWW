#!/bin/tcsh -f
set DirName_Base = $1
set DirName = $2
set OutFile = "chain_$DirName.h"
echo "The directory is $DirName_Base/$DirName"
  #foreach fileName ( `ls  $DIRNAME/*.root | awk '{print $9}' `)
  echo "void chain_$DirName( TChain *chains)">$OutFile
  echo '{'>>$OutFile
  foreach fileName ( `ls  $DirName_Base/$DirName/*.root `)
    echo $fileName
    echo '  chains->Add("'$fileName'");'>>$OutFile
  end
  echo '}'>>$OutFile
