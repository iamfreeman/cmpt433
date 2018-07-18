#ifndef _BUS1_H_
#define _BUS1_H_

#include "file.h"
#include "sleep.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>



#define I2C_DEVICE_ADDRESS 0x20
#define REG_DIRA 0x00
#define REG_DIRB 0x01
#define REG_OUTA 0x14
#define REG_OUTB 0x15
#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"

#define I2C1_BUS	"/sys/devices/platform/bone_capemgr/slots"
#define GPIO_EXPORT "/sys/class/gpio/export"
#define LEFT_DIGIT_VAL "/sys/class/gpio/gpio61/value"
#define LEFT_DIGIT_DIR "/sys/class/gpio/gpio61/direction"
#define RIGHT_DIGIT_VAL "/sys/class/gpio/gpio44/value"
#define RIGHT_DIGIT_DIR "/sys/class/gpio/gpio44/direction"


int initI2cBus(char* bus, int address);

void writeI2cReg (int i2cFileDesc, unsigned char regAddr, 
							unsigned char value);

unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr);

void initI2C();

void enableLeftDigit();

void enableRightDigit();

void turnOffBothDigits();

void lookup(int number, int* hex_val);

void displayDigits(int numLeft, int numRight);

#endif