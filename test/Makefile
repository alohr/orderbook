UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
  CXX = g++-mp-4.8
  GTEST_DIR = gtest-1.7.0
else
  CXX = g++
endif

CXXFLAGS = -Wall -std=c++11

GTEST_INCLUDE = -I$(GTEST_DIR)/include 
GTEST_LIBS = -L$(GTEST_DIR) -lgtest

INCLUDES = -I.. $(GTEST_INCLUDE)
LIBS = $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $<

%.o: ../%.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $<

orderbooktest: OrderBookTest.o OrderBook.o
	$(CXX) -o $@ $^ $(LIBS)

OrderBook.o: ../OrderBook.cpp
OrderBookTest.o: OrderBookTest.cpp

clean:
	/bin/rm -f orderbooktest *.o *~ 
