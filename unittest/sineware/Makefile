
# CC = /opt/arm-2009q1/bin/arm-none-linux-gnueabi-gcc
CC = gcc
APP = unittest

SRC = ../../src/sinewave/

OBJS1 = $(APP).o
OBJS2 = $(SRC)sinewave.o

OBJS=$(OBJS1) $(OBJS2)

CFLAGS=-g -o

LINKOPTS = -fno-stack-protector -lbcunit -dynamic -lm -lpthread -dl

MY_INC= -I$(SRC)
MY_LIBS=


MY_DEPS=$(MY_LIBS) $(MY_INC)

$(APP):$(OBJS)
	$(CC) $(CFLAGS) $@  $(OBJS) $(MY_DEPS) $(LINKOPTS)

$(OBJS2): $(SRC)%.o:$(SRC)%.c
	$(CC) -c $< $(MY_INC) $(CFLAGS) $@

$(OBJS1): %.o:%.c
	$(CC) -c $< $(MY_INC) $(CFLAGS) $@


#clean
.PHONY : clean
clean:
	rm -f $(OBJS) $(APP)
