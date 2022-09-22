#include "pcfm.h"

#include <iostream>

namespace plasma {

PCFMWaveform::PCFMWaveform(af::array code, af::array filter, double samp_rate,
                           double prf)
    : Waveform(samp_rate),
      PulsedWaveform(filter.elements() * code.elements() / samp_rate, prf),
      d_code(code), d_filter(filter / af::sum<double>(filter)) {}

af::array PCFMWaveform::sample() {
  // Compute the first-order difference between values in the input phase code,
  // then wrap the result to [-pi,pi]
  // Each value in the resulting array can be thought of as the instantaneous
  // frequency at that sample
  af::array diff = diff1(d_code);
  diff(af::abs(diff) > M_PI) -= 2 * M_PI * sign(diff(abs(diff) > M_PI));

  // "Oversample" the phase difference code by a factor equal to the shaping
  // filter length. That is, for a length-n filter, the result is an n*code_size
  // vector where each nonzero element is a code value followed by n-1 zeros
  af::array train = af::constant(0, diff.elements() * d_filter.elements(), f64);
  train(af::seq(0, train.elements() - 1, d_filter.elements())) = diff;

  // Apply the shaping filter to the impulse train to "smooth out" the frequency
  // response
  af::array freq = fir(d_filter, train);

  // Integrate frequency to phase and exponentiate it to get the resulting
  // waveform
  af::array phase = accum(freq);
  af::array out = exp(af::Im * phase);
  return out;
}

} // namespace plasma