#include "square_waveform.h"
#include <iostream>
#include <arrayfire.h>
#include <complex>

int main() {
  double prf = 1e3;
  double pulse_width = 100e-6;
  double samp_rate = 1e6;
  plasma::SquareWaveform waveform(pulse_width, prf, samp_rate);

  // Expected result
  size_t num_samps_pri = round(samp_rate / prf);
  size_t num_samps_pulse = round(pulse_width * samp_rate);
  af::array expected = af::constant(0, num_samps_pri);
  expected(af::seq(num_samps_pulse)) = 1;

  // Actual result from the object
  // std::cout << waveform.prf().scalar<double>() << std::endl;
  af::array actual = waveform.step();

  // Check the pulse length
  // ASSERT_EQ(actual.elements(), expected.elements());

  // Check that the values are the same
  af::array result = af::allTrue(actual == expected);
  // af::array result = af::constant(1,1,b8);
  // af_print(result);
  std::cout << result.scalar<char>() << std::endl;
  // std::cout << *x << std::endl;
  // ASSERT_EQ(af::allTrue(result).scalar<bool>());
  return 0;
}