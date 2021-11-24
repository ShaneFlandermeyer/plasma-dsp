#ifndef UTILS_H
#define UTILS_H

#include <fftw3.h>

#include <complex>
#include <vector>

// TODO: These are currently passed by value, but moving data might be expensive

/**
 * @brief Wrapper function for computing a forward FFT with FFTW3
 *
 * TODO: Overload this to allow user-defined FFT lengths
 *
 * @param in The input data
 * @return std::vector<std::complex<double>> The DFT of the input
 */
std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &in);

/**
 * @brief Shift the zero frequency component to the center of the spectrum
 *
 * @tparam T Input vector element data type
 * @param in Input vector
 * @return std::vector<T> Shifted output vector
 */
template <typename T>
static std::vector<T> fftshift(std::vector<T> in) {
  auto out = in;
  auto len = out.size();
  auto center = (int)floor(len / 2);
  if (len % 2 != 0) center++;
  std::rotate(out.begin(), out.begin() + center, out.end());
  return out;
}

#endif