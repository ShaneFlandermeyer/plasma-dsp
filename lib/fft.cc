#include "fft.h"

namespace plasma {
template <class T> FFT<T>::FFT() { std::cout << "TODO: Default constructor" << std::endl; }

template <class T> FFT<T>::~FFT() {
  std::cout << "TODO: Destructor" << std::endl;
}

template <class T> FFT<T>::FFT(size_t fft_size, size_t num_threads) {
  std::cout << "TODO: Constructor" << std::endl;
}

template <class T>
void FFT<T>::execute() {
std::cout << "TODO: Execute FFT" << std::endl;
}

template class FFT<std::complex<float>>;
template class FFT<float>;

} // namespace plasma
