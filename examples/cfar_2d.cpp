/**
 * Created on Wed Jan 05 2022
 *
 * Shane Flandermeyer, shaneflandermeyer@gmail.com
 *
 * Perform 2D cell-averaging (CA) CFAR detection from the data given in the
 * matlab example at
 * https://www.mathworks.com/help/phased/ug/constant-false-alarm-rate-cfar-detection.html;jsessionid=a6023502856c0dcfb2d70ddac1a2
 */

#include "cfar.h"
#include "matrix-utils.h"

#include <fstream>
#include <random>
#include <vector>
#include <Eigen/Dense>
#include <matplot/matplot.h>

using namespace plasma;
using namespace matplot;
using namespace Eigen;

std::vector<double> read_file(std::string filename) {
  // open the file:
  std::streampos fileSize;
  std::ifstream file(filename, std::ios::binary);

  // get its size:
  file.seekg(0, std::ios::end);
  fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  // read the data:
  std::vector<double> fileData(fileSize);
  file.read((char *)&fileData[0], fileSize);
  return fileData;
}

int main() {
  // TODO: Change this back to 2D
  CFARDetector2D cfar {5, 10, 1e-5};

  // Read range doppler map data from a file
  // TODO: Make a way to generate this internally
  std::vector<double> data = read_file("/home/shane/data.bin");
  ArrayXXd x = Map<ArrayXXd>(data.data(), 200, 1024);
  DetectionReport det;
  auto start = std::chrono::high_resolution_clock::now();
  det = cfar.detect(x);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "CFAR took " << duration.count() << "  milliseconds" << std::endl;
  std::cout << "Number of Detections: " << det.num_detections << std::endl;

  // Figures
  // figure();
  // x = 10 * log10(x);
  // std::vector<std::vector<double>> xvec(x.rows(),
  //                                       std::vector<double>(x.cols()));
  // for (uint i = 0; i < x.rows(); i++) {
  //   for (uint j = 0; j < x.cols(); j++) {
  //     xvec[i][j] = x.operator()(i, j);
  //   }
  // }
  // imagesc(xvec);
  // show();
  return 0;
}