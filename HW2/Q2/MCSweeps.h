#ifndef MCSWEEPS_H
#define MCSWEEPS_H 

#include <vector> 

using namespace std; 

// Function declerations 

void MCSweeps(vector<vector<int>>& arr, int Nmcs, double J);

double Energy(vector<vector<int>>& arr, double J);

int Magnetization(vector<vector<int>>& arr);

#endif // MCSWEEPS_H 
