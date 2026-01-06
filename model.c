//#include <arch/zx.h>
//#include <alloc/malloc.h>
#ifdef DEBUG
  #include <stdio.h>
#endif
#include <stdlib.h>

#include "traceplot.h"

#include "model.h"
#include "plot.h"
#include "util.h"

//#link "traceplot.c"
//#resource "traceplot.h"
//#link "plot.c"
//#resource "plot.h"
//#resource "util.h"

static int frames=0;

static int active=0;

void expiry_random_respawn( firework *f );

static struct clock_s
{
  int x;
  int y;
} clock[] = {{0,100},{50,87},{87,50},
             {100,0},{87,-50},{50,-87},
             {0,-100},{-50,-87},{-87,-50},
             {-100,0},{-87,50},{-50,87}};

static firework *fireworks=NULL;
static int maxFireworks = 0;

firework *findUnused( void )
{
  int i;
  for (i=0; i<maxFireworks; i++ )
  {
    if (fireworks[i].type == none )
    {
      return &(fireworks[i]);
    }
  }

  return NULL;
}

void expiry_explode_internal( firework *f, int speed, int life )
{
  int dir;
  firework *newf;
  for ( dir=0; dir<12 ; dir++ )
  {
    newf = findUnused();
    if (newf != NULL )
    {
      newf->type = normal;
      newf->x = f->x;
      newf->y = f->y;
      newf->vx = (f->vx/8)+clock[dir].x*speed/100;
      newf->vy = (f->vy/8)+clock[dir].y*speed/100;
      newf->life = life;
      newf->expiryHandler = NULL;
      if ( active < 10 && rand() % 20 < 3 )
      {
        newf->expiryHandler = expiry_random_respawn;
      }
    }
  }
}

void expiry_explode_big( firework *f )
{
  expiry_explode_internal( f, 100, 30 );
}

void expiry_explode_small( firework *f )
{
  expiry_explode_internal( f, 70, 10 );
}

void expiry_explode_tiny( firework *f )
{
  expiry_explode_internal( f, 60, 8 );
}

void expiry_explode_supertiny( firework *f )
{
  expiry_explode_internal( f, 10, 8 );
}

void expiry_explode_cloud( firework *f )
{
  expiry_explode_internal( f, 30, 50 );
}

void expiry_explode_chained( firework *f )
{
  int speed=25;
  int life=14;
  int dir;
  firework *newf;
  for ( dir=0; dir<12 ; dir++ )
  {
    newf = findUnused();
    if (newf != NULL )
    {
      newf->type = normal;
      newf->x = f->x;
      newf->y = f->y;
      newf->vx = (f->vx/8)+clock[dir].x*speed/100;
      newf->vy = (f->vy/8)+clock[dir].y*speed/100;
      newf->life = life;
      newf->expiryHandler = expiry_explode_supertiny;
    }
  }
}


static firework_expiryHandler explosions[] = {expiry_explode_big, expiry_explode_small, expiry_explode_tiny, expiry_explode_cloud, expiry_explode_chained};

void spawnNormal( 
	int startx,
	int starty,
	int vx,
	int vy,
	firework_expiryHandler expiryHandler,
	int fuse,
	int life
)
{
  firework *newf = findUnused();
  if (newf != NULL )
  {
    newf->type = normal;
    newf->x = startx;
    newf->y = starty;
    newf->vx = vx;
    newf->vy = vy;
    newf->fuse = fuse;
    newf->life = life;
    newf->expiryHandler = expiryHandler;
  }
  #ifdef DEBUG
    else
    {
	  printf("full\n");
    }
  #endif
}
void random_spawn( void )
{
  firework *newf = findUnused();
  int speedpct=100;
  //printf("random_spawn()\n");
  if (newf != NULL )
  {
    int dir;

    dir = ( rand()%3 + 11 ) % 12;
    newf->type = normal;
    newf->x = 16*(128 + 20*(rand()%5-rand()%5));
    newf->y = 0;
    newf->vx = clock[dir].x*speedpct/100;
    newf->vy = ((20+rand()%60)*clock[dir].y/100)*speedpct/100;
    newf->fuse = 0;
    newf->life = (rand()%20+10)*100/speedpct;
    newf->expiryHandler = explosions[ rand()%5 ];
  }
  #ifdef DEBUG
    else
    {
	  printf("full\n");
    }
  #endif
}

void expiry_random_respawn( firework *f )
{
  f = f;
  random_spawn();
}

void model_initFireworks(int n)
{
  int i;
  maxFireworks = n;
  #ifdef DEBUG
    printf("model_initFireworks(%d)\n",n);
  #endif
  fireworks = malloc( sizeof(firework) * maxFireworks );

  traceplot_init( n*10, 10 );

  for (i=0; i<maxFireworks; i++)
  {
    fireworks[i].type = none;
  }

  traceplot_newFrame();
}

void model_cleanup()
{
  free( fireworks );
}

char debug[160];
int model_mainLoop(int respawnOnExpiry)
{
  int i;
  int new_active=0;
  #ifdef DEBUG
    printf("model_mainLoop()\n");
  #endif
  *SV_ATTR_P = PAPER(BLACK)|INK(WHITE);
  for (i=0; i<maxFireworks; i++)
  {
    firework *f = &(fireworks[i]); 
    //printf("%d: t:%d (%d,%d) v:(%d,%d)\n",i,f->type,f->x/16,f->y/16,f->vx,f->vy);
    if ( f->type == none )
    {
      continue;
    }
    if ( f->life==0 )
    {
      f->type = none;
      if ( f->expiryHandler != NULL )
      {
        (*(f->expiryHandler))( f );
      }
      continue;
    }
    
    if ( f->fuse > 0 )
    {
		f->fuse --;
	}
	else
    {
		f->x = (f->x+f->vx);
		f->y = (f->y+f->vy);
		if (f->y < 0 || f->x < 0 
		||  f->y > 191*16 || f->x >255*16 )
		{
		  f->type = none;
		  continue;
		}
		--(f->vy);
		traceplot(f->x/16,f->y/16);
	}
    new_active++;
    --(f->life);

    /*
    if ( rand()%100 == 0 ) {
    	zx_beep( 100+1000*(fireworks[i].vy+fireworks[i].vx), 0.1 );
    }
    */
  }
  active = new_active;
  if ( active == 0 && respawnOnExpiry )
  {
    random_spawn();
    active = 1;
  }

  traceplot_newFrame();

  return active;
}

