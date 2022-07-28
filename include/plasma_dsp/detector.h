#ifndef D1E0965D_6969_4C06_916F_4ADE35DEF4FE
#define D1E0965D_6969_4C06_916F_4ADE35DEF4FE

#include <array>
#include <vector>
#include <arrayfire.h>

/**
 * @brief A struct used to store the results of a detection for a CPI.
 *
 *
 */
struct DetectionReport {

  DetectionReport() { num_detections = 0; }

  DetectionReport(const af::array &detections) {
    this->detections = detections;
    num_detections = detections.nonzeros();

    // Compute the detection indices from the detection matrix
    af::array linear_indices = af::where(detections);
    af::array row_indices = linear_indices % detections.dims(0);
    af::array col_indices = linear_indices / detections.dims(0);
    indices = af::join(1, row_indices, col_indices);
  }

  /**
   * @brief A logical matrix indicating whether a target was detected in each
   * bin of 
   *
   */
  af::array detections;

  /**
   * @brief A vector of the range bin indices of each detection.
   *
   */
  af::array indices;

  /**
   * @brief Number of detections.
   *
   */
  size_t num_detections;
};

#endif /* D1E0965D_6969_4C06_916F_4ADE35DEF4FE */