CC 	= gcc
CFLAGS 	= -I ./include -Wall -std=c99

lib:main.c include/zimonzk/lists.h
	$(CC) $(CFLAGS) -c $<
	ar -rcs liblists.a main.o


	
