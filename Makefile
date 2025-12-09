OBJECTS = main.o model.o plot.o traceplot.o draw.o util.o

# -startup=31 has no stdio

DEBUGBUILD=""
STARTUP=31

all: fireworks

fireworks: $(OBJECTS)
	zcc +zx -vn --opt-code-speed=all -clib=sdcc_iy -startup=$(STARTUP) -lmath16 -o fireworks -create-app $(OBJECTS)

debug: DEBUGBUILD="-DDEBUG"
debug: STARTUP=0
debug: clean fireworks

.c.o:
	zcc +zx -vn --opt-code-speed=all $(DEBUGBUILD) -clib=sdcc_iy -startup=$(STARTUP) $< -c -o $@ 

clean:
	-rm *.o *.bin *.tap
