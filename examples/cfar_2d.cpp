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
  CFARDetector2D cfar {10, 5, 1e-5};

  // Read range doppler map data from a file
  std::vector<double> data = read_file("/home/shane/data.bin");
  ArrayXXd x = Map<ArrayXXd>(data.data(), 200, 1024);
  DetectionReport det;
  cfar.detect(x, 82, 512, det);
  // Figures
  figure();
  x = 10 * log10(x);
  std::vector<std::vector<double>> xvec(x.rows(),
                                        std::vector<double>(x.cols()));
  for (uint i = 0; i < x.rows(); i++) {
    for (uint j = 0; j < x.cols(); j++) {
      xvec[i][j] = x.operator()(i, j);
    }
  }
  imagesc(xvec);
  show();
  return 0;
}