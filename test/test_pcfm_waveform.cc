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
  int N = 5;
  int over = 4;
  af::array code = af::seq(1, N);
  code = code.as(f64);

  // Generate the expected waveform
  // Compute the differences that are not wrapped around pi
  std::vector<double> difference(code.elements() - 1);
  for (int i = 1; i < code.elements(); i++) {
    difference[i - 1] = (code(i) - code(i - 1)).scalar<double>();
    if (abs(difference[i]) > M_PI)
      difference[i] -=
          2 * M_PI * (difference[i] > 0) ? 1 : ((difference[i] < 0) ? -1 :
          0);
  }

  std::vector<double> filter(over, 1 / (float)over);
  std::vector<double> freq(difference.size()*filter.size());
  for (int i = 0; i < difference.size(); i++) {
    for (int j = 0; j < filter.size(); j++) {
      freq[i * over + j] = filter[j] * difference[i];
    }
  }

  std::vector<double> phase(freq.size());
  std::partial_sum(freq.begin(), freq.end(), phase.begin());
  std::vector<std::complex<double>> expected(phase.size());
  for (int i = 0; i < phase.size(); i++) {
    expected[i] = exp(plasma::Im * phase[i]);
  }

  // Generate the actual waveform
  af::array g1 = af::constant(1 / (float)over, over, f64);
  plasma::PCFMWaveform waveform(code, g1, 0, 0);

  // Actual result from the object
  std::shared_ptr<std::complex<double>> actual_data(
      reinterpret_cast<std::complex<double> *>(
          waveform.sample().host<af::cdouble>()));
  std::vector<std::complex<double>> actual(actual_data.get(),
                                           actual_data.get() + phase.size());

  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  for (int i = 0; i < actual.size(); i++) {
    ASSERT_NEAR(actual[i].real(), expected[i].real(), 1e-10);
    ASSERT_NEAR(actual[i].imag(), expected[i].imag(), 1e-10);
  }
}