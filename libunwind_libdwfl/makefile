CC = g++
CXXFLAGS = -ggdb3 -Wall
INCLUDE = -I./
LIB = -L./ -ltrace
TARGET = test_trace
all : $(TARGET)

$(TARGET) : main.o libtrace.so
	$(CC) $(INCLUDE) main.o -o $(TARGET) $(LIB)
main.o : main.cpp
	$(CC) $(CXXFLAGS) main.cpp -c
libtrace.so: trace.cpp trace.h
	$(CC) -fPIC -shared $(INCLUDE) $(CXXFLAGS) trace.cpp -o libtrace.so -ldw -lunwind

clean :
	rm -f *.o
	rm -f libtrace.so
	rm -f $(TARGET)