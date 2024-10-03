#include <cmath>
#include <iostream> 
#include <random> 

using namespace std;

const double normalization = (exp(10)-1)/exp(10); // define the normalization factor because it is used throughout 

double f (double x) {  // define the function whose integral we are evaluating 
  return exp(-x*x);  
}

double g (double x) {  // define g functon from assignment
  return exp(-x) / normalization;
}

double G (double x) {  // define G function from assignment
  return (1 - exp(-x)) / normalization; 
}

double G_inv (double u) {  // define G inverse function from assignment
  return -log( 1 - u * normalization );
}

int main() {

  random_device r;                          // seed for mt19937
  mt19937 e2(r());                          // generate an instance mt19937
  uniform_real_distribution<> my_r(0,1);    // generate a uniform random number between 0 and 1
  int N = 1000;                             // number of loops for MC integration 
  double integral = 0;                      // initialize the sum for computing integral

  int a = 0;
  int b = 10;                       // bounds of integration
  double lower = G(a); 
  double upper = G(b);              // bounds of integration for version of importance sampling 
  double region = upper - lower;    // the region of integration 

  for (int i = 0; i < N; i++) {

    uniform_real_distribution<> my_r(0,1);          // generate a random number
    double u = my_r(e2);                            // save it as x for ease of use 
    double result = f( G_inv(u) ) / g( G_inv(u) );  // evaluate the integrand in eqn (2)   
    integral = integral + result;                   // add element area to the integral sum 

  }
 
  integral = integral / N;  // multiply by the region of integration, and divide by N

  cout << "The integral is " << integral << endl; 
  return 0;

}
