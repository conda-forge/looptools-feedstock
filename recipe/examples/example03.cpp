// Uses the C++ standard library, so can only be linked by the C++ compiler.
// example01.cpp does not, so it also links with the C compiler.
#include <cmath>
#include <iostream>
#include <vector>
#include "clooptools.h"

int main() {
  int failed = 0;
  ltini();

  // B0 is symmetric in the two masses
  const std::vector<double> momenta2 = {100., 1000., 10000.};
  for (const double p2 : momenta2) {
    const ComplexType value = B0(p2, 50., 100.);
    const ComplexType swapped = B0(p2, 100., 50.);
    std::cout << "B0(" << p2 << ", 50, 100) = " << value << std::endl;
    if (!(std::abs(value - swapped) <= 1e-12 * std::abs(value))) {
      std::cout << "FAILED: B0 is not symmetric in the masses" << std::endl;
      failed = 1;
    }
  }

  ltexi();
  return failed;
}
