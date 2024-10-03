#include <cmath>
#include <random> 
#include <iostream> 
#include <vector> 
#include <algorithm>
#include <fstream>
#include <string> 
#include "MCvar.h"
#include "MCSweeps.h" 

using namespace std; 

void writeTable(double T, double J) {
  
  double k = 1.380649e-23;

  double E_is_8 = exp(-8*J/k/T);    // lookup table for different E_delta values
  double E_is_6 = exp(-6*J/k/T);
  double E_is_4 = exp(-4*J/k/T);
  double E_is_2 = exp(-2*J/k/T);
  double E_is_neg2 = exp(2*J/k/T);
  double E_is_neg4 = exp(4*J/k/T);
  double E_is_neg6 = exp(6*J/k/T);
  double E_is_neg8 = exp(8*J/k/T);

  ofstream outFile("table.txt");    // open the lookup table file  

  outFile << E_is_8 << endl;        // write the values to the table 
  outFile << E_is_6 << endl;
  outFile << E_is_4 << endl;
  outFile << E_is_2 << endl;
  outFile << E_is_neg2 << endl;
  outFile << E_is_neg4 << endl;
  outFile << E_is_neg6 << endl;
  outFile << E_is_neg8 << endl; 

  outFile.close();  // close the file 
}

int main() { 

  double kb = 1.380649e-23;  // Boltzmann constant 
  double J, T; 
  int L, Nmeas, Nwarmup, Nsteps;  // ask the user to input simulation parameters 

  cout << "Input temperature T: ";
  cin >> T; 
  cout << "Input interaction energy J: ";
  cin >> J;
  cout << "Input lattice size L: ";
  cin >> L;
  cout << "Input number of measurements: ";
  cin >> Nmeas; 
  cout << "Input number of warmup sweeps: "; 
  cin >> Nwarmup; 
  cout << "Input number of sweeps between measurements: "; 
  cin >> Nsteps;

  writeTable(T, J);  // call writeTable to create the lookup table 

  random_device r;                                  // seed for RNG
  mt19937 e2(r());                                  // initialize RNG
  uniform_int_distribution<int> initRNG(0, 1);      // integer RNG for initializing spins 
  vector<vector<int>> SpinConf(L, vector<int>(L));  // initialize lattice

  for (int i = 0; i < L; i++) {     // iterate over each row 
   
    for (int j = 0; j < L; j++) {   // iterate over each column
     
      int x = initRNG(e2);          // generate a random number, 0 or 1
       
      if (x == 1) {                 // assign a spin state based on random number  
        SpinConf[i][j] = 1;
      } else { 
        SpinConf[i][j] = -1; 
      }
    }
  }

  MCSweeps(SpinConf, Nwarmup, J);  // perform Nwarmup sweeps with the MCSweeps function

  MCvar<double> M;  // define an MCvar for storing magnetization data
  MCvar<double> M2; // magnetization squared
  MCvar<double> M4; // magnetization to the fourth
  MCvar<double> E;  // define an MCvar for storing total energy data
  MCvar<double> E2; // energy squared
  MCvar<double> E4; // energy to the fourth
 
  ofstream M_file("M.txt");  // open a file for storing magnetization data (question 2.4)

  double mag, energy;  // initialize varable

  for (int i = 0; i < Nmeas*1000; i++) {  // loop for performing Nmeas measurements; 1000 entries per bin/measurement 

    MCSweeps(SpinConf, Nsteps, J);  // perform Nsteps sweeps before next measurement

    mag = Magnetization(SpinConf);  // get the total magnetization
    energy = Energy(SpinConf, J);   // get the total energy
    
    M_file << mag << endl;  // write the current magnetization to M_file

    M.push(mag);             // push the current magnetization to the MCvar 
    M2.push(mag*mag);
    M4.push(pow(mag, 4));
    E.push(energy);          // push the current energy to the MCvar 
    E2.push(energy*energy); 
    E4.push(pow(energy, 4));
  } 

  M_file.close();  // close M_file 

  double C = L*L*kb*kb*T*T;  // shorthand for computing Cv/kb

  double Cvkb = (E2.Avrg() - E.Avrg()*E.Avrg())/C; 
  double Cvkb_err = E2.Err_Avrg()/C - (2*E.Avrg()*E.Err_Avrg())/C; 
  double g = (3 - (M4.Avrg() / (M2.Avrg()*M2.Avrg()))) / 2;

  cout << "----------------------------------------------------------" << endl; 
  cout << "Average magnetization: " << M.Avrg() << " +- " << M.Err_Avrg() << endl; // print results to terminal 
  cout << "Average M2: " << M2.Avrg() << " +- " << M2.Err_Avrg() << endl;
  cout << "Average M4: " << M4.Avrg() << " +- " << M4.Err_Avrg() << endl;
  cout << "Average energy: " << E.Avrg() << " +- " << E.Err_Avrg() << endl;
  cout << "Average E2: " << E2.Avrg() << " +- " << E2.Err_Avrg() << endl; 
  cout << "Average E4: " << E4.Avrg() << " +- " << E4.Err_Avrg() << endl; 
  cout << "Chi: " << M2.Avrg()/(T*L*L) << " +- " << M2.Err_Avrg()/(T*L*L) << endl; 
  cout << "Cv/kb: " << Cvkb << " +- " << Cvkb_err << endl; 
  cout << "g: " << g << endl;

}
