//#include <arch/zx.h>
#include <stdlib.h>
#include "plot.h"
#include "util.h"

//#resource "plot.h"
#include "traceplot.h"

struct tracepoint
{
  unsigned int frame;
  unsigned char x;
  unsigned char y;
};

static struct tracepoint *buffer=NULL;
static int head=0;
static int tail=1;
static int count=0;
static int frame=0;
static int maxpoints=0;
static int persistence=0;

void traceplot_init( int buffsize, int pers )
{
  maxpoints=buffsize;
  persistence=pers;
  buffer = malloc( buffsize*sizeof(struct tracepoint) );
}

void pop(void)
{
  invertplot( buffer[tail].x, buffer[tail].y );
  tail = (tail+1)%maxpoints;
  --count;
}

void push( int frame, unsigned char x, unsigned char y )
{
  invertplot(x,y);
  head = (head+1)%maxpoints;
  ++count;
  buffer[head].frame = frame;
  buffer[head].x = x;
  buffer[head].y = y;
}

void traceplot_newFrame()
{
  ++frame;
  while ( count>0 && buffer[tail].frame+persistence < frame )
  {
    pop();
  }
}


void traceplot( unsigned char x, unsigned char y )
{
  if ( count>=maxpoints )
  {
    pop();
  }
  push( frame, x,y );
}

//#define TEST 1
#ifdef TEST
//#link "util.c"
//#link "plot.c"
int main( int argc, char **argv )
{
  unsigned char x,/*y,*/f;
  argc=argc; argv=argv;
  zx_border(PAPER_BLUE);
  traceplot_init( 1000, 75 );

  /* moving in a line left to right */
  for ( f=0; f<100 ; f++ )
  {
    for ( x=0; x<5 ; x++ )
    {
      traceplot( x*5,f );
    }
    traceplot_newFrame();
  }
}
#endif /* TEST */
