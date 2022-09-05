# Makefile for semu

P_NAME = semu

CC = gcc

DEPFILE = .depends
DEPTOKEN = '\#MAKEDEPENDS'
DEPFLAGS = -Y -f $(DEPFILE) -s $(DEPTOKEN)

CFLAGS = -Wall -g

INCLUDES = 
#INCLUDES = any additional include locations go here

LFLAGS = 
#LFLAGS = any library paths go here

LIBS = -lstdc++
#LIBS = any libraries to link in go here

SRCS = main.cpp State.cpp MemoryMap.cpp Ram.cpp Peripheral.cpp Port.cpp Utils.cpp #_Srcs Add all additional source files here

#OBJS is defined by replacing .c in every source file by .o
OBJS = $(SRCS:.cpp=.o)

MAIN = main

.PHONY: depend clean

all:	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(P_NAME) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o *~ $(DEPFILE)* $(P_NAME)

depend:
	rm $(DEPFILE)
	make $(DEPFILE)

$(DEPFILE):
	@echo $(DEPTOKEN) > $(DEPFILE)
	makedepend $(DEPFLAGS) -- $(CFLAGS) -- $(SRCS) >&/dev/null

sinclude $(DEPFILE)
