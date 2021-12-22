#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "squarewaveform.h"

using namespace plasma;
TEST(SquareWaveformTest, HandlesSinglePRF) {
  auto prf = 1e3;
  auto pulsewidth = 100e-6;
  auto samprate = 10e6;
  auto square = SquareWaveform(pulsewidth, prf, samprate);

  auto actual = square.pulse();
  std::vector<std::complex<double>> expected(samprate / prf, 0);
  int nSampsNonzero = samprate * pulsewidth;
  for (int i = 0; i < nSampsNonzero; i++) {
    expected[i] = std::complex<double>(1, 0);
  }

  // Verify that the pulse is the correct length
  ASSERT_EQ(actual.size(), expected.size()) << "Pulse is the wrong length";
  // TODO: Add google mock
  std::vector<double> actualAbs, expectedAbs;
  for (int i = 0; i < actual.size(); i++) {
    actualAbs.push_back(abs(actual[i]));
    expectedAbs.push_back(abs(expected[i]));
  }
  EXPECT_THAT(actualAbs, testing::Pointwise(testing::FloatEq(),expectedAbs))
      << "Pulse shape is not correct";
}