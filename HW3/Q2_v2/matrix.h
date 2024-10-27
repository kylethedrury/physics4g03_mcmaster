#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

typedef vector<double> Row;
typedef vector<Row> Matrix;

int sign (double x);
Matrix multiply (const Matrix &A, const Matrix &B);
Matrix transpose (Matrix &A);
double epsilon_func (double S0, int n);
double S0_func (Matrix &A);
void rotate (Matrix &A, int p, int q, int size, Row &d);

inline double dotprod (const Row &y, const Row &x) {
 
  double sum = 0.0;
  for (int i = 0; i < y.size(); i++) {
    sum += x[i]*y[i];
  }
  return sum;
}

inline Row scale (Row &v, double scalar) {
  for (int i = 0; i < v.size(); i++) {
    v[i] *= scalar;
  }
  return v;
}

inline Row subtract (const Row &x, const Row &y) {
  if (x.size() != y.size()) {  // check if vectors are the same size
    cout << "Vectors must be the same length." << endl;
  }
   
  Row result(x.size());  // initialize a vector to store result

  for (int i = 0; i < x.size(); i++) {
    result[i] = x[i] - y[i];
  }
  return result;
}

inline double norm (const Row &v) {
  return sqrt(dotprod(v,v));
}

inline Row normalize(Row &v) {
  return scale(v, 1/norm(v));
}

#endif // MATRIX_H
