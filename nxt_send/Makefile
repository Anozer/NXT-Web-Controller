TARGET=nxt_send.cgi
OBJECTS=nxt_send.o
VPATH=src
CC=gcc
CFLAGS=-Wall
LDFLAGS=
LIBS=

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(RM) $(OBJECTS)

.PHONY: clean	
clean:
	$(RM) $(TARGET) $(OBJECTS)