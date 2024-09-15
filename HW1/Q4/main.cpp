#include <iostream>
#include <cmath>
#include "function.h"  // Include the header file

using namespace std;

int main() {

  double x1, x2, xmid, root;  // variables to store guesses, midpoint, and the root in

  cout << "Provide an upper bound: "; 
  cin >> x2;
  cout << "Provide a lower bound: ";
  cin >> x1;

  while (x2 - x1 >= 0.0001) {

    xmid = (x2 + x1) / 2;      // get the midpoint 

    if (Bessel(0, xmid) == 0)  // midx is the root 
      root = xmid;

    else if (Bessel(0, x1) * Bessel(0, xmid) < 0) // root is between x1 and xmid
      x2 = xmid;  // set x2 to xmid

    else // root is between xmid and x2
      x1 = xmid;  // set x1 to xmid 
    }

  cout << "The root in the interval specified is " << xmid << endl;

  return 0;
  
}
