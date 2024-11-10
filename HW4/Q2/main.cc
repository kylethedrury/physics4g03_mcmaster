#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "functions.h"
#include <utility> 

using namespace std;                    

void writeMatrixToFile(const Matrix &matrix, const std::string &filename) {
  ofstream outFile(filename);

  if (!outFile) {
    cout << "Error opening file!" << std::endl;
    return;
  }

  size_t L = matrix.size();          // Assumes a square matrix (LxL)
  for (size_t i = 0; i < L; ++i) {
    for (size_t j = 0; j < L; ++j) {
      outFile << matrix[i][j];
      if (j < L - 1) {             // Avoid adding a tab after the last element
        outFile << "\t";
      }
    } 
    outFile << "\n";
  }
  outFile.close();
}

int main() {

  int L = 1000;           // number of grid points
  double e = 5e-5;        // accuracy cut off 
  double difference=100;  // variable for storing the max difference between Unew and Uold

  Matrix grid (L, Row(L, 0.0));   // initialize empty grid 
  Matrix rgrid (L, Row(L, 0.0));  // replacement grid for easy swapping
 
  for (int i=0; i<L; i++) {  // make the top row U=100
    grid[L-1][i] = 100; 
    rgrid[L-1][i] = 100; 
  }

  int counter = 0;          // sweep counter
  while (difference > e) {  // loop breaks when max difference drops below threshold
    double maxDiff = 0; 

    for (int i=L-2; i>=1; i--) {   // only sweep through the inner points; outer points are bound
      for (int j=L-2; j>=1; j--) {
        rgrid[i][j] = 0.25 * (grid[i-1][j] + grid[i+1][j] + grid[i][j-1] + grid[i][j+1]); 

        double diff = abs(grid[i][j] - rgrid[i][j]); 
        if (diff > maxDiff) {
          maxDiff = diff;      // update difference if required
        }
      }
    }

    difference = maxDiff;
    counter++;
    if (counter % 1000 == 0) {
      cout << "Iteration " << counter << " complete; max difference is " << difference << endl;
    }

    swap(grid, rgrid); 
  }
   
  writeMatrixToFile(rgrid, "output.txt");
}
