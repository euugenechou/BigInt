#include "bigint.h"
#include <iostream>

int main(void) {
  std::cout << std::boolalpha;

  BigInt i = 5;
  BigInt j = 13;

  std::cout << "i = " << i << std::endl;
  std::cout << "j = " << j << std::endl;
  std::cout << "i.invm(j) = " << i.invm(j) << std::endl;
  std::cout << "i.sqrtm(11) = " << i.sqrtm(11) << std::endl;

  return 0;
}
