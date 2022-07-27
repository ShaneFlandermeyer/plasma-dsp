#include "plasma_dsp/file.h"
#include "cfar2d.h"
//#include "plasma_dsp/cfar2d.h"
#include <fstream>
#include <iostream>
#include <arrayfire.h>
#include <numeric>

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
  cfar_temp(af::seq(cfarR_train, cfar_temp.dims(0)-cfarR_train-1), af::seq(cfarD_train, cfar_temp.dims(1)-cfarD_train-1)) = 0;
  size_t num_train_bins = af::sum<int>(cfar_temp);
  cfar_temp = cfar_temp/(af::sum<float>(cfar_temp));

  af::array power = af::ifft2(af::fft2(cfar_temp, rdm.dims(0), rdm.dims(1))*af::fft2(rdm));

  float alpha = num_train_bins*(pow(pfa, -1 / (double)num_train_bins) - 1);

  af::array detections = (rdm > power * alpha);

  return detections;

  // Return boolean matrix
  // Once that works, update detectionreport class and return indices as well
}

int main(int argc, char* argv[]) {
  int device = argc > 1? atoi(argv[1]):0;
  af::setDevice(device);
  af::info();
  std::string filename = "/home/avery/Research  Folder/MatLab/rangeDopplerMap";
  std::vector<double> rdm = plasma::read<double>(filename);
  float copy_rdm[rdm.size()/2];
  int vector_index = 0;
  for(int i=0; i<rdm.size()/2; ++i){
    copy_rdm[i] = rdm[vector_index];
    vector_index = vector_index + 2;
  }
  af::array RDM(200, 1024, copy_rdm);

  plasma::CFARDetector2D cfarDetector(2, 4, 0.00001f);
  std::cout << af::sum<float>(cfarDetector.detect(RDM)) << std::endl;

  af::saveArray("", cfar(RDM), "/home/avery/Research  Folder/MatLab/cpp_detection");

  return 0;
}