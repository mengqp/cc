OBJS = main.o
# CC = /opt/wisermind_9G45/bin/arm-none-linux-gnueabi-g++
CC = gcc
LINKOPTS=-c -g
LINK1OPTS = -g -o
main:$(OBJS)
	$(CC) $(OBJS) $(LINK1OPTS) $@

main.o:main.c
	$(CC) $(LINKOPTS) $<


clean:
	rm -f $(OBJS) main
