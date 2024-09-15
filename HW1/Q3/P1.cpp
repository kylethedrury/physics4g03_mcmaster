#include <iostream>

int main() {

  double J_previous = 0.938469807240813; // denotes J0 initially
  double J_current = 0.2422684577;       // denotes J1 initially
  double J_next;			             // initialize J_next; will be J2 first
  int n = 1;                             // current index (1)

  while (n < 20){  // stop loop when n=20; J20 was calculated on n=19

    J_next = (2 * n / 0.5) * J_current - J_previous;  // caclulate the next J with the current and previous J's
    J_previous = J_current;                           // the previous J is moved up one
    J_current = J_next;                               // the current J is moved up one
    n = n + 1;                                        // n is iterated up by one
    std::cout << J_current << std::endl;              // print out the latest J

  }

  std::cout << "J20 is " << J_current << std::endl;

}
