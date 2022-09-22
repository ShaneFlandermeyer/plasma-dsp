#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fmcw_waveform.h"

class FMCWWaveformTest : public testing::Test {
protected:
};

/**
 * @brief Test an upsweep waveform with a random bandwidth and sweep duration
 */
TEST_F(FMCWWaveformTest, SymmetricUpsweep) {

  // Randomize waveform parameters and create the waveform object, then generate
  // the actual waveform
  double sweep_time = 100e-6;
  double sweep_bandwidth = 10e6;
  double samp_rate = 2 * sweep_bandwidth;
  plasma::FMCWWaveform waveform(sweep_time, sweep_bandwidth, samp_rate,
                                plasma::FMCWWaveform::SweepInterval::SYMMETRIC,
                                plasma::FMCWWaveform::SweepDirection::UP);
  // Generate the expected waveform
  int num_samp_sweep = round(sweep_time * samp_rate);
  std::vector<std::complex<double>> expected(num_samp_sweep);
  double ts = 1 / samp_rate;
  double t;
  for (int i = 0; i < num_samp_sweep; i++) {
    t = i * ts;
    expected[i] = std::exp(plasma::Im * M_PI *
                           (-sweep_bandwidth *  t +
                            sweep_bandwidth / sweep_time * std::pow(t, 2)));
  }
  // Actual result from the object
  std::shared_ptr<std::complex<double>> actual_data(
      reinterpret_cast<std::complex<double> *>(
          waveform.sample().host<af::cdouble>()));
  std::vector<std::complex<double>> actual(actual_data.get(),
                                           actual_data.get() + num_samp_sweep);
  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  for (int i = 0; i < num_samp_sweep; i++) {
    ASSERT_NEAR(actual[i].real(), expected[i].real(), 1e-8);
    ASSERT_NEAR(actual[i].imag(), expected[i].imag(), 1e-8);
  }
}