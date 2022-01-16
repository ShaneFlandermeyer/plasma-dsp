#include "phase-coded-waveform.h"

#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <matplot/matplot.h>

class PhaseCodedWaveformTest : public testing::Test {
protected:
};

TEST_F(PhaseCodedWaveformTest, RandomSinglePRF) {
  // Choose a random bandwidth, pulse width, and PRF, then use it to instantiate
  // the waveform object
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution uniform(1, 10);
  double prf = uniform(engine) * 1e3;
  size_t num_chips = uniform(engine);
  double chip_width = uniform(engine) * 1e-6;
  double samp_rate = 1e6;

  // Generate a random phase code of length num_chips. These values are
  // completely arbitrary.
  std::uniform_real_distribution<> code_values(-M_PI, M_PI);
  Eigen::ArrayXd code(num_chips);
  for (size_t i = 0; i < num_chips; i++) {
    code(i) = code_values(engine);
  }

  // Expected result
  // This ended up being exactly the same as in the object, but there's really
  // one way to do it!
  size_t num_samps_chip = round(chip_width * samp_rate);
  size_t num_samps_pri = round(samp_rate / prf);
  Eigen::ArrayXcd expected = Eigen::ArrayXcd::Zero(num_samps_pri);
  for (size_t i = 0; i < num_chips; i++) {
    expected(Eigen::seqN(i * num_samps_chip, num_samps_chip)) =
        std::exp(plasma::Im * code(i));
  }

  // Waveform generated by the object
  plasma::PhaseCodedWaveform waveform(code, chip_width, prf, samp_rate);
  Eigen::ArrayXcd actual = waveform.pulse();

  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  EXPECT_THAT(actual.real(),
              testing::Pointwise(testing::FloatNear(1e-10), expected.real()));
  EXPECT_THAT(actual.imag(),
              testing::Pointwise(testing::FloatNear(1e-10), expected.imag()));
}