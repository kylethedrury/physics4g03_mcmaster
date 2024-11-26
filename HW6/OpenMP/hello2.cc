#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;

int main()
{     
      double start_time,run_time;
      int nthreads;
      int mythreadno,numthreads;

      start_time=omp_get_wtime();
     
      cout << "Number of threads: "<< endl;
      cin >> nthreads;
      omp_set_num_threads(nthreads);
      int i;
      //#pragma omp parallel default(none) 
      //#pragma omp parallel default(none) private(mythreadno,numthreads,i) shared(cout)
      #pragma omp parallel
      {
        mythreadno=omp_get_thread_num();
        numthreads=omp_get_num_threads();
        for (i=0;i<5;i++){
	     #pragma omp critical 
          {
            cout << "Hello number: " << i << " from: " << mythreadno << " out of " << numthreads << endl;
          }
        }
      }
      mythreadno=omp_get_thread_num();
      numthreads=omp_get_num_threads();
      cout << "Hello from otside parallel region from: " << mythreadno << " out of " << numthreads << endl;

      run_time = omp_get_wtime()-start_time;
      cout << "Run time: "<< run_time << endl;

      return 0;
}
