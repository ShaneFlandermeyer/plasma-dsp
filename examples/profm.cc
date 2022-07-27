#include "fft.h"
#include "optimization.h"
#include "pcfm.h"
#include "window.h"
#include <iostream>
#include <arrayfire.h>

using namespace plasma;
int main() {
  // Generate the initial PCFM waveform (which does not fit the template)
  double samp_rate = 10e6;
  size_t num_chips = 128;
  size_t num_over = 4;
  size_t num_samps = (num_chips - 1) * num_over;
  af::array chips = (2 * af::Pi) * af::randu(num_chips) - af::Pi;
  af::array filter = rectangular(num_over) / (float)num_over;
  PCFMWaveform waveform(chips, filter, samp_rate);
  af::array st = waveform.sample();
  af::array sf = fftshift(fft(st));

  // Create the desired spectral template
  

  //
  af::Window win;
  af::array samp_axis = af::range(num_samps);
  af::array freq_axis = -0.5*samp_rate + af::range(num_samps)*samp_rate/num_samps;
  while (!win.close()) {
    win.plot(freq_axis, 20 * log10(abs(sf)).as(f32));
    win.show();
  }
}
