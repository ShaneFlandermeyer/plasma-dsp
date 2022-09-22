#ifndef FAFECA4E_D8B7_473E_8886_1FAD2A379408
#define FAFECA4E_D8B7_473E_8886_1FAD2A379408

#include <vector>
#include <arrayfire.h>

namespace plasma {
  
template <typename T>
std::vector<T> to_vector(const af::array & in) {
  std::vector<T> out(in.elements());
  in.host(out.data());
  return out;
}

}

#endif /* FAFECA4E_D8B7_473E_8886_1FAD2A379408 */
