#include  "sleep.h"

void Sleeeep(long s, long ns){
	struct timespec reqDelay = {s, ns};
	nanosleep(&reqDelay, (struct timespec *) NULL);
}
