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
 * @tparam T Input type
 * @param x Input signal
 * @param window Spectral window
 * @param nfft Number of DFT points
 * @param noverlap Number of overlapped samples
 */
template <typename T>
Matrix<std::complex<double>, Dynamic, Dynamic> stft(std::vector<T> x, std::vector<T> window,
                                 const int nFFT = 512,
                                 const int nOverlap = 256) {
  FFT<T> fft;
  // fft.SetFlag(FFT<T>::HalfSpectrum);
  auto hopSize = window.size() - nOverlap;
  auto nCol = (int)floor((x.size() - nOverlap) / hopSize);
  // STFT matrix
  Matrix<std::complex<double>, Dynamic, Dynamic> stft(nFFT, nCol);
  Matrix<T, Dynamic, 1> xi;
  Matrix<T, Dynamic, 1> win =
      Map<Matrix<T, Dynamic, 1>>(window.data(), window.size());
  Matrix<std::complex<double>, Dynamic, 1> tmpOut;
  for (auto iCol = 0; iCol < nCol; iCol++) {
    // Multiply the current segment by the window
    xi = Map<Matrix<T, Dynamic, 1>>(x.data() + iCol * hopSize, window.size());
    xi = xi.array() * win.array();
    // std::cout << xi << std::endl;
    // Compute the FFT of the windowed segment
    fft.fwd(tmpOut, xi);
    // Store the result in the columns of the STFT matrix
    stft.col(iCol) = tmpOut;
  }
  return stft;
}
// template <typename T>
// std::vector<std::vector<std::complex<double>>> stft(std::vector<T> x,
//                                                     std::vector<double>
//                                                     window, int nfft, int
//                                                     noverlap) {
//   // Hop size
//   auto hopSize = window.size() - noverlap;
//   // Number of columns in the STFT matrix
//   auto k = (int)floor((x.size() - noverlap) / hopSize);
//   // STFT matrix
//   auto X = std::vector<std::vector<std::complex<double>>>(
//       k, std::vector<std::complex<double>>(nfft));
//   // One window length of time series data
//   auto xi = std::vector<T>(window.size());
//   for (auto iStart = 0, iVec = 0; iStart < x.size() - window.size();
//        iStart += hopSize, iVec++) {
//     // Apply the window
//     std::transform(x.begin() + iStart, x.begin() + iStart + window.size(),
//                    window.begin(), xi.begin(), std::multiplies<T>());
//     // Compute the FFT
//     X[iVec] = fft(xi);
//   }
//   return X;
// }

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