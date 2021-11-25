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
std::vector<std::vector<std::complex<double>>> stft(
    std::vector<std::complex<double>> x, double fs, std::vector<double> window,
    int nfft, int noverlap);

/**
 * @brief Plot the spectrogram (frequency vs. time) of a signal
 *
 * @param x Input signal
 * @param fs Sample Rate
 * @param window Spectral window
 * @param nfft Number of DFT points
 * @param noverlap Number of overlapped samples
 */
std::vector<std::vector<double>> spectrogram(
    std::vector<std::complex<double>> x, double fs, std::vector<double> window,
    int nfft, int noverlap);

#endif  // SPECTROGRAM_H