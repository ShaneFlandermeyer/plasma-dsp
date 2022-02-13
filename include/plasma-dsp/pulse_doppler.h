#ifndef F3BDADEA_1E2F_4FAA_8815_5EE937357AC0
#define F3BDADEA_1E2F_4FAA_8815_5EE937357AC0

#include "constants.h"
#include "eigen_config.h"

#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>

namespace plasma {

/**
 * @brief Shift zero-frequency component to center of spectrum
 *
 * @tparam T Input element type
 * @param data Input data
 * @param count Input data size
 */
template <typename T> inline void fftshift(T *data, const size_t count) {
  int center = (int)floor((float)count / 2);
  if (count % 2 != 0) {
    center++;
  }
  // odd: 012 34 changes to 34 012
  std::rotate(data, data + center, data + count);
}

/**
 * @brief Inverse zero-frequency shift
 *
 * @tparam T Input element type
 * @param data Input data
 * @param count Input data size
 */
template <typename T> inline void ifftshift(T *data, const size_t count) {
  int center = (int)floor((float)count / 2);
  // odd: 01 234 changes to 234 01
  std::rotate(data, data + center, data + count);
}

/**
 * @brief Delay a complex input signal by an arbitrary amount of time (i.e., a
 * non-integer number of samples) using Fourier interpolation
 *
 * TODO: For now, the input signal must be a Vector object
 *
 * @tparam T Data type of the elements in the signal
 * @param x Input signal vector
 * @param t Time delay (s)
 * @param nfft Number of points in the FFT
 * @param fs Sample rate (samples/sec)
 * @return Eigen::VectorX<T>
 */
template <typename T>
Eigen::VectorX<std::complex<T>> delay(const Eigen::VectorX<std::complex<T>> &x,
                                      double t, size_t nfft, double fs) {
  Eigen::FFT<double> fft;
  // Compute the shifted FFT of the input signal
  Eigen::VectorXcd x_fft = x.template cast<std::complex<double>>();
  x_fft.conservativeResize(nfft);
  fft.fwd(x_fft, x_fft);
  fftshift(x_fft.data(), x_fft.size());
  // Apply the delay as a phase shift in the frequency domain
  Eigen::ArrayXd F =
      Eigen::ArrayXd::LinSpaced(nfft, 0.0, nfft - 1) * (fs / nfft) - (fs / 2);
  x_fft = x_fft.array() * exp(-Im * 2.0 * M_PI * F * t);
  // IFFT back to the time domain
  Eigen::VectorXcd y(nfft, 1);
  ifftshift(x_fft.data(), x_fft.size());
  fft.inv(y, x_fft);
  return y.cast<std::complex<T>>();
}

/**
 * @brief Delay a real input signal by an arbitrary amount of time (i.e., a
 * non-integer number of samples) using Fourier interpolation.
 *
 * TODO: For now, the input signal must be a column vector
 *
 * @tparam T Data type of the elements in the signal
 * @param x Input signal vector
 * @param t Time delay (s)
 * @param nfft Number of points in the FFT
 * @param fs Sample rate (samples/sec)
 * @return Eigen::VectorX<T>
 */
template <typename T>
Eigen::VectorX<T> delay(const Eigen::VectorX<T> &x, double t, size_t nfft,
                        double fs) {
  Eigen::VectorX<std::complex<T>> x_fft = x.template cast<std::complex<T>>();
  Eigen::VectorXcd y = delay(x_fft, t, nfft, fs);
  return y.real().cast<T>();
}

Eigen::VectorXcd conv(Eigen::VectorXcd x, Eigen::VectorXcd h) {
  Eigen::FFT<double> fft;
  // Zero pad the inputs to the length of the convolution output
  size_t conv_length = x.size() + h.size() - 1;
  x.conservativeResize(conv_length);
  h.conservativeResize(conv_length);
  // Compute the FFT of the input signals
  Eigen::VectorXcd x_fft, h_fft;
  fft.fwd(x_fft, x);
  fft.fwd(h_fft, h);
  // Multiply the two FFTs
  Eigen::VectorXcd y = x_fft.array() * h_fft.array();
  // IFFT back to the time domain
  fft.inv(y, y);
  return y;
}
} // namespace plasma

#endif /* F3BDADEA_1E2F_4FAA_8815_5EE937357AC0 */