OBJS = GroupBroad.o main.o
# CC = /opt/wisermind_9G45/bin/arm-none-linux-gnueabi-g++
# CC =	/opt/wisermind_MPC83xx/bin/powerpc-e300c3-linux-gcc 
CC = gcc 
LINKOPTS=-c -g
LINK1OPTS = -g -o 
main:$(OBJS)
	$(CC) $(OBJS) $(LINK1OPTS) $@

GroupBroad.o:GroupBroad.c GroupBroad.h
	$(CC) $(LINKOPTS) $< 

main.o:main.c GroupBroad.h
	$(CC) $(LINKOPTS) $< 


clean:
	rm -f $(OBJS) main



