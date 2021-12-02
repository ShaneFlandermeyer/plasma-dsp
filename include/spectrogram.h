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
 * @tparam T Input type
 * @param x Input signal
 * @param window Spectral window
 * @param nfft Number of DFT points
 * @param noverlap Number of overlapped samples
 */
template <typename T1, typename T2>
Matrix<std::complex<double>, Dynamic, Dynamic> stft(std::vector<T1> x,
                                                    std::vector<T2> window,
                                                    const int nFFT = 512,
                                                    const int nOverlap = 256) {
  // Hop size between successive DFTs
  auto hopSize = window.size() - nOverlap;
  // Number of columns in the DFT matrix
  auto nCol = (int)floor((x.size() - nOverlap) / hopSize);
  // STFT matrix
  Matrix<std::complex<double>, Dynamic, Dynamic> stft(nFFT, nCol);
  Matrix<T1, Dynamic, 1> xi;
  Matrix<T2, Dynamic, 1> win =
      Map<Matrix<T2, Dynamic, 1>>(window.data(), window.size());
  Matrix<std::complex<double>, Dynamic, 1> tmpOut;

  // FFT object setup
  FFT<T2> fft;
  for (auto iCol = 0; iCol < nCol; iCol++) {
    // Multiply the current segment by the window
    xi = Map<Matrix<T1, Dynamic, 1>>(x.data() + iCol * hopSize, window.size());
    xi = xi.array() * win.array();
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
std::vector<std::vector<double>> spectrogram(std::vector<T> x,
                                             std::vector<double> window,
                                             int nfft, int noverlap) {
  // Compute the short-time fourier transform
  auto X = stft(x, window, nfft, noverlap);
  // Magnitude squared
  auto spectro = std::vector<std::vector<double>>(X.size());
  for (int iVec = 0; iVec < spectro.size(); iVec++) {
    spectro[iVec] = std::vector<double>(X[iVec].size());
    std::transform(X[iVec].begin(), X[iVec].end(), spectro[iVec].begin(),
                   [](std::complex<double> x) { return pow(abs(x), 2); });
  }

  return spectro;
}

#endif  // SPECTROGRAM_H