// Set on the condition f else clear
// bool f;         // conditional flag
// unsigned int m; // the bit mask
// unsigned int w; // the word to modify: if (f) w |= m; else w &= ~m; 

#include <vector>
#include <cmath>
#include <iostream>
#include "matrix.h"
#include "hv.h"

using namespace std;

Row hv(const Row &x, int L) {  // x is the input vector; function for evaluating Hv
  
  int size = x.size();  // get size of vector
  Row y(size, 0.0);     // initialize empty resultant vector

  // bool b;
  unsigned int k;
  
  for (unsigned int i=0; i < x.size(); i++) {
   
    if (abs(x[i])>2.2e-16) {

      int jm = L-1;
      double xov2=x[i]/2.0;
      
      for (int j=0;j<L;j++){
        k=i;
        COND_BIT_SET(k,jm,BIT_CHECK(i,j));
        COND_BIT_SET(k,j,BIT_CHECK(i,jm));
        y[k] += xov2;
        jm = j;
      }
    }
  }

  for (unsigned int i=0; i < x.size(); i++) {
    y[i]=y[i]-((double) L)/2.0*x[i]/2.0;
  }

  return y;
}
