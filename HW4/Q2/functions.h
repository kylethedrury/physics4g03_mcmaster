#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

using namespace std;

typedef vector<double> Row;  // one row of a matrix
typedef vector<Row> Matrix;  // Matrix: a vector of rows

double V(double x);

double V2 (double x);

double ksq(double x, double E);

double phi_l (double x, double h, double last, double slast, double E);

double phi_r (double x, double h, double first, double second, double E);

void saveToFile (const Row &array1, const Row &array2, const string filename);

void normalize(Row& vec, double h);

void merge(Row& phi, Row& phil, Row& phir, Row& xl, Row& xr, double xm, double E, double Nsteps, double h);

#endif // FUNCTIONS_H
