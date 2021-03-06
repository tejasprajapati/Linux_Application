/* blink.c
 *
 * Raspberry Pi GPIO example using sysfs interface.
 *
 * This file blinks GPIO 4 (P1_07) while reading GPIO 24 (P1_18).
 */
 
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gpio.h"
 
#define IN  				0
#define OUT 				1

#define PIN 		 		24													/*	P1-18 */
#define POUT 				4  													/*	P1-07 */
#define DIRECTION_MAX 		35
#define VALUE_MAX 			30


int GPIOExport(int pin)
{
	char buffer[3];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/export", O_WRONLY, S_IRWXU);
	if (fd == -1) 
	{
		printf("Open failed Line number :%d ", __LINE__);
		return 1;
	}
 
	bytes_written = snprintf(buffer, 3, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return 0;
}
 
int GPIOUnexport(int pin)
{
	char buffer[3];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/unexport", O_WRONLY, S_IRWXU);
	if (fd == -1)
	{
		printf("Open failed Line number :%d ", __LINE__);
		return 1;
	} 

	bytes_written = snprintf(buffer, 3, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return 0;
}
 
int GPIODirection(int pin, int dir)
{
	char path[DIRECTION_MAX];
	int fd;
 
	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);

	fd = open(path, O_WRONLY, S_IRWXU);
	if (fd == -1)
	{
		perror("error");
		return -1;
	}

	if (write(fd, dir == IN ? "in" : "out", dir == IN ? 2 : 3) == -1)
	{
		perror("Failed to set direction");
		return 1;
	}
 
	close(fd);
	return 0;
}
 
int GPIORead(int pin)
{
	char path[VALUE_MAX];
	char value_str[3];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY, S_IRWXU);
	if(fd == -1)
	{
		perror("Failed to open gpio value for reading!");
		return 1;
	}
 
	if (read(fd, value_str, 3) == -1) 
	{
		perror("Failed to read value!");
		return 1;
	}
 
	close(fd);
 
	return atoi(value_str);
}
 
int GPIOWrite(int pin, int value)
{
	char path[VALUE_MAX];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY, S_IRWXU);
	if (fd == -1) {
		perror("Failed to open gpio value for writing!");
		return 1;
	}
 
	if (write(fd, value == 0 ? "0" : "1", 1) == -1)
	{
		perror("Failed to write value!");
		return 1;
	}
 
	close(fd);
	return 0;
}

/*int main(void)
{
	int i;
	GPIOExport(POUT);																Enable GPIO pins
	sleep(1);

	GPIODirection(POUT, OUT);														Set GPIO directions
 
	for(i = 0; i < 10; i++)
	{
		printf("Writing gpio\n");
		if (GPIOWrite(POUT, i % 2))													Write GPIO value
		printf("I'm reading %d in GPIO %d\n", GPIORead(PIN), PIN);					Read GPIO value
		usleep(500 * 1000);
	}
 
	GPIOUnexport(POUT);																Disable GPIO pins
	return 0;
}*/
