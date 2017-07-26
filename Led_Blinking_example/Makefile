CC 			 = gcc
FLAGS        = -std=gnu99 -Iinclude
CFLAGS       = -fPIC -g #-pedantic -Wall
LDFLAGS      = -shared

TARGET = libgpio.so
SOURCES = gpio_in_out_sample.c
HEADERS = gpio.h
OBJECTS = $(SOURCES:.c=.o)

TARGETDIR = gpio
PREFIX = $(DESTDIR)/usr
LIBDIR = $(PREFIX)/lib/$(TARGETDIR)/
INCDIR = $(PREFIX)/include/$(TARGETDIR)/

all: $(TARGET) install

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	rm -rf *.o

install:
	sudo mkdir -p $(LIBDIR)
	sudo mkdir -p $(INCDIR)
	sudo cp -rf $(TARGET) $(LIBDIR)
	sudo cp -rf $(HEADERS) $(INCDIR) 

clean:
	rm -rf *.so *.o