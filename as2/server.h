#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#include "sorter.h"



void help(int fd, struct sockaddr* remaddr, socklen_t addrlen);
void get_count(int fd, struct sockaddr* remaddr, socklen_t addrlen);
void get_index(int fd, struct sockaddr* remaddr, socklen_t addrlen, int index);
void get_length(int fd, struct sockaddr* remaddr, socklen_t addrlen);
void get_array(int fd, struct sockaddr* remaddr, socklen_t addrlen);
void shut_down_sorter(int fd, struct sockaddr* remaddr, socklen_t addrlen);
void Unknown(int fd, struct sockaddr* remaddr, socklen_t addrlen);

int Server(void);

#endif