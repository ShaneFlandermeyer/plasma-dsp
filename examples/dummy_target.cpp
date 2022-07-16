#include "square_waveform.h"
#include <iostream>
#include <arrayfire.h>
#include <complex>

int main() {
  std::vector<double> prfs {1e3, 2e3, 1.5e3};
  // prfs << 1e3, 2e3, 1.5e3;
  double pulse_width = 100e-6;
  double samp_rate = 1e6;
  plasma::SquareWaveform waveform(pulse_width, prfs, samp_rate);

  // Check the first PRF
  for (int i = 0; i < prfs.size(); i++) {
    double prf = prfs[i];
    size_t num_samps_pri = round(samp_rate / prf);
    size_t num_samps_pulse = round(pulse_width * samp_rate);
    af::array expected = af::constant(0, num_samps_pri);
    expected(af::seq(num_samps_pulse)) = 1;
    // Actual result from the object
    af::array actual = waveform.step();
  }
  return 0;
}