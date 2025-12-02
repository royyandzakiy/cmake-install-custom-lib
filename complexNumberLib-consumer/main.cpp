#include <iostream>
#include "complexNumberLib/complexNumbers.hpp"

int main() {
  ComplexNumber a(2, 3);
  ComplexNumber b(4, 5);

  ComplexNumber c = a + b;
  ComplexNumber d = a - b;
  ComplexNumber e = a * b;
  ComplexNumber f = a / b;

  std::cout << c << std::endl;
  std::cout << d << std::endl;
  std::cout << e << std::endl;
  std::cout << f << std::endl;

  return 0;
}