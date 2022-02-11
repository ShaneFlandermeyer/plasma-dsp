#ifndef F3BDADEA_1E2F_4FAA_8815_5EE937357AC0
#define F3BDADEA_1E2F_4FAA_8815_5EE937357AC0
#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>

namespace plasma {
/**
 * @brief Use Fourier interpolation to delay an input signal by an arbitrary
 * amount of time (i.e., a non-integer number of samples).
 *
 * @tparam T Data type of the elements in the signal
 * @param x Input signal
 * @param t Time delay (s)
 * @param nfft Number of points in the FFT
 * @param fs Sample rate (samples/sec)
 * @return Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic>
 */
template <typename T>
Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic>
delay(Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic> x, double t, size_t nfft,
      double fs) {}
} // namespace plasma

#endif /* F3BDADEA_1E2F_4FAA_8815_5EE937357AC0 */