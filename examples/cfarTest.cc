#include "plasma_dsp/file.h"
#include <fstream>
#include <iostream>
#include <arrayfire.h>
#include <numeric>

// class cfarTest {
// public:
//   cfarTest(size_t num_guard, size_t num_train, float pfa);
//   ~cfarTest();

//   void detect(af::array &x);

// private:
//   int _guard_num;
//   int _train_num;
//   float _pfa;

//   std::vector<std::vector<int>> detections;

//   void detect(af::array &x, int cut_row, int cut_col);
// };

// cfarTest::cfarTest(size_t num_guard, size_t num_train, float pfa) {
//   _guard_num = num_guard;
//   _train_num = num_train;
//   _pfa = pfa;
// }

// void cfarTest::detect(af::array &x) {
//   for (int i = 0; i < x.dims(0); ++i) {
//     for (int j = 0; j < x.dims(1); ++j) {
//       detect(x, i, j);
//     }
//   }
// }

af::array cfar(af::array rdm) {
  // Hardcode CFAR parameters
  int cfarR_guard = 2;
  int cfarR_train = 4;
  int cfarD_guard = 2;
  int cfarD_train = 4;

  float pfa = 0.001f;

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

  af::array detections = rdm > power * alpha;
  // af_print(detections);

  return detections;

  // Return boolean matrix
  // Once that works, update detectionreport class and return indices as well
}

int main() {
  std::string filename = "/home/avery/Research  Folder/MatLab/rangeDopplerMap";
  std::vector<double> rdm = plasma::read<double>(filename);
  float copy_rdm[rdm.size()/2];
  int vector_index = 0;
  for(int i=0; i<rdm.size()/2; ++i){
    copy_rdm[i] = rdm[vector_index];
    vector_index = vector_index + 2;
  }
  af::array RDM(200, 1024, copy_rdm);

  std::cout << af::sum<int>(cfar(RDM)) << std::endl;

  return 0;
}