/*
 * gpio.h
 *
 *  Created on: Jul 26, 2017
 *      Author: Tejas Laptop
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define IN  				0
#define OUT 				1

#define PIN 		 		24													/*	P1-18 */
#define POUT 				4  													/*	P1-07 */
#define DIRECTION_MAX 		35
#define VALUE_MAX 			30


int GPIOExport(int);

int GPIOUnexport(int);

int GPIODirection(int, int);

int GPIORead(int);

int GPIOWrite(int, int);

#endif /* GPIO_H_ */
