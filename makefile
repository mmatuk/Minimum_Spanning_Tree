#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall
MAIN = mstTest

#Source files
SRCS = mstTest.cpp MST.cpp

OBJS = $(SRCS:.cpp=.o)

.PHONY: depend clean

all: $(MAIN)
	@echo build Complete

$(MAIN):$(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

#default: Lab4

# To create the executable file count we need the object files
#
#
#Lab4:  Lab4.o Sorting_Algorithms.o
#	$(CC) $(CFLAGS) -o $(MAIN) Lab4.o Sorting_Algorithms.o
#
#Lab4.o: Lab4.cpp
#	$(CC) $(CFLAGS) -c Lab4.cpp
#
#orting_Algorithms.o: Sorting_Algorithms.cpp Sorting_Algorithms.h
#	$(CC) $(CFLAGS) -c Sorting_Algorithms.cpp
#
# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) *.o *~ $(MAIN)
	@echo here

depend: $(SRCS)
	makedepend $^

run:
	./$(MAIN)

# DO NOT DELETE THIS LINE -- make depend needs it

