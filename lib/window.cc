#include "window.h"

namespace plasma {

af::array rectangular(size_t n) { return af::constant(1, n).as(f64); }

af::array blackman(size_t n) {
  af::array in = af::range(af::dim4(n), -1, f64);
  return 0.42 - 0.5 * cos(2 * M_PI * in / n) + 0.08 * cos(4 * M_PI * in / n);
}

af::array hamming(size_t n) {
  af::array in = af::range(af::dim4(n), -1, f64);
  return 0.54 - 0.46 * cos(2 * M_PI * in / (n - 1));
}

af::array hanning(size_t n) {
  af::array in = af::range(af::dim4(n), -1, f64);
  return 0.5 - 0.5 * cos(2 * M_PI * in / (n - 1));
}

} // namespace plasma