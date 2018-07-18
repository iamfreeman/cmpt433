#include "server.h"


#define PORT 12345
#define BUFSIZE 15000 //max # of bytes to contain return message of the largest return message with array length 2063
#define ELEMENT 15 //max # of bytes for displaying one array element
#define CLEAR 0 //value to for memset
bool stop = false;

extern int count;
extern int* arr;
extern int currSize;
extern pthread_mutex_t lock;


void help(int s, struct sockaddr* cliaddr, socklen_t addrlen){

	char* return_message = malloc( sizeof(char) * BUFSIZE );

    memset(return_message, CLEAR, BUFSIZE);

    strcpy(return_message, "Accepted command examples:\n");

    strcat(return_message, "count -- display number arrays sorted.\n");

    strcat(return_message, "get length -- display length of array currently being sorted.\n");

    strcat(return_message, "get array -- display the full array being sorted.\n");

    strcat(return_message, "get 10 -- display the tenth element of array currently being sorted.\n");

    strcat(return_message, "stop -- cause the server program to end.\n\n");

    sendto(s, return_message, BUFSIZE, MSG_CONFIRM, cliaddr, addrlen);

	free(return_message);
}

void get_count(int s, struct sockaddr* cliaddr, socklen_t addrlen){
	char* return_message = malloc( sizeof(char) * BUFSIZE );

    memset(return_message, CLEAR, BUFSIZE);

	sprintf(return_message, "Number of arrays sorted = %i\n\n", count);

	sendto(s, return_message, BUFSIZE, MSG_CONFIRM, cliaddr, addrlen);

	free(return_message);
}

void get_length(int s, struct sockaddr* cliaddr, socklen_t addrlen){
	char* return_message = malloc( sizeof(char) * BUFSIZE );

	memset(return_message, CLEAR, BUFSIZE);

	sprintf(return_message, "Current array length = %i\n\n", currSize);

	sendto(s, return_message, BUFSIZE, MSG_CONFIRM, cliaddr, addrlen);

	free(return_message);
}


void get_index(int s, struct sockaddr* cliaddr, socklen_t addrlen, int index){
	char* return_message = malloc( sizeof(char) * BUFSIZE );
	
    memset(return_message, CLEAR, BUFSIZE);

    pthread_mutex_lock(&lock);
	
	if (index >= 0 && index < currSize) sprintf(return_message, "Vale %i = %i\n\n", index, arr[index]);

	else sprintf(return_message, "Invalid index, try again \n\n");
		
	pthread_mutex_unlock(&lock);

	sendto(s, return_message, BUFSIZE, MSG_CONFIRM, cliaddr, addrlen);

	free(return_message);
}

void get_array(int s, struct sockaddr* cliaddr, socklen_t addrlen){
	
	pthread_mutex_lock(&lock);

	char* return_message = malloc( sizeof(char) * BUFSIZE );
	memset(return_message, CLEAR, BUFSIZE);

	for (int i = 0; i < currSize-2; i++)
	{
		char* array_value = malloc( sizeof(char) * ELEMENT );
		memset(array_value, 0,ELEMENT * sizeof(char));
		sprintf(array_value, "%i, ", arr[i]);
		strcat(return_message, array_value);
		free(array_value);
	}
	char* array_value2 = malloc( sizeof(char) * ELEMENT );
	memset(array_value2, CLEAR, ELEMENT * sizeof(char));
	sprintf(array_value2, "%i\n\n", arr[currSize-1]);
	strcat(return_message, array_value2);
	free(array_value2);

	sendto(s, return_message, BUFSIZE, MSG_CONFIRM, cliaddr, addrlen);
	free(return_message);

	pthread_mutex_unlock(&lock);

}

void shut_down_sorter(int s, struct sockaddr* cliaddr, socklen_t addrlen){
	stop = true;

	Sorter_freeArray();

	turnOffBothDigits();

	char* return_message = malloc( sizeof(char) * BUFSIZE );

    memset(return_message, CLEAR, BUFSIZE);

    strcpy(return_message, "Program Terminating\n\n");
		
	sendto(s, return_message, BUFSIZE, MSG_CONFIRM, cliaddr, addrlen);

	free(return_message);

}

void Unknown(int s, struct sockaddr* cliaddr, socklen_t addrlen){
	char* return_message = malloc( sizeof(char) * BUFSIZE );

    memset(return_message, CLEAR, BUFSIZE);

    strcpy(return_message, "Unknown Command, try again\n\n");
		
	sendto(s, return_message, BUFSIZE, MSG_CONFIRM, cliaddr, addrlen);

	free(return_message);
}


int Server(){
	
	//Create_socket();

	struct sockaddr_in myaddr; // my address 
	struct sockaddr_in cliaddr; // client address
	socklen_t addrlen = sizeof(cliaddr); // length of addresses
	int reclen; //# of bytes received
	int s; // socket 
	
	//create socket and bind socket to port 12345
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
		perror("create socket failed\n"); 
		return 0; 
	} 
	memset((char *)&myaddr, CLEAR, sizeof(myaddr)); 
	myaddr.sin_family = AF_INET; 
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	myaddr.sin_port = htons(PORT); 
	if (bind(s, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) { 
		perror("bind socket failed"); 
		return 0; 
	}

	printf("Server successfully running on port 12345!\n");

	//listening to incoming packets
	while(!stop){
		char* buf = malloc(sizeof(char) * BUFSIZE); /* receive buffer */ /* create a UDP socket */ 
		reclen = recvfrom(s, buf, BUFSIZE, 0, (struct sockaddr *)&cliaddr, &addrlen);
		int index = 0;

		if (reclen > 0) {
			buf[reclen] = '\0';

			if ( strcmp(buf, "\n") == 0 ) continue;
			
			else if	( strcmp(buf, "help\n") == 0 )	help( s, (struct sockaddr *)&cliaddr, addrlen);
				
			else if ( strcmp(buf, "count\n") == 0 )	get_count( s, (struct sockaddr *)&cliaddr, addrlen);
				
			else if ( strcmp(buf, "get length\n") == 0 ) get_length( s, (struct sockaddr *)&cliaddr, addrlen);
	
			else if ( strcmp(buf, "get array\n") == 0 )	get_array( s, (struct sockaddr *)&cliaddr, addrlen);
				
			else if ( strcmp(buf, "stop\n") == 0 )	shut_down_sorter( s, (struct sockaddr *)&cliaddr, addrlen);

			else if ( sscanf(buf, "get %i\n", &index) == 1 ){
				//printf("size of reclen = %i\n", reclen);
				get_index( s, (struct sockaddr *)&cliaddr, addrlen, index);
			}
			
			else 	Unknown( s, (struct sockaddr *)&cliaddr, addrlen);
				
		}
		free(buf);
		
	}
	return 1;
}