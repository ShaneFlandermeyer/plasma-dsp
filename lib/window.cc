#include "window.h"

namespace plasma {
namespace window {
af::array rectangular(int n) { return af::constant(1, n).as(f64); }

af::array blackman(int n) {
  af::array in = af::range(af::dim4(n), -1, f64);
  return 0.42 - 0.5 * cos(2 * M_PI * in / n) + 0.08 * cos(4 * M_PI * in / n);
}

af::array hamming(int n) {
  af::array in = af::range(af::dim4(n), -1, f64);
  return 0.54 - 0.46 * cos(2 * M_PI * in / (n - 1));
}

af::array hanning(int n) {
  af::array in = af::range(af::dim4(n), -1, f64);
  return 0.5 - 0.5 * cos(2 * M_PI * in / (n - 1));
}

af::array gaussian(int n, double alpha) {
  af::array in = af::seq(-(n - 1) / 2, (n - 1) / 2);
  return exp(-0.5 * pow(alpha * 2 * in / (n - 1), 2));
}

} // namespace window
} // namespace plasma