#include "PulsedWaveform.h"

#include <iostream>
#include <numeric>

std::vector<std::complex<double>> PulsedWaveform::getWaveform() {
  // Compute a vector of PRIs
  std::vector<double> pri;
  std::transform(d_prf.begin(), d_prf.end(), std::back_inserter(pri),
                 [](double prf) { return 1 / prf; });
  // Total time duration of the waveform
  auto duration = std::accumulate(pri.begin(), pri.end(), 0.0);
  // Total number of samples in the PRF schedule
  auto nSampsTotal = static_cast<int>(duration * d_sampRate);
  std::vector<std::complex<double>> wave(nSampsTotal);
  // Store the sample rate in a separate variable for lambda functions
  auto sampRate = d_sampRate;
  // Number of samples for every PRI
  std::vector<int> nSampsPri(pri.size());
  // Compute the number of samples per pulse in each PRI
  std::transform(pri.begin(), pri.end(), nSampsPri.begin() + 1,
                 [&sampRate](auto& pri) { return pri * sampRate; });
  // Compute a cumulative sum of the number of samples per pulse to get the
  // start indices for each pulse
  std::vector<int> startIndex(pri.size());
  std::partial_sum(nSampsPri.begin(), nSampsPri.end(), startIndex.begin(),
                   std::plus<int>());
  // Assign values to the nonzero indices
  // TODO: Investigate std::generate for this
  for (int index : startIndex) {
    auto data = sample();
    auto nSampsPulse = data.size();
    for (int ii = 0; ii < nSampsPulse; ii++) {
      wave[index + ii] = data[ii];
    }
  }

  return wave;
}