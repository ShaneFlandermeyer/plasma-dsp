#include "linear_fm_waveform.h"
#include <iostream>
#include <arrayfire.h>
#include <complex>
#include <memory>

int main() {
  // Choose a random bandwidth, pulse width, and PRF, then use it to instantiate
  // the waveform object
  double prf = 1e3;
  double pulse_width = 100e-6;
  double samp_rate = 10e6;
  double bandwidth = 7.5e6;
  plasma::LinearFMWaveform waveform(bandwidth, pulse_width, prf, samp_rate);

  // Generate the expected result
  size_t num_samp_pri = static_cast<size_t>(samp_rate / prf);
  size_t num_samp_pulse = static_cast<size_t>(pulse_width * samp_rate);

  std::vector<std::complex<double>> expected(num_samp_pri, 0);
  double ts = 1 / samp_rate;
  double t;
  for (size_t i = 0; i < num_samp_pulse; i++) {
    t = i * ts;
    expected[i] =
        std::exp(plasma::Im * M_PI *
                 (-bandwidth * t + bandwidth / pulse_width * std::pow(t, 2)));
  }
  // Actual result from the object
  // af::array result = waveform.step().as(c64); 
  // std::cout << result.type() << std::endl; 
  std::shared_ptr<std::complex<double>> actual_data(
      reinterpret_cast<std::complex<double> *>(
          waveform.step().as(c64).host<af::cdouble>()));
  std::vector<std::complex<double>> actual(actual_data.get(),
                             actual_data.get() + num_samp_pri);

  std::cout << actual.size() << " " << expected.size() << std::endl;

  return 0;
}