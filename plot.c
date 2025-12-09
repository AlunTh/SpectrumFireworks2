//#include <arch/zx.h>
#include "plot.h"

#define SCREEN_BASE 0x4000
#define ATTR_BASE 0x5800

unsigned char *zx_pxy2saddr(unsigned char x, unsigned char y)
{
   // see: http://www.breakintoprogram.co.uk/hardware/computers/zx-spectrum/screen-memory-layout
   return SCREEN_BASE | ((y&0xC0)<<5) | ((y&7)<<8) | ((y<<2)&0xE0) | ((x>>3)&0x1F);
}

unsigned char zx_px2bitmask(unsigned char x)
{
   return 1 << (7-(x & 0x07));
}

void plot(unsigned char x, unsigned char y)
{
   unsigned char y2 = 191-y;
   *zx_pxy2saddr(x,y2) |= zx_px2bitmask(x);
}

void unplot(unsigned char x, unsigned char y)
{
   unsigned char y2 = 191-y;
   *zx_pxy2saddr(x,y2) &= !zx_px2bitmask(x);
}

void invertplot(unsigned char x, unsigned char y)
{
   unsigned char y2 = 191-y;
   *zx_pxy2saddr(x,y2) ^= zx_px2bitmask(x);
}

void setPixelAttr(unsigned char x, unsigned char y, unsigned char a)
{
   unsigned char y2 = 191-y;
   *((unsigned char*)ATTR_BASE+(y2/8)*32+x/8) = a;
}

#define SOLODEBUG 0
#if SOLODEBUG
#include "util.h"
//#link "util.c"
//#resource "util.h"

#include <stdio.h>
void main(int argc, char *argv)
{
  unsigned char x=0,y=0;
  unsigned char *p;
  unsigned char i,j;

  argc=argc, argv=argv;
  p=zx_pxy2saddr(x,y);
  #ifdef DEBUG
    printf("::: %p :::\n\n",p);
  #endif
  p=zx_pxy2saddr(0,8);
  #ifdef DEBUG
    printf("::: %p :::\n\n",p);
  #endif
  plot(x,y);
  
  zx_cls();
  for (j=0; j<256; j++) {
    for (i=0; i<192; i++) {
      plot(j,i);
    }
  }

  while(1);
}
#endif

