
# CC = /opt/arm-2009q1/bin/arm-none-linux-gnueabi-gcc
CC = gcc
APP = test

SRC =

OBJS1 = $(APP).o
OBJS2 = $(SRC)cJSON.o

OBJS=$(OBJS1) $(OBJS2)

CFLAGS=-g -o

LINKOPTS =

MY_INC= 
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
