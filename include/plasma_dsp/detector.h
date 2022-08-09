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
    indices = af::where(detections);
    rows = indices % detections.dims(0);
    cols = indices / detections.dims(0);
  }

  /**
   * @brief A logical matrix indicating whether a detection was made in each
   * matrix position
   *
   */
  af::array detections;

  /**
   * @brief An array containing the (column-major) linear indices of the
   * detections
   *
   */
  af::array indices;

  /**
   * @brief An array containing the row indices of the detections
   * 
   */
  af::array rows;

  /**
   * @brief An array containing the column indices of the detections
   * 
   */
  af::array cols;

  /**
   * @brief Number of detections.
   *
   */
  size_t num_detections;
};

#endif /* D1E0965D_6969_4C06_916F_4ADE35DEF4FE */