// The five-point functions for complex parameters, which use more of LoopTools
// and of the Fortran runtime than the functions for real parameters in example01.
#include <math.h>
#include <stdio.h>
#include "clooptools.h"

// 2 -> 3 scattering of massless particles at sqrt(s) = 500
#define MOMENTA 0, 0, 0, 0, 0, 250000, -12239.172, 150000, 25000, -31183.285

static void print(const char *label, ComplexType value) {
  printf("%-22s %.17g%+.17gi\n", label, Re(value), Im(value));
}

int main() {
  int failed = 0;
  ltini();

  // For real masses the functions for complex parameters hand over to the
  // functions for real parameters, so the results have to agree
  ComplexType real_masses = E0i(ee00, MOMENTA, 10000, 10000, 10000, 10000, 10000);
  ComplexType real_masses_C = E0iC(ee00, MOMENTA, 10000, 10000, 10000, 10000, 10000);
  print("E0i(ee00)", real_masses);
  print("E0iC(ee00)", real_masses_C);
  if (!(cabs(real_masses_C - real_masses) <= 1e-12 * cabs(real_masses))) {
    printf("FAILED: E0i and E0iC differ for real masses\n");
    failed = 1;
  }

  // A small width is a small change to the result
  ComplexType mass2 = 10000 - 100 * I;
  ComplexType complex_masses = E0iC(ee00, MOMENTA, mass2, mass2, mass2, mass2, mass2);
  print("E0iC(ee00), with width", complex_masses);
  if (!(cabs(complex_masses - real_masses) <= 0.1 * cabs(real_masses))) {
    printf("FAILED: E0iC for complex masses is not close to E0i for real masses\n");
    failed = 1;
  }

  ltexi();
  return failed;
}
