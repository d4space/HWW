#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>                   // standard I/O
#include <fstream>                   // standard I/O
#include <TMath.h>
#include <TFile.h>                    // file handle class
#include <TTree.h>                    // class to access ntuples
#include <TF1.h>                      // 1D function
#include <TFitResult.h>               // class to handle fit results
#include <TGraphErrors.h>             // graph class
#include <TGraphAsymmErrors.h>             // graph class
#include "Math/LorentzVector.h"       // 4-vector class

#include "../../../Utils/CPlot.hh"          // helper class for plots
#include "../../../Utils/MitStyleRemix.hh"  // style settings for drawing

#include "RooGlobalFunc.h"
#include "RooRealVar.h"
#include "RooLandau.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooFormulaVar.h"

#endif

using namespace RooFit;
typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > LorentzVector;
//typedef ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

//Double_t pol1Func(double *x, double *par)
//{
//  Double_t a  = par[0];
//  Double_t b  = par[1];
//  
//  return a+b*x[0];
//}

Double_t dpol1Func(const TF1 *fcn, const Double_t x, const TFitResultPtr fs) {
  Double_t df[2];
  Double_t a = fcn->GetParameter(0);
  Double_t b = fcn->GetParameter(1);
  
  df[0] = 1;
  df[1] = x;
  Double_t err2 = df[0]*df[0]*(fs->GetCovarianceMatrix()[0][0])
                  + df[1]*df[1]*(fs->GetCovarianceMatrix()[1][1])
		  + 2.0*df[0]*df[1]*(fs->GetCovarianceMatrix()[0][1]);
  assert(err2>=0);
  return sqrt(err2);
}

Double_t dpol2Func(const TF1 *fcn, const Double_t x, const TFitResultPtr fs) {
  Double_t df[3];
  Double_t a = fcn->GetParameter(0);
  Double_t b = fcn->GetParameter(1);
  Double_t c = fcn->GetParameter(2);
  
  df[0] = 1;
  df[1] = x;
  df[2] = x*x;
  
  Double_t err2=0;
  for(Int_t i=0; i<3; i++) {
    err2 += df[i]*df[i]*(fs->GetCovarianceMatrix()[i][i]);
    for(Int_t j=i+1; j<3; j++) {
      err2 += 2.0*df[i]*df[j]*(fs->GetCovarianceMatrix()[i][j]);
    }
  }

  assert(err2>=0);
  return sqrt(err2);
}

void scalefit()
{
  const Int_t nbins = 11;
  double Bins[12] = {130.,200.,300.,400.,500.,600.,700.,800.,900.,1000.,1250.,1500.};
  
  TString OutDir = "plots";
  gSystem->mkdir(OutDir);
  
  TFile *fname_gg2vv;
  TFile *fname_POWHEG;
  TFile *fname_SHERPA;

  fname_gg2vv  = new TFile("gg2vvHw1Sig8TeV/gg2vvHw1Sig8TeV_CommonCut_njet.root");
  fname_POWHEG = new TFile("POWHEG_reweighted_step1/POWHEG_CommonCut_njet.root");

  char tmpName[50];
  char a0Name[50];
  char a1Name[50];
  char histName[50];
  char mWWrange[50];

  //Histograms
  TH1D* h1_gg2vv_mWW[4];
  TH1D* h1_powheg_mWW[4];
  TH1D* h1_gg2vv_mWW_noW[4];
  TH1D* h1_powheg_mWW_noW[4];
  
  TH1D* h1_gg2vv_njet[nbins];
  TH1D* h1_powheg_njet[nbins];
  TH1D* h1_gg2vv_njet_noW[nbins];
  TH1D* h1_powheg_njet_noW[nbins];
  
  TH1D* h1_powheg_gg2vv_njet[nbins];
  
  TH1D* h1_gg2vv_tmp[nbins];
  TH1D* h1_powheg_tmp[nbins];
  TH1D* h1_gg2vv_tmp_noW[nbins];
  TH1D* h1_powheg_tmp_noW[nbins];
  
  double ymax;
  double err_gg2vv;
  double err_powheg;

  for(int i(0);i<nbins;i++)
  {
    sprintf(tmpName,"h1_njet_OffSh_%d",i);
    sprintf(histName,"h1_gg2vv_njet_%d",i);
    h1_gg2vv_njet[i] = (TH1D*)fname_gg2vv->Get(tmpName)->Clone(histName); h1_gg2vv_njet[i]->Sumw2();
    
    sprintf(histName,"h1_powheg_njet_%d",i);
    h1_powheg_njet[i] = (TH1D*)fname_POWHEG->Get(tmpName)->Clone(histName); h1_powheg_njet[i]->Sumw2();
  
    sprintf(tmpName,"h1_njet_OffSh_noWeight_%d",i);
    sprintf(histName,"h1_gg2vv_njet_noW_%d",i);
    h1_gg2vv_njet_noW[i] = (TH1D*)fname_gg2vv->Get(tmpName)->Clone(histName); h1_gg2vv_njet_noW[i]->Sumw2();
    
    sprintf(histName,"h1_powheg_njet_noW_%d",i);
    h1_powheg_njet_noW[i] = (TH1D*)fname_POWHEG->Get(tmpName)->Clone(histName); h1_powheg_njet_noW[i]->Sumw2();
  }

  for(int i(3);i<4;i++)
  {
    sprintf(tmpName,"h1_mWWbin_OffSh_%d",i);
    sprintf(histName,"h1_gg2vv_mWW_%d",i);
    h1_gg2vv_mWW[i] = (TH1D*)fname_gg2vv->Get(tmpName)->Clone(histName); h1_gg2vv_mWW[i]->Sumw2();
    
    sprintf(histName,"h1_powheg_mWW_%d",i);
    h1_powheg_mWW[i] = (TH1D*)fname_POWHEG->Get(tmpName)->Clone(histName); h1_powheg_mWW[i]->Sumw2();
  
    sprintf(tmpName,"h1_mWWbin_OffSh_noWeight_%d",i);
    sprintf(histName,"h1_gg2vv_mWW_noW_%d",i);
    h1_gg2vv_mWW_noW[i] = (TH1D*)fname_gg2vv->Get(tmpName)->Clone(histName); h1_gg2vv_mWW_noW[i]->Sumw2();
    
    sprintf(histName,"h1_powheg_mWW_noW_%d",i);
    h1_powheg_mWW_noW[i] = (TH1D*)fname_POWHEG->Get(tmpName)->Clone(histName); h1_powheg_mWW_noW[i]->Sumw2();
  
    if(i==3)
    {
      for (int j(1);j<=h1_gg2vv_mWW[i]->GetNbinsX();j++)
      {
        h1_gg2vv_njet[j-1]->SetBinContent(i+1,h1_gg2vv_mWW[i]->GetBinContent(j));
        h1_gg2vv_njet_noW[j-1]->SetBinContent(i+1,h1_gg2vv_mWW_noW[i]->GetBinContent(j));
        h1_powheg_njet[j-1]->SetBinContent(i+1,h1_powheg_mWW[i]->GetBinContent(j));
        h1_powheg_njet_noW[j-1]->SetBinContent(i+1,h1_powheg_mWW_noW[i]->GetBinContent(j));
      }
    }

    //for (int j(1);j<=h1_gg2vv_mWW[i]->GetNbinsX();j++)
    //{
    //  //cout<<i<<"-jet: mWW bin_"<<j<<"\t"<<h1_gg2vv_mWW[i]->GetBinContent(j)<<"\t"<<h1_gg2vv_njet[j-1]->GetBinContent(i+1)<<endl;
    //  cout<<i<<"-jet: mWW bin_"<<j<<"\t"<<h1_powheg_mWW[i]->GetBinContent(j)<<"\t"<<h1_powheg_njet[j-1]->GetBinContent(i+1)<<endl;
    //}
  }

  for(int i(0);i<nbins;i++)
  {
    for (int j(1);j<=h1_gg2vv_njet[i]->GetNbinsX();j++)
    {
      err_gg2vv  = 0.;
      err_powheg = 0.;
      if(h1_gg2vv_njet[i]->GetBinContent(j)>0.)
        err_gg2vv  = h1_gg2vv_njet[i]->GetBinContent(j) * sqrt(h1_gg2vv_njet_noW[i]->GetBinContent(j))/h1_gg2vv_njet_noW[i]->GetBinContent(j);
      if(h1_powheg_njet[i]->GetBinContent(j)>0.)
        err_powheg = h1_powheg_njet[i]->GetBinContent(j) * sqrt(h1_powheg_njet_noW[i]->GetBinContent(j))/h1_powheg_njet_noW[i]->GetBinContent(j);
      h1_gg2vv_njet[i]  -> SetBinError(j,err_gg2vv);
      h1_powheg_njet[i] -> SetBinError(j,err_powheg);
    }
    
    //Normalize Histograms
    h1_gg2vv_njet[i]  -> Scale(1./h1_gg2vv_njet[i]->Integral());
    h1_powheg_njet[i] -> Scale(1./h1_powheg_njet[i]->Integral());
    
    //for (int j(1);j<=h1_gg2vv_njet[i]->GetNbinsX();j++)
    //{
    //  cout<<i<<" bin: "<<j<<"\t"<<h1_powheg_njet[i]->GetBinContent(j)<<"\t/\t"<<h1_gg2vv_njet[i]->GetBinContent(j)<<endl;
    //}
    
    sprintf(histName,"h1_powheg_gg2vv_njet_%d",i);
    h1_powheg_gg2vv_njet[i] = (TH1D*)h1_powheg_njet[i]->Clone(histName); //h1_powheg_gg2vv_njet[i]->Sumw2();
    h1_powheg_gg2vv_njet[i]  -> Divide(h1_gg2vv_njet[i]);
  }

  TH1D *h1_powheg_gg2vv = new TH1D("h1_powheg_gg2vv","h1_powheg_gg2vv",nbins,Bins); h1_powheg_gg2vv->Sumw2();
  
  for (int i(0);i<4;i++)
  //for (int i(2);i<3;i++) //njets numbers
  {
    for (int j(1);j<=h1_powheg_gg2vv->GetNbinsX();j++)
    {
      h1_powheg_gg2vv -> SetBinContent(j,h1_powheg_gg2vv_njet[j-1]->GetBinContent(i+1));
      h1_powheg_gg2vv -> SetBinError(j,h1_powheg_gg2vv_njet[j-1]->GetBinError(i+1));
    }

    TString pol1Func("pol1");
    TString pol2Func("pol2");
    
    //TFitResultPtr fitres;  TF1 *fit_func = new TF1("fit_func",pol1Func,0,2000);
    TFitResultPtr fitres;  TF1 *fit_func = new TF1("fit_func",pol2Func,0,2000);
    
    TGraphErrors *grRatio  = 0;
    
    Double_t xval[nbins];
    Double_t xerr[nbins];
    Double_t rMean[nbins];
    Double_t rMeanErr[nbins];
    
    for(Int_t ibin=0; ibin<nbins; ibin++) {
      xval[ibin] = 0.5*(Bins[ibin+1]+Bins[ibin]);
      xerr[ibin] = 0.5*(Bins[ibin+1]-Bins[ibin]);
      
      rMean[ibin]    = h1_powheg_gg2vv->GetBinContent(ibin+1);
      rMeanErr[ibin] = h1_powheg_gg2vv->GetBinError(ibin+1);
    
    }
    
    TCanvas *c = MakeCanvas("c","c",900,900);
    TGraphErrors *errBand = new TGraphErrors(nbins+1);

    char fitparam[100];
    char chi2ndf[50];
    
    grRatio = new TGraphErrors(nbins,xval,rMean,xerr,rMeanErr);
    grRatio->SetName("grRatio");

    //njet=0 set fit function parameter limits
    //fit_func->SetParLimits(0,0.93,0.97);
    //fit_func->SetParLimits(1,-0.00015,-0.000095);

    //njet=1 set fit function parameter limits
    //fit_func->SetParLimits(0,0.,5.);
    //fit_func->SetParLimits(1,-5.0,0.0);
    
    //fit_func->SetRange(300.,1000.);
    //fit_func->SetParameters(0.9582,-0.0001); //njet=0 fix fit function parameters

    fitres = grRatio->Fit("fit_func","QMRN0FBSE");
    //fitres = grRatio->Fit("fit_func","QMRN0SE");
    sprintf(chi2ndf,"#chi^{2}/ndf = %.4f",(fit_func->GetChisquare())/(fit_func->GetNDF()));
    errBand->SetPoint(0,0.002*(xval[nbins-1]),fit_func->Eval(0.002*(xval[nbins-1])));
    //errBand->SetPointError(0,0,dpol1Func(fit_func,0.002*(xval[nbins-1]),fitres));
    errBand->SetPointError(0,0,dpol2Func(fit_func,0.002*(xval[nbins-1]),fitres));
    for(Int_t j=1; j<=nbins; j++) {
      errBand->SetPoint(j,xval[j-1],fit_func->Eval(xval[j-1]));
      //errBand->SetPointError(j,0,dpol1Func(fit_func,xval[j-1],fitres));
      errBand->SetPointError(j,0,dpol2Func(fit_func,xval[j-1],fitres));
    }
    errBand->SetPoint(nbins+1,1.2*(xval[nbins-1]),fit_func->Eval(1.2*(xval[nbins-1])));
    //errBand->SetPointError(nbins+1,0,dpol1Func(fit_func,1.2*(xval[nbins-1]),fitres));
    errBand->SetPointError(nbins+1,0,dpol2Func(fit_func,1.2*(xval[nbins-1]),fitres));

    sprintf(histName,"Fit_%d_jet",i);
    CPlot plotFunc(histName,"","mWW","POWHEG/gg2VV Sig.");
    plotFunc.setOutDir(OutDir);
    //plotFunc.SetXRange(130,1200);
    if(i==0)
      plotFunc.SetYRange(0.7,1.5);
    if(i==1)
      plotFunc.SetYRange(0.6,1.3);
    //if(i==2)
    //  plotFunc.SetYRange(0.5,2.1);
    if(i==3)
      plotFunc.SetYRange(-0.01,4.0);
    plotFunc.AddGraph(grRatio,"");
    plotFunc.AddGraph(errBand,"3",kAzure-9,kFullDotSmall);
    plotFunc.AddGraph(grRatio,"",kBlack,kFullCircle);
    plotFunc.AddFcn(fit_func,kRed);
    
    sprintf(histName,"njet=%d",i);
    if(i==2)
      sprintf(histName,"njet#geq2");
    if(i==3)
      sprintf(histName,"Inclusive jet bins");
    plotFunc.AddTextBox(histName,0.7,0.9,0.8,0.86,0,kBlack,-1);
    plotFunc.AddTextBox(chi2ndf,0.25,0.9,0.45,0.86,0,kBlack,-1);
    sprintf(fitparam,"a = %.4f #pm %.4f",fit_func->GetParameter(0),fit_func->GetParError(0));
    plotFunc.AddTextBox(fitparam,0.25,0.86,0.45,0.82,0,kBlack,-1);
    sprintf(fitparam,"b = %.4f #pm %.4f",fit_func->GetParameter(1),fit_func->GetParError(1));
    plotFunc.AddTextBox(fitparam,0.25,0.82,0.45,0.78,0,kBlack,-1);
    sprintf(fitparam,"c = %.8f #pm %.8f",fit_func->GetParameter(2),fit_func->GetParError(2));
    plotFunc.AddTextBox(fitparam,0.25,0.78,0.45,0.74,0,kBlack,-1);
    
    plotFunc.Draw(c,kTRUE,"png");
  }

}
