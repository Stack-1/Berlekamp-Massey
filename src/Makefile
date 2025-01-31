CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror
SRCS = main.c io/io.c


all:
	@$(CC) $(CFLAGS) $(SRCS) -o berlekamp_massey

clean:
	@rm -f *.o
	@rm -f **/*.o
	@rm -f **/**/*.o

.PHONY: all clean