#include <Eigen/Dense>

#include "vector-utils.h"
namespace plasma {

using namespace Eigen;
// TODO: These functions currently only work with eigen matrices.
Matrix<std::complex<double>, Dynamic, Dynamic> MatchedFilter(
    const Matrix<std::complex<double>, Dynamic, Dynamic> &in,
    const Matrix<std::complex<double>, Dynamic, 1> &ref);

// plasma::Matrix<std::complex<double>> RangeDopplerMap(
//     const Matrix<std::complex<double>> &data);

}  // namespace plasma