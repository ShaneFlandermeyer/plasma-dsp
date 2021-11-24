#include "spectrogram.h"

#include <fftw3.h>

#include <iostream>

void stft(std::vector<std::complex<double>> x, double fs,
          std::vector<double> window, int nfft, int noverlap) {
  std::cout << "TODO: Implement me" << std::endl;
}