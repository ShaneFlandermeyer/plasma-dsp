#ifndef C8DA77F0_9C11_4535_8359_C56C62F68E47
#define C8DA77F0_9C11_4535_8359_C56C62F68E47

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace plasma {
class PhaseCode {
 public:
  enum codeType { BARKER, GENERIC = 999 };

  /**
   * @brief Return the phase values of a phase code of length n
   *
   * @param type The phase code type
   * @param n The code length
   * @return std::vector<double> The phase code vector
   */
  static std::vector<double> generate_code(codeType type, int n);
};
}  // namespace plasma
#endif /* C8DA77F0_9C11_4535_8359_C56C62F68E47 */
