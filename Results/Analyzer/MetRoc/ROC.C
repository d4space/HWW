int ROC()
{
  TFile *Fpf =new TFile("TMVA_pfmet.root");
  TFile *Fpup=new TFile("TMVA_pupmet.root");
  TFile *Ftrk=new TFile("TMVA_trkmet.root");
  char title[50]="Background Rejection vs Signal Efficiency (ROC curve)";
  cout<<title<<endl;
  TH1D *hROcPf  = (TH1D*)Fpf ->Get("Method_Cuts/Cuts/MVA_Cuts_trainingRejBvsS")->Clone("hROcPf");
  TH1D *hROcPup = (TH1D*)Fpup->Get("Method_Cuts/Cuts/MVA_Cuts_trainingRejBvsS")->Clone("hROcPup");
  TH1D *hROcTrk = (TH1D*)Ftrk->Get("Method_Cuts/Cuts/MVA_Cuts_trainingRejBvsS")->Clone("hROcTrk");

  hROcPf  ->SetLineColor(kRed);
  hROcPup ->SetLineColor(kBlue);
  hROcTrk ->SetLineColor(kGreen);
  TCanvas *myCan = new TCanvas("myCan","Can",800,800);
  CPlot* Plot_ROC = new CPlot("ROC","ggH vs. DY","SigEffi","BkgRej");
  //CPlot* Plot_MET = new CPlot(fileName,titleName,"MET[GeV]",Ytitle);
  Plot_ROC->setOutDir("./plots");
  Plot_ROC->AddHist1D(hROcPf,"HIST",kRed);
  Plot_ROC->AddHist1D(hROcPup,"HIST",kBlue);
  Plot_ROC->AddHist1D(hROcTrk,"HIST",kGreen);
  Plot_ROC->SetLegend(0.2,0.2,0.4,0.4);
  Plot_ROC->GetLegend()->AddEntry(hROcPf,"PF","l");
  Plot_ROC->GetLegend()->AddEntry(hROcPup,"PUPPI","l");
  Plot_ROC->GetLegend()->AddEntry(hROcTrk,"Trk","l");
  Plot_ROC->Draw(myCan,kTRUE,"pdf");

  return 0;
}
