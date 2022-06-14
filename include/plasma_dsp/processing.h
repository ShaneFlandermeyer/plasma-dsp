#ifndef A5C31B48_9A55_4209_8ECA_2F954DCC8005
#define A5C31B48_9A55_4209_8ECA_2F954DCC8005

#include <fftw3.h>
// #include <fftw3f.h>

#include "vector_utils.h"
#include <algorithm>
#include <chrono>
#include <complex>
#include <iostream>
#include <thread>
#include <vector>
#include <Eigen/Dense>
#include <eigen3/unsupported/Eigen/FFT>

namespace plasma {

/**
 * @brief Matlab-like syntax for computing a complex forward FFT with FFTW3
 *
 * @param in Input data vector of complex doubles
 * @return std::vector<std::complex<double>> DFT of the input
 */
std::vector<std::complex<double>>
fft(const std::vector<std::complex<double>> &x, int N = -1, size_t num_threads = 1);

/**
 * @brief Matlab-like syntax for computing a complex forward FFT with FFTW3F
 *
 * @param in Input data vector of complex floats
 * @return std::vector<std::complex<float>> DFT of the input
 */
std::vector<std::complex<float>>
fft(std::vector<std::complex<float>> &in, int N = -1, size_t num_threads = 1);

/**
 * @brief Matlab-like syntax for computing a real forward FFT with FFTW3
 *
 * @tparam T Input type
 * @param in Input data vector
 * @return std::vector<std::complex<double>> DFT of the input
 */
template <typename T>
inline std::vector<std::complex<double>> fft(std::vector<T> &in, int N = -1) {
  if (N == -1)
    N = in.size();
  auto out = std::vector<std::complex<double>>(N);
  in.resize(N);
  fftw_plan p = fftw_plan_dft_r2c_1d(
      N, reinterpret_cast<double *>(in.data()),
      reinterpret_cast<fftw_complex *>(out.data()), FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  for (auto &x : out)
    x /= N;
  return out;
}

/**
 * @brief Inverse fast Fourier Transform (IFFT)
 *
 * @tparam T Input type
 * @param in Input data
 * @return std::vector<T> Inverse FFT of input
 */
template <typename T>
std::vector<T> ifft(std::vector<std::complex<double>> in, int N = -1);
template <typename T>
std::vector<T> ifft(std::vector<std::complex<float>> in, int N = -1);

/**
 * @brief Shift the zero frequency component to the center of the spectrum
 *
 * @tparam T Input vector element data type
 * @param in Input vector
 * @return std::vector<T> Shifted output vector
 */
template <typename T> inline std::vector<T> fftshift(std::vector<T> in) {
  auto out = in;
  auto len = out.size();
  auto center = (int)floor(len / 2);
  if (len % 2 != 0)
    center++;
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
template <typename T> inline std::vector<T> ifftshift(std::vector<T> in) {
  auto out = in;
  auto len = out.size();
  auto center = (int)floor(len / 2);
  std::rotate(out.begin(), out.begin() + center, out.end());
  return out;
}

/**
 * @brief Compute the 1D convolution of two real input vectors using the FFT
 *
 * @tparam T Input data type
 * @param in1 1st input vector
 * @param in2 2nd input vector
 * @return std::vector<T> Convolution of the two input vectors with length
 * length(in1)+length(in2)-1
 */
template <typename T>
std::vector<T> conv(std::vector<T> in1, std::vector<T> in2) {
  std::vector<std::complex<T>> product;
  // Convolution length
  size_t N = in1.size() + in2.size() - 1;
  // Multiply the inputs in the frequency domain
  auto fin1 = fft(in1, N);
  auto fin2 = fft(in2, N);
  std::transform(fin1.begin(), fin1.end(), fin2.begin(),
                 std::back_inserter(product),
                 std::multiplies<std::complex<T>>());
  return ifft<T>(product, N);
}

template <typename T>
std::vector<std::complex<T>> conv(std::vector<std::complex<T>> in1,
                                  std::vector<std::complex<T>> in2) {
  // Convolution length
  size_t N = in1.size() + in2.size() - 1;
  // Multiply the inputs in the frequency domain
  std::vector<std::complex<T>> fin1 = fft(in1, N);
  std::vector<std::complex<T>> fin2 = fft(in2, N);
  std::vector<std::complex<T>> product;
  std::transform(fin1.begin(), fin1.end(), fin2.begin(),
                 std::back_inserter(product),
                 std::multiplies<std::complex<T>>());
  return ifft<std::complex<T>>(product, N);
}

template <typename T>
Eigen::ArrayX<T> conv(Eigen::ArrayX<T> &in1, Eigen::ArrayX<T> &in2) {
  std::vector<T> result =
      conv(std::vector<T>(in1.data(), in1.data() + in1.size()),
           std::vector<T>(in2.data(), in2.data() + in2.size()));
  return Eigen::Map<Eigen::ArrayX<T>, Eigen::Unaligned>(result.data(),
                                                        result.size());
}

} // namespace plasma
#endif /* A5C31B48_9A55_4209_8ECA_2F954DCC8005 */
