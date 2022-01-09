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

  DetectionReport() {num_detections = 0;}

  DetectionReport(const Eigen::MatrixXd &x) {
    num_detections = 0;
    detection = Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic>(x.rows(), x.cols());
    threshold = Eigen::ArrayXXd(x.rows(),x.cols());
    }

  /**
   * @brief A logical matrix indicating whether a target was detected in each
   * range bin at each time instance
   *
   */
  Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic> detection;

  /**
   * @brief A vector of the range bin indices of each detection
   *
   */
  Eigen::Array<size_t, Eigen::Dynamic, 2> indices;

  /**
   * @brief A vector of the computed CFAR threshold at each range bin
   *
   */
  Eigen::ArrayXXd threshold;

  /**
   * @brief Number of detections
   *
   */
  size_t num_detections;
};

// TODO: This is very ugly, but I haven't figured out a good way to store
// detection indices without breaking multithreading
inline void ComputeDetectionIndices(DetectionReport &result) {
  result.indices =
      Eigen::Array<size_t, Eigen::Dynamic, 2>(result.num_detections, 2);
  size_t i_detection = 0;
  for (size_t i = 0; i < result.detection.rows(); ++i)
    for (size_t j = 0; j < result.detection.cols(); ++j)
      if (result.detection(i, j))
        result.indices.row(i_detection++) << i, j;
}


#endif /* D1E0965D_6969_4C06_916F_4ADE35DEF4FE */
