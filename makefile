CC = gcc
CFLAG = -o2 -Wall
DEBUG = -g
OBJS = crc.o main.o
EXEC = run

all : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(EXEC)

clean :
	rm -f *.o
	rm -f $(EXEC)

%.o : %.c
	$(CC) $(CFLAG) -c $+ -o $@
