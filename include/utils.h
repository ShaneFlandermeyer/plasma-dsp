#ifndef UTILS_H
#define UTILS_H

#include <fftw3.h>

#include <complex>
#include <vector>

/**
 * @brief Wrapper function for computing a forward FFT with FFTW3
 * 
 * TODO: Overload this to allow user-defined FFT lengths
 * 
 * @param in The input data
 * @return std::vector<std::complex<double>> The DFT of the input 
 */
std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &in);

// TODO: Add an fftshift function

#endif