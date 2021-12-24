#ifndef F49FC95E_8968_41E0_96E1_16209F637F93
#define F49FC95E_8968_41E0_96E1_16209F637F93

#include <fftw3.h>
#include <matplot/matplot.h>

#include <Eigen/Dense>
#include <complex>
#include <iostream>
#include <unsupported/Eigen/FFT>
#include <vector>

// #include "utils.h"

namespace plasma {
using namespace Eigen;
/**
 * @brief Short-time Fourier transform (STFT)
 *
 * This function currently computes the two-sided STFT over the interval
 * [0,2*pi) rad/sample.
 *
 * TODO: Extend this to centered and one-sided transforms as well
 *
 * @tparam T1 Input signal data type
 * @tparam T2 Window data type
 * @param x Input signal
 * @param window Spectral window
 * @param num_fft Number of DFT points
 * @param num_overlap Number of overlapped samples
 */
template <typename T1, typename T2>
std::vector<std::vector<std::complex<double>>> stft(
    const std::vector<T1> &signal, const std::vector<T2> &window,
    const int num_fft, const int num_overlap) {
  Matrix<T1, Dynamic, 1> x = toEigen<T1>(signal);
  Matrix<T2, Dynamic, 1> win = toEigen<T2>(window);
  // Hop size between successive DFTs
  auto hopSize = window.size() - num_overlap;
  // Number of columns in the DFT matrix
  auto nCol = (int)floor((signal.size() - num_overlap) / hopSize);
  // STFT matrix
  Matrix<std::complex<double>, Dynamic, Dynamic> stft(num_fft, nCol);
  // Segment vector
  Matrix<T1, Dynamic, 1> xi;
  // Segment DFT
  Matrix<std::complex<double>, Dynamic, 1> xif;
  // FFT object setup
  FFT<T2> fft;
  for (auto iCol = 0; iCol < nCol; iCol++) {
    // Windowed time segment
    xi = x.segment(iCol * hopSize, window.size()).array() * win.array();
    // Compute the FFT of the windowed segment
    fft.fwd(xif, xi);
    // Store the result in the columns of the STFT matrix
    stft.col(iCol) = xif;
  }

  return fromEigen<std::complex<double>>(stft);
}

/**
 * @brief Plot the spectrogram (frequency vs. time) of a signal
 *
 * @tparam T Input type
 * @param x Input signal
 * @param window Spectral window
 * @param num_fft Number of DFT points
 * @param num_overlap Number of overlapped samples
 */
template <typename T>
std::vector<std::vector<double>> spectrogram(const std::vector<T> &x,
                                             const std::vector<double> &window,
                                             const int num_fft,
                                             const int num_overlap) {
  // Compute the short-time fourier transform
  auto X = toEigen(stft(x, window, num_fft, num_overlap));
  // Magnitude squared
  MatrixXd mag2 = X.array().abs2();
  auto spectro = fromEigen<double, MatrixXd>(mag2);
  return spectro;
}

} // namespace plasma

#endif /* F49FC95E_8968_41E0_96E1_16209F637F93 */
