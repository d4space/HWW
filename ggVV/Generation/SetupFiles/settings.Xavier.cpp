#include <cmath>
using std::log;
using std::sqrt;
#include <cstdlib>
using std::getenv;

#include "settings.h"
#include "phasespace.h"
#include "amp_formcalc.h"
#include "pdf.h"
#include "pi.h"
#include "small_powers.h"
#include "rng.h"
#include "utilities.h"

// Description =============================================================

const string settingsDescription = "LHC Higgs Cross Section WG, arXiv:1101.0593 [hep-ph], App. A, G_\\mu scheme";

// MC INTEGRATION MODE =====================================================

int maxNumberOfGridAdaptationIterations = 5;     // zero: skip grid adaptation
/// Event production mode
const Int64 gridAdaptationNumberOfShots = 50*numberOfEvents;
const Int64 mainRunNumberOfShots = 100*numberOfEvents;
/// Integration mode
/// **************** not implemented yet
long int seedForRandomNumberGenerator = 1;

// EVENT GENERATION MODE ===================================================

const bool generateEvents = true;
const bool unweightEvents = true;
const int numberOfEvents = 25000;

// STANDARD MODEL PARAMETERS ===============================================

// input parameters
const double SMP::gfermi = 1.16637e-5;
const double SMP::mW = 80.398;
const double SMP::mZ = 91.1876;
// derived parameters
const double SMP::sin2w = 1. - pow2(SMP::mW/SMP::mZ);
const double SMP::alpha = sqrt(2.)/Pi*SMP::gfermi*pow2(SMP::mW)*SMP::sin2w;
// W and Z widths
const double SMP::wW = 2.08872;   // NLO
const double SMP::wZ = 2.49595;   // NLO
// unstable lepton masses (for event generation only)
const double SMP::mmuon = 0.1057;
const double SMP::mtau = 1.777;
// massive quark loop amplitude parameters
const double SMP::mt = 172.5;
const double SMP::mb = 4.75;
// Higgs mass and width
const double SMP::mH = 126.;
///const double SMP::wH = SMP::gamma_H_HTO(); /// standard setting 
const double SMP::wH = 25*(SMP::gamma_H_HTO()); /// from H->ZZ setting 
// Higgs rescaling relative to SM couplings 
const double BSM::HggCouplingRescalingFactor = 1.;
///const double BSM::HWWCouplingRescalingFactor = 1.; /// standard setting
const double BSM::HWWCouplingRescalingFactor = sqrt(25.); /// from H->ZZ setting
const double BSM::HZZCouplingRescalingFactor = 1.;

// process dependent vector boson mass and width
#if defined PROCMACRO_WW2l2v
const double SMP::mV = SMP::mW;
const double SMP::wV = SMP::wW;
#endif
#if defined PROCMACRO_ZAZA2l2l
const double SMP::mV = SMP::mZ;
const double SMP::wV = SMP::wZ;
#endif
#if defined PROCMACRO_ZAZ_2l2v
const double SMP::mV = SMP::mZ;
const double SMP::wV = SMP::wZ;
#endif
#if defined PROCMACRO_ZAZA4l
const double SMP::mV = SMP::mZ;
const double SMP::wV = SMP::wZ;
#endif
#if defined PROCMACRO_WWZAZ_2l2v
// not defined because of V=W,Z ambiguity
#endif

// AMPLITUDE ===============================================================

const unsigned int amplitude_selection = (
+AmpSqr::CONTINUUMBACKGROUND
//+AmpSqr::HIGGSSIGNAL
);

// SCALES ==================================================================

vector<Scales*> scales_ptr_vector;

namespace {
FixedScales central_scale_1(SMP::mH/2.);
//FixedScales central_scale_1(SMP::mV);
}     // unnamed namespace

void initialize_scales()
{
  scales_ptr_vector.push_back(&central_scale_1);
}

const int scale_variation_factor = 2;

// SELECTION CUTS ==========================================================

const double minInvMassPhotonProp = 4.;     // GeV

namespace { const MinimalCutsSelection _selection; }
//namespace { const GeneratorCutsSelection _selection; }
//namespace { const StandardCutsSelection _selection; }
//namespace { const HiggsSearchSelection _selection; }

const Selection& selection = _selection;

// COLLIDER ================================================================

//ConstValue<double> PhaseSpace::E_CMS = 7.e3;     // GeV
ConstValue<double> PhaseSpace::E_CMS = 8.e3;     // GeV
//ConstValue<double> PhaseSpace::E_CMS = 13.e3;     // GeV
//ConstValue<double> PhaseSpace::E_CMS = 14.e3;     // GeV

// PARTON DISTRIBUTION FUNCTIONS and ALPHAS ================================

// select PDF set:
const string lhapdf_file = "cteq6l.LHpdf";
//const string lhapdf_file = "MSTW2008nnlo68cl.LHgrid";
//const string lhapdf_file = "CT10nnlo.LHgrid";    // LHAPDF >= v5.8.8
//const string lhapdf_file = "NNPDF21_nnlo_100.LHgrid";

// calculate PDF error (if supported by PDF set):
const bool requestPDFError = false;

// using set's default alpha_s (LHAPDF)

// =========================================================================

// Some settings should only be modified by advanced users:
#include "advanced_settings.inc"
