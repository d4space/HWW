#define PI  3.14159265358979323846
#define LumiTotal8TeV 19.468 // fb^-1
#define nMllBin 11
namespace GenType
{
  enum{
    kElectron   = 11,
    keNeutrino  = 12,
    kMuon       = 13, //Muon (-)
    kmuNeutrino = 14,
    kTau        = 15, //Tau (-)
    ktauNeutrino = 16,
    kTauElectron= 150011,
    kTauMuon    = 150013,
    kGluon	= 21,
    kGamma	= 22,
    kZ          = 23,
    kW          = 24,
    kHiggs      = 25,
    kWW         = 24024,
    kVZ         = 26023,
    kZgamma     = 23022,
    kWgamma     = 24022
  };
  double M_ele	= 0.000511;
  double M_mu	= 0.1057;
  double M_tau	= 1.7768;
  double M_W	= 80.385;
  double M_Z	= 91.1876;
}
