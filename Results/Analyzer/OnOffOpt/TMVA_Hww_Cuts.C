   
TCut GenOffCut = "mWW>=160";
TCut GenOnCut = "mWW<160";
TCut CommonCut = "pt1>20 && pt2>10 && trigger ==1 && nextra==0 && pfmet>20 && mll>12 && mpmet>20 && (njet ==0 || njet==1) && bveto_mu == 1 && bveto_ip==1 && ptll>30";
TCut CommonNoptll = "pt1>20 && pt2>10 && trigger ==1 && nextra==0 && pfmet>20 && mll>12 && mpmet>20 && (njet ==0 || njet==1) && bveto_mu == 1 && bveto_ip==1";
TCut ChannelCut = "(channel == 2 || channel == 3)";
TCut OffShellCut = "mll > 83 && ptll > 10";

TCut ChanCommCut = ChannelCut && CommonCut;
TCut ChanCommNoptll = ChannelCut && CommonNoptll;
TCut ChanCommOff = ChannelCut && CommonNoptll && OffShellCut;
