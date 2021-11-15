#include <matplot/matplot.h>
#include <set>
#include <iostream>
#include "LinearFMWaveform.h"
#include "SquareWaveform.h"

int main() {
  using namespace matplot;
  // auto wave = SquareWaveform(100e-6,1e3,20e6);
  auto wave = LinearFMWaveform(10e6,100e-6,1e3,20e6);
  wave.pulsewidth(500e-6);
  auto data = wave.sample();
  std::vector<float> data_real(data.size());
  for (size_t i = 0; i < data.size(); i++) {
    data_real[i] = data[i].real();
  }
  plot(data_real);
  show();
  return 0;
}