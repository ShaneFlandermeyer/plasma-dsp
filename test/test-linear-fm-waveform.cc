#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "linear-fm-waveform.h"

class LinearFMWaveformTest : public testing::Test {
protected:
};

/**
 * @brief Test the LFM waveform object by feeding it a random PRF between
 * [1,10] kHz, a pulse width between [10,100] us and a bandwidth between [1,10]
 * MHz.
 *
 */
TEST_F(LinearFMWaveformTest, RandomSinglePRF) {
  // Choose a random bandwidth, pulse width, and PRF, then use it to instantiate
  // the waveform object
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution uniform(1, 10);
  double prf = uniform(engine) * 1e3;
  double pulse_width = uniform(engine) * 10e-6;
  double bandwidth = uniform(engine) * 1e6;
  double samp_rate = bandwidth * 1.5;
  plasma::LinearFMWaveform waveform(bandwidth, pulse_width, prf, samp_rate);

  // Generate the expected result
  size_t num_samps_pri = round(samp_rate / prf);
  size_t num_samps_pulse = round(pulse_width * samp_rate);
  Eigen::ArrayXcd expected = Eigen::ArrayXcd::Zero(num_samps_pri);
  double ts = 1 / samp_rate;
  double t;
  for (size_t i = 0; i < num_samps_pulse; i++) {
    t = i * ts;
    expected(i) = std::exp(
        plasma::Im * 2.0 * M_PI *
        (-bandwidth / 2 * t + bandwidth / (2 * pulse_width) * pow(t, 2)));
  }

  // Actual result from the object
  Eigen::ArrayXcd actual = waveform.pulse();

  std::vector<double> expected_real(expected.real().data(),
                                    expected.real().data() + expected.size());
  std::vector<double> actual_real(actual.real().data(),
                                  actual.real().data() + actual.size());

  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size())
      << "SquareWaveform: Incorrect pulse length";

  // Check that the values are the same
  EXPECT_THAT(actual.real(),
              testing::Pointwise(testing::FloatEq(), expected.real()))
      << "SquareWaveform: Incorrect pulse values";
}