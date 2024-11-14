#include "myhead.h"
#include "Vec2D.h"
#include "params.h"

void setparams(Params & mypars)
{	mypars.initUcell.set_values(mypars.initUcellx,mypars.initUcelly);
        mypars.rCut = pow(2.0,1.0/6.0);
	double s=1;
	mypars.region.set_values(s*mypars.initUcellx,s*mypars.initUcelly);
	mypars.nAtoms = mypars.initUcell.VProd();
        mypars.velMag = sqrt(NDIM*(1.0-1.0/mypars.nAtoms)*mypars.temperature);
}
