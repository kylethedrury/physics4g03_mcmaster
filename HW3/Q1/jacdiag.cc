#include <cmath>
#include <vector> 
#include <iostream>
#include "matrix.h"

using namespace std;

void jacdiag (Matrix &A, Row &d) {  // function for a Jacobi sweep on A

  int size = A.size();  // get the size of the matrix
  double SqSum = 0;     // sum of squares for elements above diagonal

  for (int p = 0; p < size; p++) {  // nested for-loop for covering all elements above upper diagonal
    for (int q = p+1; q < size; q++) {  
      rotate(A, p, q, size, d);
    } 
  }

  for (int p = 0; p < size; p++) {        // get the sum of the squares above diagonal 
    for (int q = p+1; q < size; q++) { 
      SqSum += A[p][q] * A[p][q];
    }
  }

  cout << "Sum of squares: " << SqSum << endl;
}

void jacdiag_v2 (Matrix &A, Row &d, int Nsweeps) {  // Jacobi with refinements

  int size = A.size();  // get the size of the matrix
  double SqSum = 0;     // sum of squares for elements above diagonal 
  int counter = 0;      // sweep counter 

  for (int i = 0; i < Nsweeps; i++) {       // iterate over number of sweeps
    for (int p = 0; p < size; p++) {        // nested loop for iterating above diagonal 
      for (int q = p+1; q < size; q++) {    

        if (counter < 3) {  // perform this trick only during the first 3 sweeps
          double S0 = S0_func(A);                   // get S0
          double epsilon = epsilon_func(S0, size);  // get epsilon

          if (A[p][q] > epsilon) {
            rotate(A, p, q, size, d);
          }
        }
        
        else if (counter > 3) {  // perform this trick only after the first four sweeps         
          if (abs(A[p][q]) < abs(A[p][p])/1e13 && abs(A[q][q]) < abs(A[q][q])/1e13) { 
            A[p][q] = 0; 
          } else {
            rotate(A, p, q, size, d);
          }
        }
       
        else {  // if counter = 3, just rotate normally 
          rotate(A, p, q, size, d);
        }
      }    
    }  

    for (int p = 0; p < size; p++) {        // get the sum of the squares above diagonal
      for (int q = p + 1; q < size; q++) {
        SqSum += A[p][q] * A[p][q];
      }
    }

    counter += 1;   // increment counter

    cout << "Sum of squares: " << SqSum << endl;
    cout << "Eigenvalues: ";

    for (int i = 0; i < size; i++) {  // cout the eigenvalues dynamically depending on size
      cout << d[i] << " ";
    } 

    cout << endl;
    cout << "Sweep " << counter << " complete..." << endl;
    cout << "-----------------------------------------------" << endl;  

    if (SqSum == 0) { break; }  // if the off-diagonal components vanish, break loop

    SqSum = 0;  // reset SqSum
  }
}
