#ifndef PARAMS
#define PARAMS
struct Params
{
	double deltaT;
 	double density;
	int initUcellx;
	int initUcelly;
	int stepAvg;
	int stepEquil;
	int stepLimit;
 	Vec<int> initUcell;
	double temperature;
	double rCut;
 	Vec<double> region;
	int nAtoms;
	double velMag;
        int sizeHistRdf;
        double rangeRdf;
};
const int NDIM=2;
#endif
