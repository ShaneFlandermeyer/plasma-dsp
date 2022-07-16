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
  af::array expected = af::constant(0, num_samps_pri);
  expected(af::seq(num_samps_pulse)) = 1;

  // Actual result from the object
  af::array actual = waveform.step();

  // Check the pulse length
  ASSERT_EQ(actual.elements(), expected.elements());

  // Check that the values are the same
  bool result = af::allTrue(actual == expected).scalar<char>();
  EXPECT_TRUE(result);
}

/**
 * @brief Test the square waveform object by generating a 100-sample pulse with
 * a 10% duty cycle, followed by a 100-sample pulse with a 20% duty cycle
 *
 */
TEST_F(SquareWaveformTest, MultiPRF) {
  std::vector<double> prf_schedule {1e3, 2e3, 1.5e3};
  double pulse_width = 100e-6;
  double samp_rate = 1e6;
  plasma::SquareWaveform waveform(pulse_width, prf_schedule, samp_rate);

  // Check the first PRF
  for (auto &prf : prf_schedule) {
    size_t num_samps_pri = round(samp_rate / prf);
    size_t num_samps_pulse = round(pulse_width * samp_rate);
    af::array expected = af::constant(0, num_samps_pri);
    expected(af::seq(num_samps_pulse)) = 1;
    // Actual result from the object
    af::array actual = waveform.step();
    // Check the pulse length
    ASSERT_EQ(actual.elements(), expected.elements());
    // Check that the values are the same
    EXPECT_TRUE(af::allTrue(actual == expected).scalar<char>());
  }
}
