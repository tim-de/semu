# Makefile for semu

P_NAME = semu

CC = g++

DEPFILE = .depends
DEPTOKEN = '\#MAKEDEPENDS'
DEPFLAGS = -Y -f $(DEPFILE) -s $(DEPTOKEN)

CFLAGS = -Wall -g

INCLUDES = 
#INCLUDES = any additional include locations go here

LFLAGS = 
#LFLAGS = any library paths go here

LIBS = 
#LIBS = any libraries to link in go here

SRCS = main.cpp State.cpp #_Srcs Add all additional source files here

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
	rm *.o *~ $(MAIN)

depend:
	rm $(DEPFILE)
	make $(DEPFILE)

$(DEPFILE):
	@echo $(DEPTOKEN) > $(DEPFILE)
	makedepend $(DEPFLAGS) -- $(CFLAGS) -- $(SRCS) >&/dev/null

sinclude $(DEPFILE)
