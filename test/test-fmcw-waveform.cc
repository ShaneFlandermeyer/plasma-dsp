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

  Eigen::ArrayXcd actual = Eigen::ArrayXcd::Zero(100);
  Eigen::ArrayXcd expected = Eigen::ArrayXcd::Ones(100);
  
  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size())
      << "SquareWaveform: Incorrect pulse length";

  // Check that the values are the same
  EXPECT_THAT(actual.real(),
              testing::Pointwise(testing::FloatEq(), expected.real()))
      << "SquareWaveform: Incorrect pulse values";
}