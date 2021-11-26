#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "linearfmwaveform.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "utils.h"
#include "window.h"

using namespace matplot;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  auto prf = {10e3};
  auto sampRate = 20e6;
  auto wave = LinearFMWaveform(bandwidth, pulsewidth, prf, sampRate);
  auto x = wave.step();
  // auto dt = 0.001;
  // auto f0 = 50;
  // auto f1 = 250;
  // auto t1 = 2;
  // auto x = std::vector<double>();
  // for (double t = 0; t < t1; t += dt) {
  //   x.push_back(
  //       cos(2 * M_PI * t * (f0 + (f1 - f0) * pow(t, 2) / (3 * pow(t1, 2)))));
  // }
  // plot(x);
  // show();

  // Short time fourier transform equation
  auto noverlap = 64;
  auto nfft = 256;
  auto win = window::hamming(nfft);
  auto spectro = spectrogram(x, win, nfft, noverlap);
  image(spectro);
  colorbar();
  show();
  return 0;
}