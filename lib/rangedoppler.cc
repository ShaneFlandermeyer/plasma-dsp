#include "rangedoppler.h"

using namespace Eigen;
Matrix<std::complex<double>, Dynamic, Dynamic> MatchedFilter(
    const Matrix<std::complex<double>, Dynamic, Dynamic> &in,
    const Matrix<std::complex<double>, Dynamic, 1> &ref) {
  // TODO: Implement me
  Matrix<std::complex<double>, Dynamic, Dynamic> out(in.rows(), in.cols());
  return out;
}