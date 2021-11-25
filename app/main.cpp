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
  auto prf = {10e3};
  auto sampRate = 20e6;

  auto wave = LinearFMWaveform(bandwidth, pulsewidth, prf, sampRate);
  auto data = wave.step();
  
  
  // Short time fourier transform equation
  auto noverlap = 64;
  auto nfft = 256;
  auto win = window::hamming(nfft);
  auto spectro = spectrogram(data,win,nfft,noverlap);
  image(spectro);
  colorbar();
  show();
  return 0;
}