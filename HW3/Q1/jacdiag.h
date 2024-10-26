#ifndef JACOBI_H
#define JACOBI_H

#include <vector>
#include "matrix.h"

void jacdiag (Matrix &A, Row &d);
void jacdiag_v2 (Matrix &A, Row &d, int Nsweeps); 

#endif // JACOBI_H
