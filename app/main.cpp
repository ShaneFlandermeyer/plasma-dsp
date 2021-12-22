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
  std::vector<double> prf = {1e3};
  auto sampRate = 20e6;
  auto code = PhaseCode::generate_code(PhaseCode::BARKER, 13);
  // auto code = std::vector<double>(13,1);
  auto filter = rectangular(3);
  // auto wave = PCFMWaveform(code, filter);
  auto wave = LinearFMWaveform(bandwidth, pulsewidth, prf, sampRate);
  auto pulse = wave.pulse();
  pulse = fftshift(fft(pulse));
  std::vector<double> mag;
  for (auto x : pulse) mag.push_back(std::abs(x));
  
  plot(db(mag));
  // plot(mag);
  show();
  // std::vector<std::complex<double>> pulse2;
  

  return 0;
}