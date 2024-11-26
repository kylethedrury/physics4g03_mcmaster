#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include <omp.h>
#include <fstream>
#include "functions.h"

using namespace std;

int main() {

  double start_time, end_time;
  start_time = omp_get_wtime();

  int L = 200;                // matrix size  
  Matrix A (L, Row(L, 0.0));  // initialize matrix 

  for (int i=0; i<L; i++) {
    for (int j=0; j<L; j++) {
      if (j == i+1 && (i == 0 || i == L-2)) {
        A[i][j] = 1;
      } else if (i == j+1 && (i == 1 || i == L-1)) {
        A[i][j] = 1;
      } else if ((i == L-1 && j == 0) || (i == 0 && j == L-1)) {
        A[i][j] = 1;
      } else if (i == j) {
        A[i][j] = -2;
      }
    }
  }

  random_device rd;                           // random number seed 
  mt19937 gen(rd());                          // random number generator 
  uniform_real_distribution<> dis(0.0, 1.0);  // unif distribution on [0,1] 

  Row y(L, 0.0);             // random vector initialization 
  for (int i=0; i<L; i++) {
    y[i] = dis(gen); 
  }

  y = normalize(y); 

  int lambda; 
  Row x(L, 0.0);

  int N = 80;  // number of loops for power method 
  for (int n=0; n<N; n++) {
    x = multiplyRowWithMatrix(y, A);
    lambda = norm(x) / norm(y); 
    y = normalize(x); 
  }

  ofstream outfile("output.txt");
  if (!outfile) { 
    cout << "Error opening file." << endl;
    return 1;
  }

  outfile << "Eigenvalue: " << lambda << endl;
  outfile << "Eigenvector: ";
  for (int i=0; i<L; i++) {
    outfile << x[i] << " ";
  }
  outfile << endl;
  outfile.close();

  end_time = omp_get_wtime();
  cout << "Time: " << end_time - start_time << " seconds." << endl; 
  return 0;
}
