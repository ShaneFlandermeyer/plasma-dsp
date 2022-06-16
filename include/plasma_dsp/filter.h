#ifndef C38162B4_ECB4_482E_A4C9_25AF8B55C058
#define C38162B4_ECB4_482E_A4C9_25AF8B55C058

#include "fft.h"

namespace plasma {
std::vector<std::complex<float>>
conv(const std::vector<std::complex<float>> &x1,
     const std::vector<std::complex<float>> &x2, int num_threads = 1);

/**
 * @brief Convolve each column of 2D array x with a 1D vector h having 
 * 
 * @param x 2D array of complex numbers
 * @param h 1D vector of complex numbers
 * @param num_threads Number of threads to use in FFT computation
 * @return Eigen::ArrayXXcf 2D array where each column is a convolution output
 */
Eigen::ArrayXXcf conv(const Eigen::ArrayXXcf &x, const Eigen::ArrayXcf &h,
                     int num_threads = 1);
} // namespace plasma
#endif /* C38162B4_ECB4_482E_A4C9_25AF8B55C058 */
