#include "model.h"
#include "show.h"

#ifdef DEBUG
#include <stdio.h>
#endif

void spawn_barage( 
	int count,
	int startx,
	int starty,
	int dx,
	int dy,
	int vx,
	int vy,
	firework_expiryHandler expiryHandler,
	int life,
	int interval
)
{
	int i = 0;
	
	for (i=0 ; i<count ; i++)
	{
		spawnNormal( 
			startx + dx*i,
			starty + dy*i,
			vx,
			vy,
			expiryHandler,
			i*interval,
			i*interval + life
		);
	}
}

