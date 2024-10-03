#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <fstream> 
#include "MCSweeps.h" 
#include "MCvar.h"

using namespace std;

void MCSweeps(vector<vector<int>>& arr, int Nmcs, double J) {

  double E_is_8, E_is_6, E_is_4, E_is_2;
  double E_is_neg2, E_is_neg4, E_is_neg6, E_is_neg8;  // initialize variables for storing values
   
  ifstream inFile("table.txt");  // open the lookup table with values
    
  inFile >> E_is_8;  // assign the values to appropriate variables
  inFile >> E_is_6;
  inFile >> E_is_4;
  inFile >> E_is_2;
  inFile >> E_is_neg2;
  inFile >> E_is_neg4;
  inFile >> E_is_neg6;
  inFile >> E_is_neg8;
            
  inFile.close();  // close the file

  int L = arr.size();                                // get the lattice size 
  random_device r;                                   // seed for RNG
  mt19937 e2(r());                                   // initialize RNG
  uniform_int_distribution<int> unif_dist(0, L-1);   // integer RNG between 0 and L-1 
  uniform_real_distribution<> r_dist(0,1);           // real RNG between 0 and 1 

  for (int i = 0; i < Nmcs; i++) {  // loop to iterate over Nmcs sweeps 

    int N_attempts = L*L;           // number of spin flip attempts

    for (int j = 0; j < N_attempts; j++) {

      int x = unif_dist(e2);        // random x  
      int y = unif_dist(e2);        // random y 
      int current = arr[x][y];      // current spin of the randomly selected lattice point 
      int flipped = -1 * arr[x][y]; // flipped spin 
      double E_delta;               // allocate variable to store E_delta 

      if (x == 0 && y == 0) {  // the spin selected is the (0,0) corner
        E_delta = -1 * J *  (flipped - current) * (arr[x][y+1] + arr[x+1][y] + arr[x][L-1] + arr[L-1][y]);

      } else if (x == 0 && y == L-1) {  // the spin selected is the (0,L) corner
        E_delta = -1 * J * (flipped - current) * (arr[x][y-1] + arr[x+1][y] + arr[L-1][L-1] + arr[0][0]);

      } else if (x == L-1 && y == 0) {  // the spin selected is the (L,0) corner
        E_delta = -1 * J * (flipped - current) * (arr[x][y+1] + arr[x-1][y] + arr[L-1][L-1] + arr[0][0]);

      } else if (x == L-1 && y == L-1) {  // the spin is in the (L,L) corner
        E_delta = -1 * J * (flipped - current) * (arr[x][y-1] + arr[x-1][y] + arr[L-1][0] + arr[0][L-1]);

      } else if (x == 0) {  // the spin is on the left edge but not a corner
        E_delta = -1 * J * (flipped - current) * (arr[x][y-1] + arr[x][y+1] + arr[x+1][y] + arr[L-1][y]);

      } else if (x == L-1) {  // the spin is on the right edge 
        E_delta = -1 * J * (flipped - current) * (arr[x][y-1] + arr[x][y+1] + arr[x-1][y] + arr[0][y]);

      } else if (y == 0) {  // the spin is on the bottom edge
        E_delta = -1 * J * (flipped - current) * (arr[x][y+1] + arr[x-1][y] + arr[x+1][y] + arr[x][L-1]);

      } else if (y == L-1) {  // the spin is on the top edge 
        E_delta = -1 * J * (flipped - current) * (arr[x][y-1] + arr[x-1][y] + arr[x+1][y] + arr[x][0]);

      } else {  // the spin is in the lattice interior
        E_delta = -1 * J * (flipped - current) * (arr[x][y-1] + arr[x][y+1] + arr[x-1][y] + arr[x+1][y]); 
      } 
      
      double P_flip;  // allocate variable for storing spin flip probability 

      if (E_delta == 8*J) {          // use the lookup table defined above to quickly calculate P_flip 
        P_flip = min(1.0, E_is_8); 
      } else if (E_delta == 6*J) { 
        P_flip = min(1.0, E_is_6); 
      } else if (E_delta == 4*J) {
        P_flip = min(1.0, E_is_4); 
      } else if (E_delta == 2*J) {
        P_flip = min(1.0, E_is_2); 
      } else if (E_delta == 0.0) {
        P_flip = 1; 
      } else if (E_delta == -2*J) {
        P_flip = min(1.0, E_is_neg2);
      } else if (E_delta == -4*J) {
        P_flip = min(1.0, E_is_neg4);
      } else if (E_delta == -6*J) {
        P_flip = min(1.0, E_is_neg6);
      } else {
        P_flip = min(1.0, E_is_neg8);
      } 

      double random_number = r_dist(e2); // generate a random number on (0,1)

      if (random_number <= P_flip) {     // if the random number is less or equal to P_flip, flip the spin 
        arr[x][y] = flipped; 
      }
    }
  }
}

double Energy(vector<vector<int>>& arr, double J) { 

  int L = arr.size();  // get the lattice size
  double total = 0;    // initialize variable for storing total energy

  for (int i = 0; i < L-1; i++) {  // iterate over each column in the lattice 

    for (int j = 0; j < L-1; j++) {  // iterative over each row in each column 

      total += -1 * J * arr[i][j] * (arr[i+1][j] + arr[i][j+1]);;  // energy associated with a point and the points above and to the right
    }
   
    total += -1 * J * arr[i][L-1] * arr[i+1][L-1];  // calculate the energy of the top row in the lattice
    total += -1 * J * arr[L-1][i] * arr[L-1][i+1];  // calculate the energy of the rightmost column in the lattice
  }

  for (int i = 0; i < L; i++) {

    total += -1 * J * arr[i][0] * arr[i][L-1];  // calculate energy associated with bottom row interacting with top row 
    total += -1 * J * arr[0][i] * arr[L-1][i];  // calculate energy associated with left column interacting with right column
  }

  return total; 
}

int Magnetization(vector<vector<int>>& arr) {
 
  int L = arr.size();  // get the lattice size 
  int total = 0;       // initialize variable for storing total magnetization

  for (int i = 0; i < L; i++) {  // iterate over each column

    for (int j = 0; j < L; j++) {  // iterate over each row in each column

      total += arr[i][j];  // add to total 
    }
  }

  return total;
}
