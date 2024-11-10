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

  int L = 1000;       // number of grid points
  double e = 1e-5;    // accuracy cut off 
  double difference;  // variable for storing the max difference between Unew and Uold

  Matrix grid (L, Row(L, 0.0));   // initialize empty grid 
  Matrix rgrid (L, Row(L, 0.0));  // replacement grid for easy swapping
 
  for (int i=0; i<L; i++) {  // make the top row U=100
    grid[L-1][i] = 100; 
    rgrid[L-1][i] = 100; 
  }

  while (difference > e) {
    difference = 100; 

    for (int i=L-2; i>=1; i--) { 
      for (int j=L-2; j>=1; j--) {
    
        if (i==0 && j==0) {  // in bottom left corner
          rgrid[i][j] = 1/4 * (grid[i+1][j] + grid[i][j+1]); 
        } else if (i==0 && j==L-1) {  // bottom right corner
          rgrid[i][j] = 1/4 * (grid[i+1][j] + grid[i][j-1]); 
        } else if (i==L-1 && j==0) {  // top left corner
          rgrid[i][j] = 1/4 * (grid[i-1][j] + grid[i][j+1]); 
        } else if (i==L-1 && j==L-1) {  // top right corner
          rgrid[i][j] = 1/4 * (grid[i-1][j] + grid[i][j-1]); 
        } else if (i==0) {  // bottom row
          rgrid[i][j] = 1/4 * (grid[i+1][j] + grid[i][j-1] + grid[i][j+1]);
        } else if (i==L-1) {  // top row 
          rgrid[i][j] = 1/4 * (grid[i-1][j] + grid[i][j-1] + grid[i][j+1]); 
        } else if (j==0) {  // leftmost column 
          rgrid[i][j] = 1/4 * (grid[i-1][j] + grid[i+1][j] + grid[i][j+1]);
        } else if (j==L-1) {  // rightmost column 
          rgrid[i][j] = 1/4 * (grid[i-1][j] + grid[i+1][j] + grid[i][j-1]);
        } else {
          rgrid[i][j] = 1/4 * (grid[i-1][j] + grid[i+1][j] + grid[i][j-1] + grid[i][j+1]); 
        }
      
        if (abs(grid[i][j] - rgrid[i][j]) < difference) {
         difference = abs(grid[i][j] - rgrid[i][j]); 
        }

        swap(grid, rgrid); 
      }
    }
  }
  writeMatrixToFile(grid, "output.txt");
}
