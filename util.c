#include "util.h"


int putchar(int ch) {
  if (ch == 10) ch = 13; // newline -> CR
  __asm
    ld	a,4 (ix)
    rst 0x10
  __endasm;
  return ch;
}

// ---------------------------------------

void zx_border( unsigned char colour )
{
  *((unsigned char *)0x5C48) = colour;
}


void zx_cls( unsigned char attr )
{
  *SV_ATTR_P = attr;
  __asm
    call 0x0d6b
  __endasm;
  return;
}

void zx_beep( unsigned int tone, unsigned int dur )
{
  tone;
  dur;
  
  __asm
    ld l, (iy)
    ld h, 1(iy)
    ld e, 2(iy)
    ld d, 3(iy)
    ; mov l,dpl
    call 0x03b5
  __endasm;
  
  return;
}

