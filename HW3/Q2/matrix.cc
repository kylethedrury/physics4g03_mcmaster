#include <cmath>
#include <vector> 
#include <iostream>
#include "matrix.h" 

using namespace std;

typedef vector<double> Row;  // one row of a matrix
typedef vector<Row> Matrix;  // Matrix: a vector of rows 

int sign (double x) {  // function for returning the sign of a double
  if (x > 0) {
    return 1;    // positive
  } else {
    return -1;   // negative 
  }   
}

Matrix multiply (const Matrix &A, const Matrix &B) {  // function for facilitating matrix multiplication

  int size = A.size();
  Matrix C(size, Row(size, 0.0));  // initialize product matrix

  for (int i = 0; i < size; ++i) {       // Loop over rows of A
    for (int j = 0; j < size; ++j) {     // Loop over columns of B
      for (int k = 0; k < size; ++k) {   // Loop over columns of A / rows of B
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return C;
}

Matrix transpose (Matrix &A) {

  int size = A.size();

  Matrix AT(size, Row(size, 0.0));  // initialize matrix for transpose

  for (int i = 0; i < size; ++i) {     // Loop over rows of A
    for (int j = 0; j < size; ++j) {   // Loop over columns of A
      AT[j][i] = A[i][j];              // Set the transposed element
    }
  }

  return AT;
}

double epsilon_func (double S0, int n) { 
  return (1/5) * S0 / (n*n);
}

double S0_func (Matrix &A) {
  int size = A.size();
  double sum = 0;

  for (int i = 1; i < size; i++) {
    for (int j = i+1; j < size; j++) {
      sum += abs(A[i][j]);
    }
  }

  return sum; 
}

void rotate (Matrix &A, int p, int q, int size, Row &d) {

  Matrix P(size, Row(size, 0.0));  // initialize a matrix for getting the Jacobi rotations

  double alpha = (A[q][q] - A[p][p]) / (2 * A[p][q]);               // get rotation parameters
  double t = sign(alpha) / ( abs(alpha) + sqrt(alpha*alpha + 1) );
  double c = 1 / sqrt(t*t + 1);
  double s = t * c;

  for (int i = 0; i < size; i++) {  // set the diagonal of P to all 1's
    P[i][i] = 1;
  }

  P[p][p] = c;     // define the Jacobi rotation
  P[q][q] = c;
  P[p][q] = s;
  P[q][p] = -s; 

  Matrix D(size, Row(size, 0.0));                // initialize eval matrix
  D = multiply (transpose(P), multiply(A,P));    // do D = PT*A*P

  for (int i = 0; i < size; i++) {  // append the evals to the d vector
    d[i] = D[i][i];
  }

  A = D;  // set the matrix we are diagonalizing to D for next iteration
}
