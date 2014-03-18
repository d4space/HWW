// =========================================================================
// =========================================================================
// ==  The following settings should only be modified by advanced users:  ==
// =========================================================================
// =========================================================================

// AMPLITUDE ===============================================================

namespace {
  AmpSqrFormcalc _ampSqr(amplitude_selection);
}     // unnamed namespace

AmpSqr& ampSqr = _ampSqr;

// HIGGS PROPAGATOR ========================================================

const bool applyingHiggsBarScheme = true;   // Eqs. (36,37) in arXiv:1112.5517
const bool applyingHiggsFixedWidthBreitWigner = false;

// NARROW WIDTH APPROXIMATION ==============================================

const bool applyingHiggsNWA = false;

const bool applyingNWA = false;   // weak bosons V=W,Z

// STANDARD MODEL PARAMETERS ===============================================

// CKM = 1 (exploited during FormCalc code generation)
const double SMP::CKM_lambda = 0.;
const double SMP::CKM_A = 0.;
const double SMP::CKM_rho_bar = 0.;
const double SMP::CKM_eta_bar = 0.;

/*
// ------------------------------------
// CKM <> 1 requires FormCalc code generation without "CKM = IndexDelta"
// ------------------------------------
// CKM matrix, RPP 2010, Eqs. (11.3), (11.4)
// CKMfitter global fit results as of ICHEP 10
const double SMP::CKM_lambda = 0.22543;
const double SMP::CKM_A = 0.812;
const double SMP::CKM_rho_bar = 0.144;
const double SMP::CKM_eta_bar = 0.342;
*/

// PHASE SPACE  ============================================================

const double compositePhaseSpaceParameter = 4;     // deviation in Higgs widths

const double contSingleResVUpperBound = 2 * SMP::mV;     // mapping NONRESONANTHIGGSBELOW

const bool nonresonantHiggsOnly = ((SMP::mH > 450. && amplitude_selection != AmpSqr::HIGGSSIGNAL && !AmpSqr::includesOnlyBackground(ampSqr.selection())) ? true : false);     // affects phase space mapping

const bool resonantHiggsOnly = false;     // affects phase space mapping

// PARTON DISTRIBUTION FUNCTIONS and ALPHAS ================================

const string Pdf::_pathToLhapdfInputFile = "/afs/cern.ch/work/s/salee/private/HWWwidth/CMSSW_5_3_7/src/HWW/ggVV/Generation/lhapdf-5.9.1/lhapdf-5.9.1-out/share/lhapdf"+ lhapdf_file ;

// LHAPDF Fortran function declaration:
extern "C"
{
const double alphaspdf_(const double *scale);
}

namespace 
{
const double alphasLhapdf(const double scale)
{
  return alphaspdf_(&scale);
}
}     // unnamed namespace

const Alphas alphas = &alphasLhapdf;

// AMPLITUDE COMPARISONS ===================================================

Compare_amplitude_ptr compare_amplitude_ptr = 0;

#include "compare_amplitude.h"
//Compare_amplitude_ptr compare_amplitude_ptr = &compare_amplitude;
