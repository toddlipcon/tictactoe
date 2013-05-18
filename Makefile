#CC = cc
CC = gcc -Wall -g
#OPTIONS = -g -DDEBUG
#CFLAGS = -O3

# linux
LIBS = -L/usr/local/lib -L/usr/X11/lib -lXm -lXt -lX11 -lSM -lICE
INCPATH = -I/usr/local/include

# hops
#LIBS = -lXm -lXt -lX11
#INCPATH = -I/usr/openwin/include -I/usr/dt/include

CFILES= tictactoe.c callbacks.c procs.c
OFILES= tictactoe.o callbacks.o procs.o

all:    tictactoe

tictactoe: 		$(OFILES)
			$(CC) -o $@ $(OFILES) $(LIBS)

.c.o:	
	$(CC) -c -I. $(INCPATH) $(M_CFLAGS) $(DEFS) $(OPTIONS) $(CFLAGS) $<

clean:
	rm -f $(OFILES)

