#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "square_waveform.h"

class SquareWaveformTest : public testing::Test {
protected:
};

/**
 * @brief Test the square waveform object by generating a 100-sample pulse with
 * a 10% duty cycle
 *
 */
TEST_F(SquareWaveformTest, SinglePRF) {
  double prf = 1e3;
  double pulse_width = 100e-6;
  double samp_rate = 1e6;
  plasma::SquareWaveform waveform(pulse_width, prf, samp_rate);

  // Expected result
  size_t num_samps_pri = round(samp_rate / prf);
  size_t num_samps_pulse = round(pulse_width * samp_rate);
  Eigen::ArrayXcd expected = Eigen::ArrayXcd::Zero(num_samps_pri);
  expected.head(num_samps_pulse) = 1;

  // Actual result from the object
  Eigen::ArrayXcd actual = waveform.step();

  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  EXPECT_THAT(actual.real(),
              testing::Pointwise(testing::FloatNear(1e-10), expected.real()));
  EXPECT_THAT(actual.imag(),
              testing::Pointwise(testing::FloatNear(1e-10), expected.imag()));
}

/**
 * @brief Test the square waveform object by generating a 100-sample pulse with
 * a 10% duty cycle, followed by a 100-sample pulse with a 20% duty cycle
 *
 */
TEST_F(SquareWaveformTest, MultiPRF) {
  Eigen::ArrayXd prfs(3);
  prfs << 1e3, 2e3, 1.5e3;
  double pulse_width = 100e-6;
  double samp_rate = 1e6;
  plasma::SquareWaveform waveform(pulse_width, prfs, samp_rate);

  // Check the first PRF
  for (auto &prf : prfs) {
    size_t num_samps_pri = round(samp_rate / prf);
    size_t num_samps_pulse = round(pulse_width * samp_rate);
    Eigen::ArrayXcd expected = Eigen::ArrayXcd::Zero(num_samps_pri);
    expected.head(num_samps_pulse) = 1;
    // Actual result from the object
    Eigen::ArrayXcd actual = waveform.step();
    // Check the pulse length
    ASSERT_EQ(actual.size(), expected.size());
    // Check that the values are the same
    EXPECT_THAT(actual.real(),
                testing::Pointwise(testing::FloatNear(1e-10), expected.real()));
    EXPECT_THAT(actual.imag(),
                testing::Pointwise(testing::FloatNear(1e-10), expected.imag()));
  }
}
