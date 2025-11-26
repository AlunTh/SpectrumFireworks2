#define INK(c) (c)
#define PAPER(c) ((c)<<4)


#define BLACK 0
#define BLUE 0x01
#define RED 0x02
#define MAGENTA 0x03
#define GREEN 0x04
#define CYAN 0x05
#define YELLOW 0x06
#define WHITE 0x07

#define BRIGHT 0x40
#define FLASH  0x80

// ------------------------------
#define SV_ATTR_P ((unsigned char *)23693)

void zx_border( unsigned char colour );
void zx_cls( unsigned char attr );
void zx_beep( unsigned int tone, unsigned int dur );

