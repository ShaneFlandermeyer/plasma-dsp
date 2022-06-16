#ifndef C38162B4_ECB4_482E_A4C9_25AF8B55C058
#define C38162B4_ECB4_482E_A4C9_25AF8B55C058

#include "fft.h"

namespace plasma {
std::vector<std::complex<float>>
conv(const std::vector<std::complex<float>> &x1,
     const std::vector<std::complex<float>> &x2, int num_threads = 1);
}

#endif /* C38162B4_ECB4_482E_A4C9_25AF8B55C058 */
