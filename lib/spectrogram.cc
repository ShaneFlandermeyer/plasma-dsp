#include "spectrogram.h"
using namespace matplot;

std::vector<std::vector<std::complex<double>>> stft(
    std::vector<std::complex<double>> x, std::vector<double> window, int nfft,
    int noverlap) {
  // Hop size
  auto hopSize = window.size() - noverlap;
  // Number of columns in the STFT matrix
  auto k = (int)floor((x.size() - noverlap) / hopSize);
  // STFT matrix
  auto X = std::vector<std::vector<std::complex<double>>>(
      k, std::vector<std::complex<double>>(nfft));
  for (auto iStart = 0, iVec = 0; iStart < x.size() - window.size();
       iStart += hopSize, iVec++) {
    // Apply window function
    for (auto iWindow = 0; iWindow < window.size(); iWindow++)
      X[iVec][iWindow] = x[iStart + iWindow] * window[iWindow];
    // Comput the FFT of the segment
    X[iVec] = fft(X[iVec]);
  }
  return X;
}

std::vector<std::vector<double>> spectrogram(
    std::vector<std::complex<double>> x, std::vector<double> window, int nfft,
    int noverlap) {
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