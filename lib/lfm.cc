#include "lfm.h"
#include <iostream>
namespace plasma {

af::array lfm(double start_freq, double bandwidth, double pulse_width,
              double samp_rate, double prf) {
  // Sample interval
  double ts = 1 / samp_rate;
  size_t n_samp_pulse = round(samp_rate * pulse_width);
  af::array t = af::range(af::dim4(n_samp_pulse), -1, f64) * ts;
  af::array phase =
      af::Im * 2 * M_PI *
      (start_freq * t + bandwidth / (2 * pulse_width) * af::pow(t, 2));
  af::array x = af::exp(phase);

  // Zero-pad to PRF
  if (prf > 0) {
    size_t n_samp_pri = round(samp_rate / prf);
    size_t n_pad = n_samp_pri - n_samp_pulse;
    af::array zeros = af::constant(af::cdouble(0, 0), af::dim4(n_pad));
    x = af::join(0, x, zeros);
  }

  return x;
}

} // namespace plasma