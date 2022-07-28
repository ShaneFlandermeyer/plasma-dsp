#include "cfar2d.h"
#include "detector.h"
#include "file.h"
#include <fstream>
#include <iostream>
#include <numeric>
#include <arrayfire.h>

int main(int argc, char *argv[]) {
  int device = argc > 1 ? atoi(argv[1]) : 0;
  af::setDevice(device);
  af::info();

  af::array rdm = af::constant(0, af::dim4(10000, 512), f32);
  rdm(5, 4) = 1;
  rdm(10,9) = 1;

  // Setting the CFAR Window. 2 for the guard and 4 for the training.
  plasma::CFARDetector2D cfarDetector(2, 4, 0.00001f);
  
  // Compute where a detection is and then create a (row,col) array to store all
  // the detections.
  af::timer::start();
  DetectionReport results = cfarDetector.detect(rdm);
  std::cout << std::endl << "Elapsed time: " << af::timer::stop() << std::endl;

  // Print the number of detections.
  std::cout << results.num_detections << std::endl;
  af_print(results.indices);

  return 0;
}