#ifndef C04C5908_3B07_4B80_AAF8_B45F5F45F490
#define C04C5908_3B07_4B80_AAF8_B45F5F45F490

#include "detector.h"

#ifdef USE_OPENMP
#include "omp.h"
#endif


namespace plasma {
/**
 * @brief 1D Constant False Alarm Rate (CFAR) detector object
 *
 * TODO: Currently only implements cell-averaging CFAR.
 *
 */
class CFARDetector {

public:
  /**
   * @brief Construct a new CFARDetector object
   *
   */
  CFARDetector() = default;

  /**
   * @brief Construct a new CFARDetector object
   *
   * @param cfar CFARDetector object
   */
  CFARDetector(const CFARDetector &cfar) = default;

  /**
   * @brief Construct a new CFARDetector object
   *
   * @param num_train Number of training cells
   * @param num_guard Number of guard cells
   * @param pfa Probability of false alarm
   */
  CFARDetector(size_t num_train, size_t num_guard, double pfa);

  /**
   * @brief Perform CFAR on one range bin of the input
   *
   * @param x M x N matrix of real-valued input data
   * @param cut_index Zero-indexed index of the current cell under test (CUT)
   * @return DetectionReport A struct containing the following detection
   * results:
   *
   * - detections: A logical matrix indicating whether a target was detected in
   *   a given range bin
   * - indices: A vector of the matrix indices of each detection
   * - threshold: A vector of the computed CFAR threshold at each index
   * - num_detections: The total number of detections
   */
  DetectionReport detect(const Eigen::MatrixXd &x, size_t cut_index);

  /**
   * @brief Perform CFAR on all range bins (rows) in the input
   *
   * @param x M x N matrix of real-valued input data
   * @return DetectionReport A struct containing the following detection
   * results:
   *
   * - detections: A logical matrix indicating whether a target was detected in
   *   a given range bin
   * - indices: A vector of the matrix indices of each detection
   * - threshold: A vector of the computed CFAR threshold at each index
   * - num_detections: The total number of detections
   */
  DetectionReport detect(const Eigen::MatrixXd &x);

private:
  /**
   * @brief Perform CFAR on one range bin of the input
   *
   * Unlike the public version, this method takes the detection report struct
   * as input and modifies it directly to avoid unnecessary copying. This is
   * faster and thus gets used in every other version of detect()
   *
   * @param x M x N matrix of real-valued input data
   * @param cut_index Zero-indexed index of the current cell under test (CUT)
   * @param result The detection report struct to be modified
   */
  void detect(const Eigen::MatrixXd &x, size_t cut_index,
              DetectionReport &result);

protected:
  /**
   * @brief Number of guard cells on either side of the cell under test
   *
   */
  size_t d_num_guard_cells;

  /**
   * @brief Number of training cells on either side of the cell under test
   *
   */
  size_t d_num_train_cells;

  /**
   * @brief Probability of false alarm
   *
   */
  double d_pfa;
};
}; // namespace plasma

#endif /* C04C5908_3B07_4B80_AAF8_B45F5F45F490 */
