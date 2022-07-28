#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "cfar2d.h"

class CFARTest : public testing::Test {};

/**
 * @brief Test the 2D CFAR object on a simple binary matrix.
 *
 */
TEST_F(CFARTest, BinaryMatrix) {
  // Initialize the matrix to use for the test
  af::array matrix = af::constant(0, af::dim4(100, 100), f32);
  matrix(5, 4) = 1;
  matrix(60, 40) = 1;

  // Expected values
  int num_detections_expected = 2;
  af::array detections_expected = matrix;
  af::array indices_expected(af::dim4(2, 2), f32);
  indices_expected(0, 0) = 5;
  indices_expected(0, 1) = 4;
  indices_expected(1, 0) = 60;
  indices_expected(1, 1) = 40;
  // indices_expected.row(0) = {5, 4};

  // Create the CFAR object and compute the actual values from the
  // DetectionReport.
  plasma::CFARDetector2D cfar(2, 4, 1e-6);
  DetectionReport results = cfar.detect(matrix);
  int num_detections = results.num_detections;
  af::array detections = results.detections;
  af::array indices = results.indices;

  // Check the number of detections.
  ASSERT_EQ(num_detections, num_detections_expected);

  // Check that all values in the detection matrix are equal
  ASSERT_TRUE((detections == detections_expected).nonzeros() == detections.elements());

  // Check that all values in the indices matrix are equal
  ASSERT_TRUE((indices == indices_expected).nonzeros() == indices.elements());
}