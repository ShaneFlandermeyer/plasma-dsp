#include "fft.h"
#include "optimization.h"
#include "pcfm.h"
#include "window.h"
#include <iostream>
#include <arrayfire.h>

using namespace plasma;
int main() {
  // Generate the initial PCFM waveform (which does not fit the template)
  double samp_rate = 100e6;
  int num_chips = 512;
  int num_over = 4;
  int num_samp_waveform = (num_chips - 1) * num_over;
  af::array chips = (2 * af::Pi) * af::randu(num_chips) - af::Pi;
  af::array shape_filt = window::rectangular(num_over) / (float)num_over;
  PCFMWaveform waveform(chips, shape_filt, samp_rate);
  af::array samples = waveform.sample();
  // af::array waveform_freq = fftshift(fft(samples));

  // Create the desired spectral template
  int num_samp_conv = 2 * num_samp_waveform - 1;
  double alpha = 10;
  af::array spectrum_template = window::gaussian(num_samp_conv, alpha).as(f32);

  // Optimize the waveform
  int num_zero = num_samp_conv - num_samp_waveform;
  samples = af::join(0, samples, af::constant(0, num_zero, samples.type()));

  // Do alternating projections
  af::array p = samples.as(c32);
  af::array r(p.elements(),c32);
  af::timer start = af::timer::start();
  for (int i = 0; i < 5; i++) {
    r = ifft(ifftshift(abs(spectrum_template) *
                       exp(af::Im * arg(fftshift(fft(p))))));
    p = exp(af::Im * arg(r));
  }
  std::cout << af::timer::stop(start) << std::endl;
  af::array result = p;
  af::array result_freq = fftshift(fft(p));
  result_freq = result_freq / af::tile(af::max(abs(result_freq)),result_freq.elements());
  af::array result_db = 20 * log10(abs(result_freq)).as(f32);
  // Plots
  af::Window win;
  af::array freq_axis =
      -0.5 * samp_rate + af::range(num_samp_conv) * samp_rate / num_samp_conv;
  af::array xlim = {af::min<float>(freq_axis), af::max<float>(freq_axis)};
  af::array ylim = {af::min<float>(result_db), af::max<float>(result_db)};
  win.setAxesLimits(xlim, ylim, true);
  while (!win.close()) {
    win.plot(freq_axis, result_db);
    win.plot(freq_axis, 20*log10(abs(spectrum_template)));
    win.show();
  }
  // while (not win.close()) win.show();
  return EXIT_SUCCESS;
}
