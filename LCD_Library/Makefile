CC 			 = gcc
FLAGS        = -std=gnu99 -Iinclude -lgpio
CFLAGS       = -fPIC -g #-pedantic -Wall
LDFLAGS      = -shared

TARGET = liblcd.so
SOURCES = lcd.c
HEADERS = lcd.h
OBJECTS = $(SOURCES:.c=.o)

TARGETDIR = lcd
PREFIX = $(DESTDIR)/usr
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include

all: $(TARGET) install

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS)
	rm -rf *.o

install:
	sudo mkdir -p $(LIBDIR)
	sudo mkdir -p $(INCDIR)
	sudo cp -rf $(TARGET) $(LIBDIR)
	sudo cp -rf $(HEADERS) $(INCDIR) 

clean:
	rm -rf *.so *.o