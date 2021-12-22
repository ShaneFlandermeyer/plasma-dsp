#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "barkercode.h"
#include "linearfmwaveform.h"
#include "pcfm.h"
#include "phasecode.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "utils.h"
#include "window.h"

using namespace matplot;
using namespace plasma;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  auto sampRate = 20e6;
  std::vector<double> prf = {10e3};
  auto wave = LinearFMWaveform(bandwidth, pulsewidth, prf, sampRate);
  // wave.freqOffset(5e6);
  auto pulse = wave.pulse();
  // pulse = fftshift(fft(pulse));
  std::vector<double> mag;
  for (auto x : pulse) mag.push_back(x.real());
  
  plot(mag);
  // plot(db(mag));
  show();
  // std::vector<std::complex<double>> pulse2;
  

  return 0;
}