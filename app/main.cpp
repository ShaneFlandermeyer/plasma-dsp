#include <matplot/matplot.h>

#include <iostream>
#include <set>

#include "plasma-dsp/barkercode.h"
#include "plasma-dsp/linearfmwaveform.h"
#include "plasma-dsp/phasecode.h"
#include "plasma-dsp/spectrogram.h"
#include "plasma-dsp/squarewaveform.h"
#include "plasma-dsp/utils.h"
#include "plasma-dsp/window.h"

using namespace matplot;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  std::vector<double> prf = {10e3};
  auto sampRate = 20e6;
  auto wave = LinearFMWaveform(bandwidth, pulsewidth, prf, sampRate);
  auto x = wave.pulseTrain();
  auto barker = BarkerCode(13, pulsewidth / 13, prf, sampRate);
  auto pulse = barker.pulse();
  auto real = std::vector<double>(pulse.size());
  std::transform(pulse.begin(), pulse.end(), real.begin(),
                 [](auto x) { return std::real(x); });
  // for (auto x : pulse) std::cout << x << std::endl;
  // plot(real);
  // show();

  // auto dt = 0.001;
  // auto f0 = 50;
  // auto f1 = 250;
  // auto t1 = 2;
  // auto x = std::vector<double>();
  // for (double t = 0; t < t1; t += dt) {
  //   x.push_back(
  //       cos(2 * M_PI * t * (f0 + (f1 - f0) * pow(t, 2) / (3 * pow(t1, 2)))));
  // }

  // Short time fourier transform equation
  auto noverlap = 120;
  auto nfft = 128;
  auto win = window::hamming(nfft);
  auto spectro = spectrogram(x, win, nfft, noverlap);
  image(spectro, true);
  colorbar();
  show();
  return 0;
}