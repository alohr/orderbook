CXX = g++-mp-4.8
CXXFLAGS = -Wall -std=c++11 -DMAIN

OBJS = $(patsubst %.c,%.o, $(wildcard *.cpp))

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $<


orderbook: OrderBook.o
	$(CXX) -o $@ $^ $(LIBS)

clean:
	/bin/rm -f orderbook *.o *~ 

