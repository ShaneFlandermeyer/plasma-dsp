#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>

#include "circ_shift.h"
#include "matrix2d.h"
#include "vector-utils.h"
#include "signal-processing.h"
namespace plasma {

/**
 * @brief Compute the matched filter response for a the input vector
 *
 * This is just a convolution, but it's included to have a consistent interface
 *
 * @tparam T The (real-valued) input precision
 * @param in Input data vector
 * @param ref Matched filter reference waveform
 * @return std::vector<std::complex<T>> Matched filter response
 */
template <typename T>
std::vector<std::complex<T>> MatchedFilterResponse(std::vector<std::complex<T>> &in,
                                           std::vector<std::complex<T>> &ref) {
  return conv(in, ref);
}

/**
 * @brief Compute the matched filter response for a the input matrix
 *
 * @tparam T The (real-valued) input precision
 * @param in Fast-time slow-time matrix of input data
 * @param ref Matched filter reference waveform
 * @return Matrix2D<T> Matrix where each column is a matched filter response
 */
template <typename T>
Matrix2D<std::complex<T>> MatchedFilterResponse(Matrix2D<std::complex<T>> &in,
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

/**
 * @brief Generate a range-doppler map from complex-valued data
 *
 * This map is a matrix where the rows are the range bins and the columns are
 * the doppler bins.
 *
 * @tparam T Input type (real-valued)
 * @param pulses Fast-time slow-time matrix of input pulses
 * @param ref Time-reversed complex conjugate of the transmitted waveform
 * @return Matrix2D<T> Range-Doppler map
 */
template <typename T>
Matrix2D<std::complex<T>> RangeDopplerMap(Matrix2D<std::complex<T>> pulses,
                                          std::vector<std::complex<T>> ref) {
  using namespace Eigen;
  auto num_pulses = pulses.cols();
  auto conv_length = pulses.rows() + ref.size() - 1;
  Matrix<std::complex<T>, Dynamic, Dynamic> mf_resp =
      Map<Matrix<std::complex<T>, Dynamic, Dynamic>>(
          MatchedFilterResponse(pulses, ref).data(), conv_length, num_pulses);
  // Compute the FFT across each row
  FFT<T> fft;
  auto out = Matrix<std::complex<T>, Dynamic, Dynamic>(conv_length, num_pulses);
  for (int i_row = 0; i_row < conv_length; i_row++)
    out.row(i_row) = fft.fwd(mf_resp.row(i_row));
  // Shift 0 doppler to the center of the map and return
  out = Matrix<std::complex<T>, Dynamic, Dynamic>(Eigen::fftshift(out));
  return Matrix2D<std::complex<T>>(
      out.rows(), out.cols(),
      std::vector<std::complex<T>>(out.data(), out.data() + out.size()));
}
}  // namespace plasma