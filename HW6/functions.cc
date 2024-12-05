#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> Row;  // one row of a matrix
typedef vector<Row> Matrix;  // Matrix: a vector of rows

Row multiplyRowWithMatrix(const Row& row, const Matrix& matrix) {
  int rowSize = row.size();
  int matrixRows = matrix.size();
  int matrixCols = matrixRows > 0 ? matrix[0].size() : 0;

  if (rowSize != matrixRows) {  // Check dimensions for compatibility
    cout << "Row size must match the number of rows in the matrix.";
  }

  Row result(matrixCols, 0.0);  // Resultant row vector (1 x M)

  for (int j = 0; j < matrixCols; ++j) {   // Iterate over columns of the matrix
    for (int i = 0; i < rowSize; ++i) {    // Iterate over rows/elements of the row vector
      result[j] += row[i] * matrix[i][j];
    }
  }
  return result;
}

double norm(const Row& x) {  // function for computing the norm of x
  int size = x.size(); 
  double sum = 0; 
  for (int i=0; i<size; i++) {
    sum += x[i]*x[i];
  }
  return sqrt(sum); 
}

Row normalize(Row& x) {  // function for normalizing x 
  double n = norm(x);
  for (double& val : x) {
    val /= n; 
  }
  return x; 
}
