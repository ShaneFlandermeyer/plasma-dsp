#ifndef C8DA77F0_9C11_4535_8359_C56C62F68E47
#define C8DA77F0_9C11_4535_8359_C56C62F68E47

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace plasma {
/**
 * @brief Phase code generator object
 *
 */
class PhaseCode {
 public:
  /**
   * Enumeration of supported phase code types
   *
   */
  enum codeType {
    /**
     * Barker code 
     * 
     */
    BARKER,
    /**
     * Frank code
     * 
     */
    FRANK,
    /**
     * Arbitrary (currently invalid) code type
     * 
     */
    GENERIC = 999
  };

  /**
   * @brief Return the phase values of a phase code of length n
   *
   * @param type Code type
   * @param n Code length
   * @return std::vector<double> Phase code vector
   */
  static std::vector<double> generate_code(codeType type, int n);
};
}  // namespace plasma
#endif /* C8DA77F0_9C11_4535_8359_C56C62F68E47 */
