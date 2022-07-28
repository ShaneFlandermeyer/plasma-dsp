#include "optimization.h"

namespace plasma {

af::array profm(const af::array &in, const af::array &shape, int num_iter) {
  af::array pk = in;
  af::array rk(pk.elements(), pk.type());
  for (int i = 0; i < num_iter; i++) {
    rk = ifft(ifftshift(abs(shape) * exp(af::Im * arg(fftshift(fft(pk))))));
    pk = exp(af::Im * arg(rk));
  }
  return pk;
}
} // namespace plasma
