#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <vector>

using namespace std;

typedef vector<double> Row;  // one row of a matrix
typedef vector<Row> Matrix;  // Matrix: a vector of rows

Row multiplyRowWithMatrix(const Row& row, const Matrix& matrix); 

double norm(const Row& x);

Row normalize(Row& x);

#endif // FUNCTIONS_H
