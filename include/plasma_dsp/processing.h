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
 * @brief Compute the nfft-point FFT of the complex float data pointed to by in.
 *
 * @param in Pointer to input data
 * @param nfft Number of FFT points to compute
 * @param num_threads Number of threads to use in the computation
 * default: 1
 * @return std::complex<float>* Pointer to the frequency-domain data
 */
std::complex<float> *fft(std::complex<float> *in, int nfft,
                         size_t num_threads = 1);

/**
 * @brief Compute the nfft-point FFT of the complex double data pointed to by
 * in.
 *
 * @param in Pointer to input data
 * @param nfft Number of FFT points to compute
 * @param num_threads Number of threads to use in the computation
 * default: 1
 * @return std::complex<double>* Pointer to the frequency-domain data
 */
std::complex<double> *fft(std::complex<double> *in, int nfft,
                          size_t num_threads = 1);

/**
 * @brief Compute the nfft-point FFT of the complex input data
 *
 * @tparam T Precision of complex input data
 * @param in Input data vector
 * @param nfft Number of FFT points to compute
 * @param num_threads Number of threads to use in the computation
 * default: 1
 * @return std::vector<std::complex<T>> Output data vector
 */
template <typename T>
inline std::vector<std::complex<T>> fft(std::vector<std::complex<T>> &in,
                                        int nfft, size_t num_threads = 1) {
  std::complex<T> *out = fft(in.data(), nfft, num_threads);
  return std::vector<std::complex<T>>(out, out + nfft);
}

std::complex<float>* ifft(std::complex<float>* in, int nfft, size_t num_threads = 1);
std::complex<double>* ifft(std::complex<double>* in, int nfft, size_t num_threads = 1);

template <typename T>
inline std::vector<std::complex<T>> ifft(std::vector<std::complex<T>> &in,
                                        int nfft, size_t num_threads = 1) {
  std::complex<T> *out = ifft(in.data(), nfft, num_threads);
  return std::vector<std::complex<T>>(out, out + nfft);
}

// /**
//  * @brief Inverse fast Fourier Transform (IFFT)
//  *
//  * @tparam T Input type
//  * @param in Input data
//  * @return std::vector<T> Inverse FFT of input
//  */
// template <typename T>
// std::vector<T> ifft(std::vector<std::complex<double>> in, int N = -1);
// template <typename T>
// std::vector<T> ifft(std::vector<std::complex<float>> in, int N = -1);

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

// /**
//  * @brief Compute the 1D convolution of two real input vectors using the FFT
//  *
//  * @tparam T Input data type
//  * @param in1 1st input vector
//  * @param in2 2nd input vector
//  * @return std::vector<T> Convolution of the two input vectors with length
//  * length(in1)+length(in2)-1
//  */
// template <typename T>
// std::vector<T> conv(std::vector<T> in1, std::vector<T> in2) {
//   std::vector<std::complex<T>> product;
//   // Convolution length
//   size_t N = in1.size() + in2.size() - 1;
//   // Multiply the inputs in the frequency domain
//   auto fin1 = fft(in1, N);
//   auto fin2 = fft(in2, N);
//   std::transform(fin1.begin(), fin1.end(), fin2.begin(),
//                  std::back_inserter(product),
//                  std::multiplies<std::complex<T>>());
//   return ifft<T>(product, N);
// }

// template <typename T>
// std::vector<std::complex<T>> conv(std::vector<std::complex<T>> in1,
//                                   std::vector<std::complex<T>> in2) {
//   // Convolution length
//   size_t N = in1.size() + in2.size() - 1;
//   // Multiply the inputs in the frequency domain
//   std::vector<std::complex<T>> fin1 = fft(in1, N);
//   std::vector<std::complex<T>> fin2 = fft(in2, N);
//   std::vector<std::complex<T>> product;
//   std::transform(fin1.begin(), fin1.end(), fin2.begin(),
//                  std::back_inserter(product),
//                  std::multiplies<std::complex<T>>());
//   return ifft<std::complex<T>>(product, N);
// }

// template <typename T>
// Eigen::ArrayX<T> conv(Eigen::ArrayX<T> &in1, Eigen::ArrayX<T> &in2) {
//   std::vector<T> result =
//       conv(std::vector<T>(in1.data(), in1.data() + in1.size()),
//            std::vector<T>(in2.data(), in2.data() + in2.size()));
//   return Eigen::Map<Eigen::ArrayX<T>, Eigen::Unaligned>(result.data(),
//                                                         result.size());
// }

} // namespace plasma
#endif /* A5C31B48_9A55_4209_8ECA_2F954DCC8005 */
