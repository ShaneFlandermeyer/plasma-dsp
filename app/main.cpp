#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "LinearFMWaveform.h"
#include "SquareWaveform.h"

using namespace matplot;
int main() {
  std::vector<double> prf = {1e3, 5e3, 10e3};
  // auto wave = SquareWaveform(100e-6, prf, 20e6);
  auto wave = LinearFMWaveform(10e6,100e-6,prf,20e6);
  // wave.pulsewidth(500e-6);
  // auto data = wave.sample();

  auto data = wave.getWaveform();
  std::vector<float> data_real(data.size());
  for (size_t i = 0; i < data.size(); i++) {
    data_real[i] = data[i].real();
  }
  plot(data_real);
  show();
  return 0;
}