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
	#pragma omp critical
	{
        cout << "Hello from: " << 
                 mythreadno << " out of " << numthreads << endl;
	}
      }
      run_time = omp_get_wtime()-start_time;
      cout << "Run time: "<< run_time << endl;

      return 0;
}
