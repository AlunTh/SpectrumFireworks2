
#include "places.h"

#include "draw.h"

//#link "draw.c"

//#link "util.c"

//#link "plot.c"
#include <stdlib.h>
#ifdef DEBUG
  #include <stdio.h>
#endif

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
  //int i,j;
  argc=argc,argv=argv;
  
  zx_border(BLACK);
  zx_cls(PAPER(BLACK)+INK(BLUE));
  #ifdef DEBUG
    printf("\nmain()\n");
  #endif
  
  srand(1);

  polyline( place_vancouver, sizeof(place_vancouver)/3 );
  //polyline( place_london, sizeof(place_london)/3 );

  model_initFireworks(19);

  while( model_mainLoop() )
  {
    ; // empty loop, just call function until false 
  }
  
  model_cleanup();

  zx_border(INK(WHITE));
  return 0;
}

//#link "util.c"

