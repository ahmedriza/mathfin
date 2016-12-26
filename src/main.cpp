#include <config.h>
#include <iostream>

int main() {
  std::cout << "Hello" << std::endl;
  std::cout << "This is " << PACKAGE_STRING << "." << std::endl;
  return 0;
}
