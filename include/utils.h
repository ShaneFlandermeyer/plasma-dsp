#ifndef UTILS_H
#define UTILS_H

#include <fftw3.h>

#include <complex>
#include <vector>

// TODO: These are currently passed by value, but moving data might be expensive

/**
 * @brief Matlab-like syntax for computing a complex forward FFT with FFTW3
 *
 * @param in Input data
 * @return std::vector<std::complex<double>> Complex DFT of the input
 */
std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &in);

/**
 * @brief Matlab-like syntax for computing a real forward FFT with FFTW3
 *
 * @param in Input data
 * @return std::vector<std::complex<double>> Complex DFT of the input
 */
std::vector<std::complex<double>> fft(std::vector<double> &in);

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

/**
 * @brief Inverse zero-frequency component shift
 *
 * @tparam T Input vector element data type
 * @param in Input vector
 * @return std::vector<T> Shifted output vector
 */
template <typename T>
static std::vector<T> ifftshift(std::vector<T> in) {
  auto out = in;
  auto len = out.size();
  auto center = (int)floor(len / 2);
  std::rotate(out.begin(), out.begin() + center, out.end());
  return out;
}

/**
 * @brief Convert the input vector from linear scale to db
 *
 * TODO: Add a parameter for power vs voltage quantities
 *
 * @tparam T Element type of the input vector
 * @param in Input data
 * @return std::vector<T> Output data
 */
template <typename T>
static std::vector<T> db(std::vector<T> &in) {
  auto out = in;
  std::transform(out.begin(), out.end(), out.begin(),
                 [](T &x) { return 10 * log10(x); });
  return out;
}

#endif