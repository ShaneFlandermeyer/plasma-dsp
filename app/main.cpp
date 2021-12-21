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
  auto fPulse = fftshift(fft(pulse));
  // std::vector<std::complex<double>> pulse2;
  auto pulse2 = ifft<std::complex<double>>(fft(pulse));
  std::vector<double> r1, r2;
  for (int i = 0; i < pulse.size(); i++) {
    r1.push_back(pulse[i].real());
    r2.push_back(pulse2[i].real());
  }

  plot(r1);
  plot(r2);
  show();

  auto N = 10;
  auto over = 3;
  auto a_code = std::vector<double>(N, 1);
  auto g = std::vector<double>(over, 1);
  auto y = conv(a_code, g);
  std::vector<double> y2;
  std::for_each(y.begin(), y.end(),
                [](auto& x) { std::cout << x << std::endl; });
  // auto fy = fft(y);
  // ifft(fy, fy);

  return 0;
}