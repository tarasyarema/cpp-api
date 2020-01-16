CC = g++
RM = rm -rf

CFLAGS   = -Wall -Werror -pedantic -Ofast
_CFLAGS  = -g -O0
LFLAGS   = -lpthread -lm

TARGET = main
TEST = test

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LFLAGS)

fast:
	$(CC) $(_CFLAGS) $(TARGET).cpp -o $(TARGET) $(LFLAGS)

test:
	$(RM) $(TEST) && $(CC) $(_CFLAGS) $(TEST).cpp -o $(TEST) $(LFLAGS)

clean:
	$(RM) $(TARGET) $(TEST)
