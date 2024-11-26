#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
#include <omp.h>
using namespace std;

int main()
{     
      double start_time,run_time;
      int nthreads;
      int mythreadno,numthreads,i;

      start_time=omp_get_wtime();
     
      cout << "Number of threads: "<< endl;
      cin >> nthreads;
      omp_set_num_threads(nthreads);
      #pragma omp parallel default(none)  private(i,mythreadno,numthreads) shared(cout) 
      //#pragma omp parallel default(none)
      {
        #pragma omp for 
        for (i=0;i<10;i++){
          mythreadno=omp_get_thread_num();
          numthreads=omp_get_num_threads();
	      #pragma omp critical
          {
            cout << "Hello number: " << i << " from: " << mythreadno << " out of " << numthreads << endl;
          }
        }
      }
      run_time = omp_get_wtime()-start_time;
      cout << "Run time: "<< run_time << endl;

      return 0;
}
