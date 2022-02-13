#include "pulse_doppler.h"
#include "linear_fm_waveform.h"
#include <matplot/matplot.h>

int main() {
  double B = 50e6;
  double fs = 4*B;
  double Tp = 5e-6;
  double prf = 10e3;
  plasma::LinearFMWaveform wave(B, Tp, prf,fs);
  Eigen::VectorXcd x = wave.waveform();
  
  // Eigen::VectorXcd y = plasma::delay(x,5e-6,(size_t)(fs/prf),fs);
  Eigen::VectorXcd h = x.reverse().conjugate();
  // Compute the matched filter response
  Eigen::VectorXcd y = plasma::conv(x,h);
  
  std::vector<double> xv(y.size());
  for (size_t i = 0; i < y.size(); i++) {
    xv[i] = 10*log10(abs(y(i)));
  }
  matplot::plot(xv);
  matplot::show();

  return 0;
  

}