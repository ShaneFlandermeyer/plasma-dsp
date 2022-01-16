#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fmcw-waveform.h"

class FMCWWaveformTest : public testing::Test {
protected:
};

/**
 * @brief Test an upsweep waveform with a random bandwidth and sweep duration
 */
TEST_F(FMCWWaveformTest, RandomUpsweep) {

  // Randomize waveform parameters and create the waveform object, then generate
  // the actual waveform
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution uniform(1, 10);
  double sweep_time = uniform(engine) * 1e-4;
  double sweep_bandwidth = uniform(engine) * 1e5;
  double samp_rate = 2 * sweep_bandwidth;
  plasma::FMCWWaveform waveform(sweep_time, sweep_bandwidth, samp_rate);
  Eigen::ArrayXcd actual = waveform.waveform();

  // Generate the expected waveform
  size_t num_samps_expected = round(sweep_time * samp_rate);
  Eigen::ArrayXcd expected = Eigen::ArrayXcd::Zero(num_samps_expected);
  double ts = 1 / samp_rate;
  double t;
  for (size_t i = 0; i < num_samps_expected; i++) {
    t = i * ts;
    expected(i) = std::exp(plasma::Im * 2.0 * M_PI *
                           (-sweep_bandwidth / 2 * t +
                            sweep_bandwidth / (2 * sweep_time) * pow(t, 2)));
  }

  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());
  
  // Check that the values are the same
  EXPECT_THAT(actual.real(),
              testing::Pointwise(testing::FloatNear(1e-10), expected.real()));
  EXPECT_THAT(actual.imag(),
              testing::Pointwise(testing::FloatNear(1e-10), expected.imag()));
}