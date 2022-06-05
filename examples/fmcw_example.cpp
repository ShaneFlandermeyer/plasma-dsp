/**
 * Created on Sun Dec 26 2021
 *
 * Shane Flandermeyer, shaneflandermeyer@gmail.com
 *
 * Implementation of [Automotive Adaptive Cruise Control Using FMCW
 * Technology](https://www.mathworks.com/help/radar/ug/automotive-adaptive-cruise-control-using-fmcw-technology.html)
 */

#include <unsupported/Eigen/FFT>

#include <iostream>

#include "fmcw_waveform.h"
#include "spectrogram.h"
#include "vector_utils.h"
#include "window.h"

using namespace plasma;
using namespace matplot;
using namespace Eigen;

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
      FMCWWaveform(tm, bw, fs, FMCWWaveform::SweepInterval::POSITIVE,
                   FMCWWaveform::SweepDirection::UP);
  auto sig = waveform.waveform();
  std::string path = "/home/shane/sig.dat";
  auto dechirped = waveform.demod(sig);
  auto dechirped_vec = std::vector<std::complex<double>>(
      dechirped.data(), dechirped.data() + dechirped.size());
  FFT<double> fft;
  std::vector<std::complex<double>> sig_fft;

  fft.fwd(sig_fft, dechirped_vec);

  auto freq_axis = linspace(-fs / 2, fs / 2, dechirped.size());
  // auto sigf = std::vector<std::complex<float>>(sig.size());
  // std::transform(sig.begin(),sig.end(),sigf.begin(),[](auto x){return
  // (std::complex<float>)x;}); write_binary(path,sigf);

  return 0;
}
