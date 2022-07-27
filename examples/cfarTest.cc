#include "cfar2d.h"
#include "detector.h"
#include "file.h"
//#include "plasma_dsp/cfar2d.h"
#include <fstream>
#include <iostream>
#include <numeric>
#include <arrayfire.h>

af::array cfar(af::array rdm) {
  // Hardcode CFAR parameters
  int cfarR_guard = 2;
  int cfarR_train = 4;
  int cfarD_guard = 2;
  int cfarD_train = 4;

  float pfa = 0.00001f;

  size_t winR1 = 1 - cfarR_guard - cfarR_train;
  size_t winR2 = 1 + cfarR_guard + cfarR_train;

  size_t winD1 = 1 - cfarD_guard - cfarD_train;
  size_t winD2 = 1 + cfarD_guard + cfarD_train;

  size_t LR = winR2 - winR1 + 1;
  size_t LD = winD2 - winD1 + 1;

  af::array cfar_temp = af::constant(1, LR, LD);
  cfar_temp(af::seq(cfarR_train, cfar_temp.dims(0) - cfarR_train - 1),
            af::seq(cfarD_train, cfar_temp.dims(1) - cfarD_train - 1)) = 0;
  size_t num_train_bins = af::sum<int>(cfar_temp);
  cfar_temp = cfar_temp / (af::sum<float>(cfar_temp));

  af::array power =
      af::ifft2(af::fft2(cfar_temp, rdm.dims(0), rdm.dims(1)) * af::fft2(rdm));

  float alpha = num_train_bins * (pow(pfa, -1 / (double)num_train_bins) - 1);

  af::array detections = (rdm > power * alpha);

  return detections;

  // Return boolean matrix
  // Once that works, update detectionreport class and return indices as well
}

int main(int argc, char *argv[]) {
  int device = argc > 1 ? atoi(argv[1]) : 0;
  af::setDevice(device);
  af::info();
  std::string filename = "/home/shane/src/plasma-dsp/examples/rangeDopplerMap";
  std::vector<double> rdm = plasma::read<double>(filename);
  float copy_rdm[rdm.size()/2];
  int vector_index = 0;
  for(int i=0; i<rdm.size()/2; ++i){
    copy_rdm[i] = rdm[vector_index];
    vector_index = vector_index + 2;
  }
  af::array RDM(200, 1024, copy_rdm);
  // af::array RDM(af::dim4(1024, 200), rdm.data());
  // af::transposeInPlace(RDM);

  float tempArray[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  af::array _temp(9, 17, tempArray);

  plasma::CFARDetector2D cfarDetector(2, 4, 0.00001f);

  DetectionReport results = cfarDetector.detect(RDM);

  std::cout << "\n" << results.indices.size() << std::endl;

  for (int i = 0; i < results.indices.size(); ++i) {
    std::vector<int> currentCoord = results.indices[i];
    std::cout << currentCoord[0] << ", " << currentCoord[1] << std::endl;
  }

  af::saveArray("", results._detection.as(u8),
                "/home/shane/src/plasma-dsp/examples/cpp_detection");

  return 0;
}