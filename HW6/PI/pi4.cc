#include <iostream>
#include <omp.h>
static long num_steps = 3000000000; 
double step;
#define NUM_THREADS 16
#define PAD 8
int main ()
{ double start_time,run_time;
  step = 1.0/(double) num_steps;
  omp_set_num_threads(NUM_THREADS);

  start_time=omp_get_wtime();

  double sum;
  sum = 0.0;
  #pragma omp parallel reduction(+:sum)
  {
    int id,nthrds;
    long int i;
    double x;
    id = omp_get_thread_num(); 
    nthrds = omp_get_num_threads(); 
    //if (id == 0) nthreads = nthrds;
    for (i=id;i< num_steps; i=i+nthrds) { 
      x = (i+0.5)*step;
      sum += 4.0/(1.0+x*x);
    }
  }
  std:: cout << "Sum is: " << sum*step << std::endl;
  run_time = omp_get_wtime()-start_time;
  std::cout << "Run time: "<< run_time << std::endl;
}
