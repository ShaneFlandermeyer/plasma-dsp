#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "linearfmwaveform.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "window.h"
#include "utils.h"

using namespace matplot;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  auto prf = {1e3};
  auto sampRate = 20e6;

  auto wave = LinearFMWaveform(bandwidth, pulsewidth, prf, sampRate);
  auto data = wave.step();

  auto freq = fft(data);
  freq = fftshift(freq);
  auto freqdb = std::vector<double>(freq.size());
  std::transform(freq.begin(),freq.end(),freqdb.begin(),[](std::complex<double> &x){return 10*std::log10(std::abs(x));});
  plot(freqdb);
  show();
  
  return 0;
}