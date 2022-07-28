.SUFFIXES: .c .o

CC=gcc
ASRCS=myfifo1.c			
BSRCS=myfifo2.c
	
AOBJS=$(ASRCS:.c=.o)
BOBJS=$(BSRCS:.c=.o)

AEXEC=myfifo1
BEXEC=myfifo2

all:$(AOBJS) $(BOBJS)
	$(CC) -o $(AEXEC) $(AOBJS) -lpthread
	$(CC) -o $(BEXEC) $(BOBJS) -lpthread
	@echo '-------------ok--------------'

.c.o:
	$(CC) -Wall -g -o $@ -c $< 

clean:
	rm -f $(AOBJS)
	rm -f $(BOBJS)
	rm -f core*

