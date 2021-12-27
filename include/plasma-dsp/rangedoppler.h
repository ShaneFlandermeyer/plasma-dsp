#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>

#include "matrix2d.h"
#include "vector-utils.h"
namespace plasma {
// TODO: Move this somewhere else


/**
 * @brief Compute the matched filter response for a the input matrix
 * 
 * @tparam T The (real-valued) input data type
 * @param in Fast-time slow-time matrix of input data
 * @param ref Matched filter reference waveform
 * @return Matrix2D<T> Matrix where each column is a matched filter response
 */
template <typename T>
Matrix2D<T> MatchedFilter(Matrix2D<T> &in, std::vector<T> &ref) {
  using namespace Eigen;
  auto conv_length = in.rows() + ref.size() - 1;
  int num_pulses = in.cols();
  // Zero pad the input matrix
  Matrix<T, Dynamic, Dynamic> in_mat =
      Matrix<T, Dynamic, Dynamic>::Zero(conv_length, num_pulses);
  in_mat.topRows(in.rows()) =
      Map<Matrix<T, Dynamic, Dynamic>>(in.data(), in.rows(), num_pulses);
  // Zero pad the reference waveform
  Matrix<T, Dynamic, 1> ref_vec =
      Map<Matrix<T, Dynamic, 1>>::Zero(conv_length, 1);
  ref_vec.head(ref.size()) =
      Map<Matrix<T, Dynamic, 1>>(ref.data(), ref.size(), 1);
  auto out = Matrix<T, Dynamic, Dynamic>(conv_length, num_pulses);
  // Compute the FFT for each row, multiply by the transformed reference vector,
  // and IFFT back to get the result
  Eigen::FFT<T> fft;
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

/**
 * @brief Compute the matched filter response for a the input matrix
 * 
 * @tparam T The (complex-valued) input data type
 * @param in Fast-time slow-time matrix of input data
 * @param ref Matched filter reference waveform
 * @return Matrix2D<T> Matrix where each column is a matched filter response
 */
template <typename T>
Matrix2D<std::complex<T>> MatchedFilter(Matrix2D<std::complex<T>> &in,
                                        std::vector<std::complex<T>> &ref) {
  using namespace Eigen;
  auto conv_length = in.rows() + ref.size() - 1;
  int num_pulses = in.cols();
  // Zero pad the input matrix and reference vector
  Matrix<std::complex<T>, Dynamic, Dynamic> in_mat =
      Matrix<std::complex<T>, Dynamic, Dynamic>::Zero(conv_length, num_pulses);
  in_mat.topRows(in.rows()) = Map<Matrix<std::complex<T>, Dynamic, Dynamic>>(
      in.data(), in.rows(), num_pulses);
  Matrix<std::complex<T>, Dynamic, 1> ref_vec =
      Map<Matrix<std::complex<T>, Dynamic, 1>>::Zero(conv_length, 1);
  ref_vec.head(ref.size()) =
      Map<Matrix<std::complex<T>, Dynamic, 1>>(ref.data(), ref.size(), 1);
  auto out = Matrix<std::complex<T>, Dynamic, Dynamic>(conv_length, num_pulses);
  // Compute the FFT for each row, multiply by the transformed reference vector,
  // and IFFT back to get the result
  Eigen::FFT<T> fft;
  // Precompute the reference vector FFT since we will use it multiple times
  auto ref_fft = fft.fwd(ref_vec, conv_length);
  for (int i_col = 0; i_col < in.cols(); i_col++) {
    out.col(i_col) =
        ref_fft.array() * fft.fwd(in_mat.col(i_col), conv_length).array();
    out.col(i_col) = fft.inv(out.col(i_col));
  }
  return Matrix2D<std::complex<T>>(
      out.rows(), out.cols(),
      std::vector<std::complex<T>>(out.data(), out.data() + out.size()));
}
}  // namespace plasma