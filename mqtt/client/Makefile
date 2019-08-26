CFLAGS=-Wall -ggdb -I/root/srcp/mqtt/mosquitto/lib/
# LDFLAGS=-L../../lib ../../lib/cpp/libmosquittopp.so.1 ../../lib/libmosquitto.so.1
# LDFLAGS=  -lmosquittopp -lmosquitto
# LDFLAGS= /root/srcp/mqtt/mosquitto/lib/libmosquitto.so.1 /root/srcp/mqtt/mosquitto/lib/cpp/libmosquittopp.so.1  /usr/lib/libssl.so.1.0.0 /usr/lib/libcrypto.so.1.0.0
CXX=/opt/arm_linux_4.8/bin/arm-linux-g++
CC=/opt/arm_linux_4.8/bin/arm-linux-gcc

# LDFLAGS=  /root/srcp/uuid/uuid/lib/libuuid.so /root/srcp/openssl/neweem/lib/libcrypto.so.1.1 /root/srcp/openssl/neweem/lib/libssl.so.1.1 /root/srcp/mqtt/mosquitto/lib/libmosquitto.so.1 /root/srcp/mqtt/mosquitto/lib/cpp/libmosquittopp.so.1
LDFLAGS=  /root/srcp/uuid/uuid/lib/libuuid.so /root/srcp/openssl/openssl-neweem/libssl.so.1.0.0 /root/srcp/openssl/openssl-neweem/libcrypto.so.1.0.0 /root/srcp/mqtt/mosquitto/lib/libmosquitto.so.1 /root/srcp/mqtt/mosquitto/lib/cpp/libmosquittopp.so.1

.PHONY: all clean

all : main

main : main.o
	${CXX} $^ -o $@ ${LDFLAGS}

main.o : main.c
	${CXX} -c $^ -o $@ ${CFLAGS}

# temperature_conversion.o : temperature_conversion.cpp
# 	${CXX} -c $^ -o $@ ${CFLAGS}

clean :
	-rm -f *.o main
