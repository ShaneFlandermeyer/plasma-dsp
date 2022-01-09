#ifndef D4D7CDC7_8DAA_42DF_A71A_3840A89194E5
#define D4D7CDC7_8DAA_42DF_A71A_3840A89194E5

#ifdef USE_OPENMP
#include "omp.h"
#endif

#include <complex>
#include <vector>
#include <Eigen/Dense>

namespace plasma {

/**
 * @brief A struct used to store the results of a CFAR detection
 *
 */
struct DetectionReport {

  DetectionReport() { num_detections = 0; }

  DetectionReport(const Eigen::MatrixXd &x) {
    num_detections = 0;
    detections =
        Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic>(x.rows(), x.cols());
    threshold = Eigen::MatrixXd(x.rows(), x.cols());
  }

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
  Eigen::MatrixXd threshold;

  /**
   * @brief Number of detections
   *
   */
  size_t num_detections;
};

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

/**
 * @brief 2D Constant False Alarm Rate (CFAR) detector object
 *
 * TODO: Currently only implements cell-averaging CFAR.
 *
 */
class CFARDetector2D {
public:
  /**
   * @brief Construct a new CFARDetector object
   *
   */
  CFARDetector2D() = default;

  /**
   * @brief Construct a new CFARDetector object
   *
   * @param cfar CFARDetector object
   */
  CFARDetector2D(const CFARDetector2D &cfar) = default;

  /**
   * @brief Construct a new CFARDetector object
   *
   * @param size_train Number of training cells surrounding the cell under test
   * in each dimension
   * @param size_guard Number of guard cells surrounding the cell under test in
   * each dimension
   * @param pfa Probability of false alarm
   */
  CFARDetector2D(size_t size_train, size_t size_guard, double pfa);

  CFARDetector2D(Eigen::Array<size_t, 2, 1> size_guard,
                 Eigen::Array<size_t, 2, 1> size_train, double pfa);

  /**
   * @brief Perform CFAR detection on the entire input signal
   *
   * TODO: Enable tensor inputs
   *
   * @param x An M-by-1 matrix of real-valued input data.
   * @return std::vector<bool>
   */
  DetectionReport detect(const Eigen::MatrixXd &x);

  /**
   * @brief Perform CFAR detection on the specified matrix indices
   *
   * @param x Input data matrix
   * @param indices A 2-by-D
   * @return DetectionReport
   */
  DetectionReport detect(const Eigen::MatrixXd &x,
                         const Eigen::Array2Xi &indices);

private:
  /**
   * @brief Perform CFAR detection on the specified elements of the input data
   *
   *
   * @param x M-by-N matrix of real-valued input data, where M is the number of
   * range bins and N is the number of time instances in the input signal.
   * @param cut_row Zero-indexed row of the current cell under test (CUT)
   * @param cut_row Zero-indexed column of the current cell under test (CUT)
   * @return DetectionReport A struct containing
   *
   * - A logical matrix indicating whether a target was detected in each bin
   * - The CFAR threshold at each bin
   * - The matrix indices of each detection
   */
  void detect(const Eigen::MatrixXd &x, size_t cut_row, size_t cut_col,
              DetectionReport &result);

protected:
  /**
   * @brief The number of rows and columns of the guard band cells on each side
   * of the CUT cell, specified as nonnegative integers.
   *
   * A 2-by-1 array where the first element specifies the guard band size along
   * the row dimension (height) and the second element specifies the guard band
   * size along the column dimension (width)
   *
   */
  Eigen::Array<size_t, 2, 1> d_guard_win_size;

  /**
   * @brief The number of rows and columns of the training band cells on each
   * side of the CUT cell, specified as nonnegative integers.
   *
   * A 2-by-1 array where the first element specifies the training band size
   * along the row dimension (height) and the second element specifies the guard
   * band size along the column dimension (width)
   *
   */
  Eigen::Array<size_t, 2, 1> d_train_win_size;

  /**
   * @brief Probability of false alarm
   *
   */
  double d_pfa;
};

/**
 * @brief Compute the matrix indices of each detection from a detection
 * report, and store them in the report struct
 *
 * @param result A DetectionReport object
 */
inline void ComputeDetectionIndices(DetectionReport &result);
} // namespace plasma
#endif /* D4D7CDC7_8DAA_42DF_A71A_3840A89194E5 */
