#include "myhead.h"
#include "Vec2D.h"
#include "params.h"

void pheader(Params & mypars)
{	cout << "deltaT: ";
        cout << mypars.deltaT;
        cout << endl;
	cout << "Density: ";
	cout << mypars.density; 
        cout << endl;
	cout << "initUcell: ";
	cout << mypars.initUcellx; 
	cout << " ";
	cout << mypars.initUcelly; 
        cout << endl;
	cout << "stepAvg: ";
	cout << mypars.stepAvg; 
	cout << endl;
	cout << "stepEquil: ";
	cout << mypars.stepEquil; 
	cout << endl;
	cout << "stepLimit: ";
	cout << mypars.stepLimit; 
	cout << endl;
	cout << "Temperature: ";
	cout << mypars.temperature; 
	cout << endl;
	cout << "region: ";
	cout << mypars.region.x; 
	cout << " ";
	cout << mypars.region.y; 
	cout << endl;
	cout << "nAtoms: ";
	cout << mypars.nAtoms; 
	cout << endl;
	cout << "velMag: ";
	cout << mypars.velMag; 
	cout << endl;
	cout << "rCut: ";
	cout << mypars.rCut; 
	cout << endl;
	cout << "sizeHistRdf: ";
	cout << mypars.sizeHistRdf; 
	cout << endl;
	cout << "rangeRdf: ";
	cout << mypars.rangeRdf; 
	cout << endl;
}
