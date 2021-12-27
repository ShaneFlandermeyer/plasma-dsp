#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>

#include "matrix2d.h"
#include "vector-utils.h"
namespace plasma {

using namespace Eigen;

// TODO: Create a partial specialization to infer the FFT object template type
template <typename T>
Matrix2D<T> MatchedFilter(Matrix2D<T> &in, std::vector<T> &ref) {
  auto conv_length = in.rows() + ref.size() - 1;
  int num_pulses = in.cols();
  // Zero pad the input matrix and reference vector
  Matrix<T, Dynamic, Dynamic> in_mat =
      Matrix<T, Dynamic, Dynamic>::Zero(conv_length, num_pulses);
  in_mat.topRows(in.rows()) =
      Map<Matrix<T, Dynamic, Dynamic>>(in.data(), in.rows(), num_pulses);
  Matrix<T, Dynamic, 1> ref_vec =
      Map<Matrix<T, Dynamic, 1>>::Zero(conv_length, 1);
  ref_vec.head(ref.size()) =
      Map<Matrix<T, Dynamic, 1>>(ref.data(), ref.size(), 1);
  auto out = Matrix<T, Dynamic, Dynamic>(conv_length, num_pulses);
  // Compute the FFT for each row, multiply by the transformed reference vector,
  // and IFFT back to get the result
  Eigen::FFT<double> fft;
  // Precompute the reference vector FFT since we will use it multiple times
  auto ref_fft = fft.fwd(ref_vec, conv_length);
  for (int i_col = 0; i_col < in.cols(); i_col++) {
    out.col(i_col) =
        ref_fft.array() * fft.fwd(in_mat.col(i_col), conv_length).array();
    out.col(i_col) = fft.inv(out.col(i_col));
  }
  return Matrix2D<T>(out.rows(), out.cols(),
                     std::vector<T>(out.data(), out.data() + out.size()));
}
}  // namespace plasma