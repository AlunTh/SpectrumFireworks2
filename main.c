
#include "places.h"

#include "draw.h"

//#link "draw.c"

//#link "util.c"

//#link "plot.c"
#include <stdlib.h>
#include <input.h>
#include <input/input_zx.h>
#ifdef DEBUG
  #include <stdio.h>
#endif

#include "util.h"
#include "model.h"
#include "plot.h"
#include "show.h"
#include "traceplot.h"

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
  
  zx_cls((BLACK)+INK(BLUE));
  zx_setInputAreaAttrs();
  zx_border_black();
  #ifdef DEBUG
    printf("\nmain()\n");
  #endif
  
  srand(1);

  polyline( place_castell_coch, sizeof(place_castell_coch)/3 );
  //polyline( place_vancouver, sizeof(place_vancouver)/3 );
  //polyline( place_london, sizeof(place_london)/3 );

  model_initFireworks(150);
  
  spawn_barage( 3,  160,160,  320,0,  16,64,  expiry_explode_tiny, 80, 30);
  spawn_barage( 3, 240*16,160,  -320,0,  -16,64,  expiry_explode_tiny, 80, 30);

  while( model_mainLoop(1) )
  {
	  switch (in_inkey())
	  {
		  case 'v':
			zx_cls((BLACK)+INK(BLUE));
			zx_border_black();
			zx_setInputAreaAttrs();
            polyline( place_vancouver, sizeof(place_vancouver)/3 );
            traceplot_clear();
            break;
		  case 'l':
			zx_cls((BLACK)+INK(BLUE));
			zx_border_black();
			zx_setInputAreaAttrs();
            polyline( place_london, sizeof(place_london)/3 );
            traceplot_clear();
            break;
		  case 'c':
			zx_cls((BLACK)+INK(BLUE));
			zx_border_black();
			zx_setInputAreaAttrs();
            polyline( place_castell_coch, sizeof(place_castell_coch)/3 );
            traceplot_clear();
            break;
          default:
            break;
	  }
  }
  
  model_cleanup();

  return 0;
}

//#link "util.c"

