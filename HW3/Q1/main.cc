#include <cmath>
#include <vector>
#include <iostream>
#include "matrix.h"
#include "jacdiag.h"

int kronecker (int n, int m) {
  if (n == m) {
    return 1;
  } else {
    return 0;
  }
}

using namespace std; 

int main() {

  int size;     // integer for storing matrix size 
  int sweeps;   // initiaize variable for number of sweeps

  cout << "Input matrix size M: " << endl;
  cin >> size; 
  cout << "Input number of sweeps: " << endl;
  cin >> sweeps;

  Row d(size, 0.0);                 // initialize a vector of zeros for storing evals
  Matrix H(size, Row(size, 0.0));   // initialize H matrix

  for (int n = 1; n <= size; n++) {      // nested for loop for setting H
    for (int m = 1; m <= size; m++) {
      H[n-1][m-1] = kronecker(n,m) * 4 * (n*n) + min(n,m) * (0.1 + pow(-1, abs(m-n)) * 10);
      // cout << H[n-1][m-1] << " "; 
    }
    // cout << endl;
  }

  Matrix H2 = H;  // initialize a second H matrix for using jacdiag_v2

  /* cout << "JACOBI V1:" << endl;
  cout << "--------------------------------------" << endl;

  for (int i = 0; i < sweeps; i++) {  // using first implementation of jacdiag
    jacdiag(H, d);
    cout << "Eigenvalues: "; 
    for (int i = 0; i < size; i++) {  // cout the eigenvalues dynamically depending on size
      cout << d[i] << " ";
    }
    cout << endl; 
    cout << "Sweep " << i+1 << " complete..." << endl;
    cout << "-----------------------------------------------" << endl;
  } */

  cout << "JACOBI V2:" << endl;
  cout << "--------------------------------------" << endl;

  jacdiag_v2(H2, d, sweeps);
}
