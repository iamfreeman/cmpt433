OUTFILE = sorter

OUTDIR = $(HOME)/cmpt433/public/myApps

CROSS_COMPILE = arm-linux-gnueabihf-

CC_C = $(CROSS_COMPILE)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L-Werror -pthread -lm

SRC = sleep.c file.c bus1.c sorter.c server.c run_sorter_program.c main.c

all:
	$(CC_C) $(CFLAGS) $(SRC) -o $(OUTDIR)/$(OUTFILE)
	
clean:
	rm $(OUTDIR)/$(OUTFILE)