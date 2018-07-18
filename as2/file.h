#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include "file.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



int readFromFile(char file[]);

void writeToFile(char file[], char value[]);

#endif