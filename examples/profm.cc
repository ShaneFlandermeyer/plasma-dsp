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
  int num_over = 8;
  int num_samp_waveform = (num_chips - 1) * num_over;
  af::array chips = (2 * af::Pi) * af::randu(num_chips) - af::Pi;
  af::array shape_filt = window::rectangular(num_over) / (float)num_over;
  PCFMWaveform waveform(chips, shape_filt, samp_rate);
  af::array samples = waveform.sample();
  // af::array waveform_freq = fftshift(fft(samples));

  // Create the desired spectral template
  int num_samp_conv = 2 * num_samp_waveform - 1;
  double alpha = 15;
  af::array spectrum_template = window::gaussian(num_samp_conv, alpha).as(f32);

  spectrum_template(20 * log10(abs(spectrum_template)) < -50) =
      pow(10, -50 / 20);

  // Optimize the waveform using alternating projections
  int num_zero = num_samp_conv - num_samp_waveform;
  samples = af::join(0, samples, af::constant(0, num_zero, samples.type()));

  // Do alternating projections and plot the resulting PSD on top of the
  // template
  af::Window win;
  af::array freq_axis =
      -0.5 * samp_rate + af::range(num_samp_conv) * samp_rate / num_samp_conv;
  af::array xlim = {af::min<float>(freq_axis), af::max<float>(freq_axis)};
  af::array ylim = {-50, 0};
  win.grid(1, 1);
  win(0, 0).setAxesLimits(xlim, ylim, true);
  af::array p = profm(samples, spectrum_template, 5);
  // Convert to dB and normalize
  af::array result_db = 20 * log10(abs(fftshift(fft(p)))).as(f32);
  result_db -= af::max<float>(result_db);
  do {
    win(0, 0).plot(freq_axis, result_db);
    win(0, 0).plot(freq_axis, 20 * log10(abs(spectrum_template)));
    win.show();
  } while (not win.close());

  return EXIT_SUCCESS;
}
