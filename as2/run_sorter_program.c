#include "sorter.h"
#include "server.h"
#include "file.h"
#include "bus1.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>

void run_sorter_program(void){
	initADC();
	initI2C();
	Sorter_initArray();
	
	//create thread id
	pthread_t thread1, thread2, thread3, thread4;
	
	//create attributes
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_attr_t attr2;
	pthread_attr_init(&attr2);
	pthread_attr_t attr3;
	pthread_attr_init(&attr3);
	pthread_attr_t attr4;
	pthread_attr_init(&attr4);

	//create threads with selected function
	pthread_create(&thread1, &attr1, (void*)Sorter_startSorting, NULL);
	pthread_create(&thread2, &attr2, (void*)Sorter_setArraySize, NULL);
	pthread_create(&thread3, &attr3, (void*)Display_numberofSortedArray_lastSecond, NULL);
	pthread_create(&thread4, &attr4, (void*)Server, NULL);

	//wait for threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
}