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
      int mythreadno,numthreads,i=0;

      start_time=omp_get_wtime();
     
      cout << "Number of threads: "<< endl;
      cin >> nthreads;
      omp_set_num_threads(nthreads);
      {
        #pragma omp parallel for default(none)  private(mythreadno,numthreads) shared(cout) lastprivate(i)
        //#pragma omp parallel for default(none)  private(mythreadno,numthreads,i) shared(cout) 
        for (i=0;i<5;i++){
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
      cout << "i is: " << i << endl;

      return 0;
}
