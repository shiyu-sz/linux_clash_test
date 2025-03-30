CC = gcc
CXXFLAGS = -ggdb3 -Wall
INCLUDE = -I./
LIB = -L./ -ltrace
TARGET = test_trace
all : $(TARGET)

$(TARGET) : main.o libtrace.so
	$(CC) $(INCLUDE) main.o -o $(TARGET) $(LIB)
main.o : main.c
	$(CC) $(CXXFLAGS) main.c -c
libtrace.so: trace.c trace.h
	$(CC) -fPIC -shared $(INCLUDE) $(CXXFLAGS) trace.c -o libtrace.so -ldw -lunwind

clean :
	rm -f *.o
	rm -f libtrace.so
	rm -f $(TARGET)