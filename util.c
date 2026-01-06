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

void zx_border_black()
{
  __asm
	ld a, 0x38
	out (0xFE), a
  __endasm;
  return;
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

void zx_setInputAreaAttrs(void)
{
	unsigned char *p;
	unsigned int i;
	
	for (p=ATTR_BASE+(32*22), i=0 ; i<64 ; p++, i++ )
	{
		*p = *SV_ATTR_P;
	}
}
