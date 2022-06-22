#ifndef EBEAFD6D_40A7_48F8_92DE_479CA3BF6A58
#define EBEAFD6D_40A7_48F8_92DE_479CA3BF6A58

#include <algorithm>
#include <cassert>
#include <vector>

namespace plasma {

/**
 * @brief Shift zero-frequency component to center of spectrum
 *
 * This is a near exact copy of fft_shift.h from GNU Radio
 *
 * @tparam T Input array data type
 */
template <typename T> class fftshift {

public:
  /**
   * @brief Construct a new fftshift object
   *
   * @param len FFT length
   */
  fftshift(size_t len)
      : d_len(len), d_lenpos(len / 2 + (len % 2)), d_lenneg(len / 2),
        d_buf(len) {}

  /**
   * @brief Perform an fftshift on vector v
   * 
   * @param v 
   */
  void shift(std::vector<T> &v) { shift(&v.front(), v.size()); }

  /**
   * @brief Perform fftshift on an array pointer
   * 
   * @param data Pointer to input array
   * @param len Number of array elements
   */
  void shift(T *data, size_t len) {
    resize(len);
    std::copy_n(data, d_lenpos, d_buf.begin());
    std::copy_n(data + d_lenpos, d_lenneg, data);
    std::copy_n(d_buf.begin(), d_lenpos, data + d_lenneg);
  }

  void resize(size_t len) {
    if (d_len == len)
      return;
    d_len = len;
    d_lenpos = d_len / 2 + (d_len % 2);
    d_lenneg = d_len / 2;
    assert(d_lenpos + d_lenneg == d_len);
    d_buf.resize(d_lenpos);
  }

private:
  // FFT length
  size_t d_len;
  // Number of positive-frequency bins
  size_t d_lenpos;
  // Number of negative frequency bins
  size_t d_lenneg;
  // Cyclic shift buffer
  std::vector<T> d_buf;
};

} // namespace plasma

#endif /* EBEAFD6D_40A7_48F8_92DE_479CA3BF6A58 */
