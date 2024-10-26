#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

typedef vector<double> Row;
typedef vector<Row> Matrix;

int sign (double x);
Matrix multiply (Matrix &A, Matrix &B);
Matrix transpose (Matrix &A);
double epsilon_func (double S0, int n);
double S0_func (Matrix &A);
void rotate (Matrix &A, int p, int q, int size, Row &d);

#endif // MATRIX_H
