CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -g
calendar: calendar.c
	$(CC) $(CFLAGS) -o calendar calendar.c
cross:
	arm-linux-gnueabihf-gcc $(CFLAGS) -o calendar_arm calendar.c