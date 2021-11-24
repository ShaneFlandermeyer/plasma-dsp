#include <vector>
#include <complex>

/**
 * @brief Short-time Fourier transform (STFT)
 * 
 * @param x Input signal
 * @param fs Sample Rate
 * @param window Spectral window
 * @param nfft Number of DFT points
 * @param noverlap Number of overlapped samples
 */
void stft(std::vector<std::complex<double>> x, double fs, std::vector<double> window,
          int nfft, int noverlap);