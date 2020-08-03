CROSS_COMPILE=/home/idan/arm-2009q3/bin/arm-none-linux-gnueabi-
#CC=	$(CROSS_COMPILE)gcc
#CROSS_COMPILE=  /opt/arm-2014.05/bin/arm-none-linux-gnueabi-
CC=    $(CROSS_COMPILE)gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: stepmotor

stepmotor: main.c 
	$(CC) $(CFLAGS)  -static -o stepmotor.o main.c gpio.c stepmotor.c -lpthread
	


clean :
	$(RM) *.o
