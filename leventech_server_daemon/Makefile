CROSS_COMPILE_ANDROID=	/opt/toolchains/arm-2009q3/bin/arm-none-linux-gnueabi-
CCARM=	$(CROSS_COMPILE_ANDROID)gcc
CC = gcc
CCMAC = gcc-4.8
CFLAGS  = -Wall -std=gnu99 -ggdb
RM      = rm -f
#I2C functions
LDLIBS+=i2c.c
#parsing ini files 
LDLIBS+=inih/ini.c
#parse\serialize JSON
LDLIBS+=parson/parson.c
#stepmotor
LDLIBS+=leventech_step_motor/stepmotor.c
#gpio
LDLIBS+=leventech_step_motor/gpio.c

##Server complier is cross compile android


server_daemon: server.c
	$(CCARM) $(CFLAGS)  -static -o server_daemon server.c  $(LDLIBS)  -lpthread
server_daemon_send: send.c
	$(CCARM) $(CFLAGS)  -static -o server_daemon_send send.c





src=$(wildcard *.cpp *.hpp *.c *.h */*.c */*.cpp */*.h */*.hpp)

astyle:
	astyle --style=linux --lineend=linux --indent=force-tab=8 --pad-header --pad-oper --keep-one-line-blocks \
                --unpad-paren ${src}
clean :
	$(RM) server_daemon server_daemon_send


