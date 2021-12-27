#include <Eigen/Dense>

#include "matrix2d.h"
#include "vector-utils.h"
namespace plasma {

using namespace Eigen;

template <typename T>
Matrix2D<T> MatchedFilter(Matrix2D<T> &in, std::vector<T> &ref) {
  // TODO: Implement me
  auto conv_length = in.rows() + ref.size() - 1;

  Matrix<T, Dynamic, Dynamic> out =
      Map<Matrix<T, Dynamic, Dynamic>>(in.data(), conv_length, in.cols());

  std::cout << out << std::endl;
  return in;
}
}  // namespace plasma