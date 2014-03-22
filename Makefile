UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
  CXX = g++-mp-4.8
else
  CXX = g++
endif

CXXFLAGS = -Wall -std=c++11 -DMAIN

OBJS = $(patsubst %.c,%.o, $(wildcard *.cpp))


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $<

orderbook: OrderBook.o
	$(CXX) -o $@ $^ $(LIBS)

OrderBook.o: OrderBook.cpp OrderBook.h

clean:
	/bin/rm -f orderbook *.o *.s *~ 

asm:
	g++-mp-4.8 -Wall -std=c++11 -DMAIN -S OrderBook.cpp
