#include "myhead.h"
#include "MDsim.h"

void readin(Params & mypars);
void pheader(Params & mypars);
void setparams(Params & mypars);

int main()
{     
      Params simparams;
      readin(simparams);
      setparams(simparams);
      pheader(simparams);

      MDsim mysim(simparams);
      mysim.Initialize();
      for (int step=1; step <= simparams.stepLimit; step++) {
        mysim.SingleStep();
      }
      
      return 0;
}
