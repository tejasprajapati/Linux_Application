/* blink.c
 *
 * Raspberry Pi GPIO example using sysfs interface.
 *
 * This file blinks GPIO 4 (P1-07) while reading GPIO 24 (P1_18).
 */
 
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#define IN  				0
#define OUT 				1
 
#define LOW  				0
#define HIGH 				1
 
#define PIN 		 		24													/*	P1-18 */
#define POUT 				4  													/*	P1-07 */

#define DIRECTION_MAX 		35
#define VALUE_MAX 			30
 
static int GPIOExport(int pin)
{
	char buffer[3];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd == -1) 
	{
		perror("Open failed");
		return 1;
	}
 
	bytes_written = snprintf(buffer, 3, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return 0;
}
 
static int GPIOUnexport(int pin)
{
	char buffer[3];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (fd == -1)
	{
		perror("Open failed");
		return 1;
	} 

	bytes_written = snprintf(buffer, 3, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return 0;
}
 
static int GPIODirection(int pin, int dir)
{
	static const char s_directions_str[]  = "in\0out";

	char path[DIRECTION_MAX];
	int fd;
 
	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (fd == -1)
	{
		perror("Open failed");
		return 1;
	}
 
	//if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) 
	if (write(fd, IN == dir ? "in" : "out", IN == dir ? 2 : 3) == -1) 
	{
		perror("Failed to set direction");
		return 1;
	}
 
	close(fd);
	return 0;
}
 
static int GPIORead(int pin)
{
	char path[VALUE_MAX];
	char value_str[3];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
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
 
static int GPIOWrite(int pin, int value)
{
	static const char s_values_str[] = "01";
 
	char path[VALUE_MAX];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (fd == -1) {
		perror("Failed to open gpio value for writing!");
		return 1;
	}
 
	if (write(fd, LOW == value ? "0" : "1", 1) == -1)
	{
		perror("Failed to write value!");
		return 1;
	}
 
	close(fd);
	return 0;
}
 
int main(void)
{
	int i;
	if (GPIOExport(POUT) || GPIOExport(PIN))									/*	Enable GPIO pins*/
		return 1;

	if (GPIODirection(POUT, OUT) || GPIODirection(PIN, IN))						/*	Set GPIO directions*/
		return 2;
 
	for(i = 0; i < 10; i++)
	{
		if (GPIOWrite(POUT, i % 2))										/*	Write GPIO value*/
			return 1;
		printf("I'm reading %d in GPIO %d\n", GPIORead(PIN), PIN);				/*	Read GPIO value*/
 
		usleep(500 * 1000);
	}
 
	if (GPIOUnexport(POUT) || GPIOUnexport(PIN))								/*	Disable GPIO pins*/
		return 1;
 
	return 0;
}