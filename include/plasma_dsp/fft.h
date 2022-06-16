#ifndef EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4
#define EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4

#include <complex>
#include <iostream>
#include <Eigen/Dense>

namespace plasma {
/*!
\brief FFT: templated
\ingroup misc
*/

template <class T, bool forward> struct fft_input { typedef T type; };

template <> struct fft_input<float, false> {
  typedef std::complex<float> type;
};

template <class T, bool forward> struct fft_output { typedef T type; };

template <> struct fft_output<float, true> {
  typedef std::complex<float> type;
};

/**
 * @brief Class implementing a 1D FFT/IFFT.
 *
 * This is basically identical to the fft class in gnuradio's gr-fft, but
 * without the gnuradio-specific stuff.
 *
 * @tparam T The input data type if a forward FFT is performed, and the output
 * type if a reverse FFT is performed
 * @tparam forward If true, the object computes a forward FFT. If false, it
 * computes an IFFT
 */

template <class T, bool forward> class FFT {
  /**
   * @brief Number of threads to use in the computation
   *
   */
  size_t d_num_threads;

  /**
   * @brief FFT size
   *
   */
  size_t d_size;

  /**
   * @brief Input array
   *
   */
  Eigen::ArrayX<typename fft_input<T, forward>::type> d_input;

  /**
   * @brief Output array
   *
   */
  Eigen::ArrayX<typename fft_output<T, forward>::type> d_output;

  /**
   * @brief FFTW plan
   *
   */
  void *d_plan;

  /**
   * @brief Create a plan based on the size, data type, and FFT direction
   *
   * @param fft_size
   */
  void initialize_plan(size_t fft_size);

public:
  FFT(size_t fft_size, size_t nthreads = 1);
  virtual ~FFT();

  /**
   * @brief Get a pointer to the input buffer
   *
   * @return fft_input<T, forward>::type*
   */
  fft_input<typename fft_input<T, forward>::type, forward>::type *input() {
    return d_input.data();
  }

  /**
   * @brief Set the data in the input array
   *
   * @param input
   */
  void input(typename fft_input<T, forward>::type *input) {
    memcpy(d_input.data(), input,
           sizeof(typename fft_input<T, forward>::type) * d_size);
  }

  /**
   * @brief Get a pointer to the output array
   *
   * @return fft_output<T, forward>::type*
   */
  fft_output<T, forward>::type *output() { return d_output.data(); }
  
  int input_length() const { return d_input.size(); }
  int output_length() const { return d_output.size(); }

  /*!
   * compute FFT. The input comes from input, the output is placed in
   * output.
   */
  void execute();
};

// /**
//  * @brief Template class for performing FFTs on floating point data.
//  *
//  * This implementation is basically a copy-paste version of the
//  implementation
//  * in gr-fft
//  *
//  * @tparam T Input data type (float or std::complex<float>)
//  */
// template <class T, bool forward> class FFT {
// private:
//   size_t d_num_threads;
//   size_t d_size;
//   Eigen::ArrayX<T> d_input;
//   Eigen::ArrayX<T> d_output;
//   void *d_plan;

// public:
//   FFT(size_t fft_size, size_t num_threads = 1);
//   ~FFT();
//   void execute();

//   T *input() { return d_input.data(); }
//   void input(T *input) { memcpy(d_input.data(), input, sizeof(T) * d_size);
//   } T *output() { return d_output.data(); } void output(T *output) {
//     memcpy(output, d_output.data(), sizeof(T) * d_size);
//   }
// };

} // namespace plasma

#endif /* EC275AD1_95A7_4FBB_8EA1_60DE4E47A9A4 */
