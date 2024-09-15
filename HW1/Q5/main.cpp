#include <iostream>
#include <cmath>
#include <ctime>

using namespace std; 

double factorial(int n) {   // function for evaluating factorials 

  double f = 1;
  for (int i=1; i <= n; i++) {
    f = f*i;
  }

  return f;

}

double Sq_Tlr(double x, int n) {  // x is the function input, n is the number of terms in the expansion 

  double exponent = 0.5;  // the first exponent is 0.5 
  double sum = 0;         // initialize the Taylor sum as zero 
  int a = round(x);       // choose an integer a closest to x to center the expansion about 
  double coeff = 1;       // the coefficient of the first term; will be modified with each loop

  for (int i = 0; i < n; i++) {

    sum += coeff * pow(a, exponent) * pow((x-a), i) / factorial(i); // add the first Taylor term to sum
    coeff = exponent * coeff;   // get the new coeff by bringing the exponent out front (power rule)
    exponent -= 1;  // lower the exponent by 1 (power rule) 

  }

  return sum;

}

double Sq_Nwt(double x, int n) {  // x is the function input, n is the number of steps/gesses

  double a = x; // initial guess 
 
  for (int i = 0; i < n; i++) {
 
    a = 0.5 * (a + (x/a));  // make a new guess with Newton's method   

  }  

  return a; 

}

double Sq_Frc(double x, int n) {  // x is the function input, n is number of steps 

  double a = 1; 

  if (n == 1) {

    return a + (x - a*a) / a; // if n = 1, then there is no more recurring to do  

  }

  else

    return a + (x - a*a) / (a + Sq_Frc(x, n-1)); // if n > 1, the recurrence relationship is called 

}

int main() {  // we call each of the above functions 100,000 times and time how long it takes

  double answer; 

  clock_t start = clock(); // timing the Taylor series method

  for (int i = 0; i < 100000; i++) {

    answer = Sq_Tlr(2, 100);    

  }

  clock_t stop = clock();

  double duration = double(stop - start) / CLOCKS_PER_SEC;
  cout << duration << endl;

/////////////////////////////////////////////////////////////////

  start = clock(); // timing Newton's method 

  for (int i = 0; i < 100000; i++) {

    answer = Sq_Nwt(2, 100);

  }

  stop = clock();

  duration = double(stop - start) / CLOCKS_PER_SEC;
  cout << duration << endl; 

/////////////////////////////////////////////////////////////////

  start = clock(); // timing continued fraction method 

  for (int i = 0; i < 100000; i++) {

    answer = Sq_Frc(2, 100);

  }

  stop = clock();

  duration = double(stop - start) / CLOCKS_PER_SEC;
  cout << duration << endl; 

  return 0;

}
