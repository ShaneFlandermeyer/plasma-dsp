#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "lfm.h"

class LinearFMWaveformTest : public testing::Test {
protected:
};

/**
 * @brief Test the square waveform object by generating a 7.5 MHz pulse with a
 * 10 % duty cycle
 *
 */
TEST_F(LinearFMWaveformTest, SinglePRF) {
  // // Choose a random bandwidth, pulse width, and PRF, then use it to instantiate
  // // the waveform object
  // // double prf = 1e3;
  // double pulse_width = 100e-6;
  // double samp_rate = 10e6;
  // double bandwidth = 7.5e6;
  // plasma::LinearFMWaveform waveform(bandwidth, pulse_width, samp_rate, 0,
  //                                   -bandwidth / 2);

  // // Generate the expected result
  // size_t num_samp_pulse = static_cast<size_t>(pulse_width * samp_rate);

  // std::vector<std::complex<double>> expected(num_samp_pulse, 0);
  // double ts = 1 / samp_rate;
  // double t;
  // for (size_t i = 0; i < num_samp_pulse; i++) {
  //   t = i * ts;
  //   expected[i] =
  //       std::exp(plasma::Im * M_PI *
  //                (-bandwidth * t + bandwidth / pulse_width * std::pow(t, 2)));
  // }
  // // Actual result from the object
  // // af_print(waveform.sample());
  // waveform = plasma::lfm(-bandwidth/2, bandwidth, pulse_width, samp_rate);
  // std::shared_ptr<std::complex<double>> actual_data(
  //     reinterpret_cast<std::complex<double> *>(
  //         waveform.sample().as(c64).host<af::cdouble>()));
  // std::vector<std::complex<double>> actual(actual_data.get(),
  //                                          actual_data.get() + num_samp_pulse);
  // // Check the pulse length
  // ASSERT_EQ(actual.size(), expected.size());

  // // Check that the values are the same
  // for (int i = 0; i < num_samp_pulse; i++) {
  //   ASSERT_NEAR(actual[i].real(), expected[i].real(), 1e-10);
  //   ASSERT_NEAR(actual[i].imag(), expected[i].imag(), 1e-10);
  // }
}