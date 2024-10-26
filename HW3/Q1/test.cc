#include <cmath>
#include <vector>
#include <iostream>
#include "matrix.h"
#include "jacdiag.h"

using namespace std; 

int main() {

  // initialize 5x5 H matrix 
  
  Matrix H = {
    {14.1, -9.9, 10.1, -9.9, 10.1},
    {-9.9, 36.2, -19.8, 20.2, -19.8},
    {10.1, -19.8, 66.3, -29.7, 30.3},
    {-9.9, 20.2, -29.7, 104.4, -39.6},
    {10.1, -19.8, 30.3, -39.6, 150.5}
  };

  Matrix H2 = H;  // initialize matrix for testing jacdiag_v2

  Row d(5, 0.0);  // initialize a vector of zeros for storing evals

  int sweeps;  // initiaize variable for number of sweeps
  cout << "Input number of sweeps: " << endl;
  cin >> sweeps;

  cout << "FIRST IMPLEMENTATION OF JACOBI METHOD:" << endl; 
  cout << "--------------------------------------" << endl;

  for (int i = 0; i < sweeps; i++) {  // using first implementation of jacdiag
    jacdiag(H, d);
    cout << "Eigenvalues: " << d[0] << " " <<  d[1] << " " << d[2] << " " <<  d[3] << " " << " " <<  d[4] << endl;
    cout << "Sweep " << i+1 << " complete..." << endl;
    cout << "-----------------------------------------------" << endl;
  }

  cout << "SECOND IMPLEMENTATION OF JACOBI METHOD:" << endl;
  cout << "--------------------------------------" << endl;

  jacdiag_v2(H2, d, sweeps);

}
