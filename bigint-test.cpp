#include "bigint.h"

int main(void) {
  BigInt i = "12419285192019238102980198";
  std::cout << "i = " << i << std::endl;

  std::vector<uint8_t> v = BigInt::to_bytes(i);

  BigInt j = BigInt::from_bytes(v);
  std::cout << "j = " << j << std::endl;

  for (int i = 2; i < 16; i += 1) {
    std::cout << j.str_in_base(i) << std::endl;
  }

  return 0;
}
