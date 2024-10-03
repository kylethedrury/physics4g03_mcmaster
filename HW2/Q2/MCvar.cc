#ifndef MCVAR_H
#define MCVAR_H

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector> 
#include "MCvar.h" 

template <class Type> class MCvar {
// Data
public:

private:
    int bin_size;           // how many measurements we fit in one bin 
    int count;              // the current number of measurements in a bin
    int no_of_bins;         // the number of bins 
	Type av;                // the sum of data points in current bin 
	vector<double> Bins;    // vector where each element denotes the average of a bin 

// Methods
public:
    MCvar() : bin_size(1000),count(0),no_of_bins(0) {}          // default constructor; 1000 measuremente per bin 
    MCvar(int bsz) : bin_size(bsz),count(0),no_of_bins(0) {}    // constructor for choosing bin size 
       
    void push(const Type v) {  // method for adding a new measurement to the current bin 
        
        if (count == 0) {  // for when there is no measurements in the current bin 
            av = v;
            count += 1;
        }
        
        else if (count < bin_size-1) {  // for when there are measurements in current bin
            av += v;
            count += 1;
        }
        
        else {  // the last measurement in the bin; adds the bin average to the Bins vector, creates a new bin, resets count
            av += v;
            Bins.push_back(((double) av)/bin_size);
            count = 0;
            no_of_bins += 1;
        }

    }

    double Avrg() { // method for calculating the average of all bins  
        
        double res = 0.0;
        for (auto r : Bins) res += r; // sum all the bins 
        return (res/no_of_bins);      // get the average 
    }

    double Err_Avrg() { // method for calculating the error on the average 
        
        double res = 0.0, res2=0.0;
        for (auto r : Bins) {
            res2 += r*r;  // sum all the bins squared                 
        }
        res2 = res2 / no_of_bins;                           // get the second moment 
        res = sqrt((res2 - Avrg()*Avrg())/(no_of_bins-1));  // get the error of average 
        return (res);
    }
};

#endif
