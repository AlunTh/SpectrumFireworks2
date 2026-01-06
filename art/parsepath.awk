#!/bin/awk -f

# TO FIX:
# Y co-ords inverted
# X range not right ?
# some long jumps ?
# mountain horizon partialy missing ?
# sequences of multiple (M)oves
# some negative coords

BEGIN {
  cx=0;
  cy=0;
  inshape=0;
  startx=0;
  starty=0;
  printf( "{ 'M', 0, 0" );

  width="256"
  height="192"
  viewWidth=67.733332;
  viewHeight=50.8;
}

END {
  printf( "};\n" );
}

function toX(x)
{
  return (x/viewWidth)*width;
}

function toY(y)
{
  return height-(y/viewHeight)*height;
}

function move(x,y)
{
  printf( ", 'M', %d, %d\n", toX(x)+0.5, toY(y)+0.5 );
  cx = x;
  cy = y;
  inshape=0;
  startx=cx;
  starty=cy;
}

function line(x,y)
{
  printf( ", 'D', %d, %d\n", toX(x)+0.5, toY(y)+0.5 );
  cx = x;
  cy = y;
  if (!inshape)
  {
    inshape=1;
  }
}

function curve(x,y,c1x,c1y,c2x,c2y)
{
  line(x,y);
}

{
  text = $0;
# space after each command
# (don't treat "e" as a command so that scientific notation numbers aren't split)
  gsub(/([a-df-zA-DF-Z])/,"& ",text);
# commas to spaces
  gsub(/,/," ",text);
# remove double space
  gsub(/  */," ",text);
  n = split(text,word);

  i=1;
  while (i<=n) {
    cmd = word[i++];
    printf( "/* " NR ":" (i-1) " " cmd " p:" previousCmd " */ " );
    # printf( "\n%d,%s (%s)\n",i-1,cmd,previousCmd );

    if (cmd ~ /^[+\-0-9.]/ )
    {
      # no command, reuse previous command
      if (previousCmd=="M")
      {
        cmd = "L";
      }
      else if (previousCmd=="m")
      {
        cmd = "l";
      }
      else
      {
        cmd = previousCmd;
      }
      i--;
    }
    else
    {
      previousCmd = cmd;
    }

    if (cmd=="m")
    {
      dx = word[i++];
      dy = word[i++];
      move(cx+dx,cy+dy);
    }
    else if (cmd=="M")
    {
      move(word[i++],word[i++]);
    }
    else if (cmd=="Z" || cmd=="z")
    {
      # close path
      if (inshape)
      {
      	line(startx,starty);
      	inshape=0;
      }
      else
      {
      	print( "/* z when not in shape */" );
      }
    }
    else if (cmd=="l")
    {
      dx = word[i++];
      dy = word[i++];
      line(cx+dx,cy+dy);
    }
    else if (cmd=="L")
    {
      line(word[i++],word[i++]);
    }
    else if (cmd=="h")
    {
      dx = word[i++];
      line(cx+dx,cy);
    }
    else if (cmd=="H")
    {
      line(word[i++],cy);
    }
    else if (cmd=="v")
    {
      dy = word[i++];
      line(cx,cy+dy);
    }
    else if (cmd=="V")
    {
      line(cx,word[i++]);
    }
    else if (cmd=="c")
    {
      dx = word[i++];
      dy = word[i++];
      dc1x = word[i++];
      dc1y = word[i++];
      dc2x = word[i++];
      dc2y = word[i++];
      curve(cx+dx,cy+dy,cx+dc1x,cy+dc1y,cx+dc2x,cy+dc2y);
    }
    else if (cmd=="C")
    {
      x = word[i++];
      y = word[i++];
      c1x = word[i++];
      c1y = word[i++];
      c2x = word[i++];
      c2y = word[i++];
      curve(x,y,c1x,c1y,c2x,c2y);
    }
    else
    {
    	print( "/* cmd: " cmd " */");
    }
  }
}
