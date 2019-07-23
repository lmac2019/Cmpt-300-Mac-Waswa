TARGET = cs300_testapp
OBJS = cs300_testapp.o

CFLAGS = -g -std=c99 -D _GNU_SOURCE -static
CC = gcc

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)