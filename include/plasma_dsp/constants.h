#ifndef CB168327_F6DD_4F1E_839B_3A90B7B9993C
#define CB168327_F6DD_4F1E_839B_3A90B7B9993C

#include <complex>
#include <arrayfire.h>

namespace af {
const cdouble Im{0, 1};
}

namespace plasma {

// Imaginary number J
const std::complex<double> Im(0, 1);

/**
 * @brief Scale factor for db function
 *
 */
enum DbUnit {
  /**
   * @brief db function uses voltage reference
   *
   * @details db(x) = 20 * log10(x)
   */
  VOLTAGE,
  /**
   * @brief db function uses power reference
   *
   * @details db(x) = 10 * log10(x)
   */
  POWER
};

namespace physconst {
const double c = 299792458;
}

} // namespace plasma

#endif /* CB168327_F6DD_4F1E_839B_3A90B7B9993C */
