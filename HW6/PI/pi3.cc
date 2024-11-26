#include <iostream>
#include <omp.h>
static long num_steps = 1000000000; 
double step;
#define NUM_THREADS 4
#define PAD 8
int main ()
{ int i, nthreads; 
  double start_time,run_time;
  double pi=0.0;
  step = 1.0/(double) num_steps;
  omp_set_num_threads(NUM_THREADS);

  start_time=omp_get_wtime();

  #pragma omp parallel 
  {
    int i,id,nthrds;
    double x,sum;
    id = omp_get_thread_num(); 
    nthrds = omp_get_num_threads(); 
    if (id == 0) nthreads = nthrds;
    for (i=id, sum=0.0;i< num_steps; i=i+nthrds) { 
      x = (i+0.5)*step;
      sum += 4.0/(1.0+x*x);
    }
    #pragma omp critical
    pi += sum*step;
  }
  std:: cout << "Sum is: " << pi << std::endl;
  run_time = omp_get_wtime()-start_time;
  std::cout << "Run time: "<< run_time << std::endl;
}
