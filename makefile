#
#shortload: shortload.o
#	echo "compiling"
#	cc shortload.o -o shortload
#
#shortload.o: shortload.c
#	echo "object file"
#	cc -r shortload.c -o shortload.o
#clean:
#	rm -f shortload.o
#recompile:
#	rm -f shortload
#
OBJS = mainloop.c
CC = gcc
COMPILER_FLAGS = -w
LINKER_FLAGS = -L/usr/local/lib -lSDL2
obj_name = game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(obj_name)
speedtest : speedtest.c
	$(CC) -r speedtest.c -o speedtest.o
	$(CC) speedtest.o -o speedtest
	rm -f speedtest.o
