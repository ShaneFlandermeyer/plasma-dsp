#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "window.h"

class WindowTest : public testing::Test {};

TEST_F(WindowTest, Rectangular) {
  size_t n = 50;
  // Expected values
  std::vector<double> expected(n, 1);
  // Actual result from the object
  std::shared_ptr<double> actual_data(
      reinterpret_cast<double *>(plasma::rectangular(n).host<double>()));
  std::vector<double> actual(actual_data.get(), actual_data.get() + n);
  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  for (int i = 0; i < n; i++) {
    ASSERT_NEAR(actual[i], expected[i], 1e-10);
  }
}

TEST_F(WindowTest, Blackman) {
  size_t n = 50;
  // Expected values
  std::vector<double> expected(n);
  for (int i = 0; i < n; i++)
    expected[i] =
        0.42 - 0.5 * cos(2 * M_PI * i / n) + 0.08 * cos(4 * M_PI * i / n);
  // Actual result from the object
  std::shared_ptr<double> actual_data(
      reinterpret_cast<double *>(plasma::blackman(n).host<double>()));
  std::vector<double> actual(actual_data.get(), actual_data.get() + n);
  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  for (int i = 0; i < n; i++) {
    // std::cout << i << std::endl;
    ASSERT_NEAR(actual[i], expected[i], 1e-10);
  }
}

TEST_F(WindowTest, Hamming) {
  size_t n = 50;
  // Expected values
  std::vector<double> expected(n);
  for (int i = 0; i < n; i++)
    expected[i] = 0.54 - 0.46 * cos(2 * M_PI * i / (n - 1));
  // Actual result from the object
  std::shared_ptr<double> actual_data(
      reinterpret_cast<double *>(plasma::hamming(n).host<double>()));
  std::vector<double> actual(actual_data.get(), actual_data.get() + n);
  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  for (int i = 0; i < n; i++) {
    // std::cout << i << std::endl;
    ASSERT_NEAR(actual[i], expected[i], 1e-10);
  }
}

TEST_F(WindowTest, Hanning) {
  size_t n = 50;
  // Expected values
  std::vector<double> expected(n);
  for (int i = 0; i < n; i++)
    expected[i] = 0.5 - 0.5 * cos(2 * M_PI * i / (n - 1));
  // Actual result from the object
  std::shared_ptr<double> actual_data(
      reinterpret_cast<double *>(plasma::hanning(n).host<double>()));
  std::vector<double> actual(actual_data.get(), actual_data.get() + n);
  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  for (int i = 0; i < n; i++) {
    // std::cout << i << std::endl;
    ASSERT_NEAR(actual[i], expected[i], 1e-10);
  }
}