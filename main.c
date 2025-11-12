//#include <arch/zx.h>
#include <stdlib.h>

#include "util.h"
#include "model.h"
#include "plot.h"

//#link "model.c"
//#link "traceplot.c"
//#link "plot.c"
//#link "util.c"
//#resource "traceplot.h"
//#resource "plot.h"

// --------------------------------------

int main( int argc, char **argv )
{
  int i,j;
  argc=argc,argv=argv;
  
  zx_border(INK_BLACK);
  zx_cls(/*PAPER_BLACK+INK_WHITE*/);
  srand(1);

  for (i=25; i<30; i+=2) {
    for (j=0; j<255; j+=3) {
      plot(j,i);
    }
  }

  model_initFireworks(19);

  while( model_mainLoop() )
    ; // empty loop, just call function until false 
  
  model_cleanup();

  zx_border(INK_WHITE);
  return 0;
}

//#link "util.c"

