#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

typedef vector<double> Row;  // one row of a matrix
typedef vector<Row> Matrix;  // Matrix: a vector of rows

double V (double x) {
  
  if (abs(x) >= 5) {
    double y = 0;
    return y;
  } else {
    return x*x/5 - 14.0;
  }
}

double V2 (double x) {
  
  if (abs(x) >= M_PI/4) {
    return 1e20;
  } else {
    double a = 0.05 / pow(sin(x+M_PI/4),2);
    double b = 5 / pow(cos(x+M_PI/4),2); 
    return a + b;
  }
}

double ksq (double x, double E) {
  return E - V2(x);
}

double phi_l (double x, double h, double last, double slast, double E) {

  double numer = 2 * (1.0 - 5.0/12 * h*h * ksq(x-h, E)) * last - (1.0 + h*h / 12.0 * ksq(x-2*h, E)) * slast;
  double denom = 1 + h*h / 12.0 * ksq(x, E);
  
  return numer/denom;
}

double phi_r (double x, double h, double last, double slast, double E) {

  double numer = 2 * (1.0 - 5.0/12 * h*h * ksq(x+h, E)) * last - (1.0 + h*h / 12.0 * ksq(x+2*h, E)) * slast;
  double denom = 1 + h*h / 12.0 * ksq(x, E);

  return numer/denom; 
}

void saveToFile(const Row& array1, const Row& array2, const string filename) {
   
  ofstream outFile(filename, ios::trunc);
     
  if (!outFile) {
    cout << "Error opening file!" << std::endl;
    return;
  }
   
  // Ensure both arrays are of the same size
  size_t size = array1.size();
  if (size != array2.size()) {
    cout << "Arrays are not the same size!" << endl;
    return;
  }
    
  for (size_t i = 0; i < size; ++i) {
    outFile << array1[i] << "\t" << array2[i] << endl;
  }

  outFile.close();
}

void normalize(Row& vec, double h) {

  double sum = 0;                     // integrate phi to get normalization constant
  int Nsteps = vec.size();            // number of steps in the vector
  for (int i=0; i < Nsteps-1; i++) {
    sum += (vec[i] + vec[i+1])*h/2;
  }
  for (int i=0; i < Nsteps; i++) {  // normalize
   vec[i] = vec[i]/sum;
  }
}

void merge(Row& phi, Row& phil, Row& phir, Row& xl, Row& xr, double xm, double E, double Nsteps, double h) {
  
  for (int j=2; j<Nsteps; j++) {
    phil[j] = phi_l(xl[j], h, phil[j-1], phil[j-2], E);  // recusion
    phir[j] = phi_r(xr[j], h, phir[j-1], phir[j-2], E);
  }

  for (int j=0; j<Nsteps; j++) {                            // rescale phir and create wave function
    phil[j] = phil[j] * phir[xm] / phil[xm];
    
    if (j <= xm) {  // merge phil and phir together
      phi[j] = phil[j];
    } else {
    phi[j] = phir[Nsteps-j-1];
    }
  }
}
