#include "sorter.h"


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int currSize = 100;
int nextSize = 100;
int* arr = NULL;
int count = 0;
int count_temp = 0;
int count_preSec = 0;


extern bool stop;


void initADC(){
	writeToFile(SLOT_ADDR, "BB-ADC");//turn on ADC virtual cape for reading potentiometer value to set array size
	Sleeeep(1, 0); //give some time to make sure /sys/bus/iio/devices/iio:device0/in_voltage0_raw is created
}


void bubbleSort(){
	int swap = 0;
	for (int i = 0 ; i < currSize - 1; i++){
	    for (int j = 0 ; j < currSize - i - 1; j++){
	    	pthread_mutex_lock(&lock);

	    	if (arr){ //check if the array is freed (means sorting is stopped)
	    		if (arr[j] > arr[j+1]){
					swap       = arr[j];
					arr[j]   	= arr[j+1];
					arr[j+1] = swap;
				}
	    	}
			
	      	pthread_mutex_unlock(&lock);
	    }
	}
}


void printArray(int* arr, int length){
	for (int i = 0; i < length; i++){
		printf("%i ", arr[i]);
	}
	//printf("\n");
}




int Convert_potVal_toArraySize(int potVal){
	int size = 1;
	if (potVal > 0 && potVal < 500)	
		size = (int) potVal / 26.3;
	else if (potVal >= 500 && potVal <= 1000) 
		size = 20 + (int) (potVal-500)/12.5;
	else if (potVal >= 1000 && potVal <= 1500)
		size = 60 + (int) (potVal-1000)/8.3;
	else if (potVal >= 1500 && potVal <= 2000)
		size = 120 + (int) (potVal-1500)/3.846;
	else if (potVal >= 2000 && potVal <= 2500)
		size = 250 + (int) (potVal - 2000)/10;
	else if (potVal >= 2500 && potVal <= 3000)
		size = 300 + (int) (potVal-2500)/2.5;
	else if (potVal >= 3000 && potVal <= 3500)
		size = 500 + (int) (potVal-3000)/1.667;
	else if (potVal >= 3500 && potVal <= 4000)
		size = 800 + (int) (potVal-3500)/1.25;
	else if (potVal >= 4000 && potVal <= 4100)
		size = 1200 + (int) (potVal-4000)/0.11;
	return size;
}

void Sorter_startSorting(void){
	// printf("sorter thread starts\n");
	//malloc an array on heap with values 1 through the size of the array
	while (!stop){
		pthread_mutex_lock(&lock);

		//printf("\narray size = %i\n", size);
		arr = realloc(arr, nextSize * sizeof(int));
		currSize = nextSize;
		for (int i=0; i < currSize; i++){
			arr[i] = i;
		}
		//swap every element with another randomly selected elemenmt 
		for (int i=0; i < currSize; i++){
			int swap_index = rand()% currSize;
			int temp = arr[swap_index];
			arr[swap_index] = arr[i];
			arr[i] = temp;
		}
		pthread_mutex_unlock(&lock);

		bubbleSort();

		Sorter_freeArray();
		count ++;	

		//pthread_mutex_unlock(&lock);	
	}
}

void Sorter_setArraySize(){
	
	while(!stop){
		//calculate how many arrays sorted in previous second
		//pthread_mutex_lock(&lock);

		count_preSec = count - count_temp;
		count_temp = count;

		//read value from pot to set the next array size 
		int potVal = readFromFile(A2D_FILE_VOLTAGE0);
		int nextSize_temp = Convert_potVal_toArraySize(potVal);
		pthread_mutex_lock(&lock);
		nextSize = nextSize_temp;
		pthread_mutex_unlock(&lock);

		Sleeeep(1,0);
	}
}


void Display_numberofSortedArray_lastSecond(){
	//display number of arrays sorted in previous second on Beaglebone's 14-Seg display via I2C
	//display number in base of 10. display 99 if it's > 99
	while(!stop){
		//calculate the hex values of left and right digits
		int leftDigit = 0;
		int rightDigit = 0;

		if (count_preSec > 99) {
			leftDigit = 9;
			rightDigit = 9;
		} 
		else{
			leftDigit = floor(count_preSec/10);
			rightDigit = count_preSec%10;
		}
		
		//display
		displayDigits(leftDigit, rightDigit);
		
	}
}

// long long Sorter_getNumberArraysSorted(void)
// {
// 	//return the total number of arrays sorted so far. It's gonna be a large number
// 	return count;
// }
void Sorter_initArray(void){
	arr = malloc(currSize * sizeof(int));
}

void Sorter_freeArray(void)
{
	free(arr);
	arr = NULL;
}

// int Sorter_getArrayLength(void)
// {
// 	return currSize;
// }

// int* Sorter_getArrayData(int *length)
// {
// 	return arr;
// }


