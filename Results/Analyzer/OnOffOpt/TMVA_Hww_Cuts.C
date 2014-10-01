   
TCut GenOffCut = "mWW>=150";
TCut GenOnCut = "mWW<150";
TCut CommonCut    = "pt1>20 && pt2>10 && trigger ==1 && nextra==0 && pfmet>20 && mll>12 && mpmet>20 && (njet ==0 || njet==1) && bveto_mu == 1 && bveto_ip==1 && ptll>30";
TCut CommonCut0J    = "pt1>20 && pt2>10 && trigger ==1 && nextra==0 && pfmet>20 && mll>12 && mpmet>20 && njet ==0 && bveto_mu == 1 && bveto_ip==1 && ptll>30";
TCut CommonCut1J    = "pt1>20 && pt2>10 && trigger ==1 && nextra==0 && pfmet>20 && mll>12 && mpmet>20 && njet ==1 && bveto_mu == 1 && bveto_ip==1 && ptll>30";
TCut CommonNoptll = "pt1>20 && pt2>10 && trigger ==1 && nextra==0 && pfmet>20 && mll>12 && mpmet>20 && (njet ==0 || njet==1) && bveto_mu == 1 && bveto_ip==1";
TCut ChannelCut = "(channel == 2 || channel == 3)";
TCut OffShellCut = "mll > 70 || mth > 130";
//TCut OffShellCut = "mll > 83 && ptll > 10";

TCut ChanCommCut = ChannelCut && CommonCut;
TCut ChanCommNoptll = ChannelCut && CommonNoptll;
TCut ChanCommOff = ChannelCut && CommonCut && OffShellCut;
TCut ChanCommOff0J = ChannelCut && CommonCut0J && OffShellCut;
TCut ChanCommOff1J = ChannelCut && CommonCut1J && OffShellCut;
