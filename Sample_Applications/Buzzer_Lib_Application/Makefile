TARGET = test_buzzer_lib
SOURCES = test_buzzer_lib.c
HEADERS = gpio.h buzzer.h
OBJECTS = $(SOURCES:.c=.o)

PREFIX = $(DESTDIR)/usr
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include

CC 			 = gcc
FLAGS        = -std=gnu99 -I $(INCDIR)/
CFLAGS       = -Wall
LDFLAGS		 = -L $(LIBDIR) -lgpio -lbuzzer

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(FLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCES)
	rm -rf *.o

clean:
	rm -rf *.o $(TARGET)