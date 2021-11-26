#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <fftw3.h>
#include <matplot/matplot.h>

#include <complex>
#include <iostream>
#include <vector>

#include "utils.h"

/**
 * @brief Short-time Fourier transform (STFT)
 *
 * @param x Input signal
 * @param fs Sample Rate
 * @param window Spectral window
 * @param nfft Number of DFT points
 * @param noverlap Number of overlapped samples
 */
template <typename T>
std::vector<std::vector<std::complex<double>>> stft(std::vector<T> x,
                                                    std::vector<double> window,
                                                    int nfft, int noverlap) {
  // Hop size
  auto hopSize = window.size() - noverlap;
  // Number of columns in the STFT matrix
  auto k = (int)floor((x.size() - noverlap) / hopSize);
  // STFT matrix
  auto X = std::vector<std::vector<std::complex<double>>>(
      k, std::vector<std::complex<double>>(nfft));
  for (auto iStart = 0, iVec = 0; iStart < x.size() - window.size();
       iStart += hopSize, iVec++) {
    // Apply the window
    std::transform(x.begin() + iStart, x.begin() + iStart + window.size(),
                   window.begin(), X[iVec].begin(), std::multiplies<T>());
    // Compute the FFT
    X[iVec] = fft(X[iVec]);
  }
  return X;
}

/**
 * @brief Plot the spectrogram (frequency vs. time) of a signal
 *
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