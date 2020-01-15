CC = g++

CFLAGS  = -g -Wall -O3
LFLAGS  = -lpthread

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LFLAGS)

clean:
	$(RM) $(TARGET)