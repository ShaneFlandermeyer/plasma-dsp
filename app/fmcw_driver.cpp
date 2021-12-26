/**
 * Created on Sun Dec 26 2021
 *
 * Shane Flandermeyer, shaneflandermeyer@gmail.com
 *
 * Implementation of [Automotive Adaptive Cruise Control Using FMCW
 * Technology](https://www.mathworks.com/help/radar/ug/automotive-adaptive-cruise-control-using-fmcw-technology.html)
 */

#include <matplot/matplot.h>

#include <iostream>

#include "fmcwwaveform.h"
#include "spectrogram.h"
#include "vector-utils.h"
#include "window.h"

using namespace plasma;
using namespace matplot;

int main() {
  auto fc = 77e9;
  auto c = 3e8;
  auto lambda = c / fc;
  auto range_max = 200;
  // Sweep time should be 5-6 times the round trip time (i.e., the time for
  // needed for the signal to travel the maximum unambiguous range)
  auto tm = 5.5 * 2 * range_max / c;
  // Sweep bandwidth can be determined in terms of desired range resoultion
  // Slope can be determined simply as bw/time
  auto range_res = 1;
  auto bw = c / (2 * range_res);
  auto sweep_slope = bw / tm;
  /* Since we downconvert the high-bandwidth sweep to a beat waveform, we only
  need to sample at twice the bandwidth of this waveform. This frequency is
  the sum of the beat frequency corresponding to the maximum range and
  maximum doppler shift */
  // Beat frequency for the maximum range
  auto fr_max = 2 * range_max * sweep_slope / c;
  /* Beat frequency for the maximum doppler shift
  Assume the maximum speed of a car is 230 km/s */
  // Convert from km/hr to m/s
  auto v_max = 230 * 1000 / 3600;
  auto fd_max = 2 * v_max / lambda;
  auto fb_max = fr_max + fd_max;
  auto fs = std::max(2 * fb_max, bw);
  // Use the parameters above to create the FMCW waveform
  auto waveform =
      FMCWWaveform(tm, bw, fs, FMCWWaveform::SweepInterval::SYMMETRIC,
                   FMCWWaveform::SweepDirection::DOWN);
  auto sig = waveform.waveform();
  image(0, tm * 1e6, 0, fs / 1e6, spectrogram(sig, hamming(32), 32, 16), true);
  xlabel("Time (s)");
  ylabel("Frequency (MHz)");
  gca()->y_axis().reverse(false);
  show();

  return 0;
}
