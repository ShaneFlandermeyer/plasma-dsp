#include "spectrogram.h"
using namespace matplot;

// TODO: No need to pass the sample rate unless I want to plot things here
std::vector<std::vector<std::complex<double>>> stft(
    std::vector<std::complex<double>> x, double fs, std::vector<double> window,
    int nfft, int noverlap) {
  // Hop size
  auto hopSize = window.size() - noverlap;
  // Number of columns in the STFT matrix
  auto k = (int)floor((x.size() - noverlap) / hopSize);
  // STFT matrix
  auto X = std::vector<std::vector<std::complex<double>>>(k);
  for (auto ii = 0, kk = 0; ii < x.size() - window.size();
       ii += hopSize, kk++) {
    // Windowed input values
    auto xi = std::vector<std::complex<double>>(window.size());
    // Apply window function
    for (auto jj = ii; jj < ii + window.size(); jj++)
      xi[jj - ii] = x[jj] * window[jj - ii];
    // Apply DFT
    X[kk] = fft(xi);
  }
  return X;
}

// TODO: Magnitude squared of stft gives the spectrogram
std::vector<std::vector<double>> spectrogram(
    std::vector<std::complex<double>> x, double fs, std::vector<double> window,
    int nfft, int noverlap) {
  // Compute the short-time fourier transform
  auto X = stft(x, fs, window, nfft, noverlap);

  // Magnitude squared
  auto spectro = std::vector<std::vector<double>>(X.size());
  for (int ii = 0; ii < spectro.size(); ii++) {
    spectro[ii] = std::vector<double>(X[ii].size());
    std::transform(
        X[ii].begin(), X[ii].end(), spectro[ii].begin(),
        [](std::complex<double> x) { return pow(abs(x), 2); });
  }
  

  return spectro;
}