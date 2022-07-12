// #include "matrix_utils.h"
#include "constants.h"
#include "filter.h"
#include "pcfm.h"
#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Eigen;
class PCFMWaveformTest : public testing::Test {
protected:
};

TEST_F(PCFMWaveformTest, RandomSinglePRF) {
  // Example phase code
  size_t N = 5;
  size_t over = 4;
  ArrayXd code = ArrayXd::LinSpaced(N, 1, N);

  // Generate the expected waveform
  // Compute the differences that are not wrapped around pi
  Eigen::ArrayXd difference(code.size());
  std::adjacent_difference(code.begin(), code.end(), difference.begin());
  // Wrap each element to [-pi, pi]
  for (size_t i = 0; i < difference.size(); i++)
    if (std::abs(difference(i)) > M_PI)
      difference(i) -= 2 * M_PI * difference.sign()(i);
  // Construct the shaping filter
  ArrayXd g = ArrayXd::Ones(over);
  ArrayXd g1 = g / g.sum();
  // Convolve with the zero-padded impulse train
  ArrayXd train = ArrayXd::Zero(over * N);
  train(seq(0, train.size() - 1, over)) = difference / over;
  ArrayXd chi1 = plasma::filter(g1, train);
  ArrayXd phi1(chi1.size());
  std::partial_sum(chi1.begin(), chi1.end(), phi1.begin());
  ArrayXcd expected = exp(plasma::Im * phi1);

  // Generate the actual waveform
  double samp_rate = 1e6;
  plasma::PCFMWaveform pcfm(code, g1, samp_rate, 0);
  ArrayXcd actual = pcfm.sample();

  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  EXPECT_THAT(actual.real(),
              testing::Pointwise(testing::FloatNear(1e-8), expected.real()));
  EXPECT_THAT(actual.imag(),
              testing::Pointwise(testing::FloatNear(1e-8), expected.imag()));
}