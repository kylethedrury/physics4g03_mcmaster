#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include <omp.h>
#include <fstream>
#include "functions.h"
#define NUM_THREADS 32

using namespace std;

int main() {
  omp_set_num_threads(NUM_THREADS);
  
  double start_time = omp_get_wtime();

  int L = 4000;                // matrix size  
  Matrix A (L, Row(L, 0.0));  // initialize matrix 

  #pragma omp parallel for
  for (int i=0; i<L; i++) {
    //int thread_id = omp_get_thread_num();
    //int num_threads = omp_get_num_threads();

    //#pragma omp critical 
    //{
    //  cout << "Thread " << thread_id << " out of " << num_threads << " is running for iteration " << i << endl;
    //}
    
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

  int lambda; 
  Row x(L, 0.0);

  double time1 = omp_get_wtime();

  y = normalize(y); 

  int N = 200;  // number of loops for power method 
  for (int n=0; n<N; n++) {
    x = multiplyRowWithMatrix(y, A);
    lambda = norm(x) / norm(y); 
    y = normalize(x); 
  }

  double time2 = omp_get_wtime();

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

  double end_time = omp_get_wtime();
  cout << "Serial Time: " << (time1-start_time) + (end_time-time2) << " seconds" << endl;
  cout << "Total Time: " << end_time - start_time << " seconds" << endl;
  return 0;
}

