#ifndef F3BDADEA_1E2F_4FAA_8815_5EE937357AC0
#define F3BDADEA_1E2F_4FAA_8815_5EE937357AC0
#include "constants.h"
#include <iostream>
#include <Eigen/Dense>
#include <circ_shift.h>
#include <unsupported/Eigen/FFT>
namespace plasma {

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
Eigen::ArrayX<T> delay(Eigen::ArrayX<T> x, double t, size_t nfft, double fs) {
  Eigen::FFT<T> fft;
  fft.SetFlag(Eigen::FFT<T>::Unscaled);
  // Compute the shifted FFT of the input signal
  Eigen::ArrayXcd x_fft(nfft);
  fft.fwd(x_fft.data(), x.data(), nfft);
  x_fft = Eigen::fftshift(x_fft);
  // Apply the delay as a phase shift in the frequency domain
  Eigen::ArrayXd F = Eigen::ArrayXd::LinSpaced(nfft, 0.0, nfft - 1)*(fs/nfft) - (fs/2);
  x_fft = x_fft * exp(-Im * 2.0 * M_PI * F * t);
  // IFFT back to the time domain
  Eigen::ArrayX<T> y(nfft);
  x_fft = Eigen::ifftshift(x_fft);
  fft.inv(y.data(), x_fft.data(), nfft);
  std::cout << y << std::endl << std::endl;
  std::cout << x << std::endl;
  return y;
}

} // namespace plasma

#endif /* F3BDADEA_1E2F_4FAA_8815_5EE937357AC0 */