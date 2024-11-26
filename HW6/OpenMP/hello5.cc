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

      start_time=omp_get_wtime();
     
      cout << "Number of threads: "<< endl;
      cin >> nthreads;
      omp_set_num_threads(nthreads);
      #pragma omp parallel
      {
        int mythreadno=omp_get_thread_num();
        int numthreads=omp_get_num_threads();
        //#pragma omp for 
        #pragma omp for nowait
        for (int i=0;i<5;i++){
          #pragma omp critical
          {
            cout << "Hello number: " << i << " from: " << 
                 mythreadno << " out of " << numthreads << endl;
          }
        }
	    //#pragma omp barrier
        #pragma omp critical
        {
          cout << "Outside Hello from: " << mythreadno << endl;
        }
      }
      run_time = omp_get_wtime()-start_time;
      cout << "Run time: "<< run_time << endl;

      return 0;
}
