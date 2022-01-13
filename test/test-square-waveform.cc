#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "square-waveform.h"

class SquareWaveformTest : public testing::Test {
protected:
};

/**
 * @brief Test the square waveform object by feeding it a random PRF between 1
 * and 10 kHz and a pulse width between 10 and 100 us.
 * 
 */
TEST_F(SquareWaveformTest, RandomSinglePRF) {
  // Choose a random PRF and pulse width, then use it to instantiate the
  // waveform object
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution uniform(1, 10);
  double prf = uniform(engine) * 1e3;
  double pulse_width = uniform(engine) * 10e-6;
  double bandwidth = round(1 / pulse_width);
  double samp_rate = 1e6;
  plasma::SquareWaveform waveform(pulse_width, prf, samp_rate);

  // Expected result
  size_t num_samps_pri = round(samp_rate / prf);
  size_t num_samps_pulse = round(pulse_width * samp_rate);
  Eigen::ArrayXcd expected = Eigen::ArrayXcd::Zero(num_samps_pri);
  expected.head(num_samps_pulse) = 1;

  // Actual result from the object
  Eigen::ArrayXcd actual = waveform.pulse();

  // Check the pulse length, then the values themselves
  ASSERT_EQ(actual.size(), expected.size())
      << "SquareWaveform: Incorrect pulse length";
  EXPECT_THAT(actual.abs(), testing::Pointwise(testing::FloatEq(), expected.abs()))
      << "SquareWaveform: Incorrect pulse values";
}