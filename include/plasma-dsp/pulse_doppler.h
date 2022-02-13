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
template <typename T> 
inline void fftshift(T *data, const size_t count) {
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
template <typename T>
inline void ifftshift(T *data, const size_t count) {
  int center = (int)floor((float)count / 2);
  // odd: 01 234 changes to 234 01
  std::rotate(data, data + center, data + count);
}

/**
 * @brief Use Fourier interpolation to delay an input signal by an arbitrary
 * amount of time (i.e., a non-integer number of samples).
 *
 * TODO: For now, the input signal must be a column vector
 *
 * @tparam T Data type of the elements in the signal
 * @param x Input signal vector
 * @param t Time delay (s)
 * @param nfft Number of points in the FFT
 * @param fs Sample rate (samples/sec)
 * @return Eigen::ArrayX<T>
 */
template <typename T>
Eigen::MatrixX<T> delay(Eigen::MatrixX<T> x, double t, size_t nfft, double fs) {
  Eigen::FFT<T> fft;
  // Compute the shifted FFT of the input signal
  Eigen::MatrixXcd x_fft(nfft, 1);
  fft.fwd(x_fft.data(), x.data(), nfft);
  fftshift(x_fft.data(), x_fft.size());
  // Apply the delay as a phase shift in the frequency domain
  Eigen::ArrayXd F =
      Eigen::ArrayXd::LinSpaced(nfft, 0.0, nfft - 1) * (fs / nfft) - (fs / 2);
  x_fft = x_fft.array() * exp(-Im * 2.0 * M_PI * F * t);
  // IFFT back to the time domain
  Eigen::MatrixX<T> y(nfft, 1);
  ifftshift(x_fft.data(), x_fft.size());
  fft.inv(y.data(), x_fft.data(), x_fft.size());
  std::cout << y << std::endl;
  return y;
}

} // namespace plasma

#endif /* F3BDADEA_1E2F_4FAA_8815_5EE937357AC0 */