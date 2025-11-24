#include "draw.h"

#include "plot.h"
#include "util.h"

static unsigned char lastX=0,lastY=0;

void polyline( unsigned char *base, int count )
{
  for( ; count>0 ; count-- , base+=3 ) {
    switch (base[0])
    {
      case 'M':
        moveTo( base[1], base[2] );
        break;
      case 'D':
        drawTo( base[1], base[2] );
        break;
    }
  }
}

void moveTo( unsigned char x, unsigned char y)
{
  lastX = x;
  lastY = y;
}

unsigned int abs(int x)
{
  return x<0 ? -x : x;
}
  
/* This function lifted from blog.stever.dev */
void line( unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1 )
{
  unsigned char dx = abs(x1-x0);
  unsigned char dy = abs(y1-y0);
  signed char sx   = x0<x1 ? 1:-1;
  signed char sy   = y0<y1 ? 1:-1;
  int         err  = (dx>dy ? dx : -dy ) /2;
  int         e2;
  
  while (1)
  {
    plot(x0,y0);
    if (x0==x1 && y0==y1)
    {
      break;
    }
    
    e2 = err;
    if (e2>-dx)
    {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy)
    {
      err += dx;
      y0 += sy;
    }
  }
}

void drawTo( unsigned char x, unsigned char y)
{
  line( lastX,lastY , x,y );
  moveTo(x,y);
}



