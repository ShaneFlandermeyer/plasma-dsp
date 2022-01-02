#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>

#include "circ_shift.h"
#include "signal-processing.h"
#include "vector-utils.h"
namespace plasma {
using namespace Eigen;

/**
 * @brief Compute the matched filter response for a the input matrix
 *
 * @tparam T The (real-valued) input precision
 * @param in Fast-time slow-time matrix of input data
 * @param ref Matched filter reference waveform
 * @return Matrix2D<T> Matrix where each column is a matched filter response
 */
MatrixXcd MatchedFilterResponse(const MatrixXcd& in, const VectorXcd& ref) {
  auto conv_length = in.rows() + ref.size() - 1;
  auto num_pulses = in.cols();
  auto in_zeros = MatrixXcd::Zero(conv_length - in.rows(), num_pulses);
  // TODO: Define a concatenation function in MatrixBaseAddons.h
  // Zero-pad the inputs
  MatrixXcd in_mat(conv_length, num_pulses);
  in_mat << in, in_zeros;
  auto ref_zeros = VectorXcd::Zero(conv_length - ref.size());
  VectorXcd ref_vec(conv_length);
  ref_vec << ref, ref_zeros;

  auto out = MatrixXcd(conv_length, num_pulses);
  Eigen::FFT<double> fft;
  auto ref_fft = fft.fwd(ref_vec);
  for (int i_col = 0; i_col < in.cols(); i_col++) {
    out.col(i_col) = ref_fft.array() * fft.fwd(in_mat.col(i_col)).array();
    out.col(i_col) = fft.inv(out.col(i_col));
  }
  return out;
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
MatrixXcd RangeDopplerMap(const MatrixXcd& pulses, const VectorXcd& ref) {
  auto num_pulses = pulses.cols();
  auto conv_length = pulses.rows() + ref.size() - 1;
  MatrixXcd mf_resp = MatchedFilterResponse(pulses, ref);
  MatrixXcd out = MatrixXcd::Zero(conv_length, num_pulses);
  Eigen::FFT<double> fft;
  for (size_t i_row = 0; i_row < out.rows(); i_row++) {
    out.row(i_row) << fft.fwd(mf_resp.row(i_row),num_pulses);
  }
  out = MatrixXcd(Eigen::fftshift(out));
  return out;
}

}  // namespace plasma