#include "bus1.h"

int i2cFileDesc = 0;

int initI2cBus(char* bus, int address){
	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is:");
		exit(1);
	}

	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("I2C: Unable to set I2C device to slave address.");
		exit(1);
	}
	return i2cFileDesc;
}

void writeI2cReg (int i2cFileDesc, 
							unsigned char regAddr, unsigned char value)
{
	unsigned char buff[2];
	buff[0] = regAddr;
	buff[1] = value;
	int res = write(i2cFileDesc, buff, 2);
	if (res != 2) {
		perror("I2C: Unable to write i2c register.");
		exit(1);
	}
}

unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr)
{
// To read a register, must first write the address
	int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
	if (res != sizeof(regAddr)) {
		perror("I2C: Unable to write to i2c register.");
		exit(1);
	}
// Now read the value and return it
	char value = 0;
	res = read(i2cFileDesc, &value, sizeof(value));
	if (res != sizeof(value)) {
		perror("I2C: Unable to read from i2c register");
		exit(1);
	}
	return value;
}

void initI2C(){
	writeToFile(I2C1_BUS,"BB-I2C1");//enable bus 1
	writeToFile(GPIO_EXPORT, "61");//enable left digit
	writeToFile(GPIO_EXPORT, "44");//enable right digit
	writeToFile(LEFT_DIGIT_DIR, "out");//set direction of the pin to out (because lighting on is output)
	writeToFile(LEFT_DIGIT_VAL,"1");//set 1 to the value file to allow the digit to be turned on
	writeToFile(RIGHT_DIGIT_DIR, "out");//set direction of the pin to out (because lighting on is output)
	writeToFile(RIGHT_DIGIT_VAL,"1");//set 1 to the value file to allow the digit to be turned on
	i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
	writeI2cReg(i2cFileDesc, REG_DIRA, 0x00); //the default value is ff, change to 00
	writeI2cReg(i2cFileDesc, REG_DIRB, 0x00); //the default value is ff, change to 00
	close(i2cFileDesc);
}

void enableLeftDigit(){
	writeToFile(LEFT_DIGIT_VAL, "1");
	
}

void enableRightDigit(){
	writeToFile(RIGHT_DIGIT_VAL, "1");
	
}

void turnOffBothDigits(){
	writeToFile(RIGHT_DIGIT_VAL, "0");
	writeToFile(LEFT_DIGIT_VAL, "0");
}

void lookup(int number, int* hex_val){
	
	switch(number){
		case 0:
			hex_val[0] = 0xA1;
			hex_val[1] = 0x86;
      			break;
		case 1:
			hex_val[0] = 0x80;
			hex_val[1] = 0x02;
      			break;
		case 2:
			hex_val[0] = 0x31;
			hex_val[1] = 0x0E;
      			break;
		case 3:
			hex_val[0] = 0xB0;
			hex_val[1] = 0x0E;
      			break;
		case 4:
			hex_val[0] = 0x90;
			hex_val[1] = 0x8A;
      			break;
		case 5:
			hex_val[0] = 0xB0;
			hex_val[1] = 0x8C;
      			break;
		case 6:
			hex_val[0] = 0xB1;
			hex_val[1] = 0x8C;
      			break;
		case 7:
			hex_val[0] = 0x80;
			hex_val[1] = 0x06;
      			break;
		case 8:
			hex_val[0] = 0xB1;
			hex_val[1] = 0x8E;
      			break;
		case 9:
			hex_val[0] = 0x90;
			hex_val[1] = 0x8E;
	}
}

void displayDigits(int numLeft, int numRight){
	int* hexVal_left =  malloc(2 * sizeof(int));
	int* hexVal_right =  malloc(2 * sizeof(int));
	lookup(numLeft, hexVal_left);
	lookup(numRight, hexVal_right);

	int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS); //need to open this to write to 14 seg display

	//display left
	turnOffBothDigits();
	enableLeftDigit();	
	writeI2cReg(i2cFileDesc, REG_OUTA, hexVal_left[0]);
	writeI2cReg(i2cFileDesc, REG_OUTB, hexVal_left[1]);
	Sleeeep(0, 5000000); //sleep for 5 ms = 5000000ns

	//dispaly right
	turnOffBothDigits();
	enableRightDigit();
	writeI2cReg(i2cFileDesc, REG_OUTA, hexVal_right[0]);
	writeI2cReg(i2cFileDesc, REG_OUTB, hexVal_right[1]);
	Sleeeep(0, 5000000); //sleep for 5 ms = 5000000ns

	free(hexVal_left);
	free(hexVal_right);
	close(i2cFileDesc);
}