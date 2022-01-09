#ifndef D1E0965D_6969_4C06_916F_4ADE35DEF4FE
#define D1E0965D_6969_4C06_916F_4ADE35DEF4FE

// #include <complex>
// #include <vector>
#include <Eigen/Dense>

/**
 * @brief A struct used to store the results of a detection for a CPI
 *
 *
 */
struct DetectionReport {

  /**
   * @brief A logical matrix indicating whether a target was detected in each
   * range bin at each time instance
   *
   */
  Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic> detections;

  /**
   * @brief A vector of the range bin indices of each detection
   *
   */
  Eigen::Array<size_t, Eigen::Dynamic, 2> indices;

  /**
   * @brief A vector of the computed CFAR threshold at each range bin
   *
   */
  Eigen::ArrayXXd thresholds;

  /**
   * @brief Number of detections
   *
   */
  size_t num_detections;
};

#endif /* D1E0965D_6969_4C06_916F_4ADE35DEF4FE */
