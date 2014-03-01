TARGET=nxt_service
OBJECTS=nxt_service.o serialPort.o
VPATH=src
CC=gcc
CFLAGS=-Wall
LDFLAGS=
LIBS=

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^$(LIBS)
	$(RM) $(OBJECTS)

.PHONY: clean	
clean:
	$(RM) $(TARGET) $(OBJECTS)