#include "filter.h"
#include <chrono>

using namespace std::chrono;

int main() {
  size_t N = 8192;
  Eigen::ArrayXXcf x1(N, 128);
  Eigen::ArrayXcf x2(N, 1);
  // x1 = Eigen::ArrayXcf::LinSpaced(N, 1, N);
  // x2 = Eigen::ArrayXcf::LinSpaced(N, 1, N);


  
  Eigen::ArrayXXcf y = plasma::conv(x1, x2, 10);
  
  std::cout << y.size() << std::endl;
  // std::cout << y.col(0) << std::endl;

  return 0;
}