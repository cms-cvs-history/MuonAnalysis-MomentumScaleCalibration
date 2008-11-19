/**
 * MomentumScaleCorrector class
 * Author M. De Mattia - 18/11/2008
 */

#ifndef MomentumScaleCorrector_h
#define MomentumScaleCorrector_h

#include "MuonAnalysis/MomentumScaleCalibration/plugins/Functions.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include <fstream>

/**
 * This is used to have a common set of functions for the specialized templates to use.
 * It has a protected constructor, so it cannot be used directly.
 */
//template <class T>
class MomentumScaleCorrectorBase
{
 public:
  /// Method to do the corrections. It is templated to work with all the track types.
  template <class U>
  double operator()( const U & track ) {
    // return ( scaleFunction_->scale( track.pt(), track.eta(), track.phi(), track.charge(), parScale_) );
    return ( scaleFunction_->scale( track.pt(), track.eta(), track.phi(), track.charge(), parScaleArray_) );
  }
 protected:
  MomentumScaleCorrectorBase() {};
  ~MomentumScaleCorrectorBase() {
    if( parScaleArray_ != 0 ) {
      delete[] parScaleArray_;
    }
  };
  /// Parser of the parameters file
  //pair<vector<double>, vector<double> > readParameters( TString fileName );
  void readParameters( TString fileName );
  // scaleFunctionBase<vector<double> > * scaleFunction_;
  scaleFunctionBase<double * > * scaleFunction_;
  vector<double> parScale_;
  // We will use the array for the function calls because it is faster than the vector for random access.
  double * parScaleArray_;
};

//template <class T>
// pair<vector<double>, vector<double> >
//MomentumScaleCorrectorBase<T>::readParameters( TString fileName )
void MomentumScaleCorrectorBase::readParameters( TString fileName )
{
  parScaleArray_ = 0;
  // vector<double> parameterErrors;

  // Read the parameters file
  ifstream parametersFile(fileName.Data());
  string line;

  string iteration("Iteration ");
  // Loop on the file lines
  while (parametersFile) {
    getline( parametersFile, line );
    unsigned int lineInt = line.find("value");

    // if( line.find(iteration) != string::npos ) {
    unsigned int iterationSubStr = line.find(iteration);

    // Take the iteration number
    if( iterationSubStr != string::npos ) {

      int scaleFunctionNum = 0;
      // This can be used when dealing with multiple iterations
      int iterationNum = 0;

      // cout << "line = " << line << endl;
      stringstream sLine(line);
      string num;
      int wordCounter = 0;
      // Warning: this strongly depends on the parameters file structure.
      while( sLine >> num ) {
        ++wordCounter;
        //         cout << "num["<<wordCounter<<"] = " << num << endl;
        if( wordCounter == 9 ) {
          stringstream in(num);
          in >> scaleFunctionNum;
        }
        if( wordCounter == 13 ) {
          stringstream in(num);
          in >> iterationNum;
        }
      }
      // cout << "iteration number = " << iterationNum << endl;
      // cout << "scale function number = " << scaleFunctionNum << endl;

      // Set the scaleFunction
      // scaleFunction_ = scaleFunctionArrayForVec[scaleFunctionNum];
      scaleFunction_ = scaleFunctionArray[scaleFunctionNum];
    }
    // Take the parameters for the current iteration
    if ( (lineInt != string::npos) ) {
      int subStr1 = line.find("value");
      stringstream paramStr;
      double param = 0;
      // Even if all the rest of the line is taken, the following
      // convertion to a double will stop at the end of the first number.
      paramStr << line.substr(subStr1+5);
      paramStr >> param;
      parScale_.push_back(param);
      // cout << "param = " << param << endl;

      // This is to extract parameter errors
      // int subStr2 = line.find("+-");
      // stringstream parErrorStr;
      // double parError = 0;
      // parErrorStr << line.substr(subStr2+1);
      // parErrorStr >> parError;
      // parameterErrors.push_back(parError);
      // cout << "parError = " << parError << endl;
    }
  }
  parScaleArray_ = new double[parScale_.size()];
  vector<double>::const_iterator par = parScale_.begin();
  int parNum = 0;
  for ( ; par != parScale_.end(); ++par, ++parNum ) {
    parScaleArray_[parNum] = *par;
  }
  // return make_pair(parameters, parameterErrors);
}

/**
 * Momentum correction class </br>
 * The constructor receives the name identifying the parameters for the correction function.
 * It reads the parameters from a txt file in data/. Being a template,
 * the type of the template parameter selects also the parameters to be read.
 * This is achieved by template specialization.
 * The generic template class is used for globalMuons.
 */
template <class T>
class MomentumScaleCorrector : public
// MomentumScaleCorrectorBase<T>
MomentumScaleCorrectorBase
{
 public:
  /**
   * The constructor takes a string identifying the parameters to read. It
   * parses the txt file containing the parameters, extracts the index of the
   * correction function and saves the corresponding pointer. It then fills the
   * vector of parameters.
   */
  MomentumScaleCorrector( TString identifier )
  {
    identifier.Prepend("MuonAnalysis/MomentumScaleCalibration/data/");
    identifier.Append("_globalMuons.txt");
    edm::FileInPath fileWithFullPath(identifier.Data());
    // This used because it is a template
    // Alternatively it is also ok to do: MomentumScaleCorrectorBase<T>::readParameters( fileWithFullPath.fullPath() );
    // pair<vector<double>, vector<double> > parameters( this->readParameters( fileWithFullPath.fullPath() ) );
    this->readParameters( fileWithFullPath.fullPath() );
  }
  ~MomentumScaleCorrector() {}
};

/// Specialization used for tracker only tracks
template <>
class MomentumScaleCorrector<reco::Track> : public
//MomentumScaleCorrectorBase<reco::Track>
MomentumScaleCorrectorBase
{
  MomentumScaleCorrector( TString identifier )
  {
    identifier.Prepend("MuonAnalysis/MomentumScaleCalibration/data/");
    identifier.Append("_trackerTracks.txt");
    edm::FileInPath fileWithFullPath(identifier.Data());
    // This used because it is a template
    // Alternatively it is also ok to do: MomentumScaleCorrectorBase<T>::readParameters( fileWithFullPath.fullPath() );
    // pair<vector<double>, vector<double> > parameters( this->readParameters( fileWithFullPath.fullPath() ) );
    this->readParameters( fileWithFullPath.fullPath() );
  }
};
/// Specialization used for standAlone muons

#endif // MomentumScaleCorrector_h