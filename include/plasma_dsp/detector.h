#ifndef D1E0965D_6969_4C06_916F_4ADE35DEF4FE
#define D1E0965D_6969_4C06_916F_4ADE35DEF4FE

// #include <complex>
#include <vector>
#include <arrayfire.h>

/**
 * @brief A struct used to store the results of a detection for a CPI
 *
 *
 */
struct DetectionReport {

  DetectionReport() {num_detections = 0;}

  DetectionReport(const af::array &detections) {
    num_detections = af::sum<int>(detections);
    num_rows = detections.dims(0);
    num_cols = detections.dims(1);
    _detection = detections;
    }

  /**
   * @brief A logical matrix indicating whether a target was detected in each
   * range bin at each time instance
   *
   */
  af::array _detection;

  /**
   * @brief A vector of the range bin indices of each detection
   *
   */
  std::vector< std::vector<int>> indices;

  /**
   * @brief Number of detections
   *
   */
  size_t num_detections;

  size_t num_rows;

  size_t num_cols;
};

// TODO: This is very ugly, but I haven't figured out a good way to store
// detection indices without breaking multithreading
inline void ComputeDetectionIndices(DetectionReport &detectionArray) {
  float *host_detections = detectionArray._detection.host<float>();

  int hostIndex = 0;
  for(int i=0; i<detectionArray.num_rows; ++i){
    for(int j=0; j<detectionArray.num_cols; ++j){
      if(host_detections[hostIndex] == 1.0f){
        std::vector<int> coord;
        coord.push_back(i);
        coord.push_back(j);
        detectionArray.indices.push_back(coord);
      }
      ++hostIndex;
    }
  }

  af::freeHost(host_detections);

}

#endif /* D1E0965D_6969_4C06_916F_4ADE35DEF4FE */
