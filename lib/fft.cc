#include "fft.h"

namespace plasma {
af::array fftshift(const af::array &in, int dim) {
  if (dim >= 4) {
    std::cerr << "Only supports shifts up to 4D (dim <= 3)" << std::endl;
    return af::array();
  }

  int x = 0, y = 0, z = 0, w = 0;
  // Compute the amount to shift in each dimension
  switch (dim) {
  case 0:
    x = in.dims(0) / 2;
    break;
  case 1:
    y = in.dims(1) / 2;
    break;
  case 2:
    z = in.dims(2) / 2;
    break;
  case 3:
    w = in.dims(3) / 2;
    break;
  default: // Shift in all dimensions
    x = in.dims(0) / 2;
    y = in.dims(1) / 2;
    z = in.dims(2) / 2;
    w = in.dims(3) / 2;
  }

  return af::shift(in, x, y, z, w);
}

af::array ifftshift(const af::array &in, int dim) {
  if (dim >= 4) {
    std::cerr << "Only supports shifts up to 4D (dim <= 3)" << std::endl;
    return af::array();
  }

  int x = 0, y = 0, z = 0, w = 0;
  // Compute the amount to shift in each dimension
  switch (dim) {
  case 0:
    x = (in.dims(0) + 1) / 2;
    break;
  case 1:
    y = (in.dims(1) + 1) / 2;
    break;
  case 2:
    z = (in.dims(2) + 1) / 2;
    break;
  case 3:
    w = (in.dims(3) + 1) / 2;
    break;
  default: // Shift in all dimensions
    x = in.dims(0) / 2;
    y = in.dims(1) / 2;
    z = in.dims(2) / 2;
    w = in.dims(3) / 2;
  }

  return af::shift(in, x, y, z, w);
  
}
} // namespace plasma