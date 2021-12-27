#ifndef F49FC95E_8968_41E0_96E1_16209F637F93
#define F49FC95E_8968_41E0_96E1_16209F637F93

#include <fftw3.h>
#include <matplot/matplot.h>

#include <complex>
#include <iostream>
#include <vector>

#include "signal-processing.h"
#include "vector-utils.h"

namespace plasma {
using namespace Eigen;
/**
 * @brief Short-time Fourier transform (STFT)
 *
 * This function currently computes the two-sided STFT over the interval
 * [0,2*pi) rad/sample.
 *
 * TODO: Extend this to centered and one-sided transforms as well
 *
 * @tparam T1 Input signal data type
 * @tparam T2 Window data type
 * @param x Input signal
 * @param window Spectral window
 * @param num_fft Number of DFT points
 * @param num_overlap Number of overlapped samples
 */
template <typename T1, typename T2>
std::vector<std::vector<std::complex<double>>> stft(
    const std::vector<T1> &signal, const std::vector<T2> &window,
    const int num_fft, const int num_overlap) {
  // Hop size between successive DFTs
  auto hop_size = window.size() - num_overlap;
  // Number of columns in the DFT matrix
  auto num_col = (int)floor((signal.size() - num_overlap) / hop_size);
  // STFT matrix
  std::vector<std::vector<std::complex<double>>> stft(
      num_col, std::vector<std::complex<double>>(num_fft));
  // Vector of windowed segment samples
  std::vector<T1> xi(num_fft);
  for (auto i_col = 0; i_col < num_col; i_col++) {
    // Compute the windowed time segment and store its frequency spectrum in the
    // stft matrix
    std::transform(signal.begin() + i_col * hop_size,
                   signal.begin() + i_col * hop_size + window.size(),
                   window.begin(), xi.begin(), std::multiplies<T1>());
    stft[i_col] = fft(xi);
  }
  return stft;
}

/**
 * @brief Plot the spectrogram (frequency vs. time) of a signal
 *
 * @tparam T Input type
 * @param x Input signal
 * @param window Spectral window
 * @param num_fft Number of DFT points
 * @param num_overlap Number of overlapped samples
 */
template <typename T1, typename T2>
std::vector<std::vector<double>> spectrogram(const std::vector<T1> &x,
                                             const std::vector<T2> &window,
                                             const int num_fft,
                                             const int num_overlap) {
  std::vector<std::vector<std::complex<double>>> stft_mat =
      stft(x, window, num_fft, num_overlap);
  // The spectrogram is the magnitude squared of the STFT matrix
  auto spectro = std::vector<std::vector<double>>(
      stft_mat.size(), std::vector<double>(stft_mat.front().size()));
  for (int i_row = 0; i_row < stft_mat.size(); i_row++) {
    std::transform(stft_mat[i_row].begin(), stft_mat[i_row].end(),
                   spectro[i_row].begin(),
                   [](const auto &x) { return pow(abs(x), 2); });
  }
  return matplot::transpose(spectro);
}

}  // namespace plasma

#endif /* F49FC95E_8968_41E0_96E1_16209F637F93 */
