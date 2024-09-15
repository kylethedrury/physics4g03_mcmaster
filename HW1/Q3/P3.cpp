#include <iostream>
#include <cmath>

using namespace std; 

double Bessel(int n, double x) {

  int N  = 10 * (n+1);    // pick a sufficiently large N to start the recurrence at 

  double J_arr[N+2];      // an array to store values of J

  J_arr[N] = 1;           // start the recurrence
  J_arr[N+1] = 0;  

  for (int i = N; i > 0; i--) {

    J_arr[i-1] = (2 * i / x) * J_arr[i] - J_arr[i+1];   // calculate the next highest term after the previous two 

  }  

  double sum = 0; // initialize the sum of all the elements in J_array; this will be the normalization const.
  int i = 2;      // initialize a counter

  while (i < N+2) {
                          
    sum += J_arr[i];  // Sum all elements 
    i = i + 2;        // count up by 2
                              
  }

  double norm = J_arr[0] + 2*sum; // get the normalization factor  

  for (int i = 0; i < N+2; i++) {
             
    J_arr[i] = J_arr[i] / norm;  // normalize all the elements 
                               
  }

  return J_arr[n]; 

}

int main() {

  int n;
  double x;
            
  cout << "Type n: ";
  cin >> n;
  cout << "Type x: ";
  cin >> x;

  double result = Bessel(n, x);
   
  cout << "The result is " << result << endl;
 
  return 0;

}
