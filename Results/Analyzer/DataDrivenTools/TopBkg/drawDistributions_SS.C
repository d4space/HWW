#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TTree.h"

const UInt_t nProcesses = 12;

//enum {iData, iWW, iWZ, iZZ, iWg, itt, itW, iWj, iDY, iDYtau, iZgamma, iH125};
enum {iData, iWW, iH125, iDY, iDYtau, itt, itW, iWZ, iZZ, iWg, iZgamma, iWj};

TFile* input_0[nProcesses];
TFile* input_1[nProcesses];

TString process[nProcesses];

process[iData]   = "DataRun2012_Total";
process[itt]     = "TTbar";
process[itW]     = "TW";
process[iWW]     = "WW";
process[iWZ]     = "WZ";
process[iZZ]     = "ZZ";
process[iWg]     = "Wgamma";
process[iWj]     = "WJetsFakes_Total";
process[iDY]     = "DY";
process[iDYtau]  = "DYtautau";
process[iZgamma] = "Zgamma";
process[iH125]   = "HWW125";


Color_t color[nProcesses];

color[iData]   = kBlack;
color[itt]     = kYellow;
color[itW]     = kYellow;
color[iWW]     = kAzure-9;
color[iWZ]     = kAzure-2;
color[iZZ]     = kAzure-2;
color[iWg]     = kAzure-2;
color[iWj]     = kGray+1;
color[iDY]     = kGreen+2;
color[iDYtau]  = kGreen+2;
color[iZgamma] = kGreen+2;
color[iH125]   = kRed;


Double_t systError[nProcesses];

systError[iData] = 0.0;

// syst. / yield for the 0-jet bin. These numbers are for the WW study. We need to calculate systematic uncertainty for the case ggH
systError[itt]     = 21.7 / 166.0;
systError[itW]     = 21.7 / 166.0;
systError[iWW]     = 67.7 / 939.5;
systError[iWZ]     =  3.3 /  41.2;
systError[iZZ]     =  3.3 /  41.2;
systError[iWg]     =  6.1 /  19.3;
systError[iWj]     = 36.9 / 102.5;
systError[iDY]     =  9.8 /  58.2;
systError[iDYtau]  =  9.8 /  58.2;
systError[iZgamma] =  2.7 /  36.1;
systError[iH125]   =  2.7 /  36.1;


// Settings
//------------------------------------------------------------------------------
TString  _channel;
TString  _format;
TString  _output;
Int_t    _njet;
Double_t _luminosity;
Bool_t   _dataDriven;
Bool_t   _setLogy;


// Scale factors
//------------------------------------------------------------------------------
// WW Scale factors
//Double_t ttScale[] = {1.10, 1.10, 1.10, 1.10};
//Double_t tWScale[] = {1.10, 1.10, 1.10, 1.10};
//Double_t WWScale[] = {1.00, 0.92, 1.02, 1.08};
//Double_t ZjScale[] = {3.70, 4.20, 1.80, 4.00};

//ggH Scale factors: 0- and 1-jet bins
//Double_t ttScale[] = {1.11, 1.11}; // from khakim
//Double_t tWScale[] = {1.11, 1.11}; // from khakim
//Double_t ttScale[] = {1.0,  1.0};
//Double_t tWScale[] = {1.0,  1.0};
Double_t ttScale[] = {0.95,  0.95};
Double_t tWScale[] = {0.9,  0.9};
Double_t WWScale[] = {1.04, 0.95};
Double_t ZjScale[] = {3.43, 3.62};

// Levels
//------------------------------------------------------------------------------
const UInt_t nLevels = 11;

enum {
  Trigger,
  MetCut,
  LowMinv,
  ZVeto,
  pMetCut,
  JetVeto,
  DeltaPhiJet,
  SoftMuVeto,
  ExtraLepton,
  Ptll,
  TopTagging
};

const TString sLevel[nLevels] = {
  "Trigger",
  "MetCut",
  "LowMinv",
  "ZVeto",
  "pMetCut",
  "JetVeto",
  "DeltaPhiJet",
  "SoftMuVeto",
  "ExtraLepton",
  "Ptll",
  "TopTagging"
};

const TString NM1Label[nLevels] = {
  "",
  "(no loose MET cut) ",
  "(no low m_{#font[12]{ll}} cut) ",
  "(no Z veto) ",
  "(no minmet cut) ",
  "(no jet veto) ",
  "(no #Delta#phi_{#font[12]{ll}} cut) ",
  "(no soft #mu veto) ",
  "(no extra lepton veto) ",
  "(no p_{T}^{#font[12]{ll}} cut) ",
  "(no top veto) "
};


//------------------------------------------------------------------------------
// drawDistributions
//------------------------------------------------------------------------------
void drawDistributions_SS(Int_t    njet       = 10,
		          TString  channel    = "SS",
		          Double_t luminosity = 19365,
		          TString  format     = "png",
		          Bool_t   drawRatio  = true,
		          Bool_t   dataDriven = true,
		          Bool_t   setLogy    = false)
{
  _channel    = channel;
  _njet       = njet;
  _luminosity = luminosity;
  _format     = format;
  _dataDriven = dataDriven;
  _setLogy    = setLogy;

  MakeDirectory();

  gStyle->SetHatchesLineWidth(1.00);
  gStyle->SetHatchesSpacing  (0.55);


  cout<<"Njet: "<<_njet<<"++++++++++++++++++++"<<endl;
  // Read input files
  //----------------------------------------------------------------------------
  if (_njet == 10){
    TString path_0jet = Form("rootfiles/0jet/%s/", _channel.Data());
    TString path_1jet = Form("rootfiles/1jet/%s/", _channel.Data());
  }

  for (UInt_t ip=0; ip<nProcesses; ip++){
    if(_njet == 10){
      input_0[ip] = new TFile(path_0jet + process[ip] + ".root", "read");
      input_1[ip] = new TFile(path_1jet + process[ip] + ".root", "read");
    }else{
      //input[ip] = new TFile(path + process[ip] + ".root", "read");
    }
  }


  // DY distributions
  //----------------------------------------------------------------------------
  if (0) {
    DrawHistogram("hMassInZevents45.00",  "m_{#font[12]{ll}}", 1, 0, "GeV", 76, 106);
    DrawHistogram("hMassOutZevents45.00", "m_{#font[12]{ll}}", 5, 0, "GeV");
  }


  // Top distributions
  //----------------------------------------------------------------------------
  if (1) {
    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion", "2^{nd} jet TCHE", 5, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisNTopControlRegion",          "2^{nd} jet TCHE", 5, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents",            "2^{nd} jet TCHE", 5, 1, "NULL", -999, 999, false);

    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_channel", "channel", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisNTopControlRegion_channel",          "channel", 1, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents_channel",            "channel", 1, 1, "NULL", -999, 999, false);

    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_dphill", "#Delta#phi_{ll} [^{0}]", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisNTopControlRegion_dphill",          "#Delta#phi_{ll} [^{0}]", 1, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents_dphill",            "#Delta#phi_{ll} [^{0}]", 1, 1, "NULL", -999, 999, false);

    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_jetpt1", "p_{T}^{jet, max} [GeV/c]", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisNTopControlRegion_jetpt1",          "p_{T}^{jet, max} [GeV/c]", 1, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents_jetpt1",            "p_{T}^{jet, max} [GeV/c]", 1, 1, "NULL", -999, 999, false);

    //_setLogy    = true;
    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_bdt1", "BDT1 distribution", 5, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisNTopControlRegion_bdt1",          "BDT1 distribution", 5, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents_bdt1",            "BDT1 distribution", 5, 1, "NULL", -999, 999, false);

    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_bdt2", "BDT2 distribution", 5, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisNTopControlRegion_bdt2",          "BDT2 distribution", 5, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents_bdt2",            "BDT2 distribution", 5, 1, "NULL", -999, 999, false);

    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_jetmva1", "1st jet JetMVA", 1, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisNTopControlRegion_jetmva1",          "1st jet JetMVA", 1, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents_jetmva1",            "1st jet JetMVA", 1, 1, "NULL", -999, 999, false);
    //_setLogy    = false;

    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_HwidthMVAbkg", "MVA (Sig, Bkg)", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisNTopControlRegion_HwidthMVAbkg",          "MVA (Sig, Bkg)", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisTopTaggedEvents_HwidthMVAbkg",            "MVA (Sig, Bkg)", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisTopTaggedEvents_HwidthMVAbkg_nobveto_tche1",            "MVA (Sig, Bkg)", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisTopTaggedEvents_HwidthMVAbkg_nobveto",            "MVA (Sig, Bkg)", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisTopTaggedEvents_HwidthMVAbkg_tche1",            "MVA (Sig, Bkg)", 1, 1, "NULL", -999, 999, false);
    
    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_softtche", "TCHE b-Tag (15<p_{T}^{jet}<30 GeV/c)", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisNTopControlRegion_softtche",          "TCHE b-Tag (15<p_{T}^{jet}<30 GeV/c)", 1, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents_softtche",            "TCHE b-Tag (15<p_{T}^{jet}<30 GeV/c)", 1, 1, "NULL", -999, 999, false);

    //DrawHistogram("hbTagDisNTopTaggedTopControlRegion_hardtche", "TCHE b-Tag (p_{T}^{jet}>30 GeV/c)", 1, 1, "NULL", -999, 999, false);
    DrawHistogram("hbTagDisNTopControlRegion_hardtche",          "TCHE b-Tag (p_{T}^{jet}>30 GeV/c)", 1, 1, "NULL", -999, 999, false);
    //DrawHistogram("hbTagDisTopTaggedEvents_hardtche",            "TCHE b-Tag (p_{T}^{jet}>30 GeV/c)", 1, 1, "NULL", -999, 999, false);
	
    //Subtraction("hbTagDisNTopTaggedTopControlRegion_channel", "channel", 1, 1, "NULL", -999, 999, false);
    //Subtraction("hbTagDisNTopControlRegion_channel",          "channel", 1, 1, "NULL", -999, 999, false);
    //Subtraction("hbTagDisTopTaggedEvents_channel",            "channel", 1, 1, "NULL", -999, 999, false);
  }


  // PAS distributions
  //----------------------------------------------------------------------------
  if (0) {
    DrawHistogram("hPtLepton1TopTagging",       "p_{T}^{max}",                 5, 0, "GeV",  0, 160);
    DrawHistogram("hPtLepton2TopTagging",       "p_{T}^{min}",                 5, 0, "GeV", 15,  80);
    DrawHistogram("hPtDiLeptonTopTagging",      "p_{T}^{#font[12]{ll}}",       5, 0, "GeV", 40, 120);
    DrawHistogram("hMinvTopTagging",            "m_{#font[12]{ll}}",           5, 0, "GeV");
    DrawHistogram("hDeltaPhiLeptonsTopTagging", "#Delta#phi_{#font[12]{ll}}", -1, 1, "rad");
    
  }


  // N-1 distributions
  //----------------------------------------------------------------------------
  if (0) {
    DrawNM1("hDeltaPhiLeptons", "#Delta#phi_{#font[12]{ll}}", -1, 1, "rad");
    DrawNM1("hMinv",            "m_{#font[12]{ll}}",           4, 0, "GeV");
    DrawNM1("hPtDiLepton",      "p_{T}^{#font[12]{ll}}",       4, 0, "GeV", 0, 120);
    DrawNM1("hNJetsPF30",       "N_{jets}",                   -1, 0, "NULL");
  }
}


//------------------------------------------------------------------------------
// MakeDirectory
//------------------------------------------------------------------------------
void MakeDirectory()
{
  if( _njet == 10){
    _output = Form("%s/0plus1jet/%s", _format.Data(), _channel.Data());
  }else  _output = Form("%s/%djet/%s", _format.Data(), _njet, _channel.Data());

  gSystem->Exec(Form("rm -rf %s", _output.Data()));

  gSystem->mkdir(_output, kTRUE);

  //gSystem->Exec(Form("cp index.php %s/.", _format.Data()));

  //gSystem->Exec(Form("cp index.php %s/%djet/.", _format.Data(), _njet));

  //gSystem->Exec(Form("cp index.php %s/.", _output.Data()));
}


//------------------------------------------------------------------------------
// DrawNM1
//------------------------------------------------------------------------------
void DrawNM1(TString  hname,
	     TString  xtitle,
	     Int_t    ngroup       = -1,
	     Int_t    precision    = 1,
	     TString  units        = "NULL",
	     Double_t xmin         = -999,
	     Double_t xmax         =  999)
{
  for (UInt_t i=0; i<nLevels; i++)
    {
      if (hname.Contains("PtDiLepton") && !sLevel[i].Contains("Ptll"))    continue;
      if (hname.Contains("NJetsPF30")  && !sLevel[i].Contains("JetVeto")) continue;

      DrawHistogram(hname + sLevel[i] + "_NM1",
		    NM1Label[i] + xtitle,
		    ngroup,
		    precision,
		    units,
		    xmin,
		    xmax);
    }
} 


//------------------------------------------------------------------------------
// DrawHistogram
//------------------------------------------------------------------------------
void DrawHistogram(TString  hname,
		   TString  xtitle,
		   Int_t    ngroup       = -1,
		   Int_t    precision    = 1,
		   TString  units        = "NULL",
		   Double_t xmin         = -999,
		   Double_t xmax         =  999,
		   Bool_t   moveOverflow = true)
{
  //TCanvas* canvas = new TCanvas(hname, hname, 550, 720);
  TCanvas* canvas = new TCanvas(hname, hname, 800, 800);

  TPad* pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  TPad* pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 0.3); 

  pad1->SetTopMargin   (0.08);
  pad1->SetBottomMargin(0.02);
  pad1->Draw();
      
  pad2->SetTopMargin   (0.08);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();


  //----------------------------------------------------------------------------
  // pad1
  //----------------------------------------------------------------------------
  pad1->cd();

  pad1->SetLogy(_setLogy);

  THStack* hstack = new THStack(hname, hname);

  TH1F* hist[nProcesses];
  TH1F* hist_0[nProcesses]; // 0-jet
  TH1F* hist_1[nProcesses]; // 1-jet

  for (UInt_t ip=0; ip<nProcesses; ip++) {
    if( _njet == 10 ){
      hist_0[ip] = (TH1F*)input_0[ip]->Get(hname);
      hist_1[ip] = (TH1F*)input_1[ip]->Get(hname);
    }else{
      //hist[ip] = (TH1F*)input[ip]->Get(hname);
      //hist[ip]->SetName(hname + process[ip]);
    }

    if (moveOverflow){
      if(_njet ==10){
	MoveOverflowBins  (hist_0[ip], xmin, xmax);
	MoveOverflowBins  (hist_1[ip], xmin, xmax);
      }else{
	//MoveOverflowBins  (hist[ip], xmin, xmax);
      }
    }else{
      if(_njet == 10){
	ZeroOutOfRangeBins(hist_0[ip], xmin, xmax);
	ZeroOutOfRangeBins(hist_1[ip], xmin, xmax);
      }else{
	//ZeroOutOfRangeBins(hist[ip], xmin, xmax);
      }
    }

    if (ngroup > 0){
      if(_njet == 10){
	hist_0[ip]->Rebin(ngroup);
	hist_1[ip]->Rebin(ngroup);
      }else{
	//hist[ip]->Rebin(ngroup);
      }
    }
   // Add 0, 1 jet 
    if (ip == iData) {
      if(_njet == 10 ){
	hist[ip] = (TH1F*)hist_0[ip]->Clone(hname+process[ip]);
	hist[ip]->Add(hist_1[ip]);
	hist[ip]->SetMarkerStyle(kFullCircle);
      }else{
	//hist[ip]->SetMarkerStyle(kFullCircle);
      }
    }
    else {
      if(_njet == 10){

        if (_dataDriven && ip == itt)    hist_0[ip]->Scale(ttScale[0]);
        if (_dataDriven && ip == itW)    hist_0[ip]->Scale(tWScale[0]);
        if (_dataDriven && ip == iWW)    hist_0[ip]->Scale(WWScale[0]);
        if (_dataDriven && ip == iDY)    hist_0[ip]->Scale(ZjScale[0]);
        if (_dataDriven && ip == iDYtau) hist_0[ip]->Scale(ZjScale[0]);

        if (_dataDriven && ip == itt)    hist_1[ip]->Scale(ttScale[1]);
        if (_dataDriven && ip == itW)    hist_1[ip]->Scale(tWScale[1]);
        if (_dataDriven && ip == iWW)    hist_1[ip]->Scale(WWScale[1]);
        if (_dataDriven && ip == iDY)    hist_1[ip]->Scale(ZjScale[1]);
        if (_dataDriven && ip == iDYtau) hist_1[ip]->Scale(ZjScale[1]);

	hist[ip] = (TH1F*)hist_0[ip]->Clone(hname+process[ip]);
	hist[ip]->Add(hist_1[ip]);
        hist[ip]->SetFillColor(color[ip]);
        hist[ip]->SetFillStyle(1001);
        hist[ip]->SetLineColor(color[ip]);

      }else{
        //hist[ip]->SetFillColor(color[ip]);
        //hist[ip]->SetFillStyle(1001);
        //hist[ip]->SetLineColor(color[ip]);

        //if (_dataDriven && ip == itt)    hist[ip]->Scale(ttScale[_njet]);
        //if (_dataDriven && ip == itW)    hist[ip]->Scale(tWScale[_njet]);
        //if (_dataDriven && ip == iWW)    hist[ip]->Scale(WWScale[_njet]);
        //if (_dataDriven && ip == iDY)    hist[ip]->Scale(ZjScale[_njet]);
        //if (_dataDriven && ip == iDYtau) hist[ip]->Scale(ZjScale[_njet]);
      }
      hstack->Add(hist[ip]);
    }
  }

  //=========================================================
  //Save histograms to root file to draw paper style plots
  //=========================================================
  //TFile* outfile;
  //TString fname = Form("files/%s_%djet.root", hname.Data(),_njet);
  //TString fname = "files/0jet_"+hname+".root";
  //if(_njet==1) fname = "files/1jet_"+hname+".root";
  //if(_njet==10) fname = "files/10jet_"+hname+".root";
  //outfile = new TFile(fname, "create");
  
  //if(ip == iData)   TH1F* data     = (TH1F*)hist[iData]->Clone("Data");     //data   -> Sumw2();
  //if(ip == itt)     TH1F* top      = (TH1F*)hist[itt]->Clone("top");        //top    -> Sumw2();
  //if(ip == itW)     TH1F* tW       = (TH1F*)hist[itW]->Clone("tW");         //tW     -> Sumw2();
  //if(ip == iWW)     TH1F* WW       = (TH1F*)hist[iWW]->Clone("WW");         //WW     -> Sumw2();
  //if(ip == iWZ)     TH1F* VVandVVV = (TH1F*)hist[iWZ]->Clone("VVandVVV");   //VV     -> Sumw2();
  //if(ip == iZZ)     TH1F* ZZ       = (TH1F*)hist[iZZ]->Clone("ZZ");         //ZZ     -> Sumw2();
  //if(ip == iWg)     TH1F* Wg       = (TH1F*)hist[iWg]->Clone("Wg");         //Wg     -> Sumw2();
  //if(ip == iWj)     TH1F* Wjets    = (TH1F*)hist[iWj]->Clone("W+jets");     //Wjets  -> Sumw2();
  //if(ip == iDY)     TH1F* Zjets    = (TH1F*)hist[iDY]->Clone("Z+jets");     //Zjets  -> Sumw2();
  //if(ip == iDYtau)  TH1F* DYtau    = (TH1F*)hist[iDYtau]->Clone("DYtau");   //DYtau  -> Sumw2();
  //if(ip == iZgamma) TH1F* Zgamma   = (TH1F*)hist[iZgamma]->Clone("Zgamma"); //Zgamma -> Sumw2();
  //if(ip == iH125)   TH1F* ggH      = (TH1F*)hist[iH125]->Clone("ggH");      //ggH    -> Sumw2();
  //
  //top      -> Add(tW);
  //VVandVVV -> Add(ZZ);
  //VVandVVV -> Add(Wg);  
  //Zjets    -> Add(DYtau);
  //Zjets    -> Add(Zgamma);
  //
  //data     -> Write();
  //top      -> Write();
  //WW       -> Write();
  //VVandVVV -> Write();
  //Wjets    -> Write();
  //Zjets    -> Write();
  //ggH      -> Write();
  //
  //outfile -> Close();
  //
  //=========================================================
  //Draw paper style plots
  //=========================================================
  //Use LatinoPlotTools.
  //As input root file, use above saved root file "outfile"
  //Run the following executable file:
  //https://github.com/latinos/LatinoPlotTools/blob/master/WWRunI/scripts/doHWidth_Top_control.sh

  // All MC
  //----------------------------------------------------------------------------
  TH1F* allmc = (TH1F*)hist[iData]->Clone("allmc");

  allmc->SetFillColor  (kGray+2);
  allmc->SetFillStyle  (   3345);
  allmc->SetLineColor  (kGray+2);
  allmc->SetMarkerColor(kGray+2);
  allmc->SetMarkerSize (      0);

  for (UInt_t ibin=1; ibin<=allmc->GetNbinsX(); ibin++) {

    Double_t binValue = 0;
    Double_t binError = 0;

    for (UInt_t ip=0; ip<nProcesses; ip++) {

      if (ip == iData) continue;

      Double_t binContent = hist[ip]->GetBinContent(ibin);
      
      binValue += binContent;
      binError += (hist[ip]->GetBinError(ibin) * hist[ip]->GetBinError(ibin));

      //We need to calculate systematic uncertainty for ggH case
//      if (_dataDriven)
//	binError += (systError[ip]*binContent * systError[ip]*binContent);
    }
    
    binError = sqrt(binError);

    allmc->SetBinContent(ibin, binValue);
    allmc->SetBinError  (ibin, binError);
  }


  // Axis labels
  //----------------------------------------------------------------------------
  TAxis* xaxis = hist[iData]->GetXaxis();
  TAxis* yaxis = hist[iData]->GetYaxis();

  TString ytitle = Form("entries / %s.%df", "%", precision);

  xaxis->SetTitle(xtitle);
  yaxis->SetTitle(Form(ytitle.Data(), hist[iData]->GetBinWidth(0)));
  yaxis->SetTitleOffset(1.6);

  if (!units.Contains("NULL")) {
    
    xaxis->SetTitle(Form("%s [%s]", xaxis->GetTitle(), units.Data()));
    yaxis->SetTitle(Form("%s %s",   yaxis->GetTitle(), units.Data()));
  }


  // Draw
  //----------------------------------------------------------------------------
  xaxis->SetRangeUser(xmin, xmax);

  hist[iData]->Draw("ep");
  hstack     ->Draw("hist,same");
  allmc      ->Draw("e2,same");
  hist[iData]->Draw("ep,same");


  // Adjust scale
  //----------------------------------------------------------------------------
  Float_t theMax   = GetMaximumIncludingErrors(hist[iData], xmin, xmax);
  Float_t theMaxMC = GetMaximumIncludingErrors(allmc,       xmin, xmax);

  if (theMaxMC > theMax) theMax = theMaxMC;

  if (pad1->GetLogy()) {

    theMax = TMath::Power(10, TMath::Log10(theMax) + 2.7);

    hist[iData]->SetMinimum(0.05);
  }
  else theMax *= 1.55;

  hist[iData]->SetMaximum(theMax);


  // Legend
  //----------------------------------------------------------------------------
  Double_t x0      = 0.720; 
  Double_t y0      = 0.834; 
  Double_t yoffset = 0.048;
  Double_t delta   = yoffset + 0.001;
  Double_t ndelta  = 0;

  Double_t YieldTop   = Yield(hist[itt]) + Yield(hist[itW]);
  Double_t YieldVV    = Yield(hist[iWZ]) + Yield(hist[iZZ]) + Yield(hist[iWg]);
  //Double_t YieldZJets = Yield(hist[iDY]) + Yield(hist[iDYtau]);
  Double_t YieldZJets = Yield(hist[iDY]) + Yield(hist[iDYtau]) + Yield(hist[iZgamma]);

  DrawLegend(x0 - 0.49, y0 - ndelta, hist[iData], Form(" data (%.0f)", Yield(hist[iData])), "lp", 0.03, 0.2, yoffset); ndelta += delta;
  DrawLegend(x0 - 0.49, y0 - ndelta, allmc,       Form(" all (%.0f)",  Yield(allmc)),       "f",  0.03, 0.2, yoffset); ndelta += delta;
  DrawLegend(x0 - 0.49, y0 - ndelta, hist[iWW],   Form(" WW (%.0f)",   Yield(hist[iWW])),   "f",  0.03, 0.2, yoffset); ndelta += delta;
  DrawLegend(x0 - 0.49, y0 - ndelta, hist[iWZ],   Form(" VV (%.0f)",   YieldVV),            "f",  0.03, 0.2, yoffset); ndelta += delta;

  ndelta = 0;

  DrawLegend(x0 - 0.23, y0 - ndelta, hist[iDY],   Form(" Z+jets (%.0f)", YieldZJets),         "f",  0.03, 0.2, yoffset); ndelta += delta;
  DrawLegend(x0 - 0.23, y0 - ndelta, hist[iWj],   Form(" W+jets (%.0f)", Yield(hist[iWj])),   "f",  0.03, 0.2, yoffset); ndelta += delta;
  DrawLegend(x0 - 0.23, y0 - ndelta, hist[itt],   Form(" top (%.0f)",    YieldTop),           "f",  0.03, 0.2, yoffset); ndelta += delta;
  //DrawLegend(x0 - 0.23, y0 - ndelta, hist[iH125], Form(" Higgs (%.0f)",  Yield(hist[iH125])), "f",  0.03, 0.2, yoffset); ndelta += delta;
  DrawLegend(x0 - 0.23, y0 - ndelta, hist[iH125], Form(" ggH (%.0f)",  Yield(hist[iH125])), "f",  0.03, 0.2, yoffset); ndelta += delta;


  // Additional titles
  //----------------------------------------------------------------------------
  //TString channelLabel = "ee/#mu#mu/e#mu/#mue";
  TString channelLabel = "";

  //if (_channel == "EE")   channelLabel = "ee";
  //if (_channel == "MuMu") channelLabel = "#mu#mu";
  //if (_channel == "EMu")  channelLabel = "e#mu";
  //if (_channel == "MuE")  channelLabel = "#mue";
  //if (_channel == "SF")   channelLabel = "ee/#mu#mu";
  //if (_channel == "OF")   channelLabel = "e#mu/#mue";

  if( _njet != 10)
    channelLabel += Form(" %d", _njet);

  if (_njet == 0) channelLabel += "-jets";
  if (_njet == 1) channelLabel += "-jet";
  if (_njet >= 2 && _njet!= 10) channelLabel += "-jets";
  if ( _njet== 10) channelLabel += "SS 0+1 jets";

  DrawTLatex(0.185, 0.975, 0.05, 13, channelLabel.Data());
  DrawTLatex(0.940, 0.983, 0.05, 33, Form("L = %.1f fb^{-1}", _luminosity/1e3));

  //----------------------------------------------------------------------------
  // pad2
  //----------------------------------------------------------------------------
  pad2->cd();
    
  TH1F* ratio       = hist[iData]->Clone("ratio");
  TH1F* uncertainty = allmc->Clone("uncertainty");
    
  for (UInt_t ibin=1; ibin<=ratio->GetNbinsX(); ibin++) {

    Double_t mcValue = allmc->GetBinContent(ibin);
    Double_t mcError = allmc->GetBinError  (ibin);
    
    Double_t dtValue = ratio->GetBinContent(ibin);
    Double_t dtError = ratio->GetBinError  (ibin);

    Double_t ratioValue       = (mcValue > 0) ? dtValue/mcValue : 0.0;
    Double_t ratioError       = (mcValue > 0) ? dtError/mcValue : 0.0;
    Double_t uncertaintyError = (mcValue > 0) ? mcError/mcValue : 0.0;

    ratio->SetBinContent(ibin, ratioValue);
    ratio->SetBinError  (ibin, ratioError);

    uncertainty->SetBinContent(ibin, 1.0);
    uncertainty->SetBinError  (ibin, uncertaintyError);
  }


  TAxis* uaxis = (TAxis*)uncertainty->GetXaxis();
    
  uaxis->SetRangeUser(xmin, xmax);
    
    
  uncertainty->Draw("e2");
  ratio      ->Draw("ep,same");

  uncertainty->GetYaxis()->SetRangeUser(0, 2.5);


  // Save
  //----------------------------------------------------------------------------
  pad2->cd(); SetAxis(uncertainty, hist[iData]->GetXaxis()->GetTitle(), "data / prediction", 0.10, 0.8);
  pad1->cd(); SetAxis(hist[iData], "", hist[iData]->GetYaxis()->GetTitle(),                  0.05, 1.6);

  canvas->cd();

  TString suffixLogy = (_setLogy) ? "_Log" : "_Lin";

  canvas->SaveAs(Form("%s/%s%s.%s",
		      _output.Data(),
		      hname.Data(),
		      suffixLogy.Data(),
		      _format.Data()));
}


//------------------------------------------------------------------------------
// GetMaximumIncludingErrors
//------------------------------------------------------------------------------
Float_t GetMaximumIncludingErrors(TH1F*    h,
				  Double_t xmin,
				  Double_t xmax)
{
  UInt_t nbins = h->GetNbinsX();

  TAxis* axis = (TAxis*)h->GetXaxis();
  
  Int_t firstBin = (xmin != -999) ? axis->FindBin(xmin) : 1;
  Int_t lastBin  = (xmax !=  999) ? axis->FindBin(xmax) : nbins;

  Float_t maxWithErrors = 0;

  for (Int_t i=firstBin; i<=lastBin; i++) {

    Float_t binHeight = h->GetBinContent(i) + h->GetBinError(i);

    if (binHeight > maxWithErrors) maxWithErrors = binHeight;
  }

  return maxWithErrors;
}


//------------------------------------------------------------------------------
// MoveOverflowBins
//------------------------------------------------------------------------------
void MoveOverflowBins(TH1* h,
		      Double_t xmin,
		      Double_t xmax) const
{
  UInt_t nbins = h->GetNbinsX();

  TAxis* axis = (TAxis*)h->GetXaxis();
  
  Int_t firstBin = (xmin != -999) ? axis->FindBin(xmin) : 1;
  Int_t lastBin  = (xmax !=  999) ? axis->FindBin(xmax) : nbins;

  Double_t firstVal = 0;
  Double_t firstErr = 0;

  Double_t lastVal = 0;
  Double_t lastErr = 0;

  for (UInt_t i=0; i<=nbins+1; i++) {

    if (i <= firstBin) {
      firstVal += h->GetBinContent(i);
      firstErr += (h->GetBinError(i)*h->GetBinError(i));
    }

    if (i >= lastBin) {
      lastVal += h->GetBinContent(i);
      lastErr += (h->GetBinError(i)*h->GetBinError(i));
    }

    if (i < firstBin || i > lastBin) {
      h->SetBinContent(i, 0);
      h->SetBinError  (i, 0);
    }
  }

  firstErr = sqrt(firstErr);
  lastErr  = sqrt(lastErr);

  h->SetBinContent(firstBin, firstVal);
  h->SetBinError  (firstBin, firstErr);

  h->SetBinContent(lastBin, lastVal);
  h->SetBinError  (lastBin, lastErr);
}


//------------------------------------------------------------------------------
// ZeroOutOfRangeBins
//------------------------------------------------------------------------------
void ZeroOutOfRangeBins(TH1* h, Double_t xmin, Double_t xmax) const
{
  UInt_t nbins = h->GetNbinsX();

  TAxis* axis = (TAxis*)h->GetXaxis();
  
  Int_t firstBin = (xmin != -999) ? axis->FindBin(xmin) : 1;
  Int_t lastBin  = (xmax !=  999) ? axis->FindBin(xmax) : nbins;

  for (UInt_t i=0; i<=nbins+1; i++) {

    if (i < firstBin || i > lastBin) {
      h->SetBinContent(i, 0);
      h->SetBinError  (i, 0);
    }
  }
}


//------------------------------------------------------------------------------
// DrawTLatex
//------------------------------------------------------------------------------
void DrawTLatex(Double_t    x,
		Double_t    y,
		Double_t    tsize,
		Short_t     align,
		const char* text,
		Bool_t      setndc = true)
{
  TLatex* tl = new TLatex(x, y, text);

  tl->SetNDC      (setndc);
  tl->SetTextAlign( align);
  tl->SetTextFont (    42);
  tl->SetTextSize ( tsize);

  tl->Draw("same");
}


//------------------------------------------------------------------------------
// SetAxis
//------------------------------------------------------------------------------
void SetAxis(TH1*    hist,
	     TString xtitle,
	     TString ytitle,
	     Float_t size,
	     Float_t offset)
{
  TAxis* xaxis = (TAxis*)hist->GetXaxis();
  TAxis* yaxis = (TAxis*)hist->GetYaxis();

  xaxis->SetLabelFont(42);
  yaxis->SetLabelFont(42);
  xaxis->SetTitleFont(42);
  yaxis->SetTitleFont(42);

  xaxis->SetLabelOffset(0.025);
  yaxis->SetLabelOffset(0.025);
  xaxis->SetTitleOffset(1.4);
  yaxis->SetTitleOffset(offset);

  xaxis->SetLabelSize(size);
  yaxis->SetLabelSize(size);
  xaxis->SetTitleSize(size);
  yaxis->SetTitleSize(size);

  xaxis->SetTitle(xtitle);
  yaxis->SetTitle(ytitle);

  xaxis->SetNdivisions(505);
  yaxis->SetNdivisions(505);

  yaxis->CenterTitle();

  gPad->GetFrame()->DrawClone();
  gPad->RedrawAxis();
}


//------------------------------------------------------------------------------
// Yield
//------------------------------------------------------------------------------
Double_t Yield(TH1* h)
{
  Int_t nbins = h->GetNbinsX();

  return h->Integral(0, nbins+1);
}

//------------------------------------------------------------------------------
//Subtraction 
//------------------------------------------------------------------------------
void Subtraction(TString  hname,
		   TString  xtitle,
		   Int_t    ngroup       = -1,
		   Int_t    precision    = 1,
		   TString  units        = "NULL",
		   Double_t xmin         = -999,
		   Double_t xmax         =  999,
		   Bool_t   moveOverflow = true)
{
  TCanvas* canvas = new TCanvas(hname, hname, 800, 800);

  TPad* pad1 = new TPad("pad1", "pad1", 0, 0.0, 1, 1.0);

  pad1->SetTopMargin   (0.08);
  //pad1->SetBottomMargin(0.02);
  pad1->Draw();
      

  //----------------------------------------------------------------------------
  // pad1
  //----------------------------------------------------------------------------
  pad1->cd();

  pad1->SetLogy(_setLogy);

  TH1F* hist[nProcesses];

  for (UInt_t ip=0; ip<nProcesses; ip++) {

    hist[ip] = (TH1F*)input[ip]->Get(hname);
    hist[ip]->SetName(hname + process[ip]);

    if (moveOverflow) MoveOverflowBins  (hist[ip], xmin, xmax);
    else              ZeroOutOfRangeBins(hist[ip], xmin, xmax);

	if (ngroup > 0) hist[ip]->Rebin(ngroup);

	if (_dataDriven && ip == iWW)    hist[ip]->Scale(WWScale[_njet]);
	if (_dataDriven && ip == iDY)    hist[ip]->Scale(ZjScale[_njet]);
	if (_dataDriven && ip == iDYtau) hist[ip]->Scale(ZjScale[_njet]);

  }

  // Data subtraction for Top background estimation
  //----------------------------------------------------------------------------
  TH1F* subData = (TH1F*)hist[iData]->Clone("subData");
  for (UInt_t ip=0; ip<nProcesses; ip++) {
	  if (ip == itt) continue;
	  if (ip == itW) continue;
	  if (ip == iData ) continue;
	  subData->Add(hist[ip],-1);
  }
  subData->SetLineColor(kRed+1);
  Double_t subData_Yield = subData->Integral();
  //subData->SetLineColor();

  // Top background
  //----------------------------------------------------------------------------
  TH1F* Top = (TH1F*)hist[itt]->Clone("Top");
  Top->Add(hist[itW]);
  Top->SetLineColor(kBlue+1);
  Double_t Top_Yield = Top->Integral();

  // Axis labels
  //----------------------------------------------------------------------------
  TAxis* xaxis = subData->GetXaxis();
  TAxis* yaxis = subData->GetYaxis();

  TString ytitle = Form("entries / %s.%df", "%", precision);

  xaxis->SetTitle(xtitle);
  yaxis->SetTitle(Form(ytitle.Data(), subData->GetBinWidth(0)));
  yaxis->SetTitleOffset(1.6);

  if (!units.Contains("NULL")) {
    
    xaxis->SetTitle(Form("%s [%s]", xaxis->GetTitle(), units.Data()));
    yaxis->SetTitle(Form("%s %s",   yaxis->GetTitle(), units.Data()));
  }


  // Draw
  //----------------------------------------------------------------------------
  xaxis->SetRangeUser(xmin, xmax);

  subData->Draw("hist");
  Top->Draw("hist same");

  // Adjust scale
  //----------------------------------------------------------------------------
  subData->SetMinimum(0.0);
  
  Float_t theMax   = GetMaximumIncludingErrors(subData, xmin, xmax);
  Float_t theMaxMC = GetMaximumIncludingErrors(Top,       xmin, xmax);

  if (theMaxMC > theMax) theMax = theMaxMC;

  if (pad1->GetLogy()) {

    theMax = TMath::Power(10, TMath::Log10(theMax) + 2.7);

    subData->SetMinimum(0.05);
  }
  else theMax *= 1.55;

  subData->SetMaximum(theMax);

  // Legend
  //----------------------------------------------------------------------------
  Double_t x0      = 0.720; 
  Double_t y0      = 0.834; 
  Double_t yoffset = 0.048;
  Double_t delta   = yoffset + 0.001;
  Double_t ndelta  = 0;

  DrawLegend(x0 - 0.49, y0 - ndelta, subData, Form(" Data Subtraction (MC without Top) (%.0f)", Yield(subData)), "l", 0.03, 0.2, yoffset); ndelta += delta;
  DrawLegend(x0 - 0.49, y0 - ndelta, Top,     Form(" Top (%.0f)",  Yield(Top)),     "l", 0.03, 0.2, yoffset); ndelta += delta;

  // Additional titles
  //----------------------------------------------------------------------------
  //TString channelLabel = "ee/#mu#mu/e#mu/#mue";
  TString channelLabel = "";

  //if (_channel == "EE")   channelLabel = "ee";
  //if (_channel == "MuMu") channelLabel = "#mu#mu";
  //if (_channel == "EMu")  channelLabel = "e#mu";
  //if (_channel == "MuE")  channelLabel = "#mue";
  //if (_channel == "SF")   channelLabel = "ee/#mu#mu";
  //if (_channel == "OF")   channelLabel = "e#mu/#mue";

  channelLabel += Form(" %d", _njet);

  if (_njet == 0) channelLabel += "-jets";
  if (_njet == 1) channelLabel += "-jet";
  if (_njet >= 2) channelLabel += "-jets";

  DrawTLatex(0.185, 0.975, 0.05, 13, channelLabel.Data());
  DrawTLatex(0.940, 0.983, 0.05, 33, Form("L = %.1f fb^{-1}", _luminosity/1e3));
  
  if (Top_Yield!=0){ 
	  cout << "subData_Yield = "<<subData_Yield<<", Top_Yield = "<<Top_Yield<<", Ratio = "<< subData_Yield/Top_Yield <<endl;
	  TLatex *tex3 = new TLatex(0.250, 0.75, "Scale Factor");
	  tex3->SetNDC();
	  tex3->SetTextSize(0.035);
	  tex3->Draw();
	  TLatex *tex4 = new TLatex(0.250, 0.7, Form("%.0f / %.0f = %3.3f",subData_Yield ,Top_Yield ,subData_Yield/Top_Yield));
	  tex4->SetNDC();
	  tex4->SetTextSize(0.035);
	  tex4->Draw();
  }


  // Save
  //----------------------------------------------------------------------------
  pad1->cd(); 
  //SetAxis(subData, "", subData->GetYaxis()->GetTitle(),                  0.05, 1.6);

  canvas->cd();

  TString suffixLogy = (_setLogy) ? "_Log" : "_Lin";

  canvas->SaveAs(Form("%s/%s%s_sub.%s",
		      _output.Data(),
		      hname.Data(),
		      suffixLogy.Data(),
		      _format.Data()));
  
}

