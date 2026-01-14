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

void zx_fadeAttrs(void) {
	#define step 3
	unsigned char *p, *endp;
	static unsigned char o=step-1;
	
	o = (o+1)%step;
	for (p=ATTR_BASE+o, endp=ATTR_BASE+(32*24); p<endp ; p+=step )
	{
		switch (*p)
		{
			case 65:
				*p = 1;
				break;
			case 5:
				*p = 65;
				break;
			case 69:
				*p = 5;
				break;
			case 71:
				*p = 69;
		}
	}
}
