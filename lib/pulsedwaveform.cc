#include "pulsedwaveform.h"

#include <iostream>
#include <numeric>

namespace plasma {
PulsedWaveform::PulsedWaveform() : Waveform() {
  d_prf = std::vector<double>();
  d_pulsewidth = 0;
}

PulsedWaveform::PulsedWaveform(double pulsewidth, double prf) {
  d_pulsewidth = pulsewidth;
  d_prf = {prf};
}

PulsedWaveform::PulsedWaveform(double pulsewidth, std::vector<double> prf) {
  d_pulsewidth = pulsewidth;
  d_prf = prf;
}

std::vector<std::complex<double>> PulsedWaveform::pulse() {
  // Compute a vector of PRIs
  std::vector<double> pri;
  std::transform(d_prf.begin(), d_prf.end(), std::back_inserter(pri),
                 [](double prf) { return 1 / prf; });
  // Store the sample rate in a separate variable for lambda functions
  auto samp_rate = d_samp_rate;
  // Number of samples for every PRI
  std::vector<int> num_samps_pri(pri.size());
  // Compute the number of samples per pulse in each PRI
  std::transform(pri.begin(), pri.end(), num_samps_pri.begin() + 1,
                 [&samp_rate](auto& pri) { return pri * samp_rate; });
  // Compute a cumulative sum of the number of samples per pulse to get the
  // start indices for each pulse
  std::vector<int> start_index(pri.size());
  std::partial_sum(num_samps_pri.begin(), num_samps_pri.end(), start_index.begin(),
                   std::plus<int>());
  // Assign values to the nonzero indices
  // Total time duration of the waveform
  auto duration = std::accumulate(pri.begin(), pri.end(), 0.0);
  // Total number of samples in the PRF schedule
  auto nSampsTotal = static_cast<int>(duration * d_samp_rate);
  std::vector<std::complex<double>> wave(nSampsTotal);
  // Generate the waveform
  for (int index : start_index) {
    auto data = waveform();
    auto nSampsPulse = data.size();
    for (int ii = 0; ii < nSampsPulse; ii++) {
      wave[index + ii] = data[ii];
    }
  }

  return wave;
}
}  // namespace plasma