#include <matplot/matplot.h>

#include <iostream>
#include <set>


#include "barkercode.h"
#include "linearfmwaveform.h"
#include "phasecode.h"
#include "spectrogram.h"
#include "squarewaveform.h"
#include "pcfm.h"
#include "utils.h"
#include "window.h"

using namespace matplot;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  std::vector<double> prf = {1e3};
  auto sampRate = 20e6;
  auto code = PhaseCode::generate_code(PhaseCode::BARKER, 13);
  // auto code = std::vector<double>(13,1);
  auto filter = window::rectangular(3);
  auto wave = PCFMWaveform(code, filter);
  auto pulse = wave.pulse();
  // auto real = std::vector<double>(pulse.size());
  // std::transform(pulse.begin(), pulse.end(), real.begin(),
  //                [](auto x) { return std::real(x); });

  // plot(real);
  // auto x = fft(std::vector<double>(2,2));
  // for (int i = 0; i < x.size(); i++) {
  //   std::cout << x[i] << std::endl;
  // }
  // show();
  // std::vector<double> x(10,1);
  // std::vector<double> g(3,1);
  // std::vector<double> train(3*10,0);
  // for (int i = 0; i < x.size(); i++) train[i*3] = x[i];
  // plot(filt(g,{1},train));
  // show();
  
  return 0;
}