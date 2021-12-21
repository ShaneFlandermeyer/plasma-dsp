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
using namespace plasma;
int main() {
  auto bandwidth = 10e6;
  auto pulsewidth = 100e-6;
  std::vector<double> prf = {1e3};
  auto sampRate = 20e6;
  auto code = PhaseCode::generate_code(PhaseCode::BARKER, 13);
  // auto code = std::vector<double>(13,1);
  auto filter = rectangular(3);
  auto wave = PCFMWaveform(code, filter);
  auto pulse = wave.pulse();
  
  auto y = PhaseCode::generate_code(PhaseCode::FRANK,16);
  std::for_each(y.begin(),y.end(),[](auto& x){std::cout << x << std::endl;});
  
  return 0;
}