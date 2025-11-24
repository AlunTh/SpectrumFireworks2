#define INK(c) (c)
#define PAPER(c) ((c)<<8)


#define BLACK 0
#define BLUE 0x01
#define RED 0x02
#define MAGENTA 0x03
#define GREEN 0x04
#define WHITE 0x07

void zx_border( unsigned char colour );
void zx_cls( void );
void zx_beep( unsigned int tone, unsigned int dur );

