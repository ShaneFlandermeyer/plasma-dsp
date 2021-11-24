#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "linearfmwaveform.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "window.h"

using namespace matplot;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  auto prf = {1e3, 5e3, 8e3};
  auto sampRate = 20e6;

  // auto wave = SquareWaveform(100e-6, prf, 20e6);
  auto wave = LinearFMWaveform(bandwidth, pulsewidth, prf, sampRate);
  auto data = wave.step();
  auto win = window::rectangular(data.size());

  stft(data,sampRate,win,512,220);

      // auto data = wave.step();
      // std::vector<float> data_real(data.size());
      // for (size_t i = 0; i < data.size(); i++) {
      //   data_real[i] = data[i].real();
      // }
      // plot(data_real);
      // show();
  plot(win);
  show();
  return 0;
}