#include "optimization.h"

namespace plasma {
af::array profm(const af::array &in, const af::array &shape) {
  af::array pk = exp(af::Im * arg(ifft(ifftshift(in))));
  af::array rk = ifft(abs(shape) * exp(af::Im * arg(fftshift(fft(pk)))));
  // TODO: Do this in a loop (until convergence criteria is achieved or a
  // maximum number of iterations are performed)
  return pk;
}
} // namespace plasma
