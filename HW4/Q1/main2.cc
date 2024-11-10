#include <fstream>
#include <limits>
#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include "functions.h"
                   
using namespace std;                    

int main() {

  double maxE = 20;            // energy
  double Eh = 0.01;            // energy step size
  int Esteps = 2*maxE/Eh +1;   // energy steps 

  Row E (Esteps, 0.0);            // row for storing energy values
  Row G (Esteps, 0.0);            // array for storing G(E) values
  Row F (Esteps, 0.0);            // array for storing F(E) values  
  for (int i=0; i<Esteps; i++) {  // initialize  
    E[i] = -1 * maxE + i*Eh; 
  }

  double h = 0.001;            // step size for integration phi
  double f = 0.0001;           // small initial values 
  double maxval = 7;           // integration bound on RH side
  int Nsteps = 2*maxval/h +1;  // number of steps on each side of (0,0) 
  int mid_index = maxval/h;    // index of middle value 

  Row xr (Nsteps, 0.0);     // declare vectors for x and phi
  Row xl (Nsteps, 0.0);
  Row phil (Nsteps, 0.0);
  Row phir (Nsteps, 0.0);
  Row phi (Nsteps, 0.0);    // vector for storing final wave function

  for (int i=0; i<Nsteps; i++) {  // initialize xl and xr
    xl[i] = -1 * maxval + i*h;
    xr[i] = maxval - i*h;
  }
 
  phil[0] = phir[0] = 0;  // initial phi values on each side
  phil[1] = phir[1] = f;

  for (int i=0; i<Esteps; i++) {

    merge(phi, phil, phir, xl, xr, mid_index, E[i], Nsteps, h);
    normalize(phi, h);

    if (abs(phi[mid_index]) < 0.002) {                  // if phi is close to 0, must be odd
      cout << "Odd eigenvalue found: " << E[i] << endl;
    }
    else if (abs(phi[mid_index] - phi[mid_index+1]) < 0.000004) {  // if derivative close to 0, must be even
      cout << "Even eigenvalue found: " << E[i] << endl; 
    } 
  }

  saveToFile(E, G, "G.txt");  // save G(E) and F(E) 
  saveToFile(E, F, "F.txt");
  
  double plotE; 
  cout << "Which energy would you like to use to generate a dataset?" << endl;
  cin >> plotE; 

  merge(phi, phil, phir, xl, xr, mid_index, plotE, Nsteps, h);
  normalize(phi, h);

  saveToFile(xl, phi, "wave.txt"); 
}
