#include <fstream>
#include <limits>
#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include "matrix.h"
#include "jacdiag.h"
#include "hv.h"

using namespace std;
using namespace chrono;

// void eigsrt(vector<double> &d, Matrix &v);

int main() {     

  mt19937 generator;                                // initialize RNG
  uniform_real_distribution<double> dist(0,1.0);  
  int L, m, Nsweeps;

  cout << "Size of system, L: ";           // user-inputted params 
  cin >> L;
  cout << "Size of Lanczos matrix, m: ";
  cin >> m;
  cout << "Number of Jacobi sweeps, Nsweeps: ";
  cin >> Nsweeps;

  int N = pow(2,L);                          // number of states
  Row v0(N), v1(N), f(N), omega(N);          // initialize each vector
  Matrix Lan(m, Row(m, 0.0)), v(m, Row(m));  // initialize Lanczos matrix full of zeros

  for (int i=0; i < N; i++){            // loop for initializing v1 and v2
    v0[i] = 1.0 - 2.0*dist(generator);  // v1 is random starting vector
    v1[i]=0.0;                          // v2 is the second vector to be calculated
  }
      
  v[0] = normalize(v0);                         // normalize v[0]
  hv(omega, v[0], L);                           // get w (stored in omega)
  Lan[0][0] = dotprod(v[0], omega);             // get alpha_0
  f = subtract(omega, scale(v[0], Lan[0][0]));  // get f0 

  for (int j = 0; j < m-1; j++) { 

    Lan[j+1][j] = Lan[j][j+1] = norm(f);                    // set betas 
    v[j+1] = normalize(f);                                  // get next v
    
    hv(omega, v[j+1], L);
    omega = subtract(omega, scale(v[j], norm(f)));          // get next omega
    
    Lan[j+1][j+1] = dotprod(v[j+1], omega);                 // get next alpha
    f = subtract(omega, scale(v[j+1], Lan[j+1][j+1]));      // get next f
  }

  Row d(m, 0.0);                // initialize d vector for storing eigenvalues
  jacdiag_v2(Lan, d, Nsweeps);  // call jacobi v2

  double E0 = numeric_limits<double>::max();  // initialize variables for storing E0 and E1
  double E1 = numeric_limits<double>::max(); 

  for (double value : d) {
    if (value < E0) { 
      E1 = E0;     // move the current lowest to second lowest
      E0 = value;  // update lowest energy 
    } else if (value < E1) {
      E1 = value; }  // update E1 if necessary 
    }

  cout << "(E0, E1) = (" << E0 << ", " << E1 << ")" << endl; 

  ofstream outFile("output.txt", ios::app); // open in append mode
  if (outFile.is_open()) {
          outFile << E0 << " " << E1 << "\n"; // write values with a space, add a newline
              outFile.close();                    // close the file
  } else {
          cout << "Unable to open file for writing.\n";
  }

  return 0;
}
