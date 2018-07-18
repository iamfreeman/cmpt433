// sorter.h
// Module to spawn a separate thread to sort random arrays 
// (permutations) on a background thread. It provides access to the
// contents of the current (potentially partially sorted) array, 
// and to the count of the total number of arrays sorted.
#ifndef _SORTER_H_
#define _SORTER_H_


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "file.h"
#include "sleep.h"
#include "bus1.h"


#define A2D_FILE_VOLTAGE0  "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define SLOT_ADDR "/sys/devices/platform/bone_capemgr/slots"
#define A2D_VOLTAGE_REF_V  1.8
#define A2D_MAX_READING    4095






// Begin/end the background thread which sorts random permutations.
void Sorter_startSorting();
void Sorter_freeArray(void);
void Sorter_initArray(void);
// Get the size of the array currently being sorted.
// Set the size the next array to sort (don’t change current array)
void Sorter_setArraySize();
//int Sorter_getArrayLength(void);

// Get a copy of the current (potentially partially sorted) array.
// Returns a newly allocated array and sets 'length' to be the 
// number of elements in the returned array (output-only parameter).
// The calling code must call free() on the returned pointer.
//int* Sorter_getArrayData(int *length);

// Get the number of arrays which have finished being sorted.
//long long Sorter_getNumberArraysSorted(void);


void Display_numberofSortedArray_lastSecond();
int Convert_potVal_toArraySize(int potVal);


void initADC();

void printArray(int* arr, int length);
void bubbleSort();



#endif