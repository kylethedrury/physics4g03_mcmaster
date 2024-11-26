#include <iostream>
#include <omp.h>

static long num_steps = 1000000000; 
double step;
#define NUM_THREADS 4

int main ()
{ int i, nthreads; 
  double start_time,run_time;
  double pi, sum[NUM_THREADS];
  step = 1.0/(double) num_steps;

  omp_set_num_threads(NUM_THREADS);

  std:: cout << "Sum is: " << pi << std::endl;
  std::cout << "Run time: "<< run_time << std::endl;
}
