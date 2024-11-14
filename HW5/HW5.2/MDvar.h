#ifndef MDVAR
#define MDVAR
#include <iostream>
#include <algorithm>
#include <math.h>
#include <valarray>

template <class Type> class MDvar {
// Data
public:

private:
        int index;
	Type sum;
	double ssq;

//Methods
public:
        MDvar() { index =0;}
        void zero() {
          index=0;
          sum = 0.0;
          ssq = 0.0;
        }
        void push(const Type v)
	{ 
                if (index == 0) {
                        sum = v;
                        ssq = ((double) v)*((double) v);
                        index += 1;
                }else {
                        sum += v;
                        ssq += ((double) v)*((double) v);
                        index += 1;
                }
        }
        double Avrg()
	{      double res = sum/((double) index);
               return (res);
        }
        double SecMoment()
	{       double res = ssq/((double) index);
                return (res);
        }
        double Err_Avrg()
	{ 
                double res = sum,res2=ssq;
                res /= index;
                res2 /= index;
                res = sqrt((res2-res*res)/((double)index));
                return (res);
        }
};
#endif
