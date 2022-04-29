CC = gcc
CFLAG = -o2 -Wall
DEBUG = -g
OBJS = crc.o main.o
OBJS_DEBUG = crc.dbg.o main.dbg.o
EXEC = run

all : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(EXEC)

debug : $(OBJS_DEBUG)
	$(CC) $(CFLAG) $(DEBUG) $(OBJS_DEBUG) -o $(EXEC)

clean :
	rm -f *.o
	rm -f $(EXEC)

%.dbg.o: %.c
	$(CC) $(CFLAG) $(DEBUG) -c $+ -o $@

%.o : %.c
	$(CC) $(CFLAG) -c $+ -o $@
