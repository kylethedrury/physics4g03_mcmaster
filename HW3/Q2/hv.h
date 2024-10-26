#ifndef HV_H
#define HV_H

#include <vector> 

using namespace std;

// Macros for bit manipulation
#define BIT_SET(a,b) ((a) |= (1U<<(b)))                                                     // sets bit b in var a to 1
#define BIT_CLEAR(a,b) ((a) &= ~(1U<<(b)))                                                  // clears the bit b in var a (set to 0)
#define BIT_FLIP(a,b) ((a) ^= (1U<<(b)))                                                    // flips the bit b in var a
#define BIT_CHECK(a,b) ((bool)((a) & (1U<<(b))))                                            // checks if bit b in var a is set (is 1)
#define COND_BIT_SET(a,b,f) ((a) = ((a) & ~(1U<<(b))) | ((-(unsigned int)f) & (1U<<(b))))   // conditionally clears or sets bit b depending on flag f

// Function declaration
Row hv (const Row &x, int L); 

#endif // HV_H
