.SUFFIXES:.c.o

CC=gcc

SRCS=main.c

OBJS=$(SRCS:.c=.o)

EXE=hello

start:$(OBJS)
	$(CC) -o $(EXE) $(OBJS)
	@echo '----ok---------'
.c.o:
	$(CC) -Wall -g -o $@ -c $<
clean:
	rm -f $(OBJS)
	rm -f core*
