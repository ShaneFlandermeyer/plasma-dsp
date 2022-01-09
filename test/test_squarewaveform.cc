#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <numeric>

#include "square-waveform.h"

using namespace plasma;

class SquareWaveformTest : public testing::Test {
 protected:
  SquareWaveformTest() {
    prf = {1e3};
    pulsewidth = 100e-6;
    samprate = 10e6;
    square = SquareWaveform(pulsewidth, prf, samprate);
  }
  std::vector<double> prf;
  double pulsewidth;
  double samprate;
  SquareWaveform square;
};

TEST_F(SquareWaveformTest, HandlesSinglePRF) {
  auto actual = square.pulse();
  std::vector<std::complex<double>> expected(samprate / prf[0], 0);
  int nSampsNonzero = samprate * pulsewidth;
  for (int i = 0; i < nSampsNonzero; i++) {
    expected[i] = std::complex<double>(1, 0);
  }
  // Vectors of absolute values
  std::vector<double> actualAbs, expectedAbs;
  for (int i = 0; i < actual.size(); i++) {
    actualAbs.push_back(abs(actual[i]));
    expectedAbs.push_back(abs(expected[i]));
  }

  // Verify that the pulse is the correct length
  ASSERT_EQ(actual.size(), expected.size()) << "Pulse is the wrong length";
  // Verify that the pulse data is correct
  EXPECT_THAT(actualAbs, testing::Pointwise(testing::FloatEq(), expectedAbs))
      << "Pulse shape is not correct";
}

TEST_F(SquareWaveformTest, HandlesMultiPRF) {
  prf = {1e3,5e3,10e3};
  square.prf(prf);
  std::vector<double> pri(prf.size()); 
  std::transform(prf.begin(),prf.end(),pri.begin(),
                            [](auto x){return 1/x;});
  auto totalDuration = std::accumulate(pri.begin(),pri.end(), 0.0);
  auto actual = square.pulse();
  std::vector<std::complex<double>> expected(samprate*totalDuration, 0);
  int nSampsNonzero = samprate * pulsewidth;
  // Nonzero samples for the first PRF
  for (int i = 0; i < nSampsNonzero; i++) {
    expected[i] = std::complex<double>(1, 0);
    int prfStart = 0;
    for (int j = 0; j < prf.size()-1; j++) {
      prfStart += samprate/prf[j];
      expected[prfStart+i] = std::complex<double>(1, 0);
    }
  }
  // Vectors of absolute values
  std::vector<double> actualAbs, expectedAbs;
  for (int i = 0; i < actual.size(); i++) {
    actualAbs.push_back(abs(actual[i]));
    expectedAbs.push_back(abs(expected[i]));
  }

  // Verify that the pulse is the correct length
  ASSERT_EQ(actual.size(), expected.size()) << "Pulse is the wrong length";
  // Verify that the pulse data is correct
  EXPECT_THAT(actualAbs, testing::Pointwise(testing::FloatEq(),expectedAbs))
      << "Pulse shape is not correct";
}