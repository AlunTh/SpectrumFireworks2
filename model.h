#ifndef MODEL_H
#define MODEL_h

#include <stdbool.h>

typedef struct firework_s firework;
typedef void (*firework_expiryHandler)( firework *f );

enum firework_type {
  none=0,
  normal=1
};

struct firework_s
{
  enum firework_type type;
  int x;
  int y;
  int vx;
  int vy;
  int fuse;
  int life;
  firework_expiryHandler expiryHandler;
};

int model_mainLoop(int respawnOnExpiry);
void model_initFireworks(int n);
void model_cleanup();
void spawnFuse( int timer, firework_expiryHandler expiryHandler );
void spawnNormal( 
	int startx,
	int starty,
	int vx,
	int vy,
	firework_expiryHandler expiryHandler,
	int fuse,
	int life
);

void expiry_explode_big( firework *f );
void expiry_explode_small( firework *f );
void expiry_explode_tiny( firework *f );
void expiry_explode_supertiny( firework *f );
void expiry_explode_cloud( firework *f );
void expiry_explode_chained( firework *f );
#endif /* MODEL_H */

