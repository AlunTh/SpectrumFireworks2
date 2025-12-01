
#include "places.h"

#include "draw.h"

//#link "draw.c"

//#link "util.c"

//#link "plot.c"
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

unsigned char test[] = { 'M',10,10, 'D',110,60, 'D',0,120, 'M',110,65, 'D',210,10 }; 
unsigned char test2[] ={ 'M',0,0, 'D',255,0, 'D',255,191, 'D',0,191, 'D',0,0 }; 

int main( int argc, char **argv )
{
  //int i,j;
  argc=argc,argv=argv;
  
  zx_border(BLACK);
  zx_cls(PAPER(BLACK)+INK(BLUE));
  srand(1);

  /*
  for (i=25; i<30; i+=2) {
    for (j=0; j<255; j+=3) {
      plot(j,i);
    }
  }
  moveTo(10,191);
  drawTo(20,191);
  moveTo(10,15);
  drawTo(20,15);
  */
  //polyline( test2, sizeof(test2)/3 );
  //polyline( test, sizeof(test)/3 );
  //polyline( place_vancouver, sizeof(place_vancouver)/3 );
  polyline( place_london, sizeof(place_london)/3 );

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

