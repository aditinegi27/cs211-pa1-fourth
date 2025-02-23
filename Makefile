CC=gcc
CFLAG = -fsanitize=address,undefined -Og -g -Wall -Werror -std=c11 -lm

fourth: fourth.c 
	$(CC) -o fourth fourth.c $(CFLAG)
clean: fourth 
	rm -f fourth
