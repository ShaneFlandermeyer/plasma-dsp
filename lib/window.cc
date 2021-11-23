#include "window.h"

#include <cmath>

namespace window {
std::vector<double> rectangular(int n) { return std::vector<double>(n, 1.0); }
std::vector<double> blackman(int n) {
  std::vector<double> w(n);
  for (int i = 0; i < n; i++)
    w[i] = 0.42 - 0.5 * cos(2 * M_PI * i / n) + 0.08 * cos(4 * M_PI * i / n);
  return w;
}
}  // namespace window