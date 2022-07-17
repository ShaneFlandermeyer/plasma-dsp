#include "phase_coded_waveform.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class PhaseCodedWaveformTest : public testing::Test {
protected:
};

TEST_F(PhaseCodedWaveformTest, RandomCode) {
  // Choose a random bandwidth, pulse width, and PRF, then use it to instantiate
  // the waveform object
  double prf = 1e3;
  size_t num_chip = 100;
  double chip_width = 1e-6;
  double samp_rate = 2 / chip_width;

  // Generate a random phase code of length num_chips. These values are
  // completely arbitrary.
  af::array code = af::randu(num_chip, f64) * (2 * af::Pi) - af::Pi;
  plasma::PhaseCodedWaveform waveform(code, chip_width, prf, samp_rate);

  // Expected result
  size_t num_samp_chip = round(chip_width * samp_rate);
  size_t num_samp_pulse = code.elements() * num_samp_chip;
  std::vector<std::complex<double>> expected(num_samp_pulse);
  for (auto i = 0; i < num_chip; i++) {
    double chip = code(i).scalar<double>();
    for (auto j = 0; j < num_samp_chip; j++) {
      expected[i * num_samp_chip + j] =
          std::exp(plasma::Im * chip);
    }
  }

  // Actual result from the object
  std::shared_ptr<std::complex<double>> actual_data(
      reinterpret_cast<std::complex<double> *>(
          waveform.sample().as(c64).host<af::cdouble>()));
  std::vector<std::complex<double>> actual(actual_data.get(),
                                           actual_data.get() + num_samp_pulse);

  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  for (int i = 0; i < num_samp_pulse; i++) {
    ASSERT_NEAR(actual[i].real(), expected[i].real(), 1e-10);
    ASSERT_NEAR(actual[i].imag(), expected[i].imag(), 1e-10);
  }
}
