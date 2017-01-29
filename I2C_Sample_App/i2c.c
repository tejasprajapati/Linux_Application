#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "i2c-dev.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int fd;
char ret_val[3];

void i2cOpen()
{
	fd = open("/dev/i2c-2", O_RDWR);
	if (fd < 0) {
		perror("i2cOpen");
		exit(1);
	}
}

void i2cClose()
{
	close(fd);
}

int i2cSetAddress(int address)
{
	if (ioctl(fd, I2C_SLAVE_FORCE, address) < 0) {
		perror("i2cSetAddress");
		return 1;
	}
	return 0;
}

int main(void)
{
	__s32 res;
	int i;

	i2cOpen();

	if(!i2cSetAddress(0x30))
	{
		for(i=0; i< 50; i++)
		{

			res = i2c_smbus_read_word_data(fd, 0x46);
			if (res < 0) {
				/* ERROR HANDLING: i2c transaction failed */
				perror("ERROR READING");
			} else {
				printf("Value read from 0x46 is 0x%x\n",res);
			}
			usleep(100000);

			res = i2c_smbus_write_word_data(fd, 0x46, i);
		}
	}

	i2cClose();

	return 0;
}

