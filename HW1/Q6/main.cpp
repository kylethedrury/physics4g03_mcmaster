#include <iostream>
#include <cmath>

using namespace std;

double function(double x) {

  return 4 / (1 + x*x);

}

double trapazoidal(double (*f)(double x), double xl, double xh, int n) {

  double delta = (xh - xl)/n;
  double sum = 0;
  double trapazoid, x1, x2;  // variables for trapazoid, and lower and upper bounds of each step

  for (int i = 0; i < n; i++) {

    x1 = xl + i*delta;
    x2 = xl + (i+1)*delta; 
    trapazoid = 0.5 *(f(x2) + f(x1)) * delta;
    sum += trapazoid; 

  }

  return sum; 

}

double romberg (double (*f)(double x), double xl, double xh, int n) {

  double R[n+1][n+1];    // allocate an array of Romberg variables 
  double h;              // allocate h
  double sum;            // initialize a sum variable for eqn 14

  R[0][0] = (f(xl) + f(xh))/2;  // calculate inital R(0,0)

  for (int i = 1; i <= n; i++) {  // loop for calculating all R(n,0)
    
    sum = 0;               // set sum to 0
    h = (xh-xl)/pow(2,i);  // get h value

    for (int j = 1; j <= pow(2,i-1); j++) {  // loop for calculating the sum term in eqn 14

      sum += function(xl + (2*j-1)*h); 

    } 

    R[i][0] = R[i-1][0]/2 + h*sum;   

  }

  for (int i = 1; i <= n; i++) {  // loop for calculating each R(n,m)

    for (int j = i; j <= n; j++) {  

      R[j][i] = R[j][i-1] + 1 / (pow(4,i)-1) * (R[j][i-1] - R[j-1][i-1]);

    }
  
  }

  return R[n][n];

}
  
int main() {
 
  cout.precision(24);
  int trap_steps, rom_steps;
  double result; 

  cout << "Specifiy the number of steps for trapazoidal and Romberg." << endl;
  cin >> trap_steps;
  cin >> rom_steps;

  clock_t begin_time = clock();
  
  for (int i = 0; i < 100000; i++) {
    result = trapazoidal(&function, 0, 1, trap_steps); // test the trapazoidal function
  }

  clock_t end_time = clock(); 
  double trap_time = double(end_time - begin_time) / CLOCKS_PER_SEC; // the trapazoidal time 
  cout << "Result for trapazoidal function: " << result << endl;
  cout << "The error is " << 3.141592653589793238462643383279502884197169399375105820974944592307816406286 - result << endl;

  begin_time = clock();
  
  for (int i = 0; i < 100000; i++) {
    result = romberg(&function, 0, 1, rom_steps);
  }

  end_time = clock();
  double rom_time = double(end_time - begin_time) / CLOCKS_PER_SEC; // the romberg time 
  cout << "Result for Romberg: " << result << endl;
  cout << "The error is " << 3.141592653589793238462643383279502884197169399375105820974944592307816406286 - result << endl;

  cout << "Time for trapazoidal: " << trap_time << endl;
  cout << "Time for Romberg: " << rom_time << endl;

}
