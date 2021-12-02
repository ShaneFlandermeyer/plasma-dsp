#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <fftw3.h>
#include <matplot/matplot.h>

#include <Eigen/Dense>
#include <complex>
#include <iostream>
#include <unsupported/Eigen/FFT>
#include <vector>

#include "utils.h"

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
 * @param nfft Number of DFT points
 * @param noverlap Number of overlapped samples
 */
template <typename T1, typename T2>
Matrix<std::complex<double>, Dynamic, Dynamic> stft(const std::vector<T1> &signal,
                                                    const std::vector<T2> &window,
                                                    const int nFFT,
                                                    const int nOverlap) {
  Matrix<T1, Dynamic, 1> x = toEigen<T1>(signal);
  Matrix<T2, Dynamic, 1> win = toEigen<T2>(window);
  // Hop size between successive DFTs
  auto hopSize = window.size() - nOverlap;
  // Number of columns in the DFT matrix
  auto nCol = (int)floor((signal.size() - nOverlap) / hopSize);
  // STFT matrix
  Matrix<std::complex<double>, Dynamic, Dynamic> stft(nFFT, nCol);
  Matrix<T1, Dynamic, 1> xi;
  Matrix<std::complex<double>, Dynamic, 1> tmpOut;
  // FFT object setup
  FFT<T2> fft;
  for (auto iCol = 0; iCol < nCol; iCol++) {
    // Windowed time segment
    xi = x.segment(iCol * hopSize, window.size()).array() * win.array();
    // Compute the FFT of the windowed segment
    fft.fwd(tmpOut, xi);
    // Store the result in the columns of the STFT matrix
    stft.col(iCol) = tmpOut;
  }

  return stft;
}

/**
 * @brief Plot the spectrogram (frequency vs. time) of a signal
 *
 * @tparam T Input type
 * @param x Input signal
 * @param window Spectral window
 * @param nfft Number of DFT points
 * @param noverlap Number of overlapped samples
 */
template <typename T>
std::vector<std::vector<double>> spectrogram(const std::vector<T> &x,
                                             const std::vector<double> &window,
                                             const int nfft, const int noverlap) {
  // Compute the short-time fourier transform
  auto X = stft(x, window, nfft, noverlap);
  // Magnitude squared
  MatrixXd mag2 = X.array().abs2();
  auto spectro = fromEigen<double,MatrixXd>(mag2);
  return spectro;
}

#endif  // SPECTROGRAM_H