#include "myhead.h"
#include "Vec2D.h"
#include "params.h"

void readin(Params & mypars)
{	cout << "deltaT: ";
    cin >> mypars.deltaT;
	cout << "Density: ";
	cin >> mypars.density; 
	cout << "initUcellx: ";
	cin >> mypars.initUcellx; 
	cout << "initUcelly: ";
	cin >> mypars.initUcelly; 
	cout << "stepAvg: ";
	cin >> mypars.stepAvg; 
	cout << "stepEquil: ";
	cin >> mypars.stepEquil; 
	cout << "stepLimit: ";
	cin >> mypars.stepLimit; 
	cout << "Temperature: ";
	cin >> mypars.temperature; 
	cout << endl;
}
