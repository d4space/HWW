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

Double_t ExpFunc(double *x, double *par)
{
  Double_t a  = par[0];
  Double_t b  = par[1];
  Double_t c  = par[2];

  return a + b*TMath::Exp(c*x[0]);
  //return a*TMath::Exp(-x[0]/b) + c;
}

Double_t df_dParExp(Double_t *x, Double_t *p) {
  TF1 *fitFunc = new TF1("ExpFunc",ExpFunc,0,1500,3);
  fitFunc->SetParameters(p[1],p[2],p[3]);
  Double_t grad[3];
  int ipar = int(p[0]);
  assert (ipar >=0 && ipar < 3 );

  assert(fitFunc);
  fitFunc->GradientPar(x, grad);
  return grad[ipar];
}

Double_t dExpFunc(const TF1 *fcn, const Double_t x, const TFitResultPtr fs) {
  Double_t df[3];
  Double_t a = fcn->GetParameter(0);
  Double_t b = fcn->GetParameter(1);
  Double_t c = fcn->GetParameter(2);

  TF1 *deriv_par0 = new TF1("dfdp0",df_dParExp,130,1500,4);
  deriv_par0->SetParameters(0,a,b,c); // This will set the derivative for the first parameter.
  TF1 *deriv_par1 = new TF1("dfdp1",df_dParExp,130,1500,4);
  deriv_par1->SetParameters(1,a,b,c); // This will set the derivative for the second parameter
  TF1 *deriv_par2 = new TF1("dfdp2",df_dParExp,130,1500,4);
  deriv_par2->SetParameters(2,a,b,c); // This will set the derivative for the 3rd parameter
  df[0] = deriv_par0->Eval(x);
  df[1] = deriv_par1->Eval(x);
  df[2] = deriv_par2->Eval(x);
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

Double_t OneoverXFunc(double *x, double *par)
{
  Double_t a  = par[0];
  Double_t b  = par[1];

  return a + b/x[0];
}

Double_t df_dParOneoverX(Double_t *x, Double_t *p) {
  TF1 *fitFunc = new TF1("OneoverXFunc",OneoverXFunc,130,1620,3);
  fitFunc->SetParameters(p[1],p[2]);
  Double_t grad[2];
  int ipar = int(p[0]);
  assert (ipar >=0 && ipar < 2 );

  assert(fitFunc);
  fitFunc->GradientPar(x, grad);
  return grad[ipar];
}

Double_t dOneoverXFunc(const TF1 *fcn, const Double_t x, const TFitResultPtr fs) {
  Double_t df[2];
  Double_t a = fcn->GetParameter(0);
  Double_t b = fcn->GetParameter(1);

  TF1 *deriv_par0 = new TF1("dfdp0",df_dParOneoverX,130,1620,3);
  deriv_par0->SetParameters(0,a,b); // This will set the derivative for the first parameter.
  TF1 *deriv_par1 = new TF1("dfdp1",df_dParOneoverX,130,1620,3);
  deriv_par1->SetParameters(1,a,b); // This will set the derivative for the second parameter
  df[0] = deriv_par0->Eval(x);
  df[1] = deriv_par1->Eval(x);
  Double_t err2 = df[0]*df[0]*(fs->GetCovarianceMatrix()[0][0])
                  + df[1]*df[1]*(fs->GetCovarianceMatrix()[1][1])
		  + 2.0*df[0]*df[1]*(fs->GetCovarianceMatrix()[0][1]);
  assert(err2>=0);
  return sqrt(err2);
}

Double_t OneoversqrtXFunc(double *x, double *par)
{
  Double_t a  = par[0];
  Double_t b  = par[1];

  return a + b/sqrt(x[0]);
}

Double_t df_dParOneoversqrtX(Double_t *x, Double_t *p) {
  TF1 *fitFunc = new TF1("OneoversqrtXFunc",OneoversqrtXFunc,130,1620,3);
  fitFunc->SetParameters(p[1],p[2]);
  Double_t grad[2];
  int ipar = int(p[0]);
  assert (ipar >=0 && ipar < 2 );

  assert(fitFunc);
  fitFunc->GradientPar(x, grad);
  return grad[ipar];
}

Double_t dOneoversqrtXFunc(const TF1 *fcn, const Double_t x, const TFitResultPtr fs) {
  Double_t df[2];
  Double_t a = fcn->GetParameter(0);
  Double_t b = fcn->GetParameter(1);

  TF1 *deriv_par0 = new TF1("dfdp0",df_dParOneoversqrtX,130,1620,3);
  deriv_par0->SetParameters(0,a,b); // This will set the derivative for the first parameter.
  TF1 *deriv_par1 = new TF1("dfdp1",df_dParOneoversqrtX,130,1620,3);
  deriv_par1->SetParameters(1,a,b); // This will set the derivative for the second parameter
  df[0] = deriv_par0->Eval(x);
  df[1] = deriv_par1->Eval(x);
  Double_t err2 = df[0]*df[0]*(fs->GetCovarianceMatrix()[0][0])
                  + df[1]*df[1]*(fs->GetCovarianceMatrix()[1][1])
		  + 2.0*df[0]*df[1]*(fs->GetCovarianceMatrix()[0][1]);
  assert(err2>=0);
  return sqrt(err2);
}

Double_t sqrtFunc(double *x, double *par)
{
  Double_t a  = par[0];
  Double_t b  = par[1];

  return a + b*sqrt(x[0]);
}

Double_t df_dParsqrt(Double_t *x, Double_t *p) {
  TF1 *fitFunc = new TF1("sqrtFunc",sqrtFunc,130,1620,3);
  fitFunc->SetParameters(p[1],p[2]);
  Double_t grad[2];
  int ipar = int(p[0]);
  assert (ipar >=0 && ipar < 2 );

  assert(fitFunc);
  fitFunc->GradientPar(x, grad);
  return grad[ipar];
}

Double_t dsqrtFunc(const TF1 *fcn, const Double_t x, const TFitResultPtr fs) {
  Double_t df[2];
  Double_t a = fcn->GetParameter(0);
  Double_t b = fcn->GetParameter(1);

  TF1 *deriv_par0 = new TF1("dfdp0",df_dParsqrt,130,1620,3);
  deriv_par0->SetParameters(0,a,b); // This will set the derivative for the first parameter.
  TF1 *deriv_par1 = new TF1("dfdp1",df_dParsqrt,130,1620,3);
  deriv_par1->SetParameters(1,a,b); // This will set the derivative for the second parameter
  df[0] = deriv_par0->Eval(x);
  df[1] = deriv_par1->Eval(x);
  Double_t err2 = df[0]*df[0]*(fs->GetCovarianceMatrix()[0][0])
                  + df[1]*df[1]*(fs->GetCovarianceMatrix()[1][1])
		  + 2.0*df[0]*df[1]*(fs->GetCovarianceMatrix()[0][1]);
  assert(err2>=0);
  return sqrt(err2);
}

void ratiofit_vbf()
{
  const Int_t nbins = 11;
  double Bins[12] = {130.,200.,300.,400.,500.,600.,700.,800.,900.,1000.,1250.,1500.};
  
  TString OutDir = "vbf_plots_pol1Func";
  //TString OutDir = "vbf_plots_OneoversqrtXFunc";
  //TString OutDir = "vbf_plots_OneoverXFunc";
  
  gSystem->mkdir(OutDir);
  
  TFile *fname;

  fname = new TFile("mWW_sf_reweighted/scaleFactors.root");

  char tmpName[50];
  char a0Name[50];
  char a1Name[50];
  char histName[50];
  char mWWrange[50];

  //Histograms
  TH1D* h1_powheg_phantom[5];

  TString pol1Func("pol1");
  //TString pol2Func("pol2");
  //TString ExpFunc("ExpFunc");
  //TString sqrtFunc("sqrtFunc");
  //TString OneoverXFunc("OneoverXFunc");
  //TString OneoversqrtXFunc("OneoversqrtXFunc");
  
  TFitResultPtr fitres;
  TF1 *fit_func = new TF1("fit_func",pol1Func,130,1620);
  //TFitResultPtr fitres;  TF1 *fit_func = new TF1("fit_func",pol2Func,0,1500);
  //TFitResultPtr fitres;  TF1 *fit_func = new TF1("fit_func",ExpFunc,130,1500,3);
  //TFitResultPtr fitres;  TF1 *fit_func = new TF1("fit_func",sqrtFunc,130,1500,3);
  //TF1 *fit_func = new TF1("fit_func",OneoverXFunc,130,1620,2);
  //TF1 *fit_func = new TF1("fit_func",OneoversqrtXFunc,130,1620,2);
  
  TGraphErrors *grRatio  = 0;
  
  Double_t xval[nbins];
  Double_t xerr[nbins];
  Double_t rMean[nbins];
  Double_t rMeanErr[nbins];
    
  TCanvas *c = MakeCanvas("c","c",900,900);
  TGraphErrors *errBand = new TGraphErrors(nbins+2);

  char fitparam[100];
  char chi2ndf[50];
    
  for(int i(0);i<5;i++)
  {
    sprintf(tmpName,"h1_powheg_phantom_%d",i);
    h1_powheg_phantom[i] = (TH1D*)fname->Get(tmpName)->Clone(tmpName);// h1_powheg_phantom[i]->Sumw2();

    for(Int_t ibin=0; ibin<nbins; ibin++) {
      xval[ibin] = 0.5*(Bins[ibin+1]+Bins[ibin]);
      xerr[ibin] = 0.5*(Bins[ibin+1]-Bins[ibin]);
      
      rMean[ibin]    = h1_powheg_phantom[i]->GetBinContent(ibin+1);
      rMeanErr[ibin] = h1_powheg_phantom[i]->GetBinError(ibin+1);
    
    }
    
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

    //fit_func->SetParameter(0,0.95);
    //fit_func->SetParameter(1,1.52);
    //fit_func->SetParameter(2,-0.0041);
    //fit_func->FixParameter(0,0);
    //fit_func->SetParameter(0,1);
    //fit_func->SetParameter(1,-30);
    //fit_func->SetParameter(2,-0.00001);
    //fit_func->FixParameter(2,-0.00425127);
    
    //fit_func->SetParLimits(1,0.0,0.0);
    //fit_func->FixParameter(1,0);
    if(i==1)
    {
      //fit_func->SetParameter(0,1.1);
      //fit_func->SetParameter(1,0.0);
    }
    if(i==2)
    {
      fit_func->SetParameter(0,0.9);
      fit_func->SetParameter(1,0.00001);
    }
    
    if(i==3)
    {
      //fit_func->SetParLimits(1,-0.00015,-0.000095);
      fit_func->SetParameter(0,0.4);
      fit_func->SetParameter(1,0.000001);
    }
    fitres = grRatio->Fit("fit_func","QMRN0FBSE");
    //fitres = grRatio->Fit("fit_func","QMRN0SE");
    sprintf(chi2ndf,"#chi^{2}/ndf = %.4f",(fit_func->GetChisquare())/(fit_func->GetNDF()));
    //errBand->SetPoint(0,0.002*(xval[nbins-1]),fit_func->Eval(0.002*(xval[nbins-1])));
    errBand->SetPoint(0,0,130);
    errBand->SetPointError(0,0,dpol1Func(fit_func,0.002*(xval[nbins-1]),fitres));
    //errBand->SetPointError(0,0,dpol2Func(fit_func,0.002*(xval[nbins-1]),fitres));
    //errBand->SetPointError(0,0,dExpFunc(fit_func,0.002*(xval[nbins-1]),fitres));
    //errBand->SetPointError(0,0,dsqrtFunc(fit_func,0.002*(xval[nbins-1]),fitres));
    //errBand->SetPointError(0,0,dOneoverXFunc(fit_func,0.002*(xval[nbins-1]),fitres));
    //errBand->SetPointError(0,0,dOneoversqrtXFunc(fit_func,0.002*(xval[nbins-1]),fitres));
    //cout <<"0\t" << 0.002*(xval[nbins-1])<<"\t"<<fit_func->Eval(0.002*(xval[nbins-1]))<<"\t"<<dOneoversqrtXFunc(fit_func,0.002*(xval[nbins-1]),fitres)<<endl; 
    errBand->SetPoint(1,130,fit_func->Eval(130));
    //errBand->SetPointError(1,0,dOneoverXFunc(fit_func,130,fitres));
    //errBand->SetPointError(1,0,dOneoversqrtXFunc(fit_func,130,fitres));
    errBand->SetPointError(1,0,dpol1Func(fit_func,130,fitres));
    for(Int_t j=2; j<=nbins; j++) {
      errBand->SetPoint(j,xval[j-1],fit_func->Eval(xval[j-1]));
      //errBand->SetPointError(j,0,dExpFunc(fit_func,xval[j-1],fitres));
      //errBand->SetPointError(j,0,dsqrtFunc(fit_func,xval[j-1],fitres));
      //errBand->SetPointError(j,0,dOneoverXFunc(fit_func,xval[j-1],fitres));
      //errBand->SetPointError(j,0,dOneoversqrtXFunc(fit_func,xval[j-1],fitres));
      errBand->SetPointError(j,0,dpol1Func(fit_func,xval[j-1],fitres));
      //cout <<j<<"\t"<<xval[j-1]<<"\t"<<fit_func->Eval(xval[j-1])<<"\t"<<dOneoversqrtXFunc(fit_func,xval[j-1],fitres)<<endl;
    }
    errBand->SetPoint(nbins+1,1.2*(xval[nbins-1]),fit_func->Eval(1.2*(xval[nbins-1])));
    errBand->SetPointError(nbins+1,0,dpol1Func(fit_func,1.2*(xval[nbins-1]),fitres));
    //errBand->SetPointError(nbins+1,0,dpol2Func(fit_func,1.2*(xval[nbins-1]),fitres));
    //errBand->SetPointError(nbins+1,0,dExpFunc(fit_func,1.2*(xval[nbins-1]),fitres));
    //errBand->SetPointError(nbins+1,0,dsqrtFunc(fit_func,1.2*(xval[nbins-1]),fitres));
    //errBand->SetPointError(nbins+1,0,dOneoverXFunc(fit_func,1.2*(xval[nbins-1]),fitres));
    //errBand->SetPointError(nbins+1,0,dOneoversqrtXFunc(fit_func,1.2*(xval[nbins-1]),fitres));

    sprintf(histName,"Fit_%d_jet",i);
    CPlot plotFunc(histName,"","mWW","POWHEG/Phantom");
    plotFunc.setOutDir(OutDir);
    if(i>6)
    {
      plotFunc.AddGraph(grRatio,"");
      plotFunc.AddGraph(errBand,"3",kAzure-9,kFullDotSmall);
    }
    plotFunc.AddGraph(grRatio,"",kBlack,kFullCircle);
    if(i>6)
      plotFunc.AddFcn(fit_func,kRed);
    
    sprintf(histName,"njet=%d",i);
    if(i==3)
      sprintf(histName,"njet#geq3");
    if(i==4)
      sprintf(histName,"Inclusive jet bins");
    
    plotFunc.AddTextBox(histName,0.68,0.9,0.88,0.86,0,kBlack,-1);
    if(i>6)
    {
      plotFunc.AddTextBox(chi2ndf,0.25,0.9,0.45,0.86,0,kBlack,-1);
      sprintf(fitparam,"a = %.4f #pm %.4f",fit_func->GetParameter(0),fit_func->GetParError(0));
      plotFunc.AddTextBox(fitparam,0.25,0.86,0.45,0.82,0,kBlack,-1);
      sprintf(fitparam,"b = %.6f #pm %.6f",fit_func->GetParameter(1),fit_func->GetParError(1));
      plotFunc.AddTextBox(fitparam,0.25,0.82,0.5,0.78,0,kBlack,-1);
    }
    //sprintf(fitparam,"c = %.8f #pm %.8f",fit_func->GetParameter(2),fit_func->GetParError(2));
    //plotFunc.AddTextBox(fitparam,0.25,0.78,0.45,0.74,0,kBlack,-1);
    if(i==0)
    {
    //  plotFunc.SetYRange(0.5,4.0);
      //plotFunc.AddLine(0,1.52049,1640,1.52049,kBlack,2);
    }
    if(i==1)
    {
      //plotFunc.SetYRange(0.8,1.5);
      //plotFunc.AddLine(0,0.97262,1640,0.97262,kBlack,2);
    }
    if(i==2)
    {
      //plotFunc.SetYRange(0.8,1.2);
      plotFunc.AddLine(0,0.993992,1640,0.993992,kBlack,2);
    }
    if(i==3)
    {
      //plotFunc.SetYRange(0.0,1.3);
      plotFunc.AddLine(0,0.720189,1640,0.720189,kBlack,2);
    }
    
    plotFunc.Draw(c,kTRUE,"png");
  }

}
