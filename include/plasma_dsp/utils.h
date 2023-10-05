#ifndef FAFECA4E_D8B7_473E_8886_1FAD2A379408
#define FAFECA4E_D8B7_473E_8886_1FAD2A379408

#include <vector>
#include <arrayfire.h>

namespace plasma {
  
af::array pad(af::array x, size_t pad_width, double value = 0);

}

#endif /* FAFECA4E_D8B7_473E_8886_1FAD2A379408 */
