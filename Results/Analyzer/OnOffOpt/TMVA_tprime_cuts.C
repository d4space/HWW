   // cut definitions
   TCut cut_pre = "(leptonSumMass>20.0&&nJets>=2&&nBTag>0)";

   TCut cut_os_cat1  = "(nLeptons==2&&(abs(isMuon1+isMuon2)==2||(isMuon1+isMuon2)==0)&&(leptonSumMass<76.0||leptonSumMass>106.0)&&(nJets==2||nJets==3))";

   TCut cut_os_cat2  = "(nLeptons==2&&(abs(isMuon1+isMuon2)==2||(isMuon1+isMuon2)==0)&&nJets>=5)";

   TCut cut_ss  = "(nLeptons==2&&(abs(isMuon1+isMuon2)==26||abs(isMuon1+isMuon2)==24||abs(isMuon1+isMuon2)==22)&&nJets>=3&&nBTag>1)";

   TCut cut_tri = "(nLeptons>2&&nJets>=3)";

   TCut mycut  = cut_pre && (cut_os_cat1 || cut_os_cat2 || cut_ss || cut_tri) ;

//   TCut mycut  = cut_pre && (cut_tri) ;
