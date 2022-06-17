#ifndef AE8E5373_5A3D_4171_84AA_E93906C328FD
#define AE8E5373_5A3D_4171_84AA_E93906C328FD

#include <fstream>
#include <string>
#include <vector>

namespace plasma {
template <typename T>
std::vector<T> read(const std::string &filename, size_t offset = 0,
                    int nitems = -1) {
  std::ifstream infile(filename, std::ios::in | std::ios::binary);
  infile.seekg(0, std::ios::end);
  size_t nbytes;
  if (nitems == -1) {
    nbytes = infile.tellg();
    nitems = nbytes / sizeof(T);
  } else {
    nbytes = nitems * sizeof(T);
  }

  infile.seekg(offset, std::ios::beg);

  std::vector<T> data(nitems);
  infile.read(reinterpret_cast<char *>(data.data()), nbytes);
  infile.close();
  return data;
}
} // namespace plasma

#endif /* AE8E5373_5A3D_4171_84AA_E93906C328FD */
