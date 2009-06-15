#ifndef MuScleFitUtils_H
#define MuScleFitUtils_H

/** \class DTHitQualityUtils
 *  
 *  Provide basic functionalities useful for MuScleFit
 *
 *  $Date: 2009/05/27 14:35:42 $
 *  $Revision: 1.5 $
 *  \author S. Bolognesi - INFN Torino / T. Dorigo - INFN Padova
 */

#include <CLHEP/Vector/LorentzVector.h>
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
// #include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"
#include <DataFormats/FWLite/interface/Handle.h>
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TGraphErrors.h"
#include "TH2F.h"

#include <vector>

using namespace std;

// #include "Functions.h"
// class biasFunctionBase<vector<double> >;
// class scaleFunctionBase<double*>;
template <class T> class biasFunctionBase;
template <class T> class scaleFunctionBase;
class smearFunctionBase;
template <class T> class resolutionFunctionBase;
class backgroundFunctionBase;

class SimTrack; 
class TString;
class TTree;

typedef reco::Particle::LorentzVector lorentzVector;

class MuScleFitUtils {
public:
  
  // Constructor
  // ----------
  MuScleFitUtils() {};

  // Destructor
  // ----------
  virtual ~MuScleFitUtils() {};

  // Operations
  // ----------
  static std::pair<SimTrack, SimTrack> findBestSimuRes( const std::vector<SimTrack>& simMuons );
  static std::pair<lorentzVector, lorentzVector> findBestRecoRes( const std::vector<reco::LeafCandidate>& muons );
  static std::pair<lorentzVector, lorentzVector> findGenMuFromRes( const edm::Handle<edm::HepMCProduct> & evtMC );
  static std::pair<lorentzVector, lorentzVector> findSimMuFromRes( const edm::Handle<edm::HepMCProduct> & evtMC,
								   const edm::Handle<edm::SimTrackContainer> & simTracks);

  static std::vector<TGraphErrors*> fitMass (TH2F* histo);
  static std::vector<TGraphErrors*> fitReso (TH2F* histo);

  static void cleanEstimator();
  static void computeEstimator( const lorentzVector & recMu1, const lorentzVector & recMu2, const double & Zmass );
  static void computeEstimator( const lorentzVector & recMu, const double & Zmass );
  static void returnEstimator();

  static lorentzVector applyScale( const lorentzVector & muon, const std::vector<double> & parval, const int charge );
  static lorentzVector applyScale( const lorentzVector & muon, double* parval, const int charge );
  static lorentzVector applyBias( const lorentzVector & muon, const int charge );
  static lorentzVector applySmearing( const lorentzVector & muon );
  static lorentzVector fromPtEtaPhiToPxPyPz( const double* ptEtaPhiE );

  static void minimizeLikelihood();

  static double invDimuonMass( const lorentzVector & mu1, const lorentzVector & mu2 );
  static double massResolution( const lorentzVector & mu1, const lorentzVector & mu2 );
  static double massResolution( const lorentzVector & mu1, const lorentzVector & mu2, const std::vector<double> & parval );
  static double massResolution( const lorentzVector & mu1, const lorentzVector & mu2, std::auto_ptr<double> parval );
  static double massResolution( const lorentzVector & mu1, const lorentzVector & mu2, double* parval );

  static double massProb( const double & mass, const double & rapidity, const int ires, const double & massResol );
  static double massProb( const double & mass, const double & rapidity, const double & massResol, const std::vector<double> & parval );
  // static double massProb( const double & mass, const double & rapidity, const double & massResol, std::auto_ptr<double> parval );
  static double massProb( const double & mass, const double & rapidity, const double & massResol, double * parval );
  static double massProb2( const double & mass, const int ires, const double & massResol ); // Not used yet
  static double computeWeight( const double & mass );

  static double deltaPhi( const double & phi1, const double & phi2 )
  {
    double deltaPhi = phi1 - phi2;
    while(deltaPhi >= TMath::Pi()) deltaPhi -= 2*TMath::Pi();
    while(deltaPhi < -TMath::Pi()) deltaPhi += 2*TMath::Pi();
    return fabs(deltaPhi);
  }
  /// Without fabs at the end, used to have a symmetric distribution for the resolution fits and variance computations
  static double deltaPhiNoFabs( const double & phi1, const double & phi2 )
  {
    double deltaPhi = phi1 - phi2;
    while(deltaPhi >= TMath::Pi()) deltaPhi -= 2*TMath::Pi();
    while(deltaPhi < -TMath::Pi()) deltaPhi += 2*TMath::Pi();
    return deltaPhi;
  }
  static double deltaR(const double & eta1, const double & eta2, const double & phi1, const double & phi2)
  {
    return sqrt( pow( eta1-eta2, 2 ) + pow( deltaPhi(phi1, phi2), 2 ) );
  }

  static int debug;       // debug option set by MuScleFit
  static bool ResFound;   // bool flag true if best resonance found (cuts on pt and eta)

  static double massWindowHalfWidth[6][3]; // parameter set by MuScleFitUtils
  static double ResGamma[6];     // parameter set by MuScleFitUtils
  static double ResMass[6];      // parameter set by MuScleFitUtils
  static const double mMu2;
  static const double muMass;

  // Array of the pdgId of resonances
  static const unsigned int motherPdgIdArray[6];

  static unsigned int loopCounter; // parameter set by MuScleFit

  static int SmearType;
  static smearFunctionBase * smearFunction;
  static int BiasType;
  // No error, we take functions from the same group for scale and bias.
  static scaleFunctionBase<vector<double> > * biasFunction;
  static int ResolFitType;
  static resolutionFunctionBase<double *> * resolutionFunction;
  static resolutionFunctionBase<vector<double> > * resolutionFunctionForVec;
  static int ScaleFitType;
  static scaleFunctionBase<double*> * scaleFunction;
  static scaleFunctionBase<vector<double> > * scaleFunctionForVec;
  static int BgrFitType;
  static backgroundFunctionBase * backgroundFunction;

  // Parameters used to select whether to do a fit
  static std::vector<int> doResolFit;
  static std::vector<int> doScaleFit;
  static std::vector<int> doBackgroundFit;

  static int minuitLoop_;
  static TH1F* likelihoodInLoop_;

  static std::vector<double> parSmear;
  static std::vector<double> parBias;
  static std::vector<double> parResol;
  static std::vector<double> parScale;
  static std::vector<double> parBgr;
  static std::vector<int> parResolFix;
  static std::vector<int> parScaleFix;
  static std::vector<int> parBgrFix;
  static std::vector<int> parResolOrder;
  static std::vector<int> parScaleOrder;
  static std::vector<int> parBgrOrder;
  static std::vector<int> resfind;
  static int FitStrategy;
  static bool speedup;       // parameter set by MuScleFit - whether to speedup processing
  static double x[7][10000]; // smearing values set by MuScleFit constructor
  static int goodmuon;       // number of events with a usable resonance
  static int counter_resprob;// number of times there are resolution problems
  static double GLZValue[40][1001][1001]; // matrix with integral values of Lorentz * Gaussian 
  static double GLZNorm[40][1001];        // normalization values per each sigma
  static double GLValue[6][1001][1001]; // matrix with integral values of Lorentz * Gaussian 
  static double GLNorm[6][1001];        // normalization values per each sigma
  static double ResMaxSigma[6];         // max sigma of matrix
  static double ResHalfWidth[6];        // halfwidth in matrix
  static int nbins;                     // number of bins in matrix
  static int MuonType; // 0, 1, 2 - 0 is GM, 1 is SM, 2 is track

  static std::vector<std::vector<double> > parvalue;
  // static std::map<unsigned int,std::vector<double> > parvalue;
  static std::vector<int> parfix;
  static std::vector<int> parorder;
  
  static std::vector<std::pair<lorentzVector,lorentzVector> > SavedPair;

  // Defined to allow asymmetric mass windows.
  static double leftWindowFactor;
  static double rightWindowFactor;

  // This must be set to true if using events generated with Sherpa
  static bool sherpa_;

protected:

  /// Method to check if the mass value is within the mass window of the i-th resonance.
  static bool checkMassWindow( const double & mass, const int ires );
  /// Computes the probability given the mass, mass resolution and the arrays with the probabilities and the normalizations.
  static double probability( const double & mass, const double & massResol,
                             const double GLvalue[][1001][1001], const double GLnorm[][1001],
                             const int iRes, const int iY );

private:
  
   struct byPt {
     bool operator() (const reco::Muon &a, const reco::Muon &b) const { 
       return a.pt() > b.pt();
     }
   };

};

extern "C" void likelihood (int& npar, double* grad, double& fval, double* xval, int flag);

#endif