CC = gcc
CFLAGS = -Wall

all: wash

wash: wash.c
        $(CC) $(CFLAGS) -o wash.c

clean:
        rm -f *.o wash.c *~

print:
        a2ps -L70 --delegate=no -T 4 -q -Avirtual -2 -o xd wash.c

